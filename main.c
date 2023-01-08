#include "gamelib.h"
// Questo file continene solo la definizione della funzione main
// con il menu principale 1-2-3


int main( ) {
int scelta;

  do{
    scelta=0;
    //printf("\e[1;1H\e[2J \n" );
    printf("----------------\n");
    printf("||PhalsoPhobia||\n");
    printf("----------------\n");
    printf("1)IMPOSTA GIOCO\n");
    printf("2)GIOCA\n");
    printf("3)ESCI DAL GIOCO\n \n");
    printf("Cosa vuoi fare:");
    scanf("%d", &scelta);
    while((getchar()) != '\n');
    switch(scelta){
      case 1:
      printf("caso 1\n");
      imposta_gioco();
      break;

      case 2:
    
        printf("caso 2\n");

      break;

      case 3:
      printf("caso 3\n");

      break;

      default:
      printf("cosa qualsiasi \n");
      printf( " Errore di inserimento \n");

      break;
      printf("scelta: %d\n",scelta);
  }
    }while (scelta!=3);

  }
