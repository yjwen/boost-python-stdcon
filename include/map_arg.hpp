#ifndef __BOOST_PYTHON_STDCON_MAP_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_MAP_ARG_INCLUDED__
#include <boost/python.hpp>
#include <associative_arg.hpp>
#include <map>

namespace boost::python {
  template<typename Key, typename Value>
  struct arg_from_python<std::map<Key, Value> const&> :
    detail::associative_copied_from_python<std::map<Key, Value>>
  {
    typedef detail::associative_copied_from_python<std::map<Key, Value>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename Key, typename Value>
  struct arg_from_python<std::map<Key, Value> &&> :
    detail::associative_copied_from_python<std::map<Key, Value>>
  {
    typedef detail::associative_copied_from_python<std::map<Key, Value>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename Key, typename Value>
    struct expected_pytype_for_arg<std::map<Key, Value> const&> : expecting_pydict {};

    template<typename Key, typename Value>
    struct expected_pytype_for_arg<std::map<Key, Value> &&> : expecting_pydict {};
  }
}
#endif