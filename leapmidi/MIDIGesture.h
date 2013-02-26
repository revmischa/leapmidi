//
//  MIDIGesture.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIGesture__
#define __leapmidi__MIDIGesture__

#include <iostream>
#include <vector>
#include "MIDIControl.h"
#include <Leap.h>

namespace leapmidi {

class Gesture {
public:
    // given a controller, return MIDI controls recognized from gestures
    virtual void recognizedControls(const Leap::Controller &controller, std::vector<ControlPtr> &gesturesOut) = 0;
};

} // namespace leapmidi

#endif /* defined(__leapmidi__MIDIGesture__) */
