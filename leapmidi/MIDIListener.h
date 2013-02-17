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
#include <math.h>

#include "MIDITypes.h"
#include "MIDIProgram.h"
#include "MIDIGesture.h"
#include "MIDIControl.h"

using namespace std;

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace leapmidi {
    
class Program;
    
class Listener : public Leap::Listener {
public:
    Listener();
    virtual void onInit(const Leap::Controller&);
    virtual void onConnect(const Leap::Controller&);
    virtual void onDisconnect(const Leap::Controller&);
    virtual void onFrame(const Leap::Controller &controller);
    virtual void onGestureRecognized(const Leap::Controller &controller, GesturePtr gesture);
    virtual void onControlUpdated(const Leap::Controller &controller, GesturePtr gesture, ControlPtr control);
    
protected:
    Program *currentProgram;
};

} // namespace leapmidi

#pragma GCC visibility pop
#endif
