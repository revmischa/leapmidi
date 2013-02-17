//
//  BallGesture.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIGestureBall__
#define __leapmidi__MIDIGestureBall__

#include <iostream>
#include <vector>
#include <Leap.h>

#include "MIDIGesture.h"
#include "MIDIControl.h"

namespace leapmidi {

    class BallGesture : public Gesture {
        void recognizedControls(const Leap::Controller &controller, std::vector<ControlPtr> &controls);
    };

    typedef shared_ptr<BallGesture> GestureBallPtr;

}


#endif /* defined(__leapmidi__MIDIGestureBall__) */
