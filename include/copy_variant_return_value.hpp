#ifndef __BOOST_PYTHON_STDCON_COPY_VARIANT_RETURN_VALUE_INCLUDED__
#define __BOOST_PYTHON_STDCON_COPY_VARIANT_RETURN_VALUE_INCLUDED__

#include <variant>

namespace boost::python {
  namespace stdcon {
    template<bool IsLast, size_t I, typename V, typename Gen>
    struct alternative_from
    {
      typedef typename std::variant_alternative<I, V>::type alternative_type;
      typedef typename Gen::apply<alternative_type>::type alternative_converter_type;
      typedef alternative_from<I + 1 == std::variant_size<V>::value, I + 1, V, Gen> alternative_from_next;

      static bool convertible() {
        return alternative_converter_type().convertible() && alternative_from_next::convertible();
      }
    };

    template<size_t I, typename V, typename Gen>
    struct alternative_from<true, I, V, Gen>
    {
      static bool convertible() {return true;}
    };

    template<typename Gen>
    struct to_python_visitor
    {
      template<typename T>
      PyObject* operator() (T v) const {
        typedef typename Gen::apply<T>::type converter_type;
        return converter_type()(v);
      }
    };

    template<typename V, typename Gen>
    struct copy_variant_return_value
    {
      typedef alternative_from<0 == std::variant_size<V>::value, 0, V, Gen> alternative_from_0;
      bool convertible() const {
        // == true only when all type of possible values of V are
        // convertible
        return alternative_from_0::convertible();
      }

      PyObject* operator () (V const &v) const {
        return std::visit(to_python_visitor<Gen>(), v);
      }

      PyTypeObject const* get_pytype() const {return nullptr;}
    };
  } // of namespace stdcon
} // of namespace boost::python
#endif
