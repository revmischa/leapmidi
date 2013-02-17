//
//  MIDIGestureBall.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "LeapMIDI.h"
#include "MIDIGestureBall.h"

namespace LeapMIDI {
    namespace Gesture {
        void Ball::recognizedControls(const Leap::Controller &controller, std::vector<ControlBasePtr> &controls) {
            Leap::Frame frame = controller.frame();
            
            // hands detected?
            if (frame.hands().empty())
                return;
                        
            for (int i = 0; i < frame.hands().count(); i++) {
                // gonna assume the user only has two hands. sometimes leap thinks otherwise.
                if (i > 1) break;
                
                Leap::Hand hand = frame.hands()[i];
                double radius = hand.sphereRadius(); // in mm

                if (! radius)
                    continue;
                
//                LeapMIDI::Control::BallRadius *ballControl = new LeapMIDI::Control::BallRadius(i, 0, radius);
                
                BallRadiusPtr bc(new LeapMIDI::Control::BallRadius(i, 0, radius));
                
                controls.push_back(bc);
            }
        }
    }
}
