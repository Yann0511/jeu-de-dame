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
#include<math.h>
#include"../include/structure.h"
#include "../include/jeu.h"

//affichage du damier

void affiche_ligne(int i,int damier[8][8])
{
  
  char j;
  printf(" %20c ",i+'a') ;
  for(j=0 ;j<8 ;j++)
    {
      switch(damier[i][j])
	{
	case PION_BLANC :
	  printf("| b ") ;
	  break ;
	case PION_NOIR :
	  printf("| n ") ;
	  break ;
	case DAME_NOIR :
	  printf("|[N]") ;
	  break ;
	case DAME_BLANC :
	  printf("|[B]") ;
	  break ;
	default :
	  printf("|   ") ;
	  break ;
	}
    }
  printf("|%2c\n",i+'a') ;
  printf("                      |-------------------------------|\n") ;
}

/*
Fonction qui affiche le damier en totalité
*/

void affiche_damier(int damier[8][8])
{
  int i;
  printf("\n                        1   2   3   4   5   6   7   8  \n");
  printf("                      |-------------------------------|\n") ;
  for(i=0 ;i<8 ;i++)
    affiche_ligne(i,damier) ;
  printf("                        1   2   3   4   5   6   7   8  \n") ;
}


/*
  Initialisation du tableau
*/
void init_damier(damier *jeu)
{
  jeu->nb_blanc = 12 ;
  jeu->nb_noir = 12 ;
  int i,j ;
  //On initialise le tableau
  for(i=0 ;i<8 ;i++)
    for(j=0 ;j<8 ;j++)
      jeu->plateau[i][j] = 0 ;
  //On remplie la partie haute du damier par des pions noirs
  for(i=0 ;i<3 ;i++)
    {
      //Si i est pair, la première case doit être noir (active)
      if(i%2 == 0) j=0 ;
      else j=1 ;
      for(j ;j<8 ;j+=2)
	    jeu->plateau[i][j] = PION_NOIR ;
    }
  //On remplie la partie basse du damier par des pions blancs
  for(i=5 ;i<8 ;i++)
    {
      //Si i est pair, la premier case doit être noir (active)
      if(i%2 == 0) j=0 ;
      else j=1 ;
      for(j ;j<8 ;j+=2)
    	jeu->plateau[i][j] = PION_BLANC ;
    }
}

//fin du affichage

//déplacement du joeur humain

void deplace_pion(int J,deplacement d,int prise,damier *jeu, Case p)
{
  if(jeu->plateau[d.case_i.lig][d.case_i.col] == J)
  {
    jeu->plateau[d.case_i.lig][d.case_i.col] = CASE_VIDE ;
    jeu->plateau[d.case_f.lig][d.case_f.col] = J ;
    if(prise == 1)
	  {
	    if(J == PION_BLANC)
	      jeu->nb_noir-- ;
	    else 
        jeu->nb_blanc-- ;
	    jeu->plateau[(d.case_f.lig + d.case_i.lig)/2][(d.case_f.col + d.case_i.col)/2]=CASE_VIDE ;
	  }
  }

  //déplacé les dames
  else if(jeu->plateau[d.case_i.lig][d.case_i.col] == 2*J)
  {
    jeu->plateau[d.case_i.lig][d.case_i.col] = CASE_VIDE ;
    jeu->plateau[d.case_f.lig][d.case_f.col] = 2*J ;
    if(prise == 1)
    {
      //printf("\n%d\n",jeu->plateau[p.lig][p.col]);
      if(J == PION_BLANC)
        jeu->nb_noir--;
      else
        jeu->nb_blanc--;
      jeu->plateau[p.lig][p.col] = CASE_VIDE ;
    }
  }



   //faire dame
  if(J==PION_NOIR)
  {
    d.case_f.lig=7 ;
    d.case_f.col=1 ;
  }
  else 
  {
    d.case_f.lig=0 ;
    d.case_f.col=0 ;
  }
  for(d.case_f.col ;d.case_f.col<7 ;d.case_f.col+=2) 
  {
  if(jeu->plateau[d.case_f.lig][d.case_f.col] == J)
    jeu->plateau[d.case_f.lig][d.case_f.col] = 2*J ;
  }
}


