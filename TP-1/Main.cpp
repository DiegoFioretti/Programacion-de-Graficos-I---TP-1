#include <iostream>
#include <SDL.h>
using namespace std;

// VARIABLES THAT ARE CUSTOMIZABLE
int windowWidth = 640;
int windowHeight = 480;
int squareWidth = 100;
int squareHeight = 100;
int squareFakeSpeed = 5;

SDL_Window *window;
SDL_Renderer *render;
SDL_Rect square;

SDL_Texture* squareTexture;

bool CreateWindow() {
	window = SDL_CreateWindow("Hello World!", 100, 100, windowWidth, windowHeight, 0);
	if (window == nullptr)
	{
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}
	return 0;
}
bool CreateRenderer() {
	render = SDL_CreateRenderer(window, -1, 0);
	if (render == nullptr)
	{
		SDL_DestroyWindow(window);
		cout << "SDL_CreateRenderer Error: " << SDL_GetError << endl;
		SDL_Quit();
		return 1;
	}
	return 0;
}
void SetupRenderer() {
	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize(render, windowWidth, windowHeight);

	// Set color of renderer to red
	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
}
SDL_Texture* LoadTexture(const string &str){
	// Load image as SDL_Surface
	SDL_Surface* surface = SDL_LoadBMP(str.c_str());

	// SDL_Surface is just the raw pixels
	// Convert it to a hardware-optimzed texture so we can render it
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);

	// Don't need the orignal texture, release the memory
	SDL_FreeSurface(surface);

	return texture;
}
void Render() {
	// Clear the window and make it all green
	SDL_RenderClear(render);

	// Select the texture for the object
	SDL_RenderCopy(render, squareTexture, NULL, &square);

	// Render the changes above
	SDL_RenderPresent(render);
}
void RunGame() {
	SDL_Event event;
	bool gameRunning = true;
	while (gameRunning){
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				gameRunning = false;
			}
			else if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){
				case SDLK_RIGHT:
					if (square.x < windowWidth - squareWidth){
						square.x = square.x + squareFakeSpeed;
					}
					break;
				case SDLK_LEFT:
					if (square.x > 0){
						--square.x = square.x - squareFakeSpeed;
					}
					break;
				case SDLK_DOWN:
					if (square.y < windowHeight - squareHeight){
						++square.y = square.y + squareFakeSpeed;
					}
					break;
				case SDLK_UP:
					if (square.y > 0){
						--square.y = square.y - squareFakeSpeed;
					}
					break;
				default:
					break;
				}
			}
		}

		Render();

		SDL_Delay(16);

	}
}

int main(int, char**) {
	// START SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout << "SDL_Init Error:" << SDL_GetError() << endl;
		return 1;
	}

	// CREATE A WINDOW
	CreateWindow();
	
	// CREATE A RENDERER
	CreateRenderer();

	//SETUP THE RENDERER
	SetupRenderer();

	//SETUP MOVABLE OBJECT
	square.x = 20;
	square.y = 20;
	square.w = squareWidth;
	square.h = squareWidth;
	squareTexture = LoadTexture("alien.bmp");

	//START THE GAME LOOP
	RunGame();

	//FINISH THE PROGRAM
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}