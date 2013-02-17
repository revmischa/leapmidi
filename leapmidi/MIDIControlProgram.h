//
//  MIDIControlProgram.h
//  leapmidi
//
//  Created by Chris Czub on 2/16/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIControlProgram__
#define __leapmidi__MIDIControlProgram__

#include <iostream>
#include "MIDIProgram.h"
#include "MIDIGesture.h"
#include "MIDIControl.h"

namespace leapmidi {
        
    class ControlProgram : public Program {
    public:
        // find all recognized MIDI controls from frames
        // calls onGestureRecognized and onControlUpdated
        virtual void findControls(const Leap::Controller &controller,  Listener *listener);
        virtual void locateGestures(const Leap::Controller &controller, Listener *listener);
        
    };
    
    typedef shared_ptr<ControlProgram> ControlProgramPtr;
    
}

#endif /* defined(__leapmidi__MIDIControlProgram__) */
