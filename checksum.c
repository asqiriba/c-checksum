#include <stdio.h>
#include <stdlib.h>

typedef unsigned char      byte;
typedef unsigned short int word16;
typedef unsigned int       word32;

#define BUFFER_LEN        4096

word16 checksum(byte *addr, word32 count);

void main(void){
  byte        buff[BUFFER_LEN];
  word16      check;
  word32      i = 0;

  FILE *archivo;
  FILE *escritura;

  archivo = fopen("datastream.txt", "r");
  
  if(archivo == NULL)
    exit(1);
	
  while(!feof(archivo)){
    fscanf(archivo, "%c", &buff[i]);
    i++;
  }
  check = checksum(buff, i-3);

  escritura = fopen("resultant.txt", "w+");
  fprintf(escritura, "Checksum = %04X \n", check);
  fclose(escritura);
}

word16 checksum(byte *addr, word32 count){
  register word32 sum = 0;
  word16 * waddr = (word16 * ) addr; 
  
  while(count > 1){
    sum=sum + *waddr++;
    count = count - 2;
  }
  
  if (count > 0)
    sum = sum + *((byte *) addr);
  
  while (sum >> 16)
    sum = (sum & 0xFFFF) + (sum >> 16);
  
  return(~sum);
}
