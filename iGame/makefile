# this will create library

inc = /usr/local/include
lib = /usr/local/lib
options = -pthread

sprite.o: bitmap.o
	g++ -c sprite.cpp -o sprite.o -I$(inc) -L$(lib) $(options)
bitmap.o: bitmapmask.o
	g++ -c bitmap.cpp -o bitmap.o -I$(inc) -L$(lib) $(options)
bitmapmask.o: ytable.o
	g++ -c bitmapmask.cpp -o bitmapmask.o -I$(inc) $(options)
ytable.o: banksfx.o
	g++ -c ytable.cpp -o ytable.o -I$(inc) -L$(lib) $(options)
banksfx.o: eventevt.o
	g++ -c banksfx.cpp -o banksfx.o -I$(inc) -L$(lib) $(options)
eventevt.o: pinch.o
	g++ -c eventevt.cpp -o eventevt.o -I$(inc) -L$(lib) $(options)
pinch.o : event.o
	g++ -c pinch.cpp -o pinch.o -I$(inc) -L$(lib) $(options)
event.o : 
	g++ -c event.cpp -o event.o -I$(inc) -L$(lib) $(options)
