#include "gamelib.h"

//static
static void imposta_nomi(int num_giocatori);
static void imposta_difficolta();
static void imposta_oggetto_iniziale(int num_giocatori);
static void  crea_mappa();
static void inserisci_zona();
static void cancella_zona();
static int chiudi_mappa();      //RICORDA DI METTERLI IN ORDINE DI CREAZIONE
static void  stampa_mappa();
static void  scegli_oggetto(int num_giocatori);


static struct Giocatore* giocatori;
static struct Zona_Mappa* mappaNuova;
static struct Zona_Mappa* primaMappa;
static struct Zona_Mappa* ultimaMappa;
static struct Zona_Mappa* stampaMappa;
static struct Zona_Mappa* appoggioMappa;
static struct Zona_Mappa* penultimaMappa;
static struct Zona_Mappa* conteggioMappa;


int controllo_imposta=0;

// comando : gcc  main.c gamelib.c
// Definizioni delle funzioni in gamelib.c.
// Piu altre funzioni di supporto.
// Le funzioni richiamabili in main.c non devono essere static.
// Le altre devono essere static (non visibili all'esterno).

int imposta_gioco(){
  int num_giocatori;
  char scelta;
  int flag=0;
do{

  printf("Inserire il numero di giocatori(Min 1,Max 4): ");
  scanf("%c",&scelta);
  while((getchar()) != '\n');

  switch (scelta) {
    printf("%d\n",num_giocatori );
    case '1':
    case '2':
    case '3':
    case '4':
    num_giocatori=(int)scelta- '0';
    printf("%d\n",num_giocatori );
    flag=1;
    giocatori=(struct Giocatore *) calloc(num_giocatori, sizeof(struct Giocatore));
    imposta_nomi(num_giocatori);
    for(int i=0;i<num_giocatori;i++){
        giocatori[i].sanita_mentale=100;//imposiamo per  ogni giocatore la sanita mentale massima
      }
    imposta_difficolta();
    imposta_oggetto_iniziale(num_giocatori);
    scegli_oggetto(num_giocatori);
    crea_mappa();
    printf("Hai Impostato il gioco ora puoi giocare!!\n");
    controllo_imposta=1; //cambio il valore della variabile globare per poter iniziare a giocare

    break;

    default:
    printf("Valore errato\n");
    sleep(1);
    break;
  }
}while(!flag);
return controllo_imposta;
}

