/* 
 * Copyright 2011 Matthew Tytel
 *
 * dfex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dfex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dfex.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Process.h"

using namespace std;

const float* Process::cosLookup = cosInit();
const float* Process::sinLookup = sinInit();

float* Process::cosInit() {

    float* lookup = (float*)malloc(TRANSFORMSIZE * sizeof(float));
    for (int i = 0; i < TRANSFORMSIZE; i++) 
        lookup[i] = cos(2 * PI * i / TRANSFORMSIZE);

    return lookup;
}

float* Process::sinInit() {

    float* lookup = (float*)malloc(TRANSFORMSIZE * sizeof(float));
    for (int i = 0; i < TRANSFORMSIZE; i++) 
        lookup[i] = sin(2 * PI * i / TRANSFORMSIZE);

    return lookup;
}

void Process::combine(const sample_t* from, sample_t* to, int num) {

    for (int i = 0; i < num; i++)
        to[i] += from[i];
}

sample_t Process::linearInterpolate(sample_t left, sample_t right, float perc) {

    return perc * right + (1 - perc) * left;
}

void Process::fit(const sample_t* from, sample_t* to, int numFrom, int numTo) {

    float fromInc = 1.0 * numFrom / numTo;
    float fromIndex = 0;

    for (int i = 0; i < numTo; i++) {
        to[i] = linearInterpolate(from[(int)(fromIndex)], 
         from[(int)ceil(fromIndex)], fromIndex - floor(fromIndex));
        fromIndex += fromInc;
    }
}

void Process::invert(const sample_t* from, sample_t* to, int num) {

    for (int i = 0; i < num; i++)
        to[i] = -from[i];
}

void Process::power(const sample_t* from, sample_t* to, float exp, int num) {

    for (int i = 0; i < num; i++)
        to[i] = pow(from[i], exp);
}

complex<sample_t> Process::euler(int idx) {

    int norm = idx % TRANSFORMSIZE;
    norm = norm < 0 ? TRANSFORMSIZE - norm : norm;
    return complex<sample_t>(cosLookup[norm], sinLookup[norm]);
}

