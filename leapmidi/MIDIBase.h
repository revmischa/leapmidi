//
//  MIDIBas.h
//  leapmidi
//
//  Created by Chris Czub on 2/16/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIBase__
#define __leapmidi__MIDIBase__

#include <iostream>
#include "MIDITypes.h"

namespace leapmidi {
    class MIDIBase {
    public:
        // create a recognized note with raw input value from recognizer
        virtual const char *description() = 0;
        
        virtual const midi_bodypart_index handIndex()   { return _handIndex; }
        virtual const midi_bodypart_index fingerIndex() { return _fingerIndex; }
        
    protected:
        midi_bodypart_index _handIndex, _fingerIndex;

    };
}

#endif /* defined(__leapmidi__MIDIBase__) */
