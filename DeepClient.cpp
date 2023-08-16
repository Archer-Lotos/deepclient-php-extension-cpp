#include "DeepClient.h"

using namespace boost::python;

DeepClient::DeepClient() {
    _functions["select"] = boost::python::make_function(&DeepClient::select);
    _functions["insert"] = boost::python::make_function(&DeepClient::insert);
}


boost::python::object select() {
    return boost::python::object("select method called");
}

boost::python::object insert() {
    return boost::python::object("insert method called");
}
