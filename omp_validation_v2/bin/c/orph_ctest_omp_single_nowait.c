#include "omp_testsuite.h"


	int nr_iterations;
    

/* Declaration of the functions containing the code for the orphan regions */
#include <stdio.h>


/* End of declaration */


#include <stdio.h>
#include "omp_testsuite.h"

int my_iterations;
#pragma omp threadprivate(my_iterations)

int orph_ctest_omp_single_nowait(FILE * logFile)
{
    

    int total_iterations = 0;
    int i;

    nr_iterations = 0;
    my_iterations = 0;

#pragma omp parallel private(i)
    {
	for (i = 0; i < LOOPCOUNT; i++)
	{
	    
		
		{
#pragma omp atomic  
		    nr_iterations++;
		} /* end of single*/    
	    
	} /* end of for  */
    } /* end of parallel */

#pragma omp parallel private(i) 
    {
	my_iterations = 0;
	for (i = 0; i < LOOPCOUNT; i++)
	{
	    
		
		{
		    my_iterations++;
		} /* end of single*/    
	    
	} /* end of for  */
#pragma omp critical
	{
	    total_iterations += my_iterations;
	}

    } /* end of parallel */
    return ((nr_iterations == LOOPCOUNT) && (total_iterations == LOOPCOUNT));
} /* end of check_single_nowait*/
int main()
{
	int i;			/* Loop index */
	int result;		/* return value of the program */
	int failed=0; 		/* Number of failed tests */
	int success=0;		/* number of succeeded tests */
	static FILE * logFile;	/* pointer onto the logfile */
	static const char * logFileName = "bin/c/orph_ctest_omp_single_nowait.log";	/* name of the logfile */


	/* Open a new Logfile or overwrite the existing one. */
	logFile = fopen(logFileName,"w+");

	printf("######## OpenMP Validation Suite V %s ######\n", OMPTS_VERSION );
	printf("## Repetitions: %3d                       ####\n",REPETITIONS);
	printf("## Loop Count : %6d                    ####\n",LOOPCOUNT);
	printf("##############################################\n");
	printf("Testing omp single nowait\n\n");

	fprintf(logFile,"######## OpenMP Validation Suite V %s ######\n", OMPTS_VERSION );
	fprintf(logFile,"## Repetitions: %3d                       ####\n",REPETITIONS);
	fprintf(logFile,"## Loop Count : %6d                    ####\n",LOOPCOUNT);
	fprintf(logFile,"##############################################\n");
	fprintf(logFile,"Testing omp single nowait\n\n");

	for ( i = 0; i < REPETITIONS; i++ ) {
		fprintf (logFile, "\n\n%d. run of orph_ctest_omp_single_nowait out of %d\n\n",i+1,REPETITIONS);
		if(orph_ctest_omp_single_nowait(logFile)){
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

/* Automatically generated definitions of the orphan functions */

void orph1_omp_single_nowait (FILE * logFile) {
		
		{
#pragma omp atomic  
		    nr_iterations++;
		} /* end of single*/    
	    
}

void orph2_omp_single_nowait (FILE * logFile) {
		
		{
		    my_iterations++;
		} /* end of single*/    
	    
}
/* End of automatically generated definitions */
