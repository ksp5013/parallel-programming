#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int isprime(int n) {
  int i,squareroot;
  if (n>10) {
    squareroot = (int) sqrt(n);
    for (i=3; i<=squareroot; i=i+2)
      if ((n%i)==0)
        return 0;
    return 1;
  }
  else
    return 0;
}

int main(int argc, char *argv[])
{
  //float prime_density[7] = {0.25, 0.168, 0.1229, 0.096, 0.0785, 0.0665, 0.0577}
  long long int pc;       /* prime counter */
  long long int foundone = 0; /* most recent prime found */
  long long int n, limit;
  long long int output[2] = {0, 0};
  int my_rank, num_process;
  int source, dest = 0, tag = 0;
  MPI_Status status;
  
  double time;  //delete

  sscanf(argv[1],"%llu",&limit);	
  printf("Starting. Numbers to be scanned= %lld\n",limit);

  pc=0;     /* Assume (2,3,5,7) are counted here */
  
  MPI_Init(NULL, NULL);
  time = MPI_Wtime();  //delete
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_process);
  
  for (n=11+my_rank*2; n<=limit; n=n+num_process*2) {
  	//printf("%llu\n",n);
    if (isprime(n)) {
      //printf("%d\n",n);
      pc++;
      foundone = n;
    }
  }
  
  //printf("%llu %llu %d\n",pc,foundone,my_rank);
  
  output[0] = pc;
  output[1] = foundone;
  
  //printf("%llu %llu %d\n",output[0],output[1],my_rank);
  
  if(my_rank==0) {
  	pc = pc + 4;
  	for(source = 1; source < num_process; source++) {
  		MPI_Recv(&output, 2, MPI_UNSIGNED_LONG_LONG, source, tag, MPI_COMM_WORLD, &status);
  		pc += output[0];
  		if(foundone < output[1])
  			foundone = output[1];
	  }
  }
  else
  	MPI_Send(&output, 2, MPI_UNSIGNED_LONG_LONG, dest, tag, MPI_COMM_WORLD);
  
  if(my_rank == 0)
  	printf("Done. Largest prime is %d Total primes %d\n",foundone,pc);
  	
  time = MPI_Wtime() - time;  //delete
  printf("rank = %d time = %lf\n", my_rank, time);  //delete
  MPI_Finalize();

  return 0;
} 
