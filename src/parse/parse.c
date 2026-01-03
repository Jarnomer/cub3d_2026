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

void	parse_cleanup(t_parse *ctx)
{
	int	i;

	if (!ctx)
		return ;
	if (ctx->fd > 0)
		close(ctx->fd);
	if (ctx->line)
		free(ctx->line);
	if (ctx->map)
	{
		i = 0;
		while (i < 4)
			free(ctx->map->tex_paths[i++]);
		ft_free_double((void ***)&ctx->map->grid);
		free(ctx->map);
	}
}

static t_map	*init_map(void)
{
	t_map	*map;

	map = safe_calloc(sizeof(t_map));
	map->floor.a = 255;
	map->ceiling.a = 255;
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
