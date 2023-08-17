#include "DeepClient.h"

extern "C" {
#include "ext_php_headers/standard/info.h"
}

using namespace boost::python;

PHP_FUNCTION(make_deep_client) {
    char *token;
    char *url;
    size_t token_len, url_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_STRING(token, token_len)
            Z_PARAM_STRING(url, url_len)
    ZEND_PARSE_PARAMETERS_END();

    Py_Initialize();
    try {
        // Initialize Python
        PyRun_SimpleString("import sys\n"
                           "sys.path.append('.');"); // Add current directory to sys.path if needed

        // Import the module and get the function
        PyObject *pModule = PyImport_ImportModule("deep_client_interface");
        if (pModule) {
            PyObject *pFunc = PyObject_GetAttrString(pModule, "make_deep_client");
            if (pFunc && PyCallable_Check(pFunc)) {
                PyObject *pArgs = PyTuple_Pack(2, PyUnicode_DecodeFSDefault(token), PyUnicode_DecodeFSDefault(url));
                PyObject *pValue = PyObject_CallObject(pFunc, pArgs);

                if (pValue != NULL) {
                    // TODO: Convert the Python result to a PHP object

                    Py_DECREF(pValue);
                } else {
                    PyErr_Print();
                }

                Py_DECREF(pArgs);
                Py_DECREF(pFunc);
            } else {
                if (PyErr_Occurred()) PyErr_Print();
            }

            Py_DECREF(pModule);
        } else {
            PyErr_Print();
        }
    } catch (error_already_set const &) {
        PyErr_Print();
    }
    Py_Finalize();
}

ZEND_BEGIN_ARG_INFO(arginfo_make_deep_client, 0)
                ZEND_ARG_INFO(0, token)
                ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

PHP_MINFO_FUNCTION(deep_client_php_extension) {
    php_info_print_table_start();
    php_info_print_table_header(2, "deep_client_php_extension support", "enabled");
    php_info_print_table_end();
}

zend_function_entry deep_client_php_extension_functions[] = {
        PHP_FE(make_deep_client, arginfo_make_deep_client)
        PHP_FE_END
};

zend_module_entry deep_client_php_extension_module_entry = {
        STANDARD_MODULE_HEADER,
        "deep_client_php_extension",
        deep_client_php_extension_functions,
        NULL,
        NULL,
        NULL,
        NULL,
        PHP_MINFO(deep_client_php_extension),
        "1.0",
        STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(deep_client_php_extension)
