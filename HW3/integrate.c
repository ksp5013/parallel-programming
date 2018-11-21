#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define PI 3.1415926535

int main(int argc, char **argv) 
{
  long long i, num_intervals;
  double rect_width, area, sum, x_middle, rec_sum; 

  sscanf(argv[1],"%llu",&num_intervals);

  rect_width = PI / num_intervals;

  sum = 0;
  
  int my_rank, num_process;
  int source, tag = 0, dest = 0;
  MPI_Status status;
  
  double time;  //delete
  
  MPI_Init(&argc, &argv);
  time = MPI_Wtime();  //delete
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_process);
  
  for(i = 1+my_rank; i < num_intervals + 1; i+=num_process) {

    /* find the middle of the interval on the X-axis. */ 

    x_middle = (i - 0.5) * rect_width;
    area = sin(x_middle) * rect_width; 
    sum = sum + area;
  } 
  
  if(my_rank == 0) {
  	for(source = 1; source < num_process; source++) {
  		MPI_Recv(&rec_sum, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &status);
  		sum += rec_sum;
  	}	
  }
  else
  	MPI_Send(&sum, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  
  if(my_rank == 0)
  	printf("The total area is: %f\n", (float)sum);
  
  time = MPI_Wtime() - time;  //delete
  printf("rank = %d time = %lf\n", my_rank, time);  //delete
  
  MPI_Finalize();

  return 0;
}   
