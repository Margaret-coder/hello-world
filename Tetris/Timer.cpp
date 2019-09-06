#include "Timer.h"
#include <iostream>
using namespace std;


Timer::Timer()
{
	start = std::chrono::high_resolution_clock::now();
}


Timer::~Timer()
{
}

