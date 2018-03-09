#include "Oscillator.h"
#include "ofMain.h"

Oscillator::Oscillator()
{}

Oscillator::Oscillator(float frequency, double phase, float amplitude, int sampleRate)
	:frequency(frequency),
	phase(phase),
	amplitude(amplitude),
	sampleRate(sampleRate),
	phaseInc(TWO_PI * frequency / (double)sampleRate),
	currentSample(0)
{}

float Oscillator::getSample( ) {
	currentSample = sin(phase) * amplitude;
	phase += phaseInc;
	return currentSample;
}

void Oscillator::setFrequency(float frequency) {
	frequency = frequency;
	phaseInc = (TWO_PI / frequency) / (double)sampleRate;
}

void Oscillator::setAmplitude(float amplitude) {
	amplitude = amplitude;
}