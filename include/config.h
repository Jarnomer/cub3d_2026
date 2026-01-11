/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/07 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <defs.h>

typedef struct s_assets	t_assets;
typedef struct s_entdef	t_entdef;
typedef struct s_anidef	t_anidef;
typedef struct s_wpndef	t_wpndef;

# define TEXDEF_FIELD_COUNT		3
# define SHEETDEF_FIELD_COUNT	4
# define ENTDEF_FIELD_COUNT		6
# define ANIMDEF_FIELD_COUNT	7
# define WPNDEF_FIELD_COUNT		10

# define CONFIG_FILE_EXT		".def"

# define PATH_CONFIG_TEXTURE	"config/texture.def"
# define PATH_CONFIG_ENTITY		"config/entity.def"
# define PATH_CONFIG_SHEET		"config/sheet.def"
# define PATH_CONFIG_ANIM		"config/anim.def"
# define PATH_CONFIG_WEAPON		"config/weapon.def"

typedef void	(*t_cfg_proc)(char **fields, void *ctx);

typedef struct s_str_id
{
	const char	*str;
	t_i32		id;
}	t_str_id;

typedef struct s_cfgload
{
	const char		*path;
	t_i32			fields;
	t_cfg_proc		process;
	void			*ctx;
}	t_cfgload;

void		config_load_all(t_assets *assets);
void		config_parse_file(t_cfgload *cfg);
t_i32		config_str_to_id(const char *str);

void		config_load_textures(t_assets *assets);
void		config_load_sheets(t_assets *assets);
void		config_load_entities(t_entdef *defs);
void		config_load_anims(t_anidef *defs);
void		config_load_weapons(t_wpndef *defs);

#endif
