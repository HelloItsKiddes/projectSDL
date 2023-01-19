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
#include <set>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>


#ifndef Project_SDL_H
#define Project_SDL_H

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1.; // frame_rate;
constexpr unsigned frame_width = 1400/2; // Width of window in pixel
constexpr unsigned frame_height = 900/2; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 5;
constexpr unsigned ReproduceTime_ = 1000; //in milliseconds
constexpr unsigned shortInteract_range = 10;
constexpr unsigned longInteract_range = 80;
constexpr unsigned maxAnimals = 12;
constexpr unsigned boostTime = 3000;
constexpr unsigned baseSpeedSheep = 1;
constexpr unsigned rangeDog = 50;

constexpr unsigned dieFromHunger = 20000;

// Helper function to initialize SDL
void init();
class application;

class interacting_object {
  protected:
    std::set<std::string> props;
    double x;
    double y;

  public:
    virtual ~interacting_object(); 
    std::set<std::string> * getProperties() {
      return &props; //raw pointer i don't know if its good
    }

    void addProperty(std::string prop) {
      props.insert(prop);
    }

    void removeProperty(std::string prop) {
      props.erase(prop);
    }

    bool haveProperty(std::string prop) {
      return props.find(prop) != props.end();
    }

    double getX();
    double getY();
    
    void printProps();

    virtual void interact(std::shared_ptr<interacting_object> other);

    virtual void interactLong(std::shared_ptr<interacting_object> other);
};


class rendered_object : public interacting_object {
  
  protected:
  
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                      // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                            // load_surface_for
    // todo: Attribute(s) to define its position
  
 

  public: 
    SDL_Rect rect;
    rendered_object(SDL_Surface* window, const std::string& filepath);
    virtual ~rendered_object();
    double distanceTo(std::shared_ptr<rendered_object> other);
    int getX();
    int getY();
    void setY(int x);
    void setX(int y);

    SDL_Surface* getImage()
    {
      return image_ptr_;
    }
    void draw() ;

};

class moving_object : public rendered_object {
  
  protected:
    double speed = 1;
    double stepX;
    double stepY;
    int myrandint(int lower, int upper); //randint [lower,upper[
  public:
    moving_object(SDL_Surface* window, const std::string& filepath);

    
    virtual ~moving_object();
    virtual void move();
};

class playable_character : public moving_object {
    public:
        playable_character(const std::string& file_path, SDL_Surface *window_surface_ptr);
        virtual ~playable_character();
        virtual void move();
};

#include "animal.h"

#include "sheep.h"
#include "wolf.h"

#include "sheperd.h"
#include "dog.h"
#include "ground.h"

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).


// The application class, which is in charge of generating the window
class application : public std::enable_shared_from_this<application> {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;

  std::unique_ptr<ground> ground_;
  std::shared_ptr<sheperd> sheperd_;
  // Other attributes here, for example an instance of ground

protected:
  std::set<std::shared_ptr<animal>> animals;
public:
  application(unsigned n_sheep, unsigned n_wolf); // Ctor
  ~application();                                 // dtor

  void getInputs();

  void setWolfesTarget();

  void makeObjectsInteract();

  void remove_dead();

  int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
  void addBabies();
};


#endif