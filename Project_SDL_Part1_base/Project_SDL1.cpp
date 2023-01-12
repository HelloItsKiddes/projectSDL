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
        0,//                         initial position
        0,//                          initial position
        frame_width, frame_height, SDL_WINDOW_SHOWN);

    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);

    ground_ = std::make_unique<ground>(window_surface_ptr_);

    //std::vector<std::shared_ptr<animal>> animals = ground_->getVect(); //possible memory leak. Need to be std::shared_ptr<std::vector<std::shared_ptr<animal>>> ????
    


    for (size_t i = 0; i < n_sheep; i++)
         ground_->add_animal(std::make_shared<sheep>(window_surface_ptr_));

    

    for (size_t i = 0; i < n_wolf; i++)
        ground_->add_animal(std::make_shared<wolf>(window_surface_ptr_));

    
    animals = ground_->getVect();

    
    setWolfesTarget();
}

void application::setWolfesTarget() {
    std::vector<int> Xsheeps;
    std::vector<int> Ysheeps;

    for(std::shared_ptr<animal> &ani : animals)
    {
        if (std::string(typeid(*ani).name()) == "5sheep")
        {
            int x = ani->rect.x;
            int y = ani->rect.y;
            Xsheeps.push_back(x);
            Ysheeps.push_back(y);
        }
    }
    for(std::shared_ptr<animal> &ani : animals)
    {
        if (std::string(typeid(*ani).name()) == "4wolf")
        {
            int xmin = frame_width;
            int ymin = frame_height;
            int xwolf = ani->rect.x;
            int ywolf = ani->rect.y;
            int xTarget;
            int yTarget;
            for (size_t i = 0; i < Xsheeps.size(); i++)
            {
                if (abs(xwolf - Xsheeps[i]) < xmin)
                {
                    xTarget = Xsheeps[i];
                    xmin = abs(xwolf - Xsheeps[i]);
                }
                if (abs(ywolf - Ysheeps[i]) < ymin)
                {
                    yTarget = Ysheeps[i];
                    ymin = abs(ywolf - Ysheeps[i]);
                }
            }
            ani->setTargetX(xTarget);
            ani->setTargetY(yTarget);
        }
    }
    Xsheeps.clear();
    Ysheeps.clear();
}


int application::loop(unsigned period) {
    SDL_Rect windowsRect = SDL_Rect{ 0,0,frame_width, frame_height };
    bool quit = false;
    
    while (!quit && (SDL_GetTicks() <= period * 1000)) { 
        setWolfesTarget();
        SDL_FillRect(window_surface_ptr_, &windowsRect, SDL_MapRGB(window_surface_ptr_->format, 0, 255, 0));
        SDL_PollEvent(&window_event_);
        if (window_event_.type == SDL_WINDOWEVENT && window_event_.window.event == SDL_WINDOWEVENT_CLOSE) //seems like u have to do that
            break;
        ground_->update(window_surface_ptr_);
        SDL_UpdateWindowSurface(window_ptr_);
        SDL_Delay(frame_time * 30);  // Pause execution for framerate milliseconds
    }
    return 0;
}

application::~application() {
    // Close and destroy the window
    SDL_DestroyWindow(window_ptr_);
}


//animal part ------
animal::animal(const std::string& file_path, SDL_Surface *window_surface_ptr) {
    //load_surface_for(file_path.c_str(), window_surface_ptr);
    //this->ground_ = ground_;
    //this->app = app;
    image_ptr_ = IMG_Load(file_path.c_str());
    rect.x = 0; //rand() % with
    rect.y = 0;
    rect.w = image_ptr_->w;
    rect.h = image_ptr_->h;
    window_surface_ptr_ = window_surface_ptr;

};

animal::~animal() {
    SDL_FreeSurface(image_ptr_);
};

void animal::draw() {
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &rect);
};

void animal::move() {
    return;
}

int animal::myrandint(int lower, int upper) {
    
    //for random : https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range
    
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(lower, upper);
    return distr(generator);
}





//ground part -------
ground::ground(SDL_Surface* window_surface_ptr) {
    window_surface_ptr_ = window_surface_ptr;
    animalsVect_ = std::vector<std::shared_ptr<animal>>();
}

ground::~ground() {
};

void ground::add_animal(std::shared_ptr<animal> newAnimal) {
    animalsVect_.push_back(newAnimal);
}

void ground::update(SDL_Surface *window_surface_ptr_) {
    for (std::shared_ptr<animal> &oneAnimal : animalsVect_)
    {
        oneAnimal->draw();
        oneAnimal->move();
    }
}


//sheeep ------------------
sheep::sheep(SDL_Surface *window_surface_ptr) : animal("./media/sheep.png", window_surface_ptr) {
    const int range_from  = 0;
    const int range_to_frame_width    = frame_width - getImage()->w - frame_boundary;
    const int range_to_frame_height    = frame_height - getImage()->h - frame_boundary;
    int a = myrandint(range_from,range_to_frame_width);
    int b = myrandint(range_from,range_to_frame_height);
    this->rect.x = a; 
    this->rect.y = b; 
}

void sheep::move() {
    int next_x = this->rect.x + x_state;
    int next_y = this->rect.y + y_state;
    if (next_x + getImage()->w >= frame_width - frame_boundary || next_x <= 0 + frame_boundary) {
        x_state = x_state * -1;
    }
    if (next_y + getImage()->h >= frame_height - frame_boundary || next_y <= 0 + frame_boundary) {
        y_state = y_state * -1;
    }
    this->rect.x = this->rect.x + x_state;
    this->rect.y = this->rect.y + y_state;
}

void sheep::setTargetX(int x)
{
    return;
}

void sheep::setTargetY(int y)
{
    return;
}



//wolf ------------------
wolf::wolf(SDL_Surface *window_surface_ptr) : animal("./media/wolf.png", window_surface_ptr) {
    const int range_from  = 0;
    const int range_to_frame_width    = frame_width - getImage()->w - frame_boundary;
    const int range_to_frame_height    = frame_height - getImage()->h - frame_boundary;
    int a = myrandint(range_from,range_to_frame_width);
    int b = myrandint(range_from,range_to_frame_height);
    this->rect.x = a; 
    this->rect.y = b; 
}

void wolf::move() {
    if (rect.x - targetX <= 0)
    {
        rect.x = rect.x + 1;
    }
    else
    {
        rect.x = rect.x - 1;
    }
    if (rect.y - targetY <= 0)
    {
        rect.y = rect.y + 1;
    }
    else
    {
        rect.y = rect.y - 1;
    }

}

void wolf::setTargetX(int x)
{
    this->targetX = x;
}

void wolf::setTargetY(int y)
{
    this->targetY = y;
}


/*
std::shared_ptr<sheep> wolf::findTarget() {
    for (std::shared_ptr<animal> &ani : ground_->getAnimals()) {
        std::cout<<typeid(ani).name();
        }
    for (std::shared_ptr<animal> &ani : ground_->getAnimals()) {
        if (typeid(ani).name())
    }
}
*/





namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

SDL_Surface* load_surface_for(const std::string& path,
                              SDL_Surface* window_surface_ptr) {
  
  return window_surface_ptr;
  // Helper function to load a png for a specific surface
  // See SDL_ConvertSurface 

  // i don't understand why use SDL_ConvertSurface nor the use of this function
}


} // namespace
