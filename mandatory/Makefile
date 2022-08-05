##############################################################################
#	MAKEFILE by Dmercadi
##############################################################################

##############################################################################
#	VARIABLES DEFINITION
##############################################################################
#	Executable output name
NAME_EXECUTABLE = cub3D
#	Directory paths
HEADER_DIRECTORY = includes
SOURCE_DIRECTORY = srcs srcs/dda srcs/errorHandler srcs/loops srcs/moves srcs/parsing2 srcs/draw
MINILIBX_DIRECTORY = lib/minilibx_opengl
LIBFT_DIRECTORY = lib/libft
#	File Objects
SRCS = $(foreach dir, ${SOURCE_DIRECTORY}, ${wildcard $(dir)/*.c})
OBJS = ${SRCS:.c=.o}
#	Compiler Flags
COMPILER_FLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
INCLUDE_FLAGS = -I${HEADER_DIRECTORY}
LIBRARY_FLAGS = -Llib/libft -lft -Llib/minilibx_opengl -lmlx -framework OpenGL -framework AppKit
BONUS_FLAGS = -DBONUS
#	Terminal output coloring
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m

_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m

_IGREY=\x1b[40m
_IRED=\x1b[41m
_IGREEN=\x1b[42m
_IYELLOW=\x1b[43m
_IBLUE=\x1b[44m
_IPURPLE=\x1b[45m
_ICYAN=\x1b[46m
_IWHITE=\x1b[47m

.c.o:
	gcc ${COMPILER_FLAGS} ${INCLUDE_FLAGS} -c $< -o ${<:.c=.o}

${NAME_EXECUTABLE}: ${OBJS}
	@echo "${_BOLD}Compiling Libraries"
	@echo "${_END}${_YELLOW}Compiling Libft"
	@make -C ${LIBFT_DIRECTORY} >/dev/null 2>/dev/null && echo "${_GREEN}Libft compiled sucessfully" || echo "${_RED}Libft compileation failed"
	@echo "${_YELLOW}Compiling MinilibX"
	@make -C ${MINILIBX_DIRECTORY} >/dev/null 2>/dev/null && echo "${_GREEN}MinilibX compiled sucessfully" || echo "${_RED}MinilibX compileation failed"
	@echo "${_YELLOW}Compiling Cub3D"
	@gcc ${COMPILER_FLAGS} ${LIBRARY_FLAGS} ${OBJS} -o ${NAME_EXECUTABLE} && echo "${_GREEN}${NAME_EXECUTABLE} compiled sucessfully" || echo "${_RED}compilation failed"
	@echo "${_END}"

all: ${NAME_EXECUTABLE}

clean:
	@make clean -C ${LIBFT_DIRECTORY}
	@make clean -C ${MINILIBX_DIRECTORY}
	@rm -f ${OBJS}

fclean: clean
	@make fclean -C ${LIBFT_DIRECTORY}
	@rm -f ${NAME_EXECUTABLE}

re: fclean ${NAME_EXECUTABLE}

bonus: ${OBJS}
	@make -C ${LIBFT_DIRECTORY}
	@make -C ${MINILIBX_DIRECTORY}
	@gcc ${COMPILER_FLAGS} ${BONUS_FLAGS} ${LIBRARY_FLAGS} ${OBJS} -o ${NAME_EXECUTABLE}

run: ${NAME_EXECUTABLE}
	./cub3D maps/simple_map.cub

.PHONY: all, clean, fclean, re, bonus