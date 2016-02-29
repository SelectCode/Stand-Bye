//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: AverageBuffer.cpp
 * Author: Matthias Weirich
 * Contact: flobaader@web.de
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