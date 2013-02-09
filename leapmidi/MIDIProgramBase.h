//
//  MIDIProgramBase.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 1/5/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIProgram__
#define __leapmidi__MIDIProgram__

#include <iostream>
#include "MIDIGestureBase.h"

namespace LeapMIDI {
    namespace Program {
        class Base {
        public:
            virtual void onGestureRecognized(const Leap::Controller &controller, Gesture::Base &gesture) = 0;
            virtual void onControlUpdated(const Leap::Controller &controller, Gesture::Base &gesture, LeapMIDI::Control::Base &control) = 0;
            
            // find all recognized MIDI controls from frames
            virtual void findControls(const Leap::Controller&) = 0;
            
        protected:
            // gesture recognizer singletons
            std::vector<Gesture::Base *>gestureRecognizers;
        };
    }
}

#endif /* defined(__leapmidi__MIDIProgram__) */
