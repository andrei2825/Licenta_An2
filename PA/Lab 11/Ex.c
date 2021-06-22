#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
int i,j,k,a,b,u,v,n,ne=1;
int min,mincost=0,cost[12][12],parent[12];
int find(int);
int uni(int,int);
void main()
{
	n = 12;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cost[i][j] = INT_MAX;
		}
	}
    cost[8][0] = 3;
    cost[8][9] = 5;
    cost[8][11] = 8;
    cost[0][1] = 9;
    cost[0][6] = 10;
    cost[0][7] = 6;
    cost[1][2] = 5;
    cost[1][6] = 11;
    cost[2][3] = 8;
    cost[2][4] = 12;
    cost[3][5] = 9;
    cost[4][5] = 2;
    cost[6][7] = 4;
    cost[9][10] = 14;
    cost[10][11] = 7;
    
    cost[0][8] = 3;
    cost[9][8] = 5;
    cost[11][8] = 8;
    cost[1][0] = 9;
    cost[6][0] = 10;
    cost[7][0] = 6;
    cost[2][1] = 5;
    cost[6][1] = 11;
    cost[3][2] = 8;
    cost[4][2] = 12;
    cost[5][3] = 9;
    cost[5][4] = 2;
    cost[7][6] = 4;
    cost[10][9] = 14;
    cost[11][10] = 7;

	while(ne < n)
	{
		for(i=0,min=INT_MAX;i<n;i++)
		{
			for(j=0;j < n;j++)
			{
				if(cost[i][j] < min)
				{
					min=cost[i][j];
					a=u=i;
					b=v=j;
				}
			}
		}
		u=find(u);
		v=find(v);
		if(uni(u,v))
		{
			printf("(%c,%c) de cost %d\n",a + 'A',b + 'A',min);
      ne++;
			mincost +=min;
		}
		cost[a][b]=cost[b][a]=999;
	}
	printf("\nCost minim = %d\n",mincost);
}
int find(int i)
{
	while(parent[i])
	  i=parent[i];
	return i;
}
int uni(int i,int j)
{
	if(i!=j)
	{
		parent[j]=i;
		return 1;
	}
	return 0;
}