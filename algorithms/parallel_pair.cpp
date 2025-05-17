#include <iostream>
#include <string>

namespace parallel {
    // constructing a type without constructing the actual tuple
    template<typename ...T>
    struct type_list {};

    template<typename Head, typename ...Tail>
    void get_head() -> Head;

    template<typename T1, typename ...T>
    T

    template<typename T1, typename ...T>
    auto prepend_type(type_list<T...>) -> type_list<T1, T...>;

    template<template<typename> typename F>
    auto create_tuple_type() -> type_list<>;

    template<template<typename> typename F, typename T1, typename ...T>
    auto create_tuple_type() {
        using head_type = std::invoke_result_t<F<T1>, T1>;
        auto tail = create_tuple_type<F, T...>();
        return decltype(prepend_type<head_type>(tail)){};
    }

    template<typename ...T>
    auto tuple_of(type_list<T...>) -> std::tuple<T...> {}
}

using namespace parallel;
using namespace std;

template<typename T>
struct A {
    double operator()(T x) {
        return 1.0;
    }
};

int main() {
    // type_list<int, std::string> lst;
    decltype(create_tuple_type<A, int, std::string>())::asdf;
}

