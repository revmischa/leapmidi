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
#include "MIDIGesture.h"
#include "MIDITypes.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace LeapMIDI {
    class Gesture;
    
    // base offsets from which to determine MIDI control number
    enum control_index {
        BALL_RADIUS = 0,
        HANDS = 1,
        FINGERS = 10
    };

    class Listener : public Leap::Listener {
    public:
        Listener();
        virtual ~Listener();
        
        virtual void initGestures();
        
        virtual void onInit(const Leap::Controller&);
        virtual void onConnect(const Leap::Controller&);
        virtual void onDisconnect(const Leap::Controller&);
        virtual void onFrame(const Leap::Controller&);
        
    protected:
        // gesture recognizer singletons
        std::vector<Gesture *> *gestureRecognizers;
    
        // find all recognized MIDI controls from frames
        virtual void findControls(const Leap::Controller&);
    };
}

#pragma GCC visibility pop
#endif
