/*
 *  MIDIListener.cpp
 *  LeapMIDI
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#include "MIDIListener.h"

namespace leapmidi {
    
void Listener::onFrame(const Leap::Controller &controller) {    
    // use current active gesture recognizers to locate gestures
    // and then trigger appropriate note/controls
    // feed frames to recognizers
    vector<GesturePtr> gestureRecognizers;
    for (vector<GesturePtr>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
        // get controls recognized from gestures
        GesturePtr gesture = *it;
        std::vector<ControlPtr> gestureControls; // controls from this gesture
        gesture->recognizedControls(controller, gestureControls);
        
        if (! gestureControls.size())
            continue;
        
        // call gesture recognized callback
        onGestureRecognized(controller, gesture);
        
        for (vector<ControlPtr>::iterator ctl = gestureControls.begin(); ctl != gestureControls.end(); ++ctl) {
            ControlPtr control = *ctl;
            
            onControlUpdated(controller, gesture, control);
        }
    }
}

// do something productive with these in your application's Listener subclass
void Listener::onGestureRecognized(const Leap::Controller &controller, GesturePtr gesture) {}
void Listener::onControlUpdated(const Leap::Controller &controller, GesturePtr gesture, ControlPtr control) {}
    
}
