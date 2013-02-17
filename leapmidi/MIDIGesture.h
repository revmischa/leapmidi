//
//  MIDIGesture.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

// This base class represents a gesture interpreter which converts hand motions into MIDI control values.
// Each interpreter is instantiated as a singleton and passed a Leap::Controller each frame, which it can
// use to analyze current (and past) frames to make a determination about which related controls are present,
// and their values.

// An interpreter may recognize more than one control. For example, a finger gesture recognizer may return
// X/Y/Z coordinates each as a separate control, and roll/pitch/yaw as seperate controls, giving the user
// a total of 6 control values per finger

#ifndef __leapmidi__MIDIGesture__
#define __leapmidi__MIDIGesture__

#include <iostream>
#include <vector>
#include "MIDIControl.h"
#include "MIDINote.h"
#include "MIDITypes.h"
#include <Leap.h>

using namespace std;

namespace leapmidi {

class Gesture {
public:
    Gesture() {}
    
    // given a controller, return MIDI controls recognized from gestures
    virtual void recognizedControls(const Leap::Controller&, std::vector<ControlPtr>&) = 0;
    
    // given a controller, return MIDI notes recognized from gestures
    virtual void recognizedNotes(const Leap::Controller&, std::vector<NotePtr>&) = 0;
};

typedef shared_ptr<Gesture> GesturePtr;

} // namespace leapmidi

#endif /* defined(__leapmidi__MIDIGesture__) */
