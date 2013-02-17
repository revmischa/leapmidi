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

using namespace std;

class TestListener : public leapmidi::Listener {
public:
    virtual void onFrame(const Leap::Controller &controller);
};

void TestListener::onFrame(const Leap::Controller &controller) {
}

int main(int argc, const char * argv[]) {
    TestListener listener;
    Leap::Controller controller;
    controller.addListener(listener);

    cout << "Press Enter to quit..." << std::endl;
    cin.get();
    
    controller.removeListener(listener);

    return 0;
}

