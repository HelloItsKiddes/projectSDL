#include "sheep.h"



//sheeep ------------------
sheep::sheep(SDL_Surface *window_surface_ptr) : animal("./media/sheep.png", window_surface_ptr) {
    const int range_from  = 0;
    const int range_to_frame_width    = frame_width - getImage()->w - frame_boundary;
    const int range_to_frame_height    = frame_height - getImage()->h - frame_boundary;
    int a = myrandint(range_from,range_to_frame_width);
    int b = myrandint(range_from,range_to_frame_height);
    this->addProperty("prey");
    this->addProperty("sheep");
    int sex = myrandint(0,2);
    if (sex==0) {
        this->addProperty("female");
        last_offspring = SDL_GetTicks();
    }
    else {
        this->addProperty("male");
    }
    this->x = a; 
    this->y = b;
    setRandTarget();
}
/*
sheep::sheep(SDL_Surface *window_surface_ptr,int x,int y) : sheep(window_surface_ptr) {
    this->x = x; 
    this->y = y;
}
*/

void sheep::move() {
    if (SDL_GetTicks() - lastBoost > boostTime) {
        speed = baseSpeedSheep;
        this->removeProperty("fleeing");
    }
    if ( abs(target.x - this->getX()) + abs(target.y - this->getY()) < 4)
    {
        setRandTarget();
        if (this->haveProperty("fleeing")) {
            fleeFromTarget();
            
        }

        moveToTarget();
    }
    else{
        moveToTarget();
    }
}

void sheep::setTarget(int nx, int ny)
{
    this->target.x = nx;
    this->target.y = ny;
}


sheep::~sheep()
{

}

void sheep::interact(std::shared_ptr<interacting_object> other) {
    if (other->haveProperty("sheep") && this->haveProperty("female") && other->haveProperty("male"))
    {
        
        if (SDL_GetTicks() - this->last_offspring > ReproduceTime_)
        {   
            this->addProperty("pregnant");
            this->last_offspring = SDL_GetTicks();
        }
    }
}

void sheep::fleeFromTarget() {
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

void sheep::interactLong(std::shared_ptr<interacting_object> other) {
    if (other->haveProperty("hunter") && (SDL_GetTicks() - lastBoost > boostTime) )
    {
        fleeFromX = other->getX();
        fleeFromY = other->getY();
        if ( !(this->haveProperty("fleeing")) ) {
            this->addProperty("fleeing");
            this->speed = this->speed * 1.4;

            

            this->lastBoost = SDL_GetTicks();
            fleeFromTarget();
        }

    }
}
