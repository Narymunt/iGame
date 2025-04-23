# this will create library

SDL_include = /Library/Frameworks/SDL.framework/Headers

sprite.o: bitmap.o
	g++ -c sprite.cpp -o sprite.o -I$(SDL_include) 

bitmap.o: bitmapmask.o
	g++ -c bitmap.cpp -o bitmap.o -I$(SDL_include)

bitmapmask.o: ytable.o
	g++ -c bitmapmask.cpp -o bitmapmask.o -I$(SDL_include)

ytable.o:
	g++ -c ytable.cpp -o ytable.o -I$(SDL_include)

