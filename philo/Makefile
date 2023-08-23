# -=-=-=-=-	NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
NAME			= philosophers
PHILO		= philo
MK			= Makefile

# -=-=-=-=-	CLRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

RESET		:= \033[0;39m
BLACK		:= \033[0;30m
RED			:= \033[0;91m
GREEN		:= \033[0;92m
YELLOW		:= \033[0;93m
BLUE		:= \033[0;94m
MAGENTA		:= \033[0;95m
CYAN		:= \033[0;96m
GRAY		:= \033[0;90m
WHITE		:= \033[0;97m

# -=-=-=-=-	DIRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
SRC_DIR	= src/
OBJ_DIR	= obj/
INC_DIR	= hdrs/

# -=-=-=-=-	CMNDS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
CC			= gcc
SANS		= -fsanitize=address -g
CFLAGS		= -Wall -Werror -Wextra
AR			= ar -rcs
RM			= rm -f
MKDIR		= mkdir -p
CP			= cp -f
MAKE		= make -s
# -=-=-=-=-	HEADERS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
HDRS		= $(INC_DIR)philosophers.h
# -=-=-=-=-	SOURCES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRCS		:= philosophers.c parse.c

# -=-=-=-=-	OBJECTS/DEPENDENCIES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

OBJS		:= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEP			+= $(addsuffix .d, $(basename $(OBJS)))

# -=-=-=-=-	MAKING LIBS AND COMPILING WITH THEM -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: $(NAME)

$(NAME):
	@$(MAKE) $(PHILO)

$(PHILO):: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(PHILO)
	@echo "$(GREEN)🧠🗣PHILO COMPILED🧠🗣$(RESET)"

$(PHILO)::
	@echo "$(BLUE)Nothing to be done for $@$(RESET)"
	
clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(CYAN)Dependencies and objects removed$(RESET)"

fclean:	clean
	@$(RM) $(PHILO)
	@echo "$(RED)$(PHILO) succesfully removed$(RESET)"

re: fclean all

-include $(DEP)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(MK) $(HDRS)
	@$(MKDIR) $(dir $@)
	@echo "$(MAGENTA)Compiling: $<$(RESET)"
	@$(CC) -MT $@ -MMD -MP $(CFLAGS) -c $< -o $@

.PHONY:	all clean fclean re
