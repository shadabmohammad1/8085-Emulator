#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
char prog[0XFF][0XF];
int PC=0,noi=0,mnxptr=0;
int A,B,C,D,E,H,L,M,PSW,memory[0X4FFF],hexcode,SP;
int c_flag=0,z_flag=0,s_flag=0,p_flag=0,ac_flag=0,storing_flag=0;

//===========================Reset Values================
void reset_regs()
{
A=B=C=D=E=H=L=0;
}
void reset_flags()
{
c_flag=z_flag=s_flag=p_flag=ac_flag=0;
}

//=============================DISPLAY OUTPUT=================
void display()
{
    int i;
    char reg[7][2]={"A","B","C","D","E","H","L"},temp[10];
    char flags[8][3]={"S","Z","","AC","","P","","C"};
    clearviewport();


     setfillstyle(1,7);
     bar(100,60,450,240);

     setfillstyle(1,0);
   bar(105,65,200,80);
     outtextxy(107,67,"PC : ");
     sprintf(temp,"%X",PC);
     outtextxy(140,67,temp);
   bar(220,65,350,80);
     outtextxy(222,67,"SP : ");
     sprintf(temp,"%X",SP);
     outtextxy(265,67,temp);

     setfillstyle(1,0);
     bar(145,85,420,100);
     outtextxy(150,87,"Next Instruction : ");
     outtextxy(300,87,prog[mnxptr]);
     mnxptr++;

    outtextxy(105,105,"Registers :");
    setfillstyle(1,9);
    for(i=0;i<=6;i++)
       {
       bar(100+i*50,120,100+(i+1)*50,140);
       rectangle(100+i*50,120,100+(i+1)*50,140);
       outtextxy(100+i*50+20,120+8,reg[i]);
       }
     setfillstyle(1,2);
    for(i=0;i<=6;i++)
       {
       bar(100+i*50,140,100+(i+1)*50,160);
       rectangle(100+i*50,140,100+(i+1)*50,160);
       switch(i)
       {
	case 0 : sprintf(temp,"%X",A);
		break;
	case 1 : sprintf(temp,"%X",B);
		break;
	case 2 : sprintf(temp,"%X",C);
		break;
	case 3 : sprintf(temp,"%X",D);
		break;
	case 4 : sprintf(temp,"%X",E);
		break;
	case 5 : sprintf(temp,"%X",H);
		break;
	case 6 : sprintf(temp,"%X",L);
		break;
       }
       outtextxy(100+i*50+20,140+8,temp);
       }
       outtextxy(105,175,"Flag Status :");
       setfillstyle(1,9);
    for(i=0;i<=7;i++)
       {
       bar(100+i*43,190,100+(i+1)*43,210);
       rectangle(100+i*43,190,100+(i+1)*43,210);
       outtextxy(100+i*43+15,190+8,flags[i]);
       }
     setfillstyle(1,2);
    for(i=0;i<=7;i++)
       {
       strcpy(temp,"0");
       bar(100+i*43,210,100+(i+1)*43,230);
       rectangle(100+i*43,210,100+(i+1)*43,230);
       switch(i)
       {
	case 0 : sprintf(temp,"%d",s_flag);
		break;
	case 1 : sprintf(temp,"%d",z_flag);
		break;
	case 3 : sprintf(temp,"%d",ac_flag);
		break;
	case 5 : sprintf(temp,"%d",p_flag);
		break;
	case 7 : sprintf(temp,"%d",c_flag);
		break;
       }
       outtextxy(100+i*43+15,210+8,temp);
       }
     getch();
}

/*=================================FLAGS==================================*/
void flags(int prev,int curnt)
{
    int i,count=0,mask,temp;
    //================Carry Flag==============
    mask=0X100;
    temp=curnt&mask;
    if(temp==0X100)
    {
	c_flag=1;
	curnt=curnt&0XFF;
    }
    else
	c_flag=0;
    //=============Sign Flag=============
    if(curnt<0)
	s_flag=1;
    else
	s_flag=0;
    //===============Zero Flag==============
    if(curnt==0)
	z_flag=1;
    else
	z_flag=0;

    //=================Parity Flag===============
    for(i=0;i<=8;i++)
    {
	mask=1<<i;
	if((curnt&mask)!=0)
	    count++;
    }
    if(count%2==0)
	p_flag=1;
    else
	p_flag=0;
    //======================Auxiliary Carry Flag=============
    mask=0XF;
    if((prev&0XF)>(curnt&0XF) && (curnt&0XF0)>(prev&0XF0) || (prev&0XF)<(curnt&0XF) && (curnt&0XF0)<(prev&0XF0))
	ac_flag=1;
    else
	ac_flag=0;

}

/*--------------------------------Functions------------------------------------------*/

