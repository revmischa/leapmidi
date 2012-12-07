//
//  MIDIGestureBall.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "MIDIGestureBall.h"
#include "MIDIControlBallRadius.h"

namespace LeapMIDI {
    namespace Gesture {
        std::vector<LeapMIDI::Control::Base *> Ball::recognizedControls(const Leap::Controller &controller) {
            Leap::Frame frame = controller.frame();
            
            // hands detected?
            if (! frame.hands().size())
                return MIDI_GESTURES_EMPTY;
            
            std::vector<LeapMIDI::Control::Base *> controls;
            
            for (int i = 0; i < frame.hands().size(); i++) {
                // gonna assume the user only has two hands. sometimes leap thinks otherwise.
                if (i > 1) break;
                
                Leap::Hand hand = frame.hands()[i];
                const Leap::Ball *ball = hand.ball();
                if (ball == NULL)
                    continue;
                
                // found hand curvature
                double radius = ball->radius; // in mm
                
                // I'm not sure if this is the right way to return stuff in a vector
                LeapMIDI::Control::BallRadius *ballControl = new LeapMIDI::Control::BallRadius(i, 0, radius);
                controls.push_back(ballControl);
            }
            
            return controls;
        }
    }
}
