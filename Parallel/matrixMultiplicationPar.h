vector<vector<double>>  matrixMultiPar(vector<vector<double>> A, vector<vector<double>> B){
	vector<vector<double>> ans;
	for (int i = 0; i < A.size(); ++i) ans.push_back({});
	for (int i = 0; i < A.size(); ++i) for (int j = 0; j < A[i].size(); ++j) ans[i].push_back(0);

	#pragma omp parallel for schedule(static)
	for (int i = 0; i < B.size(); ++i)	
	{
		for (int j = 0; j < A.size(); ++j)
		{
			for (int k = 0; k < B.size(); ++k)
			{
					ans[i][j] += A[i][k]*B[k][j];
			}
		}
	}
	return ans;
}