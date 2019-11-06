#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
	int i;
	char *str;
	int fd;
		int fd2;
		int fd3;

	fd = open("text.txt", O_RDONLY);
	fd2 = open("t.txt", O_RDONLY);
	fd3 = open("t3.txt", O_RDONLY);

	// i = get_next_line(fd, &str);
	// printf("\n->fd1 i = %d, str=%s\n", i, str);

	// i = get_next_line(fd, &str);
	// printf("\n->fd1 i = %d, str=%s\n", i, str);
	// i =	get_next_line(fd2, &str);
	// printf("\n->fd2 i = %d, str=%s\n", i, str);
	// 	i = get_next_line(fd, &str);
	// printf("\n->fd1 i = %d, str=%s\n", i, str);
	// 	i = get_next_line(fd, &str);
	// printf("\n->fd1 i = %d, str=%s\n", i, str);
	// 	i =	get_next_line(fd2, &str);
	// printf("\n->fd2 i = %d, str=%s\n", i, str);
	// 	i =	get_next_line(fd2, &str);
	// printf("\n->fd2 i = %d, str=%s\n", i, str);
	// 	i =	get_next_line(fd2, &str);
	// printf("\n->fd2 i = %d, str=%s\n", i, str);
	
	// i = get_next_line(fd, &str);
	// printf("\n->fd1 i = %d, str=%s\n", i, str);
	// 	i = get_next_line(fd3, &str);
	// printf("\n->fd3 i = %d, str=%s\n", i, str);
	// i = get_next_line(fd, &str);
	// printf("\n->fd1 i = %d, str=%s\n", i, str);
	// 	i =	get_next_line(fd2, &str);
	// printf("\n->fd2 i = %d, str=%s\n", i, str);
	// 		i = get_next_line(fd, &str);
	// printf("\n->fd1 i = %d, str=%s\n", i, str);
	// 		i = get_next_line(fd3, &str);
	// printf("\n->fd3 i = %d, str=%s\n", i, str);
	// 		i = get_next_line(fd3, &str);
	// printf("\n->fd3 i = %d, str=%s\n", i, str);


		// get_next_line(fd2, &str);
		// get_next_line(fd, &str);
		// get_next_line(fd2, &str);

	while ((i=get_next_line(0, &str)) > 0)
	{
		printf("i = %d, str=%s\n", i, str);
		free(str);
		str = NULL;
	}
	printf("i = %d, str=%s\n", i, str);
	free(str);
	str = NULL;
	return (1);
}
