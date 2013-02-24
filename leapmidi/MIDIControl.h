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
#include "LeapMIDI.h"

namespace leapmidi {
    
class Control {
public:
    // create a recognized control with raw input value from recognizer
    Control(midi_bodypart_index handIndex, midi_bodypart_index fingerIndex, midi_control_value_raw rawValue);
    virtual ~Control() {}
    
    virtual const midi_bodypart_index handIndex()   { return _handIndex; }
    virtual const midi_bodypart_index fingerIndex() { return _fingerIndex; }
    
    virtual const midi_control_value_raw rawValue() { return _rawValue; }
    
    // map a raw value from [minRawValue,maxRawValue] into the range [0,127]
    virtual const midi_control_value mappedValue();
    
    virtual const string description() = 0;
    
    // min/max raw value, for mapping to MIDI value
    virtual const midi_control_value_raw minRawValue() = 0;
    virtual const midi_control_value_raw maxRawValue() = 0;

    // MIDI control code index
    virtual const midi_control_index controlIndex() = 0;
    
protected:
    midi_control_value_raw _rawValue, _handIndex, _fingerIndex;
};

} // namespace leapmidi

#endif /* defined(__leapmidi__MIDIControl__) */
