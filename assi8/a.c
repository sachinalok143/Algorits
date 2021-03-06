#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int min(int a[],int n)
{
	bool N=false;
	int l,m=a[0];
	for (int i = 1; i < n; ++i)if(a[i]!=a[i-1])N=true;
	if(N)
		{
			for (int i = 0; i < n; ++i)
				{
					if(m>=a[i]){m=a[i];l=i;}
				}
			return l;
		}
	else return n+1;
}
int min1(int *g1,int r,int *g)
{
	//if(r==0)return 0;
	int min=g[0];
	int l=0;
	//printf("lp=%d\n",l  );
	for (int i = 0; i < r; ++i)
		{
			if(min >= g[g1[i]]){min=g[g1[i]];l=i;}
		}
		//printf("l-%d,-%d\n",l,r );
	return l;
}
void mineffort1(int *w,int n)
{
	printf("+++part:1\n");
	int* g=(int*)malloc(n*sizeof(int));
	int* a=(int*)malloc(n*sizeof(int));
	int m;
	for (int i = 0; i < n; ++i)a[i]=w[i];
	for (int i = 0; i < n; ++i)
		{
			m=min(a,n);
			if(i==0)g[i]=w[m];
			else g[i]=w[m]+g[i-1];
			printf("\tFloor(%d):adding weight w(%d)-%d to bag,G[%d]=%d\n",i,m+1,w[m],i,g[i]);
			a[m]=999999999;
		}
	int sum=0;
	for (int i = 0; i < n; ++i)sum=sum+g[i];
	printf("---total effort: %d\n",sum);
}


void mineffort2(int *w,int n)
{
	printf("+++part:2\n");
	int *g=(int*)malloc(n*sizeof(int));
	int *g1=(int*)malloc(n*sizeof(int));
	int *a=(int*)malloc(n*sizeof(int));
	//	int *q=(int*)malloc(n*sizeof(int));
	int m1,m2,M,r=0;
	for (int i = 0; i < n; ++i)a[i]=w[i];
	//for (int i = 0; i < n; ++i)printf("%d\t",a[i] );
	for (int i = 0; i < n; ++i)
		{

			m1=min(a,n);
			int k=a[m1];
			a[m1]=999999999;
			m2=min(a,n);
			//printf("m1-%d,m2-%d\n",m1,m2 );
			//if(m1>=n||m2>=n)return;
			if(m1<n&&m2<n)
				{
					if(i!=0)
						{
							M=min1(g1,r,g);
							if(g[i-1]>a[m2]||(g[i-1]>g[g1[M]]&&r>0))
								{
									//printf("a[m2]=%d,k=%d,g[i-1]=%d\n",a[m2],k,g[i-1]);
									if (k+g[g1[M]]>k+a[m2])
										{
											g[i]=k+g[g1[M]];
											printf("\tFloor(%d):Depositing G[%d]-%d\n\t\t:adding w[%d]-%d,G[%d]-%d to bag;G[%d]=%d\n",i,i-1,g[i-1],m1+1,k,g1[M]+1,g[g1[M]],i,g[i]);
											g1[M]=i-1;
										}
									else
										{
											g[i]=k+a[m2];
											printf("\tFloor(%d):Depositing G[%d]-%d\n\t\t:adding w[%d]-%d,w[%d]-%d to bag;G[%d]=%d\n",i,i-1,g[i-1],m1+1,k,m2+1,a[m2],i,g[i]);
											a[m2]=999999999;
											g1[r]=i-1;
											r++;
										}
								}
							else
								{
									g[i]=g[i-1]+k;
									printf("\tFloor(%d):adding weight w(%d)-%d to bag,G[%d]=%d\n",i,m1+1,w[m1],i,g[i]);
								}
						}
					else
						{
							g[i]=k;
							printf("\tFloor(%d):adding weight w(%d)-%d to bag,G[%d]=%d\n",i,m1+1,w[m1],i,g[i]);
						}
				}
				else if(m1<n)
				{	
					if(g[i-1]>g[g1[M]]&&r>0)
					{
						M=min1(g1,r,g);
						//printf("m-%d,r-%d\n",M,r );
						g[i]=k+g[g1[M]];
						printf("\tFloor(%d):Depositing G[%d]-%d\n\t\t:adding w[%d]-%d,G[%d]-%d to bag;G[%d]=%d\n",i,i-1,g[i-1],m1+1,k,g1[M],g[g1[M]],i,g[i]);
						g1[M]=i-1;
					}
					else
					{
						//M=min1(g1,r,g);
						g[i]=g[i-1]+k;
						printf("\tFloor(%d):adding w[%d]-%d, to bag;G[%d]=%d\n",i,m1+1,k,i,g[i]);
						//g1[M]=i-1;
					}
				}
				else {
					M=min1(g1,r,g);
					g[i]=g[i-1]+g[g1[M]];
					printf("\tFloor(%d):adding weight G(%d)-%d to bag,G[%d]=%d\n",i,g1[M],g[g1[M]],i,g[i]);
					}

		}
	int sum=0;
	for (int i = 0; i < n; ++i)
		{
			sum=sum+g[i];
		}
	printf("---total effort: %d\n",sum);
}

int main()
{
	int n;
	scanf("%d",&n);
	printf("n-%d\n", n);
	int *w=(int*)malloc(n*sizeof(int));
	for (int i = 0; i < n; ++i)
		{
			scanf("%d",&w[i]);
			printf("%d\t",w[i]);
		}
	printf("\n");
	mineffort1(w,n);
	mineffort2(w,n);
	return 0;
}
