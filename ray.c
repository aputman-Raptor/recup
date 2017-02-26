/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 21:09:04 by aputman           #+#    #+#             */
/*   Updated: 2017/02/26 21:12:11 by aputman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/RT.h"

t_v			reflection(t_ray ray, t_winfo *w, int *nb, int depth)
{
	t_ray	ref;
	t_v		n;
	double	ret;

	if (depth <= 0)
		return (ray.color);
	ref.a = ray.current;
	n = w->obj[ray.id].c;
	ref.dir = add_v(ray.current, mult_v(mult_v(n, 2), dot(invert_v(n),
					ray.current)));
	ref.dir = normalize(ref.dir);
	ref.id = -1;
	ref.t = -1;
	intersection(&ref, w->obj, w->file.nbobj);
	if (ref.id != -1)
	{
		ret = shadow(w->light, ref, w->obj, nb);
		check_light(w->light, &ref, &w->obj[ref.id], nb[1]);
	}
	ref.current = add_v(ref.a, mult_v(ref.dir, ref.t));
	ref.color = limit_v(mult_v(ref.color, ret), 0, 255);
	if (ref.id != -1)
		return (reflection(ref, w, nb, depth - 1));
	return (ray.color);
}
