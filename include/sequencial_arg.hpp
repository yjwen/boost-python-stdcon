#ifndef __BOOST_PYTHON_STDCON_SEQUENCIAL_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_SEQUENCIAL_ARG_INCLUDED__
#include <boost/python.hpp>
#include <Python.h>

namespace boost::python {
  namespace detail {
    template<typename T>
    struct reserve
    {
      static void func(T &v, size_t sz) {/* Do nothing unless T is a vector */}
    };


    template<typename C>
    struct sequencial_copied_from_python
    {
      typedef C result_type;
      typedef typename C::value_type value_type;

      typedef arg_from_python<value_type> element_converter_type;

      sequencial_copied_from_python(PyObject* pyobj) : m_pyobj(pyobj) {}
      bool convertible() const {
        // == true when m_pyobj is a Python list and all its elements
        // are convertible to value_type
        if (!PyList_Check(m_pyobj))
          return false;
        for (Py_ssize_t i = 0; i < PyList_Size(m_pyobj); ++i) {
          if (!element_converter_type(PyList_GetItem(m_pyobj, i)).convertible())
            return false;
        }
        return true;
      }

      result_type operator()() const {
        result_type seq;
        reserve<C>::func(seq, PyList_Size(m_pyobj));
        for (Py_ssize_t i = 0; i < PyList_Size(m_pyobj); ++i) {
          seq.push_back(element_converter_type(PyList_GetItem(m_pyobj, i))());
        }
        return seq;
      }
    private:
      PyObject *m_pyobj;
    };
  } // of namespace detail
  namespace converter {
    struct expecting_pylist
    {
      static PyTypeObject const *get_pytype() {
        return &PyList_Type;
      }
    };
  }    
}

#endif
