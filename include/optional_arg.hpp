#ifndef __BOOST_PYTHON_STDCON_OPTIONAL_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_OPTIONAL_ARG_INCLUDED__
#include <boost/python.hpp>
#include <optional>
#include <expecting_null.hpp>

namespace boost::python {
  namespace stdcon {
    template<typename O>
    struct optional_copied_from_python
    {
      typedef O result_type;
      typedef typename O::value_type value_type;
      typedef arg_from_python<value_type> value_converter_type;
      optional_copied_from_python(PyObject *pyobj) : m_pyobj(pyobj) {}
      bool convertible() const {
        return m_pyobj == Py_None || value_converter_type(m_pyobj).convertible();
      }

      result_type operator()() const {
        if (m_pyobj == Py_None)
          return std::nullopt;
        else
          return value_converter_type(m_pyobj)();
      }
    private:
      PyObject *m_pyobj;
    };
  } // of namespace stdcone

  template<typename T>
  struct arg_from_python<std::optional<T> const&> :
    stdcon::optional_copied_from_python<std::optional<T>>
  {
    typedef stdcon::optional_copied_from_python<std::optional<T>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename T>
  struct arg_from_python<std::optional<T> &&> :
    stdcon::optional_copied_from_python<std::optional<T>>
  {
    typedef stdcon::optional_copied_from_python<std::optional<T>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename T>
  struct arg_from_python<std::optional<T>> :
    stdcon::optional_copied_from_python<std::optional<T>>
  {
    typedef stdcon::optional_copied_from_python<std::optional<T>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename T>
    struct expected_pytype_for_arg<std::optional<T> const&> : expecting_null {};
    template<typename T>
    struct expected_pytype_for_arg<std::optional<T> &&> : expecting_null {};
    template<typename T>
    struct expected_pytype_for_arg<std::optional<T>> : expecting_null {};
  }
}
#endif
