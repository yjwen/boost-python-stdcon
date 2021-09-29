#ifndef __BOOST_PYTHON_STDCON_COPY_RETURN_VALUE_DISPATCHER_INCLUDED__
#define __BOOST_PYTHON_STDCON_COPY_RETURN_VALUE_DISPATCHER_INCLUDED__
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <tuple>
#if __cplusplus >= 201703L
#include <optional>
#include <variant>
#endif

namespace boost::python {
  namespace stdcon {
    // Forward declarations of all converters
    template<typename T, typename Gen> struct copy_sequence_return_value;
    template<typename T, typename Gen> struct copy_distinct_return_value;
    template<typename T, typename Gen> struct copy_associative_return_value;
    template<typename T, typename Gen> struct copy_pair_return_value;
    template<typename T, typename Gen> struct copy_tuple_return_value;
#if __cplusplus >= 201703L
    template<typename T, typename Gen> struct copy_optional_return_value;
    template<typename T, typename Gen> struct copy_variant_return_value;
#endif
  }

  template<typename Base>
  struct copy_return_value_dispatcher
  {
    typedef typename Base::result_converter base_result_converter;
    typedef copy_return_value_dispatcher<Base> self;

    template<typename T>
    struct apply {
      // Generic case, using base_result_converter
      typedef typename base_result_converter::apply<T>::type type;
    };

    template<typename T, typename A>
    struct apply<std::vector<T, A>> {
      typedef stdcon::copy_sequence_return_value<std::vector<T, A>, self> type;
    };

    template<typename T, typename A>
    struct apply<std::vector<T, A> const &> {
      typedef stdcon::copy_sequence_return_value<std::vector<T, A>, self> type;
    };

    template<typename T, typename A>
    struct apply<std::list<T, A>> {
      typedef stdcon::copy_sequence_return_value<std::list<T, A>, self> type;
    };

    template<typename T, typename A>
    struct apply<std::list<T, A> const &> {
      typedef stdcon::copy_sequence_return_value<std::list<T, A>, self> type;
    };

    template<typename T, typename A>
    struct apply<std::forward_list<T, A>> {
      typedef stdcon::copy_sequence_return_value<std::forward_list<T, A>, self> type;
    };

    template<typename T, typename A>
    struct apply<std::forward_list<T, A> const &> {
      typedef stdcon::copy_sequence_return_value<std::forward_list<T, A>, self> type;
    };

    template<typename K, typename C, typename A>
    struct apply<std::set<K, C, A>> {
      typedef stdcon::copy_distinct_return_value<std::set<K, C, A>, self> type;
    };
    template<typename K, typename C, typename A>
    struct apply<std::set<K, C, A> const &> {
      typedef stdcon::copy_distinct_return_value<std::set<K, C, A>, self> type;
    };

    template<typename K, typename H, typename E, typename A>
    struct apply<std::unordered_set<K, H, E, A>> {
      typedef stdcon::copy_distinct_return_value<std::unordered_set<K, H, E, A>, self> type;
    };
    template<typename K, typename H, typename E, typename A>
    struct apply<std::unordered_set<K, H, E, A> const &> {
      typedef stdcon::copy_distinct_return_value<std::unordered_set<K, H, E, A>, self> type;
    };

    template<typename K, typename T, typename C, typename A>
    struct apply<std::map<K, T, C, A>> {
      typedef stdcon::copy_associative_return_value<std::map<K, T, C, A>, self> type;
    };
    template<typename K, typename T, typename C, typename A>
    struct apply<std::map<K, T, C, A> const &> {
      typedef stdcon::copy_associative_return_value<std::map<K, T, C, A>, self> type;
    };

    template<typename K, typename T, typename H, typename E, typename A>
    struct apply<std::unordered_map<K, T, H, E, A>> {
      typedef stdcon::copy_associative_return_value<std::unordered_map<K, T, H, E, A>, self> type;
    };

    template<typename K, typename T, typename H, typename E, typename A>
    struct apply<std::unordered_map<K, T, H, E, A> const &> {
      typedef stdcon::copy_associative_return_value<std::unordered_map<K, T, H, E, A>, self> type;
    };

    template<typename T0, typename T1>
    struct apply<std::pair<T0, T1> const &> {
      typedef stdcon::copy_pair_return_value<std::pair<T0, T1>, self> type;
    };

    template<typename T0, typename T1>
    struct apply<std::pair<T0, T1>> {
      typedef stdcon::copy_pair_return_value<std::pair<T0, T1>, self> type;
    };

    template<typename...Ts>
    struct apply<std::tuple<Ts...> const &> {
      typedef stdcon::copy_tuple_return_value<std::tuple<Ts...>, self> type;
    };

    template<typename...Ts>
    struct apply<std::tuple<Ts...>> {
      typedef stdcon::copy_tuple_return_value<std::tuple<Ts...>, self> type;
    };

#if __cplusplus >= 201703L
    template<typename T>
    struct apply<std::optional<T> const&> {
      typedef stdcon::copy_optional_return_value<std::optional<T>, self> type;
    };

    template<typename T>
    struct apply<std::optional<T>> {
      typedef stdcon::copy_optional_return_value<std::optional<T>, self> type;
    };

    template<typename...Ts>
    struct apply<std::variant<Ts...> const &> {
      typedef stdcon::copy_variant_return_value<std::variant<Ts...>, self> type;
    };

    template<typename...Ts>
    struct apply<std::variant<Ts...>> {
      typedef stdcon::copy_variant_return_value<std::variant<Ts...>, self> type;
    };
#endif
  };

} // of namespace boost::python
#endif
