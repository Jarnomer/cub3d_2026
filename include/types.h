/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include <stdbool.h>
# include <stddef.h>

typedef uint8_t			t_u8;
typedef uint16_t		t_u16;
typedef uint32_t		t_u32;
typedef uint64_t		t_u64;
typedef int8_t			t_i8;
typedef int16_t			t_i16;
typedef int32_t			t_i32;
typedef int64_t			t_i64;
typedef float			t_f32;
typedef double			t_f64;

typedef mlx_image_t		t_mimg;
typedef mlx_texture_t	t_mtex;
typedef pthread_mutex_t	t_mtx;

typedef struct s_color
{
	t_u8	r;
	t_u8	g;
	t_u8	b;
	t_u8	a;
}	t_color;

#endif
