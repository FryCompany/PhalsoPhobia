#include "gamelib.h"
// Questo file continene solo la definizione della funzione main
// con il menu principale 1-2-3


int main( ) {
  time_t t;
  srand((unsigned)time(&t));
char scelta;
int flag=0;

  do{
    scelta=0;
    flag=0;
    //printf("\e[1;1H\e[2J \n" );
    printf("----------------\n");
    printf("||PhalsoPhobia||\n");
    printf("----------------\n");
    printf("1)IMPOSTA GIOCO\n");
    printf("2)GIOCA\n");
    printf("3)ESCI DAL GIOCO\n \n");
    printf("Cosa vuoi fare:");
    scanf("%c", &scelta);
    while((getchar()) != '\n');
    switch(scelta){
      case '1':
      printf("caso 1\n");
      imposta_gioco();
      break;

      case '2':

        printf("caso 2\n");

      break;

      case '3':
      printf("caso 3\n");
       flag=1;
      break;

      default:
      printf( " Errore di inserimento \n");

      break;
      printf("scelta: %c\n",scelta);
  }
}while (flag!=1);

  }
