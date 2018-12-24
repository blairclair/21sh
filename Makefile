LIBFT=libft/libft.a
PRINT=libft/printf_functions/libftprintf.a
CC=gcc
CFLAGS= -Wall -Wextra -Werror -ltermcap
SRCS= line_edition/cpy.c\
line_edition/del_line_ed.c\
line_edition/move_words.c\
line_edition/line_edition.c\
line_edition/move_cursor.c\
line_edition/move_cursor_two.c\
line_edition/rep_line_one.c\
line_edition/rep_line_two.c\
line_edition/insert_delete.c\
line_edition/history.c\
line_edition/history_rep_line.c\
utils/utils.c\
utils/utils_two.c\
utils/utils_three.c\
utils/utils_four.c\
utils/utils_parsing.c\
utils/utils_exec.c\
builtins/ft_cd.c\
builtins/ft_cd_two.c\
builtins/extra_cd.c\
builtins/set_envs.c\
builtins/get_envs.c\
builtins/unset_envs.c\
builtins/ft_echo.c\
parsing/cmd_parsing.c\
parsing/find_flags.c\
parsing/parsing.c\
parsing/redir_parsing.c\
pipe_and_redir/heredoc_pipe_redir.c\
pipe_and_redir/heredoc_redir.c\
pipe_and_redir/multiple_pipes_to_redir.c\
pipe_and_redir/pipe_mult.c\
pipe_and_redir/piping.c\
pipe_and_redir/redir_left.c\
pipe_and_redir/redirstuff.c\
pipe_and_redir/fd_aggregation.c\
exec/execstuff.c\
exec/pipe_exec.c\
exec/redir_exec.c\
process.c\
manage_path.c\
init_values.c\
signal_handle.c\
free_vars.c\
term_setup.c\
parenthesis_management.c\
begin.c
OBJ = $(SRC:.c=.o)
NAME=21sh

all: $(NAME)

$(NAME): $(SRCS)
	make -C libft/
	make -C libft/printf_functions/
	$(CC) -c $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT) $(PRINT)
clean:
	/bin/rm -f *.o
	make -C libft/ clean
	make -C libft/printf_functions/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean
	make -C libft/printf_functions/ fclean

re: fclean all
