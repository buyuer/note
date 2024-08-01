#include <cstdlib>
#include <utility>

class OnlyStack {
public:
    int a { 5 };

    template <typename... ARGS> static OnlyStack* create(ARGS&&... args)
    {
        return new OnlyStack(std::forward<ARGS>(args)...);
    }

private:
    void* operator new(const std::size_t count)
    {
        auto ptr = ::operator new(count);
        new (ptr) OnlyStack();
        return ptr;
    }

    void* operator new(std::size_t, void* ptr) { return ptr; }
};

class OnlyHeap {
public:
    void del() { delete this; }

private:
    ~OnlyHeap() = default;
};

int main()
{
    auto test1 = OnlyStack::create();
    delete test1;
    OnlyStack test2;

    // 编译报错
    // OnlyHeap a;
    auto test3 = new OnlyHeap();
    test3->del();
    // 编译报错
    // delete test3;
}