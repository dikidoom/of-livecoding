#include "ofApp.h"
#include <dlfcn.h>

volatile std::sig_atomic_t ofApp::sigSwap;

//--------------------------------------------------------------
void signal_handler( int signal ){
  ofLog() << "Whoo, a signal!";
  ofApp::sigSwap = 1; // let ofApp know that a new library is available 
}

//--------------------------------------------------------------
void ofApp::setup(){
  hotSwap( true );  // open library for the first time
  std::signal( SIGINT, signal_handler ); // register signal handler
}

//--------------------------------------------------------------
void ofApp::update(){
  if( sigSwap == 1 ){
    hotSwap( false );
  }
}

//--------------------------------------------------------------
void ofApp::hotSwap( bool firstTime ){
  sigSwap = 0;
  if( !firstTime ){
    // close previous handle
    int close = dlclose( handle );
    if( close != 0 ){
      ofLog() << "Error: " << dlerror();
      return;
    }
  }
  // open new handle
  ofLog() << "Opening lib ... ";
  handle = dlopen( "simple.so", RTLD_LAZY );
  if( handle == NULL ){
    ofLog() << "Error: " << dlerror();
    return;
  } else {
    // bind function names
    dynamics.mydouble = (float(*)(float)) dlsym( handle, "mydouble" );
    dynamics.mytriple = (float(*)(float)) dlsym( handle, "mytriple" );
  }
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
  ofClear( ofColor::black );
  int distance = 100;
  float speed = 1.0f;
  ofPoint orbit1 = orbit( 1 * distance,
                          speed );
  ofPoint orbit2 = orbit( 2 * distance,
                          (*dynamics.mydouble)( speed ) );
  ofPoint orbit3 = orbit( 3 * distance,
                          (*dynamics.mytriple)( speed ) );
  //
  ofSetColor( ofColor::red );
  ofDrawSphere( orbit1, 20 );
  //
  ofSetColor( ofColor::green );
  ofDrawSphere( orbit2, 20 );
  //
  ofSetColor( ofColor::blue );
  ofDrawSphere( orbit3, 20 );
}

//--------------------------------------------------------------
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
