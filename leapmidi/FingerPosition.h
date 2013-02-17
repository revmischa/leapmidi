//
//  FingerPosition.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/13/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIControlFingerPosition__
#define __leapmidi__MIDIControlFingerPosition__

#include <iostream>
#include "MIDIControl.h"
#include "MIDINote.h"

using namespace std;

namespace leapmidi {

class FingerPosition : public Control, public Note {
public:
    FingerPosition(midi_bodypart_index hi, midi_bodypart_index fi, double pos) : Control(hi, fi, pos), Note(hi, fi, pos) {}

    virtual ~FingerPosition() {}

    // override this in subclass to define the control index of hand 1/finger 1
    virtual const midi_control_index controlIndexBase() = 0;
    
    virtual const midi_control_index controlIndex();
    
    virtual const midi_note_index noteIndexBase() = 0;
    
    virtual const midi_note_index noteIndex();

};
    
typedef shared_ptr<FingerPosition> FingerPositionPtr;

}


#endif /* defined(__leapmidi__MIDIControlFingerPosition__) */
