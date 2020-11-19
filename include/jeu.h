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

#ifndef JEU
#define JEU

#include "../include/structure.h"

extern void affiche_ligne(int i,int damier[8][8]) ;

extern void affiche_damier(int damier[8][8]) ;

extern void init_damier(damier *jeu) ;

extern int coup_gagnant(int dd[8][8], deplacement c, int J) ;

extern deplacement cp_gagnant_obligatoire(int dd[8][8], int J, deplacement c) ;

extern int trouve_gagnant(int dd[8][8], int J) ;

extern int fin_jeu(int dd[8][8]) ;

extern void arbitre (int J, damier *jeu, char tab[128], deplacement d, int possible) ;

extern int coup_possible(int J,deplacement c,damier *jeu, char tab[128], int possible, Case *adv, int prise) ;

extern void deplace_pion(int J,deplacement d,int prise,damier *jeu, Case p) ;

extern void faire_deplacement(int J,deplacement c, damier *jeu,char tab[128], int possible, Case adv) ;

#endif
