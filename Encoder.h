#ifndef _Encoder_H_
#define _Encoder_H_
#include "Arduino.h"
#include "Bounce2.h"

class Encoder{
private:

	int PinA;
	int PinB;
	int PinC;
	int counter;
	int counter_max;
	int counter_min;

	boolean encoder_rotate;
	boolean switch_pressed;
	boolean counter_active;
	boolean counter_endless;
	boolean stopped;

	void count(int i);

	Bounce bouncer;

public:

	Encoder();

	void setPins(int a, int b, int c);
	void stop();
	void start();
	void activateRotationCounter(boolean b);
	void activateEndlessCounter(boolean b);

	void setCounterMinMax(int min, int max);


	int getRotationCounter();
	int getRotation();

	boolean switchPressed();
	boolean started();
};

#endif
