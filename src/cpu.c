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


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include"../include/ia.h"

// les listes

//intitialisation
void init_tab_liste(Liste l[], int x)
{
    int i ;
    Liste m = creer_liste_vide() ;
    for (i=0; i<x; i++)
        l[i] = copie_liste(m, l[i]);
}

void init_un_int_tab(int tab[], int x){

    int i;
    for (i=0; i<x; i++)
    {
        tab[i]=1;
    }
}

//fin initialisation


Liste creer_liste_vide(void)
{
  return((Liste)NULL) ;
}

Liste inserer_tete(Liste l, deplacement x, int y)
/*
insere l'entier x dans la liste l et retourne la liste
resultat
*/
{
    Liste aux ;

    aux = (Liste)malloc(sizeof(tmaillon)) ;
    aux->dep.case_i.col = x.case_i.col ;
    aux->dep.case_i.lig = x.case_i.lig ;
    aux->dep.case_cible.col = x.case_cible.col ;
    aux->dep.case_cible.lig = x.case_cible.lig ;
    aux->dep.case_f.col = x.case_f.col ;
    aux->dep.case_f.lig = x.case_f.lig ;
    aux->priorite = y ;

    if (l == NULL)
    {
        aux->pred = NULL ;
        aux->suiv = NULL ;
    }
    else
    {
        aux->pred = NULL ;
        aux->suiv = l ;
    }
     return(aux) ;
}

int rechercher(Liste l, deplacement x, int mode)
/*
mode = 0 recherche dans case_debut, mode = 1 recherche dans case cible
*/
{

    Liste p = l ;
	int ret;
    if (mode == 0)
    {
        if (l == NULL)
            return (0) ;
        while (((p->dep.case_i.col != x.case_f.col) ||
               (p->dep.case_i.lig != x.case_f.lig)) &&
               (p->suiv!=NULL))
        {
            p=p->suiv ;
        }
        if ( p->dep.case_i.col == x.case_f.col &&
                 p->dep.case_i.lig == x.case_f.lig )
            ret=1 ;
        else
            ret=0 ;
    }
    if (mode == 1)
    {
        if (l == NULL)
            return (0) ;
        while (((p->dep.case_cible.col != x.case_cible.col) ||
               (p->dep.case_cible.lig != x.case_cible.lig)) &&
               (p->suiv!=NULL))
        {
            p=p->suiv ;
        }
        if ( p->dep.case_cible.col == x.case_cible.col &&
                 p->dep.case_cible.lig == x.case_cible.lig )
            ret=1 ;
        else
            ret=0 ;
    }
	return (ret);
}

void afficher_liste_inverse(Liste l)
{
    afficher_liste_inverse_principal(l) ;
    printf("\n") ;
}

void afficher_liste_inverse_principal(Liste l)
/*
affiche les elements de la liste l dans l'ordre inverse
*/
{
     if (l != NULL)
    {

		    afficher_liste_inverse_principal(l->suiv) ;
            printf("(%c, %c)->(%c, %c)  ",l->dep.case_i.lig + 'a', l->dep.case_i.col + '1',
                                          l->dep.case_f.lig + 'a', l->dep.case_f.col + '1') ;
	}
    return ;
}

Liste supprimer_tete(Liste l)
/* Supprime l'element en tete de la liste l et retourne
  la liste resultat
*/
{
   Liste p ;

   if (l==NULL)
      return (l) ;
   if (l->pred==NULL && l->suiv==NULL)
      {
        free(l) ;
        return(NULL) ;
      }
   p = l->suiv ;
   p->pred = NULL ;
   free(l) ;
   return(p) ;
}

int rechercher_prio_max(Liste l, int mode, int prio)
/*
retourne la valeur de priorité la plus grande
Mode : 0 : recherche la priorité max de la liste; 1 : verifie si prio est dans la liste
*/
{
    Liste p = l ;
    int aux = prio ;

    if (mode == 0)
    {
        if (l == NULL)
            return (-1) ;
        do
        {
            if ( p->priorite > aux)
            {
                aux = p->priorite ;
            }
                p=p->suiv ;
        } while (p!=NULL) ;
        return (aux) ;
    }

    else //mode == 1
    {
        if (l == NULL) return (0) ;
        while ((p->priorite != prio) &&
               (p->suiv!=NULL))
        {
            p=p->suiv ;
        }
        if ( p->priorite == prio )
            return(1) ;
        else
            return(0) ;
    }
}

Liste copie_liste(Liste a_copie, Liste copie)
{
 /*
  Copie la liste et la retourne dans une nouvelle
  */
    deplacement y ;
    int x ;
    Liste p = a_copie ;
	copie = creer_liste_vide();
	if(p!=NULL)
	{
		while (p != (Liste)NULL)
		{
			y.case_i.col = p->dep.case_i.col ;
			y.case_i.lig = p->dep.case_i.lig ;
            y.case_cible.col = p->dep.case_cible.col ;
			y.case_cible.lig = p->dep.case_cible.lig ;
			y.case_f.col = p->dep.case_f.col ;
			y.case_f.lig = p->dep.case_f.lig ;
			x = p->priorite ;

			copie = inserer_tete(copie, y, x) ;

			p= p->suiv ;
		}

		return (copie) ;
	}
	else
		return(NULL);
}

