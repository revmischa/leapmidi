//
//  MIDIControl.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "MIDIControlBase.h"
#include "MIDITypes.h"

namespace LeapMIDI {
    namespace Control {
        bool rangeWarning = 0;
        
        Base::Base(midi_bodypart_index handIndex, midi_bodypart_index fingerIndex, midi_control_value_raw rawValue) {
            _handIndex = handIndex;
            _fingerIndex = fingerIndex;
            _rawValue = rawValue;
        }
        
        const midi_control_value Base::mappedValue() {
            midi_control_value_raw min = minRawValue();
            midi_control_value_raw max = maxRawValue();
            midi_control_value_raw raw = rawValue();
            
            if (raw < min) {
                if (rangeWarning)
                    std::cerr << "Warning, " << description() << " got raw value " << raw
                        << " which is below the min of " << min << std::endl;
                raw = min;
            } else if (raw > max) {
                if (rangeWarning)
                    std::cerr << "Warning, " << description() << " got raw value " << raw
                        << " which is above the max of " << max << std::endl;
                raw = max;
            }
            
            midi_control_value_raw inValNorm = raw - min;
            midi_control_value_raw aUpperNorm = max - min;
            midi_control_value_raw normPosition = inValNorm / aUpperNorm;
            
            midi_control_value_raw bUpperNorm = 127 - 0;
            midi_control_value_raw bValNorm = normPosition * bUpperNorm;
            midi_control_value_raw outVal = 0 + bValNorm;
            
            return outVal;
        }
    }
}