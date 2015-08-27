// ISHFAQ HAIDER QURESHI
// 1418-BSSE/F11A IIUI

#include<iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define b_x 69 // it can not be more than 78
#define b_y 19 // it can not be more than 19
#define l_x 6 // it can not be less than 1
#define l_y 3 // it can not be less than 3

using namespace std;
void gotoxy(int x, int y) { 
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}
enum dir {u,l,d,r}; // 0 up, 1 left, 2 down, 3 right.. this will save latest 
class Dot{
public:	int xx, yy;
};								// direction of snake
class Node:public Dot // inherit class dot
{public:
	Node *previous, *next;
	Node(){ next=previous=0; }
};
class Snake{
private:
		bool first_point;
		int score;
		bool bonus_on;
		int last_bonus_at;
		int bonus_time_multiplier;
		float bonus_start,bonus_end;
		int total_bonus;
		Node *head;	
		Node point; // for new dot
		Node bonus;
		Node last_tail;
		dir dd;
		void deletefromtail();
		void addtohead(Node* temp);
		void addtotail(Node* temp);
		void NewPoint();
		void MoveTo(dir);
		bool Exist(Node*);
public: int ran;
		int level,sleep; // sleep time after one move operation
		bool wall;
		Snake();
		~Snake();
		bool IsEmpty();
		void Print(bool);
		void Move(dir temp);
		bool End();
		void CheckPoint();
		int Rand();
		void GameStart();
		void Bonus();
};
int Snake::Rand()  // function to genrate 99% randomed number
{ int x=(head->previous->xx)*(head->next->next->yy);
if(ran<=0 || ran>=32000)
	ran=125;
int temp;
 if(ran>x) {temp=ran; ran=x; x=temp;}
 ran=x%ran;
 int ret;
 for (int i=0;i<=ran;i++)
	ret=rand();
 ran=rand()*rand();
return ret;
}

