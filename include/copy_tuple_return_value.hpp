#ifndef __BOOST_PYTHON_STDCON_COPY_TUPLE_RETURN_VALUE_INCLUDED__
#define __BOOST_PYTHON_STDCON_COPY_TUPLE_RETURN_VALUE_INCLUDED__
#include <copy_return_value_dispatcher.hpp>
#include <tuple>

namespace boost::python {
  namespace stdcon {
    template<bool IsLast, size_t I, typename T, typename Gen>
    struct element_from
    {
      // Default implementation. Assuming IsLast==False and I<T's size
      typedef typename std::tuple_element<I, T>::type element_type;
      typedef typename Gen::apply<element_type>::type element_converter_type;
      typedef element_from<I + 1 == std::tuple_size<T>::value, I + 1, T, Gen> element_from_next;

      static bool convertible() {
        return element_converter_type().convertible() && element_from_next::convertible();
      }

      static PyObject* set_element(PyObject *pyobj, T const &t) {
        PyTuple_SetItem(pyobj, I, element_converter_type()(std::get<I>(t)));

        return element_from_next::set_element(pyobj, t);
      }
    };

    template<size_t I, typename T, typename Gen>
    struct element_from<true, I, T, Gen>
    {
      static bool convertible() {return true;}
      static PyObject* set_element(PyObject *pyobj, T const &t) {return pyobj;}
    };

    
    template<typename T, typename Gen>
    struct copy_tuple_return_value
    {
      typedef typename std::remove_reference<T>::type DerefT;
      typedef typename std::remove_cv<DerefT>::type BareT;
      typedef element_from<0 == std::tuple_size<BareT>::value, 0, BareT, Gen> element_from_0;

      bool convertible() const {
        // Convertible when each type in tuple is convertible
        return element_from_0::convertible();
      }

      PyObject* operator () (BareT const &p) const {
        PyObject *pyobj = PyTuple_New(std::tuple_size<T>::value);
        return element_from_0::set_element(pyobj, p);
      }

      PyTypeObject const* get_pytype() const {return &PyTuple_Type;}
    };
  } // of namespace stdcon
} // of namespace boost::python
#endif
