#include "interface.h"
#include <iostream>

// ============================================================
//                                                        Class
class Piston : public MovingPart {
public:
  Piston();        // constructor and destructor are nothing special.
  ~Piston();       //
  void update();   // update and payload are overloaded
  float payload(); // (declared purely virtual in MovingPart).
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

float Piston::payload(){
  return ((float)counter / max) * 1.0f; // <------------ change this to 2, 0.1, ...
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
