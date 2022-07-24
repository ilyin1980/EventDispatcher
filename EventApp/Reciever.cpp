#include "Reciever.h"
#include <iostream>
Reciever::Reciever()
{

}

Reciever::~Reciever()
{

}

void Reciever::call_1(size_t arg)
{
	std::cout << "call_1 function argument = " << arg << std::endl;
}

void Reciever::call_2(size_t arg)
{
	std::cout << "call_2 function argument = " << arg << std::endl;
}
