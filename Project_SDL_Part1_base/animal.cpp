#include "animal.h"



//animal part ------
animal::animal(const std::string& file_path, SDL_Surface *window_surface_ptr) : moving_object(window_surface_ptr, file_path) {
    //load_surface_for(file_path.c_str(), window_surface_ptr);
    //this->ground_ = ground_;
    //this->app = app;
    

};



animal::~animal() {
    SDL_FreeSurface(image_ptr_);
};

void animal::draw() {
    this->rect.x = this->x;
    this->rect.y = this->y;
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &rect);
};

void animal::move() {
    return;
}

void animal::setRandTarget() {
    const int range_from  = 0;
    const int range_to_frame_width    = frame_width - getImage()->w - frame_boundary;
    const int range_to_frame_height    = frame_height - getImage()->h - frame_boundary;
    int x = myrandint(range_from, range_to_frame_width);
    int y = myrandint(range_from, range_to_frame_height);
    this->target.x = x;
    this->target.y = y;
    calculate_steps();
}

void animal::calculate_steps() {
    
    double distanceX = abs(this->x - this->target.x);
    double distanceY = abs(this->y - this->target.y);

    double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

    int numStep = distance / speed;
    if (numStep == 0) {
        numStep = 1;
    }
    this->stepX = distanceX / numStep;
    this->stepY = distanceY / numStep;

    if (this->x - this->target.x > 0)
    {
        this->stepX  = this->stepX * -1;
    }
    if (this->y - this->target.y > 0)
    {
        this->stepY  = this->stepY * -1;
    }
}



void animal::moveToTarget() {
    
    this->x = this->x + this->stepX;
    this->y = this->y + this->stepY;
}

