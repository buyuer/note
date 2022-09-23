#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
    auto id = std::this_thread::get_id();
    std::cout << id << std::endl;
}