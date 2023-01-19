#include "Project_SDL1.h"
#ifndef ANIMAL_H
#define ANIMAL_H



class animal : public moving_object {
  
    
    
  protected:
    int x_state = 1;
    int y_state = 1;

    struct {int x; int y;} target;
    //std::shared_ptr<application> app;
    //std::shared_ptr<ground> ground_;
      
  public:
    

    //animal(const std::string& file_path,SDL_Surface *window_surface_ptr,std::shared_ptr<ground> ground_);
    animal(const std::string& file_path, SDL_Surface *window_surface_ptr);
    // todo: The constructor has to load the sdl_surface that corresponds to the
    // texture
    virtual ~animal(); // todo: Use the destructor to release memory and "clean up
                // behind you"


    virtual void move() = 0; // todo: Animals move around, but in a different
      // fashion depending on which type of animal

    void setRandTarget() ;

    void  moveToTarget() ;
    
    void calculate_steps ();


    void setTarget(double x, double y);
    
};

#endif /*ANIMAL_H*/