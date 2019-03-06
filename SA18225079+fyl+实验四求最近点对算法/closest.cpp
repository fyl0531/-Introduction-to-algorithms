#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;

struct point
{//点结构 
	double x;//x坐标 
	double y;//y坐标 
};

double Distance(point a,point b)
{//计算两点间距离 
	double s;
	s=sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	return s;
}
bool cmp1(point a,point b)
{//按y排序辅助函数 
	return a.y<b.y;
}
bool cmp2(point a,point b)
{//按x排序辅助函数 
	return a.x<b.x;
}

double ClosestPoint(point s[],int low,int high,point rec[])
{
	double d1,d2,d3,d;
	int mid,i,j,index;
	double x1,y1,x2,y2;//记录最近点的位置
	point P[high-low+1],temp1[2],temp2[2],temp3[2];//temp1记录左边的最近点对,temp2记录右边，temp3记录中间 
	if(high-low==1)
	{//只有两个点的时候 
		rec[0].x=s[low].x;
		rec[0].y=s[low].y;
		rec[1].x=s[high].x;
		rec[1].y=s[high].y;
		return Distance(s[low],s[high]); 
	} 
	if(high-low==2)
	{//当有三个点的时候
		//两两计算，找出距离最近的两点 
		d1=Distance(s[low],s[low+1]);
		d2=Distance(s[low+1],s[high]);
		d3=Distance(s[low],s[high]);
		if((d1<d2)&&(d1<d3))
		{
			rec[0].x=s[low].x;
			rec[0].y=s[low].y;
			rec[1].x=s[low+1].x;
			rec[1].y=s[low+1].y;
			return d1;
		} 
		else if (d2<d3)
		{
		 	rec[0].x=s[low+1].x;
			rec[0].y=s[low+1].y;
			rec[1].x=s[high].x;
			rec[1].y=s[high].y;	
			return d2;
		}
		else
		{
		 	rec[0].x=s[low].x;
			rec[0].y=s[low].y;
			rec[1].x=s[high].x;
			rec[1].y=s[high].y;
			return d3;
		}	
	}
	//三个结点以上的采用递归的办法
	
	mid=(low+high)/2;
	d1=ClosestPoint(s,low,mid,rec);//左递归 
	temp1[0]=rec[0];
	temp1[1]=rec[1];
	d2=ClosestPoint(s,mid+1,high,rec);//右递归 
	temp2[0]=rec[0];
	temp2[1]=rec[1];
	if(d1<d2)
	{//比较左右递归所得的最近点对距离 
		d=d1;
		rec[0]=temp1[0];
		rec[1]=temp1[1];
	 } 
	else
	{
		d=d2;
		rec[0]=temp2[0];
		rec[1]=temp2[1];
	}
	
	index=0;
	for(i=mid;(i>=low)&&((s[mid].x-s[i].x)<d);i--)
	{//记录[mid-d,mid]区域的点 
		P[index++]=s[i];
	}
	for(i=mid+1;(i<=high)&&((s[i].x-s[mid].x)<d);i++)
	{//记录[mid,mid+d]区域的点 
		P[index++]=s[i];
	}
	sort(P,P+index,cmp1);//对给定区间所有元素进行排序
	for(i=0;i<index;i++)
	{//找出[mid-d,mid+d]中的最近点对
		for(j=i+1;j<i+7&&j<index;j++)
		{
			if((P[j].y-P[i].y)>=d)
			{
				break;
			}
			else
			{
				d3=Distance(P[i],P[j]);
				if(d3<d)
				{
					rec[0].x=P[i].x;
					rec[0].y=P[i].y;
                    rec[1].x=P[j].x;
					rec[1].y=P[j].y;	
					d=d3;
				}
			}
		 } 
		 //return d;	
	 }
	 return d;
}


int main()
{
	point p[100];
	int n;
	double minDist;
	cout<<"输入点的个数："<<endl;
	cin>>n;
	cout<<"所有点的坐标："<<endl;
	for(int i=0;i<n;i++)
	{
		p[i].x=rand()%100;
		p[i].y=rand()%100;	
		cout<<"("<<p[i].x<<","<<p[i].y<<")"<<"  "; 
	 } 
	sort(p,p+n,cmp2);//对所有点在x轴上排序 
	
	cout<<endl<<"按x坐标排序后所有点的坐标："<<endl;
	for(int i=0;i<n;i++)
	{	
		cout<<"("<<p[i].x<<","<<p[i].y<<")"<<"  "; 
	 } 
	point index[2];
	minDist=ClosestPoint(p,0,n-1,index);

	cout<<endl<<"最小距离点对为：("<<index[0].x<<","<<index[0].y<<"),("<<index[1].x<<","<<index[1].y<<")"<<endl;
    cout<<"最小距离为："<<minDist<<endl;    
    system("pause");
    return 0;
}






















