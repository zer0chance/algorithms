#include <iostream>

using uint = unsigned int;

template<int N>
struct Int {
    static constexpr int value = N;
};

struct NIL {
    typedef NIL Head;
    typedef NIL Tail;
};

template<typename H, typename T = NIL>
struct List {
    typedef H Head;
    typedef T Tail;
};

template<typename T>
struct Len {
    static const uint result = 1 + Len<typename T::Tail>::result;
};

template<>
struct Len<NIL> {
    static const uint result = 0;
};

template<uint i, typename L>
struct Nth {
    using result = typename Nth< i - 1, typename L::Tail>::result;
};

template<typename L>
struct Nth<0, L> {
    using result = typename L::Head;
};

template<typename T1, typename T2>
struct Eq {
    static constexpr bool result = false;
};

template<typename T1>
struct Eq <T1, T1> {
    static constexpr bool result = true;
};

template<typename E, typename L>
struct Contains {
    static constexpr bool result = Eq<typename L::Head, E>::result ||
                                   Contains<E, typename L::Tail>::result; 
};

template<typename E>
struct Contains<E, NIL> {
    static constexpr bool result = false; 
};

template<typename E, typename L>
struct Prepend {
    using result = List<E, L>;
};

template<typename L, typename E>
struct _Append {
    using result = List<typename L::Head, typename _Append<typename L::Tail, E>::result>;
};

template<typename E>
struct _Append<NIL, E> {
    using result = List<E>;
};

template<typename E, typename L = NIL> 
struct Append {
    using result = typename _Append<L, E>::result;
};

class Assertion {};
template<bool cond, class T = Assertion>
struct Assert {
    using check = typename T::Fail;
};

template<>
struct Assert<true> {
    using check = void;
};

template<typename E, typename L>
struct _Position {
    static constexpr bool found  = Eq<E, typename L::Head>::result;
    static constexpr uint result = found ? 0 : 1 + _Position<E, typename L::Tail>::result;
};

template<typename E>
struct _Position<E, NIL> {
    static constexpr uint result = 0;
};

template<typename E, typename L>
struct Position {
    using assert = Assert<Contains<E, L>::result>;
    static constexpr uint result = _Position<E, L>::result;
};

int main()
{
    using L = List<Int<1>, List<Int<2>, List<Int<3>>>>;
    
    std::cout << "Len:        " << Len<L>::result << '\n';
    std::cout << "List[1]:    " << Nth<1, L>::result::value << '\n';
    std::cout << "Contains 3: " << Contains<Int<3>, L>::result << '\n';
    std::cout << "Contains 7: " << Contains<Int<7>, L>::result << '\n';

    using Lp = Prepend<Int<0>, L>::result;
    using La = Append<Int<4>, Lp>::result;
    
    std::cout << "Prepend 0:  " 
              << Lp::Head::value 
              << Lp::Tail::Head::value 
              << Lp::Tail::Tail::Head::value
              << Lp::Tail::Tail::Tail::Head::value 
              << '\n';

    std::cout << "Append 4:   " 
              << La::Head::value 
              << La::Tail::Head::value 
              << La::Tail::Tail::Head::value
              << La::Tail::Tail::Tail::Head::value 
              << La::Tail::Tail::Tail::Tail::Head::value
              << '\n';

    std::cout << "Position 3: " << Position<Int<3>, La>::result << '\n';
}
