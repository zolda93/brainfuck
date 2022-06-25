#ifndef _STR_HELPER_H
#define _STR_HELPER_H

#include <utility>


template<typename T,typename U,U v>
struct append;


template<typename U, U v,U...vs>
struct append<std::integer_sequence<U,vs...>,U,v>
{
	using type = std::integer_sequence<U,vs...,v>;
};

template<typename T,typename U, U v>
using append_t = typename append<T,U,v>::type;

template<char...cs>
using make_string = std::integer_sequence<char,cs...>;

#endif

