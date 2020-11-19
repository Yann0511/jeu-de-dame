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


#ifndef _IA_H_
#define _IA_H_

#include "../include/structure.h"
/*#include "coup.h"
#include "joue_rafle.h"
#include "listes.h"*/

//les listes
extern Liste creer_liste_vide(void) ;

extern Liste inserer_tete(Liste l, deplacement x, int y) ;

extern int rechercher(Liste l, deplacement x, int mode) ;

extern void afficher_liste_inverse(Liste l) ;

extern void afficher_liste_inverse_principal(Liste l);

extern Liste supprimer_tete(Liste l) ;

extern int rechercher_prio_max(Liste l, int mode, int prio) ;

extern Liste copie_liste(Liste a_copie, Liste copie) ;

extern void init_tab_liste(Liste l[50], int x) ;

extern void init_un_int_tab(int tab[50], int x) ;
//fin listes

//les coup
extern int recherche_rafle_pion (int damier[8][8], int ligne, int colonne,
                           int pion, Liste coups_trouve,
                           Liste coups_possible[50], int nb_coups_possible, int nb_deplacement) ;

extern int recherche_rafle_dame (int damier[8][8], int ligne, int colonne,
                           int pion, Liste coups_trouve,
                           Liste coups_possible[50], int nb_coups_possible, int nb_deplacement) ;

extern int recherche_pion (int damier[8][8], Liste coups_obligatoire[50], int joueur,int couleur) ;

extern int recherche_coup_obligatoire(Liste coups_obligatoire[50], Liste coups_possible[50], int nb_coup_possible) ;
//fin coup

//joue rafle

extern void joue_rafle_cpu( int damier[N][N], Liste coup_a_jouer_inversee );
//fin joue rafle

//minimax
extern void appel_minimax (int damier[N][N], int prof, Liste coup_a_jouer[1],int joueur);
	// Cette fonction est celle à appeler dans le main, elle permet juste d'éviter d'oublier qu'il faut appeler un max en premier

extern int minimax (int damier[N][N], int prof, int flag, Liste coup_a_jouer[1],int joueur);
	// Fonction principale du minimax. On utilise un tableau de 1 liste pour pouvoir utiliser la fonction joue_rafle, qui prend comme arg un Liste[][]
	// De part la nature des diverses fonctions et du minimax lui même, il est NECESSAIRE D'APPELER MINIMAX SUR UNE PROFONDEUR IMPAIRE

extern int eval(int damier[N][N], int joueur);
	// Fonction d'appel et de combinaison des fonctions d'évaluation.

extern int eval_pions(int damier[N][N],int joueur);
	// Fonction d'évaluation de la position des pions

extern int eval_dames(int damier[N][N],int joueur);
	// Fonction d'évaluation de la position des dames

extern int eval_nbdames(int damier[N][N],int joueur);
    // Fonction d'évaluation du nombre de dames

extern void copie_damier(int damier1[N][N], int damier2[N][N]);
	// Fonction necessaire pour le minimax (il ne faudrait pas écraser le damier de jeu... donc on copie le damier !)

//fin minimax
#endif
