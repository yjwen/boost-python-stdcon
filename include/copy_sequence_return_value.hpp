#ifndef __BOOST_PYTHON_STDCON_COPY_SEQUENCE_RETURN_VALUE_INCLUDED__
#define __BOOST_PYTHON_STDCON_COPY_SEQUENCE_RETURN_VALUE_INCLUDED__
#include <copy_return_value_dispatcher.hpp>
#include <type_traits>
#include <boost/python.hpp>


namespace boost::python {
  namespace stdcon {
    template<typename V, typename Gen>
    struct copy_sequence_return_value
    {
      typedef typename V::value_type value_type;
      typedef typename Gen::apply<value_type>::type value_converter_type;

      bool convertible() const {
        // Convertible when V::value_type is convertible
        return value_converter_type().convertible();
      }
      typedef typename std::remove_reference<V>::type DerefV;
      typedef typename std::remove_cv<DerefV>::type BareV;
      PyObject* operator () (BareV const &vec) const {
        PyObject *pyobj = PyList_New(0);
        value_converter_type value_converter;
        for (auto const &elem : vec)
          PyList_Append(pyobj, value_converter(elem));
        return pyobj;
      }

      PyTypeObject const* get_pytype() const {return &PyList_Type;}
    };
  } // of namespace stdcon
} // of namespace boost::python
#endif
