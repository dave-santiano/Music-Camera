#include "audioTools.h"

Oscillator::Oscillator()
	:frequency_(440.0f),
	phase_(0.0),
	amplitude_(0.5f),
	sampleRate_(48000),
	phaseInc_(TWO_PI * frequency_ / (double)sampleRate_),
	currentSample_(0.0)
{}


void Oscillator::setValues(float frequency, double phase, float amplitude, int sampleRate) {
	frequency_ = frequency;
	phase_ = phase;
	amplitude_ = amplitude;
	sampleRate_ = sampleRate;
	phaseInc_ = (TWO_PI * frequency_ / (double)sampleRate_);
}

float Oscillator::getSample() {
	currentSample_ = sin(phase_) * amplitude_;
	phase_ += phaseInc_;
	return currentSample_;
}

void Oscillator::setFrequency(float frequency) {
	frequency_ = frequency;
	phaseInc_ = (TWO_PI / frequency_) / (double)sampleRate_; //recalculate phase_ increment whenever
														  //frequency_ changes
}

float Oscillator::getFrequency() {
	return frequency_;
}

float Oscillator::getAmplitude() {
	return amplitude_;
}

double Oscillator::getPhaseInc() {
	return phaseInc_;
}

void Oscillator::setAmplitude(float amplitude) {
	amplitude_ = amplitude;
}


//--------------------------------------

stereoFrame Panner::pan(float input, float position) {
	stereoFrame currentFrame;

	if (position > 1) { position = 1; }
	if (position < -1) { position = -1; }

	float theta = position * 45;
	theta = ofDegToRad(theta);

	float sinTheta = sin(theta);
	float cosTheta = cos(theta);

	//Curtis Rhodes left/right panning equation (only takes radians)(also, slow :P)
	currentFrame.leftSample = input * constant * (sinTheta + cosTheta);
	currentFrame.rightSample = input * constant * (sinTheta - cosTheta);

	return currentFrame;
}