//fin des listes

//les coups

int recherche_pion (int damier[N][N], Liste coups_obligatoires[M], int joueur, int couleur)   //joueur : 1 pour J1(blanc) et 2 pour J2(noir)
{
  /*
   Recherche tout les pions du joueur qui possede le trait, afin de lancer la recherche des rafles a partir de ce pion
  */
    int i, j, pion ;
    int nb_coups_possibles = 0 ;

    Liste coups_trouves = creer_liste_vide() ;
    Liste coups_possibles[50] ; //contiendra tout les coups possibles

    /** On réinitialise nos tableaux � changement de joueur **/
    init_tab_liste(coups_possibles, M) ;
    init_tab_liste(coups_obligatoires, M) ;


    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            pion = damier[i][j] ;
            if (joueur == 1)
            {
                if (pion== -couleur)
                    nb_coups_possibles = recherche_rafle_pion(damier, i, j, pion, coups_trouves,
                                                       coups_possibles, nb_coups_possibles, 0 ) ;
                else if (pion == -2*couleur)
                    nb_coups_possibles = recherche_rafle_dame(damier, i, j, pion, coups_trouves,
                                                       coups_possibles, nb_coups_possibles, 0 ) ;
            }
            else
            {
                if (pion == couleur)
                    nb_coups_possibles = recherche_rafle_pion(damier, i, j, pion, coups_trouves,
                                                       coups_possibles, nb_coups_possibles, 0 ) ;
                else if (pion == 2*couleur)
                    nb_coups_possibles = recherche_rafle_dame(damier, i, j, pion, coups_trouves,
                                                       coups_possibles, nb_coups_possibles, 0 ) ;
            }
        }
    }
    //On aura plus besoin de nb_coups_possibles donc on peux le réutiliser
    nb_coups_possibles = recherche_coup_obligatoire(coups_obligatoires, coups_possibles, nb_coups_possibles) ;

    return nb_coups_possibles ;
}

