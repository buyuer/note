#include <cstdio>
#include <iostream>
#include <streambuf>

template <typename Char, std::streamsize BuffSize = 512>
class BasicStreamBuf : public std::basic_streambuf<Char> {
public:
    using CharT = Char;

    BasicStreamBuf() { this->setp(put_buff_, put_buff_ + BuffSize); }

protected:
    virtual std::streamsize write(CharT* p, std::streamsize size) { return 0; }

private:
    using Base = std::basic_streambuf<CharT>;
    CharT put_buff_[BuffSize + 1] {};

    int flush_put_buff()
    {
        auto size = this->pptr() - this->pbase();
        this->setp(put_buff_, put_buff_ + BuffSize);
        return write(put_buff_, size);
    }

    int sync() override { return flush_put_buff() > 0 ? 0 : -1; }

    typename Base::int_type overflow(typename Base::int_type ch) override
    {
        auto ret = flush_put_buff();
        if (ret <= 0) {
            this->pbump(this->epptr() - this->pptr());
            return Base::traits_type::eof();
        }

        if (not Base::traits_type::eq_int_type(ch, Base::traits_type::eof())) {
            *this->pptr() = ch;
            this->pbump(1);
        }

        return Base::traits_type::to_int_type(ch);
    }
};

class FileBuff : public BasicStreamBuf<char, 2> {
public:
    explicit FileBuff(std::FILE* fp_)
        : fp(fp_)
    {
    }

private:
    std::streamsize write(CharT* p, std::streamsize size) override
    {
        return std::fwrite(p, 1, size, fp);
    }

    std::FILE* fp {};
};

int main(int argc, char* argv[])
{
    FileBuff buff { stdout };
    std::ostream out { &buff };
    out << 123 << std::flush << "hello" << std::endl
        << 456 << "world" << std::flush;

    return 0;
}
