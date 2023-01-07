#include "gamelib.h"

// comando : gcc  main.c gamelib.c
// Definizioni delle funzioni in gamelib.c.
// Piu altre funzioni di supporto.
// Le funzioni richiamabili in main.c non devono essere static.
// Le altre devono essere static (non visibili all'esterno).

void imposta_gioco(){
  int num_giocatori;
  int flag=0;
do{

  printf("Inserire il numero di giocatori(Min 1,Max 4): ");
  scanf("%d",&num_giocatori);
  while((getchar()) != '\n');
  switch (num_giocatori) {
    printf("%d\n",num_giocatori );
    case 1:
    case 2:
    case 3:
    case 4:
    flag=1;
    giocatori=(struct Giocatore *) calloc(num_giocatori, sizeof(struct Giocatore));
    imposta_nomi(num_giocatori);
    for(int i=0;i<num_giocatori;i++){
        giocatori[i].sanita_mentale=100;
        //printf("%i sanita giocatore %d\n",giocatori[i].sanita_mentale,i+1 );

}
    printf("Hai selezionato il numero di player \n");
    break;

    default:
    printf("Valore errato\n");
    sleep(1);
    break;
  }
}while(!flag);

}

void imposta_nomi(int num_giocatori){
  int flag=0,flag2=0,i=0,flag3=0;
  char nomi[20];
  char appoggio[20];
  for(i=0;i<num_giocatori;i++){
    do{
    flag=0;
    flag2=0;
    flag3=0;
    printf("inserire il nome del %i giocatore :",i+1 );
       scanf("%s", giocatori[i].nome);
     while((getchar()) != '\n');
       // Verifica se ogni carattere della stringa è alfabetico
  for (int f = 0; giocatori[i].nome[f] != '\0'; f++) {
      if (!((giocatori[i].nome[f] >= 'A' && giocatori[i].nome[f] <= 'Z') || (giocatori[i].nome[f] >= 'a' && giocatori[i].nome[f] <= 'z'))) {
          printf("Il nome può contenere solo lettere\n");
          break;
        }else
        flag=1;

      }

      for(int g=0;g<20;g++){
        nomi[g]=giocatori[i].nome[g];

      }
      switch (i) {
        case 0:
        break;
        case 1:
          if (strcmp(giocatori[0].nome, giocatori[1].nome) == 0) {
            printf("sono uguali \n");

          }else{
            flag2=1;
          }

      }



    }while (!flag && !flag2);




       printf("il nome del %i giocatore : %s\n",i+1,giocatori[i].nome );

      //giocatori[i].sanita_mentale=100;

      //printf("%i sanita giocatore %d\n",giocatori[i].sanita_mentale,i+1 );
}


}
