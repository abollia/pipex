#--------------------------\\\\\___VARIABLES___/////---------------------------#

MAKEFLAGS	+= --no-print-directory

NAME		=	pipex

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3

OBJ_DIR		=	obj
SRC_DIR		=	src
BSRC_DIR	=	src/bonus

#---------------------------\\\\\___SOURCES___/////----------------------------#

SRC			=	${MAIN} ${UTILS}

MAIN		=	./src/pipex.c 

UTILS		=	./src/pipex_utils.c \
				./src/pipex_struct_utils.c

BONUS		=	./src/bonus/pipex_bonus.c \
				./src/bonus/pipex_struct_bonus.c \
				./src/bonus/pipex_utils_bonus.c

LIBFT		=	./libft/libft.a

OBJ			=	$(patsubst %.c,${OBJ_DIR}/%.o,${SRC})

OBJ_BONUS	=	$(patsubst %.c,${OBJ_DIR}/%.o,${BONUS})

#----------------------------\\\\\___RULES___/////-----------------------------#

all:			${NAME}

${OBJ_DIR}/%.o: %.c | ${OBJ_DIR}
				@mkdir -p $(dir $@)
				@${CC} ${FLAGS} -c $< -o $@

${OBJ_DIR}:
				@mkdir -p ${OBJ_DIR}

${LIBFT}:
				@echo "📡 Pulling libft..."
				@git clone https://github.com/abollia/libft.git > /dev/null 2>&1;
				@make -C libft

vpath %.c . ${SRC_DIR}

${NAME}:		${LIBFT} ${OBJ}
				@echo "🧠 Compiling ${NAME}..."
				@${CC} ${FLAGS} ${OBJ} ${LIBFT} -o ${NAME}
				@echo "✅🦾 ${NAME} is ready!"

bonus:			${LIBFT} ${OBJ_BONUS}
				@echo "🧠 Compiling ${NAME} bonus"
				@${CC} ${FLAGS} ${OBJ_BONUS} ${LIBFT} -o ${NAME}
				@echo "✅🦾 ${NAME} bonus is ready!"

clean:
				@echo "🚮 Removing project files..."
				@rm -rf ${OBJ_DIR}
				@make clean -C ./libft

fclean:			clean
				@echo "🚮 Removing project..."
				@rm -f ${NAME}
				@rm -rf libft
				@echo "❌ ${NAME} has been removed."

re:				fclean all

.PHONY:			all clean fclean re bonus
