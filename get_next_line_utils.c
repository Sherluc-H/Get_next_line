/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:38:09 by lhuang            #+#    #+#             */
/*   Updated: 2019/11/05 15:48:02 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		ft_add_fd(t_fd_list **fd_list, t_fd_list *new_fd)
{
	t_fd_list *current;

	if (fd_list != NULL && *fd_list == NULL)
	{
		*fd_list = new_fd;
		return ;
	}
	current = *fd_list;
	if (current != NULL)
	{
		while (current->next_fdl)
			current = current->next_fdl;
		current->next_fdl = new_fd;
	}
}

t_fd_list	*ft_search_fd(t_fd_list **fd_list, int fd)
{
	t_fd_list *current;
	t_fd_list *new_fd;

	current = *fd_list;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next_fdl;
	}
	if (!(new_fd = malloc(sizeof(*new_fd))))
		return (NULL);
	new_fd->fd = fd;
	new_fd->remain = NULL;
	new_fd->remain_size = 0;
	new_fd->next_fdl = NULL;
	ft_add_fd(fd_list, new_fd);
	return (new_fd);
}

void		ft_print_fd(t_fd_list **fd_list)
{
	t_fd_list *current;

	current = *fd_list;
	while (current)
	{
		printf("\tfd = %d", current->fd);
		current = current->next_fdl;
	}
}

char		*ft_merge(char *s1, char *s2, int s1_size, int s2_size)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(p = malloc(sizeof(char) * (s1_size + s2_size) + 1)))
		return (NULL);
	while (i < s1_size)
	{
		p[i] = s1[i];
		i++;
	}
	while (j < s2_size)
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	free(s1);
	free(s2);
	return (p);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		s1_size;
	int		s2_size;
	int		i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i])
			i++;
		s1_size = i;
		i = 0;
		while (s2[i])
			i++;
		s2_size = i;
		return (ft_merge(s1, s2, s1_size, s2_size));
	}
	return (NULL);
}