int coup_possible(int J,deplacement c,damier *jeu, char tab[128], int possible, Case *adv,int prise)
{
  int z,nbn = 0, nbr  = 0, a = 0,b = 0,i,j ;
  damier clone ;
  adv->lig = -1;
  adv->col = -1 ;
  c.case_i.lig = -1 ;
  c.case_i.col = -1;
  prise=0;

  //clonage du damier actuel pour tester les déplacements
  for(i = 0 ; i < 8 ; i++)
  {
    for(j = 0 ; j < 8 ; j++)
    {
      clone.plateau[i][j] = jeu->plateau[i][j] ;
    }
  }
  
  //Décodage du coup
  for(z=0; z<128 && tab[z]!='\n' && possible == 1; z++)
  {
    //décodage de la case initiale
    while(tab[z]==' ')
      z++;
    if(c.case_i.lig == -1)
    {
      if(tab[z]>='A' && tab[z]<='h' ) // si le caractère est une lettre
      {
        if((tab[z] >='a') && (tab[z] <= 'h'))
        {
          c.case_i.lig = tab[z]-'a';
          z++;
        }
        else if((tab[z] >= 'A') && (tab[z] <= 'H'))
        {
          c.case_i.lig = tab[z]-'A';
          z++;
        }
        else
          return 0;
      }
      else
        return 0 ;
    }
    while(tab[z]==' ')
      z++;
    if(c.case_i.col == -1)
    {
      if((tab[z] >= '1') && (tab[z] <='8')) //si le caractère est un chiffre
      {
        c.case_i.col = tab[z]-'1';
        z++;
      }
      else
        return 0 ;
    }
  //décodage de la case finale
    while(tab[z]==' ')
      z++;
    if(tab[z]>='A' && tab[z]<='h' ) // si le caractère est une lettre
    {
      if((tab[z] >='a') && (tab[z] <= 'h'))
      {
        c.case_f.lig = tab[z]-'a';
        z++;
      }
      else if((tab[z] >= 'A') && (tab[z] <= 'H'))
      {
        c.case_f.lig = tab[z]-'A';
        z++;
      }
      else
        return 0;
    }
    else
      return 0 ;
    while(tab[z]==' ')
      z++;
    if((tab[z] >= '1') && (tab[z] <='8'))  // si le caractère est un chiffre
    {
      c.case_f.col = tab[z]-'1';
      z++;
    }
    else
      return 0;
    while(tab[z] == ' ')
      z++;
    
  
    //fin du décodage du premeir coup. Maitenant on vérifie si le coup est possible pour les pions
    if(clone.plateau[c.case_f.lig][c.case_f.col]!=CASE_VIDE)
        possible = 0;

    if(possible!= 0)
    {
      possible = 0 ;
      //déplacement des pions simples
      if(clone.plateau[c.case_i.lig][c.case_i.col]== J)
      {
      //déplacement simple
        if(c.case_i.lig - c.case_f.lig == J && abs(c.case_i.col - c.case_f.col) == 1 && tab[z] == '\n' && prise != 1 )
          possible = 1 ;
      //gagné un pion adverse
        else if(abs(c.case_i.lig - c.case_f.lig) == 2 && abs(c.case_i.col - c.case_f.col) ==2 && abs(J)==1)
        {
          if(c.case_i.lig - c.case_f.lig < 0)
          {
            if(c.case_i.col - c.case_f.col < 0)
            {
              if(clone.plateau[c.case_i.lig+1][c.case_i.col+1]== -J ||clone.plateau[c.case_i.lig+1][c.case_i.col+1]== -2*J )
              {
                possible = 1 ;
                prise = 1 ;
              } 
            
            }
      
            else 
            {
              if(clone.plateau[c.case_i.lig+1][c.case_i.col-1]== -J || clone.plateau[c.case_i.lig+1][c.case_i.col-1]== -2*J)
              {
                possible = 1;
                prise = 1 ;
              }
            }      
          }
          else
          {
            if(c.case_i.col - c.case_f.col < 0)
            {
              if(clone.plateau[c.case_i.lig-1][c.case_i.col+1]== -J || clone.plateau[c.case_i.lig-1][c.case_i.col+1]== -2*J)
              {
                possible  = 1;
                prise = 1 ;
              }
            }
            else 
            {
              if(clone.plateau[c.case_i.lig-1][c.case_i.col-1]== -J || clone.plateau[c.case_i.lig-1][c.case_i.col-1]== -2*J)
              {
                possible = 1;
                prise = 1 ;
              }
            }      
          }
        }
      }
      //déplacement de la dame
      else if(clone.plateau[c.case_i.lig][c.case_i.col]== 2*J)
      {
        if(abs(c.case_i.lig - c.case_f.lig) == abs(c.case_i.col - c.case_f.col))
        {
          a = c.case_i.lig ;
          b = c.case_i.col ;
          while(a !=c.case_f.lig || b != c.case_f.col)
          {
            if(c.case_f.lig>c.case_i.lig)
              a++ ;
            else
              a-- ;
            if(c.case_f.col>c.case_i.col)
              b++ ;
            else
              b-- ;
            //printf("\n%d, %d\n",a,b);
            if(clone.plateau[a][b] != CASE_VIDE) 
              nbr++;
            if(clone.plateau[a][b]==-J || clone.plateau[a][b]== -2*J) 
            {
              nbn++ ;
              adv->lig = a ;
              adv->col = b ;
              //printf("\n%d\n",jeu->plateau[a][b]);
            }
          }
          if(nbr==1 && nbn==1)    
          {
            possible = 1;
            prise = 1;
          }
          else if(nbr== 0 && nbn == 0 && tab[z] == '\n' && prise != 1)
            possible = 1 ;
          else
            possible = 0 ;
        }
        else
          possible = 0 ;
      }
      if(possible == 1)
      {
        deplace_pion(J,c,prise,&clone,*adv) ;
        c.case_i.lig = c.case_f.lig;
        c.case_i.col = c.case_f.col;
        nbn = 0 ;
        nbr = 0 ;
        z = z-1 ;
      }
      
    }
  }
  if(possible == 1)
  {
    return 1 ;
  }
  else
    return 0 ;
}

