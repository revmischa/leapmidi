//
//  MIDINote.h
//  leapmidi
//
//  Created by Chris Czub on 2/16/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

// This represents a MIDI note value. Each note value must have a unique, consistent
// note number and velocity mapped into the range of 0-127.

#ifndef __leapmidi__MIDINote__
#define __leapmidi__MIDINote__

#include <iostream>
#include "LeapMIDI.h"
#include "MIDIMessage.h"

using namespace std;

namespace leapmidi {

const static string *MIDIMessageTempDesc = new string("MIDINote");

class Note : public MIDIMessage {
public:
    // create a recognized note with raw input value from recognizer
    Note(midi_control_value_raw rawValue, int hand) : MIDIMessage(rawValue, hand) {
        gettimeofday(&_timestamp, NULL);
    }
    virtual ~Note() {}
    
    virtual const midi_note_value_raw rawValue() { return _rawValue; }
    
    virtual const string &description() { return *MIDIMessageTempDesc; };
    
    // map a raw value from [minRawValue,maxRawValue] into the range [0,127]
    virtual const midi_note_value mappedValue();
    
    // min/max raw value, for mapping to MIDI value
    virtual const midi_note_value_raw minRawValue() = 0;
    virtual const midi_note_value_raw maxRawValue() = 0;
    
    // MIDI note code index
    virtual const midi_note_index noteIndex() = 0;
    
protected:
    midi_note_value_raw _rawValue;
};

typedef std::shared_ptr<Note> NotePtr;
    
} // namespace leapmidi


#endif /* defined(__leapmidi__MIDINote__) */
