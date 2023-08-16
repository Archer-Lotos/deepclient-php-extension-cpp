#include "DeepClient.h"

using namespace boost::python;

DeepClient::DeepClient() {
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
