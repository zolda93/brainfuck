#ifndef _LIST_H
#define _LIST_H


template<typename...>
struct list;

template<typename T>
struct peek;

template<typename T,typename U>
struct push;

template<typename T>
struct pop;

template<typename T,typename...Ts>
struct peek<list<T,Ts...>>
{
	using type = T;
};

template<typename T,typename...Ts>
struct push<T,list<Ts...>>
{
	using type = list<T,Ts...>;
};

template<typename T,typename ...Ts>
struct pop<list<T,Ts...>>
{
	using type = list<Ts...>;
};


//alias

template<typename T>
using peek_t = typename peek<T>::type;

template<typename T,typename U>
using push_t = typename push<T,U>::type;

template<typename T>
using pop_t = typename pop<T>::type;

#endif

