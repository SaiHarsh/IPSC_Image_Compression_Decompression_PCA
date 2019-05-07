#include <string.h>              // required for memcpy()
#include <float.h>               // required for DBL_EPSILON
#include <math.h>                // required for fabs(), sqrt();
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <cstdlib>

using namespace std;

vector<vector<double> > topKEV, CompressedMatrix;
vector<vector<double> > A; // Input Matrix
vector<vector<double>> EigenVectors; //Eigen vectors
vector<vector<double>> retrived;
vector<vector<double>> CM;// Compressed Matrix

#include "matrixMultiplicationPar.h"
#include "imageCompression.h"
#include "imageDecompression.h"


int main(int argv, char* argc[])
{

	int	dummpy;
	printf("Input Image: %s\n",argc[1] );

	printf("\nConverting in to Matrix Format...\n");
	char com[100] = "convert ";
	strcat(com,argc[1]);
	strcat(com," ");
	strcat(com,argc[1]);
	strcat(com,".pgmTEMP");
	printf("\t%s\n",com );
	
	//int	dummpy = system(com);
	
	//I = imread('test.jpg');
	int M,N,pixels;

	
	FILE *fp;
	char g[10];
	char fileName[100]="";
	strcat(fileName,argc[1]);
//	strcat(fileName,".pgm");
	printf("\nMatrix Format of Input Image:%s\n", fileName);
	fp = fopen(fileName,"r");
	dummpy = fscanf(fp,"%s",g);
	dummpy = fscanf(fp,"%d%d",&M,&N);
	dummpy = fscanf(fp,"%d",&pixels);

	int M_temp = M,elem;
	while(M_temp--) A.push_back({});
	
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j){
			dummpy = fscanf(fp,"%d",&elem);
			A[i].push_back(elem);
		}
	fclose(fp);

	vector<vector<double> > A_dup = A;
	
	double tic = omp_get_wtime();
	printf("\n\nCompressing Image...\n");
	imageCompression();
	
	printf("\nDe-Compressing Image...\n");
	imageDecompression(atof(argc[2]));
	double time = omp_get_wtime() - tic;


	strcpy(fileName,"");
	string retrievedFile = argc[1];
	retrievedFile[0] = 'o';
	retrievedFile[1] = 'p';

	strcat(fileName,retrievedFile.c_str());
	strcat(fileName,"_compressed.pgm");
	printf("\n\nMatrix Format of Compressed Image:%s\n", fileName);
	//printf("%s\n",fileName );
	fp = fopen(fileName,"w");
	dummpy = fprintf(fp,"%s\n",g);
	dummpy = fprintf(fp,"%d %d\n",M,CM[0].size());
	dummpy = fprintf(fp,"%d\n",pixels);

	for (int i = 0; i < CM.size(); ++i){
		for (int j = 0; j < CM[i].size(); ++j){
			dummpy = fprintf(fp,"%.0lf ",CM[i][j]);
		}
		dummpy = fprintf(fp,"\n");
	}
	fclose(fp);


	printf("\nConverting Compressed matrix to an Image...\n");
	char command[100] = "convert ";
	strcat(command,retrievedFile.c_str());
	strcat(command,"_compressed.pgm ");
	strcat(command,retrievedFile.c_str());
	strcat(command,"_compressed.pgm.png");
	printf("\t%s\n",command );
	dummpy = system(command);

	strcat(fileName,".png");	
	printf("\nCompressed Image: %s\n",fileName );

	strcpy(fileName,"");
	strcat(fileName,retrievedFile.c_str());
	strcat(fileName,"_retrieved.pgm");
	printf("\n\nMatrix Format of Retrived Image:%s\n", fileName);

	fp = fopen(fileName,"w");
	dummpy = fprintf(fp,"%s\n",g);
	dummpy = fprintf(fp,"%d %d\n",N,N);
	dummpy = fprintf(fp,"%d\n",pixels);

	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			dummpy = fprintf(fp,"%.0lf ",retrived[i][j]);
		}
		dummpy = fprintf(fp,"\n");
	}
	fclose(fp);



	printf("\nConverting retrived matrix to an Image...\n");
	strcpy(command,"convert ");
	strcat(command,retrievedFile.c_str());
	strcat(command,"_retrieved.pgm ");
	strcat(command,retrievedFile.c_str());
	strcat(command,"_retrieved.pgm.png");
	printf("\t%s\n",command );
	dummpy = system(command);

	strcat(fileName,".png");	
	printf("\nRetrieved Image: %s\n",fileName );

	printf("\n\n[[[Executed Succesfully]]]\n");
	printf("Running Time : %lf sec\n",time );


	return 0;
}

