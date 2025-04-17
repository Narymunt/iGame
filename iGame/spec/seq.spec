# seq to plik z sekwencjami kiedy odpalamy jakas animacje
# wszystko co w linii zaczynajacej sie od hasha jest pomijane
# typ seq jest zarezerwowany
# maksymalnie 100 zdarzen w scence
# pliki .snd przypisane sa do animacji, dlatego ze dla jednej animacji moga byc np 5 roznych wav - np gdy mowi dobrze 
# w pliku snd zapisane sa zdarzenia dzwiekowe, czyli np dobrze.snd moze miec random z 5 roznych .wav - za kazdym razem bedzie mowil inaczej 

typ
nazwa
plik.evt
event
plik.snd

# np.SIMPLE, czyli odtwarza jedno zdarzenie
SIMPLE
wyskok
bobul.evt
skacze
benc.snd

# np. RANDOM, czyli odtwarza losowe zdarzenie
RANDOM
radosc
bobul.evt
dowolne
radosc.snd

# np. SEQ2 odtwarzam dwa zdarzenia jedno po drugim, czyli np najpierw postac mowi - sprawdzam zadanie, a potem doskonale !
SEQ2
dobrze
bobul.evt
sprawdzam	
sprawdzam.snd
doskonale
doskonale.snd

# np SEQ3, odwarzam 3 zdarzenia, np sprawdzam, zle, sproboj ponownie
SEQ3
zle
bobul.evt
sprawdzam
sprawdzam.snd
zle
zle.snd
odnowa
odnowa.snd

# np SEQ4, odtwarzam 4 zdarzenia, np wstaje, zle zrobione, sproboj ponownie, siadam
SEQ4
zle
bobul.evt
sprawdzam
sprawdzam.snd
zle
zle.snd
odnowa
odnowa.snd
siadam
siadamipierdze.snd

# np SPEAK, odtwarzam 2 zdarzenie tak dlugo az trwa dzwiek, potem koncze 3 zdarzenie
SPEAK
intro
bobul.evt
wlatuje
wlatuje.snd
gadaj
intro.snd
wylatuje
wylatuje.snd


