NAME = pipex

CC = cc
C_FLAGS = -Wall -Wextra -Werror

LIB_DIR = lib
SRC_DIR = src

LIBS = $(addprefix $(LIB_DIR)/, $(LIB_NAME))
SRCS = main.c child.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(C_FLAGS) -L $(LIB_DIR)/ -lyusung -o $@ $^

%.o : %.c
	$(CC) $(C_FLAGS) -c $^

clean :
	make -C $(LIB_DIR) clean
	rm -f $(OBJS)
 
fclean : clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re : 
	make fclean
	make all

PHONY	: all clean fclean re
