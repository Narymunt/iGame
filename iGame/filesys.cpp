
// filesystem inside one file
// TODO : 
// - check sum
// - strcmp instead of search loop
// - case check A^a and so on
// - long filenames
// - resources editor
// - dynamic add^remove files from archives
// USAGE :
// create class with filename filesys_archive("data.mml");
// filesys_load(&buffer,"file.bin");


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "iGame.h"

//--- 

Filesystem::Filesystem(char cArchiveName[])
{
  
  cpArchiveNname = (char *) malloc(strlen(cArchiveName)+1);

  strcpy(archive_name, name);	// hmm... to ciekawe, bo ze strcmp sa czasem problemy

}

Filesystem::~Filesystem()
{
    free (cpArchiveName);
}

//--- search for filename inside archive

long Filesystem::SearchFile(char cFilename[])
{

}

//--- load file

void Filesystem::LoadIn(unsigned char *uc_pBuffer)
{
  FILE* fptr;
  fptr = fopen(archive_name, "rb");
  fseek(fptr, -FFilesys_indexblock.lokation, SEEK_END);

  switch (FFilesys_indexblock.compression)
	{
	case compr_lzari:
	  lzari_decompress(fptr, uc_pBuffer, FFilesys_indexblock.length);
	  break;
	case compr_lzss:
	  lzss_decompress(fptr, uc_pBuffer, FFilesys_indexblock.length);
	  break;
	case compr_none:
	  fread(uc_pBuffer, FFilesys_indexblock.length, 1, fptr);
	  break;
	}
  fclose(fptr);
  return;
}

//--- load file from filesystem

void Filesystem::Load(unsigned char *uc_pBuffer, char cFilename[])
{


}

//--- insert char into buffer

int putc_buffer(int outc)
{
  to_buffer[to_pointer++] = (unsigned char) outc;
  return(1);
}

//--- get char from buffer

int getc_lz(void)
{
  if (from_pointer++ == from_max)
    return(EOF);	// increased pointer
  return(getc(lz_fptr));
}

// dekoduj lzss - szybkie
// dekodowanie chunk

void lzss_decode(void)
{
	int i, j, k, r, c;
	unsigned int flags;

	for (i = 0; i < N - F; i++) text_buf[i] = ' ';
	r = N - F;  flags = 0;
	
	for ( ; ; ) 
	{
		
		if (((flags >>= 1) & 256) == 0) 
		{
			if ((c = getc_lz()) == EOF) break;
			flags = c | 0xff00;
		}
		
		if (flags & 1) 
		{
			if ((c = getc_lz()) == EOF) break;
			putc_buffer(c);  
			text_buf[r++] = c;  
			r &= (N - 1);
		} 
		else 
		{
			if ((i = getc_lz()) == EOF) break;
			if ((j = getc_lz()) == EOF) break;
			
			i |= ((j & 0xf0) << 4);  j = (j & 0x0f) + THRESHOLD;
		
			for (k = 0; k <= j; k++) 
			{
				c = text_buf[(i + k) & (N - 1)];
				putc_buffer(c);  
				text_buf[r++] = c;  
				r &= (N - 1);
			}
		}
	}
}

// dekompresuj

void lzss_decompress(FILE* fptr1, unsigned char* tbuffer, long comp_size)
{
  lz_fptr = fptr1;
  from_pointer = 0;		// poczatek
  from_max = comp_size;
  to_pointer = 0;
  to_buffer = tbuffer;
  lzss_decode();
}

// ustawianie bitu

void PutBit(int bit)
{
	if (bit) PB_buffer |= PB_mask;

	if ((PB_mask >>= 1) == 0) 
	{
		PB_buffer = 0;  PB_mask = 128;  codesize++;
	}
}

// odswiez bufor z zapisem bitowym

void FlushBitBuffer(void)
{
	int  i;
	for (i = 0; i < 7; i++) PutBit(0);
}

// pobierz bit z bufora

int GetBit(void)
{
	if ((GB_mask >>= 1) == 0) 
	{
		GB_buffer = getc_lz(); 
		GB_mask = 128;
	}
	return ((GB_buffer & GB_mask) != 0);
}

// zacznij budowac 

