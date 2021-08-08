#ifndef __BOOST_PYTHON_STDCON_LIST_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_LIST_ARG_INCLUDED__
#include <boost/python.hpp>
#include <sequence_arg.hpp>
#include <list>

namespace boost::python {
  // Specialization of arg_from_python
  template<typename T>
  struct arg_from_python<std::list<T> const&> :
      detail::sequence_copied_from_python<std::list<T>>
  {
    typedef detail::sequence_copied_from_python<std::list<T>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename T>
  struct arg_from_python<std::list<T> &&> :
      detail::sequence_copied_from_python<std::list<T>>
  {
    typedef detail::sequence_copied_from_python<std::list<T>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename T>
    struct expected_pytype_for_arg<std::list<T> const&> : expecting_pylist {};

    template<typename T>
    struct expected_pytype_for_arg<std::list<T>&&> : expecting_pylist {};
  }    
}
#endif
