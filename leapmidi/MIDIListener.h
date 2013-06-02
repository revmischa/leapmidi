/*
 *  MIDIListener.h
 *  LeapMIDI
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#ifndef LeapMIDI_
#define LeapMIDI_

#include <Leap.h>
#include <vector>
#include <iostream>
#include <assert.h>

#ifdef LeapMIDI_OSX
    #include <mach/mach_time.h>
    #include <CoreMIDI/CoreMIDI.h>
    #include <CoreMIDI/MIDIServices.h>
#endif

#include "MIDIGesture.h"
#include "BallGesture.h"

namespace leapmidi {
    
const unsigned int packetListSize = 512;
    
class Listener : public Leap::Listener {
public:
    Listener();
    ~Listener();
    
    void init();
    
    // vector of Gesture instances to detect gesture input
    // and emit control messages
    std::vector<GesturePtr>& gestureRecognizers() { return _gestureRecognizers; }

    // called when we have identified a gesture in the current frame
    virtual void onGestureRecognized(const Leap::Controller &controller, GesturePtr gesture);
    
    // called for each control message emitted by a gesture recognizer
    virtual void onControlUpdated(const Leap::Controller &controller, GesturePtr gesture, ControlPtr control);

    // from Leap::Listener
    virtual void onFrame(const Leap::Controller &controller);
    virtual void onConnect(const Leap::Controller &controller);
    
protected:
    double minLatency = 0, maxLatency = 0, controlCount = 0, totalLatency = 0;
    struct timeval firstFrameAbs;
    int64_t firstFrameLeap, frameCount;
    
    std::vector<GesturePtr> _gestureRecognizers;
    
    void fatal(const char *msg);
    
    void initPacketList();
    void createDevice();
};

} // namespace leapmidi

#endif
