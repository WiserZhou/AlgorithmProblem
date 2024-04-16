#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>
#include <cmath>
using namespace std;
int n,k,t;
double sig(vector<vector<int>> & N,int a)
{

    int n = N.size();
	double ave;
	for(int i =a;i<a+k;i++)
	{
		ave+=N[i][0];
	}
	ave = ave/(double) k;
	double sum=0;
	for(int i =a;i<a+k;i++)
	{

		sum+=pow(N[i][0]-ave,2);
		
	}
	sum=sum/(double)k;
	return sum;
	
}
bool cmp(vector<int> a,vector<int> b)
{
	return a[0]<b[0];
}
int main()
{
	scanf("%d%d%d",&n,&k,&t);
	vector<vector<int>> score;
	
	for(int i =0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		vector<int> c;
		c.push_back(x);
		c.push_back(i);
		score.push_back(c);
	}
	sort(score.begin(),score.end(),cmp);
	double min = 1e9;
	int flag ;
	for(int i =0;i<=n-k;i++)
	{
		double ss = sig(score,i);
		if(ss<min){
			min = ss;
			flag = i;
		}
	}
	int flag2 = flag +k-1;
    int maxx =0;
    for(int i =flag;i<=flag2;i++)
    {
    	maxx = max(maxx,score[i][1]);
	}
	cout<<maxx+1;
	return 0;
	
//	vector<double> choose(n+2);
//	vector<bool> flag(n+2,false);
//	for(int i =0;i<k;i++)
//	{
//		flag[i]=true;
//	}
//	choose[k] = sig(score,flag);
//	if(choose[k]<t) {
//		cout<<"k";
//		return 0;
//	}
//	for(int i =k+1;i<=n;i++)
//	{
//		double min=1e9;
//		vector
//		flag[i-1] = true;
//		for(int j = 1;j<=k;j++ )
//		{
//			flag[j-1] =false;
//			double s = sig(score,flag);
//			if(s<t) {
//				cout<<i;
//				return 0;
//			}
//			flag[j-1]=true;
//		}
//		choose[i]=
//	}
	
	
}
