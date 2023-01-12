// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1.; // frame_rate;
constexpr unsigned frame_width = 1400/2; // Width of window in pixel
constexpr unsigned frame_height = 900/2; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 0;

// Helper function to initialize SDL
void init();
class application;
class animal {
  private:
    SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                      // animal to be drawn, also non-owning
    SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                            // load_surface_for
    // todo: Attribute(s) to define its position
  
    
  protected:
    int x_state = 1;
    int y_state = 1;

    //std::shared_ptr<application> app;
    //std::shared_ptr<ground> ground_;
      
  public:
    
    SDL_Rect rect;
    

    //animal(const std::string& file_path,SDL_Surface *window_surface_ptr,std::shared_ptr<ground> ground_);
    animal(const std::string& file_path, SDL_Surface *window_surface_ptr);
    // todo: The constructor has to load the sdl_surface that corresponds to the
    // texture
    virtual ~animal(); // todo: Use the destructor to release memory and "clean up
                // behind you"

    void draw() ; // todo: Draw the animal on the screen <-> window_surface_ptr.
                  // Note that this function is not virtual, it does not depend
                  // on the static type of the instance

    virtual void move() = 0; // todo: Animals move around, but in a different
      // fashion depending on which type of animal

    int myrandint(int lower, int upper);

    SDL_Surface* getImage()
    {
      return image_ptr_;
    }
    virtual void setTargetX(int x) = 0;

    virtual void setTargetY(int y) = 0 ;
};

// Insert here:
// class sheep, derived from animal
class sheep : public animal {

  public:
  sheep(SDL_Surface *window_surface_ptr);
	virtual ~sheep() {}
	virtual void move() override;

  void setTargetX(int x);

  void setTargetY(int y);
  // implement functions that are purely virtual in base class
};



// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves
class wolf : public animal {
  private:
    int targetX;
    int targetY;

  public:

  wolf(SDL_Surface *window_surface_ptr);
	virtual ~wolf() {}
	virtual void move() override;

  void setTargetX(int x);

  void setTargetY(int y);
};


// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
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
  
};

// The application class, which is in charge of generating the window
class application : public std::enable_shared_from_this<application> {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;

  std::unique_ptr<ground> ground_;
  // Other attributes here, for example an instance of ground

protected:
  std::vector<std::shared_ptr<animal>> animals;
public:
  application(unsigned n_sheep, unsigned n_wolf); // Ctor
  ~application();                                 // dtor

  void setWolfesTarget();

  int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};