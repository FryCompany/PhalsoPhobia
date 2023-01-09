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
        giocatori[i].sanita_mentale=100;//imposiamo per  ogni giocatore la sanita mentale massima
      }
    imposta_difficolta();
    imposta_oggetto_iniziale(num_giocatori);
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
  int flag=0,flag2=0,i=0;
  char nomi[4][20];
  char appoggio[20];
  for(i=0;i<num_giocatori;i++){
    do{
    flag=0;
    flag2=0;

    printf("inserire il nome del %i giocatore :",i+1 );
       scanf("%s", giocatori[i].nome);
     while((getchar()) != '\n');
       // Verifica se ogni carattere della stringa è alfabetico
  for (int f = 0; giocatori[i].nome[f] != '\0'; f++) {
      if (!((giocatori[i].nome[f] >= 'A' && giocatori[i].nome[f] <= 'Z') || (giocatori[i].nome[f] >= 'a' && giocatori[i].nome[f] <= 'z'))) {
          printf("Il nome non puo' contenere numeri o caratteri speciali \n");
          flag=1;
        break;
        }
        }
        //Copiamo in un array di caratteri il nome inserito per verificare che il nome non sia gia stato inserito
        for (int h = 0; h < strlen(giocatori[i].nome); h++) {
          nomi[i][h] = giocatori[i].nome[h];
        }
        // Aggiungiamo il carattere di fine stringa all'array
          nomi[i][strlen(giocatori[i].nome)] = '\0';

      for (int y = 0; y < num_giocatori; y++)
          if ((strcmp(nomi[y], giocatori[i].nome) == 0) && y!=i) {
            printf("Nome gia' inserito , Reinseriscilo  \n");
            flag=1;
            break;

          }
    }while(flag==1);
       printf("il nome del %i giocatore : %s\n",i+1,giocatori[i].nome );
}


}

void imposta_difficolta(){
  char input;
  int flag=0;
do{
  flag=0;
  input=0;
printf("Selezionare la difficolta :\n");
printf("1) Dilettante \n");
printf("2) Intermedio \n");
printf("3) Incubo \n");
printf("Inserire la scelta :");
scanf("%c", &input);
while((getchar()) != '\n');
switch (input) {
  case '1':
    printf("1) Dilettante \n");
      flag=1;
    break;
  case '2':
    printf("2) Intermedio \n");
      flag=1;
    break;
  case '3':
    printf("3) Incubo \n");
      flag=1;
    break;
  default:
printf("Valore errato \n");

    break;
  }
}while (flag!=1);



}
void imposta_oggetto_iniziale(int num_giocatori) {
int oggetto_iniziale;
int flag=0;

for (int i = 0; i < num_giocatori; i++) {
  oggetto_iniziale=rand()%5;

  giocatori[i].zaino[0]=oggetto_iniziale;
  if (oggetto_iniziale<=2) { //controllo se e' stato generato almeno un oggetto neccessario
    flag=1;
  }
  printf("ziano: %d\n", giocatori[i].zaino[0]);
  }



  if (flag==0){
      int oggetto_necessario=rand()%3;             //se non viene inserito un oggetto per raccogliere le prove
      int giocatore_casuale=rand()%num_giocatori+1;//viene imposto ad un giocatore casuale
      giocatori[giocatore_casuale].zaino[0]=oggetto_necessario;
      printf("Il valore necesa è stato inserito \n");
        printf("ziano: %d\n", giocatori[giocatore_casuale].zaino[0]);
  }
}
