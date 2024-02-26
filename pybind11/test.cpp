#include <pybind11/pybind11.h>

int add(int i, int j)
{
    printf("result = %d\n", i + j);
    return 0;
}

PYBIND11_MODULE(pybind11_test, m)
{
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");
}
