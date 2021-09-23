#ifndef __BOOST_PYTHON_STDCON_COPY_OPTIONAL_RETURN_VALUE_INCLUDED__
#define __BOOST_PYTHON_STDCON_COPY_OPTIONAL_RETURN_VALUE_INCLUDED__

#include <optional>
namespace boost::python {
  namespace stdcon {
    template<typename O, typename Gen>
    struct copy_optional_return_value
    {
      typedef typename std::remove_reference<O>::type DerefO;
      typedef typename std::remove_cv<DerefO>::type BareO;
      typedef typename BareO::value_type value_type;
      typedef typename Gen::apply<value_type>::type value_converter_type;
      bool convertible() const {
        return value_converter_type().convertible();
      }

      PyObject* operator () (BareO const &o) const {
        if (o) {
          return value_converter_type()(*o);
        } else {
          Py_RETURN_NONE;
        }
      }

      // No specific expecting type
      PyTypeObject const* get_pytype() const {return nullptr;}
    };
  } // of namespace stdcon
} // of namespace boost::python
#endif
