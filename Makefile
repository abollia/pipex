#--------------------------\\\\\___VARIABLES___/////---------------------------#

MAKEFLAGS	+= --no-print-directory

NAME		=	pipex

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3

#---------------------------\\\\\___SOURCES___/////----------------------------#

SRC			=	${MAIN} ${UTILS}

MAIN		=	./src/pipex.c 

UTILS		=	./src/pipex_utils.c \
				./src/pipex_struct_utils.c

BONUS		=	./src/bonus/pipex_bonus.c \
				./src/bonus/pipex_struct_bonus.c \
				./src/bonus/pipex_utils_bonus.c

LIBFT		=	./libft/libft.a

OBJ			=	${SRC:.c=.o}

OBJ_BONUS	=	${BONUS:.c=.o}

#----------------------------\\\\\___RULES___/////-----------------------------#

all:			${NAME}

%.o: %.c
				@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${LIBFT}:
				@echo "🧠 Compiling libft..."
				@make -C libft

${NAME}:		${OBJ} ${LIBFT}
				@echo "🧠 Compiling ${NAME}..."
				@${CC} ${FLAGS} ${OBJ} ${LIBFT} -o ${NAME}
				@echo "✅ 🦾 ${NAME} is ready!"

bonus:			${OBJ_BONUS} ${LIBFT}
				@echo "🧠 Compiling ${NAME} bonus"
				@${CC} ${FLAGS} ${OBJ_BONUS} ${LIBFT} -o ${NAME}
				@echo "✅ 🦾 ${NAME} bonus is ready!"

clean:
				@echo "🚮 Removing project files..."
				@rm -f ${OBJ} ${OBJ_BONUS}
				@make clean -C ./libft

fclean:			clean
				@echo "🚮 Removing project..."
				@rm -f ${NAME}
				@rm -f ${LIBFT}
				@echo "❌ ${NAME} has been removed."

re:				fclean all

.PHONY:			all clean fclean re bonus
