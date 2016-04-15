#include "interface.h"
#include <iostream>

// ============================================================
//                                                        Class
MovingPart::MovingPart()
  : counter( 0 )
  , max( 360 ){
  std::cout << "in classy.so: constructor\n";
}

void MovingPart::update(){
  ++counter;
  counter %= max;
}

float MovingPart::payload(){
  return ((float)counter / max) * 1.0f; // <------------ change this to 2, 0.1, ...
}

// class Piston : public MovingPart {
// public:
//   Piston();
//   void update();
//   float payload();
//   int counter;
//   int max;
// };

// Piston::Piston()
//   : max( 360 ){  
// }

// void Piston::update(){
//   ++counter;
//   counter %= max;
// }

// float Piston::payload(){
//   return 1.0f * counter / max;
// }

// =============================================================
//                                             Library Interface
extern "C" {
  void sanity( void );
  MovingPart* createObject( void );
  void destroyObject( MovingPart* object );
};

void sanity( void ){
  std::cout << "sanity\n";
}

MovingPart* createObject( void ){
  std::cout << "in classy.so: createObject\n";
  MovingPart* foo = new MovingPart;
  return foo;
}

void destroyObject( MovingPart* object ){
  delete object;
}
