#include "wolf.h"



//wolf ------------------
wolf::wolf(SDL_Surface *window_surface_ptr) : animal("./media/wolf.png", window_surface_ptr) {
    const int range_from  = 0;
    const int range_to_frame_width    = frame_width - getImage()->w - frame_boundary;
    const int range_to_frame_height    = frame_height - getImage()->h - frame_boundary;
    int a = myrandint(range_from,range_to_frame_width);
    int b = myrandint(range_from,range_to_frame_height);
    this->x = a; 
    this->y = b; 
    this->addProperty("hunter");

    
}

void wolf::move() {
    if (SDL_GetTicks() - last_meal > dieFromHunger) {
        this->addProperty("dead");
    }
    calculate_steps();
    moveToTarget();

}

void wolf::setTargetX(int x)
{
    this->target.x = x;
}

void wolf::setTargetY(int y)
{
    this->target.y = y;
}

void wolf::interact(std::shared_ptr<interacting_object> other) {
    if (other->haveProperty("prey") && !other->haveProperty("dead"))
    {
        other->addProperty("dead");
        this->last_meal = SDL_GetTicks();
    }
}
wolf::~wolf() {

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
