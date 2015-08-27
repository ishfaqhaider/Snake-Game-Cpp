// ISHFAQ HAIDER QURESHI
// 1418-BSSE/F11A IIUI

#include"snake.h"

void main()
{ Snake s1;
 	cout<<"----------Developed By : ISHFAQ QURESHI----------";
	cout<<"\nEnter level of game between 1 to 5 "; cin>>s1.level;
	if (s1.level<1) s1.level=1; if (s1.level>5) s1.level=5;
gotoxy(0,1);
cout<<"Enter 1 for wall game(#) or 0 for classic game("<<char(177)<<") ";
cin>>s1.wall;
 s1.sleep=300-(50*s1.level);

		for(int i=l_y;i<=b_y;i++)
		for(int j=l_x;j<=b_x;j++)
		if(i==l_y || i==b_y || j==l_x || j==b_x )
	  { gotoxy(j,i); if(s1.wall) cout<<'#'; else cout<<char(177);  }
	gotoxy(0,b_y+2);
	  cout<<"Enter your lucky number to start game ";
	 int tg; cin>>tg;
	  
	  s1.ran=tg;
	  s1.GameStart();
	  s1.Print(1);
	gotoxy(0,b_y+2);
	cout<<"Press \'e\' for exit any time                       ";
	gotoxy(0,b_y+3);
	char c=getch();
	do	{
		do{ s1.Print(0);
			switch(c){
			case 72: { s1.Move(u); break;}
			case 75: { s1.Move(l); break;}
			case 80: { s1.Move(d); break;}
			case 77: { s1.Move(r); break;}	}
			s1.Print(1);
			Sleep(s1.sleep); 
			}
			while(!kbhit() && (!s1.End()) );
			gotoxy(0,b_y+3);
			if(!s1.End())
			c=getch();
	}while(c!='e' && c!='E' && (!s1.End()) );
	
	if(s1.End())
	{ //getch();
		gotoxy(0,b_y+3); cout<<"Game end any key to exit       ";
		do{ Sleep(200);
			s1.Print(0);
			gotoxy(0,b_y+2);
			Sleep(200);	
			s1.Print(1);
			gotoxy(0,b_y+2);	
			}while( !kbhit() );
	}
gotoxy(0,b_y+3);	  
system("pause");
}