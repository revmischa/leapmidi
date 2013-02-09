//
//  MIDIGesturepointable.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/13/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "LeapMIDI.h"
#include "MIDIGestureFinger.h"

namespace LeapMIDI {
    namespace Gesture {
        void recognizedControls(const Leap::Controller &controller, std::vector<LeapMIDI::Control::Base *> &controls) {
            Leap::Frame frame = controller.frame();
            
            // hands detected?
            if (frame.hands().empty())
                return;
                        
            size_t handCount = frame.hands().count();
            for (int i = 0; i < handCount; i++) {
                // gonna assume the user only has two hands. sometimes leap thinks otherwise.
                if (i > 1) break;

                Leap::Hand hand = frame.hands()[i];
                
                // we need at least one pointable to make this work
                size_t pointableCount = hand.pointables().count();
                if (! pointableCount)
                    continue;
                
                // calculate average X/Y/Z coords
                double x=0, y=0, z=0;
                double velX=0, velY=0, velZ=0;
                for (int pointableIndex = 0; pointableIndex < pointableCount; pointableIndex++) {
                    Leap::Pointable pointable = hand.pointables()[pointableIndex];
                    
//                    std::cout << "vel X: " << pointable.tipVelocity().x << std::endl;
                    // we want to know the velocity yo
//                    if (! pointable.tipVelocity())
//                        continue;
                    
                    x += pointable.tipPosition().x;
                    y += pointable.tipPosition().y;
                    z += pointable.tipPosition().z;
                    
                    velX += pointable.tipVelocity().x;
                    velY += pointable.tipVelocity().y;
                    velZ += pointable.tipVelocity().z;
                }
                x /= pointableCount;
                y /= pointableCount;
                z /= pointableCount;
                velX /= pointableCount;
                velY /= pointableCount;
                velZ /= pointableCount;
                
                // only register if velocity is greater than this threshold
                double velocityThreshold = 5.0;
//                std::cout << "velX: " << velX << " velY: " << velY << " velZ: " << velZ << std::endl;
                
                // generate one pointable position control per hand coordinate, determined by number of pointables
                if (abs(velX) > velocityThreshold) {
                    LeapMIDI::Control::FingerPosition *pointablePosControlX = new LeapMIDI::Control::FingerPositionX(handCount, pointableCount, x);
                        controls.push_back(pointablePosControlX);
                }
                
                if (abs(velY) > velocityThreshold) {
                    LeapMIDI::Control::FingerPosition *pointablePosControlY = new LeapMIDI::Control::FingerPositionY(handCount, pointableCount, y);
                    controls.push_back(pointablePosControlY);
                }
                
                if (abs(velZ) > velocityThreshold) {
                    LeapMIDI::Control::FingerPosition *pointablePosControlZ = new LeapMIDI::Control::FingerPositionZ(handCount, pointableCount, z);
                    controls.push_back(pointablePosControlZ);
                }
            }
            
            return;
        }
    }
}
