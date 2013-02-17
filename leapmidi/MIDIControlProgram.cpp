//
//  Created by Chris Czub on 2/16/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#include "MIDIListener.h"
#include "MIDIControlProgram.h"

namespace leapmidi {
    
    void ControlProgram::findControls(const Leap::Controller &controller, Listener *listener) {
        // feed frames to recognizers
        for (vector<GesturePtr>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
            // get controls recognized from gestures
            GesturePtr gesture = *it;
            std::vector<ControlPtr> gestureControls; // controls from this gesture
            gesture->recognizedControls(controller, gestureControls);
            
            if (! gestureControls.size())
                continue;
            
            // call gesture recognized callback
            listener->onGestureRecognized(controller, gesture);
            
            for (vector<ControlPtr>::iterator ctl = gestureControls.begin(); ctl != gestureControls.end(); ++ctl) {
                ControlPtr control = *ctl;
                
                listener->onControlUpdated(controller, gesture, control);
            }
        }
    }
    
    void ControlProgram::locateGestures(const Leap::Controller &controller, Listener *listener) {
        findControls(controller, listener);
    }
    
} // namespace leapmidi