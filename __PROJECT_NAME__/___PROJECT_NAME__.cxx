/* csankey.cpp | MIT License | https://github.com/kirin123kirin/csankey/raw/main/LICENSE */
#include "__PROJECT_NAME__.hpp"

extern "C" PyObject* __PROJECT_NAME___py(PyObject* self, PyObject* args, PyObject* kwargs) {
    PyObject* o;

    const char* kwlist[2] = {"o", NULL};

    if(!PyArg_ParseTupleAndKeywords(args, kwargs, "O", (char**)kwlist, &o))
        return NULL;

    if(!PyList_Check(o) && !PyTuple_Check(o))
        return PyErr_Format(PyExc_TypeError, "argument is list or tuple object only.");

    return hello();
}

#define MODULE_NAME ___PROJECT_NAME__
#define MODULE_NAME_S "___PROJECT_NAME__"

/* {{{ */
// this module description
#define MODULE_DOCS                       \
    "__PROJECT_NAME__ Overview.\n" \
    "Description xxxx.\n"                 \
    ""

#define __PROJECT_NAME___py_DESC "\n"

/* }}} */
#define PY_ADD_METHOD(py_func, c_func, desc) \
    { py_func, (PyCFunction)c_func, METH_VARARGS, desc }
#define PY_ADD_METHOD_KWARGS(py_func, c_func, desc) \
    { py_func, (PyCFunction)c_func, METH_VARARGS | METH_KEYWORDS, desc }

/* Please extern method define for python */
/* PyMethodDef Parameter Help
 * https://docs.python.org/ja/3/c-api/structures.html#c.PyMethodDef
 */
static PyMethodDef py_methods[] = {
    PY_ADD_METHOD_KWARGS("__PROJECT_NAME__", __PROJECT_NAME___py, __PROJECT_NAME___py_DESC),
    {NULL, NULL, 0, NULL}};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef py_defmod = {PyModuleDef_HEAD_INIT, MODULE_NAME_S, MODULE_DOCS, 0, py_methods};
#define PARSE_NAME(mn) PyInit_##mn
#if defined(DATETIME_H)
#define PARSE_FUNC(mn)                      \
    PyMODINIT_FUNC PARSE_NAME(mn)() {       \
        PyDateTime_IMPORT;                  \
        return PyModule_Create(&py_defmod); \
    }
#else
#define PARSE_FUNC(mn) \
    PyMODINIT_FUNC PARSE_NAME(mn)() { return PyModule_Create(&py_defmod); }
#endif

#else
#if defined(DATETIME_H)
#define PARSE_NAME(mn)                                                \
    init##mn(void) {                                                  \
        PyDateTime_IMPORT;                                            \
        (void)Py_InitModule3(MODULE_NAME_S, py_methods, MODULE_DOCS); \
    }
#else
#define PARSE_NAME(mn) \
    init##mn(void) { (void)Py_InitModule3(MODULE_NAME_S, py_methods, MODULE_DOCS); }
#endif
#define PARSE_FUNC(mn) PyMODINIT_FUNC PARSE_NAME(mn)
#endif

PARSE_FUNC(MODULE_NAME);
