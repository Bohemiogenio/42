/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:33:21 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/03 15:46:27 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	**sl_split_lines(const char *buf)
{
	size_t	i;
	size_t	start;
	size_t	row;
	size_t	len;
	char	**out;

	out = malloc(sizeof(char *) * (sl_count_lines(buf) + 1));
	if (!out)
		return (NULL);
	i = 0;
	start = 0;
	row = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			len = i - start;
			out[row] = sl_copy_line(buf, start, len);
			if (!out[row])
				return (sl_free_partial(out, row), NULL);
			row++;
			start = i + 1;
		}
		i++;
	}
	if (i > start)
	{
		len = i - start;
		out[row] = sl_copy_line(buf, start, len);
		if (!out[row])
			return (sl_free_partial(out, row), NULL);
		row++;
	}
	out[row] = NULL;
	return (out);
}