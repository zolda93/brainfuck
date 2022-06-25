#ifndef _PARSER_H 
#define _PARSER_H

#include "tape.h"
#include "str_helper.h"





// https://fr.wikipedia.org/wiki/Brainfuck

template<typename Memory,typename input,typename output>
struct State
{
	using mem = Memory;
	using in = input;
	using out = output;
};


template<typename state,typename mem>
using state_set_mem = State<mem,typename state::in,typename state::out>;

template<typename parse,typename state>
using eval = typename parse::template eval<state>;

template<char...cs>
struct Parse;

template<>
struct Parse<>
{
	template<typename state>
		using eval = state;
};

template<char...cs>
struct Parse<'<',cs...>
{
	template<typename state>
	using eval = eval<Parse<cs...>,state_set_mem<state,typename state::mem::lshift>>;
};

template<char...cs>
struct Parse<'>',cs...>
{
	template<typename state>
	using eval = eval<Parse<cs...>,state_set_mem<state,typename state::mem::rshift>>;
};

template<char...cs>
struct Parse<'+',cs...>
{
	template<typename state>
	using eval = eval<Parse<cs...>,state_set_mem<state,typename state::mem::add>>;
};


template<char...cs>
struct Parse<'-',cs...>
{
	template<typename state>
	using eval = eval<Parse<cs...>,state_set_mem<state,typename state::mem::sub>>;
};


template<char...cs>
struct Parse<'.',cs...>
{
	template<typename state>
	using eval = eval<Parse<cs...>,
      	           State<
		      typename state::mem,
		      typename state::in,
		      append_t<
			      typename state::out,
		              std::remove_cv_t<decltype(state::mem::get::value)>,
			      state::mem::get::value>>>;
};


template<char...cs>
struct Parse<',',cs...>
{
	template<typename state>
	using eval = eval<Parse<cs...>,
                   State<
	              typename state::mem::template put<peek_t<typename state::in>::value>,
                      pop_t<typename state::in>,
                      typename state::out>>;
};


template<bool end,std::size_t depth,typename loopbody,char...program>
struct Loop;

template<std::size_t depth,char..._body,char...program>
struct Loop<true,depth,make_string<_body...>,program...>
{
	using body = Parse<_body...>;
	using next = Parse<program...>;
};

template<std::size_t depth,char...b,char c,char...cs>
struct Loop<false,depth,make_string<b...>,c,cs...>
{
	using inner = Loop<
		(depth == 1 && c == ']'),
		(c == '[' ? (depth + 1) : (c == ']'? (depth-1): depth)),
		make_string<b...,c>,
		cs...>;
	using body = typename inner::body;
	using next = typename inner::next;
};


template<typename first,typename next>
struct Then
{
	template<typename state>
	using eval = eval<next,eval<first,state>>;
};


template <typename consequent, typename alternate>
struct LoopBranch {
    template <typename state>
    using eval = eval<
        typename std::conditional<state::mem::get::value == 0,
            alternate,
            Then<
                consequent,
                LoopBranch<consequent, alternate>>>::type,
        state>;
};


template<char...cs>
struct Parse<'[',cs...>
{
	template<typename state,typename loop=Loop<false,1,make_string<>,cs...>>
	using eval = eval<
	      LoopBranch<typename loop::body,typename loop::next>,state>;
};

template<char c,char...cs>
struct Parse<c,cs...>
{
	template<typename state>
	using eval = eval<Parse<cs...>,state>;
};

using Memory = tape<ListOfCase<>>;

template<char...input>
using init_state = State<Memory,make_string<input...>,make_string<>>;


template<typename program,char...cs>
using evaluate = typename program::template eval<init_state<cs...>>::out;

#endif
		
		              
	              




























