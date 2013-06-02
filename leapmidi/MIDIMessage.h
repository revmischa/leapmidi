//
//  MIDIMessage.h
//
//  Base class for messages that can be sent over MIDI. Used for "Control" and "Note" messages
//
//  Created by Mischa Spiegelmock on 6/2/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIMessage__
#define __leapmidi__MIDIMessage__

#include <iostream>
#include <sys/time.h>
#include "LeapMIDI.h"

namespace leapmidi {
    
class MIDIMessage {
public:
    MIDIMessage(midi_control_value_raw rawValue, int hand) :
    _rawValue(rawValue), _handIndex(hand) {
        gettimeofday(&_timestamp, NULL);
    }
    
    // overloaded by subclasses with a human-readable description
    virtual const std::string &description() = 0;
    
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

#endif /* defined(__leapmidi__MIDIMessage__) */
