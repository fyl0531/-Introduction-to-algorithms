#include<iostream>
#include<string>
#include<stdlib.h> 
using namespace std;
const int LEN=26;
char RAND[LEN]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

void PRINT_LCS(int **b,int i,int j,string X,string Y)
{//按逆序依次构造出LCS的所有元素 
	if(i==0||j==0)
        return;
    if(b[i][j]==0)
	{
        PRINT_LCS(b,i-1,j,X,Y);
	}
    if(b[i][j]==1)
    {
    	PRINT_LCS(b,i,j-1,X,Y);	
	}        
    if(b[i][j]==2)       
   {
   	    PRINT_LCS(b,i-1,j-1,X,Y);
        cout<<X[i-1]<<" ";
          
	}   
}
    
int LCS_Length(string X,string Y)
{//计算LCS长度 
	int m=X.size()+1;
	int n=Y.size()+1;
	int i,j;
	
	//建立二维数组c[m,n],保存X和Y的LCS长度 
	int** c=new int* [m];
	for(i=0;i<m;i++)
	{
		c[i]=new int [n];
	}
	//建立二维数组b[m,n],帮助构造最优解，记录箭头 
	int** b=new int* [m];
	for(i=0;i<m;i++)
	{
		b[i]=new int [n];
	}
	//二维数组b、c初始化 
	 for(i=0;i<m;i++){
        c[i][0] = 0;
        b[i][0] = 0;
    }
    for(j=0;j<n;j++){
        c[0][j] = 0;
        b[0][j] = 0;
    }
	cout<<"查找最长子序列二维矩阵(2=↖；1=←；0=↑)："<<endl; 
	//逐步填表 
	for(int i=1;i<m;i++)
	{
        for(int j=1;j<n;j++)
		{
            if(X[i-1]==Y[j-1])
			{
                c[i][j] = c[i-1][j-1]+1;
                b[i][j] = 2;
            }
			else
			{
                if(c[i-1][j]>=c[i][j-1])
				{
                    c[i][j] = c[i-1][j];
                    b[i][j] = 0;
                }
				else
				{
                    c[i][j] = c[i][j-1];
                    b[i][j] = 1;
                }
            }
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
	cout<<"最长公共子序列为：";
	//cout<<c[m-1][n-1];
	PRINT_LCS(b,m-1,n-1,X,Y);
	return c[m-1][n-1];	
}


int main()
{
	int i,j;
	int x,y;//X,Y字符串长度
	cout<<"输入第一个字符串的长度：";
	do
	{
		cin>>x;
	}while(x<=0);
	char* X=new char[x+1];
	X[x]='\0';
	int iRand=0;
	//srand((unsigned)time(0));
	for(int i=0;i<x;i++)
	{
		iRand=rand()%LEN;
		X[i]=RAND[iRand];
	}
	//RAND_CHAR(x,X);
	cout<<"随机生成的字符串为：";
	cout<<X<<endl; 
	
	cout<<"输入第二个字符串的长度：";
	do
	{
		cin>>y;
	}while(y<=0);
	char* Y=new char[y+1];
	Y[y]='\0';
	iRand=0;
	//srand((unsigned)time(0));
	for(int i=0;i<y;i++)
	{
		iRand=rand()%LEN;
		Y[i]=RAND[iRand];
	}
	//RAND_CHAR(y,Y);
	cout<<"随机生成的字符串为：";
	cout<<Y<<endl; 
	
	string s1=X;
	string s2=Y;
	
	cout<<endl<<"最长公共子序列长度为："<<LCS_Length(s1,s2);
	return 0; 
	system("pause");
	//string X,Y
}
