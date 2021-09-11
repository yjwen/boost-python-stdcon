#include <type_traits>
#include <tuple_arg.hpp>
#include <optional_arg.hpp>
#include <variant_arg.hpp>

template<size_t I, typename T>
auto tuple_get(T t) -> std::remove_reference_t<decltype(std::get<I>(t))>
{
  return std::get<I>(t);
}

template<typename T>
bool is_none(T v) {return !bool(v);}

template<typename Var>
size_t var_index(Var v) {return v.index();}

void def_17() {
  namespace py = boost::python;
  py::def("tuple1_get0", &tuple_get<0, std::tuple<int>>);
  py::def("tuple2_get1", &tuple_get<1, std::tuple<int, char> const &>);
  py::def("tuple3_get2", &tuple_get<2, std::tuple<int, char, std::string>&&>);

  py::def("is_none", &is_none<std::optional<int>>);
  py::def("is_none_rvalue", &is_none<std::optional<int>&&>);
  py::def("is_none_cref", &is_none<std::optional<int> const&>);

  typedef std::variant<int, char, float> var_icf;
  py::def("var_index", &var_index<var_icf>);
  py::def("var_index_cref", &var_index<var_icf const&>);
  py::def("var_index_rvalue", &var_index<var_icf &&>);
}
