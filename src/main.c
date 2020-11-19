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


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "jeu.c"
#include "cpu.c"
#include "../include/ia.h"
#include "../include/jeu.h"


int calcul_pion (damier jeu, int joueur)
{
    int i, j ;
    int compteur = 0 ;

    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            if (joueur == 1)
            {
                if (jeu.plateau[i][j] == PION_BLANC || jeu.plateau[i][j] == DAME_BLANC)
                    compteur++ ;
            }
            else
            {
                if (jeu.plateau[i][j] == PION_NOIR || jeu.plateau[i][j] == DAME_NOIR)
                    compteur++ ;
            }
        }
    }
    return compteur ;
}


int main (void)
{
  deplacement d; 
  damier jeu;
  char tab[128]={0},choix[128] ={0}, entrer[128];
  int possible = 1, p, i=0;
  int profondeur = 7 ;
  srand(time(NULL));
	int aleatoir=rand()%22;
	int aleatoir2=rand()%22;
  joueur j;
  Liste coups_obligatoires[M] ; //contiendra tout les cas que le joueurs peut jouer

	Liste coup_a_jouer[1];
	Liste coup_a_jouer_ordonne[1];
	init_tab_liste(coup_a_jouer, 1); 
  jeu.nb_noir = 12;
  jeu.nb_blanc = 12;

  printf("                               \n\
			 ###    ##   ## ##  ####  .### \n\
			 #  #  #  #  # # #  #     #    \n\
			 #  #  ####  # # #  ###    ##  \n\
			 #  #  #  #  #   #  #        # \n\
			 ###   #  #  #   #  ####  ###. \n\n\
			      ~ Projet de Langage C ~    \n\n\
			     Par : DEGBEGNI Moulero Andy      \n\
			                 et       \n\
			           OLOU Yann Kelly        \n\n");
  
  printf ("MODE DE JEUX ? \n\
    - a : Humain VS IA \n\
    - b : HUMAIN vs HUMAIN \n\
    - c : IA VS IA\n") ;

   do
   {
    fgets(choix,128,stdin) ;
    while(choix[i] == ' ')
       i++;
   }while(!(choix[i] >= 'a' && choix[i] <= 'c')) ;
   
  init_damier(&jeu) ;
  affiche_damier(jeu.plateau);
  j.couleur = PION_BLANC ;
  switch (choix[i])
   {
      case 'a' :
         do
         {
            arbitre (j.couleur, &jeu,tab,d, possible);
            printf("\n\tNombre de pion blanc = %d \n\tNombre de pion noir = %d\n",calcul_pion (jeu,HUMAIN), calcul_pion (jeu, CPU));
    
            printf("\nTour du Joueur IA\n") ;

		      appel_minimax (jeu.plateau, profondeur, coup_a_jouer, -j.couleur);

		      printf(" \tL'IA a joué le coup : ");

		      coup_a_jouer_ordonne[0] = copie_liste(coup_a_jouer[0], coup_a_jouer_ordonne[0]);

		      afficher_liste_inverse(coup_a_jouer_ordonne[0]);

		      joue_rafle_cpu(jeu.plateau, coup_a_jouer_ordonne[0]);
            for (i=0; i<N; i++)
            {
               if (jeu.plateau[7][i] == PION_NOIR)
                jeu.plateau[7][i] = DAME_NOIR ;
               else if(jeu.plateau[0][i] == PION_BLANC)
                  jeu.plateau[0][i] = DAME_BLANC ;
            }
            affiche_damier(jeu.plateau);

            printf("\n\tNombre de pion blanc = %d \n\tNombre de pion noir = %d\n",calcul_pion (jeu,HUMAIN), calcul_pion (jeu, CPU));

         } while(fin_jeu(jeu.plateau) == 0 && calcul_pion (jeu,HUMAIN) > 0 && calcul_pion (jeu, CPU) > 0 && possible == 1);
         break;
      
      case 'b' :
         do 
         {
            arbitre (j.couleur, &jeu,tab,d, possible);
            printf("\n\tNombre de pion blanc = %d \n\tNombre de pion noir = %d\n",calcul_pion (jeu,HUMAIN), calcul_pion (jeu, CPU));
            j.couleur = -j.couleur ;
         }while(fin_jeu(jeu.plateau) == 0 && calcul_pion (jeu,HUMAIN) > 0 && calcul_pion (jeu, CPU) > 0 && possible == 1);
         break;
      
      case 'c' :
         do
         {

		      appel_minimax (jeu.plateau, profondeur, coup_a_jouer, j.couleur);

		      printf(" \tL'IA a joué le coup : ");

		      coup_a_jouer_ordonne[0] = copie_liste(coup_a_jouer[0], coup_a_jouer_ordonne[0]);

		      afficher_liste_inverse(coup_a_jouer_ordonne[0]);

		      joue_rafle_cpu(jeu.plateau, coup_a_jouer_ordonne[0]);
            for (i=0; i<N; i++)
            {
               if (jeu.plateau[7][i] == PION_NOIR)
                jeu.plateau[7][i] = DAME_NOIR ;
               else if(jeu.plateau[0][i] == PION_BLANC)
                  jeu.plateau[0][i] = DAME_BLANC ;
            }
            affiche_damier(jeu.plateau);

            printf("\n\tNombre de pion blanc = %d \n\tNombre de pion noir = %d\n",calcul_pion (jeu,HUMAIN), calcul_pion (jeu, CPU));
            j.couleur = -j.couleur ;
            fgets(entrer,128,stdin);

         }while(fin_jeu(jeu.plateau) == 0 && calcul_pion (jeu,HUMAIN) > 0 && calcul_pion (jeu, CPU) > 0 && possible == 1);
         break ;
      default :
         break ;
   }

  if(calcul_pion (jeu,HUMAIN) > calcul_pion (jeu, CPU))
    printf("   Fin du jeu!!!\n\t Le joueur en blanc a gagné!!!!!\n");
  else
  {
    printf("   Fin du jeu!!!\n\t Le joueur en noir a gagné!!!!!\n");
    if(aleatoir==1||aleatoir2==1)
      printf("\nc 'etait trop facile on recommence ? ");
		if(aleatoir==2||aleatoir2==2)
      printf("\nVOS NEURONES NE POURRONT$JAMAIS RIEN CONTRE MON IA\n");
		if(aleatoir==3||aleatoir2==3)
      printf("\nJE COMPTE ECRIRE UN LIVRE:$ANDY ET YANN vous explique$les bases des dames$IL FAUDRA QUE VOUS LE LISIE ?\n ");
		if(aleatoir==4||aleatoir2==4)
      printf("\n NE VOUS FAITES PAS D'ILLUSION$VOUS ETES FICHU\n ");
		if(aleatoir==5||aleatoir2==5)
      printf("\nIL N'Y A PAS DE HONTE A ABANDONNER...$QUAND ON EST UN HUMAIN\n ");
		if(aleatoir==6||aleatoir2==6)
      printf("\nA VOTRE PLACE,JE ME PLAINDRAIS$AUPRES DES CONCEPTEURS DE L'IA\n");
		if(aleatoir==7||aleatoir2==7)
      printf("\nA FORCE DE VOUS COTOYER$J'AI PEUR DE REGRESSER\n");
		if(aleatoir==8||aleatoir2==8)
      printf("\nDISONS QUE VOUS AVEZ UNE$GRANDE MARGE DE PROGRESSION\n");
		if(aleatoir==9||aleatoir2==9)
      printf("\nJE CONNAIS UN JEU AVEC$DES B ET DES N...$ET PUIS NON,C'EST TROP$DIFFICILE POUR VOUS\n");
		if(aleatoir==10||aleatoir2==10)
      printf("\nLAISSEZ TOMBER LE JEU DE DAME,$ALLEZ PLUTOT VOUS BRANLÉ\n ");
		if(aleatoir==11||aleatoir2==11)
      printf("\n \n");
		if(aleatoir==12||aleatoir2==12)
      printf("\n \n");
		if(aleatoir==13||aleatoir2==13)
      printf("\n \n");
		if(aleatoir==14||aleatoir2==14)
      printf("\nCA FAIT TROP LONGTEMPS QUE$JE VOUS LAISSE GAGNER \n");
		if(aleatoir==15||aleatoir2==15)
      printf("\nVOUS MANQUEZ DE CONCENTRATION\n");
		if(aleatoir==16||aleatoir2==16)
      printf("\nREFLECHISSEZ AU LIEU DE$JOUER N'IMPORTE QUOI \n");
		if(aleatoir==17||aleatoir2==17)
      printf("\nCE QUI EST BIEN AVEC VOUS,$C'EST QU'IL SUFFIT D'ATTENDRE$QUE VOUS VOUS PLANTIEZ\n");
		if(aleatoir==18||aleatoir2==18)
      printf("\nERRARE HUMANUM EST\n");
		if(aleatoir==19||aleatoir2==19)
      printf("\nVOUS ETES VRAIMENT TROP$FACILE A BATTRE \n");
		if(aleatoir==20||aleatoir2==20)
      printf("\n \n");
		if(aleatoir==21||aleatoir2==21)
      printf("\nc 'etait trop difficile on recommence ? \n");
		if(aleatoir==22||aleatoir2==22)
      printf("\nc 'etait trop difficile on recommence ? \n");
  }
  return 0 ;
}
