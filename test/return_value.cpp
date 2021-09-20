#include <copy_return_value.hpp>

using namespace std;
namespace py = boost::python;

template<typename Seq, bool from_back = true>
Seq make_seq(size_t sz)
{
  Seq seq;
  for (size_t i = 0; i < sz; ++i) {
    if constexpr (from_back) {
      seq.push_back(i);
    } else {
      seq.push_front(i);
    }
  }
  return seq;
}

template<typename Seq, bool from_back = true>
Seq const & append_return(typename Seq::value_type v)
{
  static Seq seq;
  if constexpr (from_back) {
    seq.push_back(v);
  } else {
    seq.push_front(v);
  }
  return seq;
}

void def_return_value() {
  py::def("make_vec", &make_seq<vector<int>>, py::copy_return_value<>());
  py::def("vec_append_return", &append_return<vector<int>>, py::copy_return_value<>());

  py::def("make_list", &make_seq<list<int>>, py::copy_return_value<>());
  py::def("list_append_return", &append_return<list<int>>, py::copy_return_value<>());

  py::def("make_flist", &make_seq<forward_list<int>, false>, py::copy_return_value<>());
  py::def("flist_append_return", &append_return<forward_list<int>, false>, py::copy_return_value<>());
}

