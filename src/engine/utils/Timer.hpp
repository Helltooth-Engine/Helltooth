#pragma once

#include <chrono>

namespace ht { namespace utils {

	class Timer {
	private:
		std::chrono::high_resolution_clock::time_point last;

	public:
		Timer() {
			last = std::chrono::high_resolution_clock::now();
		}

		float GetDelta() {
			std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> delta = std::chrono::duration_cast<std::chrono::duration<float>>(now - last);
			last = now;
			return delta.count();
		}
	};

} }