#ifndef __BOOST_PYTHON_STDCON_COPY_PAIR_RETURN_VALUE_INCLUDED__
#define __BOOST_PYTHON_STDCON_COPY_PAIR_RETURN_VALUE_INCLUDED__

#include <type_traits>

namespace boost::python {
  namespace stdcon {
    template<typename P, typename Gen>
    struct copy_pair_return_value
    {
      typedef typename P::first_type first_type;
      typedef typename Gen::apply<first_type>::type first_converter_type;
      typedef typename P::second_type second_type;
      typedef typename Gen::apply<second_type>::type second_converter_type;

      bool convertible() const {
        // Convertible when both types are convertible
        return first_converter_type().convertible() && second_converter_type().convertible();
      }

      typedef typename std::remove_reference<P>::type DerefP;
      typedef typename std::remove_cv<DerefP>::type BareP;

      PyObject* operator () (BareP const &p) const {
        PyObject *pyobj = PyTuple_New(2);
        PyTuple_SetItem(pyobj, 0, first_converter_type()(p.first));
        PyTuple_SetItem(pyobj, 1, second_converter_type()(p.second));
        return pyobj;
      }

      PyTypeObject const* get_pytype() const {return &PyTuple_Type;}
    };
  } // of namespace stdcon
} // of namespace boost::python
#endif
