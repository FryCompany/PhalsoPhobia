#include "gamelib.h"
// Questo file continene solo la definizione della funzione main
// con il menu principale 1-2-3
int controllo=0;

int main( ) {
  time_t t;
  srand((unsigned)time(&t));
char scelta;
int flag=0;

  do{
    scelta=0;
    flag=0;
    printf("\e[1;1H\e[2J \n" );
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

      controllo =imposta_gioco();
      break;

      case '2':
      if(controllo==1){
        gioca(num_giocatori);
      }else
      printf("Non hai ancora impostato il gioco!!!\n");


      break;

      case '3':
      //dealloca 
       flag=1;
      break;

      default:
      printf( " Errore di inserimento \n");

      break;


}

}while (flag!=1);

  }
