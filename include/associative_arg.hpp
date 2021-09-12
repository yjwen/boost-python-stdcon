#ifndef __BOOST_PYTHON_STDCON_ASSOCIATIVE_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_ASSOCIATIVE_ARG_INCLUDED__
#include <boost/python.hpp>
#include <Python.h>

namespace boost::python {
  namespace stdcon {
    template<typename C>
    struct associative_copied_from_python
    {
      typedef C result_type;
      typedef typename C::key_type key_type;
      typedef typename C::mapped_type value_type;

      typedef arg_from_python<key_type> key_converter_type;
      typedef arg_from_python<value_type> value_converter_type;

      associative_copied_from_python(PyObject *pyobj) : m_pyobj(pyobj) {}
      bool convertible() const {
        // == true when m_pyobj is a Python dict and all its keys are
        // convertible to key_type and all its values are convertible
        // to value_type
        if (!PyDict_Check(m_pyobj))
          return false; // Not a dict

        PyObject *key;
        PyObject *value;
        Py_ssize_t pos = 0;
        while (PyDict_Next(m_pyobj, &pos, &key, &value)) {
          if (!key_converter_type(key).convertible() ||
              !value_converter_type(value).convertible())
            return false; // Unmatched key or value type
        }
        return true;
      }

      result_type operator()() const {
        result_type seq;

        PyObject *key;
        PyObject *value;
        Py_ssize_t pos = 0;
        while (PyDict_Next(m_pyobj, &pos, &key, &value)) {
          seq.emplace(key_converter_type(key)(),
                      value_converter_type(value)());
        }
        return seq;
      }

    private:
      PyObject *m_pyobj;
    };
  } // of namespace stdcon

  namespace converter {
    struct expecting_pydict
    {
      static PyTypeObject const *get_pytype() {return &PyDict_Type;}
    };
  } // of namespace converter
}
#endif
