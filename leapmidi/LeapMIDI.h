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
#include "MIDITypes.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace LeapMIDI {
    
class Gesture::Base;

// MIDI control number offsets
enum control_index {
    BALL_RADIUS_HAND_1 = 0,
    BALL_RADIUS_HAND_2,
    
    PALM_HAND_1_X,
    PALM_HAND_1_Y,
    PALM_HAND_1_Z,
    PALM_HAND_1_ROLL,
    PALM_HAND_1_PITCH,
    PALM_HAND_1_YAW,
    
    PALM_HAND_2_X,
    PALM_HAND_2_Y,
    PALM_HAND_2_Z,
    PALM_HAND_2_ROLL,
    PALM_HAND_2_PITCH,
    PALM_HAND_2_YAW,
    
    FINGER_1_HAND_1_X,
    FINGER_1_HAND_1_Y,
    FINGER_1_HAND_1_Z,
    FINGER_2_HAND_1_X,
    FINGER_2_HAND_1_Y,
    FINGER_2_HAND_1_Z
    
    // etc...
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
    std::vector<Gesture::Base *>gestureRecognizers;

    // find all recognized MIDI controls from frames
    virtual void findControls(const Leap::Controller&);
};
    
}

#pragma GCC visibility pop
#endif
