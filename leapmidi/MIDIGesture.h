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

using namespace std;

namespace leapmidi {

class Gesture {
public:
    Gesture() {}
    
    // given a controller, return MIDI controls recognized from gestures
    virtual void recognizedControls(const Leap::Controller&, std::vector<ControlPtr>&) = 0;
};

} // namespace leapmidi

#endif /* defined(__leapmidi__MIDIGesture__) */
