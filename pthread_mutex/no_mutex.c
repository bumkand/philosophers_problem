#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int counter = 0;

void *increment(void *arg)
{
	char	*msg = (char*) arg;
	for (int i = 0; i < 100; i++)
		{
			printf("%s %i\n", msg, counter);
			counter++;
			usleep(1000);
		}
	return (NULL);
}

int main()
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, increment, "thread 1 = ");
	pthread_create(&t2, NULL, increment, "thread 2 = ");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Final counter value: %d\n", counter);
	return (0);
}
