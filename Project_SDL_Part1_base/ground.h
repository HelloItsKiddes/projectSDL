#include "Project_SDL1.h"
#include <algorithm>
#ifndef GROUND_H
#define GROUND_H

class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Surface* window_surface_ptr_;

  std::vector<std::shared_ptr<animal>> animalsVect_;
  // here
  
public:
 

  ground(SDL_Surface* window_surface_ptr); // todo: Ctor

  ~ground(); // todo: Dtor, again for clean up (if necessary) 
  //i dunno if it is necessary 

  void add_animal(std::shared_ptr<animal> animalToAdd); // todo: Add an animal


  void update(SDL_Surface *window_surface_ptr_); // todo: "refresh the screen": Move animals and draw them
  // Possibly other methods, depends on your implementation

  void test();

  std::vector<std::shared_ptr<animal>> getVect()
  {
    return animalsVect_;
  }

  void makeAllInteract() {

  }
  
  void make_interact() ;

  void setTargets();  

  void remove_animal(int animalToRemove);

  void remove_dead();

};

#endif /*GROUND_H*/