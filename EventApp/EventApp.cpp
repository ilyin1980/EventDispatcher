#include <iostream>
#include "Reciever.h"
#include "EventDispatcher.h"

int main()
{
	Reciever* reciever = new Reciever();
	EventDispatcher::getInstance()->addEventListener(std::bind(&Reciever::call_1, reciever, std::placeholders::_1), reciever, EventDispatcher::EVENT_1);

	std::function<void(size_t)> func = std::bind(&Reciever::call_2, reciever, std::placeholders::_1);
	EventDispatcher::getInstance()->addEventListener(func, reciever, EventDispatcher::EVENT_2);

	while (true)
	{
		std::cout << "Enter size_t value\n";
		int n = 0;
		std::cin >> n;
		if (n == 1)
		{
			EventDispatcher::getInstance()->dispatch(EventDispatcher::EVENT_1, 123);
		}
		else if (n == 2)
		{
			EventDispatcher::getInstance()->dispatch(EventDispatcher::EVENT_2, 456);
		}

	}
}

