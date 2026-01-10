/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/09 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static t_wpn_id	str_to_wpn_id(const char *str)
{
	if (ft_strcmp(str, "WEAPON_SHOTGUN") == 0)
		return (WEAPON_SHOTGUN);
	if (ft_strcmp(str, "WEAPON_PISTOL") == 0)
		return (WEAPON_PISTOL);
	return (WEAPON_NONE);
}

static t_ammo	str_to_ammo(const char *str)
{
	if (ft_strcmp(str, "AMMO_SHELL") == 0)
		return (AMMO_SHELL);
	if (ft_strcmp(str, "AMMO_BULLET") == 0)
		return (AMMO_BULLET);
	if (ft_strcmp(str, "AMMO_CELL") == 0)
		return (AMMO_CELL);
	if (ft_strcmp(str, "AMMO_EXPLOSIVE") == 0)
		return (AMMO_EXPLOSIVE);
	return (AMMO_SHELL);
}

static void	parse_wpn_line(char **p, t_wpndef *def)
{
	def->id = str_to_wpn_id(p[0]);
	def->sheet_id = str_to_sheet_id(p[1]);
	def->anim_idle = str_to_anim_id(p[2]);
	def->anim_fire = str_to_anim_id(p[3]);
	def->anim_reload = str_to_anim_id(p[4]);
	def->ammo_type = str_to_ammo(p[5]);
	def->damage = ft_atoi(p[6]);
	def->pellets = ft_atoi(p[7]);
	def->mag_size = ft_atoi(p[8]);
	def->fire_rate = ft_atof(p[9]);
}

static void	process_line(char *line, t_wpndef *defs)
{
	char		**parts;
	t_wpndef	def;

	parts = safe_split(line, ' ');
	if (parse_count_parts(parts) < WPNDEF_FIELD_COUNT)
		err_exit_msg(MSG_CONF_FMT);
	ft_bzero(&def, sizeof(t_wpndef));
	parse_wpn_line(parts, &def);
	if (def.id != WEAPON_NONE && def.id < WEAPON_COUNT)
		defs[def.id] = def;
	free_arr(parts);
}

void	config_load_weapons(t_wpndef *defs)
{
	int		fd;
	char	*line;

	ft_bzero(defs, sizeof(t_wpndef) * WEAPON_COUNT);
	fd = parse_file_open(PATH_CONFIG_WEAPON, ".def");
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
