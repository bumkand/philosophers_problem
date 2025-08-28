#include "../includes/philo.h"

int main(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("Sekundy: %li\n", tv.tv_sec);
	printf("Mikrosekundy: %li\n", tv.tv_usec);
	return (0);
}