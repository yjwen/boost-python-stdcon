#include <vector_arg.hpp>
#include <list_arg.hpp>
#include <forward_list_arg.hpp>
#include <map_arg.hpp>
#include <unordered_map_arg.hpp>
#include <set_arg.hpp>
#include <unordered_set_arg.hpp>
#include <pair_arg.hpp>
#include <type_traits>

using namespace std;
namespace py = boost::python;

template<typename T>
struct remove_ref_and_const
{
  typedef typename remove_const<typename remove_reference<T>::type>::type type;
};

template<typename T>
typename remove_ref_and_const<T>::type::value_type
pack(T seq)
{
  typedef typename remove_ref_and_const<T>::type::value_type value_type;
  value_type i = 0;
  for (int v : seq) i = i * 10 + v;
  return i;
}

template<typename M>
typename remove_ref_and_const<M>::type::mapped_type
map_find(M m,
         typename remove_ref_and_const<M>::type::key_type k,
         typename remove_ref_and_const<M>::type::mapped_type v)
{
  auto it = m.find(k);
  if (it != m.end())
    return it->second;
  else
    return v;
}

template<typename S>
bool
element_of(S s,
           typename remove_ref_and_const<S>::type::value_type k)
{
  return s.find(k) != s.end();
}

template<typename P0, typename P1>
bool
pair_equal(P0 p0, P1 p1)
{
  return (p0.first == p1.first && p0.second == p1.second);
}

BOOST_PYTHON_MODULE(stdcon) {
  typedef vector<int> ivector;
  py::def("vpack", &pack<ivector>);
  py::def("vpack_rvalue", &pack<ivector&&>);
  py::def("vpack_cref", &pack<ivector const&>);

  typedef list<int> ilist;
  py::def("lpack", &pack<ilist>);
  py::def("lpack_rvalue", &pack<ilist&&>);
  py::def("lpack_cref", &pack<ilist const&>);

  typedef forward_list<int> iforwardlist;
  py::def("flpack", &pack<iforwardlist>);
  py::def("flpack_rvalue", &pack<iforwardlist&&>);
  py::def("flpack_cref", &pack<iforwardlist const&>);

  typedef map<int, float> ifmap;
  py::def("map_find", &map_find<ifmap>);
  py::def("map_find_cref", &map_find<ifmap const &>);
  py::def("map_find_rvalue", &map_find<ifmap&&>);

  typedef unordered_map<int, float> ifhashmap;
  py::def("hashmap_find", &map_find<ifhashmap>);
  py::def("hashmap_find_cref", &map_find<ifhashmap const &>);
  py::def("hashmap_find_rvalue", &map_find<ifhashmap&&>);

  typedef set<int> iset;
  py::def("set_element_of", &element_of<iset>);
  py::def("set_cref_element_of", &element_of<iset const&>);
  py::def("set_rvalue_element_of", &element_of<iset &&>);

  typedef unordered_set<int> ihashset;
  py::def("hashset_element_of", &element_of<ihashset>);
  py::def("hashset_cref_element_of", &element_of<ihashset const &>);
  py::def("hashset_rvalue_element_of", &element_of<ihashset &&>);

  typedef pair<int, char> icpair;
  py::def("icpair_equal0", &pair_equal<icpair, icpair const&>);
  py::def("icpair_equal1", &pair_equal<icpair &&, icpair const&>);

  void def_17();
  def_17();
}
