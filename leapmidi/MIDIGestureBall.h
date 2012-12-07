//
//  MIDIGestureBall.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIGestureBall__
#define __leapmidi__MIDIGestureBall__

#include <iostream>
#include "MIDIGesture.h"
#include <vector>
#include "MIDIControl.h"
#include <Leap.h>

namespace LeapMIDI {
namespace Gesture {
    
class Ball : public LeapMIDI::Gesture::Base {
    std::vector<LeapMIDI::Control::Base> recognizedControls(const Leap::Controller &controller);
};
    
}
}

#endif /* defined(__leapmidi__MIDIGestureBall__) */
