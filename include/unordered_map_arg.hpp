#ifndef __BOOST_PYTHON_STDCON_UNORDERED_MAP_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_UNORDERED_MAP_ARG_INCLUDED__
#include <boost/python.hpp>
#include <associative_arg.hpp>
#include <unordered_map>

namespace boost::python {
  template<typename Key, typename Value, typename Hash,
           typename Eq, typename Alloc>
  struct arg_from_python<std::unordered_map<Key, Value, Hash, Eq, Alloc> const &> :
    stdcon::associative_copied_from_python<std::unordered_map<Key, Value, Hash, Eq, Alloc>>
  {
    typedef stdcon::associative_copied_from_python<std::unordered_map<Key, Value, Hash, Eq, Alloc>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename Key, typename Value, typename Hash,
           typename Eq, typename Alloc>
  struct arg_from_python<std::unordered_map<Key, Value, Hash, Eq, Alloc> &&> :
    stdcon::associative_copied_from_python<std::unordered_map<Key, Value, Hash, Eq, Alloc>>
  {
    typedef stdcon::associative_copied_from_python<std::unordered_map<Key, Value, Hash, Eq, Alloc>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename Key, typename Value, typename Hash,
           typename Eq, typename Alloc>
  struct arg_from_python<std::unordered_map<Key, Value, Hash, Eq, Alloc>> :
    stdcon::associative_copied_from_python<std::unordered_map<Key, Value, Hash, Eq, Alloc>>
  {
    typedef stdcon::associative_copied_from_python<std::unordered_map<Key, Value, Hash, Eq, Alloc>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename Key, typename Value, typename Hash,
             typename Eq, typename Alloc>
    struct expected_pytype_for_arg<std::unordered_map<Key, Value, Hash, Eq, Alloc> const&> :
      expecting_pydict {};

    template<typename Key, typename Value, typename Hash,
             typename Eq, typename Alloc>
    struct expected_pytype_for_arg<std::unordered_map<Key, Value, Hash, Eq, Alloc> &&> :
      expecting_pydict {};

    template<typename Key, typename Value, typename Hash,
             typename Eq, typename Alloc>
    struct expected_pytype_for_arg<std::unordered_map<Key, Value, Hash, Eq, Alloc>> :
      expecting_pydict {};
  }
}
#endif
