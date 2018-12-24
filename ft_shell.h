/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 10:46:31 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:52:55 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H
# include "libft/libft.h"
# include "libft/printf_functions/ft_printf.h"
# include <dirent.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <term.h>
# include <termios.h>
# define LEFT 0x445B1B
# define RIGHT 0x435B1B
# define ENTER 0xA
# define F6 542091860763
# define F5 542058306331
# define COPKEY 42947
# define PASTEKEY 32975
# define CUTKEY 8948194
# define HIGHLIGHT 39371
# define UPLINE 41410
# define DOWNLINE 10650850
# define DELLINE 8554722
# define BACK 0x7F
# define WORDLEFT 25115
# define WORDRIGHT 26139
# define UP 4283163
# define DOWN 4348699
# define RED   "\x1B[31m"
# define BLUE  "\x1B[34m"
# define BLACK "\033[30m"
# define WORDMOVE d == WORDLEFT || d == WORDRIGHT
# define CHARMOVE d == LEFT || d == RIGHT
# define HOMEEND d == F5 || d == F6
# define DELETE d == BACK
# define EDIT d == HIGHLIGHT || d == CUTKEY || d == COPKEY || d == PASTEKEY
# define HISTORY d == UP || d == DOWN
# define LINEMOVE d == UPLINE || d == DOWNLINE

typedef	struct			s_termstuff
{
	struct termios		newterm;
	struct termios		oldterm;
	int					track;
	int					highlong;
	int					highpos;
	int					*selected;
	char				*highcpy;
	int					historypos;
	char				*origline;
	int					collen;
	int					rowlen;
	int					multine;
	int					newrow;
	char				herestring[50];
	int					num_hist;
	int					row_pos;
	int					changed_len;
	int					prev_row_len;
	int					whole_line_len;
	int					delline;
}						t_term_stuff;

t_term_stuff			g_termstuff;
char					g_history[2000][200];

typedef struct			s_env_vars
{
	char				**env_names;
	char				**env_values;
	int					num_envs;
	char				**full_envs;
	char				*oldpwd;
}						t_env_vars;

enum					e_tok_type
{
	UNKNOWN = 1,
	SEMICOLON = 2,
	AND = 3,
	PIPE = 5,
	REDIR1LEFT = 6,
	REDIR1RIGHT = 7,
	REDIR2LEFT = 8,
	REDIR2RIGHT = 9,
	REGCMD = 11,
	NUM = 12,
	MINUS = 13,
	END = 14

};
typedef enum e_tok_type	t_tok_type;
typedef struct			s_execute
{
	t_tok_type			type;
	int					status;
	char				**data;
	struct s_execute	*prev;
	struct s_execute	*next;

}						t_execute;

int						ft_cd(char **args, t_env_vars *env_vars);
int						ft_echo(char **args, t_env_vars *env_vars);
void					initialize_envs(t_env_vars *env_vars);
void					free_envs(t_env_vars *env_vars);
int						ft_env(t_env_vars *env_vars);
int						get_num_args_minishell(char **args);
int						ft_setenv(char **args, t_env_vars *env_vars);
int						ft_unset_env(char **arg, t_env_vars *env_vars);
int						check_path(char **args, t_env_vars *env_vars);
int						get_process(char **args, char *arg,
						t_env_vars *env_vars);
char					*get_val(char *value, t_env_vars *env_vars);
void					free_args(char **args);
int						resort_env(t_env_vars *env_vars, int i);
int						is_env(t_env_vars *env_vars, char *arg);
int						ft_cd_home(t_env_vars *env_vars);
int						tilda_home(char **args, char *tmpcwd,
						t_env_vars *env_vars);
int						tilda_other(char **args, char *tmparg, char *tmpcwd);
int						tilda_cd(char **args, t_env_vars *env_vars);
int						ft_exit(t_env_vars *env_vars);
void					get_user();
void					sighandlec(int i);
char					*ft_strtok(char *s, const char *delim);
int						move_words_left(char *str);
int						move_words_right(char *str);
int						ft_charput(int c);
void					move_highlight(char *str);
void					reset_highlight(char *str);
void					ft_copy(char *str);
char					*ft_paste(char *str, int j);
void					save_history(char *str);
char					*get_history_up(char *str);
char					*get_history_down(char *str);
int						num_quotes(char *str);
char					*loop_quote(char *str, int singdoub);
char					*get_new_str(char *str, char c);
void					sighandlewindow(int i);
char					*get_del_str(char *str);
char					*ft_cut(char *str);
void					print_args(char **args);
int						get_bfunc(char **args, t_env_vars *env_vars);
int						ft_ispipe(char *str, char **strpipe);
void					ft_isspace(char *str, char **parsestr);
int						is_builtin(char *str);
int						piped_args(t_env_vars *env_vars, char **args1,
						char **args2, int fd);
char					*ft_strsep(char **stringp, char delim);
int						create_list(char *str, t_env_vars *env_vars,
						t_execute *cmdlist);
int						use_list(t_execute *cmdlist, t_env_vars *env_vars);
int						ft_isdelim(char c);
int						redir_right(t_execute *cmdlist, t_env_vars *env_vars);
int						redir_two_right(t_execute *cmdlist,
						t_env_vars *env_vars);
