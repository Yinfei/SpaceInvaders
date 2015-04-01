CC  	= gcc
SRC 	= $(wildcard *.c)
NAME	= SpaceInvaders
OBJ   = $(SRC:.c=.o)
RM		= rm -f
CFLAGS	=	-ansi -pedantic -W -Wall -Werror `sdl2-config --cflags`
LDFLAGS	=	`sdl2-config --libs` -lSDL2_image

$(NAME) : $(OBJ)
	  gcc $(CFLAGS) $(SRC) -o SpaceInvaders $(LDFLAGS)

all	: $(NAME)

clean	:
	  $(RM) $(OBJ)

fclean	: clean
	  $(RM) $(NAME)

re	: fclean all
