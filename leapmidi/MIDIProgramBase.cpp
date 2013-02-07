//
//  MIDIProgramBase.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 1/5/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#include "MIDIProgramControl.h"

namespace LeapMIDI {
    namespace Program {
        // not sure where this belongs
        void Base::findControls(const Leap::Controller &controller) {
            // feed frames to recognizers
            for (vector<Gesture::Base *>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
                // get controls recognized from gestures
                Gesture::Base *gesture = *it;
                vector<LeapMIDI::Control::Base *> recognizedControls = gesture->recognizedControls(controller);
                
                // call gesture recognized callback
                this->onGestureRecognized(controller, *gesture);
                
                for (vector<LeapMIDI::Control::Base *>::iterator ctl = recognizedControls.begin(); ctl != recognizedControls.end(); ++ctl) {
                    LeapMIDI::Control::Base *control = *ctl;
                    
                    // skip control recognition failures
                    if (control->controlIndex() == MIDI_CONTROL_UNRECOGNIZED)
                        continue;
                    
                    // call control updated callback
                    this->onControlUpdated(controller, *gesture, *control);
                    
                    // done with control, it can go away now
                    delete *ctl;
                }
            }
        }
    }
}