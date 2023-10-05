SRCC = Src/ft_client.c
SRCS = Src/ft_server.c
OBJS = ${SRCS:.c=.o}
OBJC = ${SRCC:.c=.o}
NAMES = server 
NAMEC = client

SRCBC = Src/ft_client_bonus.c
SRCBS = Src/ft_server_bonus.c
OBJBS = ${SRCBS:.c=.o}
OBJBC = ${SRCBC:.c=.o}
NAMEBS = server_bonus 
NAMEBC = client_bonus

PRINTF = Printf/libftprintf.a
LIBFT = Libft/libft.a
CC = cc 
FLAGS = -Wall -Wextra -Werror
RM = rm -f

${NAMES}: ${OBJS}
	make -C Printf
	make -C Libft
	${CC} ${FLAGS} ${OBJS} -I Inc ${PRINTF} ${LIBFT} -o ${NAMES}

${NAMEC}: ${OBJC}
	make -C Printf
	make -C Libft
	${CC} ${FLAGS} ${OBJC} -I Inc ${PRINTF} ${LIBFT} -o ${NAMEC}

all: server client

${NAMEBS}: ${OBJBS}
	make -C Printf
	make -C Libft
	${CC} ${FLAGS} ${OBJBS} -I Inc ${PRINTF} ${LIBFT} -o ${NAMEBS}

${NAMEBC}: ${OBJBC}
	make -C Printf
	make -C Libft
	${CC} ${FLAGS} ${OBJBC} -I Inc ${PRINTF} ${LIBFT} -o ${NAMEBC}

bonus: server_bonus client_bonus

clean:
	make clean -C Printf
	make clean -C Libft
	${RM} ${OBJS} ${OBJC}
	${RM} ${OBJBS} ${OBJBC}

fclean: clean
	make fclean -C Printf
	make fclean -C Libft
	${RM} ${NAMES} ${NAMEC}
	${RM} ${NAMEBS} ${NAMEBC}
	${RM} ${PRINTF} ${LIBFT}

re: fclean client server

.PHONY: all bonus clean fclean