// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

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

    
    //animals = ground_->getVect();

    
    //setWolfesTarget();
}

void application::addBabies(){
    for (std::shared_ptr<animal> &oneAnimal : ground_->getVect())
    {
        if (ground_->getVect().size()>=maxAnimals)
        {
            return;
        }
        if (oneAnimal->haveProperty("pregnant"))
        {
            oneAnimal->removeProperty("pregnant");
            
            ground_->add_animal(std::make_shared<sheep>(window_surface_ptr_)); // if more animal can reproduce add a condition
            ground_->getVect().back()->setX(oneAnimal->getX());
            ground_->getVect().back()->setY(oneAnimal->getY());
            ground_->getVect().back()->setRandTarget();

        }
    }
} 

void application::remove_dead() {
    for (size_t i = 0; i < ground_->getVect().size();i++) {
        if (ground_->getVect().at(i)->haveProperty("dead")){
            ground_->remove_animal(i);
        }
    }
}


int application::loop(unsigned period) {
    SDL_Rect windowsRect = SDL_Rect{ 0,0,frame_width, frame_height };
    bool quit = false;
    
    while (!quit && (SDL_GetTicks() <= period * 1000)) { 
        addBabies();
        remove_dead();
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







interacting_object::~interacting_object() {

}
void interacting_object::interact(std::shared_ptr<interacting_object> other) {
    return;
}
void interacting_object::printProps(){
    for (std::string prop : props)
    {
        std::cout<<prop;
        std::cout << "\n";
    }
    std::cout << "\n";
}

rendered_object::rendered_object(SDL_Surface* window_surface_ptr, const std::string& file_path) {

    image_ptr_ = IMG_Load(file_path.c_str());
    rect.x = 0; //rand() % with
    rect.y = 0;
    rect.w = image_ptr_->w;
    rect.h = image_ptr_->h;
    window_surface_ptr_ = window_surface_ptr;
    this->rect.h = this->rect.h/2;
    this->rect.w = this->rect.w/2;
}

int rendered_object::getX() {
    return this->x;
}

int rendered_object::getY() {
    return this->y;
}

void rendered_object::setX(int x) {
    this->x = x;
}

void rendered_object::setY(int y) {
    this->y = y;
}

rendered_object::~rendered_object()
{

}
double rendered_object::distanceTo(std::shared_ptr<rendered_object> other) {
    double distanceX = abs(this->x - other->x);
    double distanceY = abs(this->y - other->y);

    return sqrt(distanceX * distanceX + distanceY * distanceY);
}


//moving object
moving_object::moving_object(SDL_Surface* window_surface_ptr, const std::string& file_path) : rendered_object(window_surface_ptr,file_path) {
    this->speed = 1;
}



int moving_object::myrandint(int lower, int upper) {
    
    //for random : https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range
    
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(lower, upper);
    return distr(generator);
}

moving_object::~moving_object()
{

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

  // i don't understand why use SDL_ConvertSurface nor the use of this function
}


} // namespace
