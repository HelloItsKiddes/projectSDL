#include "Project_SDL1.h"

#ifndef SHERPERD_H
#define SHERPERD_H

class sheperd : public playable_character {
    private :
        int left = 0;
        int right = 0;
        int up = 0;
        int down = 0;
    public:
        sheperd(SDL_Surface *window_surface_ptr);
        ~sheperd();
        void move() override;

        void setUp(int x);
        void setDown(int x);
        void setLeft(int x);
        void setRight(int x);

};

#endif