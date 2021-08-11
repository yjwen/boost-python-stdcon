#include <vector_arg.hpp>
#include <list_arg.hpp>
#include <map_arg.hpp>
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
sum(T seq)
{
  typedef typename remove_ref_and_const<T>::type::value_type value_type;
  value_type i = 0;
  for (int v : seq) i += v;
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

BOOST_PYTHON_MODULE(stdcon) {
  typedef vector<int> ivector;
  py::def("vsum", &sum<ivector>);
  py::def("vsum_rvalue", &sum<ivector&&>);
  py::def("vsum_cref", &sum<ivector const&>);

  typedef list<int> ilist;
  py::def("lsum", &sum<ilist>);
  py::def("lsum_rvalue", &sum<ilist&&>);
  py::def("lsum_cref", &sum<ilist const&>);

  typedef map<int, float> ifmap;
  py::def("map_find", &map_find<ifmap>);
  py::def("map_find_cref", &map_find<ifmap const &>);
  py::def("map_find_rvalue", &map_find<ifmap&&>);
}
