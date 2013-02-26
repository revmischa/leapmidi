//
//  FingerGesture.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/13/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIGestureFinger__
#define __leapmidi__MIDIGestureFinger__

#include <iostream>
#include <vector>
#include <Leap.h>
#include <math.h>

#include "LeapMIDI.h"
#include "MIDIControl.h"
#include "MIDIGesture.h"
#include "FingerPosition.h"
#include "FingerPositionX.h"
#include "FingerPositionY.h"
#include "FingerPositionZ.h"

namespace leapmidi {

class FingerGesture : public Gesture {
    void recognizedControls(const Leap::Controller &controller, std::vector<ControlPtr> &controls);
};

typedef std::shared_ptr<FingerGesture> FingerGesturePtr;

}


#endif /* defined(__leapmidi__MIDIGestureFinger__) */
