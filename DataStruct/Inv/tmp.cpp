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