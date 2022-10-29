#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 915
#define SCREEN_HIGHT 915
#define PADDING 50

/* color palettes */

/* #define DARK  0x0D5C63FF */
/* #define LIGHT 0x44A1A0FF */

#define DARK  0x786452FF
#define LIGHT 0xA5907EFF

#define RED   0xFF0000FF
#define GREEN 0x00A300FF

/* #define DARK 0x191308FF */
/* #define LIGHT 0x322A26FF */

int scc(int code){
		if(code<0){
      fprintf(stderr, "SDL error: %s\n", SDL_GetError());
			exit(1);
		}
    return code;
}
void* scp(void* ptr){
  if(ptr == NULL){
    fprintf(stderr, "SDL error: %s\n", SDL_GetError());
    exit(1);
  }
  return ptr;
}

void sdl_set_color_hex(SDL_Renderer* renderer, Uint32 color_hex){
  scc(SDL_SetRenderDrawColor(renderer,
                             (color_hex >> (3*8)) & 0xFF,
                             (color_hex >> (2*8)) & 0xFF,
                             (color_hex >> (1*8)) & 0xFF,
                             (color_hex >> (0*8)) & 0xFF));
}

void highlight_sq(SDL_Renderer* renderer, int mouse_x, int mouse_y){
  int i=(mouse_x-PADDING)/100;
  int j=(mouse_y-PADDING)/100;
  SDL_Rect mrect;
  mrect.x=PADDING+100*i;
  mrect.y=PADDING+100*j;
  mrect.w=100;
  mrect.h=100;
  sdl_set_color_hex(renderer, GREEN);
  SDL_RenderFillRect(renderer, &mrect);
}

void draw_grid(SDL_Renderer* renderer, int nb_cells, int mouse_x, int mouse_y, int mouse_pressed){
  /* for(int i=0; i<=nb_cells; i++){ */
  /*   scc(SDL_RenderDrawLine(renderer, 5+100*i, 5, 5+100*i, nb_cells*100+5)); */

  /* } */
  /* for(int j=0; j<=nb_cells; j++){ */
  /*   scc(SDL_RenderDrawLine(renderer, 5, 5+100*j, nb_cells*100+5, 5+100*j)); */
  /* } */
  for(int i=0; i<nb_cells; i++){
    for(int j=0; j<nb_cells; j++){
      SDL_Rect myrect;
      myrect.x=PADDING+100*i;
      myrect.y=PADDING+100*j;
      myrect.w=100;
      myrect.h=100;
      if((i+j)%2){
        sdl_set_color_hex(renderer, DARK);
      }
      else{
        sdl_set_color_hex(renderer, LIGHT);
      }
      SDL_RenderFillRect(renderer, &myrect);
    }
  }
  if(mouse_pressed) highlight_sq(renderer, mouse_x, mouse_y);
}

int main(int argc, char* argv[]){

  scc(SDL_Init(SDL_INIT_EVERYTHING));
  SDL_Window* window = scp(SDL_CreateWindow("First Window", 100, 100, SCREEN_WIDTH, SCREEN_HIGHT, SDL_WINDOW_RESIZABLE));
	SDL_Renderer* renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
  int mouse_x;
  int mouse_y;
  int mouse_pressed=0;

	int quit=0;
	while(!quit){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
      case SDL_MOUSEBUTTONDOWN:{
        SDL_GetMouseState(&mouse_x, &mouse_y);
        mouse_pressed=1;
        /* printf("mouse coord: %i,%i\n", mouse_x, mouse_y); */
      } break;
			case SDL_QUIT:{
		     		quit=1;
			} break;
			}
		}
    scc(SDL_SetRenderDrawColor(renderer, 18, 18, 18, 255));
    scc(SDL_RenderClear(renderer));
    draw_grid(renderer, 8, mouse_x, mouse_y, mouse_pressed);
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	return 0;
}
