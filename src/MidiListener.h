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

#ifndef MIDILISTENER_H
#define MIDILISTENER_H

#include <stdlib.h>
#include "Processor.h"

class MidiListener : public Processor {
public:

    virtual MidiListener() : Processor::Processor() { }
    virtual ~MidiListener() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new MidiListener(); }

    virtual void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif