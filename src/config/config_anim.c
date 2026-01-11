/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

t_anim_id	str_to_anim_id(const char *str)
{
	if (ft_strcmp(str, "ANIM_DOOR_IDLE") == 0)
		return (ANIM_DOOR_IDLE);
	if (ft_strcmp(str, "ANIM_DOOR_OPEN") == 0)
		return (ANIM_DOOR_OPEN);
	if (ft_strcmp(str, "ANIM_DOOR_CLOSE") == 0)
		return (ANIM_DOOR_CLOSE);
	if (ft_strcmp(str, "ANIM_BARREL_IDLE") == 0)
		return (ANIM_BARREL_IDLE);
	if (ft_strcmp(str, "ANIM_BARREL_EXPLODE") == 0)
		return (ANIM_BARREL_EXPLODE);
	if (ft_strcmp(str, "ANIM_SHOTGUN_IDLE") == 0)
		return (ANIM_SHOTGUN_IDLE);
	if (ft_strcmp(str, "ANIM_SHOTGUN_FIRE") == 0)
		return (ANIM_SHOTGUN_FIRE);
	if (ft_strcmp(str, "ANIM_SHOTGUN_RELOAD") == 0)
		return (ANIM_SHOTGUN_RELOAD);
	return (ANIM_NONE);
}

static void	parse_anim_line(char **p, t_anidef *def)
{
	def->id = str_to_anim_id(p[0]);
	def->start = (t_u16)ft_atoi(p[1]);
	def->total = (t_u16)ft_atoi(p[2]);
	def->duration = ft_atof(p[3]);
	def->next = (t_u16)ft_atoi(p[4]);
	def->is_looping = (ft_atoi(p[5]) != 0);
	def->is_reversed = (ft_atoi(p[6]) != 0);
}

static void	process_line(char *line, t_anidef *defs)
{
	char		**parts;
	t_anidef	def;

	parts = safe_split(line, ' ');
	if (parse_count_parts(parts) < ANIMDEF_FIELD_COUNT)
		err_exit_msg(MSG_CONF_FMT);
	ft_bzero(&def, sizeof(t_anidef));
	parse_anim_line(parts, &def);
	if (def.id != ANIM_NONE && def.id < ANIM_COUNT)
		defs[def.id] = def;
	free_arr(parts);
}

void	config_load_anims(t_anidef *defs)
{
	int		fd;
	char	*line;

	ft_bzero(defs, sizeof(t_anidef) * ANIM_COUNT);
	fd = parse_file_open(PATH_CONFIG_ANIM, ".def");
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
