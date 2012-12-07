//
//  MIDIControlBallRadius.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/6/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIControlBallRadius__
#define __leapmidi__MIDIControlBallRadius__

#include <iostream>
#include "MIDIControlBase.h"
#include "MIDITypes.h"
#include "LeapMIDI.h"

namespace LeapMIDI {
    namespace Control {
        class BallRadius : public Base {
        public:
            BallRadius(midi_bodypart_index hi, midi_bodypart_index fi, double radius) : Base(hi, fi, radius) {};
            
            virtual const midi_control_value_raw minRawValue() { return 48; };
            virtual const midi_control_value_raw maxRawValue() { return 145; };
            virtual const midi_control_index controlIndex();
        };
    }
}

#endif /* defined(__leapmidi__MIDIControlBallRadius__) */