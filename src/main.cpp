#include "main.h"

int main(int argc, char *argv[])
{

	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
	SDL_Window* win = SDL_CreateWindow("WITHER",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					1000, 1000, 0);

	//triggers the program that controls your
	//graphics hardware adn sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	
	//creates a renderer to render images
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
	
	//creates a surface to load an image into the main memory
	SDL_Surface* surface;

	//TODO which image?, please provide a path for your image
	surface = IMG_Load("/home/scott/projects/wither/resources/square.jpg");

	//loads image to our graphics hardware memory
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

	//clears main-memory
	SDL_FreeSurface(surface);

	//let us control our image position
	//so that we can move it with our keyboard
	SDL_Rect dest;

	//connects our texture with des to control position
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

	//adjust height and with of our image box
	dest.w /= 6;
	dest.h /= 6;

	//set inital x-postion of object
	dest.x = (1000 - dest.w) / 2;

	//set inital y-position of object
	dest.y = (1000 - dest.h) / 2;
	
	//control animation loop
	int close = 0;

	//speed of box
	int speed = 300;

	//animation loop
	while (!close){
		SDL_Event event;
			
		//Event managment
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT://close button
					close = 1;
					break;
				case SDL_KEYDOWN://keyboard API for keypress
					switch(event.key.keysym.scancode){
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							dest.y -= speed / 30;
							break;
						case SDL_SCANCODE_A:	
						case SDL_SCANCODE_LEFT:	
							dest.x -= speed / 30;
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							dest.y += speed / 30;
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							dest.x += speed / 30;
							break;
						default:
							break;
					}
					
			}
		}

		//right boundry
		if (dest.x + dest.w > 1000){
			dest.x = 1000 - dest.w;
		}
		
		//left boundry	
		if (dest.x < 0){
			dest.x = 0;
		}

		//bottom boudary
		if (dest.y + dest.h > 1000){
			dest.y = 1000 - dest.h;
		}

		//top boudary
		if (dest.y < 0){
			dest.y = 0;
		}

		//clears the screen
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, tex, NULL, &dest);

		//trigger the double buffers
		//for multiple rendering
		SDL_RenderPresent(rend);
	
		//calculates to 60 fps
		SDL_Delay(1000/60);	
	}
	
	// destroy texture
	SDL_DestroyTexture(tex);
	
	// destoy renderer
	SDL_DestroyRenderer(rend);

	//destroy window
	SDL_DestroyWindow(win);

	//close SDL
	SDL_Quit();
 
	return 0;
}
