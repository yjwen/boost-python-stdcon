#ifndef __BOOST_PYTHON_STDCON_FORWARD_LIST_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_FORWARD_LIST_ARG_INCLUDED__
#include <boost/python.hpp>
#include <forward_list>

namespace boost::python {
  namespace detail {
    template<typename C>
    struct forward_list_copied_from_python
    {
      typedef C result_type;
      typedef typename C::value_type value_type;

      typedef arg_from_python<value_type> element_converter_type;

      forward_list_copied_from_python(PyObject *pyobj) : m_pyobj(pyobj) {}

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
        result_type flist;
        for (Py_ssize_t i = PyList_Size(m_pyobj); i != 0;) {
          --i;
          flist.push_front(element_converter_type(PyList_GetItem(m_pyobj, i))());
        }
        return flist;
      }
    private:
      PyObject *m_pyobj;
    };
  }

  template<typename T, typename A>
  struct arg_from_python<std::forward_list<T, A> const &> :
    detail::forward_list_copied_from_python<std::forward_list<T, A>>
  {
    typedef detail::forward_list_copied_from_python<std::forward_list<T, A>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };
  template<typename T, typename A>
  struct arg_from_python<std::forward_list<T, A> &&> :
    detail::forward_list_copied_from_python<std::forward_list<T, A>>
  {
    typedef detail::forward_list_copied_from_python<std::forward_list<T, A>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };
  template<typename T, typename A>
  struct arg_from_python<std::forward_list<T, A>> :
    detail::forward_list_copied_from_python<std::forward_list<T, A>>
  {
    typedef detail::forward_list_copied_from_python<std::forward_list<T, A>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename T, typename A>
    struct expected_pytype_for_arg<std::forward_list<T, A> const&> : expecting_pylist {};
    template<typename T, typename A>
    struct expected_pytype_for_arg<std::forward_list<T, A> &&> : expecting_pylist {};
    template<typename T, typename A>
    struct expected_pytype_for_arg<std::forward_list<T, A>> : expecting_pylist {};
  }
}
#endif
