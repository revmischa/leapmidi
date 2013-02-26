/*
 *  MIDIListener.h
 *  LeapMIDI
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#ifndef LeapMIDI_
#define LeapMIDI_

#include <Leap.h>
#include <vector>
#include <iostream>
#include "MIDIGesture.h"
#include "BallGesture.h"

namespace leapmidi {
    
class Listener : public Leap::Listener {
public:
    Listener();

    // vector of Gesture instances to detect gesture input
    // and emit control messages
    std::vector<GesturePtr>& gestureRecognizers() { return _gestureRecognizers; }

    // called when we have identified a gesture in the current frame
    virtual void onGestureRecognized(const Leap::Controller &controller, GesturePtr gesture);
    
    // called for each control message emitted by a gesture recognizer
    virtual void onControlUpdated(const Leap::Controller &controller, GesturePtr gesture, ControlPtr control);

    // from Leap::Listener
    virtual void onFrame(const Leap::Controller &controller);
    
protected:
    std::vector<GesturePtr> _gestureRecognizers;
};

} // namespace leapmidi

#endif
