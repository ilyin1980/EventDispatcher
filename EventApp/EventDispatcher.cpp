#include "EventDispatcher.h"

const char* EventDispatcher::EVENT_1 = "EVENT_1";
const char* EventDispatcher::EVENT_2 = "EVENT_2";
EventDispatcher* EventDispatcher::_instance = nullptr;
std::map < size_t, std::vector<EventDispatcher::Command> > EventDispatcher::_event_map;

size_t EventDispatcher::getHash(const std::string& in_str)
{
	size_t b = 378551;
	size_t a = 63689;
	size_t hash = 0;

	for (std::size_t i = 0; i < in_str.length(); i++)
	{
		hash = hash * a + in_str[i];
		a = a * b;
	}

	return (hash & 0x7FFFFFFF);
}

size_t EventDispatcher::getHash(const char* in_str)
{
	std::string str = in_str;
	return getHash(str);
}

EventDispatcher::EventDispatcher()
{

}

EventDispatcher::~EventDispatcher()
{

}

EventDispatcher* EventDispatcher::getInstance()
{
	if (!_instance)
	{
		_instance = new EventDispatcher();
	}
	return _instance;
}

void EventDispatcher::releaseInstance()
{
	delete _instance;
	_instance = nullptr;
}

void EventDispatcher::dispatch(const char* event, size_t arg)
{
	auto it = _event_map.find(getHash(event));
	if (it != _event_map.end())
	{
		std::vector<EventDispatcher::Command> params = it->second;
		for (size_t i=0; i < params.size(); ++i)
		{
			auto par = params.at(i);
			par.func(arg);
		}
	}
}


