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
#include "MIDIProgram.h"
#include "MIDIGesture.h"

namespace leapmidi {

class Listener;
    
class Program {
public:
    virtual ~Program() {};
    virtual void initGestures() = 0;
    
    // find all gestures from frames
    virtual void locateGestures(const Leap::Controller &controller,  Listener *listener);
    
protected:
    // gesture recognizer singletons
    std::vector<GesturePtr>gestureRecognizers;
};

typedef shared_ptr<Program> ProgramPtr;

}

#endif /* defined(__leapmidi__MIDIProgram__) */
