#include "interface.h"
#include "ofMain.h" // <------------ hey look, its openFrameworks!
#include <iostream>

// this is the implementation of the 'interface' defined in interface.h
// note that it can be a subclass of the interface and add additional
// members & methods, as long as it also implements the pure virtual
// methods of the interface.
//
// the helper functions for constructing and de-constructing objects
// are due to the linkage limitations – language linkage only works for
// C semantics, which excludes C++ constructors/destructors – and
// because the main app _intentionally_ has no clue about this implementation.

// ============================================================
//                                                        Class
class Piston : public MovingPart {
public:
  Piston();        // constructor and destructor are nothing special.
  ~Piston();       //
  void update();   // update, draw and payload are overloaded
  void draw();     // (declared purely virtual in MovingPart).
  float payload(); //
private:
  int counter;     // all kinds of additional hijinx -
  int max;         // nobody cares as long as the MovingPart interface is satisfied.
};

Piston::Piston()
  : counter( 0 )
  , max( 360 ){
}

Piston::~Piston(){
}

void Piston::update(){
  ++counter;
  counter %= max;
}

void Piston::draw(){
  // Whats this, an openFrameworks call in your shared library? Oh yes!
  ofSetColor( ofColor::blue ); // <------------ change to white, yellow, ...
  ofDrawSphere( { ofGetWidth() / 2, ofGetHeight() / 2 }, 30 );
}

float Piston::payload(){
  return ((float)counter / max) * 1.0f;
}

// =============================================================
//                                             Library Interface
extern "C" {
  Piston* createObject( void );         // because language linkage happens in C and the main C++ app
  void destroyObject( Piston* object ); // has no clue of our class details, we need these helpers.
};

Piston* createObject( void ){
  return new Piston;
}

void destroyObject( Piston* object ){
  delete object;
}
