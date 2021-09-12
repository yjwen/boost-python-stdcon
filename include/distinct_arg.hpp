#ifndef __BOOST_PYTHON_STDCON_DISTINCT_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_DISTINCT_ARG_INCLUDED__
#include <boost/python.hpp>
#include <Python.h>

namespace boost::python {
  namespace stdcon {
    template<typename S>
    struct distinct_copied_from_python
    {
      typedef S result_type;
      typedef typename S::value_type value_type;

      typedef arg_from_python<value_type> value_converter_type;

      distinct_copied_from_python(PyObject *pyobj) : m_pyobj(pyobj) {}
      bool convertible() const {
        // == true when m_pyobj is a Python set or frozen set and all
        // its elements are convertible to value_type
        if (!PyAnySet_Check(m_pyobj))
          return false;
        PyObject *iter = PyObject_GetIter(m_pyobj);
        PyObject *elem;
        while (elem = PyIter_Next(iter)) {
          bool elem_convertible = value_converter_type(elem).convertible();
          Py_DECREF(elem);
          if (!elem_convertible) {
            Py_DECREF(iter);
            return false;
          }
        }
        Py_DECREF(iter);
        return true;
      }

      result_type operator()() const {
        result_type set;
        PyObject *iter = PyObject_GetIter(m_pyobj);
        PyObject *elem;
        while (elem = PyIter_Next(iter)) {
          set.insert(value_converter_type(elem)());
          Py_DECREF(elem);
        }
        Py_DECREF(iter);
        return set;
      }

    private:
      PyObject *m_pyobj;
    };
  } // of namespace stdcon

  namespace converter {
    struct expecting_pyset_or_pyfronzenset
    {
      static PyTypeObject const * get_pytype() {
        // Both set or frozenset is OK. No restriction
        return nullptr;
      }
    };
  }
}
#endif
