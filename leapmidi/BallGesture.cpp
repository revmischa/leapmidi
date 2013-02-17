//
//  BallGesture.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "BallGesture.h"
#include "BallRadius.h"

namespace leapmidi {

void BallGesture::recognizedControls(const Leap::Controller &controller, std::vector<ControlPtr> &controls) {
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
                
        BallRadiusPtr bc = make_shared<BallRadius>(i, 0, radius);
//        ControlPtr cptr = dynamic_pointer_cast<ControlPtr>(bc);
        
//        controls.push_back(cptr);
    }
}

}
