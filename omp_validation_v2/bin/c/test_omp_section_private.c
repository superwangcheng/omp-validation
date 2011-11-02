
#include <stdio.h>
#include "omp_testsuite.h"

int test_omp_section_private(FILE * logFile){
    
	int sum;
	int sum0;
        int i;
    
    int known_sum;

    sum = 7;
    sum0 = 0;

#pragma omp parallel
    {
	
#pragma omp  sections private(sum0,i)
	{
#pragma omp section 
	    {
		sum0 = 0;
		for (i = 1; i < 400; i++)
		    sum0 = sum0 + i;
#pragma omp critical
		{
		    sum = sum + sum0;
		} /*end of critical */
	    }    
#pragma omp section
	    {
		sum0 = 0;
		for (i = 400; i < 700; i++)
		    sum0 = sum0 + i;
#pragma omp critical
		{
		    sum = sum + sum0;
		} /*end of critical */
	    }
#pragma omp section
	    {
		sum0 = 0;
		for (i = 700; i < 1000; i++)
		    sum0 = sum0 + i;
#pragma omp critical
		{
		    sum = sum + sum0;
		} /*end of critical */
	    }               
	} /*end of sections*/
	
    } /* end of parallel */
    known_sum = (999 * 1000) / 2 + 7;
    return (known_sum == sum); 
} /* end of check_section_private*/
int main()
{
	int i;			/* Loop index */
	int result;		/* return value of the program */
	int failed=0; 		/* Number of failed tests */
	int success=0;		/* number of succeeded tests */
	static FILE * logFile;	/* pointer onto the logfile */
	static const char * logFileName = "bin/c/test_omp_section_private.log";	/* name of the logfile */


	/* Open a new Logfile or overwrite the existing one. */
	logFile = fopen(logFileName,"w+");

	printf("######## OpenMP Validation Suite V %s ######\n", OMPTS_VERSION );
	printf("## Repetitions: %3d                       ####\n",REPETITIONS);
	printf("## Loop Count : %6d                    ####\n",LOOPCOUNT);
	printf("##############################################\n");
	printf("Testing omp section private\n\n");

	fprintf(logFile,"######## OpenMP Validation Suite V %s ######\n", OMPTS_VERSION );
	fprintf(logFile,"## Repetitions: %3d                       ####\n",REPETITIONS);
	fprintf(logFile,"## Loop Count : %6d                    ####\n",LOOPCOUNT);
	fprintf(logFile,"##############################################\n");
	fprintf(logFile,"Testing omp section private\n\n");

	for ( i = 0; i < REPETITIONS; i++ ) {
		fprintf (logFile, "\n\n%d. run of test_omp_section_private out of %d\n\n",i+1,REPETITIONS);
		if(test_omp_section_private(logFile)){
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
