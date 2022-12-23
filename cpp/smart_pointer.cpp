#include <iostream>
#include <memory>

static void do_1(std::unique_ptr<int[]> up) {
    if (up) {
        std::cout << up[0] << std::endl;
    }
}

static void do_2(std::shared_ptr<int[]> sp) {
    if (sp) {
        std::cout << "temp   use_count() " << sp.use_count() << std::endl;
    }
}

int main(int argc, char *argv[]) {
    std::unique_ptr<int[]> up(new int[10]{2});

    do_1(std::move(up));
    std::cout << bool(up) << std::endl;

    std::shared_ptr<int[]> sp(new int[10]{1});

    auto sp2{sp}, sp3{sp}, sp4{sp2};

    std::cout << "before use_count() " << sp2.use_count() << std::endl;
    do_2(sp);
    std::cout << "after  use_count() " << sp2.use_count() << std::endl;

    return 0;
}
