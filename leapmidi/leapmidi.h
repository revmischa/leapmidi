/*
 *  leapmidi.h
 *  leapmidi
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#ifndef leapmidi_
#define leapmidi_

#include <deque>
#include <Leap.h>

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace leapmidi {

    const unsigned int lm_default_smoothing = 4;

    enum control_value {
        BALL_RADIUS,
        FINGER1
    };

    class listener : public Leap::Listener {
        public:
            listener();
            void set_smoothing(unsigned int);
            void get_control_value(control_value);
            virtual void onInit(const Leap::Controller&);
            virtual void onConnect(const Leap::Controller&);
            virtual void onDisconnect(const Leap::Controller&);
            virtual void onFrame(const Leap::Controller&);
            
        protected:
            unsigned int smoothing;
            std::deque<Leap::Frame *> *frames;
    };
    
}
#pragma GCC visibility pop
#endif
