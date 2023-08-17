#include <php.h>
#include <boost/python.hpp>

extern "C" {
#include "ext_php_headers/standard/info.h"
}

using namespace boost::python;

PHP_FUNCTION(php_make_deep_client) {
    const char *token;
    size_t token_len;
    const char *url;
    size_t url_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_STRING(token, token_len)
            Z_PARAM_STRING(url, url_len)
    ZEND_PARSE_PARAMETERS_END();

    Py_Initialize();
    try {
        python_exec("from deep_client_interface import DeepClient");
        python_eval("def make_deep_client(token, url):\n"
                    "    if not token:\n"
                    "        raise ValueError('No token provided')\n"
                    "    if not url:\n"
                    "        raise ValueError('No url provided')\n"
                    "    return DeepClient()");
        python_eval("result = make_deep_client('" + std::string(token) + "', '" + std::string(url) + "')");

        // TODO: Convert the Python result to a PHP object

    } catch (error_already_set const &) {
        PyErr_Print();
    }
    Py_Finalize();
}

PHP_MINFO_FUNCTION(deep_client_cpp_extension) {
    php_info_print_table_start();
    php_info_print_table_header(2, "deep_client_cpp_extension support", "enabled");
    php_info_print_table_end();
}

zend_function_entry deep_client_cpp_extension_functions[] = {
        PHP_FE(php_make_deep_client, NULL)
        PHP_FE_END
};

zend_module_entry deep_client_cpp_extension_module_entry = {
        STANDARD_MODULE_HEADER,
        "deep_client_php_extension",
        deep_client_cpp_extension_functions,
        NULL,
        NULL,
        NULL,
        NULL,
        PHP_MINFO(deep_client_cpp_extension),
        NULL,
        NULL,
        NULL,
        STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_DEEP_CLIENT_CPP_EXTENSION
ZEND_GET_MODULE(deep_client_cpp_extension)
#endif
