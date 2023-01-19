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
    if (this->haveProperty("fleeing")) {
        fleeFromTarget();
        moveToTarget();
        this->removeProperty("fleeing");
    }
    else {
        calculate_steps();
        moveToTarget();
    }
   

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



void wolf::interactLong(std::shared_ptr<interacting_object> other) {
    if (other->haveProperty("dog") )
    {
        this->addProperty("fleeing");
        fleeFromX = other->getX();
        fleeFromY = other->getY();
    }
}

wolf::~wolf() {

}

void wolf::fleeFromTarget() {
    double targetx = this->getX() + (this->getX() - fleeFromX);
    double targety = this->getY() + (this->getY() - fleeFromY);
    if (targetx>=frame_width - frame_boundary - this->rect.w) {
        targetx = frame_width - frame_boundary - this->rect.w;
    }
    else if (targetx<= 0) {
        targetx = 1;
    }

    if (targety>=frame_height - frame_boundary - this->rect.h) {
        targety = frame_height - frame_boundary- this->rect.h;
    }
    else if (targety<=0) {
        targety = 1;
    }
    this->setTarget(targetx,targety);
    this->calculate_steps();
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
