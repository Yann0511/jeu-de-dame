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


NAME 	=	dame 

LIBS_DIR 	=	librarys/

CFLAGS	=	-ftest-coverage -O2

HEADERS_DIR 	=	 $(shell find include -name "*.h")

SRC 	=	 $(shell find  -name "*.c")

OBJ  	=	$(SRC:.c=.o)

all: 	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(SRC) $(CFLAGS) $(HEADERS_DIRS) -g3 -gdwarf-4

temp:
	find . -name "*[#,~,.o]" -type f -delete

clean:   temp
	rm -f $(NAME)
	rm -f $(OBJ)

fclean:  clean
	rm -f $(NAME)

re: 	 fclean  all

auteur:  echo $(USER) > auteur

