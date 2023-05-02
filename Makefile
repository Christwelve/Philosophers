PHILO		= 	philo
CFLAGS		= 	-Wall -Werror -Wextra -g -fsanitize=address
CC			= 	cc
RM			=	rm -rf
INCLUDE 	= 	-I include

MAN_FILES	=	src_man/philo.c src_man/check_input.c src_man/utils.c src_man/loops.c \
				src_man/loops_utils.c src_man/threads.c src_man/set.c

MAN_OBJ		=	$(MAN_FILES:.c=.o)

GREEN		= 	\033[0;32m
BLUE		=	\033[0;94m
WHITE		=	\033[0m


ifdef DEBUG
	CFLAGS += -g
endif

# RULES

all: $(PHILO)

$(PHILO): $(MAN_OBJ)
	$(CC) $(CFLAGS) -o $(PHILO) $(MAN_OBJ) $(INCLUDE)
	@echo "$(GREEN)*** Philo compiled!***$(WHITE)"


%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(MAN_OBJ)
	@echo "$(BLUE)*** Object files Philo cleaned! ***$(WHITE)"

fclean: clean
	$(RM) $(PHILO)
	@echo "$(BLUE)*** Executable Philo cleaned! ***$(WHITE)"

re: fclean all
	@echo "$(GREEN)*** Cleaned and rebuilt Philo! ***$(WHITE)"

.PHONY:  bonus fclean re all