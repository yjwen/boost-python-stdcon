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

template<typename Set>
Set make_set(size_t sz)
{
  Set s;
  for (size_t i = 0; i < sz; ++i) {
    s.insert(i);
  }
  return s;
}

template<typename Set>
Set const & insert_return(typename Set::value_type v)
{
  static Set s;
  s.insert(v);
  return s;
}

template<typename Map>
Map make_map(typename Map::key_type k, typename Map::mapped_type v)
{
  Map m;
  m[k] = v;
  return m;
}

template<typename Map>
Map const & update_map(typename Map::key_type k, typename Map::mapped_type v)
{
  static Map m;
  m[k] =v;
  return m;
}


void def_return_value() {
  py::def("make_vec", &make_seq<vector<int>>, py::copy_return_value<>());
  py::def("vec_append_return", &append_return<vector<int>>, py::copy_return_value<>());

  py::def("make_list", &make_seq<list<int>>, py::copy_return_value<>());
  py::def("list_append_return", &append_return<list<int>>, py::copy_return_value<>());

  py::def("make_flist", &make_seq<forward_list<int>, false>, py::copy_return_value<>());
  py::def("flist_append_return", &append_return<forward_list<int>, false>, py::copy_return_value<>());

  py::def("make_set", &make_set<set<int>>, py::copy_return_value<>());
  py::def("set_insert_return", &insert_return<set<int>>, py::copy_return_value<>());

  py::def("make_uset", &make_set<unordered_set<int>>, py::copy_return_value<>());
  py::def("uset_insert_return", &insert_return<unordered_set<int>>, py::copy_return_value<>());

  py::def("make_map", &make_map<map<int, char>>, py::copy_return_value<>());
  py::def("update_map", &make_map<map<int, char>>, py::copy_return_value<>());

  py::def("make_umap", &make_map<unordered_map<int, char>>, py::copy_return_value<>());
  py::def("update_umap", &make_map<unordered_map<int, char>>, py::copy_return_value<>());

}

