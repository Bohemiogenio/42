/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/07 20:32:29 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"

/* Global var */
extern int				g_signal;

/* ===== ENUMS ===== */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}	t_token_type;

/* ===== STRUCTS ===== */

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_redir
{
	t_token_type		type;
	char				*file;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char				**args;
	t_redir				*redirs;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_shell
{
	t_env				*env;
	t_cmd				*cmds;
	t_token				*tokens;
	int					exit_status;
	int					stdin_backup;
	int					stdout_backup;
}	t_shell;

/* ===== SIGNALS ===== */
void		setup_signals(void);
void		setup_signals_child(void);

/* ===== ENVIRONMENT ===== */
t_env		*env_init(char **envp);
char		*env_get(t_env *env, char *key);
int			env_set(t_env **env, char *key, char *value);
int			env_unset(t_env **env, char *key);
char		**env_to_array(t_env *env);
int			env_size(t_env *env);

/* ===== LEXER ===== */
t_token		*tokenize(char *line);
t_token		*token_new(t_token_type type, char *value);
void		token_add_back(t_token **lst, t_token *new_tok);
int			check_quotes(char *line);

/* ===== EXPANDER ===== */
t_token		*expand_tokens(t_token *tokens, t_shell *shell);

/* ===== PARSER ===== */
t_cmd		*parse_tokens(t_token *tokens);
int			check_syntax(t_token *tokens);
int			count_args(t_token *tok);
void		add_redir(t_cmd *cmd, t_token_type type, char *file);
t_cmd		*new_cmd(int arg_count);

/* ===== BUILTINS ===== */
int			is_builtin(char *cmd);
int			exec_builtin(t_cmd *cmd, t_shell *shell);
int			builtin_echo(t_cmd *cmd);
int			builtin_cd(t_cmd *cmd, t_shell *shell);
int			builtin_pwd(void);
int			builtin_export(t_cmd *cmd, t_shell *shell);
int			builtin_unset(t_cmd *cmd, t_shell *shell);
int			builtin_env(t_shell *shell);
int			builtin_exit(t_cmd *cmd, t_shell *shell);

/* ===== EXECUTOR ===== */
int			executor(t_cmd *cmds, t_shell *shell);
char		*find_command_path(char *cmd, t_env *env);
pid_t		exec_pipeline(t_cmd *cmds, t_shell *shell);
int			apply_redirections(t_cmd *cmd, t_shell *shell);
int			handle_heredoc(char *delimiter);
void		restore_fds(t_shell *shell);
void		setup_child_fds(t_cmd *cmd, int in_fd, int *pipefd);
void		exec_child_cmd(t_cmd *cmd, t_shell *shell);

/* ===== EXPANDER INTERNAL ===== */
char		*expand_string(char *str, t_shell *shell);
char		*expand_var_name(char *str, int *i, char *res, t_shell *shell);
char		*append_char(char *str, char c);
char		*expand_tilde(char *str, t_shell *shell);

/* ===== UTILS ===== */
void		free_tokens(t_token *tokens);
void		free_cmds(t_cmd *cmds);
void		free_env(t_env *env);
void		free_array(char **arr);
void		free_shell(t_shell *shell);
void		print_error(char *cmd, char *arg, char *msg);

#endif