int recherche_rafle_pion (int damier[N][N], int ligne, int colonne,
                          int pion, Liste coups_trouves,
                          Liste coups_possibles[50], int nb_coups_possibles, int nb_deplacement)
{
  /*
   Pour chaques pions trouvés on répertorie toutes les rafles possibles
   */
    Case test_dep ;
    deplacement mouv ;
    int cellule ; // cases que l'on teste
    int recherche ; // resultat de la recherche

    mouv.case_i.col = colonne ;
    mouv.case_i.lig = ligne ;
    /****
    Recherche des coups possibles pour les pions
    ****/

        /***    test diag sup gauche    ***/
        mouv.case_cible.col = colonne-1 ;
        mouv.case_cible.lig= ligne -1 ;

        if (mouv.case_cible.col>=0 && mouv.case_cible.lig>=0)
        {
            cellule = damier[mouv.case_cible.lig][mouv.case_cible.col] ;

            //Si la case est vide et qu'on a pas fait de déplacement
            if (pion == PION_BLANC && cellule == CASE_VIDE && nb_deplacement == 0)
            {
                mouv.case_f.lig = mouv.case_cible.lig ;
                mouv.case_f.col = mouv.case_cible.col ;
                coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves, coups_possibles[nb_coups_possibles]) ;
                nb_coups_possibles++ ;
                coups_trouves = supprimer_tete(coups_trouves) ;
            }
            //Sinon il faut que la case soit occupée par l'adversaire
            else if ( ( pion == PION_BLANC && (cellule == PION_NOIR || cellule == DAME_NOIR)) ||
                      ( pion == PION_NOIR && (cellule == PION_BLANC || cellule == DAME_BLANC)) )
            {
                recherche = rechercher(coups_trouves, mouv, 1) ;
                if (recherche == 0)
                {
                    test_dep.col = colonne-2 ;
                    test_dep.lig = ligne -2 ;

                    if (test_dep.col>=0 && test_dep.lig>=0 )
                    {
                        cellule = damier[test_dep.lig][test_dep.col] ;
                        mouv.case_f.col = test_dep.col ;
                        mouv.case_f.lig = test_dep.lig ;
                        recherche = rechercher(coups_trouves, mouv, 0) ;
                        //Verification que la cellule d'arrivée soit bien vide
                        if (cellule == CASE_VIDE || (cellule == pion && recherche == 1))
                        {
                            nb_deplacement++ ;

                            coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;

                            nb_coups_possibles = recherche_rafle_pion (damier, test_dep.lig, test_dep.col,
                                                                pion, coups_trouves, coups_possibles,
                                                                nb_coups_possibles, nb_deplacement) ;
                            nb_deplacement-- ;
                            coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves,
                                                                                coups_possibles[nb_coups_possibles]) ;
                            nb_coups_possibles++ ;
                            coups_trouves = supprimer_tete(coups_trouves) ;
                        }
                    }
                }
            }
        }


        /***    test diag sup droite    ***/
        mouv.case_cible.col = colonne+1 ;
        mouv.case_cible.lig= ligne -1 ;

        if (mouv.case_cible.col<N && mouv.case_cible.lig>=0)
        {
            cellule = damier[mouv.case_cible.lig][mouv.case_cible.col] ;

            if (pion == PION_BLANC && cellule == CASE_VIDE && nb_deplacement == 0)
            {
                mouv.case_f.lig = mouv.case_cible.lig ;
                mouv.case_f.col = mouv.case_cible.col ;
                coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves, coups_possibles[nb_coups_possibles]) ;
                nb_coups_possibles++ ;
                coups_trouves = supprimer_tete(coups_trouves) ;

            }
            else if ( ( pion == PION_BLANC && (cellule == PION_NOIR || cellule == DAME_NOIR)) ||
                      ( pion == PION_NOIR && (cellule == PION_BLANC || cellule == DAME_BLANC)) )
            {
                recherche = rechercher(coups_trouves, mouv, 1) ;
                if (recherche == 0)
                {
                    test_dep.col = colonne+2 ;
                    test_dep.lig = ligne -2 ;

                    if (test_dep.col<N && test_dep.lig>=0 )
                    {
                        cellule = damier[test_dep.lig][test_dep.col] ;
                        mouv.case_f.col = test_dep.col ;
                        mouv.case_f.lig = test_dep.lig ;
                        recherche = rechercher(coups_trouves, mouv, 0) ;
                        if (cellule == CASE_VIDE || (cellule == pion && recherche == 1))
                        {
                            nb_deplacement++ ;
                            coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;

                            nb_coups_possibles = recherche_rafle_pion (damier, test_dep.lig, test_dep.col,
                                                                pion, coups_trouves, coups_possibles,
                                                                nb_coups_possibles, nb_deplacement) ;
                            nb_deplacement-- ;
                            coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves,
                                                                                coups_possibles[nb_coups_possibles]) ;
                            nb_coups_possibles++ ;
                            coups_trouves = supprimer_tete(coups_trouves) ;
                        }
                    }
                }
            }
        }


        /***    test diag inf droite    ***/
        mouv.case_cible.col = colonne+1 ;
        mouv.case_cible.lig= ligne +1 ;

        if (mouv.case_cible.col<N && mouv.case_cible.lig<N)
        {
            cellule = damier[mouv.case_cible.lig][mouv.case_cible.col] ;

            if (pion == PION_NOIR && cellule == CASE_VIDE && nb_deplacement == 0)
            {
                mouv.case_f.lig = mouv.case_cible.lig ;
                mouv.case_f.col = mouv.case_cible.col ;
                coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves, coups_possibles[nb_coups_possibles]) ;
                nb_coups_possibles++ ;
                coups_trouves = supprimer_tete(coups_trouves) ;

            }
            else if ( ( pion == PION_BLANC && (cellule == PION_NOIR || cellule == DAME_NOIR)) ||
                      ( pion == PION_NOIR && (cellule == PION_BLANC || cellule == DAME_BLANC)) )
            {
                recherche = rechercher(coups_trouves, mouv, 1) ;
                if (recherche == 0)
                {
                    test_dep.col = colonne+2 ;
                    test_dep.lig = ligne +2 ;

                    if (test_dep.col<N && test_dep.lig<N )
                    {
                        cellule = damier[test_dep.lig][test_dep.col] ;
                        mouv.case_f.col = test_dep.col ;
                        mouv.case_f.lig = test_dep.lig ;
                        recherche = rechercher(coups_trouves, mouv, 0) ;
                        if (cellule == CASE_VIDE || (cellule == pion && recherche == 1))
                        {
                            nb_deplacement++ ;
                            coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;

                            nb_coups_possibles = recherche_rafle_pion (damier, test_dep.lig, test_dep.col,
                                                                pion, coups_trouves, coups_possibles,
                                                                nb_coups_possibles, nb_deplacement) ;
                            nb_deplacement-- ;
                            coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves,
                                                                                coups_possibles[nb_coups_possibles]) ;
                            nb_coups_possibles++ ;
                            coups_trouves = supprimer_tete(coups_trouves) ;
                        }
                    }
                }
            }
        }


        /***    test diag inf gauche    ***/
        mouv.case_cible.col = colonne-1 ;
        mouv.case_cible.lig= ligne +1 ;

        if (mouv.case_cible.col>=0 && mouv.case_cible.lig<N)
        {
            cellule = damier[mouv.case_cible.lig][mouv.case_cible.col] ;

            if (pion == PION_NOIR && cellule == CASE_VIDE && nb_deplacement == 0)
            {
                mouv.case_f.lig = mouv.case_cible.lig ;
                mouv.case_f.col = mouv.case_cible.col ;
                coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves, coups_possibles[nb_coups_possibles]) ;
                nb_coups_possibles++ ;
                coups_trouves = supprimer_tete(coups_trouves) ;

            }
            else if ( ( pion == PION_BLANC && (cellule == PION_NOIR || cellule == DAME_NOIR)) ||
                      ( pion == PION_NOIR && (cellule == PION_BLANC || cellule == DAME_BLANC)) )
            {
                recherche = rechercher(coups_trouves, mouv, 1) ;
                if (recherche == 0)
                {
                    test_dep.col = colonne-2 ;
                    test_dep.lig = ligne +2 ;

                    if (test_dep.col>=0 && test_dep.lig<N )
                    {
                        cellule = damier[test_dep.lig][test_dep.col] ;
                        mouv.case_f.col = test_dep.col ;
                        mouv.case_f.lig = test_dep.lig ;
                        recherche = rechercher(coups_trouves, mouv, 0) ;
                        if (cellule == CASE_VIDE || (cellule == pion && recherche == 1))
                        {
                            nb_deplacement++ ;
                            coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;

                            nb_coups_possibles = recherche_rafle_pion (damier, test_dep.lig, test_dep.col,
                                                                pion, coups_trouves, coups_possibles,
                                                                nb_coups_possibles, nb_deplacement) ;
                            nb_deplacement-- ;
                            coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves,
                                                                                coups_possibles[nb_coups_possibles]) ;
                            nb_coups_possibles++ ;
                            coups_trouves = supprimer_tete(coups_trouves) ;
                        }
                    }
                }
            }
        }
        return nb_coups_possibles ;
}