static void imposta_nomi(int num_giocatori){
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

static void imposta_difficolta(){
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
static void imposta_oggetto_iniziale(int num_giocatori) {
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
void scegli_oggetto(int num_giocatori){
  int turni[num_giocatori];
  int temp=0,random_i,flag;
  char input;
  for (int i = 0; i < num_giocatori; i++) {
      turni[i] = i;                            //nell'array vengono inseriti tutti i numeri da 0 a num_giocatori
  }
  for (int i = 0; i < num_giocatori; i++) {
     temp = turni[i];
     random_i = rand() % num_giocatori;

    turni[i] = turni[random_i];             //le posizioni degli elementi vengono mescolate per creare i turni random
    turni[random_i] = temp;
 }
 for (int i = 0; i < num_giocatori; i++) {
   printf("ecco l'ordine %d\n",turni[i] );
 }

  for (int i = 0; i < num_giocatori; i++) {
    do{
      flag=0;
      printf("Selezionare l'oggetto da inserire nello zaino tra :\n");
      printf(" 1)EMF \n");
      printf(" 2)Spirit Box \n");
      printf(" 3)Videocamera \n");
      printf(" 4)Calmanti \n");
      printf(" 5)Sale \n");
      printf(" 6)Adrenalina \n");
      printf(" 7)Cento Dollari \n");
      printf(" 8)Coltello \n");
     printf("Giocatore %s scegli l'oggetto :", giocatori[turni[i]].nome);
     scanf("%c", &input);
     while((getchar()) != '\n');
     switch (input) {
        case '1':

           flag=1;
         break;
        case '2':
        

             flag=1;
           break;
        case '3':

               flag=1;
             break;
         case '4':

                 flag=1;
               break;
         case '5':

                   flag=1;
                 break;
          case '6':

                     flag=1;
                   break;
          case '7':

              flag=1;
                     break;
          case '8':

                flag=1;
                       break;
         default:
         printf("Valore errato \n");
         break;
         }
       }while (flag!=1);
                            //nell'array vengono inseriti tutti i numeri da 0 a num_giocatori
   }
 }

static  void crea_mappa(){
    char scelta;
    int flag=3,flag1,flag2=0;
    printf("Verra inserite tre zone casuali(il minimo per poter giocare, puoi aggiungerne altre dal menu)  \n");
    while(flag!=0){
      flag=flag-1;
      mappaNuova = (struct Zona_Mappa *) malloc(sizeof(struct Zona_Mappa));
      mappaNuova->prossima_zona= NULL;
      do{
      mappaNuova->zona=rand()%7;
        }while( mappaNuova->zona ==0);
      if( primaMappa== NULL) {// No node in the list
        primaMappa = mappaNuova; // The first node is the newly created one
        ultimaMappa = mappaNuova; // The last node is the newly created one
      }
      else
      {
 // Else, there is already at least one node in the list
  ultimaMappa-> prossima_zona= mappaNuova; // the last node becomes the second one
  ultimaMappa= mappaNuova; // The last node is the newly created one
  ultimaMappa->prossima_zona=primaMappa;
  }
  printf("ecco l'ultima zona :%d\n",mappaNuova->zona );
  }

  do{
    flag1=0;
    scelta=0;
    printf("Creazione mappa \n");
    printf("1) Inserisci una zona della mappa \n");
    printf("2) Cancella l'ultima zona inserita \n");
    printf("3) Stampa i campi della mappa  \n");
    printf("4) Fine della creazione della mappa  \n");
    printf("Inserire la scelta :");
    scanf("%c", &scelta);
    while((getchar()) != '\n');
    //printf("\e[1;1H\e[2J \n" );
    switch (scelta) {
      case '1':
      inserisci_zona();
      break;

      case '2':
     cancella_zona();
      break;

      case '3':
      stampa_mappa();
      break;

      case '4':
      flag2=chiudi_mappa();
      if(flag2==1){
      printf("Non è presente il numero minimo di zone della mappa (Min3)\n");
    }else{
      flag1=1;}
      break;

      default:
      printf("Valore errato \n");
      break;
  }
  }while (flag1!=1);

}

static void inserisci_zona(){
    mappaNuova = (struct Zona_Mappa *) malloc(sizeof(struct Zona_Mappa));
    mappaNuova->prossima_zona=NULL;
    do{
    mappaNuova->zona=rand()%7;
      }while( mappaNuova->zona ==0); //effettuo un controllo per verificare che non esca 0 perche è il caravan e non  si puo creare un caravan
    if( primaMappa== NULL) {// No node in the list
      primaMappa = mappaNuova; // The first node is the newly created one
      ultimaMappa = mappaNuova; // The last node is the newly created one
      primaMappa->prossima_zona=primaMappa;
    }
    else
    {
      // Else, there is already at least one node in the list
      ultimaMappa-> prossima_zona= mappaNuova; // the last node becomes the second one
      ultimaMappa= mappaNuova; // The last node is the newly created one
      ultimaMappa->prossima_zona=primaMappa;
    }
    printf("ecco l'ultima zona :%d\n",mappaNuova->zona );
  }

  void stampa_mappa(){
    if(primaMappa == NULL) // No node in the list
    {
      printf("No node in the list!");
    }
    else
    {
      // New pointer used to scan the list.
      stampaMappa = primaMappa;
      do{
        int tipo_zona;
        tipo_zona=stampaMappa->zona;
        switch (tipo_zona) {
          case 1:
          printf("Zona:Cucina\n" );
          break;
          case 2:
          printf("Zona:Soggiorno\n");
          break;
          case 3:
          printf("Zona:Camera\n");
          break;
          case 4:
          printf("Zona:Bagno\n");
          break;
          case 5:
          printf("Zona:Garage\n");
          break;
          case 6:
          printf("Zona:Seminterrato\n");
          break;
          default:
          printf("Errore \n" );
          break;

        }
        stampaMappa = stampaMappa->prossima_zona;
      }while(stampaMappa!= primaMappa); //NULL when this was the last node
    }

    }

    void cancella_zona(){
      if(primaMappa == NULL)
      printf("Non è presente nessuna zona della mappa!\n");
      else {
         penultimaMappa = NULL;
         appoggioMappa = primaMappa;
        if(appoggioMappa->prossima_zona == primaMappa) {// controllo se è l'ultimo della lista cioè il primo perchè la mappa e circolare
          free(appoggioMappa); // Free memory
          primaMappa= NULL; // Now the list is empty
        }
        else {// Otherwise, I need to scan the list until I find the last node (pLast)
          do{
            if((appoggioMappa-> prossima_zona) == ultimaMappa) {// Reached the node before the end
              penultimaMappa = appoggioMappa;
              break;
            }
            else
            appoggioMappa= appoggioMappa-> prossima_zona; // Otherwise, I need to iterate
          }while((appoggioMappa-> prossima_zona) != NULL);
          free(penultimaMappa-> prossima_zona); // Free memory allocated to the last node
          penultimaMappa-> prossima_zona = primaMappa; // imposto alla penultima zona la prima perchè è diventatal'ultima della lista
          ultimaMappa = penultimaMappa; // pPrev becomes the last node
        }
      }


    }

static int chiudi_mappa(){
    int num_mappa=0;
    int flag=0;

    conteggioMappa=primaMappa;
    do{
      num_mappa+=1;
      conteggioMappa = conteggioMappa->prossima_zona;

    }while(conteggioMappa!= primaMappa);
    if (num_mappa<3) {
      flag=1;
    }

    return flag;
  }
