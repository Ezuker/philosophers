_BOLD=$'\033[0;1m
_UNDER=$'\033[4m
_REV=$'\033[7m
_END=$'\033[0m

# Colors
_GREY=$'\033[30m
_RED=$'\033[31m
_GREEN=$'\033[0;32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
_PURPLE=$'\033[35m
_CYAN=$'\033[36m
_WHITE=$'\033[37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\033[40m
_IRED=$'\033[41m
_IGREEN=$'\033[42m
_IYELLOW=$'\033[43m
_IBLUE=$'\033[44m
_IPURPLE=$'\033[45m
_ICYAN=$'\033[46m
_IWHITE=$'\033[47m

SRC = \
	./src/main.c \
	./src/philo.c \

INCLUDES = \
	-I./include/ \

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo
NORME_ERROR = $(shell norminette $(SRC) include/ | grep "Error" | wc -l)
BOOL_EXEC = 0
EXEC = ./$(NAME)
IS_COMPILING = 0

all: display $(NAME)

exec:
	@$(eval BOOL_EXEC = 1)

$(NAME): $(OBJ)
	@echo
	@echo "$(_BOLD)$(_CYAN)Compiling ($(_RED)$@$(_CYAN))$(_END)"
	@echo
	@echo " $(_BOLD)$(_RED)$(NAME) : $(_END)$(_GREY) $(CC) $(OBJ) $(_END)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo
	@echo "$(_BOLD)$(_CYAN)Other ($(_RED)$@$(_CYAN))$(_END)"
	$(norme)
	@echo
	@ \
	if [ $(BOOL_EXEC) -eq 1 ]; then \
		@echo "$(_BOLD)$(_CYAN)Executing...$(_END)"; \
		@echo; \
		$(EXEC); \
	fi


display :
	@echo
	@echo "		$(_CYAN)	"" ██▓███   ██░ ██  ██▓ ██▓     ▒█████  "
	@echo "		$(_CYAN)	""▓██░  ██▒▓██░ ██▒▓██▒▓██▒    ▒██▒  ██▒"
	@echo "		$(_CYAN)	""▓██░ ██▓▒▒██▀▀██░▒██▒▒██░    ▒██░  ██▒"
	@echo "		$(_CYAN)	""▒██▄█▓▒ ▒░▓█ ░██ ░██░▒██░    ▒██   ██░"
	@echo "		$(_CYAN)	""▒██▒ ░  ░░▓█▒░██▓░██░░██████▒░ ████▓▒░"
	@echo "		$(_CYAN)	""▒▓▒░ ░  ░ ▒ ░░▒░▒░▓  ░ ▒░▓  ░░ ▒░▒░▒░ "
	@echo "		$(_CYAN)	""░▒ ░      ▒ ░▒░ ░ ▒ ░░ ░ ▒  ░  ░ ▒ ▒░ "
	@echo "		$(_CYAN)	""░░        ░  ░░ ░ ▒ ░  ░ ░   ░ ░ ░ ▒  "
	@echo "		$(_CYAN)	""          ░  ░  ░ ░      ░  ░    ░ ░  "

valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXEC)

%.o: %.c
	@ \
	if [ $(IS_COMPILING) -eq 0 ]; then \
		echo "$(_BOLD)$(_CYAN)Entering ($(_RED)./src$(_CYAN))$(_END)"; \
		echo; \
	fi
	@$(eval IS_COMPILING = 1)
	@echo "$(_BOLD)$(_RED) $< : $(_END) $(_GREY) $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(_END)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

define norme =
	@echo
	@ \
	if [ $(NORME_ERROR) -eq 0 ]; then \
		echo "$(_BOLD)$(_GREEN) Norminette passed$(_END)"; \
	else \
		echo "$(_BOLD)$(_RED) Norminette error : $(NORME_ERROR)$(_END)"; \
	fi
endef

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
