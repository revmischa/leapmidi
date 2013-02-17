//
//  MIDINote.cpp
//  leapmidi
//
//  Created by Chris Czub on 2/16/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#include "MIDINote.h"

namespace leapmidi {
    
    bool _noteRangeWarning = 0;
    
    Note::Note(midi_bodypart_index handIndex, midi_bodypart_index fingerIndex, midi_note_value_raw rawValue) {
        _handIndex = handIndex;
        _fingerIndex = fingerIndex;
        _rawValue = rawValue;
    }
    
    const midi_note_value Note::mappedValue() {
        midi_note_value_raw min = minRawValue();
        midi_note_value_raw max = maxRawValue();
        midi_note_value_raw raw = rawValue();
        
        if (raw < min) {
            if (_noteRangeWarning)
                std::cerr << "Warning, " << description() << " got raw value " << raw
                << " which is below the min of " << min << std::endl;
            raw = min;
        } else if (raw > max) {
            if (_noteRangeWarning)
                std::cerr << "Warning, " << description() << " got raw value " << raw
                << " which is above the max of " << max << std::endl;
            raw = max;
        }
        
        midi_note_value_raw inValNorm = raw - min;
        midi_note_value_raw aUpperNorm = max - min;
        midi_note_value_raw normPosition = inValNorm / aUpperNorm;
        
        midi_note_value_raw bUpperNorm = 127 - 0;
        midi_note_value_raw bValNorm = normPosition * bUpperNorm;
        midi_note_value_raw outVal = 0 + bValNorm;
        
        return outVal;
    }
    
}