void faire_deplacement(int J,deplacement c, damier *jeu,char tab[128], int possible, Case adv)
{
  int p,z=0, prise = 0,a,b,nbr = 0 , nbn = 0 ;
  deplacement d ;
  c.case_i.lig = -1 ;
  c.case_i.col = -1 ;
  //affiche_damier(jeu->plateau) ;
    while(z<128 && tab[z]!='\n')
    {
      //décodage de la case initiale
      while(tab[z]==' ')
        z++;
      if(c.case_i.lig==-1)
      {
        if(tab[z]>='A' && tab[z]<='h' ) // si le caractère est une lettre
        {
          if((tab[z] >='a') && (tab[z] <= 'h'))
          {
            c.case_i.lig = tab[z]-'a';
            z++;
          }
          else if((tab[z] >= 'A') && (tab[z] <= 'H'))
          {
            c.case_i.lig = tab[z]-'A';
            z++;
          }
        }
        else ;
      }
      while(tab[z]==' ')
        z++;
      if(c.case_i.col == -1)
      {
        if((tab[z] >= '1') && (tab[z] <='8')) //si le caractère est un chiffre
        {
          c.case_i.col = tab[z]-'1';
          z++;
        }
        else ;
      }
      //décodage de la case finale
      while(tab[z]==' ')
        z++;
      if(tab[z]>='A' && tab[z]<='h' ) // si le caractère est une lettre
      {
        if((tab[z] >='a') && (tab[z] <= 'h'))
        {
          c.case_f.lig = tab[z]-'a';
          z++;
        }
        else if((tab[z] >= 'A') && (tab[z] <= 'H'))
        {
          c.case_f.lig = tab[z]-'A';
            z++;
        }
      }
      else ;
      while(tab[z]==' ')
        z++;
      if((tab[z] >= '1') && (tab[z] <='8'))  // si le caractère est un chiffre
      {
        c.case_f.col = tab[z]-'1';
        z++;
      }
      else ;
      while(tab[z]==' ')
        z++;
      if((c.case_f.lig == 0 || c.case_f.lig == 7) && jeu->plateau[c.case_i.lig][c.case_i.col] == J)
        z = 128 ;
      

      if(jeu->plateau[c.case_i.lig][c.case_i.col]== 2*J)
      {
        if(abs(c.case_i.lig - c.case_f.lig) == abs(c.case_i.col - c.case_f.col))
        {
          a = c.case_i.lig ;
          b = c.case_i.col ;
          while(a !=c.case_f.lig || b != c.case_f.col)
          {
            if(c.case_f.lig>c.case_i.lig)
              a++ ;
            else
              a-- ;
            if(c.case_f.col>c.case_i.col)
              b++ ;
            else
              b-- ;
            //printf("\n%d, %d\n",a,b);
            if(jeu->plateau[a][b] != CASE_VIDE) 
              nbr++;
            if(jeu->plateau[a][b]==-J || jeu->plateau[a][b]== -2*J) 
            {
              nbn++ ;
              adv.lig = a ;
              adv.col = b ;
              //printf("\n%d\n",jeu->plateau[a][b]);
            }
          }
          if(nbr==1 && nbn==1)    
          {
            prise = 1;
          }
          else 
            prise = 0 ;
        }
        else ;
      }
      if(coup_gagnant(jeu->plateau, c, J))
      {
        prise = 1 ;
        deplace_pion(J,c,prise,jeu,adv);
        c.case_i.lig = c.case_f.lig;
        c.case_i.col = c.case_f.col;
      }
      else
      {
         if(!trouve_gagnant(jeu->plateau,J))
        {
          prise = 0 ;
          deplace_pion(J,c,prise,jeu,adv);
          c.case_i.lig = c.case_f.lig;
          c.case_i.col = c.case_f.col;
        }
        else 
        {
          prise = 1 ;
          printf("\n Un coup gagnant trouver!! Je le joue pour vous!!!.\n ") ;
          d = cp_gagnant_obligatoire(jeu->plateau, J,c) ;
          printf("\n\t C'est le déplacement %c%c%c%c.\n\t C'est gratuit!!! Me remercie pas!!", d.case_i.lig + 'a',d.case_i.col+'1',d.case_f.lig + 'a',d.case_f.col+'1') ;
          deplace_pion(J,d,prise,jeu,adv);
          z = 128 ;
        }
      }
    }
  affiche_damier(jeu->plateau) ; 
}

