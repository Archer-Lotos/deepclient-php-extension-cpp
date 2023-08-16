#include "DeepClient.h"

#include <boost/python.hpp>
#include <php.h>
#include <map>
#include <vector>

using namespace boost::python;

class DeepClient {
public:
    std::map<int, std::string> _ids;
    std::map<std::string, std::string> _serialize;

    std::map<std::string, boost::python::object> _functions;

    DeepClient() {
        _functions["select"] = boost::python::make_function(
                boost::python::detail::bind(&DeepClient::select, this),
                boost::python::default_call_policies(),
                boost::mpl::vector<>()
        );

        _functions["insert"] = boost::python::make_function(
                boost::python::detail::bind(&DeepClient::insert, this),
                boost::python::default_call_policies(),
                boost::mpl::vector<>()
        );
    }


    boost::python::object select() {
        return boost::python::object("select method called");
    }

    boost::python::object insert() {
        return boost::python::object("insert method called");
    }

};

BOOST_PYTHON_MODULE(example) {
    class_<DeepClient>("DeepClient")
            .def("__init__", make_constructor(boost::python::detail::construct<DeepClient>()))
            .def("select", &DeepClient::select)
            .def("insert", &DeepClient::insert)
            ;
}


extern "C" {
    ZEND_FUNCTION(deepclient_select);
    ZEND_FUNCTION(deepclient_insert);
}

zend_function_entry deepclient_functions[] = {
        ZEND_FE(deepclient_select, NULL)
        ZEND_FE(deepclient_insert, NULL)
        // Добавьте здесь остальные функции
        {NULL, NULL, NULL}
};

zend_module_entry deepclient_module_entry = {
        STANDARD_MODULE_HEADER,
        "deepclient",
        deepclient_functions,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NO_VERSION_YET,
        STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(deepclient)

ZEND_FUNCTION(deepclient_select) {
    zend_parse_parameters_none();

    DeepClient deepClient;

    boost::python::dict result = deepClient.select(boost::python::object(), boost::python::dict());

    std::ostringstream resultStream;
    boost::python::extract<const char*> resultExtractor(result);
    if (resultExtractor.check()) {
        resultStream << resultExtractor();
        RETURN_STRING(resultStream.str().c_str());
    } else {
        RETURN_NULL();
    }
}

ZEND_FUNCTION(deepclient_insert) {
    zend_parse_parameters_none();

    DeepClient deepClient;

    boost::python::dict result = deepClient.insert(boost::python::object(), boost::python::dict());

    std::ostringstream resultStream;
    boost::python::extract<const char*> resultExtractor(result);
    if (resultExtractor.check()) {
        resultStream << resultExtractor();
        RETURN_STRING(resultStream.str().c_str());
    } else {
        RETURN_NULL();
    }
}
