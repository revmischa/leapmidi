//
//  MIDIControl.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

// This represents a MIDI control value. Each control value must have a unique, consistent
// control number and value mapped into the range of 0-127.

#ifndef __leapmidi__MIDIControl__
#define __leapmidi__MIDIControl__

#include <iostream>
#include "MIDITypes.h"

namespace LeapMIDI {
    class Control {
    public:
        // create a recognized control with raw input value from recognizer
        Control(midi_control_value_raw rawValue);
        
    protected:
        // map a raw value into the range of 0-127
        virtual midi_control_value map(midi_control_value_raw rawValue);
        
        // min/max raw value, for mapping to MIDI value
        virtual midi_control_value_raw minRawValue() { throw "minRawValue() not implemented"; };
        virtual midi_control_value_raw maxRawValue() { throw "maxRawValue() not implemented"; };
    };
}

#endif /* defined(__leapmidi__MIDIControl__) */
