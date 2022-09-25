#include <SDL2/SDL.h>
#include <iostream>

int GRID_CELL_SIZE = 27;
int GRID_WIDTH = 29;
int GRID_HEIGHT = 23;
const int SCREEN_WIDTH = ((GRID_WIDTH + 2) * GRID_CELL_SIZE);
const int SCREEN_HEIGHT = ((GRID_HEIGHT + 4) * GRID_CELL_SIZE);

SDL_Window *window = NULL;
SDL_Renderer *grenderer = NULL;

SDL_Rect temprect;

SDL_Color grid_background = {244, 164, 96, 255}; // Barely Black

bool init()
{
	bool flag = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL coud not initialize: %s\n", SDL_GetError());
		flag = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		window = SDL_CreateWindow("Mine It Out", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Problem createing window: %s", SDL_GetError());
			flag = false;
		}
		else
		{
			grenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (grenderer == NULL)
			{
				printf("Problem creating Renderer: %s\n", SDL_GetError());
				flag = false;
			}
			else
			{
				SDL_SetRenderDrawColor(grenderer, 255, 255, 255, 0xFF);
			}
		}
	}

	return flag;
}

void close()
{
	SDL_DestroyRenderer(grenderer);
	SDL_DestroyWindow(window);
	grenderer = NULL;
	window = NULL;
	SDL_Quit();
}
int a = 0;

class Block
{
public:
	void destroy()
	{
		isrendered = false;
		canmove = true;
	}
	void currentrect(int i, int j)
	{
		myblock = {i, j, bsize, bsize};
		SDL_SetRenderDrawColor(grenderer, 255, 255, 255, 255);
		SDL_RenderFillRect(grenderer, &myblock);
	}
	void render(int i, int j)
	{
		if (isrendered)
		{
			myblock = {i, j, bsize, bsize};
			SDL_SetRenderDrawColor(grenderer, 139, 69, 19, 255);
			SDL_RenderDrawRect(grenderer, &myblock);
			SDL_RenderFillRect(grenderer, &myblock);
		}
	}
	void rendercolor(int i, int j, Uint8 r, Uint8 g, Uint8 b)
	{
		if (isrendered)
		{
			myblock = {i, j, bsize, bsize};
			SDL_SetRenderDrawColor(grenderer, r, g, b, 255);
			SDL_RenderDrawRect(grenderer, &myblock);
			SDL_RenderFillRect(grenderer, &myblock);
		}
	}
	void boundrycheck(int *i, int *j)
	{
		if (*i < 0)
		{
			*i = 0;
		}
		else if (*j < 0)
		{
			*j = 0;
		}
		else if (*i > GRID_WIDTH - 1)
		{
			--(*i);
		}
		else if (*j > GRID_HEIGHT - 1)
		{
			--(*j);
		}
	}
	bool isrendered = true;
	bool canmove = false;

private:
	SDL_Rect myblock;
	int bsize = GRID_CELL_SIZE;
};

