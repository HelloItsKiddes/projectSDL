#include "sheperd.h"
sheperd::sheperd(SDL_Surface *window_surface_ptr) : playable_character("./media/sheperd.png", window_surface_ptr) {
    //load_surface_for(file_path.c_str(), window_surface_ptr);
    //this->ground_ = ground_;
    //this->app = app;
    const int range_from  = 0;
    const int range_to_frame_width    = frame_width - getImage()->w - frame_boundary;
    const int range_to_frame_height    = frame_height - getImage()->h - frame_boundary;
    int a = myrandint(range_from,range_to_frame_width);
    int b = myrandint(range_from,range_to_frame_height);
    this->x = a; 
    this->y = b; 
    this->addProperty("sheperd");
    

};

sheperd::~sheperd() {
}

void sheperd::setUp(int x)
{
    this->up = x;
}

void sheperd::setDown(int x)
{
    this->down = x;
}
void sheperd::setLeft(int x)
{
    this->left = x;
}
void sheperd::setRight(int x)
{
    this->right = x;
}


void sheperd::move() {
    
    int nx = 0;
    int ny = 0;

    if (left) {
        nx = this->x - 1;
        if (nx <= 0 + frame_boundary) {
            nx = 0 + frame_boundary;
        }
        this->x = nx;
    }

    if (up == 1){
        
        ny = this->y - 1;
        if (ny <= 0 + frame_boundary) {
            ny = 0 + frame_boundary;
        }
        this->y = ny;
    }
    if (right == 1) {
        
        int nx = this->x + 1;
        if (nx >= frame_height - this->rect.h - frame_boundary) {
            nx = frame_height - this->rect.h - frame_boundary;
        }
        this->x = nx;
    }
    if (down == 1) {
        
        int ny = this->y + 1;
        if (ny >= frame_width - this->rect.w - frame_boundary) {
            ny = frame_width - this->rect.w - frame_boundary;
        }
        this->y = ny;
    }

    
    /*
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_w:
                        tempx = -1;
                        break;
                    case SDLK_RIGHT:
                        tempx =  1;
                        break;
                    case SDLK_UP:
                        tempy = -1;
                        break;
                    case SDLK_DOWN:
                        tempy =  1;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        if( tempx < 0 )
                            tempx = 0;
                        break;
                    case SDLK_RIGHT:
                        if( tempx > 0 )
                            tempx = 0;
                        break;
                    case SDLK_UP:
                        if( tempy < 0 )
                            tempy = 0;
                        break;
                    case SDLK_DOWN:
                        if( tempy > 0 )
                            tempy = 0;
                        break;
                    default:
                        break;
                }
                break;
            
            default:
                break;
        }
    }
    */
}