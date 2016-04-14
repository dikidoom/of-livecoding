#include "ofApp.h"
#include <dlfcn.h>
#include <csignal>

//--------------------------------------------------------------
void signal_handler( int signal ){
  ofLog() << "Whoo, a signal!";
}

void ofApp::setup(){
  // opening
  ofLog() << "Opening lib ... ";
  handle = dlopen( "mylib.so", RTLD_LAZY );
  if( handle == NULL ){
    ofLog() << "Error: " << dlerror();
  } else {
    // binding
    dynamics.mydouble = (int(*)(int)) dlsym( handle, "mydouble" );
  }
  // signal
  std::signal( SIGINT, signal_handler );
}

void ofApp::exit(){
  ofLog() << "Exiting ... ";
  int close = -1;
  if( handle != NULL ){
    ofLog() << "Closing lib ... ";
    close = dlclose( handle );
    if( close != 0 ){
      ofLog() << "Error: " << dlerror();
    }
  }
  ofBaseApp::exit();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
ofPoint orbit( int distance = 300, float speed = 1.0f ){
  uint64_t time = ofGetElapsedTimeMillis();
  float scale = speed / 1000;
  ofPoint center = { ofGetWindowWidth() / 2,
                     ofGetWindowHeight() / 2 };
  ofPoint offset = { cos( time * scale ) * distance,
                     sin( time * scale ) * distance };
  return center + offset;
}

void ofApp::draw(){
  ofSetColor( ofColor::black );
  ofPoint orbit1 = orbit( 100,
                          1.0f );
  ofPoint orbit2 = orbit( (*dynamics.mydouble)(100),
                          2.0f );
  ofDrawSphere( orbit1, 20 );
  ofDrawSphere( orbit2, 20 );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
