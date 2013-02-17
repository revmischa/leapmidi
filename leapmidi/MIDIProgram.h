//
//  MIDIProgram.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 1/5/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIProgram__
#define __leapmidi__MIDIProgram__

#include <iostream>
#include "MIDIListener.h"
#include "MIDIProgram.h"
#include "MIDIGesture.h"
#include "MIDIControl.h"

namespace leapmidi {

class Listener;
    
class Program {
public:
    virtual void onGestureRecognized(const Leap::Controller &controller, GesturePtr gesture) = 0;
    virtual void onControlUpdated(const Leap::Controller &controller, GesturePtr gesture, ControlPtr control) = 0;
    
    // find all recognized MIDI controls from frames
    void findControls(const Leap::Controller &controller,  Listener &listener, std::vector<ControlPtr> &inOutRecognizedControls);
    
protected:
    // gesture recognizer singletons
    std::vector<GesturePtr>gestureRecognizers;
};

}

#endif /* defined(__leapmidi__MIDIProgram__) */
