#include "WaveMaker.h"
#include <stdio.h>

using namespace std;

double WaveMaker::sine(double val) {
    return sin(val) / 2 + 0.5;
}

double WaveMaker::cosine(double val) {
    return cos(val) / 2 + 0.5;
}

double WaveMaker::square(double val) {
    return sin(val) >= 0 ? 1 : 0;
}

double WaveMaker::sawRise(double val) {
    val /= (2 * PI);
    return val - floor(val);
}

double WaveMaker::sawFall(double val) {
    return 1 - sawRise(val);
}

waveFunction WaveMaker::getFunction(int type) {
    if (type == kOn)
        return on;
    if (type == kOff)
        return off;
    if (type == kSine)
        return sine;
    if (type == kCos)
        return cosine;
    if (type == kSquare)
        return square;
    if (type == kSawRise)
        return sawRise;
    return sawFall;
}

sample_t* WaveMaker::createWave(int type, int frames, float min, 
 float max, int offset) {

    sample_t* wave = (sample_t*)malloc(frames * sizeof(sample_t));
    waveFunction waveFunc = getFunction(type);
    float k = 2 * PI / frames;
    float a = max - min;

    for (int i = offset; i < frames + offset; i++)
        wave[i] = a * waveFunc(k * i) + min;

    return wave;
}
