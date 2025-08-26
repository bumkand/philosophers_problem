#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*print_message(void *arg)
{
	char	*message;
	int		i;

	message = (char *) arg;
	i = 0;
	while (i < 5)
	{
		printf("%s %d\n", message, i);
		usleep(10000);
		i++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, print_message, "helooooo thread 1");
	pthread_create(&t2, NULL, print_message, "hiiiiiii thread 2");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return (0);
}
