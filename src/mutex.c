#include "../includes/philo.h"

typedef struct s_data
{
	int	count;
	pthread_mutex_t	mut;
	char	*msg;
}	t_data;



void	*counter(void *arg)
{
	t_data	*data = (t_data *) arg;
	while (data->count < 100)
	{
		pthread_mutex_lock(&data->mut);
		printf("%s %i\n", data->msg, data->count);
		data->count++;
		pthread_mutex_unlock(&data->mut);
		//usleep(10000);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	t_data		data1;
	t_data		data2;

	data1.count = 0;
	data1.msg = "thread 1 ";
	pthread_mutex_init(&data1.mut, NULL);

	data2.count = 0;
	data2.msg = "thread 2 ";
	pthread_mutex_init(&data2.mut, NULL);

	pthread_create(&t1, NULL, counter, &data1);
	pthread_create(&t2, NULL, counter, &data2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&data1.mut);
	pthread_mutex_destroy(&data2.mut);

	return (0);
}
