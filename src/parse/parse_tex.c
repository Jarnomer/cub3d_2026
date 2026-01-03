/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	parse_texture(t_parse *ctx, t_elem type)
{
	char	*value;
	char	*path;

	value = parse_skip_spaces(ctx->line + 3);
	path = safe_strdup(value);
	parse_remove_newline(path);
	parse_file_validate(path, ".png");
	ctx->map->tex_paths[type] = path;
}
