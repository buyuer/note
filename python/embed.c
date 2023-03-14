#include <Python.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void print_from_py(const char *str, long num)
{
    PyObject *pyModule_builtins =
        PyImport_Import(PyUnicode_FromString("builtins"));
    if (!pyModule_builtins)
    {
        perror("failed\n");
        return;
    }
    PyObject *pyFunc_print = PyObject_GetAttrString(pyModule_builtins, "print");
    if (!pyFunc_print)
    {
        perror("failed\n");
        return;
    }

    PyObject *pyTuple_args   = PyTuple_New(2);
    PyObject *pyUnicode_arg1 = PyUnicode_FromString(str);
    PyObject *pyLong_arg2    = PyLong_FromLong(num);
    PyTuple_SetItem(pyTuple_args, 0, pyUnicode_arg1);
    PyTuple_SetItem(pyTuple_args, 1, pyLong_arg2);

    PyObject *py_ret = PyObject_CallObject(pyFunc_print, pyTuple_args);
    printf("print return type is %s", py_ret->ob_type->tp_name);

    /* 不再使用，减少引用计数 */
    Py_DECREF(py_ret);
    Py_DECREF(pyUnicode_arg1);
    Py_DECREF(pyLong_arg2);
    // Py_DECREF(pyTuple_args);
    Py_DECREF(pyFunc_print);
    Py_DECREF(pyModule_builtins);
}

int main(int argc, char *argv[])
{
    const char *env_pyhome = "PYTHONHOME=" PYTHONHOME;
    const char *env_pypath = "PYTHONPATH=" PYTHONHOME "/lib";

    putenv(env_pyhome);
    putenv(env_pypath);

    wchar_t *program = Py_DecodeLocale(argv[0], NULL);

    Py_SetProgramName(program);
    Py_Initialize();
    PyRun_SimpleString("print('Hello python!')");

    print_from_py("hello", 123);

    if (Py_FinalizeEx() < 0)
    {
        exit(12);
    }
    PyMem_RawFree(program);
    return 0;
}