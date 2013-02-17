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

namespace LeapMIDI {
    namespace Control {
        class FingerPosition : public Base {
        public:
            FingerPosition(midi_bodypart_index hi, midi_bodypart_index fi, double pos) : Base(hi, fi, pos) {}
            virtual ~FingerPosition() {}

            // override this in subclass to define the control index of hand 1/finger 1
            virtual const midi_control_index controlIndexBase() = 0;
            
            virtual const midi_control_index controlIndex();
        };
    }
}

typedef std::shared_ptr<LeapMIDI::Control::FingerPosition> FingerPositionPtr;

#endif /* defined(__leapmidi__MIDIControlFingerPosition__) */
