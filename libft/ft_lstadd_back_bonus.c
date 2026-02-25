/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:28:49 by jtinaut-          #+#    #+#             */
/*   Updated: 2024/10/01 18:40:05 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *ft_new)
{
	t_list	*iteri;

	iteri = ft_lstlast(*lst);
	if (!iteri)
	{
		ft_lstadd_front(lst, ft_new);
		return ;
	}
	iteri->next = ft_new;
	ft_new->next = NULL;
}
