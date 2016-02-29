//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: AverageBuffer.h
 * Author: Matthias Weirich
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#define lock(X, B) System::Threading::Monitor::Enter(X, B)
#define ulock(X)if(System::Threading::Monitor::IsEntered(X)) System::Threading::Monitor::Exit(X)

ref class AverageBuffer {
private:

	array<float>^ buffer;
	int ind = 0;
	int size;

public:

	AverageBuffer(int s);
	void Put(float f);
	float GetAverage();
};