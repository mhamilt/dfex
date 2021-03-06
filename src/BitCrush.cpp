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

#include "BitCrush.h"

using namespace rapidxml;

Class BitCrush::cls(std::string("BitCrush"), newInstance);

BitCrush::BitCrush(float bits) : Effect::Effect() {
  mBits = new Constant(bits);
}

BitCrush::~BitCrush() {
  delete mBits;
}

void BitCrush::process(const sample_t* in, sample_t* out, int num) {
  sample_t bits[num];
  mBits->process(in, bits, num);

  for (int i = 0; i < num; i++) {
    float mult = pow(2, bits[i] / 2);
    float disc = round(mult * in[i]);
    out[i] = disc / mult;
  }
  postProcess(in, out, num);
}

xml_node<> &BitCrush::read(xml_node<> &inode) {
  Effect::read(inode);

  delete mBits;
  mBits = Processor::readParameter(inode, "bits", DEFAULTBITS);

  return inode;
}

xml_node<> &BitCrush::write(xml_node<> &onode) const {
  return onode;
}
