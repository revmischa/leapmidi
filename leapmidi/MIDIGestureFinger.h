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

#include "MIDIGestureBase.h"
#include "MIDIControlBase.h"
#include "MIDIControlFingerPosition.h"

namespace LeapMIDI {
    namespace Gesture {
        class Finger : public LeapMIDI::Gesture::Base {
            std::vector<LeapMIDI::Control::Base *> recognizedControls(const Leap::Controller &controller);
        };
    }
}

#endif /* defined(__leapmidi__MIDIGestureFinger__) */
