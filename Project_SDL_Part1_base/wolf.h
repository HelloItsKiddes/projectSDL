#include "Project_SDL1.h"
#ifndef WOLF_H
#define WOLF_H

// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves
class wolf : public animal {
  private:
    int last_meal = 0;
  public:

  wolf(SDL_Surface *window_surface_ptr);
	virtual ~wolf();
	virtual void move() override;

  void setTargetX(int x);

  void setTargetY(int y);

  void interact(std::shared_ptr<interacting_object> other) override;
};

#endif 