void run(int step)
{
    int memloc=0,data=0,prev=0;
//    PC=1;
//    memory[1]=0X76;
   PSW=s_flag*0X80+z_flag*0X40+ac_flag*0X10+p_flag*0X4+c_flag*0X1;
   while(1)
    {
    if(step==1)
     display();
    switch(memory[PC])
    {
	case 0X00 : break;
	//--------------------Move Opreations---------------------//
	case 0X7F : A=A;
		    break;
	case 0X78 : A=B;
		    break;
	case 0X79 : A=C;
		    break;
	case 0X7A : A=D;
		    break;
	case 0X7B : A=E;
		    break;
	case 0X7C : A=H;
		    break;
	case 0X7D : A=L;
		    break;
	case 0X7E : memloc=L;
		    memloc+=H<<8;
		    A=memory[memloc];
		    break;
	case 0X47 : B=A;
		    break;
	case 0X40 : B=B;
		    break;
	case 0X41 : B=C;
		    break;
	case 0X42 : B=D;
		    break;
	case 0X43 : B=E;
		    break;
	case 0X44 : B=H;
		    break;
	case 0X45 : B=L;
		    break;
	case 0X46 : memloc=L;
		    memloc+=H<<8;
		    B=memory[memloc];
		    break;
	case 0X4F : C=A;
		    break;
	case 0X48 : C=B;
		    break;
	case 0X49 : C=C;
		    break;
	case 0X4A : C=D;
		    break;
	case 0X4B : C=E;
		    break;
	case 0X4C : C=H;
		    break;
	case 0X4D : C=L;
		    break;
	case 0X4E : memloc=L;
		    memloc+=H<<8;
		    C=memory[memloc];
		    break;
	case 0X57 : D=A;
		    break;
	case 0X50 : D=B;
		    break;
	case 0X51 : D=C;
		    break;
	case 0X52 : D=D;
		    break;
	case 0X53 : D=E;
		    break;
	case 0X54 : D=H;
		    break;
	case 0X55 : D=L;
		    break;
	case 0X56 : memloc=L;
		    memloc+=H<<8;
		    D=memory[memloc];
		    break;
	case 0X5F : E=A;
		    break;
	case 0X58 : E=B;
		    break;
	case 0X59 : E=C;
		    break;
	case 0X5A : E=D;
		    break;
	case 0X5B : E=E;
		    break;
	case 0X5C : E=H;
		    break;
	case 0X5D : E=L;
		    break;
	case 0X5E : memloc=L;
		    memloc+=H<<8;
		    E=memory[memloc];
		    break;
	case 0X67 : H=A;
		    break;
	case 0X60 : H=B;
		    break;
	case 0X61 : H=C;
		    break;
	case 0X62 : H=D;
		    break;
	case 0X63 : H=E;
		    break;
	case 0X64 : H=H;
		    break;
	case 0X65 : H=L;
		    break;
	case 0X66 : memloc=L;
		    memloc+=H<<8;
		    H=memory[memloc];
		    break;
	case 0X6F : L=A;
		    break;
	case 0X68 : L=B;
		    break;
	case 0X69 : L=C;
		    break;
	case 0X6A : L=D;
		    break;
	case 0X6B : L=E;
		    break;
	case 0X6C : L=H;
		    break;
	case 0X6D : L=L;
		    break;
	case 0X6E : memloc=L;
		    memloc+=H<<8;
		    L=memory[memloc];
		    break;
	case 0X77 : memloc=L;
		    memloc+=H<<8;
		    memory[memloc]=A;
		    break;
	case 0X70 : memloc=L;
		    memloc+=H<<8;
		    memory[memloc]=B;
		    break;
	case 0X71 : memloc=L;
		    memloc+=H<<8;
		    memory[memloc]=C;
		    break;
	case 0X72 : memloc=L;
		    memloc+=H<<8;
		    memory[memloc]=D;
		    break;
	case 0X73 : memloc=L;
		    memloc+=H<<8;
		    memory[memloc]=E;
		    break;
	case 0X74 : memloc=L;
		    memloc+=H<<8;
		    memory[memloc]=H;
		    break;
	case 0X75 : memloc=L;
		    memloc+=H<<8;
		    memory[memloc]=L;
		    break;
	//----------------------------HLT-------------------------
	case 0X76 : return;
	//======================XCHG=====================
	case 0XEB : prev=E,data=D;
		    E=L,D=H;
		    L=prev,H=data;
		    break;
	//-------------------------LDA Adrss---------------------------
	case 0X3A : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    A=memory[memloc];
		    break;
       //-------------------------STA Adrss---------------------------
	case 0X32 : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    memory[memloc]=A;
		    break;
	//=========================LHLD================================
	case 0X2A : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    L=memory[memloc];
		    H=memory[memloc+1];
		    break;
	//==========================SHLD===============================
	case 0X22 : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    memory[memloc]=L;
		    memory[memloc+1]=H;
		    break;
	//-------------------------MVI Data-----------------------------
	case 0X3E : PC++;
		    data=memory[PC];
		    A=data;
		    break;
	case 0X06 : PC++;
		    data=memory[PC];
		    B=data;
                    break;
	case 0X0E : PC++;
		    data=memory[PC];
		    C=data;
		    break;
	case 0X16 : PC++;
		    data=memory[PC];
                    D=data;
		    break;
        case 0X1E : PC++;
                    data=memory[PC];
		    E=data;
		    break;
	case 0X26 : PC++;
		    data=memory[PC];
		    H=data;
		    break;
	case 0X2E : PC++;
		    data=memory[PC];
		    L=data;
		    break;
	case 0X36 : PC++;
		    data=memory[PC];
		    memloc=L;
		    memloc+=H<<8;
		    memory[memloc]=data;
		    break;
	//------------------------LXI Rp, Addrs--------------------------------
	case 0X01 : PC++;
		    C=memory[PC];
		    PC++;
		    B=memory[PC];
		    break;
	case 0X11 : PC++;
		    E=memory[PC];
		    PC++;
		    D=memory[PC];
		    break;
	case 0X21 : PC++;
		    L=memory[PC];
		    PC++;
		    H=memory[PC];
		    break;
	case 0X31 : PC++;
		    SP=memory[PC];
		    PC++;
		    SP+=memory[PC]<<8;
		    break;
	//========================ADD R===================
	case 0X87 : prev=A;
		    A=A+A;
		    flags(prev,A);
		    A=A&0XFF;
		    break;
	case 0X80 : prev=A;
		    A=A+B;
		    flags(prev,A);
		    A=A&0XFF;
		    break;
	case 0X81 : prev=A;
		    A=A+C;
		    flags(prev,A);
		    A=A&0XFF;
		    break;
	case 0X82 : prev=A;
		    A=A+D;
		    flags(prev,A);
		    A=A&0XFF;
		    break;
	case 0X83 : prev=A;
		    A=A+E;
		    flags(prev,A);
		    A=A&0XFF;
		    break;
	case 0X84 : prev=A;
		    A=A+H;
		    flags(prev,A);
		    A=A&0XFF;
		    break;
	case 0X85 : prev=A;
		    A=A+L;
		    flags(prev,A);
		    A=A&0XFF;
		    break;
	case 0X86 : prev=A;
		    memloc=L;
		    memloc+=H<<8;
		    A=A+memory[memloc];
		    flags(prev,A);
		    A=A&0XFF;
		    break;
	//======================SUB R=======================
	case 0X97 : prev=A;
		    A=A-A;
		    flags(prev,A);
		    if(c_flag==1)
		    A=~A+1,s_flag=1;
		    break;
	case 0X90 : prev=A;
		    A=A-B;
		    flags(prev,A);
		    if(c_flag==1)
		    A=~A+1,s_flag=1;
		    break;
	case 0X91 : prev=A;
		    A=A-C;
		    flags(prev,A);
		    if(c_flag==1)
		    A=~A+1,s_flag=1;
		    break;
	case 0X92 : prev=A;
		    A=A-D;
		    flags(prev,A);
		    if(c_flag==1)
		    A=~A+1,s_flag=1;
		    break;
	case 0X93 : prev=A;
		    A=A-E;
		    flags(prev,A);
		    if(c_flag==1)
		    A=~A+1,s_flag=1;
		    break;
	case 0X94 : prev=A;
		    A=A-H;
		    flags(prev,A);
		    if(c_flag==1)
		    A=~A+1,s_flag=1;
		    break;
	case 0X95 : prev=A;
		    A=A-L;
		    flags(prev,A);
		    if(c_flag==1)
		    A=~A+1,s_flag=1;
		    break;
	case 0X96 : prev=A;
		    memloc=L;
		    memloc+=H<<8;
		    A=A-memory[memloc];
		    flags(prev,A);
		    if(c_flag==1)
		    A=~A+1,s_flag=1;
		    break;
	//======================DAD Rp===================
	case 0X09 : L=L+C;
		    flags(L,L);
		    L=L&0XFF;
		    if(c_flag==1)
		    H++;
		    H=H+B;
		    flags(H,H);
		    H=H&0XFF;
		    prev=c_flag;
		    reset_flags();
		    c_flag=prev;
		    break;
	 case 0X19 : L=L+E;
		    flags(L,L);
		    L=L&0XFF;
		    if(c_flag==1)
		    H++;
		    H=H+D;
		    H=H&0XFF;
		    flags(H,H);
		    prev=c_flag;
		    reset_flags();
		    c_flag=prev;
		    break;
	case 0X29 : L=L+L;
		    flags(L,L);
		    L=L&0XFF;
		    if(c_flag==1)
		    H++;
		    H=H+H;
		    H=H&0XFF;
		    flags(H,H);
		    prev=c_flag;
		    reset_flags();
		    c_flag=prev;
		    break;
	 case 0X39 : L=L+SP&0X00FF;
		    flags(L,L);
		    L=L&0XFF;
		    if(c_flag==1)
		    H++;
		    H=H+SP&0XFF00;
		    flags(H,H);
		    H=H&0XFF;
		    prev=c_flag;
		    reset_flags();
		    c_flag=prev;
		    break;
	//=====================CMP R=========================
	case 0XBF : flags(A-A,A-A);
		    break;
	case 0XB8 : flags(A-B,A-B);
		    break;
	case 0XB9 : flags(A-C,A-C);
		    break;
	case 0XBA : flags(A-D,A-D);
		    break;
	case 0XBB : flags(A-E,A-E);
		    break;
	case 0XBC : flags(A-H,A-H);
		    break;
	case 0XBD : flags(A-L,A-L);
		    break;
	case 0XBE : memloc=L;
		    memloc+=H<<8;
		    data=memory[memloc];
		    flags(A-data,A-data);
		    break;

	//====================Jump Instructions=============
	case 0XDA : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    if(c_flag==1)
			PC=memloc-1;
		    break;
	case 0XFA : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    if(s_flag==1)
			PC=memloc-1;
		    break;
	case 0XC3 : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
			PC=memloc-1;
		    break;
	case 0XD2 : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    if(c_flag==0)
			PC=memloc-1;
		    break;
	case 0XC2 : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    if(z_flag==0)
			PC=memloc-1;
		    break;
	case 0XF2 : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    if(s_flag==0)
			PC=memloc-1;
		    break;
	case 0XEA : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    if(p_flag==1)
			PC=memloc-1;
		    break;
	case 0XE2 : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    if(p_flag==0)
			PC=memloc-1;
		    break;
	case 0XCA : PC++;
		    memloc=memory[PC];
		    PC++;
		    memloc+=memory[PC]<<8;
		    if(z_flag==1)
			PC=memloc-1;
		    break;
    //===========================INR R==================
	case 0X3C : prev=A;
		    A=A+1;
		    flags(prev,A);
		    A=A&0XFF;
		    break;
	case 0X04 : prev=B;
		    B=B+1;
		    flags(prev,B);
		    B=B&0XFF;
		    break;
	case 0X0C : prev=C;
		    C=C+1;
		    flags(prev,C);
		    C=C&0XFF;
		    break;
	case 0X14 : prev=D;
		    D=D+1;
		    flags(prev,D);
		    D=D&0XFF;
		    break;
	case 0X1C : prev=E;
		    E=E+1;
		    flags(prev,E);
		    E=E&0XFF;
		    break;
	case 0X24 : prev=H;
		    H=H+1;
		    flags(prev,H);
		    H=H&0XFF;
		    break;
	case 0X2C : prev=L;
		    L=L+1;
		    flags(prev,L);
		    L=L&0XFF;
		    break;
	case 0X34 : memloc=L;
		    memloc+=H<<8;
		    data=memory[memloc];
		    prev=data;
		    data+=1;
		    flags(prev,data);
		    data=data&0XFF;
		    memory[memloc]=data;
		    break;
	//===========================DCR R==================
	case 0X3D : prev=A;
		    A=A-1;
		    flags(prev,A);
		    A=A&0XFF;
		    break;
	case 0X05 : prev=B;
		    B=B-1;
		    flags(prev,B);
		    B=B&0XFF;
		    break;
	case 0X0D : prev=C;
		    C=C-1;
		    flags(prev,C);
		    C=C&0XFF;
		    break;
	case 0X15 : prev=D;
		    D=D-1;
		    flags(prev,D);
		    D=D&0XFF;
		    break;
	case 0X1D : prev=E;
		    E=E-1;
		    flags(prev,E);
		    E=E&0XFF;
		    break;
	case 0X25 : prev=H;
		    H=H-1;
		    flags(prev,H);
		    H=H&0XFF;
		    break;
	case 0X2D : prev=L;
		    L=L-1;
		    flags(prev,L);
		    L=L&0XFF;
		    break;
	case 0X35 : memloc=L;
		    memloc+=H<<8;
		    data=memory[memloc];
		    prev=data;
		    data-=1;
		    flags(prev,data);
		    A=A&0XFF;
		    memory[memloc]=data;
		    break;
	//======================INX Rp=============
	case 0X03 : C=C+1;
		    flags(C,C);
		    if(c_flag==1)
			{
			C=C&0XFF;
			B=B+1;
			}
		    reset_flags();
		    break;
	case 0X13 : E=E+1;
		    flags(E,E);
		    if(c_flag==1)
			{
			E=E&0XFF;
			D=D+1;
			}
		    reset_flags();
		    break;
	case 0X23 : L=L+1;
		    flags(L,L);
		    if(c_flag==1)
			{
			L=L&0XFF;
			H=H+1;
			}
		    reset_flags();
		    break;
	case 0X33 : SP++;
		    break;
	//=========================DCX Rp=====================
	case 0X0B : C=C-1;
		    flags(C,C);
		    if(c_flag==1)
			{
			C=C&0XFF;
			B=B-1;
			}
		    reset_flags();
		    break;
	case 0X1B : E=E-1;
		    flags(E,E);
		    if(c_flag==1)
			{
			E=E&0XFF;
			D=D-1;
			}
		    reset_flags();
		    break;
	case 0X2B : L=L-1;
		    flags(L,L);
		    if(c_flag==1)
			{
			L=L&0XFF;
			H=H-1;
			}
		    reset_flags();
		    break;
	case 0X3B : SP--;
		    break;
       //==========================ANA R==========================
	case 0XA7 : A=A&A;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=1;
		    break;
	case 0XA0 : A=A&B;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=1;
		    break;
	case 0XA1 : A=A&C;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=1;
		    break;
	case 0XA2 : A=A&D;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=1;
		    break;
	case 0XA3 : A=A&E;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=1;
		    break;
	case 0XA4 : A=A&H;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=1;
		    break;
	case 0XA5 : A=A&L;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=1;
		    break;
	case 0XA6 : memloc=L;
		    memloc+=H<<8;
		    data=memory[memloc];
		    A=A&data;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=1;
		    break;
       //==================================ORA R===================
       case 0XB7 : A=A|A;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XB0 : A=A|B;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XB1 : A=A|C;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XB2 : A=A|D;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XB3 : A=A|E;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XB4 : A=A|H;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XB5 : A=A|L;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XB6 : memloc=L;
		    memloc+=H<<8;
		    data=memory[memloc];
		    A=A|data;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	//==========================XRA R==========================
	case 0XAF : A=A^A;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XA8 : A=A^B;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XA9 : A=A^C;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XAA : A=A^D;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XAB : A=A^E;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XAC : A=A^H;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XAD : A=A^L;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;
	case 0XAE : memloc=L;
		    memloc+=H<<8;
		    data=memory[memloc];
		    A=A^data;
		    flags(A,A);
		    c_flag=0;
		    ac_flag=0;
		    break;

	//===========================PUSH Rp=======================
	case 0XC5 :  SP--;
		     memory[SP]=B;
		     SP--;
		     memory[SP]=C;
		     break;
	case 0XD5 :  SP--;
		     memory[SP]=D;
		     SP--;
		     memory[SP]=E;
		     break;
	case 0XE5 :  SP--;
		     memory[SP]=H;
		     SP--;
		     memory[SP]=L;
		     break;
	case 0XF5 :  SP--;
		     memory[SP]=A;
		     SP--;
		     memory[SP]=PSW;
		     break;
	 //========================POP Rp=================
	case 0XC1 :  C=memory[SP];
		     SP++;
		     B=memory[SP];
		     SP++;
		     break;
	case 0XD1 :  E=memory[SP];
		     SP++;
		     D=memory[SP];
		     SP++;
		     break;
	case 0XE1 :  L=memory[SP];
		     SP++;
		     H=memory[SP];
		     SP++;
		     break;
	case 0XF1 :  PSW=memory[SP];
		     s_flag=PSW&0X80;
		     z_flag=PSW&0X40;
		     ac_flag=PSW&0X10;
		     p_flag=PSW&0X4;
		     c_flag=PSW&0X1;

		     SP++;
		     A=memory[SP];
		     SP++;
		     break;

    }

    PC++;
    }
}


