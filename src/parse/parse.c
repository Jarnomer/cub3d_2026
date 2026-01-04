/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_map	*init_map(void)
{
	t_map	*map;

	map = safe_calloc(sizeof(t_map));
	map->floor_col.a = 255;
	map->ciel_col.a = 255;
	return (map);
}

t_map	*parse(const char *filepath)
{
	t_parse		ctx;

	ft_bzero(&ctx, sizeof(t_parse));
	ctx.map = init_map();
	ctx.fd = parse_file_open(filepath);
	parse_elements(&ctx);
	parse_map(&ctx);
	close(ctx.fd);
	return (ctx.map);
}
