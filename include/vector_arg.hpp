#ifndef __BOOST_PYTHON_STDCON_VECTOR_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_VECTOR_ARG_INCLUDED__
#include <boost/python.hpp>
#include <vector>

namespace boost::python {
  namespace detail {
    template<typename T>
    struct vector_copied_from_python
    {
      typedef std::vector<T> result_type;

      typedef arg_from_python<T> element_converter_type;

      vector_copied_from_python(PyObject* pyobj) : m_pyobj(pyobj) {}
      bool convertible() const {
        // == true when m_pyobj is a python list and all its elements
        // are convertible to T
        if (!PyList_Check(m_pyobj))
          return false;
        for (Py_ssize_t i = 0; i < PyList_Size(m_pyobj); ++i) {
          if (!element_converter_type(PyList_GetItem(m_pyobj, i)).convertible())
            return false;
        }
        return true;
      }

      result_type operator()() const {
        result_type vec;
        vec.reserve(PyList_Size(m_pyobj));
        for (Py_ssize_t i = 0; i < PyList_Size(m_pyobj); ++i) {
          vec.push_back(element_converter_type(PyList_GetItem(m_pyobj, i))());
        }
        return vec;
      }
    private:
      PyObject *m_pyobj;
    };
  } // of namespace detail

  // Specialization of arg_from_python
  template<typename T>
  struct arg_from_python<std::vector<T> const&> :
    detail::vector_copied_from_python<T>
  {
    typedef detail::vector_copied_from_python<T> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename T>
  struct arg_from_python<std::vector<T> &&> :
    detail::vector_copied_from_python<T>
  {
    typedef detail::vector_copied_from_python<T> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    struct expecting_pylist
    {
      static PyTypeObject const *get_pytype() {
        return &PyList_Type;
      }
    };

    template<typename T>
    struct expected_pytype_for_arg<std::vector<T> const&> : expecting_pylist {};

    template<typename T>
    struct expected_pytype_for_arg<std::vector<T>&&> : expecting_pylist {};
  }    

}

#endif
