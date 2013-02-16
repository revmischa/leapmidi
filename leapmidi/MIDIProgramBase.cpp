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
        void Base::findControls(const Leap::Controller &controller, std::vector<ControlBasePtr> &recognizedControls) {            
            // feed frames to recognizers
            for (vector<GestureBasePtr>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
                // get controls recognized from gestures
                GestureBasePtr gesture = *it;
                std::vector<ControlBasePtr> gestureControls; // controls from this gesture
                gesture->recognizedControls(controller, gestureControls);
                
                if (! gestureControls.size())
                    continue;
                
                // call gesture recognized callback
                this->onGestureRecognized(controller, gesture);
                
                for (vector<ControlBasePtr>::iterator ctl = gestureControls.begin(); ctl != gestureControls.end(); ++ctl) {
                    ControlBasePtr control = *ctl;
                    
                    recognizedControls.push_back(control);
                    this->onControlUpdated(controller, gesture, control);
                }
            }
        }
    }
}