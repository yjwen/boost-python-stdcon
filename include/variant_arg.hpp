#ifndef __BOOST_PYTHON_STDCON_VARIANT_ARG_INCLUDED__
#define __BOOST_PYTHON_STDCON_VARIANT_ARG_INCLUDED__
#include <boost/python.hpp>
#include <variant>
#include <stdexcept>
#include <string>

namespace boost::python {
  namespace stdcon {
    template<typename Var>
    struct variant_copied_from_python
    {
      typedef Var result_type;

      variant_copied_from_python(PyObject *pyobj) : m_pyobj(pyobj) {}
      template<size_t I>
      bool convertible_from_alternative() const {
        if constexpr (I == std::variant_size_v<Var>) {
          return false;
        } else {
          typedef std::variant_alternative_t<I, Var> alternative_type;
          return (arg_from_python<alternative_type>(m_pyobj).convertible() ||
                  convertible_from_alternative<I + 1>());
        }
      }
      bool convertible() const {
        // == true when m_pyobj is convertible to object of any type
        // held by Var
        return convertible_from_alternative<0>();
      }

      template<size_t I>
      result_type try_convert_from_alternative() const {
        if constexpr (I == std::variant_size_v<Var>) {
          // Not convertible as any alternative type and passed
          // convertible() check?
          throw std::runtime_error(std::string("boost-python-stdcon: Cannot convert python object to ") + typeid(Var).name());
        } else {
          typedef std::variant_alternative_t<I, Var> alternative_type;
          auto converter = arg_from_python<alternative_type>(m_pyobj);
          if (converter.convertible())
            return converter();
          else
            return try_convert_from_alternative<I + 1>();
        }
      }

      result_type operator()() const {
        return try_convert_from_alternative<0>();
      }
    private:
      PyObject *m_pyobj;
    };
  }
  template<typename...Ts>
  struct arg_from_python<std::variant<Ts...> const&> :
    stdcon::variant_copied_from_python<std::variant<Ts...>>
  {
    typedef stdcon::variant_copied_from_python<std::variant<Ts...>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename...Ts>
  struct arg_from_python<std::variant<Ts...> &&> :
    stdcon::variant_copied_from_python<std::variant<Ts...>>
  {
    typedef stdcon::variant_copied_from_python<std::variant<Ts...>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  template<typename...Ts>
  struct arg_from_python<std::variant<Ts...>> :
    stdcon::variant_copied_from_python<std::variant<Ts...>>
  {
    typedef stdcon::variant_copied_from_python<std::variant<Ts...>> base_type;
    arg_from_python(PyObject *pyobj) : base_type(pyobj) {}
  };

  namespace converter {
    template<typename...Ts>
    struct expected_pytype_for_arg<std::variant<Ts...> const&> : expecting_null {};
    template<typename...Ts>
    struct expected_pytype_for_arg<std::variant<Ts...> &&> : expecting_null {};
    template<typename...Ts>
    struct expected_pytype_for_arg<std::variant<Ts...>> : expecting_null {};
  }
}
#endif
