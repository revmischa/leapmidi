//
//  MIDIProgramBase.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 1/5/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#include "MIDIProgramBase.h"

using namespace std;

namespace LeapMIDI {
    namespace Program {
        void Base::findControls(const Leap::Controller &controller) {
            // feed frames to recognizers
            std::vector<LeapMIDI::Control::Base *> recognizedControls;

            for (vector<Gesture::Base *>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
                // get controls recognized from gestures
                Gesture::Base *gesture = *it;
                gesture->recognizedControls(controller, recognizedControls);
                
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