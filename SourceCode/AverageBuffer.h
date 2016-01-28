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