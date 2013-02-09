/*
 *  LeapMIDI.h
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

#include "MIDIProgramBase.h"
#include "MIDIGestureBase.h"
#include "MIDIControlBase.h"
#include "MIDITypes.h"
#include "MIDIGestureBall.h"
#include "MIDIGestureFinger.h"

using namespace std;

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace LeapMIDI {
    class Gesture::Base;

    class Listener : public Leap::Listener {
    public:
        Listener();
        virtual void onInit(const Leap::Controller&);
        virtual void onConnect(const Leap::Controller&);
        virtual void onDisconnect(const Leap::Controller&);
        virtual void onFrame(const Leap::Controller &controller);
        virtual void onGestureRecognized(const Leap::Controller &controller, Gesture::Base &gesture) = 0;
        virtual void onControlUpdated(const Leap::Controller &controller, Gesture::Base &gesture, LeapMIDI::Control::Base &control) = 0;
        
    protected:
        Program::Base *currentProgram;
    };
}

#pragma GCC visibility pop
#endif
