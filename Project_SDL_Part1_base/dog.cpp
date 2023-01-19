
#include "dog.h"
#include <cmath>

dog::dog(SDL_Surface *window_surface_ptr, std::shared_ptr<sheperd> sheperd) : animal("./media/dog.png", window_surface_ptr) {

    this->addProperty("dog");
    this->sheperd_ = sheperd;
    
    this->rangeX = 0;
    this->rangeY = 0 - int(rangeDog);

    this->incr = 1;

    this->x = this->sheperd_->getX() + rangeX;
    if (this->x >= frame_width - frame_boundary - this->rect.w) {
        this->x = frame_width - frame_boundary - this->rect.w;
    }
    else if (this->x <= 0 + frame_boundary){
        this->x =  0 + frame_boundary;
    }

    this->y = this->sheperd_->getY() + rangeY;

    if (this->y >= frame_height - frame_boundary - this->rect.h) {
        this->y = frame_height - frame_boundary - this->rect.h;
    }
    else if (this->y <= 0 + frame_boundary){
        this->y =  0 + frame_boundary;
    }
    
}


dog::~dog() {

}

void dog::interact(std::shared_ptr<interacting_object> other){

}

void dog::interactLong(std::shared_ptr<interacting_object> other) {
}
void dog::setSheperd(std::shared_ptr<sheperd> shep) {
    this->sheperd_ = shep;
}




void dog::move() {

    
    angle = angle + 0.02*incr;
    this->x = this->sheperd_->getX() + (int(rangeDog)) * cos(angle);

    if (this->x >= frame_width - frame_boundary - this->rect.w) {
        this->x = frame_width - frame_boundary - this->rect.w;
    }
    else if (this->x <= 0 + frame_boundary){
        this->x =  0 + frame_boundary;
    }

    this->y = this->sheperd_->getY() + (int(rangeDog)) * sin (angle);
    if (this->y >= frame_height - frame_boundary - this->rect.h) {
        this->y = frame_height - frame_boundary - this->rect.h;
    }
    else if (this->y <= 0 + frame_boundary){
        this->y =  0 + frame_boundary;
    }
}

