/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:45:17 by raulsanc          #+#    #+#             */
/*   Updated: 2025/07/30 00:45:22 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	character = 0;
	static int				bit_index = 0;

	(void)context;
	if (sig == SIGUSR2)
		character |= (1 << (7 - bit_index));
	bit_index++;
	if (bit_index == 8)
	{
		ft_putchar(character);
		if (character == '\0')
			ft_putchar('\n');
		bit_index = 0;
		character = 0;
	}
	if (info && info->si_pid)
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
