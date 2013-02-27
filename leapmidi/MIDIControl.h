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
#include <sys/time.h>

#include "LeapMIDI.h"

namespace leapmidi {
    
class Control {
public:
    // create a recognized control with raw input value from recognizer
    Control(midi_control_value_raw rawValue, int hand) :
        _rawValue(rawValue), _handIndex(hand) {
        gettimeofday(&_timestamp, NULL);
    }
    
    // map a raw value from [minRawValue,maxRawValue] into the range [0,127]
    virtual midi_control_value mappedValue();
    
    // overloaded by subclasses with a human-readable description
    virtual const std::string &description() = 0;
    
    // min/max raw value, for mapping to MIDI value
    virtual midi_control_value_raw minRawValue() = 0;
    virtual midi_control_value_raw maxRawValue() = 0;

    // MIDI control code index
    virtual midi_control_index controlIndex() = 0;
    
    // public accessors
    int handIndex() { return _handIndex; }
    midi_control_value_raw rawValue() { return _rawValue; }
    struct timeval& timestamp() { return _timestamp; }

protected:
    struct timeval _timestamp;
    int _handIndex;
    midi_control_value_raw _rawValue;
};

} // namespace leapmidi

#endif /* defined(__leapmidi__MIDIControl__) */
