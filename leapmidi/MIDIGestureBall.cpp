//
//  MIDIGestureBall.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "MIDIGestureBall.h"

std::vector<LeapMIDI::Control *> recognizedControls(const Leap::Controller &controller) {
    Leap::Frame frame = controller.frame();
    
    // hands detected?
    if (! frame.hands().size())
        return MIDI_GESTURES_EMPTY;
    
    for (int i = 0; i < frame.hands().size(); i++) {
        Leap::Hand hand = frame.hands()[i];
        const Leap::Ball *ball = hand.ball();
        if (ball == NULL)
            continue;
        
        // found hand curvature
        double radius = ball->radius; // in mm
        
        // now to return a MIDIControlBall instance...
    }
}
