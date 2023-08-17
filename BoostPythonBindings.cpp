#include "DeepClient.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(deep_client_python) {
    class_<DeepClient>("DeepClient")
            .def("select", &DeepClient::select)
            .def("insert", &DeepClient::insert);
}