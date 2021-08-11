#ifndef __BOOST_PYTHON_STDCON_LIST_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_LIST_ARG_INCLUDED__
#include <boost/python.hpp>
#include <sequencial_arg.hpp>
#include <list>

namespace boost::python {
  // Specialization of arg_from_python
  template<typename T, typename A>
  struct arg_from_python<std::list<T, A> const&> :
    detail::sequencial_copied_from_python<std::list<T, A>>
  {
    typedef detail::sequencial_copied_from_python<std::list<T, A>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename T, typename A>
  struct arg_from_python<std::list<T, A> &&> :
    detail::sequencial_copied_from_python<std::list<T, A>>
  {
    typedef detail::sequencial_copied_from_python<std::list<T, A>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename T, typename A>
  struct arg_from_python<std::list<T, A>> :
    detail::sequencial_copied_from_python<std::list<T, A>>
  {
    typedef detail::sequencial_copied_from_python<std::list<T, A>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename T, typename A>
    struct expected_pytype_for_arg<std::list<T, A> const&> : expecting_pylist {};

    template<typename T, typename A>
    struct expected_pytype_for_arg<std::list<T, A>&&> : expecting_pylist {};

    template<typename T, typename A>
    struct expected_pytype_for_arg<std::list<T, A>> : expecting_pylist {};
  }    
}
#endif
