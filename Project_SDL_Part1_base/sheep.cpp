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
    if ( abs(target.x - this->getX()) + abs(target.y - this->getY()) < 4)
    {
        setRandTarget();

        moveToTarget();
    }
    else{
        moveToTarget();
    }
}

void sheep::setTargetX(int x)
{
    return;
}

void sheep::setTargetY(int y)
{
    return;
}


sheep::~sheep()
{

}

void sheep::interact(std::shared_ptr<interacting_object> other) {
    if (other->haveProperty("sheep") && this->haveProperty("female") && other->haveProperty("male"))
    {
        
        if (SDL_GetTicks() - this->last_offspring > ReproduceTime_)
        {   
            std::cout << "one prgnant";
            this->addProperty("pregnant");
            this->last_offspring = SDL_GetTicks();
        }
    }
    
}

