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
#include "LeapMIDI.h"

namespace leapmidi {

class FingerPosition : public Control {
public:
    FingerPosition(int hi, int fi, double pos) : Control(pos, hi) {
        _fingerIndex = fi;
    }
    
    // override this in subclass to define the control index of hand 1/finger 1
    virtual midi_control_index controlIndexBase() = 0;
    
    virtual midi_control_index controlIndex();

    int fingerIndex() { return _fingerIndex; }

protected:
    int _fingerIndex;
};
    
typedef std::shared_ptr<FingerPosition> FingerPositionPtr;

}


#endif /* defined(__leapmidi__MIDIControlFingerPosition__) */
