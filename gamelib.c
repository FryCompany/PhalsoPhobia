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
static void stampa_inventario(int p);
static void menu_scelte(int p);
static void torna_caravan(int p);
static void stampa_info_p(int p);
static void stampa_info_z(int p);
static void avanza(int p);
static int raccogli_prova(int p);
static void raccogli_oggetto(int p);
static void usa_oggetto(int p,int num_giocatori);
static void passa(int p);
static void deallocalista();









static struct Giocatore* giocatori;
static struct Zona_Mappa* mappaNuova;
static struct Zona_Mappa* primaMappa;
static struct Zona_Mappa* ultimaMappa;
static struct Zona_Mappa* stampaMappa;
static struct Zona_Mappa* appoggioMappa;
static struct Zona_Mappa* penultimaMappa;
static struct Zona_Mappa* conteggioMappa;
static struct Zona_Mappa* zonaCaravan;



int controllo_imposta=0,difficolta=0,avanza_counter=1;
int prova1_trovata=0,prova2_trovata=0,prova3_trovata=0;
int somma1=0,raccolta_emf=0,raccolta_spirit=0,raccolta_video=0;


// comando : gcc  main.c gamelib.c
// Definizioni delle funzioni in gamelib.c.
// Piu altre funzioni di supporto.
// Le funzioni richiamabili in main.c non devono essere static.
// Le altre devono essere static (non visibili all'esterno).


int imposta_gioco(){
  if(controllo_imposta==1){
    deallocalista(); //se il giocatore
  }                 // vuole reimpostare il gioco devo deallocare le cose allocate prima
  char scelta=0;
  int flag=0;
  printf("\e[1;1H\e[2J \n" );
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
        giocatori[i].sanita_mentale=100;//imposto per  ogni giocatore la sanita mentale massima
        giocatori[i].stato=1; //imposto per ogni giocatore lo stato 1 cioè vivo
      }
    imposta_difficolta();
    imposta_oggetto_iniziale(num_giocatori);
    scegli_oggetto(num_giocatori);

    crea_mappa();
    printf("Hai Impostato il gioco ora puoi giocare!!\n");
    sleep(2);
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
    printf("\e[1;1H\e[2J \n" );
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
          sleep(1);
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
            sleep(1);
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
  printf("\e[1;1H\e[2J \n" );
do{
  flag=0;
  input=0;
printf("Selezionare la difficolta :\n");
printf("1) Dilettante \n");
printf("2) Intermedio \n");
printf("3) Incubo \n");
printf("ecco :%p\n",(void*) &giocatori[0]);
printf("Inserire la scelta :");
scanf("%c", &input);
while((getchar()) != '\n');
printf("\e[1;1H\e[2J \n" );
switch (input) {
  case '1':
    difficolta=1;
    flag=1;
    break;
  case '2':
    difficolta=2;
    flag=1;
    break;
  case '3':
    difficolta=3;
    flag=1;
    break;

   default:
   printf("Valore errato \n");
   sleep(1);
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
  }



  if (flag==0){
      int oggetto_necessario=rand()%3;   //se non viene inserito un oggetto per raccogliere le prove
      if(num_giocatori!=1){                                //viene imposto ad un giocatore casuale
      int giocatore_casuale=rand()%num_giocatori+1;
      giocatori[giocatore_casuale].zaino[0]=oggetto_necessario;
      }else{ // se c'è un solo giocatore lo inserisco direttamente nel suo inventario
      giocatori[0].zaino[0]=oggetto_necessario;
    }
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
    printf("\e[1;1H\e[2J \n" );
    do{
      flag=0;

      printf("Selezionare l'oggetto da inserire nello zaino tra :\n");
      printf(" 1)Adrenalina \n");
      printf(" 2)Cento Dollari \n");
      printf(" 3)Coltello \n");

     printf("Giocatore %s scegli l'oggetto :", giocatori[turni[i]].nome);
     scanf("%c", &input);
     while((getchar()) != '\n');
     printf("\e[1;1H\e[2J \n" );
     switch (input) {
        case '1':
          giocatori[turni[i]].zaino[1]=adrenalina;//l'oggetto zero nello zaino viene generato casualmente
          flag=1;
          break;
        case '2':
          giocatori[turni[i]].zaino[1]=cento_dollari;
          flag=1;
          break;
        case '3':
          giocatori[turni[i]].zaino[1]=coltello;
          flag=1;
          break;

         default:
         printf("Valore errato, Riprova! \n");
         sleep(1);
         break;
         }
         giocatori[turni[i]].zaino[2]=nessun_oggetto;//Imposto gli altri slot nello zaino nessun oggetto
         giocatori[turni[i]].zaino[3]=nessun_oggetto;
       }while (flag!=1);

   }

 }