bool Snake::Exist(Node* temp)
{ Node *tt=head;
do{ if(tt->xx==temp->xx && tt->yy==temp->yy )
	 return 1; tt=tt->next;
}while(tt!=head);
return 0;
}
void Snake::NewPoint()
{ int a=0,b=0;
do{ a=Rand();
abc: b=Rand();
if(a==b) goto abc;
a=(a%(b_x-l_x-1));
a=a+1+l_x;
b=(b%(b_y-l_y-1));
b=b+l_y+1;
point.xx=a; point.yy=b;
}while(Exist(&point) || (bonus.xx==point.xx && bonus.yy==point.yy ) );
if (first_point==0) {score=0; first_point=1;}
else score++;
gotoxy(b_x-12,b_y+1); cout<<"Score: "<<(score*level)+total_bonus;
}
void Snake::CheckPoint()
{
	if(Exist(&point))
  { Node *tem=new Node;
tem->xx=last_tail.xx;
tem->yy=last_tail.yy;
addtotail(tem);
NewPoint(); }

}
void Snake::Bonus()
{ if( score>0 && score%5==0 && bonus_on==0 && score>last_bonus_at ) // print bonus
{ int a=0,b=0;
do{ a=Rand();
abc: b=Rand();
if(a==b) goto abc;
a=(a%(b_x-l_x-1));
a=a+1+l_x;
b=(b%(b_y-l_y-1));
b=b+l_y+1;
bonus.xx=a; bonus.yy=b;
}while( Exist(&bonus) || (bonus.xx==point.xx && bonus.yy==point.yy ));
bonus_start=clock();
gotoxy(bonus.xx,bonus.yy); cout<<'$';
bonus_end=bonus_start+(bonus_time_multiplier*sleep);
bonus_on=1; // set flag
last_bonus_at=score;
gotoxy(0,b_y+3); 
//cout<<"bonus start ";
}
if(bonus_on)
{  int tt=clock();
	if(tt>bonus_end)
	{ bonus_on=0; bonus_start=0; bonus_end=0;
		gotoxy(bonus.xx,bonus.yy); cout<<' ';
		bonus.xx=-1; bonus.yy=-1;
	gotoxy(0,b_y+3); 
	//cout<<"bonus finish  ";
	}
}

if( bonus_on==1 && Exist(&bonus) )
{ float dif=clock();
	if(dif<=bonus_end)
	{ float bb=0;
		bb=((bonus_end-dif)/(bonus_end-bonus_start));
		bb=bb*(float(level))*50;
		total_bonus+=int(bb);  
		bonus_on=0;
		bonus_start=0; bonus_end=0;
		bonus.xx=-1; bonus.yy=-1;
		gotoxy(b_x-5,b_y+1); cout<<(score*level)+total_bonus;
	gotoxy(0,b_y+3); 
	//cout<<"bonus collect  ";
	}
}


}
bool Snake::End()
{ 	Node *cmp=head->next;
	while(cmp!=head)
	{if( head->xx==cmp->xx && head->yy==cmp->yy )
		return 1;
	 	cmp=cmp->next;
		}
	if(head->yy==l_y || head->yy==b_y || head->xx==l_x || head->xx==b_x) 
		return 1;	
	return 0;
}
void Snake::MoveTo(dir tt)
{ int a=head->xx, b=head->yy;
	head=head->previous;
	last_tail.xx=head->xx;
	last_tail.yy=head->yy;
	switch(tt){
case u:{ if(!wall && b==l_y+1 ) b=b_y-1; else b--;   dd=u; break;}
case l:{ if(!wall && a==l_x+1 ) a=b_x-1; else a--;   dd=l; break;}
case d:{ if(!wall && b==b_y-1 ) b=l_y+1; else b++;   dd=d; break;}
case r:{ if(!wall && a==b_x-1 ) a=l_x+1; else a++;   dd=r; break;}
	}
head->xx=a;
head->yy=b;
CheckPoint();
Bonus();
}
void Snake::Move(dir temp)
{
switch(dd){
	case u:{
	switch(temp){	case u: {MoveTo(temp); break;}
					case l: {MoveTo(temp); break;}
					case r: {MoveTo(temp); break;}
							 } break;}
	case l:{
	switch(temp){	case u: {MoveTo(temp); break;}
					case d: {MoveTo(temp); break;}
					case l: {MoveTo(temp); break;}
							} break;} 
	case d:{
	switch(temp){	case d: {MoveTo(temp); break;}
					case l: {MoveTo(temp); break;}
					case r: {MoveTo(temp); break;}
							} break;} 
	case r:{
	switch(temp){	case r: {MoveTo(temp); break;}
					case u: {MoveTo(temp); break;}
					case d: {MoveTo(temp); break;}
							} break;}
}
}
Snake::Snake()
{ head=0; score=-1; level=5; first_point=0;
bonus_time_multiplier=(b_x-l_x-2)+(b_y-l_y-2);
bonus_on=0;
last_bonus_at=0;
bonus.xx=-1; bonus.yy=-1;
total_bonus=0;
}
void Snake::GameStart()
{int i=30,j=10;
Node *temp; 
dd=l;
for(i=30;i<=40;i++)
{ temp=new Node;
	temp->xx=i; temp->yy=j;
	addtotail(temp);
}
NewPoint();
}

bool Snake::IsEmpty()
{ return head==0?1:0; }

Snake::~Snake()
{ while(!IsEmpty())
	deletefromtail(); }

void Snake::deletefromtail()
{ if(!IsEmpty())
{ if(head==head->next)
	{ delete head; head=0; }
else { Node *temp=head->previous;
		temp->previous->next=head;
		head->previous=temp->previous;
		delete temp;}
}
}
void Snake::addtotail(Node* temp)
{ if(head==0)
{head=temp; head->previous=head;
head->next=head;}
else{  Node *tt=head->previous;
	tt->next=temp;
	temp->previous=tt;
	temp->next=head;
	head->previous=temp;}
}

void Snake::Print(bool b)
{ if(!IsEmpty())
{ Node *ctail=head->previous;
	Node *temp=head->next;
	gotoxy(point.xx,point.yy);			// printing dot
	if(b) cout<<'O'; else cout<<' ';	// printing dot 
	do{
		gotoxy(temp->xx,temp->yy);	
		if(temp==head)
		{if(b){switch(dd){ 
			case u:{cout<<char(30);break;}  // 30 
			case d:{cout<<char(31);break;}  // 31
			case l:{cout<<char(17);break;}   // 17
			case r:{cout<<char(16);break;}}  // 16
				}
		else cout<<' ';
		}
		else { if(b) cout<<char(236); else cout<<' '; }
//cout<<"\n"<<int(temp->previous)<<'\t'<<int(temp)<<'\t'<<int(temp->next);
		temp=temp->next;
	} while(temp!=head->next);
	

}
}
