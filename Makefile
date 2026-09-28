NAME        = push_swap

CFLAGS      = -Wall -Wextra -Werror
AR      := ar rcs
RM      := rm -f

SRCS    := main.c errors_cleaner.c ft_atol.c ft_auxiliary.c nodes.c normalize.c lis.c lis_inverted.c operations_one.c operations_two.c turkish.c turkish_targets.c turkish_costs.c turkish_push_cheaper.c sort_two_to_five.c turkish_rotations.c main_functions.c ft_split.c lis_init.c

OBJ         = $(SRCS:.c=.o)

# ====== REGLA PRINCIPAL ======
all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

# ====== COMPILACIÓN DE OBJETOS ======
# Incluimos el directorio de libft para poder hacer #include "libft.h"
%.o: %.c
	cc $(CFLAGS) -c $< -o $@

# ====== LIMPIEZA ======
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re