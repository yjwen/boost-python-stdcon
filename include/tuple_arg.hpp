#ifndef __BOOST_PYTHON_STDCON_TUPLE_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_TUPLE_ARG_INCLUDED__
#include <boost/python.hpp>
#include <tuple>

namespace boost::python {
  namespace stdcon {
    // Extract the I-th object of tuple T from the I-th element of
    // a python tuple
    template<size_t I, typename T>
    typename std::tuple_element<I, T>::type
    extract_tuple_elem(PyObject *pyobj) {
      typedef typename std::tuple_element<I, T>::type element_type;
      return arg_from_python<element_type>(PyTuple_GetItem(pyobj, I))();
    }

    template<typename T, size_t ...Idx>
    struct tuple_maker
    {
      static T make(PyObject *pyobj) {
        return T(extract_tuple_elem<Idx, T>(pyobj)...);
      }
    };

    template<bool C, template <typename, size_t...> class MF, typename T, size_t ...Idx>
    struct get_tuple_maker_if
    {
      typedef tuple_maker<T, Idx...> type;
    };

    template<template <typename, size_t...> class MF, typename T, size_t ...Idx>
    struct get_tuple_maker_if<false, MF, T, Idx...>
    {
      typedef typename MF<T, Idx..., sizeof...(Idx)>::type type;
    };

    template<typename T, size_t ...Idx>
    struct get_tuple_maker
    {
      typedef typename get_tuple_maker_if<sizeof...(Idx) == std::tuple_size_v<T>,
                                          get_tuple_maker, T, Idx...>::type type;
    };

    template<typename T>
    struct tuple_copied_from_python
    {
      typedef T result_type;

      tuple_copied_from_python(PyObject *pyobj) : m_pyobj(pyobj) {}

      template<size_t I>
      bool element_convertible_from() const {
        if constexpr (I == std::tuple_size_v<T>) {
          return true;
        } else {
          typedef std::tuple_element_t<I, T> element_type;
          typedef arg_from_python<element_type> element_converter_type;
          return (element_converter_type(PyTuple_GetItem(m_pyobj, I)).convertible() &&
                  element_convertible_from<I + 1>());
        }
      }
      bool convertible() const {
        // == true when m_pyobj is a Python tuple of the same size and
        // all its elements are convertible to corresponding element
        // type
        return (PyTuple_Check(m_pyobj) &&
                (PyTuple_Size(m_pyobj) == std::tuple_size<T>::value) &&
                element_convertible_from<0>());
      }

      result_type operator()() const {
        // Type deduction from tuple type to tuple maker type
        typedef typename get_tuple_maker<T>::type maker_type;
        return maker_type::make(m_pyobj);
      }
    private:
      PyObject *m_pyobj;
    };
  } // of namespace stdcon

  template<typename...Ts>
  struct arg_from_python<std::tuple<Ts...> const&> :
    stdcon::tuple_copied_from_python<std::tuple<Ts...>>
  {
    typedef stdcon::tuple_copied_from_python<std::tuple<Ts...>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };
  template<typename...Ts>
  struct arg_from_python<std::tuple<Ts...> &&> :
    stdcon::tuple_copied_from_python<std::tuple<Ts...>>
  {
    typedef stdcon::tuple_copied_from_python<std::tuple<Ts...>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };
  template<typename...Ts>
  struct arg_from_python<std::tuple<Ts...>> :
    stdcon::tuple_copied_from_python<std::tuple<Ts...>>
  {
    typedef stdcon::tuple_copied_from_python<std::tuple<Ts...>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    struct expecting_pytuple
    {
      static PyTypeObject const *get_pytype() {return &PyTuple_Type;}
    };

    template<typename...Ts>
    struct expected_pytype_for_arg<std::tuple<Ts...> const&> : expecting_pytuple {};
    template<typename...Ts>
    struct expected_pytype_for_arg<std::tuple<Ts...> &&> : expecting_pytuple {};
    template<typename...Ts>
    struct expected_pytype_for_arg<std::tuple<Ts...>> : expecting_pytuple {};
  }
}

#endif
