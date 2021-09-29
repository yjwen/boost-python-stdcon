#ifndef __BOOST_PYTHON_STDCON_COPY_RETURN_VALUE_INCLUDED__
#define __BOOST_PYTHON_STDCON_COPY_RETURN_VALUE_INCLUDED__
#include <copy_sequence_return_value.hpp>
#include <copy_distinct_return_value.hpp>
#include <copy_associative_return_value.hpp>
#include <copy_pair_return_value.hpp>
#include <copy_tuple_return_value.hpp>
#include <copy_optional_return_value.hpp>
#include <copy_variant_return_value.hpp>

namespace boost::python {

  template<typename Base = default_call_policies>
  struct copy_return_value : Base
  {
    typedef copy_return_value_dispatcher<Base> result_converter;
  };
} // of namespace boost::python

#endif