int recherche_rafle_dame (int damier[N][N], int ligne, int colonne,
                          int pion, Liste coups_trouves,
                          Liste coups_possibles[50], int nb_coups_possibles, int nb_deplacement)
{
  /*
   Pour chaques dames trouv�es on r�pertorie toutes les rafles possibles
   */
    Case test_dep ;
    deplacement mouv ;
    int cellule ; // cases que l'on teste
    int recherche ; // resultat de la recherche
    int flag, flag2 ;
    int i, j ; // variables pour les boucles For

    mouv.case_i.col = colonne ;
    mouv.case_i.lig = ligne ;
    /****
    Recherche des coups possibles pour les dames
    ****/

        /***    test diag sup gauche    ***/
        flag = 0 ;
        flag2 = 0 ;
        i= mouv.case_i.lig ;
        j= mouv.case_i.col;

        while ( (i>= 1 && j>= 1) && flag == 0)
        {
            cellule = damier[i][j] ;
            if ((pion == DAME_BLANC && (cellule == PION_NOIR || cellule == DAME_NOIR)) ||
                (pion == DAME_NOIR && (cellule == PION_BLANC || cellule == DAME_BLANC)) )
            {
                mouv.case_cible.lig = i ;
                mouv.case_cible.col = j ;
                recherche = rechercher(coups_trouves, mouv, 1) ;
                if (recherche == 0)
                {
                    test_dep.col = j-1 ;
                    test_dep.lig = i-1 ;
                    if (test_dep.col >= 0 && test_dep.lig >= 0)
                    {
                        cellule = damier[test_dep.lig][test_dep.col] ;
                        mouv.case_f.col = test_dep.col ;
                        mouv.case_f.lig = test_dep.lig ;
                        recherche = rechercher(coups_trouves, mouv, 0) ;
                        if (cellule == CASE_VIDE || (cellule == pion && recherche == 1) )
                            flag = 1 ;
                    }
                }
            }
            i-- ;
            j-- ;
        }
        if (flag == 0 && nb_deplacement == 0)
        {
            i= mouv.case_i.lig-1 ;
            j= mouv.case_i.col-1 ;
            if (i >=0 && j >=0)
            {
                while ((i>=0 && j>=0) && flag2 == 0)
                {
                    mouv.case_f.lig = i ;
                    mouv.case_f.col = j ;
                    cellule = damier[i][j] ;
                    recherche = rechercher (coups_trouves, mouv, 0) ;
                    if ( (pion == DAME_BLANC && (cellule == PION_BLANC || (cellule == DAME_BLANC && recherche == 0))) ||
                        (pion == DAME_NOIR && (cellule == PION_NOIR || (cellule == DAME_NOIR && recherche == 0))) )
                        flag2 = 1 ;
                    else
                    {
                        coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                        coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves, coups_possibles[nb_coups_possibles]) ;
                        nb_coups_possibles++ ;
                        coups_trouves = supprimer_tete(coups_trouves) ;
                        i-- ;
                        j-- ;
                    }
                }
            }
        }
        else if (flag == 1)
        {
            i= mouv.case_cible.lig-1 ;
            j= mouv.case_cible.col-1 ;
            while ((i>=0 && j>=0) && flag2 == 0)
            {
                mouv.case_f.lig = i ;
                mouv.case_f.col = j ;
                cellule = damier[i][j] ;
                recherche = rechercher (coups_trouves, mouv, 0) ;
                if (cellule != CASE_VIDE && recherche == 0)
                    flag2 = 1 ;
                else
                {
                    nb_deplacement++ ;
                    coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                    nb_coups_possibles = recherche_rafle_dame (damier, i, j,
                                                               pion, coups_trouves, coups_possibles,
                                                               nb_coups_possibles, nb_deplacement) ;
                    nb_deplacement-- ;
                    coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves,
                                                                        coups_possibles[nb_coups_possibles]) ;
                    nb_coups_possibles++ ;
                    coups_trouves = supprimer_tete(coups_trouves) ;
                    i-- ;
                    j-- ;
                }
            }
        }

        /***    test diag sup droite    ***/
        flag = 0 ;
        flag2 = 0 ;
        i= mouv.case_i.lig ;
        j= mouv.case_i.col ;

        while ((i>= 1 && j<= 8) && flag == 0)
         {
            cellule = damier[i][j] ;
            if ((pion == DAME_BLANC && (cellule == PION_NOIR || cellule == DAME_NOIR)) ||
                (pion == DAME_NOIR && (cellule == PION_BLANC || cellule == DAME_BLANC)))
            {
                mouv.case_cible.lig = i ;
                mouv.case_cible.col = j ;
                recherche = rechercher(coups_trouves, mouv, 1) ;
                if (recherche == 0)
                {
                    test_dep.col = j+1 ;
                    test_dep.lig = i-1 ;
                    if (test_dep.col < N && test_dep.lig >= 0)
                    {
                        cellule = damier[test_dep.lig][test_dep.col] ;
                        mouv.case_f.col = test_dep.col ;
                        mouv.case_f.lig = test_dep.lig ;
                        recherche = rechercher(coups_trouves, mouv, 0) ;
                        if (cellule == CASE_VIDE || (cellule == pion && recherche == 1) )
                            flag = 1 ;
                    }
                }
            }
            i-- ;
            j++ ;
        }
        if (flag == 0 && nb_deplacement == 0)
        {
            i= mouv.case_i.lig-1 ;
            j= mouv.case_i.col+1 ;
            if (i >=0 && j <N)
            {
                while ((i>=0 && j<N) && flag2 == 0)
                {
                    mouv.case_f.lig = i ;
                    mouv.case_f.col = j ;
                    cellule = damier[i][j] ;
                    recherche = rechercher (coups_trouves, mouv, 0) ;
                    if ( (pion == DAME_BLANC && (cellule == PION_BLANC || (cellule == DAME_BLANC && recherche == 0))) ||
                         (pion == DAME_NOIR && (cellule == PION_NOIR || (cellule == DAME_NOIR && recherche == 0))) )
                        flag2 = 1 ;
                    else
                    {
                        coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                        coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves, coups_possibles[nb_coups_possibles]) ;
                        nb_coups_possibles++ ;
                        coups_trouves = supprimer_tete(coups_trouves) ;
                        i-- ;
                        j++ ;
                    }
                }
            }
        }
        else if (flag ==1)
        {
            i= mouv.case_cible.lig-1 ;
            j= mouv.case_cible.col+1 ;
            while ((i>=0 && j<N) && flag2 == 0)
            {
                mouv.case_f.lig = i ;
                mouv.case_f.col = j ;
                cellule = damier[i][j] ;
                recherche = rechercher (coups_trouves, mouv, 0) ;
                if (cellule != CASE_VIDE && recherche == 0)
                    flag2 = 1 ;
                else
                {
                    nb_deplacement++ ;
                    coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                    nb_coups_possibles = recherche_rafle_dame (damier, i, j,
                                                               pion, coups_trouves, coups_possibles,
                                                               nb_coups_possibles, nb_deplacement) ;
                    nb_deplacement-- ;
                    coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves,
                                                                        coups_possibles[nb_coups_possibles]) ;
                    nb_coups_possibles++ ;
                    coups_trouves = supprimer_tete(coups_trouves) ;
                    i-- ;
                    j++ ;
                }
            }
        }

        /***    test diag inf droite    ***/
        flag = 0 ;
        flag2 = 0 ;
        i= mouv.case_i.lig ;
        j= mouv.case_i.col;

        while ((i<=8 && j<= 8) && flag == 0)
         {
            cellule = damier[i][j] ;
            if ((pion == DAME_BLANC && (cellule == PION_NOIR || cellule == DAME_NOIR)) ||
                (pion == DAME_NOIR && (cellule == PION_BLANC || cellule == DAME_BLANC)) )
            {
                mouv.case_cible.lig = i ;
                mouv.case_cible.col = j ;
                recherche = rechercher(coups_trouves, mouv, 1) ;
                if (recherche == 0)
                {
                    test_dep.col = j+1 ;
                    test_dep.lig = i+1 ;
                    if (test_dep.col <N && test_dep.lig <N)
                    {
                        cellule = damier[test_dep.lig][test_dep.col] ;
                        mouv.case_f.col = test_dep.col ;
                        mouv.case_f.lig = test_dep.lig ;
                        recherche = rechercher(coups_trouves, mouv, 0) ;
                        if (cellule == CASE_VIDE || (cellule == pion && recherche == 1) )
                            flag = 1 ;
                    }
                }
            }
            i++ ;
            j++ ;
        }
        if (flag == 0 && nb_deplacement == 0)
        {
            i= mouv.case_i.lig+1 ;
            j= mouv.case_i.col+1 ;
            if (i <N && j <N)
            {
                while ((i<N && j<N) && flag2 ==0)
                {
                    mouv.case_f.lig = i ;
                    mouv.case_f.col = j ;
                    cellule = damier[i][j] ;
                    recherche = rechercher (coups_trouves, mouv, 0) ;
                    if ( (pion == DAME_BLANC && (cellule == PION_BLANC || (cellule == DAME_BLANC && recherche == 0))) ||
                         (pion == DAME_NOIR && (cellule == PION_NOIR || (cellule == DAME_NOIR && recherche == 0))) )
                        flag2 = 1 ;
                    else
                    {
                        coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                        coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves, coups_possibles[nb_coups_possibles]) ;
                        nb_coups_possibles++ ;
                        coups_trouves = supprimer_tete(coups_trouves) ;
                        i++ ;
                        j++ ;
                    }
                }
            }
        }
        else if (flag == 1)
        {
            i= mouv.case_cible.lig+1 ;
            j= mouv.case_cible.col+1 ;
            while ((i<N && j<N) && flag2 == 0)
            {
                mouv.case_f.lig = i ;
                mouv.case_f.col = j ;
                cellule = damier[i][j] ;
                recherche = rechercher (coups_trouves, mouv, 0) ;
                if (cellule != CASE_VIDE && recherche == 0)
                    flag2 = 1 ;
                else
                {
                    nb_deplacement++ ;
                    coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                    nb_coups_possibles = recherche_rafle_dame (damier, i, j,
                                                               pion, coups_trouves, coups_possibles,
                                                               nb_coups_possibles, nb_deplacement) ;
                    nb_deplacement-- ;
                    coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves,
                                                                        coups_possibles[nb_coups_possibles]) ;
                    nb_coups_possibles++ ;
                    coups_trouves = supprimer_tete(coups_trouves) ;
                    i++ ;
                    j++ ;
                }
            }
        }

        /***    test diag inf gauche    ***/
        flag = 0 ;
        flag2 = 0 ;
        i= mouv.case_i.lig ;
        j= mouv.case_i.col;

        while ((i<=8 && j>=1) && flag == 0)
         {
            cellule = damier[i][j] ;
            if ((pion == DAME_BLANC && (cellule == PION_NOIR || cellule == DAME_NOIR)) ||
                (pion == DAME_NOIR && (cellule == PION_BLANC || cellule == DAME_BLANC)) )
            {
                mouv.case_cible.lig = i ;
                mouv.case_cible.col = j ;
                recherche = rechercher(coups_trouves, mouv, 1) ;
                if (recherche == 0)
                {
                    test_dep.col = j-1 ;
                    test_dep.lig = i+1 ;
                    if (test_dep.col >=0 && test_dep.lig <N)
                    {
                        cellule = damier[test_dep.lig][test_dep.col] ;
                        mouv.case_f.col = test_dep.col ;
                        mouv.case_f.lig = test_dep.lig ;
                        recherche = rechercher(coups_trouves, mouv, 0) ;
                        if (cellule == CASE_VIDE || (cellule == pion && recherche == 1) )
                            flag = 1 ;
                    }
                }
            }
            i++ ;
            j-- ;
        }
        if (flag == 0 && nb_deplacement == 0)
        {
            i= mouv.case_i.lig+1 ;
            j= mouv.case_i.col-1 ;
            if (i <N && j >=0)
            {
                while ((i<N && j>=0) && flag2 == 0)
                {
                    mouv.case_f.lig = i ;
                    mouv.case_f.col = j ;
                    cellule = damier[i][j] ;
                    recherche = rechercher (coups_trouves, mouv, 0) ;
                    if ( (pion == DAME_BLANC && (cellule == PION_BLANC || (cellule == DAME_BLANC && recherche == 0))) ||
                         (pion == DAME_NOIR && (cellule == PION_NOIR || (cellule == DAME_NOIR && recherche == 0))) )
                        flag2 = 1 ;
                    else
                    {
                        mouv.case_f.lig = i ;
                        mouv.case_f.col = j ;
                        coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                        coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves, coups_possibles[nb_coups_possibles]) ;
                        nb_coups_possibles++ ;
                        coups_trouves = supprimer_tete(coups_trouves) ;
                        i++ ;
                        j-- ;
                    }
                }
            }
        }
        else if (flag ==1)
        {
            i= mouv.case_cible.lig+1 ;
            j= mouv.case_cible.col-1 ;
            while ((i<N && j>=0) && flag2 == 0)
            {
                mouv.case_f.lig = i ;
                mouv.case_f.col = j ;
                cellule = damier[i][j] ;
                recherche = rechercher (coups_trouves, mouv, 0) ;
                if (cellule != CASE_VIDE && recherche == 0)
                    flag2 = 1 ;
                else
                {
                    nb_deplacement++ ;
                    coups_trouves = inserer_tete(coups_trouves, mouv, nb_deplacement) ;
                    nb_coups_possibles = recherche_rafle_dame (damier, i, j,
                                                               pion, coups_trouves, coups_possibles,
                                                               nb_coups_possibles, nb_deplacement) ;
                    nb_deplacement-- ;
                    coups_possibles[nb_coups_possibles] = copie_liste(coups_trouves,
                                                                        coups_possibles[nb_coups_possibles]) ;
                    nb_coups_possibles++ ;
                    coups_trouves = supprimer_tete(coups_trouves) ;
                    i++ ;
                    j-- ;
                }
            }
        }

        return nb_coups_possibles ;
}

