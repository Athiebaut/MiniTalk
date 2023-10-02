SRCC = Src/ft_client.c
SRCS = Src/ft_server.c
OBJS = ${SRCS:.c=.o}
OBJC = ${SRCC:.c=.o}
NAMES = server 
NAMEC = client 
PRINTF = Printf/libftprintf.a
LIBFT = Libft/libft.a
CC = cc 
FLAGS = -Wall -Wextra -Werror
RM = rm -f

${NAMES}: ${OBJS}
	make -C Printf
	${CC} ${FLAGS} ${OBJS} -I Inc ${PRINTF} -o ${NAMES}

server: ${NAMES}

${NAMEC}: ${OBJC}
	make -C Printf
	make -C Libft
	${CC} ${FLAGS} ${OBJC} -I Inc ${PRINTF} ${LIBFT} -o ${NAMEC}

client: ${NAMEC}

clean:
	make clean -C Printf
	make clean -C Libft
	${RM} ${OBJS} ${OBJC}

fclean: clean
	make fclean -C Printf
	make fclean -C Libft
	${RM} ${NAMES} ${NAMEC}
	${RM} ${PRINTF} ${LIBFT}

re: fclean client server