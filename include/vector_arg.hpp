#ifndef __BOOST_PYTHON_STDCON_VECTOR_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_VECTOR_ARG_INCLUDED__
#include <boost/python.hpp>
#include <sequencial_arg.hpp>
#include <vector>

namespace boost::python {
  namespace detail {
    template<typename T, typename A>
    struct reserve<std::vector<T, A>>
    {
      static void func(std::vector<T, A> &v, size_t sz) {
        v.reserve(sz);
      }
    };
  }

  // Specialization of arg_from_python
  template<typename T, typename A>
  struct arg_from_python<std::vector<T, A> const&> :
    detail::sequencial_copied_from_python<std::vector<T, A>>
  {
    typedef detail::sequencial_copied_from_python<std::vector<T, A>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename T, typename A>
  struct arg_from_python<std::vector<T, A> &&> :
    detail::sequencial_copied_from_python<std::vector<T, A>>
  {
    typedef detail::sequencial_copied_from_python<std::vector<T, A>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename T, typename A>
  struct arg_from_python<std::vector<T, A>> :
    detail::sequencial_copied_from_python<std::vector<T, A>>
  {
    typedef detail::sequencial_copied_from_python<std::vector<T, A>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename T, typename A>
    struct expected_pytype_for_arg<std::vector<T, A> const&> : expecting_pylist {};

    template<typename T, typename A>
    struct expected_pytype_for_arg<std::vector<T, A>&&> : expecting_pylist {};

    template<typename T, typename A>
    struct expected_pytype_for_arg<std::vector<T, A>> : expecting_pylist {};
  }
}

#endif
