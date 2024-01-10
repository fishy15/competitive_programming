#define MethodToTemplateLambda(method) \
    template<typename T>               \
    struct method##_t {                \
        auto operator()(T x) {         \
            return x. method ();       \
        }                              \
    };                                 \
    
template<typename T, typename U>
struct parallel_pair {
    T first;
    U second;
    parallel_pair() : first{}, second{} {}
    parallel_pair(T x, U y) : first{x}, second{y} {}

#define OP(op, apply_op)                                                  \
    auto operator op(const parallel_pair<T, U> &other) const {            \
        return parallel_pair{first op other.first, second op other.second}; \
    }                                                                     \
    auto &operator apply_op(const parallel_pair<T, U> &other) {           \
        return *this = *this op other;                                    \
    }

    OP(+, +=);
    OP(-, -=);
    OP(*, *=);
    OP(/, /=);
#undef OP

    template<template<typename> typename F>
    auto call() {
        return parallel_pair{F<T>{}(first), F<U>{}(second)};
    }

    template<template<typename> typename F, typename Input>
    auto call(Input x) {
        return parallel_pair{F<T>{}(first, x), F<U>{}(second, x)};
    }
};

