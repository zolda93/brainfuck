#include <iostream>
#include "parser.h"




//https://fr.wikipedia.org/wiki/Brainfuck

using hello_world = Parse<
    '+', '+', '+', '+', '+', '+', '+', '+', '+', '+',
    '[', '>', '+', '+', '+', '+', '+', '+', '+', '>',
    '+', '+', '+', '+', '+', '+', '+', '+', '+', '+',
    '>', '+', '+', '+', '>', '+', '<', '<', '<', '<',
    '-', ']', '>', '+', '+', '.', '>', '+', '.', '+',
    '+', '+', '+', '+', '+', '+', '.', '.', '+', '+',
    '+', '.', '>', '+', '+', '.', '<', '<', '+', '+',
    '+', '+', '+', '+', '+', '+', '+', '+', '+', '+',
    '+', '+', '+', '.', '>', '.', '+', '+', '+', '.',
    '-', '-', '-', '-', '-', '-', '.', '-', '-', '-',
    '-', '-', '-', '-', '-', '.', '>', '+', '.', '>',
    '.'>;

auto lambda = []<char...cs>(std::integer_sequence<char,cs...>){(std::cout << ... << cs);};

int main()
{
	lambda(evaluate<hello_world>{});
}
