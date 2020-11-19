/////////////////////////////////////////////////////////////////
//                                                             //
//                    Projet de Langage C                      //
//                                                             //
//                         Jeu de dames                        //
//                    Supervisé par Mr SOUDE                   //
//                                                             //
//  Etudiants: DEGBEGNI Moulero Andy et OLOU Yann Kelly        //
//                                                             //
/////////////////////////////////////////////////////////////////
//                                                             //
//                    Classe Préparatoire 1                    //
/**                         IMSP - UAC                        **/
//                                                             //
/////////////////////////////////////////////////////////////////



#ifndef giflele
#define giflele
# define N 8
# define M 50
#define PION_BLANC 1
#define DAME_BLANC 2
#define PION_NOIR -1
#define DAME_NOIR -2
#define CASE_VIDE 0
#define HUMAIN 1
#define CPU 2
#define MAX 1
#define MIN 0


/*La structure Case, qui symbolise une case,
 elle a donc pour élément deux entiers, 
 un pour la ligne,un autre pour la colonne :*/
typedef struct Case {
int lig,col ;
}Case;


/* La structure deplacement, qui symbolise un
   deplacement, cette structure possède deux éléments,
   deux case, une étant la case initiale, l’autre la case finale :*/
typedef struct deplacement
{
  Case case_i,case_f,case_cible ;
}deplacement;


/*La structure element, qui est un élément d’une liste chaînée.
 Enzffet, dans notre programme, pour représenté les rafles,
 nous avons choisis d’utiliser comme structure de données les listes chaînées.*/

typedef struct element *listeCases ;
struct element 
{
  Case c ;
  listeCases suivante ;
}element;


/*La structure joueur, qui symbolise un joueur,
 elle a pour élément le nom du joueur, son type CPU
 ou HUMAIN, ainsi que la couleur des pions du joueurs :*/
typedef struct joueur 
{
  char *nom ;
  int type ;
  int couleur ;
}joueur;

/* La structure damier, qui symbolise la jeu,
    elle contient le nombre de pions de chaque couleur, et un
    tableau représentant la position des pions sur le plateau :*/
typedef struct damier {
int plateau[8][8] ; // Représente l’état duplateau
int nb_noir ;
// Représente le nombre de pion noir
int nb_blanc ;
// Représente le nombre de pion blanc
}damier;

struct maillon
{
    deplacement dep ;
    int priorite ;
    struct maillon *pred, *suiv ;
} ;

typedef struct maillon tmaillon ;

typedef tmaillon *Liste ;
#endif
