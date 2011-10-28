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

#ifndef DELAY_H
#define DELAY_H

#include <stdlib.h>
#include <math.h>
#include "ProcessorList.h"

#define MEMORYSIZE 4800000
#define DEFAULTPERIOD 5000

class Delay : public ProcessorList {
public:

    Delay(float period = 5000) : mSingle(0), mOffset(0), mCycleOffset(0),
     mCurPeriod(0) {
        memset(mMemory, 0, MEMORYSIZE * 2 * sizeof(sample_t));
        memset(mBuffer, 0, MAXBUFFER * sizeof(sample_t));
        mPeriod = new Constant(period);
    }

    virtual ~Delay() {
        delete mPeriod;
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Delay(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    sample_t mMemory[MEMORYSIZE * 2];
    sample_t mBuffer[MAXBUFFER];
    int mSingle;
    long mOffset, mCycleOffset;
    Processor *mPeriod;
    sample_t mCurPeriod;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
