//
//  leapmidi
//
//  Created by Mischa Spiegelmock on 1/5/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#ifndef leapmidi_MIDIProgramControl_h
#define leapmidi_MIDIProgramControl_h

#include "MIDIProgramBase.h"

namespace LeapMIDI {
    namespace Program {
        class Control : public Base {
        public:
            Control();
            virtual ~Control();
            
            virtual void initGestures();
                        
            virtual void onGestureRecognized(const Leap::Controller &controller, Gesture::Base &gesture);
            virtual void onControlUpdated(const Leap::Controller &controller, Gesture::Base &gesture, LeapMIDI::Control::Base &control);
        };
    }
}

#endif
