/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	validate_no_empty_lines(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
		{
			if (content[i + 1] == '\n')
				err_exit_msg(MSG_MAP_BLANK);
			if (content[i + 1] != '\0' && parse_is_empty_line(content + i + 1))
				err_exit_msg(MSG_MAP_BLANK);
		}
		i++;
	}
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = safe_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*read_map_content(t_parse *ctx, char *first_line)
{
	char	*content;
	char	*line;

	content = first_line;
	line = get_next_line(ctx->fd);
	while (line)
	{
		content = join_and_free(content, line);
		line = get_next_line(ctx->fd);
	}
	return (content);
}

static char	*skip_empty_lines(t_parse *ctx)
{
	char	*line;

	line = get_next_line(ctx->fd);
	while (line && parse_is_empty_line(line))
	{
		free(line);
		line = get_next_line(ctx->fd);
	}
	return (line);
}

void	parse_map(t_parse *ctx)
{
	char	*first_line;
	char	*content;

	first_line = skip_empty_lines(ctx);
	if (!first_line)
		err_exit_msg(MSG_MAP_MISS);
	content = read_map_content(ctx, first_line);
	validate_no_empty_lines(content);
	ctx->map->grid = safe_split(content, '\n');
	free(content);
	parse_map_validate(ctx);
}
