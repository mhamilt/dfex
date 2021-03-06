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

#ifndef WAVEFUNCTIONS_H
#define WAVEFUNCTIONS_H

#include <math.h>
#include <stdlib.h>
#include <string>
#include "Setup.h"

typedef double(*waveFunction)(double);

class WaveFunctions {
  public:
    enum {kOn, kOff, kSine, kCos, kSquare, kSawRise, kSawFall};

    static waveFunction getFunction(int type);
    static waveFunction getFunction(const std::string &name);

  protected:
    static double on(double val) { return 1; }
    static double off(double val) { return 0; }
    static double sine(double val);
    static double cosine(double val);
    static double square(double val);
    static double sawRise(double val);
    static double sawFall(double val);
    static double cosWindow(double val);
};

#endif
