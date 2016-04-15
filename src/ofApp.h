#pragma once

#include "ofMain.h"
#include "../bin/data/interface.h"
#include <csignal>

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
        void exit();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        
        void hotSwap( bool firstTime ); // (re-)load library

        void* handle; // library handle

        struct {
          MovingPart* (*create)(void);
          void (*destroy)(MovingPart*);
        } dynamics;

        MovingPart* piston;
        
        static volatile std::sig_atomic_t sigSwap; // signal flag (interprocess communication gymnastics)
};
