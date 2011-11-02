
#include <stdio.h>
#include <stdlib.h>
#include "omp_testsuite.h"

//static int sum1 = 789;

int ctest_omp_parallel_firstprivate(FILE * logFile)
{
    
	int sum, num_threads,sum1;
    
    int known_sum;

    sum = 0;
    sum1=7;
    num_threads = 0;


#pragma omp parallel private(sum1)
    {

	/*printf("sum1=%d\n",sum1);*/
	
	int i;
#pragma omp for 
	    for (i = 1; i < 1000; i++)
	    {
		sum1 = sum1 + i;
	    } /*end of for*/
#pragma omp critical
	{
	    sum = sum + sum1;
            num_threads++;
	} /*end of critical*/
	
    } /* end of parallel*/    
    known_sum = (999 * 1000) / 2 + 7 * num_threads;
    return (known_sum == sum);

}
int main()
{
	int i;			/* Loop index */
	int result;		/* return value of the program */
	int failed=0; 		/* Number of failed tests */
	int success=0;		/* number of succeeded tests */
	static FILE * logFile;	/* pointer onto the logfile */
	static const char * logFileName = "bin/c/ctest_omp_parallel_firstprivate.log";	/* name of the logfile */


	/* Open a new Logfile or overwrite the existing one. */
	logFile = fopen(logFileName,"w+");

	printf("######## OpenMP Validation Suite V %s ######\n", OMPTS_VERSION );
	printf("## Repetitions: %3d                       ####\n",REPETITIONS);
	printf("## Loop Count : %6d                    ####\n",LOOPCOUNT);
	printf("##############################################\n");
	printf("Testing omp parallel firstprivate\n\n");

	fprintf(logFile,"######## OpenMP Validation Suite V %s ######\n", OMPTS_VERSION );
	fprintf(logFile,"## Repetitions: %3d                       ####\n",REPETITIONS);
	fprintf(logFile,"## Loop Count : %6d                    ####\n",LOOPCOUNT);
	fprintf(logFile,"##############################################\n");
	fprintf(logFile,"Testing omp parallel firstprivate\n\n");

	for ( i = 0; i < REPETITIONS; i++ ) {
		fprintf (logFile, "\n\n%d. run of ctest_omp_parallel_firstprivate out of %d\n\n",i+1,REPETITIONS);
		if(ctest_omp_parallel_firstprivate(logFile)){
			fprintf(logFile,"Test successful.\n");
			success++;
		}
		else {
			fprintf(logFile,"Error: Test failed.\n");
			printf("Error: Test failed.\n");
			failed++;
		}
	}

    if(failed==0){
		fprintf(logFile,"\nDirective worked without errors.\n");
		printf("Directive worked without errors.\n");
		result=0;
	}
	else{
		fprintf(logFile,"\nDirective failed the test %i times out of %i. %i were successful\n",failed,REPETITIONS,success);
		printf("Directive failed the test %i times out of %i.\n%i test(s) were successful\n",failed,REPETITIONS,success);
		result = (int) (((double) failed / (double) REPETITIONS ) * 100 );
	}
	printf ("Result: %i\n", result);
	return result;
}
