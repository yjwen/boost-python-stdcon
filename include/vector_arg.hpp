#ifndef __BOOST_PYTHON_STDCON_VECTOR_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_VECTOR_ARG_INCLUDED__
#include <boost/python.hpp>
#include <sequence_arg.hpp>
#include <vector>

namespace boost::python {
  namespace detail {
    template<typename T>
    struct reserve<std::vector<T>>
    {
      static void func(std::vector<T> &v, size_t sz) {
        v.reserve(sz);
      }
    };
  }

  // Specialization of arg_from_python
  template<typename T>
  struct arg_from_python<std::vector<T> const&> :
      detail::sequence_copied_from_python<std::vector<T>>
  {
    typedef detail::sequence_copied_from_python<std::vector<T>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename T>
  struct arg_from_python<std::vector<T> &&> :
    detail::sequence_copied_from_python<std::vector<T>>
  {
    typedef detail::sequence_copied_from_python<std::vector<T>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename T>
    struct expected_pytype_for_arg<std::vector<T> const&> : expecting_pylist {};

    template<typename T>
    struct expected_pytype_for_arg<std::vector<T>&&> : expecting_pylist {};
  }    
}

#endif
