
#include "ground.h"

#include <float.h> 




//ground part -------
ground::ground(SDL_Surface* window_surface_ptr) {
    window_surface_ptr_ = window_surface_ptr;
    animalsVect_ = std::vector<std::shared_ptr<animal>>();
}

ground::~ground()
{
  window_surface_ptr_ = NULL;

}

void ground::add_animal(std::shared_ptr<animal> newAnimal) {
    animalsVect_.push_back(newAnimal);
}

void ground::remove_animal(int animalToRemove) {
    animalsVect_.erase(animalsVect_.begin() + animalToRemove);
}







void ground::make_interact() {
    for (std::shared_ptr<animal> &oneAnimal : animalsVect_)
    {
        for (std::shared_ptr<animal> &anotherAnimal : animalsVect_)
        {
            if (oneAnimal->distanceTo(anotherAnimal)<=interact_range) {
                oneAnimal->interact(anotherAnimal);
            }
        }
    }
}

void ground::update(SDL_Surface *window_surface_ptr_) {
    for (std::shared_ptr<animal> &oneAnimal : animalsVect_)
    {
        setTargets();
        make_interact();
        
        oneAnimal->draw();
        oneAnimal->move();

    }
}

void ground::setTargets() {
    for (std::shared_ptr<animal> &oneAnimal : animalsVect_)
    {
        if(oneAnimal->haveProperty("hunter")) {
            double minimalDist = DBL_MAX;
            for (std::shared_ptr<animal> &anotherAnimal : animalsVect_)
            {   
                if(anotherAnimal->haveProperty("prey")) {
                    double dist = oneAnimal->distanceTo(anotherAnimal);
                    if (dist < minimalDist) {
                        minimalDist = dist;
                        if (anotherAnimal->getX() < 0)
                        {
                            std::cout<<anotherAnimal->getX();
                        }
                        oneAnimal->setTargetX(anotherAnimal->getX());
                        oneAnimal->setTargetY(anotherAnimal->getY());
                    }
                }
            }
        }
    }
}



