#include <list>
#include <vector_arg.hpp>

using namespace std;
namespace py = boost::python;

template<typename SEQ>
size_t seq_size(SEQ v){return v.size();}

void def_mixed()
{
  py::class_<vector<float>>("float_vector");
  py::class_<list<float>>("float_list");

  // These two functions are both registered as accepting
  // Python list, even if vector<float> is already registered as a Python
  // extension class, due to the included file <vector_arg.hpp>
  py::def("int_vector_size", &seq_size<vector<int>>);
  py::def("float_vector_size", &seq_size<vector<float>>);

  // However, this function is registered as accepting the Python
  // extension class of type vector<float>, as its argument is of
  // lvalue type that is not overwritten by boost-std-con
  py::def("float_vector_size_lvalue", &seq_size<vector<float>&>);

  // This function is also registered as accepting the Python
  // extension class of type list<float>, unless <list_arg.hpp> is
  // included
  py::def("float_list_size", &seq_size<list<float>>);
}
  
