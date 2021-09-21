#ifndef __BOOST_PYTHON_STDCON_COPY_RETURN_VALUE_INCLUDED__
#define __BOOST_PYTHON_STDCON_COPY_RETURN_VALUE_INCLUDED__
#include <copy_sequence_return_value.hpp>
#include <copy_distinct_return_value.hpp>
#include <copy_associative_return_value.hpp>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

namespace boost::python {
  template<typename Base>
  struct copy_return_value_dispatcher
  {
    typedef typename Base::result_converter base_result_converter;

    template<typename T>
    struct apply {
      // Generic case, using base_result_converter
      typedef typename base_result_converter::apply<T>::type type;
    };

    template<typename T, typename A>
    struct apply<std::vector<T, A>> {
      typedef stdcon::copy_sequence_return_value<std::vector<T, A>, base_result_converter> type;
    };

    template<typename T, typename A>
    struct apply<std::vector<T, A> const &> {
      typedef stdcon::copy_sequence_return_value<std::vector<T, A>, base_result_converter> type;
    };

    template<typename T, typename A>
    struct apply<std::list<T, A>> {
      typedef stdcon::copy_sequence_return_value<std::list<T, A>, base_result_converter> type;
    };

    template<typename T, typename A>
    struct apply<std::list<T, A> const &> {
      typedef stdcon::copy_sequence_return_value<std::list<T, A>, base_result_converter> type;
    };

    template<typename T, typename A>
    struct apply<std::forward_list<T, A>> {
      typedef stdcon::copy_sequence_return_value<std::forward_list<T, A>, base_result_converter> type;
    };

    template<typename T, typename A>
    struct apply<std::forward_list<T, A> const &> {
      typedef stdcon::copy_sequence_return_value<std::forward_list<T, A>, base_result_converter> type;
    };

    template<typename K, typename C, typename A>
    struct apply<std::set<K, C, A>> {
      typedef stdcon::copy_distinct_return_value<std::set<K, C, A>, base_result_converter> type;
    };
    template<typename K, typename C, typename A>
    struct apply<std::set<K, C, A> const &> {
      typedef stdcon::copy_distinct_return_value<std::set<K, C, A>, base_result_converter> type;
    };

    template<typename K, typename H, typename E, typename A>
    struct apply<std::unordered_set<K, H, E, A>> {
      typedef stdcon::copy_distinct_return_value<std::unordered_set<K, H, E, A>, base_result_converter> type;
    };
    template<typename K, typename H, typename E, typename A>
    struct apply<std::unordered_set<K, H, E, A> const &> {
      typedef stdcon::copy_distinct_return_value<std::unordered_set<K, H, E, A>, base_result_converter> type;
    };

    template<typename K, typename T, typename C, typename A>
    struct apply<std::map<K, T, C, A>> {
      typedef stdcon::copy_associative_return_value<std::map<K, T, C, A>, base_result_converter> type;
    };
    template<typename K, typename T, typename C, typename A>
    struct apply<std::map<K, T, C, A> const &> {
      typedef stdcon::copy_associative_return_value<std::map<K, T, C, A>, base_result_converter> type;
    };

    template<typename K, typename T, typename H, typename E, typename A>
    struct apply<std::unordered_map<K, T, H, E, A>> {
      typedef stdcon::copy_associative_return_value<std::unordered_map<K, T, H, E, A>, base_result_converter> type;
    };

    template<typename K, typename T, typename H, typename E, typename A>
    struct apply<std::unordered_map<K, T, H, E, A> const &> {
      typedef stdcon::copy_associative_return_value<std::unordered_map<K, T, H, E, A>, base_result_converter> type;
    };
  };

  template<typename Base = default_call_policies>
  struct copy_return_value : Base
  {
    typedef copy_return_value_dispatcher<Base> result_converter;
  };
} // of namespace boost::python

#endif