int recherche_coup_obligatoire(Liste coups_obligatoires[50], Liste coups_possibles[50], int nb_coups_possibles)
{
 /*
  Parcours notre tableau des coups possible afin d'en extraire le(s) coup(s) obligatoire(s)
 */
    int i, prio, recherche ;
    int prio_max = 0 ;
    int nb_element = 0 ;

    for(i=0; i<nb_coups_possibles; i++)
    {
        prio = rechercher_prio_max(coups_possibles[i], 0, prio_max) ;
        if (prio_max < prio)
            prio_max = prio ;
    }

    for(i=0; i<nb_coups_possibles; i++)
    {
        recherche = rechercher_prio_max(coups_possibles[i], 1, prio_max) ;
        if (recherche == 1)
        {
            coups_obligatoires[nb_element] = copie_liste(coups_possibles[i],
                                                        coups_obligatoires[nb_element]) ;
            nb_element++ ;
        }
    }

    return nb_element ;
}
//fin des coups

//joue rafle

void joue_rafle_cpu( int damier[N][N], Liste coup_a_jouer_inversee ) 
{
	int mouvements_restants, prio, pion, i, j;

	Liste coup_a_jouer = creer_liste_vide();
	coup_a_jouer = copie_liste(coup_a_jouer_inversee, coup_a_jouer) ;
	mouvements_restants = coup_a_jouer_inversee->priorite ;
	prio = mouvements_restants ;

	while(((mouvements_restants > 0 && prio != 0) || (mouvements_restants == 0 && prio == 0)))
    {
        if(mouvements_restants != prio)
        {
            coup_a_jouer=supprimer_tete(coup_a_jouer);
        }

        i = coup_a_jouer->dep.case_i.lig ;
        j = coup_a_jouer->dep.case_i.col ;
		pion = damier[i][j] ;

        while (i!= coup_a_jouer->dep.case_f.lig && j!= coup_a_jouer->dep.case_f.col)
        {
            damier[i][j]= 0 ;
            if (coup_a_jouer->dep.case_i.lig - coup_a_jouer->dep.case_f.lig < 0)
                i++ ;
            else
                i-- ;
             if (coup_a_jouer->dep.case_i.col - coup_a_jouer->dep.case_f.col < 0)
                j++ ;
            else
                j-- ;
        }
        damier[coup_a_jouer->dep.case_f.lig][coup_a_jouer->dep.case_f.col] = pion ;

		mouvements_restants-- ;
	}
}