void StartModel(void)
{
	int ch, sym, i;

	sym_cum[N_CHAR] = 0;
	
	for (sym = N_CHAR; sym >= 1; sym--) 
	{
		ch = sym - 1;
		char_to_sym[ch] = sym;  sym_to_char[sym] = ch;
		sym_freq[sym] = 1;
		sym_cum[sym - 1] = sym_cum[sym] + sym_freq[sym];
	}
	
	sym_freq[0] = 0;
	position_cum[N] = 0;
	
	for (i = N; i >= 1; i--)
		position_cum[i - 1] = position_cum[i] + 10000 / (i + 200);
}

// aktualizuj

void UpdateModel(int sym)
{
	int i, c, ch_i, ch_sym;

	if (sym_cum[0] >= MAX_CUM) 
	{
		c = 0;
		
		for (i = N_CHAR; i > 0; i--) 
		{
			sym_cum[i] = c;
			c += (sym_freq[i] = (sym_freq[i] + 1) >> 1);
		}
		sym_cum[0] = c;
	}
	
	for (i = sym; sym_freq[i] == sym_freq[i - 1]; i--) ;
	
	if (i < sym) 
	{
		ch_i = sym_to_char[i];    
		ch_sym = sym_to_char[sym];
		
		sym_to_char[i] = ch_sym;  
		sym_to_char[sym] = ch_i;
		
		char_to_sym[ch_i] = sym; 
		char_to_sym[ch_sym] = i;
	}
	sym_freq[i]++;
	while (--i >= 0) sym_cum[i]++;
}

// sekwencja bitow na wyjscie

static void Output(int bit)
{
	PutBit(bit);
	for ( ; shifts > 0; shifts--) PutBit(! bit);
}

// pozycja

void EncodePosition(int position)
{
	unsigned long int  range;

	range = high - low;
	high = low + (range * position_cum[position    ]) / position_cum[0];
	low +=       (range * position_cum[position + 1]) / position_cum[0];
	
	for ( ; ; ) 
	{
		if (high <= Q2) Output(0);
		else 
			if (low >= Q2) 
			{
			Output(1);  low -= Q2;  high -= Q2;
			} 
			else 
			if (low >= Q1 && high <= Q3) 
			{
			shifts++;  low -= Q1;  high -= Q1;
			} else break;
		low += low;  high += high;
	}
}

// koniec 

void EncodeEnd(void)
{
	shifts++;
	if (low < Q1) Output(0);  else Output(1);
	FlushBitBuffer();
}

// szukaj 

int BinarySearchSym(unsigned int x)
{
	int i, j, k;

	i = 1;  j = N_CHAR;
	
	while (i < j) 
	{
		k = (i + j) / 2;
		if (sym_cum[k] > x) i = k + 1;  else j = k;
	}
	return i;
}

// szukaj pozycji

int BinarySearchPos(unsigned int x)
{
	int i, j, k;
	i = 1;  j = N;
	
	while (i < j) 
	{
		k = (i + j) / 2;
		if (position_cum[k] > x) i = k + 1;  else j = k;
	}
	return i - 1;
}

// zacznij dekodowanie

void StartDecode(void)
{
	int i;
	for (i = 0; i < M + 2; i++)
		value = 2 * value + GetBit();
}

// dekoduj znak

int DecodeChar(void)
{
	int	 sym, ch;
	unsigned long int  range;

	range = high - low;
	sym = BinarySearchSym((unsigned int)
		(((value - low + 1) * sym_cum[0] - 1) / range));
	
	high = low + (range * sym_cum[sym - 1]) / sym_cum[0];
	low +=       (range * sym_cum[sym    ]) / sym_cum[0];
	
	for ( ; ; ) 
	{
		if (low >= Q2)
		{
			value -= Q2;  low -= Q2;  high -= Q2;
		}
		else 
			if (low >= Q1 && high <= Q3) 
			{
			value -= Q1;  low -= Q1;  high -= Q1;
			}
			else 
			if (high > Q2) break;
		low += low;  high += high;
		value = 2 * value + GetBit();
	}
	ch = sym_to_char[sym];
	UpdateModel(sym);
	return ch;
}

// dekoduj pozycje 

