/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:41:18 by ebinjama          #+#    #+#             */
/*   Updated: 2023/11/10 20:57:46 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*dummy;

	if (!lst)
		return ;
	if (*lst)
	{
		dummy = *lst;
		while (dummy->next)
			dummy = dummy->next;
		dummy->next = new;
	}
	else
		*lst = new;
}