void arbitre (int J, damier *jeu, char tab[128], deplacement d, int possible)
{
  int p, k = 0,prise;
  Case adv={-2,-2};
  if(J == PION_BLANC)
    printf("\n \tJOUEUR_BLANC -->> ");
  else
    printf("\n\t JOUEUR_NOIR -->> ");
  fgets(tab,128,stdin);
  p = coup_possible(J,d,jeu,tab,possible,&adv,prise);
  if(p)
  {
    faire_deplacement(J,d,jeu,tab,possible,adv);
    //printf("\n\tNombre de pion blanc = %d \n\tNombre de pion noir = %d\n",jeu->nb_blanc, jeu->nb_noir);
  }
  
  else
  {
    for(k=1; k==1; k--)
    {
      printf("   Mauvais deplacement.\n");
      if(J == PION_BLANC)
        printf("\n \tJOUEUR_BLANC -->> ");
      else
        printf("\n\t JOUEUR_NOIR -->> ");
      fgets(tab,128,stdin);
      p = coup_possible(J,d,jeu,tab,possible,&adv,prise);
      if(p)
      {
        faire_deplacement(J,d,jeu,tab,possible,adv);
        //printf("\n\tNombre de pion blanc = %d \n\tNombre de pion noir = %d\n",jeu->nb_blanc, jeu->nb_noir);   
        k = 0 ;     
      }
    }
    if(!p)
    {
      if(J==PION_BLANC)
        jeu->nb_blanc = 0 ;
      else
        jeu->nb_noir = 0 ;
    }
  }  
}

