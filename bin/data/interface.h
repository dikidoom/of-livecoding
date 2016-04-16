#pragma once

// this is the 'interface' class included by both the main app
// and the classy.so library.
// note that all functions are pure virtual (=0) and
// there is no constructor / destructor.

class MovingPart {
 public:
  // virtual MovingPart()=0;
  // virtual ~MovingPart()=0;
  virtual void update()=0;
  virtual void draw()=0;
  virtual float payload()=0;
};
