#include <iostream>
#include <string>
#include <vector>
using namespace std;
//int tran(char c)
//{
//	if(c=='1') return 1;
//	else if(c=='2' ) return 2;
//	else if(c=='3') return 3;
//	else if(c=='4') return 5;
//	else if(c=='5' ) return 4;
//	else if(c=='6') return 4;
//	else if(c=='7') return 2;
//	else if(c=='8') return 2;
//	else if(c=='9') return 2;
//	else if(c=='0') return 13;
//}
//int str(string s)
//{
//	int n = s.size();
//	int num=15;
//	for(int i =0;i<n;i++)
//	{
//		num+=tran(s[i]);
//	}
//	return num;
//}
//
//int main()
//{
//	for()
//}
int N=0;
bool T(vector<vector<bool>> matrix)
{
	for(int i =1;i<=5;i++)
	{
		bool flag=matrix[i][1];
		int num=1;
		for(int j=2;j<=5;j++)
		{
			if(matrix[i][j]==flag){
				 num++;
			}
		}
		if(num==5) return true;
	}
	for(int i =1;i<=5;i++)
	{
		bool flag=matrix[1][i];
		int num=1;
		for(int j=2;j<=5;j++)
		{
			if(matrix[j][i]==flag){
				 num++;
			}
		}
		if(num==5) return true;
	}
	bool flag = matrix[1][1];
		int num=1;
	for(int i =2;i<=5;i++)
	{
		
	    if(matrix[i][i] ==flag) num++;
	}
	if(num==5 ) return true;
	flag = matrix[1][5];
	num=1;
	for(int i=2;i<=5;i++)
	{
		if(matrix[6-i][i]==flag) num++;
	}
	if(num==5) return true;
	
	return false;
	
}
void dfs(vector<vector<bool>> matrix,int y,int flag,int num)
{
 cout<<"s"<<endl;
	if(y>25 ) return;
    	if(num==13) {
//	   cout<<"N++"<<endl;
		N++;
		if(T(matrix)){
			N--;
		}
		return ;
	}	
    if(flag == 0)
    {
    		dfs(matrix,y+1,0,num);
     	dfs(matrix,y+1,1,num);
	}else{
			int z = y;
	int x= y/5 +1 ;
	y = y%5;
		matrix[x][y]=true;
	num++;
	dfs(matrix,z+1,0,num);
	dfs(matrix,z+1,1,num);
	}
}

int main()
{
	vector<vector<bool>>  matrix(6,vector<bool> (6,false));
	dfs(matrix,1,0,0);
		dfs(matrix,1,1,0);
	cout<<N;
}
