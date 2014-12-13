int                     get_next_line(int fd, char **line);

#include <stdio.h>

int main(void)
{
	char *line;

	while (get_next_line(1, &line))
	{
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
