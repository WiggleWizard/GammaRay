#pragma once

#include <chrono>

class SimpleBench
{
public:
	SimpleBench(bool startNow = false)
	{
		Start();
	}

	~SimpleBench()
	{
		Stop();
	}

	void Start()
	{
		startTimePoint = std::chrono::high_resolution_clock::now();
	}

	/**
	 * \brief Stops the benchmark and returns the duration in milliseconds.
	 */
	double Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
		auto end   = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		duration = end - start;

		return GetDurationInMs();
	}

	double GetDurationInMs() const { return (double)duration * (double)0.001f; }
	long long GetDurationInUs() const { return duration; }

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
	long long duration = 0;
};
