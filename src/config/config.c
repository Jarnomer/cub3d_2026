/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/10 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static const t_str_id	g_id_table[] = {
{"TEXTURE_FLOOR", TEXTURE_FLOOR},
{"TEXTURE_CEILING", TEXTURE_CEILING},
{"SPRITE_BARREL", SPRITE_BARREL},
{"SPRITE_HEALTH", SPRITE_HEALTH},
{"SPRITE_ARMOR", SPRITE_ARMOR},
{"SPRITE_AMMO", SPRITE_AMMO},
{"SHEET_DOOR", SHEET_DOOR},
{"SHEET_BARREL", SHEET_BARREL},
{"SHEET_SHOTGUN", SHEET_SHOTGUN},
{"ENTITY_BARREL", ENTITY_BARREL},
{"ENTITY_DOOR", ENTITY_DOOR},
{"ENTITY_HEALTH", ENTITY_HEALTH},
{"ENTITY_ARMOR", ENTITY_ARMOR},
{"ENTITY_AMMO", ENTITY_AMMO},
{"ANIM_DOOR_IDLE", ANIM_DOOR_IDLE},
{"ANIM_DOOR_OPEN", ANIM_DOOR_OPEN},
{"ANIM_DOOR_CLOSE", ANIM_DOOR_CLOSE},
{"ANIM_BARREL_IDLE", ANIM_BARREL_IDLE},
{"ANIM_BARREL_EXPLODE", ANIM_BARREL_EXPLODE},
{"ANIM_SHOTGUN_IDLE", ANIM_SHOTGUN_IDLE},
{"ANIM_SHOTGUN_FIRE", ANIM_SHOTGUN_FIRE},
{"ANIM_SHOTGUN_RELOAD", ANIM_SHOTGUN_RELOAD},
{"WEAPON_SHOTGUN", WEAPON_SHOTGUN},
{"WEAPON_PISTOL", WEAPON_PISTOL},
{"AMMO_SHELL", AMMO_SHELL},
{"AMMO_BULLET", AMMO_BULLET},
{"AMMO_CELL", AMMO_CELL},
{"AMMO_EXPLOSIVE", AMMO_EXPLOSIVE},
{NULL, -1}
};

t_i32	config_str_to_id(const char *str)
{
	t_i32	i;

	if (!str)
		return (-1);
	i = 0;
	while (g_id_table[i].str)
	{
		if (ft_strcmp(str, g_id_table[i].str) == 0)
			return (g_id_table[i].id);
		i++;
	}
	return (-1);
}

void	config_parse_file(t_cfgload *cfg)
{
	char	**fields;
	char	*line;
	int		fd;

	fd = parse_file_open(cfg->path, CONFIG_FILE_EXT);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_skip_line(line))
		{
			fields = safe_split(line, ' ');
			if (parse_count_fields(fields) != cfg->fields)
				err_exit_msg(MSG_CONF_FMT);
			cfg->process(fields, cfg->ctx);
			free_arr(fields);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	config_load_all(t_assets *assets)
{
	config_load_textures(assets);
	config_load_sheets(assets);
	config_load_entities(assets->entdefs);
	config_load_weapons(assets->wpndefs);
	config_load_anims(assets->anidefs);
}
