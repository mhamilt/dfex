#ifndef EFFECT_H
#define EFFECT_H

#include <jack/jack.h>
#include <string.h>
#include <iostream>
#include "Class.h"

#define MAXBUFFER 1024

typedef jack_default_audio_sample_t sample_t;

class Effect : public Object {
public:

    Effect() : mWet(1.0) { }
    virtual ~Effect() { }

    static Effect* readEffect(std::istream &is);

    virtual void process(const sample_t* in, sample_t* out, int num){
        memcpy(out, in, num * sizeof(sample_t));
    }

    void setWet(float wet) { mWet = wet; }

    friend std::ostream &operator<<(std::ostream &os, const Effect &b)
     {return b.Write(os);}
    friend std::istream &operator>>(std::istream &is, Effect &b)
     {return b.Read(is);}

protected:
    char mOn;
    float mWet; 
    static int indent;

    //After the class is determined, then read/write data
    virtual std::istream &Read(std::istream &);
    virtual std::ostream &Write(std::ostream &) const;
};

#endif
