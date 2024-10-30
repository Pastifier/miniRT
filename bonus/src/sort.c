/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 06:17:51 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/29 06:27:40 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static size_t	partition(t_itx *arr, size_t start, size_t end);
static void 	quick_sort_recursion(t_itx *arr, size_t start, size_t end);

void quick_sort_intersections(t_itx *arr, size_t size)
{
	if (size)
		quick_sort_recursion(arr, 0, size - 1);
}

static void	ft_coop(t_itx *a, t_itx *b)
{
	t_itx	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static size_t	partition(t_itx *arr, size_t start, size_t end)
{
	const double	pivot_value = arr[end].t;
	size_t 			i;
	size_t 			j;

	i = start;
	j = start;
	while (j < end)
	{
		if (arr[j].t <= pivot_value)
		{
			ft_coop(&arr[j], &arr[i]);
			++i;
		}
		++j;
	}
	ft_coop(&arr[i], &arr[end]);
	return (i);
}

static void	quick_sort_recursion(t_itx *arr, size_t start, size_t end)
{
	if (start < end)
	{
		size_t i = partition(arr, start, end);
		if (i != 0)
			quick_sort_recursion(arr, start, i - 1);
		if (i + 1 < end)
			quick_sort_recursion(arr, i + 1, end);
	}
}
