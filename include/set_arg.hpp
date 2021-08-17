#ifndef __BOOST_PYTHON_STDCON_SET_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_SET_ARG_INCLUDED__
#include <boost/python.hpp>
#include <distinct_arg.hpp>
#include <set>

namespace boost::python {
  template<typename Key, typename Compare, typename Alloc>
  struct arg_from_python<std::set<Key, Compare, Alloc> const&> :
    detail::distinct_copied_from_python<std::set<Key, Compare, Alloc>>
  {
    typedef detail::distinct_copied_from_python<std::set<Key, Compare, Alloc>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };
  template<typename Key, typename Compare, typename Alloc>
  struct arg_from_python<std::set<Key, Compare, Alloc> &&> :
    detail::distinct_copied_from_python<std::set<Key, Compare, Alloc>>
  {
    typedef detail::distinct_copied_from_python<std::set<Key, Compare, Alloc>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename Key, typename Compare, typename Alloc>
  struct arg_from_python<std::set<Key, Compare, Alloc>> :
    detail::distinct_copied_from_python<std::set<Key, Compare, Alloc>>
  {
    typedef detail::distinct_copied_from_python<std::set<Key, Compare, Alloc>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename Key, typename Compare, typename Alloc>
    struct expected_pytype_for_arg<std::set<Key, Compare, Alloc> const&> :
      expecting_pyset_or_pyfronzenset {};
    template<typename Key, typename Compare, typename Alloc>
    struct expected_pytype_for_arg<std::set<Key, Compare, Alloc> &&> :
      expecting_pyset_or_pyfronzenset {};
    template<typename Key, typename Compare, typename Alloc>
    struct expected_pytype_for_arg<std::set<Key, Compare, Alloc>> :
      expecting_pyset_or_pyfronzenset {};
  } // of namespace converter
}
#endif
