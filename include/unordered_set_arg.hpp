#ifndef __BOOST_PYTHON_STDCON_UNORDERED_SET_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_UNORDERED_SET_ARG_INCLUDED__
#include <boost/python.hpp>
#include <distinct_arg.hpp>
#include <unordered_set>

namespace boost::python {
  template<typename Key, typename Hash, typename Eq, typename Alloc>
  struct arg_from_python<std::unordered_set<Key, Hash, Eq, Alloc> const &> :
    detail::distinct_copied_from_python<std::unordered_set<Key, Hash, Eq, Alloc>>
  {
    typedef detail::distinct_copied_from_python<std::unordered_set<Key, Hash, Eq, Alloc>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };
  template<typename Key, typename Hash, typename Eq, typename Alloc>
  struct arg_from_python<std::unordered_set<Key, Hash, Eq, Alloc> &&> :
    detail::distinct_copied_from_python<std::unordered_set<Key, Hash, Eq, Alloc>>
  {
    typedef detail::distinct_copied_from_python<std::unordered_set<Key, Hash, Eq, Alloc>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };
  template<typename Key, typename Hash, typename Eq, typename Alloc>
  struct arg_from_python<std::unordered_set<Key, Hash, Eq, Alloc>> :
    detail::distinct_copied_from_python<std::unordered_set<Key, Hash, Eq, Alloc>>
  {
    typedef detail::distinct_copied_from_python<std::unordered_set<Key, Hash, Eq, Alloc>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename Key, typename Hash, typename Eq, typename Alloc>
    struct expected_pytype_for_arg<std::unordered_set<Key, Hash, Eq, Alloc> const &> :
      expecting_pyset_or_pyfronzenset {};
    template<typename Key, typename Hash, typename Eq, typename Alloc>
    struct expected_pytype_for_arg<std::unordered_set<Key, Hash, Eq, Alloc> &&> :
      expecting_pyset_or_pyfronzenset {};
        template<typename Key, typename Hash, typename Eq, typename Alloc>
    struct expected_pytype_for_arg<std::unordered_set<Key, Hash, Eq, Alloc>> :
      expecting_pyset_or_pyfronzenset {};
  }
}
#endif
