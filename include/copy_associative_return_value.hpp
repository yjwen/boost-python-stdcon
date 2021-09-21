#ifndef __BOOST_PYTHON_STDCON_COPY_ASSOCIATIVE_RETURN_VALUE_INCLUDED__
#define __BOOST_PYTHON_STDCON_COPY_ASSOCIATIVE_RETURN_VALUE_INCLUDED__
namespace boost::python {
  namespace stdcon {
    template<typename A, typename Gen>
    struct copy_associative_return_value
    {
      typedef typename A::key_type key_type;
      typedef typename Gen::apply<key_type>::type key_converter_type;
      typedef typename A::mapped_type mapped_type;
      typedef typename Gen::apply<mapped_type>::type mapped_converter_type;

      bool convertible() const {
        // Convertible when both key and mapped types are convertible
        return key_converter_type().convertible() && mapped_converter_type().convertible();
      }

      typedef typename std::remove_reference<A>::type DerefA;
      typedef typename std::remove_cv<DerefA>::type BareA;
      PyObject* operator () (BareA const &a) const {
        PyObject *pyobj = PyDict_New();
        key_converter_type key_converter;
        mapped_converter_type mapped_converter;
        for (auto const &elem : a)
          PyDict_SetItem(pyobj, key_converter(elem.first), mapped_converter(elem.second));
        return pyobj;
      }

      PyTypeObject const* get_pytype() const {return &PyDict_Type;}
    };
  } // of namespace stdcon
} // of namespace boost::python
#endif
