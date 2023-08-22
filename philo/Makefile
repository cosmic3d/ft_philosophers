# -=-=-=-=-	NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
NAME			= minitalk
SERVER		= server
CLIENT		= client
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
LIB_DIR	= lib/ft_libft/
PRINTF_DIR = lib/ft_printf/

# -=-=-=-=-	CMNDS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
CC			= gcc
SANS		= -fsanitize=address -g
CFLAGS		= -Wall -Werror -Wextra
AR			= ar -rcs
RM			= rm -f
MKDIR		= mkdir -p
CP			= cp -f
MAKE		= make -s
# -=-=-=-=-	LIBS/HEADERS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

LIBS		+= $(LIB_DIR)libft.a
LIBS		+= $(PRINTF_DIR)libftprintf.a
LIBS_HDRS	+= $(INC_DIR)minitalk.h
INCLUDE		= -I $(LIBS_HDRS) -I $(LIB_DIR)

# -=-=-=-=-	SOURCES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRCS_SERVER		:= server.c utils.c
SRCS_CLIENT		:= client.c utils.c

# -=-=-=-=-	OBJECTS/DEPENDENCIES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

OBJS_SERVER		:= $(addprefix $(OBJ_DIR), $(SRCS_SERVER:.c=.o))
OBJS_CLIENT		:= $(addprefix $(OBJ_DIR), $(SRCS_CLIENT:.c=.o))
DEP			+= $(addsuffix .d, $(basename $(OBJS_SERVER)))
DEP			+= $(addsuffix .d, $(basename $(OBJS_CLIENT)))

# -=-=-=-=-	MAKING LIBS AND COMPILING WITH THEM -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: $(NAME) make_libs

make_libs:
	@$(MAKE) -sC $(LIB_DIR)
	@$(MAKE) -sC $(PRINTF_DIR)

$(NAME): make_libs
	@$(MAKE) $(SERVER)
	@$(MAKE) $(CLIENT)

$(SERVER):: $(OBJS_SERVER)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBS) -o $(SERVER)
	@echo "$(GREEN)🧩SERVER COMPILED🧩$(RESET)"

$(SERVER)::
	@echo "$(BLUE)Nothing to be done for $@$(RESET)"

$(CLIENT):: $(OBJS_CLIENT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBS) -o $(CLIENT)
	@echo "$(GREEN)🧩CLIENT COMPILED🧩$(RESET)"

$(CLIENT)::
	@echo "$(BLUE)Nothing to be done for $@$(RESET)"
	
clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -sC $(LIB_DIR)
	@make clean -sC $(PRINTF_DIR)
	@echo "$(CYAN)Dependencies and objects removed$(RESET)"

fclean:	clean
	@$(RM) $(SERVER) $(CLIENT)
	@make fclean -sC $(LIB_DIR)
	@make fclean -sC $(PRINTF_DIR)
	@echo "$(RED)$(SERVER) and $(CLIENT) succesfully removed$(RESET)"

re: fclean all

-include $(DEP)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(MK)
	@$(MKDIR) $(dir $@)
	@echo "$(YELLOW)Compiling: $<$(RESET)"
	@$(CC) -MT $@ -MMD -MP $(CFLAGS) -c $< -o $@

.PHONY:	all clean fclean re make_libs bonus
