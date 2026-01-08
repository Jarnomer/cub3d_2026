/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/06 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_type	str_to_type(const char *str)
{
	if (ft_strcmp(str, "ENTITY_BARREL") == 0)
		return (ENTITY_BARREL);
	if (ft_strcmp(str, "ENTITY_DOOR") == 0)
		return (ENTITY_DOOR);
	if (ft_strcmp(str, "ENTITY_HEALTH") == 0)
		return (ENTITY_HEALTH);
	if (ft_strcmp(str, "ENTITY_ARMOR") == 0)
		return (ENTITY_ARMOR);
	if (ft_strcmp(str, "ENTITY_AMMO") == 0)
		return (ENTITY_AMMO);
	return (ENTITY_NONE);
}

static t_spr_id	str_to_spr_id(const char *str)
{
	if (ft_strcmp(str, "SPRITE_BARREL") == 0)
		return (SPRITE_BARREL);
	if (ft_strcmp(str, "SPRITE_DOOR") == 0)
		return (SPRITE_DOOR);
	if (ft_strcmp(str, "SPRITE_HEALTH") == 0)
		return (SPRITE_HEALTH);
	if (ft_strcmp(str, "SPRITE_ARMOR") == 0)
		return (SPRITE_ARMOR);
	if (ft_strcmp(str, "SPRITE_AMMO") == 0)
		return (SPRITE_AMMO);
	return (0);
}

static void	parse_def_line(char **p, t_entdef *def)
{
	def->type = str_to_type(p[0]);
	def->spr_id = str_to_spr_id(p[1]);
	def->scale = ft_atof(p[2]);
	def->z_offset = ft_atof(p[3]);
	def->health = ft_atoi(p[4]);
	def->solid = (ft_atoi(p[5]) != 0);
}

static void	process_line(char *line, t_entdef *defs)
{
	char		**parts;
	t_entdef	def;

	parts = safe_split(line, ' ');
	if (parse_count_parts(parts) < ENTDEF_FIELD_COUNT)
		err_exit_msg(MSG_CONF_FMT);
	ft_bzero(&def, sizeof(t_entdef));
	parse_def_line(parts, &def);
	if (def.type != ENTITY_NONE && def.type < ENTITY_COUNT)
		defs[def.type] = def;
	free_arr(parts);
}

void	config_load_entities(t_entdef *defs)
{
	int		fd;
	char	*line;

	ft_bzero(defs, sizeof(t_entdef) * ENTITY_COUNT);
	fd = parse_file_open(PATH_CONFIG_ENTITY, ".def");
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_skip_line(line))
			process_line(line, defs);
		free_str(line);
		line = get_next_line(fd);
	}
	close(fd);
}
