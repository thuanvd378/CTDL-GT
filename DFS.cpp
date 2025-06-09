#include<iostream>
using namespace std;
int visited[9]={0,0,0,0,0,0,0,0,0};
char vertex[7]={'A','B','C','D','E','F','G'};
char vertex1[9]={'1','2','3','4','5','6','7','8','9'};
void DFS(int G[][7], int index){
	visited[index]=1;
	cout<< vertex[index];
	for(int i=0;i<7;i++){
		if(G[index][i]== 1 && visited[i]== 0){
			DFS(G,i);
		}
	}
}
void DFS1(int **G, int n, int index){
	visited[index]=1;
	cout<< vertex1[index]<<"\t";
	for(int i=0;i<n;i++){
		if(G[index][i]== 1 && visited[i]== 0){
			DFS1(G,n,i);
		}
	}
}
int main (){
	int A1[7][7]={
	{0,1,0,0,0,1,0},
	{0,0,1,0,0,0,0},
	{0,0,0,1,1,0,1},
	{0,1,0,0,1,0,0},
	{0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0},
	};
	DFS(A1,0);
	cout<<endl;
	int A2[9][9]={
	{0,1,1,0,0,0,0,0,0},
	{1,0,0,1,1,0,0,0,0},
	{1,0,0,0,0,1,1,0,0},
	{0,1,0,0,0,0,0,1,0},
	{0,1,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,1},
	{0,0,1,0,0,0,0,0,0},
	{0,0,0,1,0,0,0,0,1},
	{0,0,0,0,0,1,0,1,0},
	};
	int **a=new int*[9];
	for(int i=0;i<9;i++){
		a[i]=new int [9];
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++)
		a[i][j]=A2[i][j];
	}
	DFS1(a,9,0);

}
