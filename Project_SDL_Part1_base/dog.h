#include "Project_SDL1.h"
#ifndef DOG_H
#define DOG_H

// Insert here:
// class sheep, derived from animal
class dog : public animal {
    private:
        std::shared_ptr<sheperd> sheperd_;
        double rangeX;
        double rangeY;

        int incr;

        double angle = 0;

    public:
        dog(SDL_Surface *window_surface_ptr, std::shared_ptr<sheperd> sheperd);
        //sheep::sheep(SDL_Surface *window_surface_ptr,int x,int y) ;
        virtual ~dog();
        void move() override;

        void setSheperd(std::shared_ptr<sheperd> shep);
        void interact(std::shared_ptr<interacting_object> other) override;

        void interactLong(std::shared_ptr<interacting_object> other) override;
};

#endif 
