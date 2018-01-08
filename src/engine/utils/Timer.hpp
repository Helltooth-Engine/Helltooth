#pragma once

#include <chrono>

using namespace std::chrono;

namespace ht { namespace utils {

	class Timer {
	private:
		high_resolution_clock::time_point last;

	public:
		Timer() {
			last = high_resolution_clock::now();
		}

		float GetDelta() {
			high_resolution_clock::time_point now = high_resolution_clock::now();
			duration<float> delta = duration_cast<duration<float>>(now - last);
			last = now;
			return delta.count();
		}
	};


} }