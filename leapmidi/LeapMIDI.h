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

#include <deque>
#include <Leap.h>

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace LeapMIDI {
    const unsigned int kLeapMIDIDefaultSmoothingFrames = 4;

    enum control_value {
        BALL_RADIUS,
        FINGER1
    };

    class Listener : public Leap::Listener {
    public:
        Listener();
        ~Listener();
        void setSmoothing(unsigned int);
        void getControlValue(control_value);
        virtual void onInit(const Leap::Controller&);
        virtual void onConnect(const Leap::Controller&);
        virtual void onDisconnect(const Leap::Controller&);
        virtual void onFrame(const Leap::Controller&);
            
    protected:
        unsigned int smoothing; // ring buffer size in frames
        std::deque<Leap::Frame *> *frames;  // frame ring buffer
    };
}
#pragma GCC visibility pop
#endif
