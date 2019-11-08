/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:10:52 by lhuang            #+#    #+#             */
/*   Updated: 2019/11/08 12:02:48 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE=0

# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_fd_list
{
	int					fd;
	char				*remain;
	int					remain_size;
	struct s_fd_list	*next_fdl;
}				t_fd_list;

char			*ft_merge(char *s1, char *s2,
				int s1_size, int s2_size);
char			*ft_strjoin(char *s1, char *s2);
int				ft_create_remain(t_fd_list **current,
				int i, int end_line, char *b);
int				ft_cut_line(char *b, t_fd_list **current,
				int *rd, char **str1);
int				ft_cut_remain(char *b, t_fd_list **current,
				int *end_line, char **str1);
void			ft_add_fd(t_fd_list **fd_list, t_fd_list *new_fd);
t_fd_list		*ft_search_fd(t_fd_list **fd_list, int fd);
int				ft_read(int end_line, t_fd_list **fd_list,
				t_fd_list **current, char **line);
int				ft_free_fd(t_fd_list **fd_list, int fd);
int				get_next_line(int fd, char **line);

#endif
