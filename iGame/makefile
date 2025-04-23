# iGame main make

inc = /usr/local/include
lib = /usr/local/lib
link = -lSDL -lSDL_mixer
options = -pthread
iGame = /opt/prj/iGame
iGame_lib = $(iGame)/sprite.o \
$(iGame)/ytable.o \
$(iGame)/bitmap.o \
$(iGame)/bitmapmask.o \
$(iGame)/banksfx.o \
$(iGame)/eventevt.o \
$(iGame)/event.o \
$(iGame)/pinch.o \
$(iGame)/button_flat.o \
$(iGame)/xml_node.o

main.exe: $(iGame_lib)
	g++ -O2 main.cpp -o main $(iGame_lib) -I$(inc) -I$(iGame) $(link) $(options)
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
event.o : button_flat.o
	g++ -c event.cpp -o event.o -I$(inc) -L$(lib) $(options)
button_flat.o : xml_node.o
	g++ -c button_flat.cpp -o button_flat.o -I$(inc) -L$(lib) $(options)
xml_node.o : 
	g++ -c xml_node.cpp -o xml_node.o -I$(inc) -L$(lib) $(options)



