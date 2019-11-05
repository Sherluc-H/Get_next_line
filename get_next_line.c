/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:37:51 by lhuang            #+#    #+#             */
/*   Updated: 2019/11/05 16:02:16 by lhuang           ###   ########.fr       */
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

int			ft_cut_line(char *b, t_fd_list **current, int *rd, char **str1)
{
	int		i;
	int		end_line;
	char	*str2;

	i = 0;
	end_line = 0;
	if (!(str2 = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (i < *rd && !end_line)
	{
		if (b[i] == '\n')
			end_line = 1;
		str2[i] = b[i];
		if (end_line)
		{
			str2[i] = '\0';
			*str1 = ft_strjoin(*str1, str2);
		}
		else if (i == *rd - 1)
		{
			str2[i + 1] = '\0';
			*str1 = ft_strjoin(*str1, str2);
			return (0);
		}
		i++;
	}
	(*current)->remain_size = *rd;
	if ((ft_create_remain(current, i, end_line, b)) == -1)
		return (-1);
	return (1);
}

// a la norme
// int			ft_cut_line(char *b, t_fd_list **current, int *rd, char **str1)
// {
// 	int		i;
// 	int		end_line;
// 	char	*str2;

// 	i = 0;
// 	end_line = 0;
// 	if (!(str2 = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
// 		return (-1);
// 	while (i < *rd && !end_line)
// 	{
// 		str2[i] = b[i];
// 		if (b[i] == '\n' || i == *rd - 1)
// 		{
// 			end_line = i == *rd - 1 ? 0 : 1;
// 			str2[i + (i == *rd - 1 ? 1 : 0)] = '\0';
// 			*str1 = ft_strjoin(*str1, str2);
// 			if (i == *rd - 1)
// 				return (0);
// 		}
// 		i++;
// 	}
// 	(*current)->remain_size = *rd;
// 	return (ft_create_remain(current, i, end_line, b));
// }

int			ft_create_remain(t_fd_list **current, int i, int end_line, char *b)
{
	int		j;
	char	*t;

	j = 0;
	t = NULL;
	if (end_line && i + j < (*current)->remain_size)
	{
		if (!(t = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		while (end_line && i + j < (*current)->remain_size)
		{
			t[j] = b[j + i];
			j++;
		}
		t[j] = '\0';
		(*current)->remain = t;
		(*current)->remain_size = j;//verifier que cest exact 100%
	}
	else
	{
		(*current)->remain = NULL;
		(*current)->remain_size = 0;
	}
	return (1);
}

int			ft_cut_remain(char *b, t_fd_list **current, int *end_line, char **str1)
{
	int		i;
	char	*str2;

	i = 0;
	if (!(str2 = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (i < BUFFER_SIZE && !*end_line)
	{
		if (b[i] == '\n')
			*end_line = 1;
		str2[i] = b[i];
		if (*end_line)
			str2[i] = '\0';
		i++;
	}
	str2[i] = '\0';
	*str1 = str2;
	if ((ft_create_remain(current, i, *end_line, b) == -1))
		return (-1);
	return (1);
}

int			ft_free_fd(t_fd_list **fd_list, int fd)
{
	t_fd_list *current;
	t_fd_list *next;
	t_fd_list *tmp;

	current = *fd_list;
	while ((current->next_fdl))
	{
		if ((current->next_fdl)->fd == fd)
		{
			tmp = current;
			if ((current->next_fdl)->remain_size > 0)
			{
				free((current->next_fdl)->remain);
				(current->next_fdl)->remain = NULL;
			}
			next = (current->next_fdl)->next_fdl;
			free((current->next_fdl));
			(current->next_fdl) = NULL;
			tmp->next_fdl = next;
			return (0);
		}
		current = current->next_fdl;
	}
	if (current->fd == fd &&current->remain_size > 0)
	{
		free(current->remain);
		current->remain = NULL;
		free(current);
		current = NULL;
	}
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
	t_fd_list			*first;
	first = current;
	printf("avant\n");
	ft_print_fd(&fd_list);
	if(!(current = ft_search_fd(&fd_list, fd)))
		return (-1);
	// printf("apres\n");
	// ft_print_fd(&first);
	if (current->remain_size > 0)
		ft_cut_remain(current->remain, &current, &end_line, line);
	else
	{
		if(!(*line = malloc(sizeof(char) * 1)))
			return (-1);
		(*line)[0] = '\0';
	}
	while (!end_line && (rd = read(fd, b, BUFFER_SIZE)) > 0)
		end_line = ft_cut_line(b, &current, &rd, line);
	if (rd == 0 && !end_line)
	{
		printf("free%d\n", fd);
		ft_free_fd(&first, fd);
					ft_print_fd(&fd_list);
					printf("<-after\n");
		return (0);
	}
	else if (rd < 0)
		return (-1);
	return (1);
}
