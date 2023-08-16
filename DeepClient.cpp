using namespace boost::python;

class DeepClientWrapper
{
public:
    DeepClientWrapper()
    {
        class_<DeepClient>("DeepClient")
                .def("select", &DeepClient::select)
                .def("insert", &DeepClient::insert)
                .def("update", &DeepClient::update)
                .def("delete", &DeepClient::delete_)
                .def("serial", &DeepClient::serial)
                .def("reserve", &DeepClient::reserve)
                .def("wait_for", &DeepClient::wait_for)
                .def("id", &DeepClient::id)
                .def("id_local", &DeepClient::id_local)
                .def("guest", &DeepClient::guest)
                .def("jwt", &DeepClient::jwt)
                .def("whoami", &DeepClient::whoami)
                .def("login", &DeepClient::login)
                .def("logout", &DeepClient::logout)
                .def("can", &DeepClient::can)
                .def("name", &DeepClient::name)
                .def("name_local", &DeepClient::name_local);
    }
};

BOOST_PYTHON_MODULE(example)
        {
                DeepClientWrapper();
        }