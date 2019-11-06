/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:37:51 by lhuang            #+#    #+#             */
/*   Updated: 2019/11/06 15:15:13 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//clean quand un fichier est lu en entier
// free ce qu'il faut
//free quand ya un probleme
//tester avec plein de buffer_size different
//faire une fonction search and free avec free all aussi?
//si cest t qui rate le malloc je free le str2
//creer fichier bonus
//norminette
//free s1 et s2 ici ?on envoie p de toute facon et str va pointer sur p dans merge ?

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

int			ft_free_all_fd(t_fd_list **fd_list)
{
	t_fd_list	*current;
	t_fd_list	*tmp;

	current = NULL;
	if (fd_list)
		current = *fd_list;
	if (current)
	{
		while (current)
		{
			tmp = current->next_fdl;
			free(current->remain);
			current->remain = NULL;
			free(current);
			current = tmp;
		}
		*fd_list = NULL;
	}
	return (-1);
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
		return (0);
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
	return (0);
}

int			get_next_line(int fd, char **line)
{
	int					rd;
	char				b[BUFFER_SIZE];
	static t_fd_list	*fd_list = NULL;
	t_fd_list			*current;
	int					end_line;

	*line = NULL;
	end_line = 0;
	if (!(current = ft_search_fd(&fd_list, fd)))
		return (ft_free_all_fd(&fd_list));
	if (current->remain_size > 0)
		ft_cut_remain(current->remain, &current, &end_line, line);
	else
	{
		if (!(*line = malloc(sizeof(char) * 1)))
			return (ft_free_all_fd(&fd_list));
		(*line)[0] = '\0';
	}
	while (!end_line && (rd = read(fd, b, BUFFER_SIZE)) > 0 && end_line != -1)
		end_line = ft_cut_line(b, &current, &rd, line);
	if (rd == 0 && !end_line)
		return (ft_free_fd(&fd_list, fd));
	else if (rd < 0 || end_line == -1)
		return (ft_free_all_fd(&fd_list));
	return (1);
}
