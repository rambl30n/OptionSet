#pragma once
#include <tuple>

// workaround until we have constexpr function arguments
#define cex(x) []{ return x; }

template<typename T, T val>
struct Tag
{
    using type = T;
    T value = val;
};

template<typename L>
constexpr auto makeTag(L l) {
    return Tag<decltype(l()), l()>{};
}

template<typename T, int Idx, typename Tuple>
decltype(auto) getFirst(Tuple&& t)
{
    using Target = std::decay_t<decltype(std::get<Idx>(t))>;
    if constexpr (std::is_same<T, typename Target::type>()) {
        return std::get<Idx>(t);
    }
    else {
        return getFirst<T, Idx+1>(std::forward<Tuple>(t));
    }
}

template<typename... T>
struct OptionSet
{
    template<typename U>
    auto get() {
        return getFirst<U, 0>(options_).value;
    }

    template<typename U>
    OptionSet& set(U val) {
        getFirst<U, 0>(options_).value = val;
        return *this;
    }

private:
    std::tuple<T...> options_;
};

template<typename... T>
constexpr auto MakeOptionSet(T... vals)
{
    return OptionSet<decltype(makeTag(vals))...>{};
}
