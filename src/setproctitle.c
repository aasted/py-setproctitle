/*-------------------------------------------------------------------------
 *
 * setproctitle.c
 *    Python extension module to update and read the process title.
 *
 * Copyright (c) 2009-2012 Daniele Varrazzo <daniele.varrazzo@gmail.com>
 *
 * The module allows Python code to access the functions get_ps_display()
 * and set_ps_display().
 *
 *-------------------------------------------------------------------------
 */

#include "spt.h"
#include "spt_setup.h"
#include "spt_status.h"

#ifndef SPT_VERSION
#define SPT_VERSION unknown
#endif

/* macro trick to stringify a macro expansion */
#define xstr(s) str(s)
#define str(s) #s

/* ----------------------------------------------------- */

static PyObject *spt_version;


static char spt_setproctitle__doc__[] =
"setproctitle(title) -- Change the process title."
;

static PyObject *
spt_setproctitle(PyObject *self, PyObject *args, PyObject *kwargs)
{
    const char *title = NULL;
    static char *kwlist[] = {"title", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s", kwlist, &title))
        return NULL;

    set_ps_display(title, true);

    Py_INCREF(Py_None);
    return Py_None;
}


static char spt_getproctitle__doc__[] =
"getproctitle() -- Get the current process title."
;

static PyObject *
spt_getproctitle(PyObject *self, PyObject *args)
{
    size_t tlen;
    const char *title;
    title = get_ps_display(&tlen);

    return Py_BuildValue("s#", title, (int)tlen);
}


/* List of methods defined in the module */

static struct PyMethodDef spt_methods[] = {
    {"setproctitle",
        (PyCFunction)spt_setproctitle,
        METH_VARARGS|METH_KEYWORDS,
        spt_setproctitle__doc__},

    {"getproctitle",
        (PyCFunction)spt_getproctitle,
        METH_NOARGS,
        spt_getproctitle__doc__},

    {NULL, (PyCFunction)NULL, 0, NULL}        /* sentinel */
};


/* Initialization function for the module (*must* be called initsetproctitle) */

static char setproctitle_module_documentation[] =
"Allow customization of the process title."
;

#ifdef IS_PY3K

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "setproctitle",
    setproctitle_module_documentation,
    -1,
    spt_methods,
    NULL,
    NULL,
    NULL,
    NULL
};

#endif

PyMODINIT_FUNC
INIT_MODULE(setproctitle)(void)
{
    PyObject *m, *d;

    spt_debug("module init");

    /* Create the module and add the functions */
#ifdef IS_PY3K
    m = PyModule_Create(&moduledef);
#else
    m = Py_InitModule3("setproctitle", spt_methods,
        setproctitle_module_documentation);
#endif
    if (m == NULL) { goto exit; }

    /* Add version string to the module*/
    d = PyModule_GetDict(m);
    spt_version = Py_BuildValue("s", xstr(SPT_VERSION));
    PyDict_SetItemString(d, "__version__", spt_version);

    /* Initialize the process title */
    spt_setup();

    /* Check for errors */
    if (PyErr_Occurred()) {
        Py_FatalError("can't initialize module setproctitle");
        Py_DECREF(m);
        m = NULL;
    }

exit:

#ifdef IS_PY3K
    return m;
#else
    return;
#endif

}

