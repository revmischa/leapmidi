//
//  Created by Mischa Spiegelmock on 1/5/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#include "MIDIProgram.h"

namespace leapmidi {
    
void Program::findControls(const Leap::Controller &controller, Listener &listener) {
    // feed frames to recognizers
    for (vector<GesturePtr>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
        // get controls recognized from gestures
        GesturePtr gesture = *it;
        std::vector<ControlPtr> gestureControls; // controls from this gesture
        gesture->recognizedControls(controller, gestureControls);
        
        if (! gestureControls.size())
            continue;
        
        // call gesture recognized callback
        listener.onGestureRecognized(controller, gesture);
        
        for (vector<ControlPtr>::iterator ctl = gestureControls.begin(); ctl != gestureControls.end(); ++ctl) {
            ControlPtr control = *ctl;
            
            listener.onControlUpdated(controller, gesture, control);
        }
    }
}

} // namespace leapmidi