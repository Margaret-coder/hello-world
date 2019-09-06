#include <thread>
#include <chrono>
#include <thread>
#pragma once
class Timer
{
	typedef std::chrono::high_resolution_clock high_resolution_clock;
	typedef std::chrono::seconds seconds;
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point stop;
public:
	Timer();
	~Timer();
	seconds Elapsed() const
	{
		return std::chrono::duration_cast<seconds>(high_resolution_clock::now() - start);
	}
};

