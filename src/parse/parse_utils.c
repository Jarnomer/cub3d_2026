/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

char	*parse_skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str == ' ')
		str++;
	return (str);
}

bool	parse_skip_line(const char *line)
{
	if (!line)
		return (true);
	while (ft_isspace(*line))
		line++;
	if (*line == '\0' || *line == '\n' || *line == '#')
		return (true);
	return (false);
}

bool	parse_is_empty_line(const char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

void	parse_remove_newline(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

t_i32	parse_count_fields(char **parts)
{
	t_i32	count;

	if (!parts)
		return (0);
	count = 0;
	while (parts[count])
		count++;
	return (count);
}
