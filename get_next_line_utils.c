/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:38:09 by lhuang            #+#    #+#             */
/*   Updated: 2019/11/06 15:16:03 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void		ft_print_fd(t_fd_list **fd_list)
// {
// 	t_fd_list *current;

// 	current = *fd_list;
// 	while (current)
// 	{
// 		printf("\tfd = %d", current->fd);
// 		current = current->next_fdl;
// 	}
// }

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

//pas a la norm
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
// 		if (b[i] == '\n')
// 			end_line = 1;
// 		str2[i] = b[i];
// 		if (end_line)
// 		{
// 			str2[i] = '\0';
// 			*str1 = ft_strjoin(*str1, str2);
// 		}
// 		else if (i == *rd - 1)
// 		{
// 			str2[i + 1] = '\0';
// 			*str1 = ft_strjoin(*str1, str2);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	(*current)->remain_size = *rd;
// 	if ((ft_create_remain(current, i, end_line, b)) == -1)
// 		return (-1);
// 	return (1);
// }

// a la norme

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
		str2[i] = b[i];
		if (b[i] == '\n' || i == *rd - 1)
		{
			end_line = i == *rd - 1 ? 0 : 1;
			str2[i + (i == *rd - 1 ? 1 : 0)] = '\0';
			*str1 = ft_strjoin(*str1, str2);
			if (i == *rd - 1)
				return (0);
		}
		i++;
	}
	(*current)->remain_size = *rd;
	return (ft_create_remain(current, i, end_line, b));
}

int			ft_cut_remain(char *b, t_fd_list **current,
			int *end_line, char **str1)
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
