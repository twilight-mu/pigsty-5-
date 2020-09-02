using namespace std;
#include<bits/stdc++.h>
#define random(a,b) (rand()%(b-a+1))+a

struct pig
{
	int species; //黑猪为1 小花猪为2 大白花猪为3 
	int id; 	//编号 
	int gday; 	//成长天数(一个月按30天计) 
	//int isInfected; //被感染为1 没被感染为2 
	double weight; //体重 
	pig *next;
};
class pigsty
{
	private:
		pig *head=NULL;
		int isblack=0;
		int sum=0;
	public:
		pigsty();				//初始化 
		int getspecies(int i);	//获取种类信息 
		int getgday(int i);		//获取成长天数信息 
		double getweight(int i);//获取重量 
		double getprice();		//获取价钱
		//void print();			//打印猪圈信息 
		//void clear();			//清空猪圈 
		void addpig(pig*p);		//加猪，主要用于初始化
		void insert(int i);      //加猪，主要用于购买插入 
		void setisblack(int i);	//设置黑猪圈,1为黑猪圈，0为非黑猪圈 
		int getsumspecies(int i);	//获取某种猪的数量 
		int getsum()
		{
			return sum;
		}
		int getisblack()
		{
			return isblack;
		}                
		pig* gethead()
		{
			return head;
		}
};
pigsty::pigsty()
{
	int sum=0;
	int isblack=0;
	head=NULL;
}
int pigsty::getspecies(int i) 
{
	pig *p=head;
	for(int k=0;k<i&&p!=NULL;k++)
	{
		p=p->next;
	}
	return p->species;
}
int pigsty::getgday(int i)
{
	pig *p=head;
	for(int k=0;k<i&&p!=NULL;k++)
	{
		p=p->next;
	}
	return p->gday;
}
double pigsty::getweight(int i)
{
	pig *p=head;
	for(int k=0;k<i&&p!=NULL;k++)
	{
		p=p->next;
	}
	return p->weight;
}
double pigsty::getprice()
{
	double sellprice=0;
	if(head==0)
	return 0;
	int day,flag=0;

	pig*p=head,*p1=p;
	while(p)
	{
		day=p->gday;
		if(day>=360||p->weight>75)
		{
			if(sum==1)
			{
			setisblack(0);
			head=NULL;
			delete p;
			sum--;
			break;
			}
			if(p->species==1)
			{
				sellprice+=30*p->weight;
			}
			if(p->species==2)
			{
				sellprice+=14*p->weight;
			}
			if(p->species==3)
			{
				sellprice+=12*p->weight;
			}
			p1->next=p->next;
			delete p;
			p=p1->next;
			sum--;
			continue;
		}
		else if(flag==0)
		{
			flag=1;
			head=p;
		}
		p1=p;
		p=p1->next;
	}
	return sellprice;
}
void pigsty::addpig(pig *p)
{
	sum++;
	p->next=NULL;
	if(head==NULL)
	{
		head=p;
	}
	else 
	{
		pig*p1=head;
		while(p1->next)
		{
			p1=p1->next;
		}
	p1->next=p;
	}
}
void pigsty::setisblack(int i)
{
	isblack=i;	
}
int pigsty::getsumspecies(int i)
{
	int count;
	pig *p=head;
	for(int k=0;k<sum&&p!=NULL;k++)
	{
		if(p->species==i)
		count++;
		p=p->next;
	}
	return count;
}
int getallpig(pigsty ps[])
{
	int count=0;
	for(int i=0;i<100;i++)
	{
		count+=ps[i].getsum();
	}
	return count;
}
void buypig(pigsty ps[])
{
	srand((int)time(NULL));
	int pig1=random(0,15);
	int pig2=random(0,15);
	int pig3=random(0,15);
	while(pig1--)
	{
		for(int i=0;i<100;i++)
		{
			if(ps[i].getisblack()==1&&ps[i].getsum()<10)
			{
				ps[i].insert(1);
				break; 
			}
			if(ps[i].gethead()==NULL)
			{
				ps[i].insert(1);
				ps[i].setisblack(1);
				break;
			}
		}		
	}	
	
	while(pig2--)
	{
		int ave=getallpig(ps)/100+1;
		for(int i=0;i<100;i++)
		{
			if(ps[i].getisblack()==0&&ps[i].getsum()<=ave)
			{
				ps[i].insert(2);
				break; 
			}
			if(ps[i].gethead()==NULL)
			{
				ps[i].insert(2);
				ps[i].setisblack(0);
				break;
			}
		}
	}
	while(pig3--)
	{
		int ave=getallpig(ps)/100+1;
		for(int i=0;i<100;i++)
		{
			if(ps[i].getisblack()==0&&ps[i].getsum()<=ave)
			{
				ps[i].insert(3);
				break; 
			}
			if(ps[i].gethead()==NULL)
			{
				ps[i].insert(3);
				ps[i].setisblack(0);
				break;
			}
		}
	}
}
void start(pigsty ps[])//程序开始，猪圈初始化 
{
	int count=300;	//开始先放300只猪 
	pig *p;
	while(count--)
	{
		srand((int)time(NULL));
		p=new pig;
		p->species=random(1,3);
		p->weight=random(20,50);
		p->gday=0;
		for(int i=0;i<100;i++)
		{
			if(p->species==1&&(ps[i].getisblack()==1||ps[i].gethead()==NULL)&&ps[i].getsum()<10)
			{
				p->id=ps[i].getsum();
				ps[i].addpig(p);
				ps[i].setisblack(1);
				break;
			}
			if(p->species!=1&&ps[i].getisblack()==0&&ps[i].getsum()<5)
			{
				p->id=ps[i].getsum();
				ps[i].addpig(p);
				break;
			}
		}
	}
}
void pigsty::insert(int i) 
{
	pig*p=new pig;
	p->species=i;		
	p->weight=random(20,30);	
	p->gday=0;
	if(head==NULL)
	{
		p->id=0;
		p->next=NULL;
		head=p;
		sum++;
		return;
	}
	if(head->id!=0)
	{
		p->id=0;
		p->next=head;
		head=p;
		sum++;
		return;
	}
	else 
	{
	pig*p1=head,*p2=p1;
	int k=0;
	while(p1->id==k&&p1->next)
	{
		k++;
		p2=p1;
		p1=p1->next;
	}
	if(p1->next==NULL)
	{
		p->id=sum;
		p->next=NULL;
		p1->next=p;
	}
	else
	{
		p->id=k;
		p2->next=p;
		p->next=p1;
	}
	sum++;
	} 
}
void oneday(pigsty ps[])
{
	for(int i=0;i<100;i++)
	{
		pig *p;
		p=ps[i].gethead();
		while(p)
		{
			srand((int)time(NULL));
			int w1=random(0,12);
			double w2=double(w1)/10.0;
			p->weight+=w2;
			p->gday++;
			p=p->next;
		}	
	} 
}
double getsumprice(pigsty ps[])
{
	double sumprice;
	for(int i=0;i<100;i++)
	{
		sumprice+=ps[i].getprice();
	}
	return sumprice;
}
int main()
{
	pigsty ps[100];
	start(ps);
	int day=0;
	while(true)
	{
		int n;
		cin>>n;
		if(n==0)
		break;
		char s;//d表示过一天，m表示过一个月 
		cin>>s;
		if(s=='d')
		{
			oneday(ps);
			day+=1;
		}
		if(s=='m')
		{
			for(int i=0;i<30;i++)
			oneday(ps);
			day+=30;
		}
		if(day>=90)
		{
			double sumprice=0;
			int sellpig1,sellpig2; 
			day-=90;
			sellpig1=getallpig(ps);
			for(int i=0;i<100;i++)
			{
				sumprice+=ps[i].getprice();
			}
			cout<<"已满三个月将自动出卷一批猪！"<<endl;
			sellpig2=getallpig(ps);
			cout<<"出圈成功，共计出卷"<<sellpig1-sellpig2<<"只猪,"<<"得到"<<sumprice<<"元！"<<endl; 
			cout<<"已满三个月将自动入卷一批猪！"<<endl;
			buypig(ps);
			cout<<"入圈成功！"<<endl; 
		}
	}
	return 0;
}
