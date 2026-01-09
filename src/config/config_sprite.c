/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_spr_id	str_to_spr_id(const char *str)
{
	if (ft_strcmp(str, "SPRITE_BARREL") == 0)
		return (SPRITE_BARREL);
	if (ft_strcmp(str, "SPRITE_HEALTH") == 0)
		return (SPRITE_HEALTH);
	if (ft_strcmp(str, "SPRITE_ARMOR") == 0)
		return (SPRITE_ARMOR);
	if (ft_strcmp(str, "SPRITE_AMMO") == 0)
		return (SPRITE_AMMO);
	return (SPRITE_COUNT);
}

static void	process_line(char *line, t_assets *assets)
{
	char		**parts;
	t_spr_id	id;

	parts = safe_split(line, ' ');
	if (parse_count_parts(parts) < TEXDEF_FIELD_COUNT)
		err_exit_msg(MSG_CONF_FMT);
	parse_remove_newline(parts[2]);
	if (ft_strcmp(parts[0], "SPRITE") == 0)
	{
		id = str_to_spr_id(parts[1]);
		if (id < SPRITE_COUNT)
			texture_load(&assets->sprites[id], parts[2]);
	}
	free_arr(parts);
}

void	config_load_sprites(t_assets *assets)
{
	int		fd;
	char	*line;

	fd = parse_file_open(PATH_CONFIG_TEXTURE, ".def");
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_skip_line(line))
			process_line(line, assets);
		free_str(line);
		line = get_next_line(fd);
	}
	close(fd);
}
