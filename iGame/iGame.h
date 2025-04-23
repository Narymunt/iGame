#include <SDL/SDL.h>
#include <SDL_mixer/SDL_mixer.h>
#include "debug.h"		// obsluga bledow, zapisywanie do dziennika
#include "sprite.h"		// obsluga grafiki
#include "bitmap.h"		// statyczna bitmapa
#include "bitmapmask.h"		// maskowanie
#include "ytable.h"		// tablica z przeliczeniami, zamiast y*640+x jest ytable[y]+x
#include "sintable.h"		// tablice przeliczen
#include "filesys.h"		// pliki formatu .exedat
#include "eventsnd.h"		// zdarzenia dzwiekowe
#include "banksfx.h"		// bank zdarzen dzwiekowych
#include "event.h"		// zdarzenie
#include "eventevt.h"		// zdarzenie animacyjne
#include "pinch.h"		// tunele x/y
#include "button_flat.h"	// plaski obszar do naciskania przycisku
#include "xml_node.h"		// wezel do parsowania plikow xml
#include "xml_file.h"		// parsowanie pliku xml
//#include <nn_matrix.h>	// operacja na macierzach


