// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
  

  //we want to suppress that next
  auto window_ptr = SDL_CreateWindow("SDL2 Window",
          SDL_WINDOWPOS_CENTERED,
          SDL_WINDOWPOS_CENTERED,
          194, 259,
          0);

  if (!window_ptr)
    throw std::runtime_error(std::string(SDL_GetError()));

  auto window_surface_ptr = SDL_GetWindowSurface(window_ptr);

  if (!window_surface_ptr)
    throw std::runtime_error(std::string(SDL_GetError()));
}


//implementation of the .h


//Application part -----

application::application(unsigned n_sheep, unsigned n_wolf) {
    
    //here we creat window
    window_ptr_ = SDL_CreateWindow(
        "SHEEP AND WOLFES",                  // title
        0,//SDL_WINDOWPOS_UNDEFINED,            initial position
        0,//SDL_WINDOWPOS_UNDEFINED,            initial position
        frame_width, frame_height, SDL_WINDOW_SHOWN);

    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);

    ground_ = std::make_uniqueground>(window_surface_ptr_);

    for (size_t i = 0; i < n_sheep; i++)
        ground_->add_animal(std::make_shared<sheep>(window_surface_ptr_));
/*
    for (size_t i = 0; i < n_wolf; i++)
        ground_->add_animal(std::make_shared<wolf>(window_surface_ptr_));*/
}

int application::loop(unsigned period) {
    SDL_Rect windowsRect = SDL_Rect{ 0,0,frame_width, frame_height };
    bool quit = false;
    while (!quit && (SDL_GetTicks() <= period * 1000)) { 
        SDL_FillRect(window_surface_ptr_, &windowsRect, SDL_MapRGB(window_surface_ptr_->format, 0, 255, 0));
        SDL_PollEvent(&window_event_);
        if (window_event_.type == SDL_QUIT)  //|| window_event_.type == SDL_WINDOWEVENT && window_event_.window.event == SDL_WINDOWEVENT_CLOSE
            break;
        ground_->update();
        SDL_UpdateWindowSurface(window_ptr_);
        SDL_Delay(frame_time * 1000);  // Pause execution for framerate milliseconds
    }
    return 1;
}


//animal part ------
animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr) {
    //load_surface_for(file_path.c_str(), window_surface_ptr);
    image_ptr_ = IMG_Load(file_path.c_str());
    window_surface_ptr_ = window_surface_ptr;
    rect.x = 200; //rand() % with
    rect.y = 0;
    rect.w = image_ptr_->w;
    rect.h = image_ptr_->h;

};

animal::~animal() {
    SDL_FreeSurface(image_ptr_);
};

void animal::draw() {
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &rect);
};





//ground part -------
ground::ground(SDL_Surface* window_surface_ptr) {
    window_surface_ptr_ = window_surface_ptr;
    animalsVect = std::vector<std::shared_ptr<animal>>();
}

void ground::add_animal(std::shared_ptr<animal> newAnimal) {
    animalsVect.push_back(newAnimal);
}

void ground::update() {
    for (std::shared_ptr<animal> oneAnimal : animalsVect)
    {
        oneAnimal->draw();
        oneAnimal->move();
    }
}

//sheeep ------------------
sheep::sheep(SDL_Surface* window_surface_ptr) : animal("./media/sheep.png", window_surface_ptr) {
    this->rect.x = rand() % 200; //getRandomSpawn(DIRECTION::HORIZONTAL);
    this->rect.y = rand() % 200; // getRandomSpawn(DIRECTION::VERTICAL);
}

void sheep::move() {
    return;
}



namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

SDL_Surface* load_surface_for(const std::string& path,
                              SDL_Surface* window_surface_ptr) {
  
  return window_surface_ptr;
  // Helper function to load a png for a specific surface
  // See SDL_ConvertSurface 
  // i don't understand why use SDL_ConvertSurface
}
} // namespace
