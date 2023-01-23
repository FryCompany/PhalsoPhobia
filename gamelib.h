// Dichiarazione delle funzioni da chiamare in main.c
// Definizione dei tipi necessari alla libreria
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>





//funzioni
int imposta_gioco();
void gioca(int num_giocatori);


int num_giocatori;


//enum
enum tipo_oggetto_iniziale {emf=0, spirit_box=1, videocamera=2, calmanti=3,sale=4};
enum tipo_oggetto_zona {adrenalina=5,cento_dollari=6,coltello=7,nessun_oggetto=8};
enum  tipo_zona{caravan,cucina,soggiorno,camera,bagno,garage,seminterrato};
enum tipo_prova {prova_emf=9,prova_spirit_box=10,prova_videocamera=11,nessuna_prova=12};


//struct
struct Giocatore{
  char nome[20];
  unsigned char sanita_mentale;
  struct Zona_Mappa* posizione;
  unsigned char zaino[4];
  int stato;
};

struct Zona_Mappa{
  enum tipo_zona zona;
  enum tipo_oggetto_zona oggetto_zona;
  enum tipo_prova prova;
  struct Zona_Mappa *prossima_zona;
};
