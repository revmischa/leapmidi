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
#include "MIDIGestureBase.h"
#include "MIDIControlBase.h"
#include "MIDITypes.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace LeapMIDI {
    const char *controlDescription(midi_control_index idx);

    class Gesture::Base;

    class Listener : public Leap::Listener {
    public:
        Listener();
        virtual ~Listener();
        
        virtual void initGestures();
        
        virtual void onInit(const Leap::Controller&);
        virtual void onConnect(const Leap::Controller&);
        virtual void onDisconnect(const Leap::Controller&);
        virtual void onFrame(const Leap::Controller&);
        
        virtual void onGestureRecognized(const Leap::Controller &controller, Gesture::Base &gesture);
        virtual void onControlUpdated(const Leap::Controller &controller, Gesture::Base &gesture, Control::Base &control);
        
    protected:
        // gesture recognizer singletons
        std::vector<Gesture::Base *>gestureRecognizers;

        // find all recognized MIDI controls from frames
        virtual void findControls(const Leap::Controller&);
        
        
    };
}

#pragma GCC visibility pop
#endif
