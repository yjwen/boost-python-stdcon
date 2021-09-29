#ifndef __BOOST_PYTHON_STDCON_COPY_DISTINCT_RETURN_VALUE_INCLUDED__
#define __BOOST_PYTHON_STDCON_COPY_DISTINCT_RETURN_VALUE_INCLUDED__
#include <copy_return_value_dispatcher.hpp>
#include <type_traits>
#include <boost/python.hpp>

namespace boost::python {
  namespace stdcon {
    template<typename D, typename Gen>
    struct copy_distinct_return_value
    {
      typedef typename D::value_type value_type;
      typedef typename Gen::apply<value_type>::type value_converter_type;

      bool convertible() const {
        // Convertible when V::value_type is convertible.
        return value_converter_type().convertible();
      }

      typedef typename std::remove_reference<D>::type DerefD;
      typedef typename std::remove_cv<DerefD>::type BareD;
      PyObject* operator () (BareD const &d) const {
        PyObject *pyobj = PySet_New(nullptr);
        value_converter_type value_converter;
        for (auto const &elem : d)
          PySet_Add(pyobj, value_converter(elem));
        return pyobj;
      }

      PyTypeObject const* get_pytype() const {return &PySet_Type;}
    };
  } // of namespace stdcon
} // of namespace boost::python
#endif
