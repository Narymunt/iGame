libinc = /Library/Frameworks/SDL.framework/Headers \
/Library/Frameworks/SDL_mixer.framework/Headers

libdir = .

files = BankSFX.o \
BitmapMask.o \
YTable.o \
Bitmap.o \
Button.o \
XmlFile.o \
XmlNode.o \
ButtonFlat.o \
Event.o \
EventEVT.o \
EventSND.o \
Pinch.o \
SinTable.o

iGame.a : $(files)
	ar cr iGame.a $(files)

BankSFX.o:
	g++ -I $(libinc) -c BankSFX.cpp -o BankSFX.o

BitmapMask.o:
	g++ -I $(libinc) -c BitmapMask.cpp -o BitmapMask.o

YTable.o:
	g++ -I $(libinc) -c YTable.cpp -o YTable.o

Bitmap.o:
	g++ -I $(libinc) -c Bitmap.cpp -o Bitmap.o

Button.o:
	g++ -I $(libinc) -c Button.cpp -o Button.o

XmlFile.o:
	g++ -I $(libinc) -c XmlFile.cpp -o XmlFile.o

XmlNode.o:
	g++ -I $(libinc) -c XmlNode.cpp -o XmlNode.o

ButtonFlat.o:
	g++ -I $(libinc) -c ButtonFlat.cpp -o ButtonFlat.o

Event.o:
	g++ -I $(libinc) -c Event.cpp -o Event.o

EventEVT.o:
	g++ -I $(libinc) -c EventEVT.cpp -o EventEVT.o

EventSND.o:
	g++ -I $(libinc) -c EventSND.cpp -o EventSND.o

Pinch.o:
	g++ -I $(libinc) -c Pinch.cpp -o Pinch.o

SinTable.o:
	g++ -I $(libinc) -c SinTable.cpp -o SinTable.o

