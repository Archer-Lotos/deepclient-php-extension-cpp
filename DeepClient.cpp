#include "DeepClient.h"

DeepClient::DeepClient() {
    _functions["select"] = boost::python::make_function(&DeepClient::select);
    _functions["insert"] = boost::python::make_function(&DeepClient::insert);
}

boost::python::dict DeepClient::select(boost::python::object exp, boost::python::dict options) {
    return boost::python::dict();
}

boost::python::dict DeepClient::insert(boost::python::object objects, boost::python::dict options) {
    return boost::python::dict();
}

boost::python::object select(boost::python::object exp, boost::python::dict options)
{
    return boost::python::object("select");
}

boost::python::object insert(boost::python::object objects, boost::python::dict options)
{
    return boost::python::object("insert");
}

