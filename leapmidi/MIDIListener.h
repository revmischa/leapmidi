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

using namespace std;

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace leapmidi {
    
class Listener : public Leap::Listener {
public:
    virtual void onFrame(const Leap::Controller &controller);
    virtual void onControlUpdated(const Leap::Controller &controller, GesturePtr gesture, ControlPtr control);
    virtual void onGestureRecognized(const Leap::Controller &controller, GesturePtr gesture);
};

} // namespace leapmidi

#pragma GCC visibility pop
#endif
