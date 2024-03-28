/*
	Conways Game of Life

	very basic - terminal style

*/

#include <iostream>
#include <ctime>
#include <cstdlib>

#define XSIZE 32
#define YSIZE 32

#define DEAD	0
#define LIVE	255

class World 
{
	public:

	//Constructor only with init random numbers
	World (void)
	{
		std::srand( (unsigned) std::time(0) );
	}

	// Conway rules are default
	//    neigbors:        0      1     2     3     4     5     6     7     8
	bool ruledeath[9] = { true  ,true ,false,false,true ,true ,true ,true ,true  };
	bool rulebirth[9] = { false ,false,false,true ,false,false,false,false,false };

	//boot ruledeath[9] = { true  ,true ,false,false,true ,true ,true ,true ,true  };
	//bool rulebirth[9] = { false ,false,false,true ,false,false,false,false,false };

	int living=0 ;
	
	unsigned char get( int x, int y) 
	{
		if (x<0) x=XSIZE-1 ;	//wrap around
		if (y<0) y=YSIZE-1 ;
		if (x==XSIZE) x=0;
		if (y==YSIZE) y=0;
		
		return ( cell[x][y] );
	}
	
	void set( int x, int y, char value ) 
	{
		if (x<0) x=XSIZE-1 ;	//wrap around
		if (y<0) y=YSIZE-1 ;
		if (x==XSIZE) x=0;
		if (y==YSIZE) y=0;

		cell[x][y]=value;
	}
	
	void zero( void )
	{ 
		for (int x=0 ; x<XSIZE ; x++ )
			for (int y=0 ; y<YSIZE ; y++)
				cell[x][y]= (unsigned char) ( std::rand() % 2 );
	}
	
	void print(void)
	{
		std::cout<<"\033[;H\033[;2J";

		for (int y=1 ; y<YSIZE; y++ )
		{	
			std::cout<<"\n" ;
			for (int x=1 ; x<XSIZE; x++)
			{
				if (cell[x][y]==LIVE)
					std::cout<<"##";
				else 
					std::cout<<"..";
			}
		}

		std::cout<<"\n";
	}

	int nachbarn( int x, int y)
	{
		int lebend=0;

		//check Nordost
		if ( get(x-1,y-1) == LIVE ) { lebend++ ; }
		//check Nord
		if ( get(x  ,y-1) == LIVE ) { lebend++ ; }
		//check Nordwest
		if ( get(x+1,y-1) == LIVE ) { lebend++ ; }
		//check Ost
		if ( get(x-1,y  ) == LIVE ) { lebend++ ; }
		//check West
		if ( get(x+1,y  ) == LIVE ) { lebend++ ; }
		//check Südost
		if ( get(x-1,y+1) == LIVE ) { lebend++ ; }
		//check Süd
		if ( get(x  ,y+1) == LIVE ) { lebend++ ; }
		//check Südwest
		if ( get(x+1,y+1) == LIVE ) { lebend++ ; }

		return (lebend);	
			
	}

	// void load (std::string filename)
	// void save (std::string filename)
	
	private:

	unsigned char cell [XSIZE][YSIZE] ;

} ;



// main with logic (counting neigbors and decide)

int main (void)
{
	bool quit=false;

	unsigned char buf[XSIZE][YSIZE];	//buffer with new grid
		
	World welt;

	welt.zero(); // fill with random
	
	int x,y;
	int step=0;

	while (step<500)
	{
		int n=0;

		//next Generation
		for (x=0 ; x <XSIZE ; x++) 
		{
			for (y=0 ; y<YSIZE ; y++) 
			{
				n=welt.nachbarn(x,y);
				buf[x][y]=DEAD;

				if ( welt.ruledeath[n] )
					buf[x][y]=DEAD ;
				else if ( welt.rulebirth[n] )
					buf[x][y]=LIVE ;
				else
					buf[x][y]=welt.get(x,y);
			}
		}

		welt.living=0;

		for (x=0 ; x<XSIZE ; x++) 
		{
			for (y=0 ; y<YSIZE ; y++) 
			{
				welt.set(x,y,buf[x][y]);
				if (buf[x][y]==LIVE) welt.living++ ;
			}
		}

		welt.print();

		char a = std::getchar();
		
		step++;
		
	}
}