void storing()
{
    memory[PC]=hexcode;
    PC++;
    storing_flag++;;
}


int conv_hex(char c1,char c2)
{
    int k=0;
    char c;
    hexcode=0;
    c=c1;
    do
    {
    switch(c)
    {
	case '0' :  hexcode+=(k%2==0)?0X00:0X00;
		    break;
	case '1' :  hexcode+=(k%2==0)?0X10:0X01;
		    break;
	case '2' :  hexcode+=(k%2==0)?0X20:0X02;
		    break;
	case '3' :  hexcode+=(k%2==0)?0X30:0X03;
		    break;
	case '4' :  hexcode+=(k%2==0)?0X40:0X04;
		    break;
	case '5' :  hexcode+=(k%2==0)?0X50:0X05;
		    break;
	case '6' :  hexcode+=(k%2==0)?0X60:0X06;
		    break;
	case '7' :  hexcode+=(k%2==0)?0X70:0X07;
		    break;
	case '8' :  hexcode+=(k%2==0)?0X80:0X08;
		    break;
	case '9' :  hexcode+=(k%2==0)?0X90:0X09;
		    break;
	case 'A' :  hexcode+=(k%2==0)?0XA0:0X0A;
		    break;
	case 'B' :  hexcode+=(k%2==0)?0XB0:0X0B;
		    break;
	case 'C' :  hexcode+=(k%2==0)?0XC0:0X0C;
		    break;
	case 'D' :  hexcode+=(k%2==0)?0XD0:0X0D;
		    break;
	case 'E' :  hexcode+=(k%2==0)?0XE0:0X0E;
		    break;
	case 'F' :  hexcode+=(k%2==0)?0XF0:0X0F;
		    break;
	default  :  return 1;
	}
	k++;
	c=c2;
    }while(k<=1);
    storing();
    return 0;
}

