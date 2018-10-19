#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <semaphore.h> 

long thread_count;
long long n;
long long toss;
long long sum;

sem_t S;

void* Monte_Carlo(void* parameter) {
	srand(time(NULL));
	int local_sum = 0;
	double x, y;
	long i;
	for (i = 0; i < toss; i++) {
		x = (double)rand() / (RAND_MAX + 1.0);
		y = (double)rand() / (RAND_MAX + 1.0);
		if (x*x + y*y < 1)
			local_sum++;
	}
	sem_wait(&S);
	sum += local_sum;
	sem_post(&S);
	return NULL;
}

int main(int argc, char *argv[]) {
	clock_t start_time, end_time;
	float total_time = 0;
	start_time = clock();

	long thread;
	pthread_t* pthread_handles;

	thread_count = strtol(argv[1],NULL,10);
	n = strtoll(argv[2],NULL,10);
	toss = n / thread_count;
	pthread_handles = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);
	S = malloc(sizeof(sem_t));
	sem_init(&S,0,1);

	sum = 0;
	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&pthread_handles[thread], NULL, Monte_Carlo, (void*)NULL);

	//join
	for (thread = 0; thread < thread_count; thread++)
		pthread_join(pthread_handles[thread], NULL);

	double output = (double)sum / (double)n * 4;

	free(pthread_handles);
	free(S);
	end_time = clock();
	total_time = (float)(end_time - start_time) / CLOCKS_PER_SEC;


	printf("pi = %lf\n", output);
	printf("%f sec\n", total_time);
	return 0;
}
