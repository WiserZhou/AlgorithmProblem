#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>
#include <cmath>
using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	vector<int> N;
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		N.push_back(x);
	}
	int num=0;
	for(int i =0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(j==i) continue;
			for(int l = 0;l<n;l++)
			{
				if(l==j || l==i ) continue;
				for(int r = 0;r<n;r++)
				{
					if(r==i||r==j||r==l) continue;
					if(N[l]%N[i]==0 && N[r]%N[j]==0) num++;
				}
			}
		}
	}
	cout<<num;
	return 0;
}
