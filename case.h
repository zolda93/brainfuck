#ifndef _CASE_H
#define _CASE_H

template<char c=(char)0>
struct Case
{
	static constexpr auto value = c;

	using add = Case<value+1>;
	using sub = Case<value-1>;

	template<char new_value>
	using put = Case<new_value>;
};

#endif


