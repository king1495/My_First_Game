#pragma once

namespace nRandom {	
	inline float GetRandomFloat(float min = 0.f, float max = 1.f) {
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd*(max - min) + min);
	}

	inline int GetRandomInt(int min = 0, int max = 1) {
		return rand() % (max - min + 1) + min;
	}
}