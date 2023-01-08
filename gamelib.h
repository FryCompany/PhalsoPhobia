// Dichiarazione delle funzioni da chiamare in main.c
// Definizione dei tipi necessari alla libreria
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>




//funzioni
void imposta_gioco();


//static
static void imposta_nomi(int num_giocatori);
static void imposta_difficolta();
static struct Giocatore* giocatori;


//enum
enum tipo_oggetto_iniziale {emf, spirit_box, videocamera, calmanti,sale};
enum tipo_oggetto_zona {adrenalina,cento_dollari,coltello,nessun_oggetto};
enum  tipo_zona{caravan,cucina,soggiorno,camera,bagno,garage,seminterrato};
enum tipo_prova {prova_emf,prova_spirit_box,prova_videocamera,nessuna_prova};

//struct
struct Giocatore{
  char nome[20];
  unsigned char sanita_mentale;
  struct Zona_Mappa* posizione;
  unsigned char zaino[4];
};

struct Zona_Mappa{
  enum tipo_zona zona;
  enum tipo_oggetto_zona oggetto_zona;
  enum tipo_prova prova;
  struct Zona_Mappa *prossima_zona;
};
