/*
 *  MIDIListener.cpp
 *  LeapMIDI
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#include "MIDIListener.h"

using namespace std;

namespace leapmidi {
    
static int64_t tv_to_msec(struct timeval &tv) {
    int64_t msec = tv.tv_sec * 1000.0;      // sec to ms
    msec += tv.tv_usec / 1000.0;   // us to ms
    return msec;
}

static int64_t tv_to_usec(struct timeval &tv) {
    int64_t usec = tv.tv_sec * 1000000.0;      // sec to us
    usec += tv.tv_usec;   // us to ms
    return usec;
}

    
Listener::Listener() {    
    firstFrameAbs.tv_sec = 0;
    firstFrameLeap = 0;
}
    
Listener::~Listener() {
    cout << "Total: " << controlCount << ", avg: " <<
    (totalLatency / controlCount) << ", min: " <<
    minLatency << ", max: " << maxLatency << endl;
}
    
void Listener::init() {
}
    
void Listener::onConnect(const Leap::Controller &controller) {
    // reset timers
    cout << "connected\n";
    firstFrameLeap = 0;
    frameCount = 0;
}

void Listener::onFrame(const Leap::Controller &controller) {
    Leap::Frame curFrame = controller.frame();
    if (firstFrameLeap == 0 && ++frameCount > 10) {
        gettimeofday(&firstFrameAbs, NULL);
        firstFrameLeap = curFrame.timestamp();
        cout << "First frame clock time: " << tv_to_usec(firstFrameAbs) << endl;
        cout << "First frame leap time: " << firstFrameLeap << endl;
    }
    
    // use current active gesture recognizers to locate gestures
    // and then trigger appropriate note/controls
    // feed frames to recognizers
    vector<GesturePtr> recognizers = gestureRecognizers();
    for (vector<GesturePtr>::iterator it = recognizers.begin(); it != recognizers.end(); ++it) {
        // get controls recognized from gestures
        GesturePtr gesture = *it;
        std::vector<ControlPtr> gestureControls; // controls from this gesture
        gesture->recognizedControls(controller, gestureControls);
        
        if (! gestureControls.size())
            continue;
        
        // call gesture recognized callback
        onGestureRecognized(controller, gesture);
        
        for (vector<ControlPtr>::iterator ctl = gestureControls.begin(); ctl != gestureControls.end(); ++ctl) {
            ControlPtr control = *ctl;
            
            onControlUpdated(controller, gesture, control);
        }
    }
}
    
// do something productive with these in your application's Listener subclass
void Listener::onGestureRecognized(const Leap::Controller &controller, GesturePtr gesture) {}
void Listener::onControlUpdated(const Leap::Controller &controller, GesturePtr gesture, ControlPtr control) {
    midi_control_index ctrlIdx = control->controlIndex();
    midi_control_value ctrlVal = control->mappedValue();
//    
//    cout << "Recognized control index " << ctrlIdx
//         << " (" << control->description() << ")"
//         << ", raw value: "
//         << control->rawValue() << " mapped value: " << ctrlVal << endl;
    
    if (frameCount <= 10) return;
    
    // control latency
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double elapsedTime = (tv.tv_sec - control->timestamp().tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (tv.tv_usec - control->timestamp().tv_usec) / 1000.0;   // us to ms
    
    // frame latency
    double absoluteTimeOffset = tv_to_usec(tv) - tv_to_usec(firstFrameAbs);
//    cout << "absolute time offset: " << absoluteTimeOffset << endl;
    int64_t curFrameTime = controller.frame().timestamp();
    int64_t frameOffset = curFrameTime - firstFrameLeap;
    int64_t frameLatency = absoluteTimeOffset - frameOffset;
//    cout << "frame: " << curFrameTime << ", absolute offset: " << (absoluteTimeOffset / 1000) << ", frameOffset: " << (frameOffset / 1000) << ", diff: " << (frameLatency / 1000) << endl;
    
    if (minLatency == 0 || frameLatency < minLatency)
        minLatency = frameLatency;
    if (frameLatency > maxLatency)
        maxLatency = frameLatency;
    controlCount++;
    totalLatency += frameLatency;
    
    if (elapsedTime > 3)
        cout << "frame latency: " << (frameLatency / 1000) << ", control output latency: " << elapsedTime << endl;
}
    
void Listener::onNoteUpdated(const Leap::Controller &controller, GesturePtr gesture, NotePtr note) {
    cout << "got note\n";
}

}
