NAME			= main
SRCS			= main.c split.c LinkedList.c input.c struct.c
OBJS			= $(SRCS:.c=.o)
CC				= gcc
CFLAG		= 
LIBS				= 

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAG) $(LIBS) -o $(NAME)

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all