int DecodePosition(void)
{
	int position;
	unsigned long int  range;

	range = high - low;
	position = BinarySearchPos((unsigned int)
		(((value - low + 1) * position_cum[0] - 1) / range));
	high = low + (range * position_cum[position    ]) / position_cum[0];
	low +=       (range * position_cum[position + 1]) / position_cum[0];
	
	for ( ; ; ) 
	{
		if (low >= Q2) 
		{
			value -= Q2;  low -= Q2;  high -= Q2;
		} 
		else 
			if (low >= Q1 && high <= Q3) 
			{
			value -= Q1;  low -= Q1;  high -= Q1;
			} 
			else 
			
			if (high > Q2) break;
		low += low;  high += high;
		value = 2 * value + GetBit();
	}
	return position;
}

// dekoduj arytmetycznie

void lzari_Decode(void)
{
	int  i, j, k, r, c;
	unsigned long int  count, temp;

	textsize = 0;
	temp = getc_lz() << 24;
	textsize |= temp;
	temp = getc_lz() << 16;
	textsize |= temp;
	temp = getc_lz() << 8;
	textsize |= temp;
	temp = getc_lz();
	textsize |= temp;

	if (textsize == 0) return;
	StartDecode();  StartModel();
	
	for (i = 0; i < N - F2; i++) text_buf[i] = ' ';
	r = N - F2;
	
	for (count = 0; count < textsize; ) 
	{
		c = DecodeChar();
		
		if (c < 256) 
		{
			putc_buffer(c);  text_buf[r++] = c;
			r &= (N - 1);  count++;
		} 
		else 
		{
			i = (r - DecodePosition() - 1) & (N - 1);
			j = c - 255 + THRESHOLD;
			
			for (k = 0; k < j; k++) 
			{
				c = text_buf[(i + k) & (N - 1)];
				putc_buffer(c);  text_buf[r++] = c;
				r &= (N - 1);  count++;
			}
		}
	}
}

// dekompresuj 

void lzari_decompress(FILE* fptr1, unsigned char* tbuffer, long comp_size)
{
  lz_fptr = fptr1;
  textsize = 0;
  codesize = 0;
  from_pointer = 0;
  to_pointer = 0;
  PB_buffer = 0;
  PB_mask = 128;
  GB_buffer = 0;
  GB_mask = 0;
  low = 0;
  high = Q4;
  value = 0;
  shifts = 0;
  from_max = comp_size;
  to_buffer = tbuffer;
  lzari_Decode();
  return;
}

// szukaj pliku w spakowanym

long FFilesys_search(char name[])
{
  FILE* fptr;
  long i, seeklong;
//  int j,ok;

  fptr = fopen(archive_name, "rb"); // bez sprawdzania czy plik istnieje, wiec moga byc bugi
  seeklong = sizeof(FFilesys_header);
  fseek(fptr, -seeklong, SEEK_END);
  fread(&FFilesys_header, sizeof(FFilesys_header), 1, fptr);
  
  seeklong-=2;
  
  for (i = 0; i < FFilesys_header.number_files; i++)
	{
	
	seeklong += sizeof(FFilesys_indexblock)-5;	// pomylka w offsetach ? 
	
	fseek(fptr, -seeklong, SEEK_END);
	
	fread(&FFilesys_indexblock.name, 13, 1, fptr);
	fread(&FFilesys_indexblock.lokation,1,sizeof(FFilesys_indexblock.lokation),fptr);
	fread(&FFilesys_indexblock.length,1,sizeof(FFilesys_indexblock.length),fptr);
	fread(&FFilesys_indexblock.original_length,1,sizeof(FFilesys_indexblock.original_length),fptr);
	fread(&FFilesys_indexblock.compression,1,sizeof(FFilesys_indexblock.compression),fptr);

	if ((int)strcmp(FFilesys_indexblock.name, name) == 0)
	  break;
	}
  fclose(fptr);
  return(FFilesys_indexblock.original_length);
}

// wczytanie pliku


// wczytuj, zwracaj 0 jezeli blad jezeli nie, to 1

int FFilesys_load(unsigned char *buffer,char filename[])
{
	long datalen;	// jak dlugi jest rozkompresowany rekord

	datalen = FFilesys_search(filename);

	if (datalen==0) return 0; // nie znalazl, albo plik 0 dlugosci, a takich nie ma

	FFilesys_load_in(buffer);

	return 1;
}

// end

