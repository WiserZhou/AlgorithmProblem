#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>
#include <cmath>
using namespace std;
struct Node{
	int c;
	vector<int> next;
};

int n,q;
vector<Node> M;
int cal(vector<bool> C)
{
	int sum=0;
	for(int i=0;i<20;i++ )
	{
		if(C[i]) sum++;
	}
	return sum;
}
void dfs(int s,int d,int path,int min,vector<bool> C,int& kind,vector<bool> visit)
{
	
	C[s] = true;
	visit[s] = true;
	if(s==d) {
		if(path <= min){
			min  = path;
//			cout<<cal(C)<<"C"<<endl;
			kind = max(cal(C),kind);
		}
		return ;
	}
	int n = M[s].next.size();
    
	for(int i=0;i<n;i++)
	{
		if(!visit[M[s].next[i]])
		dfs(M[s].next[i],d,path+1,min,C,kind,visit);
	}
	
}
int main()
{
	scanf("%d%d",&n,&q);

	for(int i =0;i<n;i++)
	{  
		Node p;
		int x;
		scanf("%d",&x);
		p.c = x;
		M.push_back(p);
	}
	
	for(int i =0;i<n-1;i++)
	{
	    int x,y;
	    scanf("%d%d",&x,&y);
	    M[x-1].next.push_back(y-1);
	    M[y-1].next.push_back(x-1);
	}
	for(int i=0;i<q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		vector<bool> C(21,false);
		int min=n+2,kind=0;
		vector<bool> visit(n+1,false);
		dfs(x-1,y-1,0,min,C,kind,visit);
		cout<<kind-1<<"\n";
	}
	return 0;
}
