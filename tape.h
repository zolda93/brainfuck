#ifndef _TAPE_H
#define _TAPE_H

#include <type_traits>
#include "case.h"
#include "list.h"


template<typename left=list<Case<>>,typename T=Case<>,typename right=list<Case<>>>
struct ListOfCase;

template<typename T>
struct move_right;

template<typename T>
struct move_left;

template<typename T>
struct tape;

template<typename left,typename current,typename right>
struct move_right<ListOfCase<left,current,right>>
{
	using curr = peek_t<right>;
	using r = std::conditional_t<std::is_same_v<pop_t<right>,list<>>,list<Case<>>,pop_t<right>>;
	using l = push_t<current,left>;
	using result = ListOfCase<l,curr,r>;
};

template<typename left,typename current,typename right>
struct move_left<ListOfCase<left,current,right>>
{
	using curr = peek_t<left>;
	using l = std::conditional_t<std::is_same_v<pop_t<left>,list<>>,list<Case<>>,pop_t<left>>;
	using r = push_t<current,right>;
	using result = ListOfCase<l,curr,r>;
};



template<typename left,typename curr,typename right>
struct tape<ListOfCase<left,curr,right>>
{
	using get = curr;
	using l = left;
	using r = right;

	template<char new_value>
	using put = tape<ListOfCase<l,typename get::template put<new_value>,r>>;

	using add = tape<ListOfCase<l,typename get::add,r>>;
	using sub = tape<ListOfCase<l,typename get::sub,r>>;

	using lshift = tape<typename move_left<ListOfCase<l,get,r>>::result>;
	using rshift = tape<typename move_right<ListOfCase<l,get,r>>::result>;
};


#endif
