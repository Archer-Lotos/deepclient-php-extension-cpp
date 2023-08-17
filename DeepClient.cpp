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

class GqlPhpWrapper : public Php::Base {
public:
    GqlPhpWrapper() {
        Py_Initialize();
        pyModule = PyImport_ImportModule("gql");
    }

    ~GqlPhpWrapper() {
        Py_DECREF(pyModule);
        Py_Finalize();
    }

    Php::Value executeQuery(const Php::Value& query) {
        Php::Value result;
        if (pyModule) {
            PyObject* pyFunc = PyObject_GetAttrString(pyModule, "execute_query");
            if (pyFunc && PyCallable_Check(pyFunc)) {
                PyObject* pyArgs = PyTuple_Pack(1, PyUnicode_DecodeFSDefault(query.stringValue().c_str()));
                PyObject* pyResult = PyObject_CallObject(pyFunc, pyArgs);
                if (pyResult) {
                    result = Php::Value(PyUnicode_AsUTF8(pyResult));
                    Py_DECREF(pyResult);
                } else {
                    PyErr_Print();
                }
                Py_DECREF(pyArgs);
            } else {
                PyErr_Print();
            }
            Py_XDECREF(pyFunc);
        }
        return result;
    }

private:
    PyObject* pyModule = nullptr;
};

