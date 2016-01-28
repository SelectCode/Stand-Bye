#include "stdafx.h"
#include "AverageBuffer.h"

AverageBuffer::AverageBuffer(int s) {
	buffer = gcnew array<float>(s);
	size = s;
	for each(float f in buffer) {
		f = 0.0f;
	}
}

void AverageBuffer::Put(float f) {
	bool taken1 = false, taken2 = false;

	lock(buffer, taken1);
	lock(ind, taken2);
	if (taken1&&taken2) {
		buffer[ind] = f;
		ind = (ind + 1) % size;
	}
	ulock(buffer);
	ulock(ind);
}

float AverageBuffer::GetAverage() {
	float sum = 0.0f;

	bool taken = false;
	lock(buffer, taken);
	if (taken) {
		for each (float f in buffer) {
			sum += f;
		}
	}
	ulock(buffer);

	return sum / (float)size;
}