//fin joue rafle


//minimax pour l'IA

void appel_minimax (int damier[N][N], int prof, Liste coup_a_jouer[1],int joueur)
{
	minimax (damier, prof, MAX, coup_a_jouer,joueur);
}

int minimax (int damier[N][N], int prof, int flag, Liste coup_a_jouer[1],int joueur)
{
	if(prof == 0)
		return (eval(damier,joueur));

	int val1;
	int i, val;
	int nb_coups ;
	int damier_copie[N][N];

	if(flag == MAX) // MAX
	{
		//printf("JE FAIS UN MAX \n");
		val1 = INT_MIN; // Element neutre sur un int d'un maximum

		Liste coups_obligatoire[M];
		init_tab_liste(coups_obligatoire, M);

		nb_coups = recherche_pion(damier, coups_obligatoire, CPU,joueur);

		for (i=0; ((i<nb_coups) && (coups_obligatoire[i]!=NULL)); i++)
		{
            copie_damier(damier, damier_copie);
            Liste coup_a_jouer_copie_inverse ;
			Liste coup_a_jouer_copie[1] ;
			init_tab_liste(coup_a_jouer_copie, 1) ;
            coup_a_jouer_copie_inverse = copie_liste(coup_a_jouer[0], coup_a_jouer_copie_inverse);
            coup_a_jouer_copie[0] = copie_liste(coup_a_jouer_copie_inverse, coup_a_jouer_copie[0]);

            joue_rafle_cpu(damier_copie, coups_obligatoire[i]);
            val = minimax (damier_copie, prof - 1, MIN, coup_a_jouer_copie,joueur);

            if (val > val1)
            {
                val1=val;

                coup_a_jouer[0] = copie_liste( coups_obligatoire[i], coup_a_jouer[0]);
				//printf("MAX : J'ai trouve mieux : ");
				//afficher_liste_inverse(coup_a_jouer[0]);
            }
        }
    }

	else if(flag==MIN)		// MIN
	{
		//printf("JE FAIS UN MIN \n");
		val1 = INT_MAX; // Element neutre sur un int d'un minimum

		Liste coups_obligatoire[M];
		init_tab_liste(coups_obligatoire, M);

		nb_coups = recherche_pion(damier, coups_obligatoire, HUMAIN,joueur);
		for (i=0; i<nb_coups; i++)
		{
            copie_damier(damier, damier_copie);
            Liste coup_a_jouer_copie_inverse ;
			Liste coup_a_jouer_copie[1] ;
			init_tab_liste(coup_a_jouer_copie, 1) ;
            coup_a_jouer_copie_inverse = copie_liste(coup_a_jouer[0], coup_a_jouer_copie_inverse);
            coup_a_jouer_copie[0] = copie_liste(coup_a_jouer_copie_inverse, coup_a_jouer_copie[0]);

            joue_rafle_cpu(damier_copie, coups_obligatoire[i]);	////
            val = minimax (damier_copie, prof - 1, MAX, coup_a_jouer_copie,joueur);

            if (val < val1)
            {
                val1=val;


                coup_a_jouer[0] = copie_liste( coups_obligatoire[i], coup_a_jouer[0]);
				//printf("MIN : J'ai trouve mieux : ");
				//afficher_liste_inverse(coup_a_jouer[0]);
            }
        }
    }

	return val1;
}

