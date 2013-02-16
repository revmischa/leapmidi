//
//  MIDIGestureBall.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIGestureBall__
#define __leapmidi__MIDIGestureBall__

#include <iostream>
#include <vector>
#include <Leap.h>

#include "MIDIGestureBase.h"
#include "MIDIControlBase.h"

namespace LeapMIDI {
    namespace Gesture {
        class Ball : public LeapMIDI::Gesture::Base {
            void recognizedControls(const Leap::Controller &controller, std::vector<ControlBasePtr> &controls);
        };
    }
}

#endif /* defined(__leapmidi__MIDIGestureBall__) */
