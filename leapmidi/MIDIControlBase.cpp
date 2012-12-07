//
//  MIDIControl.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "MIDIControl.h"

namespace LeapMIDI {
namespace Control {

midi_control_value Base::map(midi_control_value_raw rawValue) {
    midi_control_value_raw min = minRawValue();
    midi_control_value_raw max = maxRawValue();
    
    midi_control_value_raw inValNorm = rawValue - min;
    midi_control_value_raw aUpperNorm = max - min;
    midi_control_value_raw normPosition = inValNorm / aUpperNorm;
    
    midi_control_value_raw bUpperNorm = 127 - 0;
    midi_control_value_raw bValNorm = normPosition * bUpperNorm;
    midi_control_value_raw outVal = 0 + bValNorm;

    return outVal;
}

}
}