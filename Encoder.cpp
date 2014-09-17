#include "Encoder.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

Encoder::Encoder() {
	counter = 0;
	counter_max = 0;
	counter_min = 0;
	switch_pressed = false;
	encoder_rotate = false;
	counter_active = false;
	counter_endless = true;
	stopped = false;
	Bounce bouncer;
}

/*
 * starts the Encoder after it has stopped
 */

void Encoder::start() {
	stopped = false;
}

/*
 * stops the encoder
 */

void Encoder::stop() {
	stopped = true;
}

/*
 * activates rotation counter
 */

void Encoder::activateRotationCounter(boolean b) {
	counter_active = b;
}

/*
 * activates endless counter
 */

void Encoder::activateEndlessCounter(boolean b) {
	counter_endless = b;
}

/**
 * sets Counter mini and max
 */

void Encoder::setCounterMinMax(int min, int max) {
	counter_min = min;
	counter_max = max;
	counter = 0;
}

/*
 * returns the state
 */

boolean Encoder::started() {
	if (stopped) {
		return false;
	}
	return true;
}

/*
 *  setup the pins ; a & b for rotate, c for the switch
 */

void Encoder::setPins(int a, int b, int c) {
	PinA = a;
	PinB = b;
	PinC = c;

	pinMode(PinA, INPUT);
	digitalWrite(PinA, HIGH);

	pinMode(PinB, INPUT);
	digitalWrite(PinB, HIGH);

	pinMode(PinC, INPUT);
	digitalWrite(PinC, HIGH);

	bouncer.attach(PinC);
	bouncer.interval(5);
}

/*
 * increase or decrease the counter
 */

void Encoder::count(int i) {
	if (counter_active) {
		if (counter_min == 0 && counter_max == 0) {

			counter += i;
			return;
		}
		if (counter_endless) {
			if ((counter == counter_min) && (i < 0)) {
				counter = counter_max;
				return;
			}
			if ((counter == counter_max) && (i > 0)) {
				counter = counter_min;
				return;
			}

		}
		if (!counter_endless) {
			if ((counter == counter_min) && (i < 0)) {
				return;
			}
			if ((counter == counter_max) && (i > 0)) {
				return;
			}

		}
		counter += i;
	}
}

/**
 * get counter
 */

int Encoder::getRotationCounter() {
	return counter;
}

/*
 *  returns the direction of the rotation; -1 for ccw, +1 for cw, 0 for no rotation
 */

int Encoder::getRotation() {
	if (!stopped) {
		int Pina = digitalRead(PinA);
		int Pinb = digitalRead(PinB);

		if (Pina == LOW && Pinb == HIGH && !encoder_rotate) {
			encoder_rotate = true;
			count(+1);
			return +1;
		}

		if (Pinb == LOW && Pina == HIGH && !encoder_rotate) {
			encoder_rotate = true;
			count(-1);
			return -1;
		}

		if (Pina == HIGH && Pinb == HIGH) {
			encoder_rotate = false;
			delay(5);
			return 0;
		}
	}
	return 0;

}

/*
 * returns true if the switch pressed ( released )
 */

boolean Encoder::switchPressed() {
	if (stopped) {
		return false;
	}
	bouncer.update();
	int sw = bouncer.read();

	if (sw == LOW) {
		switch_pressed = true;
	}

	if (sw == HIGH) {
		if (switch_pressed) {
			switch_pressed = false;
			return true;
		}
	}

	return false;
}

