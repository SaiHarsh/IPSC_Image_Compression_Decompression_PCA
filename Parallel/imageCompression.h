vector<double> meanArray;
int M, N;
double singular_values[1000];
#include "getEigenVector_SVD.h"

void imageCompression(){
	meanArray.resize(A.size(),0);
	for (int i = 0; i < A.size(); ++i)
	{
		for (int j = 0; j < A[i].size(); ++j)
			meanArray[i] += A[i][j];		
		meanArray[i] /= A[i].size();
	}

	for (int i = 0; i < A.size(); ++i)
	{
		for (int j = 0; j < A[i].size(); ++j)
			A[i][j]	-= meanArray[i];		
	}
	vector<vector<double>> A_T;
	for (int i = 0; i < A.size(); ++i)
	{
		A_T.push_back({});
		A_T[i].resize(A.size(),0);
		for (int j = 0; j < A[i].size(); ++j)
			A_T[i][j] = A[j][i];
		
	}
	#if PRINT
		printf("-------A-------A_T-------\n");
		for (int i = 0; i < A.size(); ++i)
		{
			for (int j = 0; j < A[i].size(); ++j)
				printf("%lf ",  A[i][j]);
			printf("\n");
		}	
		printf("\n");
		for (int i = 0; i < A.size(); ++i)
		{
			for (int j = 0; j < A[i].size(); ++j)
				printf("%lf ",  A_T[i][j]);
			printf("\n");
		}
		printf("-----------------------------\n");
	#endif
	vector<vector<double>> Sigma = matrixMultiPar(A,A_T);

	for (int i = 0; i < Sigma.size(); ++i)
	{
		for (int j = 0; j < Sigma[i].size(); ++j)
			Sigma[i][j] /= Sigma[i].size()-1;
	}
	#if PRINT
		printf("\nMean Values\n");
		for(auto a:meanArray) printf("%lf\n",a );
		printf("\n");
	#endif

	M = A.size();
	N = A.size();
	double U[M][N];
	double V[M][N];


	double* dummy_array; 
	double diagonal[N];      
	double superdiagonal[N];
	dummy_array = (double*) malloc(N * sizeof(double));

	double pos[M][N]={{0}};
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
			pos[i][j] = Sigma[i][j];
	
	printf("Sigma Values\n");
	#if PRINT
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
			printf("%lf ", pos[i][j]);
		printf("\n");
	}
	#endif

	int err = Singular_Value_Decomposition((double*) pos, M, N, (double*) U,    
                              singular_values, (double*) V, dummy_array);   
                                                                              
     if (err < 0) printf(" Failed to converge\n");                          
     else  printf("\n\nThe singular value decomposition of Sigma Matrix is \n");

  
	for(int i=0;i<M;i++){
	    EigenVectors.push_back({});
	    for(int j=0;j<N;j++)
	    {
	    	EigenVectors[i].push_back(V[i][j]);
	    	#if PRINT
    	  		printf("%lf ", V[i][j]);
    	  	#endif
	    }
		#if PRINT
    		printf("\n");
    	#endif
  	}
  	#if PRINT
  		printf("\n");
  	#endif
}

