#pragma once
#include <thread>

class ThreadWrapper
{
public:
	ThreadWrapper(std::thread &threadObj)
		:m_ThreadObj{threadObj}
	{

	}
	~ThreadWrapper()
	{
		if (m_ThreadObj.joinable())
		{
			m_ThreadObj.detach();
		}
	}
private:
	std::thread &m_ThreadObj;
};
