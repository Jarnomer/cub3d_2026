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

t_map	*parse(const char *filepath)
{
	t_parse	ctx;

	ctx = (t_parse){0};
	ctx.map = safe_calloc(sizeof(t_map));
	ctx.fd = parse_file_open(filepath, ".cub");
	parse_elements(&ctx);
	parse_map(&ctx);
	close(ctx.fd);
	return (ctx.map);
}
