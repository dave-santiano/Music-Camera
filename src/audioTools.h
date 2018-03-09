#ifndef AUDIO_TOOLS_H
#define AUDIO_TOOLS_H
#pragma once
#include "ofMain.h"

class Oscillator {
public:
	Oscillator();
	//Oscillator(float frequency, double phase, float amplitude, int sampleRate);
	void setValues(float frequency_, double phase_, float amplitude_, int sampleRate_);
	float getSample();
	void setFrequency(float frequency);
	void setAmplitude(float amplitude);
	float getFrequency();
	float getAmplitude();
	double getPhaseInc();

private:
	float frequency_;
	double phase_;
	float amplitude_;
	int sampleRate_;
	double phaseInc_;
	float currentSample_;
};

struct stereoFrame {
	float leftSample;
	float rightSample;
};

//-----------------------------------------------
class Panner {
public:
	stereoFrame pan(float input, float position);

private:
	float constant = sqrt(2) / (float)2;

};
#endif