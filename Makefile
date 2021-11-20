SERVER = server

CLIENT = client

CC = clang

FLAGS = -Wall -Wextra -Werror

LIBFT = libft-printf

INCLUDES = includes

%.o : %.c
	@$(CC) $(FLAGS) $< -c -I $(INCLUDES)

all: $(SERVER) $(CLIENT)

$(SERVER): srcs/server.o
		make -C $(LIBFT) all
		$(CC) $(FLAGS) server.o $(LIBFT)/libftprintf.a -o server

$(CLIENT): srcs/client.o
		make -C $(LIBFT) all
		$(CC) $(FLAGS) client.o $(LIBFT)/libftprintf.a -o client

clean:
		make -C $(LIBFT) clean
		rm -rf client.o server.o

fclean: clean
		make -C $(LIBFT) fclean
		rm -rf $(CLIENT) $(SERVER)

re: fclean all
