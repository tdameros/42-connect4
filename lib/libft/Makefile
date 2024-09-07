NAME			=	libft.a

SRCS			=	src/char/ft_isalnum.c \
					src/char/ft_isalpha.c \
					src/char/ft_isascii.c \
					src/char/ft_isdigit.c \
					src/char/ft_isprint.c \
					src/char/ft_tolower.c \
					src/char/ft_toupper.c \
					src/int/ft_atoi.c \
					src/list/ft_lstadd_back.c \
					src/list/ft_lstadd_front.c \
					src/list/ft_lstclear.c \
					src/list/ft_lstdelone.c \
					src/list/ft_lstiter.c \
					src/list/ft_lstlast.c \
					src/list/ft_lstmap.c \
					src/list/ft_lstnew.c \
					src/list/ft_lstsize.c \
					src/mem/ft_bzero.c \
					src/mem/ft_calloc.c \
					src/mem/ft_memchr.c \
					src/mem/ft_memcmp.c \
					src/mem/ft_memcpy.c \
					src/mem/ft_memmove.c \
					src/mem/ft_memset.c \
					src/print/ft_printf.c \
					src/print/print_hexa.c \
					src/print/print_number.c \
					src/print/print_string.c \
					src/put/ft_putchar_fd.c \
					src/put/ft_putendl_fd.c \
					src/put/ft_putnbr_fd.c \
					src/put/ft_putstr_fd.c \
					src/string/ft_is_number.c \
					src/string/ft_itoa.c \
					src/string/ft_split.c \
					src/string/ft_strchr.c \
					src/string/ft_strdup.c \
					src/string/ft_striteri.c \
					src/string/ft_strjoin.c \
					src/string/ft_strlcat.c \
					src/string/ft_strlcpy.c \
					src/string/ft_strlen.c \
					src/string/ft_strmapi.c \
					src/string/ft_strncmp.c \
					src/string/ft_strcmp.c \
					src/string/ft_strnstr.c \
					src/string/ft_strrchr.c \
					src/string/ft_strtrim.c \
					src/string/ft_substr.c \
					src/file/get_next_line.c \
					src/file/get_next_line_utils.c

DIR_INCS		=	include/
DIR_BUILD		=	.build/
OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
DEPS			=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
DEPS_FLAGS		=	-MMD -MP
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf
AR				= 	ar rcs

all : $(NAME)

$(NAME) : $(OBJS)
		$(AR) $(NAME) $(OBJS)

clean :
		$(RM) $(DIR_BUILD)

fclean : clean
		$(RM) $(NAME)

re : fclean
	$(MAKE) all

-include $(DEPS)

$(DIR_BUILD)%.o : %.c
		mkdir -p $(shell dirname $@)
		$(CC) $(CFLAGS) $(DEPS_FLAGS) -I $(DIR_INCS) -c $< -o $@

.PHONY: all clean fclean re
