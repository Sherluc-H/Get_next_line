/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:10:25 by lhuang            #+#    #+#             */
/*   Updated: 2019/11/08 14:54:49 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int			ft_free_fd(t_fd_list **fd_list, int fd)
{
	t_fd_list *current;
	t_fd_list *next;
	t_fd_list *tmp;

	current = *fd_list;
	if (current->fd == fd)
	{
		*fd_list = current->next_fdl;
		free(current->remain);
		current->remain = NULL;
		current->remain_size = 0;
		free(current);
		return (-1);
	}
	while (current->next_fdl && (current->next_fdl)->fd != fd)
		current = current->next_fdl;
	tmp = current;
	next = (current->next_fdl)->next_fdl;
	free((current->next_fdl)->remain);
	(current->next_fdl)->remain = NULL;
	free((current->next_fdl));
	(current->next_fdl) = NULL;
	tmp->next_fdl = next;
	return (-1);
}

int			ft_read(int end_line, t_fd_list **fd_list,
			t_fd_list **current, char **line)
{
	char	*b;
	int		rd;

	rd = 0;
	if (!(b = malloc(sizeof(char) * BUFFER_SIZE)))
		return (-1);
	while (!end_line && end_line != -1 && (rd = read((*current)->fd, b,
	BUFFER_SIZE)) > 0)
		end_line = ft_cut_line(b, current, &rd, line);
	free(b);
	if (rd == 0 && !end_line)
	{
		ft_free_fd(fd_list, (*current)->fd);
		return (0);
	}
	else if (rd < 0 || end_line == -1)
		return (ft_free_fd(fd_list, (*current)->fd));
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static t_fd_list	*fd_list = NULL;
	t_fd_list			*current;
	int					end_line;

	if (!line || BUFFER_SIZE == 0)
		return (-1);
	*line = NULL;
	end_line = 0;
	if (!(current = ft_search_fd(&fd_list, fd)))
		return (ft_free_fd(&fd_list, fd));
	if (fd >= 0)
	{
		if (current->remain_size > 0)
			ft_cut_remain(current->remain, &current, &end_line, line);
		else
		{
			if (!(*line = malloc(sizeof(char) * 1)))
				return (ft_free_fd(&fd_list, fd));
			(*line)[0] = '\0';
		}
	}
	return (ft_read(end_line, &fd_list, &current, line));
}
