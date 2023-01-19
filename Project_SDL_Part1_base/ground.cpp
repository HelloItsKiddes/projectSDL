
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

void ground::addSheperd(SDL_Surface * window_surface_ptr_) {
    this->sheperd_ = std::make_shared<sheperd>(window_surface_ptr_);
}

void ground::addDog(SDL_Surface * window_surface_ptr_)
{
    animalsVect_.push_back(std::make_shared<dog>(window_surface_ptr_,this->sheperd_));
}

void ground::add_animal(std::shared_ptr<animal> newAnimal) {
    animalsVect_.push_back(newAnimal);
}

void ground::remove_animal(int animalToRemove) {
    animalsVect_.erase(animalsVect_.begin() + animalToRemove);
}


std::shared_ptr<sheperd> ground::getSheperd() {
    return sheperd_;
}




void ground::make_interact() {
    for (std::shared_ptr<animal> &oneAnimal : animalsVect_)
    {
        for (std::shared_ptr<animal> &anotherAnimal : animalsVect_)
        {
            if (oneAnimal->distanceTo(anotherAnimal)<=shortInteract_range) {
                oneAnimal->interact(anotherAnimal);
            }
            if (oneAnimal->distanceTo(anotherAnimal)<=longInteract_range) {
                oneAnimal->interactLong(anotherAnimal);
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
    sheperd_->move();
    sheperd_->draw();
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
                        oneAnimal->setTarget(anotherAnimal->getX(),anotherAnimal->getY());
                    }
                }
            }
        }
    }
}



