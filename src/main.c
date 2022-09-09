
#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <SDL.h>

#define NB_RECT 25

#define RED   {255, 0, 0}
#define GREEN {0, 255, 0}
#define BLUE  {0, 0, 255}

SDL_Color rgba[3]             = {RED, GREEN, BLUE};

void refresh(SDL_Renderer * renderer, SDL_Rect rect[], SDL_Event event, SDL_Color color[]){

   SDL_bool quit = SDL_FALSE;
   int x;

    while(!quit){
        SDL_WaitEvent(&event);

        if(event.type == SDL_QUIT){
            quit = SDL_TRUE;

        }else if(event.type == SDL_MOUSEBUTTONUP
         && (event.button.button == SDL_BUTTON_LEFT)){
            SDL_Point point = {event.button.x, event.button.y};

            for(int i = 0; i < NB_RECT; i++){
                if(SDL_PointInRect(&point, &rect[i])){
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                    SDL_RenderFillRect(renderer, &rect[i]);
                    break;
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
}


void printRectOnScreen(SDL_Renderer * renderer, SDL_Rect rect[], SDL_Color color[]){
    int i = 0;
    int r, g, b;
    int def_y = 0;
    int def_x = 0;

    for(i = 0; i < NB_RECT; i++){
        rect[i].w = rect[i].h = 60;
        rect[i].x = def_x;
        def_x += rect[i].w;
        if(def_x > 240){
            def_y += rect[i].h;
            rect[i].y = def_y;
            def_x = 0;
        }else{
            rect[i].y = def_y;
        }
        SDL_Color  c = rgba[rand() % 3];
        color[i] = c;
        SDL_SetRenderDrawColor(renderer, color[i].r, color[i].g, color[i].b, 255);
        SDL_RenderFillRect(renderer, &rect[i]);
    }
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]){

    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Event event;

    if(0 != SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr, "Error occur on SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Flood It", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 240, 240, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if( 0 != SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255)){
        fprintf(stderr, "Error occur on SDL_RenderDrawColor : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Rect rect[NB_RECT];
    SDL_Color color[NB_RECT];

    printRectOnScreen(renderer, rect, color);

    refresh(renderer, rect, event, color);

    if(renderer != NULL){
        SDL_DestroyRenderer(renderer);
    }
    SDL_Quit();
    return 0;
}
