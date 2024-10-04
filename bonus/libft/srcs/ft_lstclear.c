/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:41:36 by ebinjama          #+#    #+#             */
/*   Updated: 2023/11/07 11:29:53 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;

	if (!del || !lst || !(*lst))
		return ;
	while (*lst)
	{
		curr = *lst;
		*lst = curr->next;
		ft_lstdelone(curr, del);
	}
	*lst = NULL;
}
