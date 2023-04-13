PHILO		= 	philo
# PHILO_BONUS	=	philo_bonus
CFLAGS		= 	-Wall -Werror -Wextra
CC			= 	cc
RM			=	rm -rf
INCLUDE 	= 	-I include

MAN_FILES	=	src_man/philo.c src_man/utils.c
# BONUS_FILES	=	src_bonus/philo_bonus.c

MAN_OBJ		=	$(MAN_FILES:.c=.o)
# BONUS_OBJ	=	$(BONUS_FILES:.c=.o)

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

# $(PHILO_BONUS): $(BONUS_OBJ)
# 	$(CC) $(CFLAGS) -o $(PHILO_BONUS) $(BONUS_OBJ) $(INCLUDE)
# 	@echo "$(GREEN)*** Philo_Bonus compiled!***$(WHITE)"

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

# bonus: $(PHILO_BONUS)

# Philo_Bonus
# $(RM) $(BONUS_OBJ)

clean:
	$(RM) $(MAN_OBJ)
	@echo "$(BLUE)*** Object files Philo cleaned! ***$(WHITE)"

fclean: clean
	$(RM) $(PHILO)
	@echo "$(BLUE)*** Executable Philo cleaned! ***$(WHITE)"

re: fclean all
	@echo "$(GREEN)*** Cleaned and rebuilt Philo! ***$(WHITE)"

.PHONY:  bonus fclean re all