/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/06 19:55:57 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(char *line, t_shell *shell)
{
	if (check_quotes(line))
	{
		shell->exit_status = 2;
		return ;
	}
	shell->tokens = tokenize(line);
	if (!shell->tokens)
		return ;
	if (check_syntax(shell->tokens))
	{
		shell->exit_status = 2;
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		return ;
	}
	shell->tokens = expand_tokens(shell->tokens, shell);
	shell->cmds = parse_tokens(shell->tokens);
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	if (shell->cmds)
		shell->exit_status = executor(shell->cmds, shell);
	free_cmds(shell->cmds);
	shell->cmds = NULL;
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (g_signal == SIGINT)
		{
			shell->exit_status = 130;
			g_signal = 0;
		}
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (line[0] != '\0')
			add_history(line);
		if (line[0] != '\0')
			process_line(line, shell);
		free(line);
	}
}

static t_shell	init_shell(char **envp)
{
	t_shell	shell;

	shell.env = env_init(envp);
	shell.cmds = NULL;
	shell.tokens = NULL;
	shell.exit_status = 0;
	shell.stdin_backup = dup(STDIN_FILENO);
	if (shell.stdin_backup == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
	shell.stdout_backup = dup(STDOUT_FILENO);
	if (shell.stdout_backup == -1)
	{
		perror("dup");
		close(shell.stdin_backup);
		exit(EXIT_FAILURE);
	}
	return (shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	setup_signals();
	shell_loop(&shell);
	free_shell(&shell);
	return (shell.exit_status);
}
