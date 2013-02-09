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
        void Base::findControls(const Leap::Controller &controller, std::vector<ControlBasePtr> &inOutRecognizedControls) {
            // feed frames to recognizers
            for (vector<GestureBasePtr>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
                // get controls recognized from gestures
                GestureBasePtr gesture = *it;
                (*gesture)->recognizedControls(controller, inOutRecognizedControls);
                
                // call gesture recognized callback
                this->onGestureRecognized(controller, gesture);
                
                for (vector<ControlBasePtr>::iterator ctl = inOutRecognizedControls.begin(); ctl != inOutRecognizedControls.end(); ++ctl) {
                    ControlBasePtr control = *ctl;
                    
                    // skip control recognition failures
                    if ((*control)->controlIndex() == MIDI_CONTROL_UNRECOGNIZED)
                        continue;
                    
                    // call control updated callback
                    this->onControlUpdated(controller, gesture, control);
                }
            }
        }
    }
}