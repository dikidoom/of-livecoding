#pragma once

class MovingPart {
 public:
  MovingPart();
  virtual void update();
  virtual float payload();
  int counter;
  int max;
};
