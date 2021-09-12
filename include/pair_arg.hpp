#ifndef __BOOST_PYTHON_STDCON_PAIR_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_PAIR_ARG_INCLUDED__
#include <boost/python.hpp>
#include <utility>

namespace boost::python {
  namespace stdcon {
    template<typename P>
    struct pair_copied_from_python
    {
      typedef P result_type;
      typedef typename P::first_type first_type;
      typedef typename P::second_type second_type;
      typedef arg_from_python<first_type> first_element_converter_type;
      typedef arg_from_python<second_type> second_element_converter_type;

      pair_copied_from_python(PyObject *pyobj) : m_pyobj(pyobj) {}
      bool convertible() const {
        // == true when m_pyobj is a Python tuple of size 2 and all
        // its elements are convertible to corresponding type
        return (PyTuple_Check(m_pyobj) &&
                (PyTuple_Size(m_pyobj) == 2) &&
                first_element_converter_type(PyTuple_GetItem(m_pyobj, 0)).convertible() &&
                second_element_converter_type(PyTuple_GetItem(m_pyobj, 1)).convertible());
      }

      result_type operator()() const {
        return result_type(first_element_converter_type(PyTuple_GetItem(m_pyobj, 0))(),
                           second_element_converter_type(PyTuple_GetItem(m_pyobj, 1))());
      }
    private:
      PyObject *m_pyobj;
    };
  }

  template<typename T0, typename T1>
  struct arg_from_python<std::pair<T0, T1> const&>:
    stdcon::pair_copied_from_python<std::pair<T0, T1>>
  {
    typedef stdcon::pair_copied_from_python<std::pair<T0, T1>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };
  template<typename T0, typename T1>
  struct arg_from_python<std::pair<T0, T1> &&>:
    stdcon::pair_copied_from_python<std::pair<T0, T1>>
  {
    typedef stdcon::pair_copied_from_python<std::pair<T0, T1>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };
  template<typename T0, typename T1>
  struct arg_from_python<std::pair<T0, T1>>:
    stdcon::pair_copied_from_python<std::pair<T0, T1>>
  {
    typedef stdcon::pair_copied_from_python<std::pair<T0, T1>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    struct expecting_pypair
    {
      static PyTypeObject const *get_pytype() {
        return &PyTuple_Type;
      }
    };

    template<typename T0, typename T1>
    struct expected_pytype_for_arg<std::pair<T0, T1> const&> : expecting_pypair {};
    template<typename T0, typename T1>
    struct expected_pytype_for_arg<std::pair<T0, T1> &&> : expecting_pypair {};
    template<typename T0, typename T1>
    struct expected_pytype_for_arg<std::pair<T0, T1>> : expecting_pypair {};
  }
}
#endif
