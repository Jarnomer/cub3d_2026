/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static bool	parse_single_elem(t_parse *ctx, t_elem type)
{
	if (ctx->elements[type])
		err_exit_context(ctx->line, MSG_ELEM_DUP);
	if ((type == ELEM_F || type == ELEM_C))
		parse_color(ctx, type);
	else
		parse_texture(ctx, type);
	ctx->elements[type] = true;
	ctx->elem_count++;
	return (true);
}

static bool	try_parse_texture(t_parse *ctx, char *line)
{
	if (ft_strncmp(line, ID_NORTH, ft_strlen(ID_NORTH)) == 0)
		return (parse_single_elem(ctx, ELEM_NO));
	if (ft_strncmp(line, ID_SOUTH, ft_strlen(ID_SOUTH)) == 0)
		return (parse_single_elem(ctx, ELEM_SO));
	if (ft_strncmp(line, ID_WEST, ft_strlen(ID_WEST)) == 0)
		return (parse_single_elem(ctx, ELEM_WE));
	if (ft_strncmp(line, ID_EAST, ft_strlen(ID_EAST)) == 0)
		return (parse_single_elem(ctx, ELEM_EA));
	return (false);
}

static bool	try_parse_color(t_parse *ctx, char *line)
{
	if (ft_strncmp(line, ID_FLOOR, ft_strlen(ID_FLOOR)) == 0)
		return (parse_single_elem(ctx, ELEM_F));
	if (ft_strncmp(line, ID_CEILING, ft_strlen(ID_CEILING)) == 0)
		return (parse_single_elem(ctx, ELEM_C));
	return (false);
}

static void	parse_element_line(t_parse *ctx)
{
	char	*line;

	line = parse_skip_spaces(ctx->line);
	if (parse_is_empty_line(line))
		return ;
	if (try_parse_texture(ctx, line))
		return ;
	if (try_parse_color(ctx, line))
		return ;
	err_exit_context(ctx->line, MSG_ELEM_ID);
}

void	parse_elements(t_parse *ctx)
{
	while (ctx->elem_count < ELEM_COUNT)
	{
		if (ctx->elem_count == ELEM_COUNT)
			break ;
		ctx->line = get_next_line(ctx->fd);
		if (!ctx->line)
			err_exit_msg(MSG_ELEM_MISS);
		parse_element_line(ctx);
		ft_free_single((void **)&ctx->line);
	}
}
