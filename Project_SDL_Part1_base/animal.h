#include "Project_SDL1.h"
#ifndef ANIMAL_H
#define ANIMAL_H



class animal : public moving_object {
  
    
    
  protected:
    int x_state = 1;
    int y_state = 1;

    Target target;
    //std::shared_ptr<application> app;
    //std::shared_ptr<ground> ground_;
      
  public:
    

    //animal(const std::string& file_path,SDL_Surface *window_surface_ptr,std::shared_ptr<ground> ground_);
    animal(const std::string& file_path, SDL_Surface *window_surface_ptr);
    // todo: The constructor has to load the sdl_surface that corresponds to the
    // texture
    virtual ~animal(); // todo: Use the destructor to release memory and "clean up
                // behind you"

    virtual void draw() ; // todo: Draw the animal on the screen <-> window_surface_ptr.
                  // Note that this function is not virtual, it does not depend
                  // on the static type of the instance

    virtual void move() = 0; // todo: Animals move around, but in a different
      // fashion depending on which type of animal

    void setRandTarget() ;

    void  moveToTarget() ;
    
    void calculate_steps ();

    SDL_Surface* getImage()
    {
      return image_ptr_;
    }
    virtual void setTargetX(int x) = 0;

    virtual void setTargetY(int y) = 0 ;

    
};

#endif /*ANIMAL_H*/