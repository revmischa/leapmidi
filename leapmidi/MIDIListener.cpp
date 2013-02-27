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
    
Listener::Listener() {
    BallGesturePtr ballGesture = make_shared<BallGesture>();
    GesturePtr ballGestureBasePtr = dynamic_pointer_cast<Gesture>(ballGesture);
    _gestureRecognizers.push_back(ballGestureBasePtr);
    
    midiPacketList = NULL;
    createDevice();
}

void Listener::onFrame(const Leap::Controller &controller) {    
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
    
    cout << "Recognized control index " << ctrlIdx
         << " (" << control->description() << ")"
         << ", raw value: "
         << control->rawValue() << " mapped value: " << ctrlVal << endl;
    
    assert(ctrlIdx < 120);
    assert(ctrlVal <= 127);
    
    // build midi packet
    u_int8_t packetOut[3];
    packetOut[0] = 0xB0;     // channel
    packetOut[1] = ctrlIdx;  // controller number
    packetOut[2] = ctrlVal;  // controller value
    
    int z;
    printf("Sending MIDI packet: ");
    for (z = 0; z < 3; z++)
    {
        if (z > 0) printf(":");
        printf("%02X", packetOut[z]);
    }
    printf("\n");
    
    
    // add packet to packet list
    initPacketList();
    curPacket = MIDIPacketListAdd(midiPacketList, packetListSize, curPacket, 0, 3, packetOut);
    if (! curPacket) {
        std::cerr << "Buffer overrun on midi packet list\n";
        exit(1);
    }
    OSStatus res = MIDIReceived(deviceEndpoint, midiPacketList);
    if (res)
        fatal("MIDIReceived() failed");
}

void Listener::initPacketList() {
    if (midiPacketList) {
        free(midiPacketList);
        midiPacketList = NULL;
    }
    
    midiPacketList = (MIDIPacketList *)malloc(packetListSize * sizeof(char));
    curPacket = MIDIPacketListInit(midiPacketList);
}
    
void Listener::createDevice() {
    OSStatus result;
    
    result = MIDIClientCreate(CFSTR("LeapMIDIX"), NULL, NULL, &deviceClient);
    if (result)
        fatal("Failed to create MIDI client");
    
    result = MIDISourceCreate(deviceClient, CFSTR("LeapMIDIX Control"), &deviceEndpoint);
    if (result)
        fatal("Failed to create MIDI source");
    
}

void Listener::fatal(const char *msg) {
    cerr << "Fatal error: " << msg << endl;
    exit(1);
}

}
