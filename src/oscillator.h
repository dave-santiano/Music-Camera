#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#pragma once
class Oscillator {
public:
	Oscillator();
	Oscillator(float frequency, double phase, float amplitude, int sampleRate);
	float getSample();
	void setFrequency(float frequency);
	void setAmplitude(float amplitude);

private:
	float frequency;
	double phase;
	double phaseInc;
	float amplitude;
	float currentSample;
	int sampleRate;
};
#endif