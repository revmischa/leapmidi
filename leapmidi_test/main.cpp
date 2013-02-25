//
//  main.cpp
//  leapmidi_test
//
//  Created by Mischa Spiegelmock on 11/28/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include <iostream>
#include <LeapMIDI.h>
#include <Leap.h>
#include "MIDIListener.h"

using namespace std;

int main(int argc, const char * argv[]) {
    leapmidi::Listener listener;
    Leap::Controller controller;
    controller.addListener(listener);

    cout << "Press enter to quit..." << std::endl;
    cin.get();
    
    controller.removeListener(listener);

    return 0;
}