//======================Ckecking After Mnemonics============
int after_mnemo(int i,int j)
{
    if(strlen(prog[i])>(j+1))
	return 1;
    else
	return 0;

}

/*---------------------Breaking Mnemonics & Check Error----------------------*/
int interpreter(int i)
{
    char opcode[5]={'\0','\0','\0','\0','\0'},reg1,reg2,oprand_add[4]={0},oprand_data[2]={0};
    int j=0,k=0,err_flag=1,address,data;

    while(prog[i][j]!=' ' && prog[i][j]!='\0')
    {
	opcode[k]=prog[i][j];
	j++,k++;
	if(k>4)
	    break;
    }
    k=0;
    j++;
    //====================================Loading Data From Memory to Registers=============================
    if(strcmp(opcode,"LXI")==0)
    {

			err_flag=0;
			hexcode=0X1;
			reg1=prog[i][j];
			switch(reg1)
			{
			    case 'B' :  hexcode+=0;
					break;
			    case 'D' :  hexcode+=0x10;
					break;
			    case 'H' :  hexcode+=0x20;
					break;
			    case 'S' :  hexcode+=0x30;
					 if(prog[i][j+1]!='P')
					 err_flag=1;
					 j++;
					break;
			    default :   err_flag=1;
			}
			if(err_flag==1)
			    return(err_flag);
			storing();
			    j=j+3;
			//---------------Syntex Error Checking--------------------
			if(prog[i][j+4]!='H')
			{
			    err_flag=1;
			    return(err_flag);
			}
			while(prog[i][j]!='H')
			{
			    oprand_add[k]=prog[i][j];
			    j++;k++;
			}
			if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
			err_flag=conv_hex(oprand_add[2],oprand_add[3]);
			if(err_flag==1)
			    return(err_flag);
			err_flag=conv_hex(oprand_add[0],oprand_add[1]);
			if(err_flag==1)
			    return(err_flag);
    }
    else if(strcmp(opcode,"LDA")==0)
    {
	err_flag=0;
	hexcode=0X3A;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);

    }
    else if(strcmp(opcode,"STA")==0)
    {
	err_flag=0;
	hexcode=0X32;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    else if(strcmp(opcode,"LHLD")==0)
    {
	err_flag=0;
	hexcode=0X2A;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);

    }
    else if(strcmp(opcode,"SHLD")==0)
    {
	err_flag=0;
	hexcode=0X22;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);

    }
    //=========================Move Data to Register==============
    else if(strcmp(opcode,"MOV")==0)
    {
		err_flag=0;
		reg1=prog[i][j];
		j+=3;
		reg2=prog[i][j];
		switch(reg1)
		{
		    case 'A' : hexcode=0X78;
				break;
		    case 'B' : hexcode=0X40;
				break;
		    case 'C' : hexcode=0X48;
				break;
		    case 'D' : hexcode=0X50;
				break;
		    case 'E' : hexcode=0X58;
				break;
		    case 'H' : hexcode=0X60;
				break;
		    case 'L' : hexcode=0X68;
				break;
		    case 'M' : hexcode=0X70;
				break;
		    default : err_flag=1;
		}
		if(err_flag==1)
			    return(err_flag);
		switch(reg2)
		{
		    case 'A' : hexcode+=0X07;
				break;
		    case 'B' : hexcode+=0X00;
				break;
		    case 'C' : hexcode+=0X01;
				break;
		    case 'D' : hexcode+=0X02;
				break;
		    case 'E' : hexcode+=0X03;
				break;
		    case 'H' : hexcode+=0X04;
				break;
		    case 'L' : hexcode+=0X05;
				break;
		    case 'M' : hexcode+=0X06;
				break;
		    default : err_flag=1;
		}
		if(err_flag==1)
			    return(err_flag);
		storing();
    }
    else if(strcmp(opcode,"XCHG")==0)
    {
	err_flag=0;
	hexcode=0XEB;
	storing();
	j-=2;
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    else if(strcmp(opcode,"MVI")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	j+=3;
	hexcode=0X6;
	switch(reg1)
	{
		    case 'A' : hexcode+=0X38;
				break;
		    case 'B' : hexcode+=0X00;
				break;
		    case 'C' : hexcode+=0X08;
				break;
		    case 'D' : hexcode+=0X10;
				break;
		    case 'E' : hexcode+=0X18;
				break;
		    case 'H' : hexcode+=0X20;
				break;
		    case 'L' : hexcode+=0X28;
				break;
		    case 'M' : hexcode+=0X30;
				break;
		    default : err_flag=1;
	}
	if(err_flag==1)
			    return(err_flag);
	storing();
	if(prog[i][j+2]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_data[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_data[0],oprand_data[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    //======================ALU Operations==========================
    else if(strcmp(opcode,"ADD")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0X80;
	switch(reg1)
		{
		    case 'A' : hexcode+=0X07;
				break;
		    case 'B' : hexcode+=0X00;
				break;
		    case 'C' : hexcode+=0X01;
				break;
		    case 'D' : hexcode+=0X02;
				break;
		    case 'E' : hexcode+=0X03;
				break;
		    case 'H' : hexcode+=0X04;
				break;
		    case 'L' : hexcode+=0X05;
				break;
		    case 'M' : hexcode+=0X06;
				break;
		    default : err_flag=1;
		}
		if(err_flag==1)
			    return(err_flag);
		storing();
		if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    else if(strcmp(opcode,"SUB")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0X90;
	switch(reg1)
		{
		    case 'A' : hexcode+=0X07;
				break;
		    case 'B' : hexcode+=0X00;
				break;
		    case 'C' : hexcode+=0X01;
				break;
		    case 'D' : hexcode+=0X02;
				break;
		    case 'E' : hexcode+=0X03;
				break;
		    case 'H' : hexcode+=0X04;
				break;
		    case 'L' : hexcode+=0X05;
				break;
		    case 'M' : hexcode+=0X06;
				break;
		    default : err_flag=1;
		}
		if(err_flag==1)
			    return(err_flag);
		storing();
		if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    else if(strcmp(opcode,"CMP")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0XB8;
	switch(reg1)
		{
		    case 'A' : hexcode+=0X07;
				break;
		    case 'B' : hexcode+=0X00;
				break;
		    case 'C' : hexcode+=0X01;
				break;
		    case 'D' : hexcode+=0X02;
				break;
		    case 'E' : hexcode+=0X03;
				break;
		    case 'H' : hexcode+=0X04;
				break;
		    case 'L' : hexcode+=0X05;
				break;
		    case 'M' : hexcode+=0X06;
				break;
		    default : err_flag=1;
		}
		if(err_flag==1)
			    return(err_flag);
		storing();
		if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    else if(strcmp(opcode,"DAD")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0X9;
       switch(reg1)
			{
			    case 'B' :  hexcode+=0X00;
					break;
			    case 'D' :  hexcode+=0x10;
					break;
			    case 'H' :  hexcode+=0x20;
					break;
			    case 'S' :  hexcode+=0x30;
					if(prog[i][j+1]!='P')
					err_flag=1;
					j++;
					break;
			    default :   err_flag=1;
			}
	if(err_flag==1)
			return(err_flag);
	storing();
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    //=====================Increament and Decreament Operations=============
    else if(strcmp(opcode,"INR")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0X4;
	switch(reg1)
	{
		    case 'A' : hexcode+=0X38;
				break;
		    case 'B' : hexcode+=0X00;
				break;
		    case 'C' : hexcode+=0X08;
				break;
		    case 'D' : hexcode+=0X10;
				break;
		    case 'E' : hexcode+=0X18;
				break;
		    case 'H' : hexcode+=0X20;
				break;
		    case 'L' : hexcode+=0X28;
				break;
		    case 'M' : hexcode+=0X30;
				break;
		    default : err_flag=1;
	}
	if(err_flag==1)
			return(err_flag);
	storing();
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    else if(strcmp(opcode,"DCR")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0X5;
	switch(reg1)
	{
		    case 'A' : hexcode+=0X38;
				break;
		    case 'B' : hexcode+=0X00;
				break;
		    case 'C' : hexcode+=0X08;
				break;
		    case 'D' : hexcode+=0X10;
				break;
		    case 'E' : hexcode+=0X18;
				break;
		    case 'H' : hexcode+=0X20;
				break;
		    case 'L' : hexcode+=0X28;
				break;
		    case 'M' : hexcode+=0X30;
				break;
		    default : err_flag=1;
	}
	if(err_flag==1)
			return(err_flag);
	storing();
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    else if(strcmp(opcode,"INX")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0X3;
       switch(reg1)
			{
			    case 'B' :  hexcode+=0;
					break;
			    case 'D' :  hexcode+=0x10;
					break;
			    case 'H' :  hexcode+=0x20;
					break;
			    case 'S' :  hexcode+=0x30;
					if(prog[i][j+1]!='P')
					err_flag=1;
					j++;
					break;
			    default :   err_flag=1;
			}
	if(err_flag==1)
			return(err_flag);
	storing();
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    else if(strcmp(opcode,"DCX")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0XB;
       switch(reg1)
			{
			    case 'B' :  hexcode+=0;
					break;
			    case 'D' :  hexcode+=0x10;
					break;
			    case 'H' :  hexcode+=0x20;
					break;
			    case 'S' :  hexcode+=0x30;
					if(prog[i][j+1]!='P')
					err_flag=1;
					j++;
					break;
			    default :   err_flag=1;
			}
	if(err_flag==1)
			return(err_flag);
	storing();
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    //+==========================Logical Operations====================
    else if(strcmp(opcode,"ANA")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0XA0;
	switch(reg1)
	{
		    case 'A' : hexcode+=0X7;
				break;
		    case 'B' : hexcode+=0X0;
				break;
		    case 'C' : hexcode+=0X1;
				break;
		    case 'D' : hexcode+=0X2;
				break;
		    case 'E' : hexcode+=0X3;
				break;
		    case 'H' : hexcode+=0X4;
				break;
		    case 'L' : hexcode+=0X5;
				break;
		    case 'M' : hexcode+=0X6;
				break;
		    default : err_flag=1;
	}
	if(err_flag==1)
			return(err_flag);
	storing();
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    else if(strcmp(opcode,"ORA")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0XB0;
	switch(reg1)
	{
		    case 'A' : hexcode+=0X7;
				break;
		    case 'B' : hexcode+=0X0;
				break;
		    case 'C' : hexcode+=0X1;
				break;
		    case 'D' : hexcode+=0X2;
				break;
		    case 'E' : hexcode+=0X3;
				break;
		    case 'H' : hexcode+=0X4;
				break;
		    case 'L' : hexcode+=0X5;
				break;
		    case 'M' : hexcode+=0X6;
				break;
		    default : err_flag=1;
	}
	if(err_flag==1)
			return(err_flag);
	storing();
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
     else if(strcmp(opcode,"XRA")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0XA8;
	switch(reg1)
	{
		    case 'A' : hexcode+=0X7;
				break;
		    case 'B' : hexcode+=0X0;
				break;
		    case 'C' : hexcode+=0X1;
				break;
		    case 'D' : hexcode+=0X2;
				break;
		    case 'E' : hexcode+=0X3;
				break;
		    case 'H' : hexcode+=0X4;
				break;
		    case 'L' : hexcode+=0X5;
				break;
		    case 'M' : hexcode+=0X6;
				break;
		    default : err_flag=1;
	}
	if(err_flag==1)
			return(err_flag);
	storing();
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    //===========================PUSH POP Operation===============
     else if(strcmp(opcode,"PUSH")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0XC5;
	switch(reg1)
		{
		    case 'B' : hexcode+=0X0;
				break;
		    case 'D' : hexcode+=0X10;
				break;
		    case 'H' : hexcode+=0X20;
				break;
		    case 'P' : hexcode+=0X30;
			       if(prog[i][j+1]!='S' || prog[i][j+2]!='W')
				   err_flag=1;
				j+=2;
				break;
		    default : err_flag=1;
		}
		if(err_flag==1)
			    return(err_flag);
		storing();
		if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
      else if(strcmp(opcode,"POP")==0)
    {
	err_flag=0;
	reg1=prog[i][j];
	hexcode=0XC1;
	switch(reg1)
		{
		    case 'B' : hexcode+=0X0;
				break;
		    case 'D' : hexcode+=0X10;

				break;
		    case 'H' : hexcode+=0X20;
				break;
		    case 'P' : hexcode+=0X30;
				if(prog[i][j+1]!='S' || prog[i][j+2]!='W')
				   err_flag=1;
				j+=2;
				break;
		    default : err_flag=1;
		}
		if(err_flag==1)
			    return(err_flag);
		storing();
		if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
    }
    //====================Jump Operations=============================
    else if(strcmp(opcode,"JC")==0)
    {
	err_flag=0;
	hexcode=0XDA;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    else if(strcmp(opcode,"JNC")==0)
    {
	err_flag=0;
	hexcode=0XD2;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    else if(strcmp(opcode,"JM")==0)
    {
	err_flag=0;
	hexcode=0XFA;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    else if(strcmp(opcode,"JMP")==0)
    {
	err_flag=0;
	hexcode=0XC3;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    else if(strcmp(opcode,"JNZ")==0)
    {
	err_flag=0;
	hexcode=0XC2;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    else if(strcmp(opcode,"JP")==0)
    {
	err_flag=0;
	hexcode=0XF2;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    else if(strcmp(opcode,"JPE")==0)
    {
	err_flag=0;
	hexcode=0XEA;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    else if(strcmp(opcode,"JPO")==0)
    {
	err_flag=0;
	hexcode=0XE2;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    else if(strcmp(opcode,"JZ")==0)
    {
	err_flag=0;
	hexcode=0XCA;
	storing();
	if(prog[i][j+4]!='H')
	{
	    err_flag=1;
	    return(err_flag);
	}
	while(prog[i][j]!='H')
	{
		oprand_add[k]=prog[i][j];
		k++;j++;
	}
	if(after_mnemo(i,j))
			{
			    err_flag=1;
			    return(err_flag);
			}
	err_flag=conv_hex(oprand_add[2],oprand_add[3]);
	if(err_flag==1)
			    return(err_flag);
	err_flag=conv_hex(oprand_add[0],oprand_add[1]);
	if(err_flag==1)
			    return(err_flag);
    }
    return(err_flag);
}
/*-----------------------------------------------------------------------------------------------------------*/


/*--------------------It will take input in form of Mnemonics-----------------------------------------------*/
void input()
{

    int i=0,check=0;
    char curinst[0XF];
    while(1)
    {
	storing_flag=0;
	printf("%X\t",PC);
	fflush(stdin);
	gets(curinst);
	strcpy(prog[i],strupr(curinst));
	if(strlen(curinst)>0XF)
	{
	   check=1;
	   goto loc1;
	}

	if(strcmp(strupr(curinst),"HLT")==0)
	   {
		hexcode=0X76;
		storing();
		break;
	   }

	check=interpreter(i);
 loc1 : if(check==1)
	{
	    printf("\nSyntex Error in Mnemonics. Enter Again..\n");
	    PC=PC-storing_flag;
	}
	else
	i++;
    }
    printf("Program is Successfully Entered.");
    getch();
}
/*------------------------------------------------------------------------------------------------------------*/


/*-----------------------------Main-------------------------------------------------------*/
int main()
{
    int gd=DETECT,gm;
    char ch;
    int i_p;
	  initgraph(&gd,&gm,"");
    while(1)
    {
	clearviewport();
	fflush(stdin);
	gotoxy(1,1);
	printf("1.Enter Program\n2.Enter Data at Memory Location\n3.View Memory Location\n4.Run Program\n5.Run Step By step\n6.Reset PSW\n7.Exit\nEnter choice : ");
	ch=getche();
	switch(ch)
	{
	case '1' :  printf("\nEnter PC = ");
		    i_p=scanf("%X",&PC);
		    if(PC>=0 && PC<=0X4FFF && i_p)
		    {
		    printf("\nEnter Program :\n");
		    input();
		    }
		    else
		    {
		     printf("Invalid Input..!!");
		     getch();
		    }
		    break;
	case '2' :  printf("\nEnter Memory Location = ");
		    i_p=scanf("%X",&PC);
		    if(PC>=0 && PC<=0X4FFF && i_p)
		    {
		    do
		    {
			fflush(stdin);
			printf("\n%X = ",PC);
			i_p=scanf("%X",&hexcode);
			if(hexcode>=0 && hexcode<=0XFF && i_p)
			{
			storing();
			printf("Next[y/n] : ");
			ch=getche();
			}
			else
			{
			 printf("\nInvalid Input..!!");
			 getch();
			 ch='y';
			}
		    }while(ch=='y' || ch=='Y');
		    }
		    else
		    {
		     printf("Invalid Input..!!");
		     getch();
		    }

		    break;
	case '3' :  printf("\nEnter Memory Location = ");
		    i_p=scanf("%X",&PC);
		     if(PC>=0 && PC<=0X4FFF && i_p)
		    {
		      do
		    {
		       printf("\n%X\t%X",PC,memory[PC]);
		       PC++;
		    }while(getche()!=27);
		    }
		    else
		    {
		     printf("Invalid Input..!!");
		     getch();
		    }

		    break;
	case '4' :  printf("\nEnter PC = ");
		    i_p=scanf("%X",&PC);
		    if(PC>=0 && PC<=0X4FFF && i_p)
		    {
		    run(0);
		    display();
		    }
		    else
		    {
		     printf("Invalid Input..!!");
		     getch();
		    }
		    break;
	case '5' :  mnxptr=0;
		    printf("\nEnter PC = ");
		    i_p=scanf("%X",&PC);
		     if(PC>=0 && PC<=0X4FFF && i_p)
		    {
		    run(1);
		    }
		    else
		    {
		     printf("Invalid Input..!!");
		     getch();
		    }
		    break;
	case '6' :  reset_regs();
		    reset_flags();
		    printf("PSW has been reset...");
		    getch();
		    break;
	case '7' : exit(1);
	default  : printf("\nWrong Choice ... ");
		   getch();
	}
    }

}
