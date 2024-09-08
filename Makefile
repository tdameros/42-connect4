NAME = connect4

# *** FILES ****************************************************************** #

MAKE_DIR := .make/
BUILD_DIR := $(MAKE_DIR)$(shell git branch --show-current)/

SRCS_DIR = src/
SRCS = $(addsuffix .c, $(SRC))

OBJS = $(patsubst %.c,$(BUILD_DIR)%.o,$(SRCS))

DEPS = $(patsubst %.o,%.d,$(OBJS))

SRC = \
	ai_play \
	display	\
	heuristic \
	init		\
	main		\
	user_play	\
	utils \
	win \
	score \

# *** LIBRARIES && INCLUDES  ************************************************* #

LIBS_PATH = \
	lib/libft/libft.a \
		
LIBS = \
	$(patsubst lib%.a,%,$(notdir $(LIBS_PATH))) \

INCS_DIR = include/
INCS = \
	$(INCS_DIR) \
	$(dir $(LIBS_PATH)) \
	$(addsuffix $(INCS_DIR),$(dir $(LIBS_PATH))) \

# *** CONFIG ***************************************************************** #

CFLAGS		=	-Wall -Wextra -Werror $(OFLAGS)
OFLAGS 		=	-Ofast -flto -march=native

DEFINES		=

CPPFLAGS 	=	\
				$(addprefix -D, $(DEFINES)) \
				$(addprefix -I, $(INCS)) \
				-MMD -MP \

LDFLAGS		=	$(addprefix -L, $(dir $(LIBS_PATH)))
LDLIBS		=	$(addprefix -l, $(LIBS))

MAKEFLAGS	=	--no-print-directory

# *** COMPILATION MODES ****************************************************** #

MODE_TRACE = $(MAKE_DIR).trace 
LAST_MODE = $(shell cat $(MODE_TRACE) 2>/dev/null)

MODE ?=

ifneq ($(MODE),)
BUILD_DIR := $(BUILD_DIR)$(MODE)/
endif

ifeq ($(MODE),debug)
CFLAGS := $(filter-out $(OFLAGS),$(CFLAGS)) -g3
else ifeq ($(MODE),fsanitize)
CFLAGS := $(filter-out $(OFLAGS),$(CFLAGS)) -g3 -fsanitize=address
else ifeq ($(MODE),animation)
DEFINES += ANIMATION
else ifneq ($(MODE),)
ERROR = MODE
endif

ifneq ($(LAST_MODE),$(MODE))
$(NAME) : FORCE
endif

# *** MISC ******************************************************************* #

LOGFILE = $(MAKE_DIR).mklog

LOADING_BAR_SIZE = 48

# *** TARGETS **************************************************************** #

.PHONY : all
all : $(NAME)

$(NAME) : $(LIBS_PATH) $(OBJS) | PREMAKE
	@echo "$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)" >> $(LOGFILE)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "$(MODE)" > $(MODE_TRACE)
	@printf "\n$(BOLD)\nCONNECT4$(RESET) @tdameros @ibertran\n"

$(BUILD_DIR)%.o : $(SRCS_DIR)%.c | count PREMAKE
	@true || echo "$(NAME)_object"
	$(eval COUNT_DONE := $(shell echo $$(($(COUNT_DONE) + 1))))
	$(eval LOADING_COMPLETED := $(shell echo "$(COUNT_DONE) * $(LOADING_BAR_SIZE) / $(COUNT_TOTAL)" | bc 2> /dev/null))
	@mkdir -p $(@D)
	@echo "$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@" >> $(LOGFILE)
	@$(CC) $(CPPFLAGS)  $(CFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BOLD)$(CC) $(BLUE)$(CFLAGS) $(CPPFLAGS) $(YELLOW)$(patsubst $(MAKE_DIR)%, %, $(basename $@)) $(RESET)\n"
	@printf "🔧 $(BOLD)$(CYAN)Compiling sources: $(WHITE)["
	@for i in $(shell seq 1 $(LOADING_COMPLETED)); do printf "="; done 
	@for i in $(shell seq 1 $(shell echo "$(LOADING_BAR_SIZE) - $(LOADING_COMPLETED)" | bc 2> /dev/null)); do printf " "; done
	@printf "] $(shell echo "$(COUNT_DONE) * 100 / $(COUNT_TOTAL)" | bc 2> /dev/null)%%$(RESET)"

$(LIBS_PATH): FORCE | PREMAKE
	@$(MAKE) -C $(@D)

.PHONY : animation
animation :
	$(MAKE) MODE=animation

.PHONY : debug
debug :
	$(MAKE) MODE=debug

.PHONY : fsanitize
fsanitize :
	$(MAKE) MODE=fsanitize

.PHONY : clean
clean :
	-for f in $(dir $(LIBS_PATH)); do $(MAKE) -s -C $$f $@; done
	rm -rf $(BUILD_DIR)
	@printf "🚮 $(BOLD)$(RED)$(NAME) building files removed!$(RESET)\n"

.PHONY : fclean
fclean :
	-for f in $(dir $(LIBS_PATH)); do $(MAKE) -s -C $$f $@; done
	rm -rf $(MAKE_DIR) $(NAME)
	@printf "🚮 $(BOLD)$(RED)$(NAME) files removed!$(RESET)\n"

.PHONY : re
re : fclean
	$(MAKE)

.PHONY : print-%
print-% :
	@echo $(patsubst print-%,%,$@)=
	@echo $($(patsubst print-%,%,$@))

.PHONY : count
count :
ifneq ($(AS_COUNTED),TRUE)
	$(eval COUNT_TOTAL := $(shell $(MAKE) -j -n MODE=$(MODE) AS_COUNTED=TRUE | grep "$(NAME)_object" | wc -l))
	$(eval COUNT_DONE := 0)
endif

.PHONY : run
run : $(NAME)
	./$(NAME)

VALGRIND = \
	valgrind \
	--leak-check=full \
	--trace-children=yes \
	--track-fds=yes \
	--show-leak-kinds=all \

.PHONY : valgrind
valgrind : debug
	$(VALGRIND) ./$(NAME)

.PHONY: check-format
check-format:
	clang-format -style=file $(addprefix $(SRCS_DIR),$(SRCS)) -n --Werror

.PHONY: format
format:
	clang-format -style=file $(addprefix $(SRCS_DIR),$(SRCS)) -i

.PHONY: build_docker_image
build_docker_image:
	docker build -t $(NAME) .

.PHONY: run_docker_container
run_docker_container:
	docker run --rm -it $(NAME)


# *** SPECIAL TARGETS ******************************************************** #

-include $(DEPS)

.DEFAULT_GOAL := all

.SILENT : clean fclean re debug fsanitize norminette

.PHONY : FORCE
FORCE :

.PHONY : PREMAKE
PREMAKE :
ifneq ($(MODE),)
	@printf "🔨 $(BOLD)Building $(NAME)($(MODE))...$(RESET)\n"
else
	@printf "🔨 $(BOLD)Building $(NAME)...$(RESET)\n"
endif
	@rm -f $(LOGFILE)
ifeq ($(ERROR),MODE)
	$(error Invalid mode: $(MODE))
endif

# *** FANCY STUFF ************************************************************ #

RESET	=	\e[0m
ERASE	=	\033[2K\r
BOLD	=	\033[1m
UNDER	=	\033[4m
SUR		=	\033[7m
GREY	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PURPLE	=	\033[35m
CYAN	=	\033[36m
WHITE	=	\033[37m
C12	=	\033[39m
C13	=	\033[43m

# **************************************************************************** #