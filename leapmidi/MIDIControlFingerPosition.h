//
//  MIDIControlFingerPosition.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/13/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIControlFingerPosition__
#define __leapmidi__MIDIControlFingerPosition__

#include <iostream>
#include "MIDIControlBase.h"
#include "MIDITypes.h"
#include "LeapMIDI.h"

namespace LeapMIDI {
    namespace Control {
        class FingerPosition : public Base {
        public:
            FingerPosition(midi_bodypart_index hi, midi_bodypart_index fi, double radius) : Base(hi, fi, radius) {}
            virtual ~FingerPosition() {}
            
            virtual const midi_control_value_raw minRawValue() { return 30; };
            virtual const midi_control_value_raw maxRawValue() { return 340; };
            virtual const midi_control_index controlIndex();
        };
    }
}

#endif /* defined(__leapmidi__MIDIControlFingerPosition__) */