int main(int argc, char **argv)
{
	if (!init())
	{
		printf("\nInitialization failed\n");
		return 0;
	}

	bool quit = false;
	SDL_bool mouse_active = SDL_FALSE;
	SDL_bool mouse_hover = SDL_FALSE;
	SDL_Event event;
	int posX = 0, posY = 0;
	Block block[GRID_WIDTH][GRID_HEIGHT + 1];
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

			if (keyboard_state_array[SDL_SCANCODE_UP] && (keyboard_state_array[SDL_SCANCODE_SPACE]))
			{
				block[posX][posY - 1].destroy();
			}
			else if (keyboard_state_array[SDL_SCANCODE_DOWN] && (keyboard_state_array[SDL_SCANCODE_SPACE]))
			{
				block[posX][posY + 1].destroy();
			}

			else if (keyboard_state_array[SDL_SCANCODE_LEFT] && (keyboard_state_array[SDL_SCANCODE_SPACE]))
			{
				block[posX - 1][posY].destroy();
			}
			else if (keyboard_state_array[SDL_SCANCODE_RIGHT] && (keyboard_state_array[SDL_SCANCODE_SPACE]))
			{
				block[posX + 1][posY].destroy();
			}

			else
			{
				switch (event.type)
				{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_w:
					case SDLK_UP:
						if (posY == 1)
							posY--;
						else if (posY > 0)
						{
							if (block[posX][posY - 1].isrendered)
							{
								if (block[posX][posY - 1].canmove)
								{
										posY--;
								}
							}
							else if(posY >= 1)
							{
								if (!block[posX][posY - 1].isrendered)
								{
									if (block[posX][posY - 1].canmove)
										posY--;
								}
							}
						}
						block[posX][posY].boundrycheck(&posX, &posY);
						break;
					case SDLK_s:
					case SDLK_DOWN:
						if (posY == GRID_HEIGHT - 2)
							posY++;
						else if (posY < GRID_HEIGHT - 1)
						{
							if (block[posX][posY + 1].isrendered)
							{
								if (block[posX][posY + 1].canmove)
									posY++;
							}
							else if (posY >= 1)
							{
								if (!block[posX][posY + 1].isrendered)
								{
									if (block[posX][posY + 1].canmove)
										posY++;
								}
							}
						}
						block[posX][posY].boundrycheck(&posX, &posY);
						break;
					case SDLK_a:
					case SDLK_LEFT:
						if (posX == 1)
							posX--;
						else if (posX > 0)
						{
							if (block[posX - 1][posY].isrendered)
							{
								if (block[posX - 1][posY].canmove)
									posX--;
							}
							else
							{
								if (!block[posX-1][posY].isrendered)
								{
									if (block[posX-1][posY].canmove)
										posX--;
								}
							}
						}
						block[posX][posY].boundrycheck(&posX, &posY);
						break;
					case SDLK_d:
					case SDLK_RIGHT:
						if (posX == GRID_WIDTH - 2)
							posX++;
						else if (posX < GRID_WIDTH - 1)
						{
							if (block[posX + 1][posY].isrendered)
							{	
								if (block[posX + 1][posY].canmove)
										posX++;
							}
							else
							{
								if (!block[posX+1][posY].isrendered)
								{
									if (block[posX+1][posY].canmove)
										posX++;
								}
							}
						}
						block[posX][posY].boundrycheck(&posX, &posY);
						break;
					}
					break;
				case SDL_QUIT:
					quit = SDL_TRUE;
					break;
				}
			}
		}

		SDL_Rect viewport = {GRID_CELL_SIZE, GRID_CELL_SIZE * 3, SCREEN_WIDTH, (SCREEN_HEIGHT - GRID_CELL_SIZE * 3)};
		SDL_RenderSetViewport(grenderer, &viewport);

		// Draw grid background.
		SDL_SetRenderDrawColor(grenderer, grid_background.r, grid_background.g,
							   grid_background.b, grid_background.a);
		SDL_RenderClear(grenderer);

		for (int i = 0; i < GRID_WIDTH; i++)
		{
			for (int j = 0; j < GRID_HEIGHT; j++)
			{
				if (j == 0 || j == 1)
				{
					block[i][j].rendercolor(i * GRID_CELL_SIZE, j * GRID_CELL_SIZE, 173, 216, 230);
					block[i][j].canmove = true;
				}
				else if (j == 2)
				{
					block[i][j].rendercolor(i * GRID_CELL_SIZE, j * GRID_CELL_SIZE, 0, 128, 0);
				}
				else
				{
					block[i][j].render(i * GRID_CELL_SIZE, j * GRID_CELL_SIZE);
				}
			}
		}
		block[posX][posY].currentrect(posX * GRID_CELL_SIZE, posY * GRID_CELL_SIZE);
		SDL_RenderPresent(grenderer);
	}

	close();
	return 0;
}