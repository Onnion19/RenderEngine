#pragma once

#include <chrono>

namespace Timers {
	struct FrameTimer
	{
	public: 
		FrameTimer() : tick(clock::now()) {}
		float Tick()
		{
			auto now = clock::now(); 
			auto frameTime = now - tick; 
			tick = now;
			return std::chrono::duration_cast<precision>(frameTime).count();
		}

	private:
		using clock = std::chrono::steady_clock;
		using precision = std::chrono::duration<float, std::milli>;
		std::chrono::steady_clock::time_point tick;
	};
}