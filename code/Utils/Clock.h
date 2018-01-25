#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>
#include <type_traits>
#include <cstdint>
#include <thread>

template<class Resolution>
class Clock
{
public:
	Clock() :
	timePoint(ClockType::now())
	{
	}

	void sample()
	{
		timePoint = ClockType::now();
	}

	uint64_t ticksSinceSample()
	{
		return std::chrono::duration_cast<Resolution>(
			ClockType::now() - timePoint).count();
	}

	void sleep(uint64_t ticks)
	{
		std::this_thread::sleep_for(Resolution(ticks));
	}

private:
	typedef std::conditional<
		std::chrono::high_resolution_clock::is_steady,
		std::chrono::high_resolution_clock,
		std::chrono::steady_clock>::type ClockType;

	std::chrono::time_point<ClockType> timePoint;
};

#endif
