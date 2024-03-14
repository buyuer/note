#include <Python.h>

#include <stdio.h>

static PyObject* mypy_hello(PyObject* self, PyObject* args)
{
    printf("hello mypy\n");
    return Py_None;
}

static PyObject* mypy_system(PyObject* self, PyObject* args)
{
    const char* command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return PyLong_FromLong(sts);
}

static PyMethodDef mypy_methods[] = {
    { "system", mypy_system, METH_VARARGS, "Execute a shell command." },
    { "hello", mypy_hello, METH_VARARGS, "Print hello." },
    { NULL, NULL, 0, NULL },
};

static struct PyModuleDef mypy_module = {
    PyModuleDef_HEAD_INIT, "mypy", "my py module", -1, mypy_methods,
};

PyMODINIT_FUNC PyInit_mypy(void) { return PyModule_Create(&mypy_module); }