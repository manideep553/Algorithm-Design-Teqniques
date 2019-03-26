#include <fstream>
#include <iostream>
#include<stdio.h>
#include <new>
#include <algorithm>  

using namespace std;

int result;
int func;
ofstream outputfile;


void hamiltonioncycle(int **array, int *vertexarray, int vertex,int fact)
{
	func++;
	int vvertex=vertex-1;
	int grapharray[100];
	int graphdata = 0;
	int graphindex;
	int vertex2;
	int lesgraph = 0;
	int h;
	for (int i = 0; i < vvertex; i++)
	{
		int a=vertexarray[i];
		int b=vertexarray[i+1];
		lesgraph = lesgraph + array[a][b];
	}
	int a=vertexarray[vvertex];
	int b=vertexarray[0];
	lesgraph = lesgraph + array[a][b];
	 lesgraph;
	if(lesgraph<result)
	{
		result=lesgraph;
	}
	
	if(fact==func)
{
	outputfile<<result<<endl;
}
return;	
}

void permutation(int **array,int *vertexarray, int arraysize, int vertex,int fact) 
{ 
    if (arraysize == 1) 
    { 
        hamiltonioncycle(array,vertexarray,vertex,fact); 
        return; 
    } 
  
    for (int i=0; i<arraysize; i++) 
    { 
        permutation(array,vertexarray,arraysize-1,vertex,fact); 
  		if (arraysize%2==1) 
           {
		    swap(vertexarray[0], vertexarray[arraysize-1]); 
  		}
		  else
		  { 
            swap(vertexarray[i], vertexarray[arraysize-1]); 
    	}
	} 
} 

int main(int argc, char *argv[])
{

	int *elementlist;
	int *myints;
	int *vertexarray;
	int vertex1, vertex2, weight2;
	ifstream filein;
	filein.open(argv[1]);
	//filein.open("dataset.txt");
	int dataset;
	int vvertex, vedge, vweight;
	int vertex, edge, weight;
	filein >> dataset;
	outputfile.open(argv[2]);
	//outputfile.open("finalset2.txt");
	
	for (int i = 0; i < dataset; i++)
	{
		int fact = 1;
		int smallestelement=100;
		int numberofpermutations = 0;
		filein >> vertex >> edge;
		vvertex = vertex-1;
		vedge = edge;
		vertexarray = new int[vvertex];
		myints = new int[vvertex];
		for (int j = 1; j <= vertex; j++)
		{
			fact = fact * j;
		}
		result=10000;
		func=0;
		int** array = new int*[vertex];
		for (int j = 0; j < vertex; ++j)
		{
			array[j] = new int[vertex];
		}

		for (int j = 0; j < edge; j++)
		{
			filein >> vertex1 >> vertex2 >> weight2;
			array[vertex1][vertex2] = weight2;
			array[vertex2][vertex1] = weight2;
		}

	
			for (int j = 0; j < vertex; j++)
			{
				vertexarray[j]=j;
		}
			permutation(array,vertexarray,vertex,vertex,fact);
	}

	filein.close();
	outputfile.close();
}


