#ifndef BITCRUSH_H
#define BITCRUSH_H

#include <stdlib.h>
#include <math.h>
#include "Effect.h"

class BitCrush : public Effect {
public:

    BitCrush() : mPossible(2), Effect::Effect() {}
    ~BitCrush() {}

    const Class *GetClass() const { return &mClass; }
    static Object *newInstance() { return new BitCrush(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setResolution(int bits, int zero = 1) {
        mPossible = pow(2, bits) + zero;
    }
   
protected:

    static Class mClass;

    int mPossible;

    std::istream &Read(std::istream &);
    std::ostream &Write(std::ostream &) const;
};

#endif
