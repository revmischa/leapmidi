//
//  MIDIGestureFinger.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/13/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIGestureFinger__
#define __leapmidi__MIDIGestureFinger__

#include <iostream>
#include <vector>
#include <Leap.h>
#include <math.h>

#include "MIDIGestureBase.h"
#include "MIDIControlBase.h"
#include "MIDIControlFingerPosition.h"
#include "MIDIControlFingerPositionX.h"
#include "MIDIControlFingerPositionY.h"
#include "MIDIControlFingerPositionZ.h"

namespace LeapMIDI {
    namespace Gesture {
        class Finger : public LeapMIDI::Gesture::Base {
            virtual ~Finger() {}
            
            void recognizedControls(const Leap::Controller &controller, std::vector<LeapMIDI::Control::Base *> &controls);
        };
    }
}

#endif /* defined(__leapmidi__MIDIGestureFinger__) */