int						redir_left(t_execute *cmdlist, t_env_vars *env_vars);
int						get_num_pipes(t_execute *cmdlist);
void					pipe_mult(t_execute *cmdlist, t_env_vars *env_vars,
						int in, int out);
int						redirtwo_left(t_execute *cmdlist,
						t_env_vars *env_vars);
int						rep_line(char *str);
void					pipe_to_redir(t_execute *cmdlist, int outfile,
						int num_pipes, int fdin);
int						redir_ag_right(t_execute *cmdlist,
						t_env_vars *env_vars, int bef, int aft);
void					reset_term();
int						piped_args_heredoc(t_execute *cmdlist,
						t_env_vars *env_vars);
int						line_ed_one(unsigned long d, t_env_vars *env_vars,
						t_execute *cmdlist);
void					get_first_term();
void					get_new_term();
int						doub_left_to_right(t_execute *cmdlist,
						t_env_vars *env_vars);
int						left_to_right(t_execute *cmdlist,
						t_env_vars *env_vars);
int						heredoc_to_pipe_to_redir(t_execute *cmdlist,
						t_env_vars *env_vars);
int						clist(t_execute *cmdlist, int dir, int num,
						t_tok_type syntype);
int						redir_ag_pipe(t_execute *cmdlist, t_env_vars *env_vars,
						int bef, int aft);
void					update_values(void);
int						last_cd(t_env_vars *env_vars);
int						echpar_rep_line(char *str);
char					*echo_par(int quote_num);
char					*del_character(char *str, char c);
void					history_rep_line(char *str);
void					create_individual_rows(char **tmp, int i,
						char *str, int col);
void					define_values_rep_line(int *j, int *i, char *str);
void					initialize_envs(t_env_vars *env_vars);
void					define_values_history_rep_line(int col);
void					assign_env_names(t_env_vars *env_vars);
int						env_malloc_size(char **str);
int						define_values_create_list(char *str, char ***arg,
						int *j, t_execute **cmdlist);
t_execute				*define_first_vars(int *i, int *j, t_execute *cmdlist,
						int pipes[]);
void					pipe_pipes(int pipes[], int i, int j);
int						heredoc_rep_line(char *str);
void					read_heredoc(void);
int						ctrl_d_heredoc(int fd, char *line, t_execute *cmdlist,
						t_env_vars *env_vars);
int						line_ed_heredoc(int fd, char *line, t_execute *cmdlist,
						t_env_vars *env_vars);
char					**deepcopy(char **data);
void					add_to_end(t_execute **head, int status, char **data,
						t_tok_type type);
int						find_flag(char **arg, char *str, int i);
char					*get_fn_and_print_line(char *line, int fd);
void					restore_fd(int tmpin, int tmpout);
char					*ft_21_strjoin(char *s1, char *s2);
int						ispath(char *arg, t_env_vars *env_vars);
int						cmd_parsing_two(char **arg, char *str,
						t_execute **cmdlist, int i);
int						add_reg_cmd(int i, char **arg,
						t_execute **cmdlist, char *str);
int						redir_parsing(char **arg, char *str,
						t_execute **cmdlist, int i);
int						ft_isallspace(char **arg, t_execute **cmdlist,
						char *str, int i);
int						single_letter(char *str, char **arg,
						t_execute **cmdlist);
void					close_in_out_fd(int tmpin, int tmpout);
t_execute				*pipe_exec(t_execute *cmdlist, t_env_vars *env_vars);
t_execute				*redir_two_left_exec(t_execute *cmdlist,
						t_env_vars *env_vars);
t_execute				*redir_two_left_exec_two(t_execute *cmdlist,
						t_env_vars *env_vars);
t_execute				*redir_left_exec(t_execute *cmdlist,
						t_env_vars *env_vars);
t_execute				*redir_right_exec(t_execute *cmdlist,
						t_env_vars *env_vars);
t_execute				*fd_agg_check(t_execute *cmdlist,
						t_env_vars *env_vars);
t_execute				*move_cmd_to(t_execute *cmdlist,
						t_tok_type syntype, int check);
t_execute				*unknown_exec(t_execute *cmdlist);
int						bad_syntax_two(t_execute *cmdlist);
int						bad_syntax(t_execute *cmdlist);
t_execute				*cmd_exec(t_execute *cmdlist, t_env_vars *env_vars);
char					*ft_21_free_first_strjoin(char *s1, char *s2);
void					free_everything(t_execute *cmdlist);
void					free_cd(char *mypwd, t_env_vars *env_vars);
void					move_words(unsigned long d);
void					move_char_left(int col);
void					move_char_right(int col);
void					move_characters(unsigned long d, int col);
void					home_end_keys(unsigned long d);
void					move_cursor_line(unsigned long d);
void					delete_char(void);
void					del_entire_line(void);
char					*update_str2_paste(char *str, char *str2,
						int i, int k);
void					reset_pwd(t_env_vars *env_vars);
void					reset_old_pwd(t_env_vars *env_vars);
void					check_quotes(void);
int						islinejustspacetab(char *line);
int						get_lens(char **tmp);
int						adjust_for_len(int i);
int						set_term_environ();
char					*quote_is_closed(char *line, int fd,
						int quote_num, char *buf);
#endif
