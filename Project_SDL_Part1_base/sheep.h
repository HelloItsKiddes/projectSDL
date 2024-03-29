#include "Project_SDL1.h"
#ifndef SHEEP_H
#define SHEEP_H

// Insert here:
// class sheep, derived from animal
class sheep : public animal {
  private:
    int last_offspring; //maybe make it property but for a time it seems strange
    int lastBoost;
    double fleeFromX;
    double fleeFromY;
  public:
  sheep(SDL_Surface *window_surface_ptr);
  //sheep::sheep(SDL_Surface *window_surface_ptr,int x,int y) ;
	virtual ~sheep();
	void move() override;

  void setTarget(int nx, int ny);
  // implement functions that are purely virtual in base class

  void fleeFromTarget();

  void interact(std::shared_ptr<interacting_object> other) override;

  void interactLong(std::shared_ptr<interacting_object> other) override;
};

#endif 
