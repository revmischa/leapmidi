//
//  Created by Chris Czub on 2/16/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#include "MIDIListener.h"
#include "MIDINoteProgram.h"

namespace leapmidi {
    
    void NoteProgram::findNotes(const Leap::Controller &controller, Listener *listener) {
        // feed frames to recognizers
        for (vector<GesturePtr>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
            // get controls recognized from gestures
            GesturePtr gesture = *it;
            std::vector<NotePtr> gestureNotes; // controls from this gesture
            gesture->recognizedNotes(controller, gestureNotes);
            
            if (! gestureNotes.size())
                continue;
            
            // call gesture recognized callback
            listener->onGestureRecognized(controller, gesture);
            
            for (vector<NotePtr>::iterator ctl = gestureNotes.begin(); ctl != gestureNotes.end(); ++ctl) {
                NotePtr note = *ctl;
                
                listener->onNoteUpdated(controller, gesture, note);
            }
        }
    }
    
    void NoteProgram::locateGestures(const Leap::Controller &controller, Listener *listener) {
        findNotes(controller, listener);
    }
    
} // namespace leapmidi