#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUITKEY SDLK_ESCAPE
#define WIDTH 		800
#define HIGHT 		800
#define BLOCKSIZE 	4
#define FELDH 		HIGHT/BLOCKSIZE
#define FELDW 		WIDTH/BLOCKSIZE

#define DEAD 		0
#define LIVE 		255

//global vars
int quit=0;

//SDL Declaration
int errorCount=0 ;
SDL_Window* screen = NULL;
SDL_Renderer* renderer;
SDL_Event event;
SDL_Rect rect, source, destination, dst;

//Declarations

unsigned char welt[FELDH+1][FELDW+1] = {0};
unsigned char buffer[FELDH+1][FELDW+1] = {0} ;

unsigned char getWelt (int x,int y)
{
	if (x==-1) x=FELDW ;
	if (y==-1) y=FELDH ;
	return (welt[x][y]);
}

void putWelt (int x, int y, unsigned char value)
{
	if (x==-1) x=FELDW ;
	if (y==-1) y=FELDH ;
	welt[x][y]=value ;
}

unsigned char getBuf (int x,int y)
{
	if (x==-1) x=FELDW ;
	if (y==-1) y=FELDH ;
	return (buffer[x][y]);
}

void putBuf (int x, int y, unsigned char value)
{
	if (x==-1) x=FELDW ;
	if (y==-1) y=FELDH ;
	buffer[x][y]=value ;
}

void initFeld () {
	int i,j ;
	
	for (i=0 ; i < FELDW+1 ; i++ ) 
	{
		for ( j=0 ; j < FELDH+1 ; j++ ) 
		{
			putWelt(i,j, (rand() % 2)*255 ) ;
		}
	}
}

void copyBuffer() {
	int i,j ;
	
	for (i=0 ; i < FELDW+1 ; i++ ) 
	{
		for ( j=0 ; j < FELDH+1 ; j++ ) 
		{
			welt[i][j]=buffer[i][j];
		}
	}
}

void check( int x, int y ) {
	
	int lebend=0;
	
	//check Nordost
	if ( getWelt(x-1,y-1) == LIVE ) { lebend++ ; }
	//check Nord
	if ( getWelt(x  ,y-1) == LIVE ) { lebend++ ; }
	//check Nordwest
	if ( getWelt(x+1,y-1) == LIVE ) { lebend++ ; }
	//check Ost
	if ( getWelt(x-1,y  ) == LIVE ) { lebend++ ; }
	//check West
	if ( getWelt(x+1,y  ) == LIVE ) { lebend++ ; }
	//check Südost
	if ( getWelt(x-1,y+1) == LIVE ) { lebend++ ; }
	//check Süd
	if ( getWelt(x  ,y+1) == LIVE ) { lebend++ ; }
	//check Südwest
	if ( getWelt(x+1,y+1) == LIVE ) { lebend++ ; }
	
	//Logik
	if ( (lebend<2) || (lebend>3) ) putBuf(x,y,DEAD) ;
	if ( lebend==3 ) putBuf(x,y, LIVE) ;
	if ( lebend==2 ) putBuf(x,y, getWelt(x,y) );
}

void nextGeneration (void)
{
	int x,y ;
	for (x=0 ; x<FELDW ; x++)
	{
		for (y=0 ; y<FELDH ; y++)
		{
			check(x,y);
		}
	}
	copyBuffer();
}

//SDL Stuff
void LogError(char* msg) {
	errorCount++;
	printf( msg," %d",errorCount );
	printf("SDL Error: %s\n", SDL_GetError() );
}

void InitSetup() {
	srand((int)time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WIDTH, HIGHT, SDL_WINDOW_SHOWN, &screen, &renderer);
	if (!screen) 
	{
		LogError("InitSetup failed to create window");
	}
	SDL_SetWindowTitle( screen,"Game of life" );
}

void ExitClean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	SDL_Quit();
}

void drawFeld( void ) {

	int i,j,r,g,b ;
	unsigned char s;
	
	for (i=0 ; i < FELDW ; i++ ) {
		for ( j=0 ; j < FELDH ; j++ ) {
			s=getWelt(i,j);
	
			switch (s) {
				case 0	: r=50 	; g=0   ; b=0   ; break ;
				case 255: r=189	; g=255 ; b=255	; break ;
			}
			rect.y=( j * BLOCKSIZE ) ; 
			rect.x=( i * BLOCKSIZE ) ; 
			rect.w= BLOCKSIZE-1 ;
			rect.h= BLOCKSIZE-1 ;
			SDL_SetRenderDrawColor(renderer,r,g,b,255);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	SDL_RenderPresent(renderer);
}

int main( void ){
	int quit=0;
	int ticks=0 ;

	initFeld();
	InitSetup();
	
	while(quit==0)
	{
		drawFeld();
		nextGeneration();
	}

	ExitClean();
	return (0);
}

int pressed ( void ) {
	int k=0 ;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_LEFT:
						k=1 ;
					break;
					case SDLK_RIGHT:
						k=2 ;
					break;
					case SDLK_a:
						k=4 ;
					break;
					case SDLK_s:
						k=8 ;
					break;
					case SDLK_DOWN:
						k=16 ;
					break;
					default:
						k=0 ;
					break;
				}
			break;
				
			case SDL_KEYUP:  
				switch(event.key.keysym.sym){
					case SDLK_LEFT:
						k=0 ;
					break;
					case SDLK_RIGHT:
						k=0 ;
					break;
					case SDLK_a:
						k=0 ;
					break;
					case SDLK_s:
						k=0 ;
					break;
					case SDLK_DOWN:
						k=0 ;
					default:
					break;
				}
			break;
				
			case SDL_QUIT:
				quit = 1;
			break;
				
			default:
			break;	
		}
	}
	return (k) ;
}
