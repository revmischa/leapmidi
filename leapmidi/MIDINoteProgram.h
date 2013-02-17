//
//  MIDINoteProgram.h
//  leapmidi
//
//  Created by Chris Czub on 2/16/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#ifndef __leapmidi__MIDINoteProgram__
#define __leapmidi__MIDINoteProgram__

#include <iostream>
#include "MIDIProgram.h"
#include "MIDIGesture.h"
#include "MIDINote.h"

namespace leapmidi {
    
    class NoteProgram : public Program {
    public:
        // find all recognized MIDI notes from frames
        // calls onGestureRecognized and onNoteUpdated
        virtual void findNotes(const Leap::Controller &controller,  Listener *listener);
        virtual void locateGestures(const Leap::Controller &controller, Listener *listener);
        
    };
    
    typedef shared_ptr<NoteProgram> NoteProgramPtr;
    
}

#endif /* defined(__leapmidi__MIDINoteProgram__) */
