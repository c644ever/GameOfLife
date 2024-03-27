#include <iostream> //import std;
#include <ctime>
#include <cstdlib>

#define XSIZE 32
#define YSIZE 32

class World 
{
	public:
	World (void)
	{
		std::srand((unsigned)std::time(0));
	}
	 
	bool get( int x, int y) 
	{
		if (x<0) x=XSIZE ;
		if (y<0) y=YSIZE ;
		//if (x>XSIZE) x=XSIZE;
		//if (y>YSIZE) x=YSIZE;
		return ( cell[x+1][y+1] );
	}
	
	void set( int x, int y, bool value ) 
	{
		if (x<0) x=XSIZE ;
		if (y<0) y=YSIZE ;
		//if (x>XSIZE) x=XSIZE;
		//if (y>YSIZE) x=YSIZE;
		cell[x+1][y+1]=value;
	}
	
	void zero( void )
	{ 
		for (int x=0 ; x<=XSIZE; x++ )
			for (int y=0 ; y<=YSIZE; y++)
				cell[x][y]=(bool)(std::rand()%2);
	}
	
	void print(void)
	{
		std::cout<<"\033[;H\033[;2J";

		for (int y=0 ; y<YSIZE; y++ )
		{	std::cout<<"\n" ;
			for (int x=0 ; x<XSIZE; x++)
			{
				if (cell[x][y])
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
		if ( get(x-1,y-1) == true ) { lebend++ ; }
		//check Nord
		if ( get(x  ,y-1) == true ) { lebend++ ; }
		//check Nordwest
		if ( get(x+1,y-1) == true ) { lebend++ ; }
		//check Ost
		if ( get(x-1,y  ) == true ) { lebend++ ; }
		//check West
		if ( get(x+1,y  ) == true ) { lebend++ ; }
		//check Südost
		if ( get(x-1,y+1) == true ) { lebend++ ; }
		//check Süd
		if ( get(x  ,y+1) == true ) { lebend++ ; }
		//check Südwest
		if ( get(x+1,y+1) == true ) { lebend++ ; }

		return (lebend);	
			
	}

	// void load (std::string filename)
	// void save (std::string filename)
	
	private:
	bool cell [XSIZE+1][YSIZE+1] ;

} ;


int main (void)
{
	bool quit=false;
	bool buf[XSIZE][YSIZE];
		
	World welt;
	welt.zero();
	int x,y;
	int step=0;

	while (step<1000)
	{
		//next Generation
		for (x=0 ; x <XSIZE ; x++) {
			for (y=0 ; y<YSIZE ; y++) {
				switch (welt.nachbarn(x,y))
				{
					case 2: buf[x][y]=welt.get(x,y) ; break ;
					case 3: buf[x][y]=true ; break ;
					default: buf[x][y]=false ; break ;
				}
			}
		}

		for (x=0 ; x<XSIZE ; x++)
			for (y=0 ; y<YSIZE ; y++)
				welt.set(x,y,buf[x][y]);
			
		welt.print();

		//char a = std::getchar();
		
		step++;
		
	}
}
