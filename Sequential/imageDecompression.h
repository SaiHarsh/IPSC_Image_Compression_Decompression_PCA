
int imageDecompression(double threshold){

	vector<vector<double>> V_T;
	for(int i=0;i<EigenVectors.size();i++){
		V_T.push_back({});
		V_T[i].resize(EigenVectors[i].size(),0);
		for(int j=0;j<EigenVectors[i].size();j++){
			V_T[i][j]=EigenVectors[j][i];
		}
	}

	double K = threshold;
	int N = V_T.size();
	printf(" k = %lf\n", K);
	K *= N;
	if(K>N) {
		printf("k > N error, at Line %d in FILE %s.!\n",__LINE__,__FILE__);
		return 0;
	}

	printf("Compressed matrix:\n");
	//vector<vector<double>> CM;// = matrixMultiPar(A,V_T);
	for (int i = 0; i < N; ++i){
		CM.push_back({});
		for (int j = 0; j < K; ++j)
			CM[i].push_back(0);
	}


	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < K; ++j)
		{
			for (int k = 0; k < N; ++k)
			{
				CM[i][j] += A[i][k]*V_T[k][j];
				//CM[i][j] += V[i][k]*A[k][j];
			}
		}
	}
	#if PRINT
		for (int i = 0; i < CM.size(); ++i)
		{
			for (int j = 0; j < CM[i].size(); ++j)
				printf("%lf ",CM[i][j]);
			printf("\n");
		}
	#endif

	vector<vector<double>> ans;// = matrixMultiPar(CM,EigenVectors);	
	for (int i = 0; i < N; ++i){
		ans.push_back({});
		ans[i].resize(N,0);
	}



	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			for (int k = 0; k < K; ++k)  
			{
				ans[i][j] += CM[i][k]*EigenVectors[k][j];
				//ans[i][j] += CM[k][j]*V[i][k];
			}
		}
	}
	printf("\nRetrieved matrix:\n");
	for (int i = 0; i < N; ++i)
	{
		retrived.push_back({});
		//retrived[i].resize(ans[i].size(),0.0);
		for (int j = 0; j < N; ++j)
		{
			double p=ans[i][j]+meanArray[i];
			retrived[i].push_back(p);
			#if PRINT
				printf("%.0lf ",p);
			#endif
		}
		#if PRINT
			printf("\n");
		#endif
	}
}
