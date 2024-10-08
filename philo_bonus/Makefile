################################################################################
##                              COMPILER CHECK                                ##
################################################################################

HAS_GCC := $(shell command -v gcc 2> /dev/null)
HAS_CLANG := $(shell command -v clang 2> /dev/null)

ifdef HAS_CLANG
  CC = clang
else ifdef HAS_GCC
  CC = gcc
else
  $(error No compiler found)
endif

NAME = philo_bonus
FLAGS = -Wall -Wextra -Werror
LINKS = -lpthread -lrt

################################################################################
##                              SOURCES AND OBJECTS                           ##
################################################################################

SRC = main.c \
	  check_death_while_usleep.c \
	  create_philosophers.c \
	  philo_routine.c \
	  one_philo_routine.c \
	  start_philo_routines.c \
	  philo_actions.c \
	  get_time.c \
	  watcher_routine.c \
	  init_watchers.c \
	  monitor_watchers.c \
      print_state.c \
      ft_atoi.c \
	  ft_itoa.c \
	  ft_strlen.c \
	  ft_strjoin.c \
	  ft_strlcpy.c \
	  safe_malloc.c \
	  safe_fork.c \
	  safe_pthread.c

OBJ = $(SRC:%.c=obj/%.o)

################################################################################
##                                    COLORS                                  ##
################################################################################

END=\033[0m
BOLD=\033[1m
GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
YELLOW=\033[33m
MAGENTA=\033[35m
TURQUOISE=\033[36m

################################################################################
##                                     RULES                                  ##
################################################################################

all : head $(NAME)

head :
	@echo "$(MAGENTA)"
	@echo "\t██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗"
	@echo "\t██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝"
	@echo "\t██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗"
	@echo "\t██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║"
	@echo "\t██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║"
	@echo "\t╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝"                                                                                
	@echo ""
	@echo "\t                               42_Malaga: by jorvarea"
	@echo "\tProyect: \033[36m philosophers $(MAGENTA)"
	@echo "\tCommands:\033[36m all clean fclean re bonus $(BLUE)"
	@echo "\t🛠   Compiler: $(CC) $(END)\n"

$(NAME) : line $(OBJ)
	@echo "✦ -------------------------- ✦$(END)"
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LINKS)

line :
	@echo "$(GREEN) $(BOLD)"
	@echo "  COMPILING PHILOSOPHERS...$(END) $(GREEN)"
	@echo "✦ -------------------------- ✦"

obj/%.o: %.c philosophers.h
	@mkdir -p obj
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(GREEN)  ✓ Compiled: $(notdir $<)"

clean :
	@printf "\n$(YELLOW) 🗑   Removing objects$(END)"
	@rm -f obj/*.o
	@rmdir obj 2>/dev/null || true
	@echo "$(GREEN)\r  ✓  $(RED)Removed  objects from $(NAME) $(END)"

fclean: clean
	@printf "$(YELLOW) 🗑   Removing $(NAME) $(END)"
	@rm -f $(NAME)
	@echo "$(GREEN)\r  ✓  $(RED)Removed  $(NAME) $(END)\n"

re : fclean all

.PHONY: all clean fclean re