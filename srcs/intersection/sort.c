/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:48:28 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/01 18:47:09 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include <stdio.h>

static size_t partition(t_intersection *arr, size_t start, size_t end);
static void quick_sort_recursion(t_intersection *arr, size_t start, size_t end);

void quick_sort_intersections(t_intersection *arr, size_t size)
{
	if (size)
		quick_sort_recursion(arr, 0, size - 1);
}

#include "libft.h"

static void ft_coop(t_intersection *a, t_intersection *b)
{
	t_intersection	temp;

	//ft_memmove(&temp, a, sizeof(*a));
	//ft_memmove(a, b, sizeof(*b));
	//ft_memmove(b, &temp, sizeof(temp));
	temp = *a;
	*a = *b;
	*b = temp;
}

static size_t partition(t_intersection *arr, size_t start, size_t end)
{
	double pivot_value = arr[end].t;
	size_t i = start;
	size_t j = start;

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

void quick_sort_recursion(t_intersection *arr, size_t start, size_t end)
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
