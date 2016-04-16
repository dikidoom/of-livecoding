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
  handle = NULL;
  piston = nullptr;
  hotSwap( true );  // open library for the first time
  std::signal( SIGINT, signal_handler ); // register signal handler
}

//--------------------------------------------------------------
void ofApp::update(){
  if( sigSwap == 1 ){
    hotSwap( false );
  }
  piston->update();
}

//--------------------------------------------------------------
void ofApp::hotSwap( bool firstTime ){
  sigSwap = 0;
  if( !firstTime ){
    ofLog() << "Closing lib ... ";
    // close previous handle
    dynamics.destroy( piston );
    int close = dlclose( handle );
    if( close != 0 ){
      ofLog() << "Error: " << dlerror();
      return;
    } else {
      ofLog() << "Lib closed ok.";
    }
  }
  // open new handle
  ofLog() << "Opening lib ... ";
  handle = dlopen( "classy.so", RTLD_LAZY );
  if( handle == NULL ){
    ofLog() << "Error: " << dlerror();
    return;
  } else {
    ofLog() << "Lib opened ok.";
    // bind function names
    dynamics.create = (MovingPart*(*)()) dlsym( handle, "createObject" );
    dynamics.destroy = (void(*)(MovingPart*)) dlsym( handle, "destroyObject" );
    if( dynamics.create == NULL ||
        dynamics.destroy == NULL){
      ofLog() << "Error binding symbols";
    }
    // create object from library
    piston = dynamics.create();
  }
}

//--------------------------------------------------------------
ofPoint orbit( int distance = 300, float position = .0f ){
  ofPoint center = { ofGetWindowWidth() / 2,
                     ofGetWindowHeight() / 2 };
  ofPoint offset = { cos( position * TWO_PI ) * distance,
                     sin( position * TWO_PI ) * distance };
  return center + offset;
}

void ofApp::draw(){
  ofClear( ofColor::black );
  int distance = 100;
  float position = ofGetElapsedTimeMillis() / 5000.f;
  ofPoint orbit1 = orbit( distance,
                          position );
  ofPoint orbit2 = orbit( 2 * distance,
                          piston->payload() );
  /* ofPoint orbit3 = orbit( 3 * distance, */
  /*                         (*dynamics.mytriple)( speed ) ); */
  //
  ofSetColor( ofColor::red );
  ofDrawSphere( orbit1, 20 );
  //
  ofSetColor( ofColor::green );
  ofDrawSphere( orbit2, 20 );
  //
  /* ofSetColor( ofColor::blue ); */
  /* ofDrawSphere( orbit3, 20 ); */
  piston->draw();
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
