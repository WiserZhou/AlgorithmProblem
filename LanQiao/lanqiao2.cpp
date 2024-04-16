#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>
using namespace std;
struct Node{
	int val;
	vector<int> next;
};
int n,m;
vector<vector<int>> result1;
vector<vector<int>> result2;
void bfs(vector<Node>& N,int i,vector<int> str)
{
	str.push_back(N[i].val);
	int k = N[i].next.size();
	if(k==0) {
		result1.push_back(str);
		return ;
	}
	for(int j =0;j<k;j++)
	{
		bfs(N,N[i].next[j],str);
	}
}
void kbfs(vector<Node>& N,int i,vector<int> str)
{
	str.push_back(N[i].val);
	int k = N[i].next.size();
	if(k==0) {
		result2.push_back(str);
		return ;
	}
	for(int j =0;j<k;j++)
	{
		kbfs(N,N[i].next[j],str);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	vector<Node> N;
	vector<Node> M;
	for(int i =0;i<n;i++)
	{
		Node p;
		int x;
		scanf("%d",&x);
		p.val = x;
		N.push_back(p);
	}
		for(int i =0;i<m;i++)
	{
		Node p;
		int x;
		scanf("%d",&x);
		p.val = x;
		M.push_back(p);
	}
	for(int i =0;i<n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		N[x-1].next.push_back(y-1);
	}
	for(int i =0;i<m-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		M[x-1].next.push_back(y-1);
	}
	vector<int> str;
	bfs(N,0,str);
	kbfs(M,0,str);
	int n1 = result1.size();
	int n2 = result2.size();
	int Num=0;
	for(int i=0;i<n1;i++)
	{
		for(int j=0;j<n2;j++)
		{
			
			int N1 = result1[i].size();
			int N2 = result2[j].size();
			int N3 = min(N1,N2);
			int MM=0;
			for(int l=0;l<N3;l++)
			{
				if(result1[i][l]==result2[j][l]){
					MM++;
				}else break;
			}
			Num = max(Num,MM);
		}
	}
	cout<<Num;
	return 0;
	
}