int coup_gagnant(int dd[8][8], deplacement c, int J)
{
  int z, a = 0 , b = 0 , nbn = 0 , nbr = 0;
  
      // les pions
  if(abs(c.case_i.lig - c.case_f.lig) == 2 && abs(c.case_i.col - c.case_f.col) == 2 && dd[c.case_i.lig][c.case_i.col] == J)
    return 1 ;

    //les dames
  if(dd[c.case_i.lig][c.case_i.col] == J*2)
  {
    if(abs(c.case_i.lig - c.case_f.lig) == abs(c.case_i.col - c.case_f.col))
    {
      a = c.case_i.lig ;
      b = c.case_i.col ;
      while(a !=c.case_f.lig || b != c.case_f.col)
      {
        if(c.case_f.lig>c.case_i.lig)
          a++ ;
        else
          a-- ;
        if(c.case_f.col>c.case_i.col)
          b++ ;
        else
          b-- ;
        if(dd[a][b] != CASE_VIDE) 
          nbr++;
        if(dd[a][b]==-J || dd[a][b]== -2*J) 
          nbn++ ;
      }
      if(nbr==1 && nbn==1)    
        return 1 ;
    }
  }
  return 0;
}


// la fonction qui vient parcours le damier et recherche le coup gagnant obligatoire

deplacement cp_gagnant_obligatoire(int dd[8][8], int J, deplacement c)
{
  int i, j ;
  c.case_i.lig = 9 ;
  c.case_i.col = 0 ;
  c.case_f.lig = 0 ;
  c.case_f.col = 0 ;
  for(i = 0; i < 8 ; i++)
  {
    for(j = 0 ; j < 8 ; j++)
    {
      // pour les pions simples
      if(dd[i][j] == J)
      {
        if(i-1 < 8 && i-2 >= 0 )
        {
          if(j+2 < 8)
          {
            if((dd[i-1][j+1] == -J || dd[i-1][j+1] == -2*J) && dd[i-2][j+2] == 0)
            {
              c.case_i.lig = i;
              c.case_i.col = j ;
              c.case_f.lig= (i-2) ;
              c.case_f.col= (j+2) ;
              
            }
          }
          if(j-2 >= 0)
          {
            if((dd[i-1][j-1] == -J || dd[i-1][j-1] == -2*J) && dd[i-2][j-2] == 0)
            {
              c.case_i.lig = i ;
              c.case_i.col =  j ;
              c.case_f.lig = (i-2) ;
              c.case_f.col = (j-2) ;
              
            }
          }
        }
        if(i+2 < 8)
        {
          if(j+2 < 8)
          {
            if((dd[i+1][j+1] == -J || dd[i+1][j+1] == -2*J) && dd[i+2][j+2] == 0)
            {
              c.case_i.lig = i ;
              c.case_i.col = j ;
              c.case_f.lig = (i+2) ;
              c.case_f.col = (j+2) ;
              
            }
          }
          if(j-2 >= 0)
          {
            if((dd[i+1][j-1] == -J || dd[i+1][j-1] == -2*J) && dd[i+2][j-2] == 0)
            {
              c.case_i.lig = i ;
              c.case_i.col = j ;
              c.case_f.lig = (i+2) ;
              c.case_f.col = (j-2) ;
              
            }
          }
        }
      }
    }
  }
  return c ;
}

int trouve_gagnant(int dd[8][8], int J)
{
  deplacement c, d ;
  d = cp_gagnant_obligatoire(dd, J, c) ;
  if(d.case_i.lig != 9)
    return 1 ;
  return 0 ;
}


int fin_jeu(int dd[8][8])
{
  int i, j , p = 0, q  = 0 ;
  for(i = 0 ; i < 8 ; i++) 
  {
    for (j = 0 ; j < 8 ; j++)
    {
      if(dd[i][j] == -1 || dd[i][j] == -2 )
        p++;
      if(dd[i][j] == 1 || dd[i][j] == 2 )
        q++;
    }
  }
  if(p == 0 || q == 0)
    return 1 ;
  return 0 ;
}

//fin du déplacement du joueur humain