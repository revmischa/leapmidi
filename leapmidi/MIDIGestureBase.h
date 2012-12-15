//
//  MIDIGesture.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

// This base class represents a gesture interpreter which converts hand motions into MIDI control values.
// Each interpreter is instantiated as a singleton and passed a Leap::Controller each frame, which it can
// use to analyze current (and past) frames to make a determination about which related controls are present,
// and their values.

// An interpreter may recognize more than one control. For example, a finger gesture recognizer may return
// X/Y/Z coordinates each as a separate control, and roll/pitch/yaw as seperate controls, giving the user
// a total of 6 control values per finger

#ifndef __leapmidi__MIDIGesture__
#define __leapmidi__MIDIGesture__

#include <iostream>
#include <vector>
#include "MIDIControlBase.h"
#include "MIDITypes.h"
#include <Leap.h>

const std::vector<LeapMIDI::Control::Base *> MIDI_GESTURES_EMPTY;

namespace LeapMIDI {
    class Control::Base;

    namespace Gesture {
        class Base {
        public:
            Base() {}
            virtual ~Base() {}
            
            // given a controller, return MIDI controls recognized from gestures
            virtual std::vector<LeapMIDI::Control::Base *> recognizedControls(const Leap::Controller&) = 0;
        };
    }
}

#endif /* defined(__leapmidi__MIDIGesture__) */
