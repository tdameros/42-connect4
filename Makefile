#*******************************  VARIABLES  **********************************#

NAME			=	connect4

# --------------- FILES --------------- #

include src.mk

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
DIR_INCLUDES 	=	\
					$(DIR_INCLUDE) \
					$(DIR_LIBFT)include/
DIR_LIB			= 	lib/
DIR_LIBFT		=	$(DIR_LIB)libft/
LIBFT			=	$(DIR_LIBFT)libft.a

# ------------- SHORTCUTS ------------- #

OBJ				=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEP				=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
SRC				=	$(addprefix $(DIR_SRC),$(LIST_SRC))
INCLUDES		=	$(addprefix -I , $(DIR_INCLUDES))
MAKELIBFT		=	$(MAKE) -C $(DIR_LIBFT)

# ------------ COMPILATION ------------ #

CFLAGS			=	-Wall -Wextra -Werror -O3
DEBUG_CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g3

DEP_FLAGS		=	-MMD -MP

# -------------  COMMANDS ------------- #

RM				=	rm -rf
MKDIR			=	mkdir -p
OS				=	$(shell uname -s)

ifeq ($(OS), Linux)
	LIBS_FLAGS		=	-lncursesw -L$(DIR_LIBFT) -lft
endif
ifeq ($(OS), Darwin)
	LIBS_FLAGS		=	-lncurses -L$(DIR_LIBFT) -lft
endif

#***********************************  RULES  **********************************#

.PHONY: all
all:
				$(MAKELIBFT)
				$(MAKE) $(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS_FLAGS)

# ---------- COMPILED RULES ----------- #

-include $(DEP)

$(DIR_BUILD)%.o: %.c
				mkdir -p $(shell dirname $@)
				$(CC) $(CFLAGS) $(DEP_FLAGS) $(INCLUDES) -c $< -o $@

.PHONY: run
run:	all
				./$(NAME)

.PHONY: clean
clean:
				$(MAKELIBFT) clean
				$(RM) $(DIR_BUILD)

.PHONY: fclean
fclean: clean
				$(MAKELIBFT) fclean
				$(RM) $(NAME)

.PHONY: re
re:				fclean
				$(MAKE) all

.PHONY: debug
debug:	fclean
				$(MAKE) all CFLAGS="$(DEBUG_CFLAGS)"

.PHONY: check-format
check-format:
				clang-format -style=file $(SRC) -n --Werror

.PHONY: format
format:
				clang-format -style=file $(SRC) -i

.PHONY: build_docker_image
build_docker_image:
				docker build -t ${NAME} .

.PHONY: run_docker_container
run_docker_container:
				docker run --rm -it ${NAME}