int eval(int damier[N][N],int joueur)
{
	return (eval_pions(damier,joueur) + eval_dames(damier,joueur) + eval_nbdames(damier,joueur) ) ;
}

int eval_pions(int damier[N][N], int joueur)
{
	int tab_val[N][N] = { { 80,0, 100,   0, 125,   0, 100,   0  } , \
					    {   0, 70,  0,   70,  0,   70,  0,  70  } , \
					    {   25, 0,  20,   0,  20,   0,  20,  0  } , \
					    {   0,  10,   0,  10,   0,  10,   0,  25} , \
					    {   25, 0,  10,   0,  10,   0,  10,   0 } , \
					    {   0,  20,   0,  20,   0,  20,   0,  25} , \
					    {   70,  0,  70,   0,  70,   0,  70,   0} , \
					    {   0, 100,   0, 125,   0, 100,   0,  80} }  ;

	int i, j, acc = 0;

	for (i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			if(damier[i][j]==joueur ||  damier[i][j]==2*joueur)
			{
				acc += tab_val[i][j];
			}
			else if (damier[i][j] ==-joueur ||  damier[i][j]==-2*joueur)
			{
				acc -= tab_val[i][j];
			}
		}
	}

	return acc;
}

int eval_dames(int damier[N][N], int joueur)
{
	int i, j, x=0, y=0, acc=0, trouve=0, case_precedente=0;

	for (i=0; i<N;	i++)
	{
		for(j=0; j<N; j++)
		{
			if(damier[i][j]== 2*joueur)
			{
						// BAS DROITE
				x=i+1;
				y=j+1;

				if(damier[x][y] == -joueur || damier[x][y]==-2*joueur)
				{
					acc -=1000;
				}

				else
				{
					while( x<=N-1 && y <=N-1 && !trouve && case_precedente==0)
					{
						if((damier[x][y] == -joueur || damier[x][y]==-2*joueur) && case_precedente == 0 && x<N-2 && y<N-2)
						{
							if (damier[x+1][y+1]==0)
							{
								trouve = 1;
								acc += 100;
							}

						}
						else
						{
							case_precedente = damier[x][y];
							x++;
							y++;
						}


					}
				}

						// BAS GAUCHE
				x=i+1;
				y=j-1;

				if(damier[x][y] == -joueur || damier[x][y]==-2*joueur)
				{
					acc -=1000;
				}

				else
				{
					while( x<=N-1 && y <=0 && !trouve && case_precedente==0)
					{
						if((damier[x][y] == -joueur || damier[x][y]==-2*joueur) && case_precedente == 0 && x<N-2 && y<1)
						{
							if (damier[x+1][y-1]==0)
							{
								trouve = 1;
								acc += 100;
							}

						}
						else
						{
							case_precedente = damier[x][y];
							x++;
							y--;
						}


					}
				}
						// HAUT GAUCHE
				x=i-1;
				y=j-1;

				if(damier[x][y] == -joueur || damier[x][y]==-2*joueur)
				{
					acc -=1000;
				}

				else
				{
					while( x<=0 && y <=0 && !trouve && case_precedente==0)
					{
						if((damier[x][y] == -joueur || damier[x][y]==-2*joueur) && case_precedente == 0 && x<1 && y<1)
						{
							if (damier[x-1][y-1]==0)
							{
								trouve = 1;
								acc += 100;
							}

						}
						else
						{
							case_precedente = damier[x][y];
							x--;
							y--;
						}


					}
				}

						// HAUT DROITE
				x=i-1;
				y=j+1;

				if(damier[x][y] == -joueur || damier[x][y]==-2*joueur)
                {
					acc -=1000;
				}

				else
				{
					while( x<=0 && y <=N-1 && !trouve && case_precedente==0)
					{
						if((damier[x][y] == -joueur || damier[x][y]==-2*joueur) && case_precedente == 0 && x<1 && y<N-2)
						{
							if (damier[x-1][y+1]==0)
							{
								trouve = 1;
								acc += 100;
							}

						}
						else
						{
							case_precedente = damier[x][y];
							x--;
							y++;
						}


					}
				}
			}
		}
	}
	return acc;
}

void copie_damier(int damier1[N][N], int damier2[N][N])
{
	int i, j;

	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			damier2[i][j]=damier1[i][j];
		}
	}

	return;
}

int eval_nbdames(int damier[N][N], int joueur)
{
	int i, j, acc=0;

	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
		    if (damier[i][j]==joueur*2)
            {
                acc+=250;
            }
            else if (damier[i][j]==-joueur*2)
            {
                acc-=300;
            }
		}
	}
	return acc;
}
//fin minimax