static  void crea_mappa(){
    char scelta;
    int flag=3,flag1,flag2=0;
    printf("\e[1;1H\e[2J \n" );
    printf("Verranno inserite tre zone casuali(il minimo per poter giocare, puoi aggiungerne altre dal menu)  \n");
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
  //  printf("\e[1;1H\e[2J \n" );
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

  zonaCaravan = (struct Zona_Mappa *) malloc(sizeof(struct Zona_Mappa));//creo la zona di memoria per il caravan
  zonaCaravan->prossima_zona=primaMappa; //prossima zona la imposto la prima
  zonaCaravan->zona=caravan;
  zonaCaravan->oggetto_zona=nessun_oggetto;
  zonaCaravan->prova=nessuna_prova;

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
  }

  void stampa_mappa(){
    printf("\e[1;1H\e[2J \n" );
    if(primaMappa == NULL) // No node in the list
    {
      printf("Non è presente nessuna zona della mappa! \n");
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
      printf("\e[1;1H\e[2J \n" );
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
  static void stampa_inventario(int p){
        int oggetto;
        printf("Ecco gli elementi nello zaino di %s : \n",giocatori[p].nome);
        for (int y = 0; y < 4; y++) {
          oggetto=giocatori[p].zaino[y];
        switch(oggetto){
          case 0:
          printf("•EMF \n");
          break;
          case 1:
          printf("•Spirit Box \n");
          break;
          case 2:
          printf("•Videocamera \n");
          break;
          case 3:
          printf("•Calmanti  \n");
          break;
          case 4:
          printf("•Sale \n");
          break;
          case 5:
          printf("•Adrenalina \n");
          break;
          case 6:
          printf("•Cento Dollari \n");
          break;
          case 7:
          printf("•Coltello \n");
          break;
          case 8:
          printf("•Nessun Oggetto\n" );
          break;
          case 9:
          printf("•Prova EMF\n" );
          break;
          case 10:
          printf("•Prova Spirit Box\n" );
          break;
          case 11:
          printf("•Prova Videocamera \n" );
          break;
          default:
          printf("•Errore\n");
          break;
        }
      }
      }


void  gioca(int num_giocatori){
  printf("\e[1;1H\e[2J \n" );
    int turni[num_giocatori];
    int temp=0,random_i,flag,possibila_prova,stampa_zona,fantasma=0,flag1;
    char input;
    for (int i = 0; i < num_giocatori; i++) {
      giocatori[i].posizione=primaMappa; //imposto tutti i giocatori presenti nella mappa iniziale
    }

    for (int i = 0; i < num_giocatori; i++) {
        turni[i] = i;                            //nell'array vengono inseriti tutti i numeri da 0 a num_giocatori
    }

   int p=0;
   primaMappa->prova=nessuna_prova;
   primaMappa->oggetto_zona=nessun_oggetto; //AL primo turno non puo' esserci ne una prova ne un oggetto
  do{

    for (int i = 0; i < num_giocatori; i++) {
       temp = turni[i];
       random_i = rand() % num_giocatori;

      turni[i] = turni[random_i];             //le posizioni degli elementi vengono mescolate per creare i turni random
      turni[random_i] = temp;
   }
  for (int i = 0; i < num_giocatori; i++) {
    if (turni[i]==0 && giocatori[turni[i]].stato==1) { //controllo se il giocatore a cui tocca il turo se è vivo
      p=0;
      menu_scelte(p);
    }
    if (turni[i]==1 && giocatori[turni[i]].stato==1) {
      p=1;
      menu_scelte(p);
    }
    if (turni[i]==2 && giocatori[turni[i]].stato==1) {
      p=2;
      menu_scelte(p);
    }
    if (turni[i]==3 && giocatori[turni[i]].stato==1)  {
      p=3;
      menu_scelte(p);
    }
    if (turni[i]==4 && giocatori[turni[i]].stato==1) {
      p=4;
      menu_scelte(p);
    }

}
}while(1); //il gioco si ripete finche i giocatori perdono o vincono



    }
 void menu_scelte(int p){
   int flag=0,usa_sale=0,fantasma=0;
   do{
   char scelta;
   printf("\n");
   printf("Giocatore %s cosa vuoi fare :\n",giocatori[p].nome);
   printf("1)Torna al caravan\n");
   printf("2)Stampa le info del giocatore\n");
   printf("3)Stampa i valori della zona in cui ti trovi  \n");
   printf("4)Avanza\n");
   printf("5)Raccogli Prova \n");
   printf("6)Raccogli Oggetto \n");
   printf("7)Usa Oggetto \n");
   printf("8)Fine Turno \n");
   printf("Inserire la scelta: ");
   scanf("%c",&scelta);
   while((getchar()) != '\n');
   switch (scelta) {
     case '1':
     if(fantasma==0){
      torna_caravan(p);
    }else{
      printf("Non puoi tornare al caravan se il fantasma e presente nella stanza \n");
      printf("Finisci il turno per far scomparire il fantasma..\n");
    }
     break;
     case '2':
     stampa_info_p(p);
     break;
     case '3':
     stampa_info_z(p);
     break;
     case '4':
      if(num_giocatori!=1){
     if(avanza_counter>=1){
       avanza_counter=avanza_counter-1;
     avanza(p);
      }else{
        printf("Non puoi più avanzare \n");
      }
        }else{
          avanza(p);
        }
     break;
     case '5':
     fantasma= raccogli_prova(p);
     break;
     case '6':
     raccogli_oggetto(p);
     break;
     case '7':
     usa_oggetto(p,num_giocatori);
     break;
     case '8':
     flag=1;
     avanza_counter=1; //Imposto la variabile uguale ad uno cosi il prossimo player puo avanzare
     fantasma=0; //quando il giocatore passa il turno il fantasma "scompare"
     break;
   }
 }while(flag!=1);

 }
void torna_caravan(int p){
  int pos_prova=0,somma=0;
  printf("\e[1;1H\e[2J \n" );
  printf("Complimenti sei riuscito a tornare al caravan sano e salvo \n");
  giocatori[p].posizione=zonaCaravan;
  for(int i=0;i<4;i++){
    if(giocatori[p].zaino[i]==prova_emf){
      prova1_trovata=1;
      pos_prova=i;
    }
    if(giocatori[p].zaino[i]==prova_spirit_box){
      prova2_trovata=1;
      pos_prova=i;

    }
    if(giocatori[p].zaino[i]==prova_videocamera){
      prova3_trovata=1;
      pos_prova=i;
    }
    somma=prova1_trovata+prova2_trovata+prova3_trovata;
    printf("%d\n",somma);
    if(somma==1){
      if(prova1_trovata==1){
        giocatori[p].zaino[pos_prova]=spirit_box;
      }
      if(prova2_trovata==1){
        giocatori[p].zaino[pos_prova]=videocamera;
      }
      if(prova3_trovata==1){
        giocatori[p].zaino[pos_prova]=emf;
      }
    }
    if(somma==2){
      if(prova1_trovata==1 && prova2_trovata ==1){
        giocatori[p].zaino[pos_prova]=videocamera;
      }
      if(prova2_trovata==1 && prova3_trovata==1){
        giocatori[p].zaino[pos_prova]=emf;
      }
      if(prova1_trovata==1 && prova3_trovata==1){
        giocatori[p].zaino[pos_prova]=spirit_box;
      }
    }
    }
    }




void stampa_info_z(int p){
int stampa_zona,stampa_oggetti_Mappa,stampa_prova_Mappa;
printf("\e[1;1H\e[2J \n" );
printf("Ecco dove ti trovi:\n");
stampaMappa=giocatori[p].posizione;
stampa_zona=stampaMappa->zona;
switch (stampa_zona) {
  case 0:
  printf("Zona:Caravan\n");
  break;
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
stampa_oggetti_Mappa=stampaMappa->oggetto_zona;
switch (stampa_oggetti_Mappa) {
  case 5:
  printf("•E' presente una siringa di Adrenalina \n");
  break;
  case 6:
  printf("•Sono presenti Cento Dollari \n");
  break;
  case 7:
  printf("•E' presente un Coltello \n");
  break;
  case 8:
  printf("•Nessun Oggetto\n" );
  break;
  default:
  printf("•Errore\n");
  break;

}
stampa_prova_Mappa=stampaMappa->prova;
switch (stampa_prova_Mappa) {
  case 9:
  printf("•E' presente una Prova EMF \n");
  break;
  case 10:
  printf("•E' presente una Prova Spirit Box \n");
  break;
  case 11:
  printf("•E' presente una Prova Videocamera \n");
  break;
  case 12:
  printf("•Nessuna Prova \n" );
  break;
  default:
  printf("•Errore\n");
  break;

}
}
  void stampa_info_p(int p){
  printf("\e[1;1H\e[2J \n" );
  printf("Nome: %s\n",giocatori[p].nome );
  printf("Sanita Mentale: %u\n",giocatori[p].sanita_mentale);
  stampa_inventario(p);
  }



  int raccogli_prova(int p){
    int oggetto,flag=0,spawn_fantasma=0,fantasma=0;
    appoggioMappa=NULL;
    appoggioMappa=giocatori[p].posizione;
    for (int y = 0; y < 4; y++) {
      oggetto=giocatori[p].zaino[y];
      switch (oggetto) {
        case 0:
        flag=1;
        if(appoggioMappa->prova==9){
          printf("Hai racolto la prova EMF \n");
          giocatori[p].zaino[y]=prova_emf;
          raccolta_emf=1;
          somma1=raccolta_emf+raccolta_spirit+raccolta_video;
          switch (difficolta) {
            case 1:
              spawn_fantasma=rand()%100;
                if(somma1==1){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 30:
                  fantasma=1;
                  printf("BOOO ANDATEVENE DA CASA MIA..\n");
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      giocatori[i].sanita_mentale-=20;
                    }
                  }
                  break;
                }
                }
                if(somma1==2){
                  spawn_fantasma=rand()%100;
                  switch (spawn_fantasma) {
                    case 0 ... 40:
                    fantasma=1;
                    printf("IL MIO POTERE AUMENTA OGNI VOLTA CHE MI VEDETE\n" );
                    appoggioMappa=giocatori[p].posizione;
                    for (int i = 0; i < num_giocatori; i++) {
                      if(giocatori[i].posizione==appoggioMappa){
                        giocatori[i].sanita_mentale-=30;
                      }
                    }
                    break;
                  }
                }
                if(somma1==3){
                  spawn_fantasma=rand()%100;
                  switch (spawn_fantasma) {
                    case 0 ... 60:
                    fantasma=1;
                    printf("LASCIATEMI IN PACE O PAGHERETE LE CONSEGUENZE \n");
                    appoggioMappa=giocatori[p].posizione;
                    for (int i = 0; i < num_giocatori; i++) {
                      if(giocatori[i].posizione==appoggioMappa){
                        giocatori[i].sanita_mentale-=50;
                      }
                    }
                    break;
                  }
                }




            break;
            case 2:
            spawn_fantasma=rand()%100;
              if(somma1==1){
              spawn_fantasma=rand()%100;
              switch (spawn_fantasma) {
                case 0 ... 40:
                fantasma=1;
                printf("BOOO ANDATEVENE DA CASA MIA..\n");
                appoggioMappa=giocatori[p].posizione;
                for (int i = 0; i < num_giocatori; i++) {
                  if(giocatori[i].posizione==appoggioMappa){
                    giocatori[i].sanita_mentale-=30;
                  }
                }
                break;
              }
              }
              if(somma1==2){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 50:
                  fantasma=1;
                  printf("IL MIO POTERE AUMENTA OGNI VOLTA CHE MI VEDETE\n" );
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      giocatori[i].sanita_mentale-=40;
                    }
                  }
                  break;
                }
              }
              if(somma1==3){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 70:
                  fantasma=1;
                  printf("LASCIATEMI IN PACE O PAGHERETE LE CONSEGUENZE \n");
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      giocatori[i].sanita_mentale-=50;
                    }
                  }
                  break;
                }
              }

            break;
            case 3:
            spawn_fantasma=rand()%100;
              if(somma1==1){
              spawn_fantasma=rand()%100;
              switch (spawn_fantasma) {
                case 0 ... 50:
                fantasma=1;
                printf("BOOO ANDATEVENE DA CASA MIA..\n");
                appoggioMappa=giocatori[p].posizione;
                for (int i = 0; i < num_giocatori; i++) {
                  if(giocatori[i].posizione==appoggioMappa){
                    giocatori[i].sanita_mentale-=40;
                  }
                }
                break;
              }
              }
              if(somma1==2){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 65:
                  fantasma=1;
                  printf("IL MIO POTERE AUMENTA OGNI VOLTA CHE MI VEDETE\n" );
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      giocatori[i].sanita_mentale-=50;
                    }
                  }
                  break;
                }
              }
              if(somma1==3){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 80:
                  fantasma=1;
                  printf("LASCIATEMI IN PACE O PAGHERETE LE CONSEGUENZE \n");
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      if(giocatori[i].sanita_mentale>60){
                      giocatori[i].sanita_mentale-=60;
                    }else{
                      giocatori[i].stato=0;
                      for(int y=0;y<4; y++){
                      if(giocatori[i].zaino[y]==emf || giocatori[i].zaino[y]==spirit_box || giocatori[i].zaino[y]==videocamera){
                        appoggioMappa=giocatori[i].posizione;
                        appoggioMappa->oggetto_zona=giocatori[i].zaino[y]; //quando il giocatore muore è possiede
                                                                           // un oggetto per raccogliere le prove
                      }                                                    // quel oggetto viene lascitato come oggetto
                                                                           // nella zona per poter continuare a giocare
                      }
                    }
                    }
                  }
                  break;
                }
              }

            break;
          }
        }else{
          printf("Non è presente nessuna prova!! \n");
        }
        break;
        case 1:
        flag=1;
        if(appoggioMappa->prova==10){
          printf("Hai racolto la prova Spirit Box \n");
          giocatori[p].zaino[y]=prova_spirit_box;
          raccolta_spirit=1;
          somma1=raccolta_emf+raccolta_spirit+raccolta_video;
          switch (difficolta) {
            case 1:
              spawn_fantasma=rand()%100;
                if(somma1==1){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 30:
                  fantasma=1;
                  printf("BOOO ANDATEVENE DA CASA MIA..\n");
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      giocatori[i].sanita_mentale-=20;
                    }
                  }
                  break;
                }
                }
                if(somma1==2){
                  spawn_fantasma=rand()%100;
                  switch (spawn_fantasma) {
                    case 0 ... 40:
                    fantasma=1;
                    printf("IL MIO POTERE AUMENTA OGNI VOLTA CHE MI VEDETE \n" );
                    appoggioMappa=giocatori[p].posizione;
                    for (int i = 0; i < num_giocatori; i++) {
                      if(giocatori[i].posizione==appoggioMappa){
                        giocatori[i].sanita_mentale-=30;
                      }
                    }
                    break;
                  }
                }
                if(somma1==3){
                  spawn_fantasma=rand()%100;
                  switch (spawn_fantasma) {
                    case 0 ... 60:
                    fantasma=1;
                    printf(" LASCIATEMI IN PACE O PAGHERETE LE CONSEGUENZE\n");
                    appoggioMappa=giocatori[p].posizione;
                    for (int i = 0; i < num_giocatori; i++) {
                      if(giocatori[i].posizione==appoggioMappa){
                        if(giocatori[i].sanita_mentale>50){
                        giocatori[i].sanita_mentale-=50;
                      }else{
                        giocatori[i].stato=0;
                        for(int y=0;y<4; y++){
                        if(giocatori[i].zaino[y]==emf || giocatori[i].zaino[y]==spirit_box || giocatori[i].zaino[y]==videocamera){
                          appoggioMappa=giocatori[i].posizione;
                          appoggioMappa->oggetto_zona=giocatori[i].zaino[y]; //quando il giocatore muore è possiede
                                                                             // un oggetto per raccogliere le prove
                        }                                                    // quel oggetto viene lascitato come oggetto
                                                                             // nella zona per poter continuare a giocare
                        }
                      }
                      }
                    }
                    break;
                  }
                }

            break;
            case 2:
            spawn_fantasma=rand()%100;
              if(somma1==1){
              spawn_fantasma=rand()%100;
              switch (spawn_fantasma) {
                case 0 ... 40:
                fantasma=1;
                printf("BOOO ANDATEVENE DA CASA MIA..\n");
                appoggioMappa=giocatori[p].posizione;
                for (int i = 0; i < num_giocatori; i++) {
                  if(giocatori[i].posizione==appoggioMappa){
                    giocatori[i].sanita_mentale-=30;
                  }
                }
                break;
              }
              }
              if(somma1==2){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 50:
                  fantasma=1;
                  printf("IL MIO POTERE AUMENTA OGNI VOLTA CHE MI VEDETE\n" );
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      giocatori[i].sanita_mentale-=40;
                    }
                  }
                  break;
                }
              }
              if(somma1==3){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 70:
                  fantasma=1;
                  printf("LASCIATEMI IN PACE O PAGHERETE LE CONSEGUENZE \n");
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      if(giocatori[i].sanita_mentale>50){
                      giocatori[i].sanita_mentale-=50;
                      }else{
                        giocatori[i].stato=0;
                        for(int y=0;y<4; y++){
                        if(giocatori[i].zaino[y]==emf || giocatori[i].zaino[y]==spirit_box || giocatori[i].zaino[y]==videocamera){
                          appoggioMappa=giocatori[i].posizione;
                          appoggioMappa->oggetto_zona=giocatori[i].zaino[y]; //quando il giocatore muore è possiede
                                                                             // un oggetto per raccogliere le prove
                        }                                                    // quel oggetto viene lascitato come oggetto
                                                                             // nella zona per poter continuare a giocare
                        }
                    }
                    }
                  }
                  break;
                }
              }

            break;
            case 3:
            spawn_fantasma=rand()%100;
              if(somma1==1){
              spawn_fantasma=rand()%100;
              switch (spawn_fantasma) {
                case 0 ... 50:
                fantasma=1;
                printf("BOOO ANDATEVENE DA CASA MIA..\n");
                appoggioMappa=giocatori[p].posizione;
                for (int i = 0; i < num_giocatori; i++) {
                  if(giocatori[i].posizione==appoggioMappa){
                    giocatori[i].sanita_mentale-=40;
                  }
                }
                break;
              }
              }
              if(somma1==2){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 65:
                  fantasma=1;
                  printf("IL MIO POTERE AUMENTA OGNI VOLTA CHE MI VEDETE.\n" );
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      giocatori[i].sanita_mentale-=50;
                    }
                  }
                  break;
                }
              }
              if(somma1==3){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 80:
                  fantasma=1;
                  printf("LASCIATEMI IN PACE O PAGHERETE LE CONSEGUENZE \n");
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      if(giocatori[i].sanita_mentale>60){
                      giocatori[i].sanita_mentale-=60;
                    }else{
                      giocatori[i].stato=0;
                      for(int y=0;y<4; y++){
                      if(giocatori[i].zaino[y]==emf || giocatori[i].zaino[y]==spirit_box || giocatori[i].zaino[y]==videocamera){
                        appoggioMappa=giocatori[i].posizione;
                        appoggioMappa->oggetto_zona=giocatori[i].zaino[y]; //quando il giocatore muore è possiede
                                                                           // un oggetto per raccogliere le prove
                      }                                                    // quel oggetto viene lascitato come oggetto
                                                                           // nella zona per poter continuare a giocare
                      }
                    }
                    }
                  }
                  break;
                }
              }

            break;
          }
        }else{
          printf("Non è presente nessuna prova!! \n");
        }
        break;
        case 2:
        flag=1;
        if(appoggioMappa->prova==11){
          printf("Hai racolto la prova Videocamera \n");
          giocatori[p].zaino[y]=prova_videocamera;
          raccolta_video=1;
          somma1=raccolta_emf+raccolta_spirit+raccolta_video;
          switch (difficolta) {
            case 1:
              spawn_fantasma=rand()%100;
                if(somma1==1){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 30:
                  fantasma=1;
                  printf("BOOO ANDATEVENE DA CASA MIA..\n");
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      giocatori[i].sanita_mentale-=20;
                    }
                  }
                  break;
                }
                }
                if(somma1==2){
                  spawn_fantasma=rand()%100;
                  switch (spawn_fantasma) {
                    case 0 ... 40:
                    fantasma=1;
                    printf("IL MIO POTERE AUMENTA OGNI VOLTA CHE MI VEDETE.\n" );
                    appoggioMappa=giocatori[p].posizione;
                    for (int i = 0; i < num_giocatori; i++) {
                      if(giocatori[i].posizione==appoggioMappa){
                        giocatori[i].sanita_mentale-=30;
                      }
                    }
                    break;
                  }
                }
                if(somma1==3){
                  spawn_fantasma=rand()%100;
                  switch (spawn_fantasma) {
                    case 0 ... 60:
                    fantasma=1;
                    printf("LASCIATEMI IN PACE O PAGHERETE LE CONSEGUENZE \n");
                    appoggioMappa=giocatori[p].posizione;
                    for (int i = 0; i < num_giocatori; i++) {
                      if(giocatori[i].posizione==appoggioMappa){
                        if(giocatori[i].sanita_mentale>50){
                        giocatori[i].sanita_mentale-=50;
                      }else{
                        giocatori[i].stato=0;
                        for(int y=0;y<4; y++){
                        if(giocatori[i].zaino[y]==emf || giocatori[i].zaino[y]==spirit_box || giocatori[i].zaino[y]==videocamera){
                          appoggioMappa=giocatori[i].posizione;
                          appoggioMappa->oggetto_zona=giocatori[i].zaino[y]; //quando il giocatore muore è possiede
                                                                             // un oggetto per raccogliere le prove
                        }                                                    // quel oggetto viene lascitato come oggetto
                                                                             // nella zona per poter continuare a giocare
                        }
                      }
                      }
                    }
                    break;
                  }
                }




            break;
            case 2:
            spawn_fantasma=rand()%100;
              if(somma1==1){
              spawn_fantasma=rand()%100;
              switch (spawn_fantasma) {
                case 0 ... 40:
                fantasma=1;
                printf("BOOO ANDATEVENE DA CASA MIA..\n");
                appoggioMappa=giocatori[p].posizione;
                for (int i = 0; i < num_giocatori; i++) {
                  if(giocatori[i].posizione==appoggioMappa){
                    giocatori[i].sanita_mentale-=30;
                  }
                }
                break;
              }
              }
              if(somma1==2){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 50:
                  fantasma=1;
                  printf("IL MIO POTERE AUMENTA OGNI VOLTA CHE MI VEDETE\n" );
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      giocatori[i].sanita_mentale-=40;
                    }
                  }
                  break;
                }
              }
              if(somma1==3){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 70:
                  fantasma=1;
                  printf("LASCIATEMI IN PACE O PAGHERETE LE CONSEGUENZE \n");
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      if(giocatori[i].sanita_mentale>50){
                      giocatori[i].sanita_mentale-=50;
                    }else{
                      giocatori[i].stato=0;
                      for(int y=0;y<4; y++){
                      if(giocatori[i].zaino[y]==emf || giocatori[i].zaino[y]==spirit_box || giocatori[i].zaino[y]==videocamera){
                        appoggioMappa=giocatori[i].posizione;
                        appoggioMappa->oggetto_zona=giocatori[i].zaino[y]; //quando il giocatore muore è possiede
                                                                           // un oggetto per raccogliere le prove
                      }                                                    // quel oggetto viene lascitato come oggetto
                                                                           // nella zona per poter continuare a giocare
                      }
                    }
                    }
                  }
                  break;
                }
              }

            break;
            case 3:
              if(somma1==1){
              spawn_fantasma=rand()%100;
              switch (spawn_fantasma) {
                case 0 ... 50:
                fantasma=1;
                printf("BOOO ANDATEVENE DA CASA MIA..\n");
                appoggioMappa=giocatori[p].posizione;
                for (int i = 0; i < num_giocatori; i++) {
                  if(giocatori[i].posizione==appoggioMappa){
                    giocatori[i].sanita_mentale-=40;
                  }
                }
                break;
              }
              }
              if(somma1==2){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 65:
                  fantasma=1;
                  printf("IL MIO POTERE AUMENTA OGNI VOLTA CHE MI VEDETE\n" );
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      giocatori[i].sanita_mentale-=50;
                    }
                  }
                  break;
                }
              }
              if(somma1==3){
                spawn_fantasma=rand()%100;
                switch (spawn_fantasma) {
                  case 0 ... 80:
                  fantasma=1;
                  printf("LASCIATEMI IN PACE O PAGHERETE LE CONSEGUENZE \n");
                  appoggioMappa=giocatori[p].posizione;
                  for (int i = 0; i < num_giocatori; i++) {
                    if(giocatori[i].posizione==appoggioMappa){
                      if(giocatori[i].sanita_mentale>60){
                      giocatori[i].sanita_mentale-=60;
                    }else{
                      giocatori[i].stato=0;
                      for(int y=0;y<4; y++){
                      if(giocatori[i].zaino[y]==emf || giocatori[i].zaino[y]==spirit_box || giocatori[i].zaino[y]==videocamera){
                        appoggioMappa=giocatori[i].posizione;
                        appoggioMappa->oggetto_zona=giocatori[i].zaino[y]; //quando il giocatore muore è possiede
                                                                           // un oggetto per raccogliere le prove
                      }                                                    // quel oggetto viene lascitato come oggetto
                                                                           // nella zona per poter continuare a giocare
                      }
                    }
                    }
                  }
                  break;
                }
              }

            break;
          }
        }else{
          printf("Non è presente nessuna prova!! \n");
        }
        break;

      }
      }
      if(flag==0){
        printf("Non possiedi l'oggetto necessario per raccogliere la prova \n" );
        }
        return fantasma;
      }
      void raccogli_oggetto(int p ){
        int oggetto,flag=0;
        appoggioMappa=NULL;
        appoggioMappa=giocatori[p].posizione;
        for (int y = 0; y < 4; y++) {
          oggetto=giocatori[p].zaino[y];
          switch (oggetto) {
            case 8:
            flag=1;
            if(appoggioMappa->oggetto_zona!=8){
              printf("Hai racolto l'oggetto presente nella zona \n");
              giocatori[p].zaino[y]=appoggioMappa->oggetto_zona;
              appoggioMappa->oggetto_zona=nessun_oggetto;
              flag=2;
            }else{
              printf("Non è presente nessuna oggetto raccoglibile!! \n");
              y=4;//se non e presente nessuno oggetto esce subito dal ciclo for
            }
            break;
          }
          if (flag==2) {
            y=4; //se l'oggetto è stato raccolto esce subito dal ciclo for
          }
          }
          if(flag==0){
            printf("Zaino pieno\n" );
            }
          }

        void usa_oggetto(int p,int num_giocatori){
          char scelta=0;
          int oggetto,contatore=0,g=0,contatore2=0,flag=0,flag2=0;
          for (int y = 0; y < 4; y++) {
            oggetto=giocatori[p].zaino[y];
          switch(oggetto){
            case 8:
            contatore=contatore+1;
            break;
          }
        }
        if(contatore==4){
          printf("Il tuo zaino è vuoto \n");
        }else{
          do{
          printf("Quale oggetto vuoi usare: \n");
              printf("[C]per i calmanti \n");
              printf("[S]per il sale \n");
              printf("[A]per l'adrenalina \n");
              printf("[D]per i cento dollari \n");
              printf("[X]per il coltello \n");
              printf("Inserire la scelta:");
              scanf("%c", &scelta);
              while((getchar()) != '\n');
              switch (scelta) {
          case 'C':
          case 'c':
              contatore=0;
              for(int i=0;i<4;i++){
                if(giocatori[p].zaino[i]==calmanti){
                  flag2=1;
              if(giocatori[p].sanita_mentale==100){
                printf("Hai la sanita mentale massima \n");
                }else{
                if(giocatori[p].sanita_mentale>=60){
                giocatori[p].sanita_mentale=100;// se la sanita mentale e maggiore o uguale a 60
                                                //viene impostata la sanita mentale massima
              }else{
                giocatori[p].sanita_mentale+=40;
              }
                giocatori[p].zaino[i]=8; //rimuovo l'oggetto utilizzato
              }
            }else{
            contatore2=contatore2+1;
            }
            if(flag2==1){ // se il giocatore ha due oggetti uguali se ne utilizza uno solo
              i=4;        // è quindi si esce dal ciclo che controllo lo zaino del giocatore
            }
              }
              if(contatore2==4){
                printf("Non possiedi l'oggetto nello zaino \n");
              }
              break;
              case 'S':
              case 's':
              contatore2=0;
              for(int i=0;i<4;i++){
                if(giocatori[p].zaino[i]==sale){
                  //da completare
              }else{
                contatore2=contatore2+1;
              }
              }
              if(contatore2==4){
                printf("Non possiedi l'oggetto nello zaino \n");
              }
              break;
              case 'A':
              case 'a':
              contatore2=0;
              flag2=0;
              for(int i=0;i<4;i++){
                if(giocatori[p].zaino[i]==adrenalina){
                  flag2=1;
                  avanza_counter=avanza_counter+1;
                  giocatori[p].zaino[i]=nessun_oggetto;
              }else{
                contatore2=contatore2+1;
              }
              if(flag2==1){
                i=4;
              }
              }
              if(contatore2==4){
                printf("Non possiedi l'oggetto nello zaino \n");
              }
              break;
              case 'D':
              case 'd':
              contatore2=0;

              for(int i=0;i<4;i++){
                if(giocatori[p].zaino[i]==cento_dollari){
                  g=rand()%2;
                  if(g==0){
                    giocatori[p].zaino[i]=sale;
                    printf("Hai ricevuto del sale \n");
                  }else{
                    giocatori[p].zaino[i]=calmanti;
                    printf("Hai ricevuto un calmante\n");
                  }
              }else{
                contatore2=contatore2+1;
              }
              }
              if(contatore2==4){
                printf("Non possiedi l'oggetto nello zaino \n");
              }
              break;
              case 'X':
              case 'x':
              contatore2=0;
              for(int i=0;i<4;i++){
                if(giocatori[p].zaino[i]==coltello){

                  if(giocatori[p].sanita_mentale<30){
                  for (int i = 0; i < num_giocatori; i++) {
                    if(memcmp(&giocatori[p],&giocatori[i], sizeof(struct Giocatore)) != 0){
                      if(giocatori[i].posizione==giocatori[p].posizione){
                        giocatori[i].stato=0;// Il giocatore è morto
                        for(int y=0;y<4; y++){
                        if(giocatori[i].zaino[y]==emf || giocatori[i].zaino[y]==spirit_box || giocatori[i].zaino[y]==videocamera){
                          appoggioMappa=giocatori[i].posizione;
                          appoggioMappa->oggetto_zona=giocatori[i].zaino[y]; //quando il giocatore muore è possiede
                                                                             // un oggetto per raccogliere le prove
                        }                                                    // almeno un'oggetto viene lascitato come oggetto
                                                                             // nella zona per poter continuare a giocare
                        }// Il giocatore è morto
                      }
                    }
                  }
                }else{
                  printf("Non puoi usare questo oggetto!! \n");
                }
              }else{
                contatore2=contatore2+1;
              }
              }
              if(contatore2==4){
                printf("Non possiedi l'oggetto nello zaino \n");
              }
              break;
              default:
              printf("Valore errato \n");
              flag=1;
              break;
            }


        }while (flag==1);
        }
      }

      void avanza(int p){
        int prova_spawn=0,oggetto_spawn=0;
        prova_spawn=rand()%100;
        oggetto_spawn=rand()%100;
        appoggioMappa=giocatori[p].posizione;
        appoggioMappa=appoggioMappa->prossima_zona;
        giocatori[p].posizione=appoggioMappa;
        printf("\e[1;1H\e[2J \n" );
        printf("Stai attento ai fantasmi..\n");
        switch (prova_spawn) {
          case 0 ... 39:
          printf("Non è apparsa nessuna prova\n");
          appoggioMappa->prova=nessuna_prova;
          break;
          case 40 ... 59:
          printf( "E' apparsa la prova Videocamera \n");
          appoggioMappa->prova=prova_videocamera;
          break;
          case 60 ... 79:
          printf( "E' apparsa la prova Spirit Box \n");
          appoggioMappa->prova=prova_spirit_box;
          break;
          case 80 ... 99:
          printf( "E' apparsa la prova EMF \n");
          appoggioMappa->prova=prova_emf;
          break;
        }
        switch (oggetto_spawn) {
          case 0 ... 69:
          appoggioMappa->oggetto_zona=nessun_oggetto;
          break;
          case 70 ... 79:
          appoggioMappa->oggetto_zona=adrenalina;
          break;
          case 80 ... 89:
          appoggioMappa->oggetto_zona=cento_dollari;
          break;
          case 90 ... 99:
          appoggioMappa->oggetto_zona=coltello;
          break;
        }


      }
      static void deallocalista(){ //funzione che scorre la lista stanze e dealloca la memoria allocata
        free(giocatori);//dealloco la memoria allocata per l'array di giocatori
        free(zonaCaravan);//dealloco la zona del caravan perchè non trovandosi nella lista la devo liberare a parte
        conteggioMappa= primaMappa;
        while (conteggioMappa != primaMappa) { //da aggiustare 
          struct Zona_Mappa* appoggio = conteggioMappa;
          conteggioMappa = conteggioMappa->prossima_zona;
          free(appoggio);  //dealloco le zone dalla mappa
        }
      }
