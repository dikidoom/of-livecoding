#pragma once

class MovingPart {
 public:
  // virtual MovingPart()=0;
  // virtual ~MovingPart()=0;
  virtual void update()=0;
  virtual float payload()=0;
};
