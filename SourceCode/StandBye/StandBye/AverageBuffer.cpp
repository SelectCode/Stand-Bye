//////////////////////////////////////////////////////////////////////////
/*!
 * STAND-BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de or https://github.com/flobaader/Stand-Bye
 * Author: Matthias Weirich
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
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
	lock(index, taken2);
	if (taken1&&taken2) {
		buffer[index] = f;
		index = (index + 1) % size;
	}
	ulock(buffer);
	ulock(index);
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