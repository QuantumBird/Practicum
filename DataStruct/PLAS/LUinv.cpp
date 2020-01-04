#include<stdio.h>
#include <string.h>
#define N 4
float buildMat()
int main()
{ 
	float a[N][N];
	float L[N][N],U[N][N],out[N][N], out1[N][N];
	float r[N][N],u[N][N];
	memset( a , 0 , sizeof(a));
	memset( L , 0 , sizeof(L));
	memset( U , 0 , sizeof(U));
	memset( r , 0 , sizeof(r));
	memset( u , 0 , sizeof(u));
	int n=N;
	int k,i,j;
	int flag=1;
	float s,t;
	printf("input A=\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%f",&a[i][j]);
		printf("输入矩阵:\n");
		for(i=0;i<n;i++)
		{
			for (j = 0; j < n; j++)
			{
				printf("%lf ", a[i][j]);
			}
			printf("\n");
		}
		for(j=0;j<n;j++)
			a[0][j]=a[0][j];  //计算U矩阵的第一行
		
		for(i=1;i<n;i++)
			a[i][0]=a[i][0]/a[0][0];   //计算L矩阵的第1列
		for(k=1;k<n;k++)
		{
			for(j=k;j<n;j++)
			{
				s=0;
				for (i=0;i<k;i++)
					s=s+a[k][i]*a[i][j];   //累加
				a[k][j]=a[k][j]-s; //计算U矩阵的其他元素
			}
			for(i=k+1;i<n;i++)
			{
				t=0;
				for(j=0;j<k;j++)
					t=t+a[i][j]*a[j][k];   //累加
				a[i][k]=(a[i][k]-t)/a[k][k];    //计算L矩阵的其他元素
			}
		}
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			{ 
				if(i>j)
				{ 
					L[i][j]=a[i][j]; 
					U[i][j]=0;
				}
				else
				{
					U[i][j]=a[i][j];
					if(i==j) 
						L[i][j]=1; 
					else 
						L[i][j]=0;
				}
			}  
			if(U[1][1]*U[2][2]*U[3][3]*U[4][4]==0)
			{
				flag=0;
				printf("\n逆矩阵不存在");}
			if(flag==1)
			{
				/////////////////////求L和U矩阵的逆
				for (i=0;i<n;i++) /*求矩阵U的逆 */
				{
					u[i][i]=1/U[i][i];//对角元素的值，直接取倒数
					for (k=i-1;k>=0;k--)
					{
						s=0;
						for (j=k+1;j<=i;j++)
							s=s+U[k][j]*u[j][i];
						u[k][i]=-s/U[k][k];//迭代计算，按列倒序依次得到每一个值，
					}
				}
				for (i=0;i<n;i++) //求矩阵L的逆 
				{
					r[i][i]=1; //对角元素的值，直接取倒数，这里为1
					for (k=i+1;k<n;k++)
					{
						for (j=i;j<=k-1;j++)
							r[k][i]=r[k][i]-L[k][j]*r[j][i];   //迭代计算，按列顺序依次得到每一个值
					}
				}
				/////////////////绘制矩阵LU分解后的L和U矩阵///////////////////////
				printf("\nLU分解后L矩阵:");
				for(i=0;i<n;i++)
				{ 
					printf("\n");
					for(j=0;j<n;j++)
						printf(" %lf",L[i][j]);
				}
				printf("\nLU分解后U矩阵:");
				for(i=0;i<n;i++)
				{ 
					printf("\n");
					for(j=0;j<n;j++)
						printf(" %lf",U[i][j]);
				}
				printf("\n");
				////////绘制L和U矩阵的逆矩阵
				printf("\nL矩阵的逆矩阵:");
				for(i=0;i<n;i++)
				{ 
					printf("\n");
					for(j=0;j<n;j++)
						printf(" %lf",r[i][j]);
				}
				printf("\nU矩阵的逆矩阵:");
				for(i=0;i<n;i++)
				{ 
					printf("\n");
					for(j=0;j<n;j++)
						printf(" %lf",u[i][j]);
				}
				printf("\n");
				//验证将L和U相乘，得到原矩阵
				printf("\nL矩阵和U矩阵乘积\n");
				for(i=0;i<n;i++)
				{
					for(j=0;j<n;j++)
					{
						out[i][j]=0;
					}
				}
				for(i=0;i<n;i++)
				{
					for(j=0;j<n;j++)
					{
						for(k=0;k<n;k++)
						{
							out[i][j]+=L[i][k]*U[k][j];
						}
					}  
				}
				for(i=0;i<n;i++)
				{
					for(j=0;j<n;j++)
					{
						printf("%lf\t",out[i][j]);
					}
					printf("\r\n");
				}
				//////////将r和u相乘，得到逆矩阵
				printf("\n原矩阵的逆矩阵:\n");
				for(i=0;i<n;i++)
				{
					for(j=0;j<n;j++)
					{out1[i][j]=0;}
				}
				for(i=0;i<n;i++)
				{
					for(j=0;j<n;j++)
					{
						for(k=0;k<n;k++)			
						{
							out1[i][j]+=u[i][k]*r[k][j];
						}
					}  
				}
				for(i=0;i<n;i++)
				{
					for(j=0;j<n;j++)
					{
						printf("%lf\t",out1[i][j]);
					}
					printf("\r\n");
				}
			}
}