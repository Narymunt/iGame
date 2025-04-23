iGame = /opt/prj/iGame
iGame_lib = $(iGame)/sprite.o \
$(iGame)/ytable.o \
$(iGame)/bitmap.o \
$(iGame)/bitmapmask.o \
$(iGame)/banksfx.o \
$(iGame)/eventevt.o \
$(iGame)/event.o


inc_dir = /usr/local/include
link = -lSDL -lSDL_mixer
options = -pthread

main.exe:
	g++ -O2 main.cpp -o main $(iGame_lib) -I$(inc_dir) -I$(iGame) $(link) $(options)
