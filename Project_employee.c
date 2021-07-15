//A menu driven program in C using Graphics and File system for management of Personnel records.
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>

struct Employee
{
    long int empid;
    char empnm[1000];
    int age;
    float sal;
    char phone[10]; 
};
typedef struct Employee emp;
struct old_employee
{
    long int empid;
    char empnm[1000];
    int age;
    float sal;
    char phone[10]; 
    int date,month,year;
    int resdate,resmon,resyear;


};
typedef struct old_employee exemp;

void insert(FILE *fp,int *n)
    {
        emp e1;
        char another,ch;
        do
        {
            clrscr();
            fseek(fp,0,SEEK_END);
            another='Y';
            gotoxy(25,3);
            cprintf("ADD EMPLOYEE RECORD");
            gotoxy(25,6);
            cprintf("1.ENTER EMPLOYEE ID: ");
            scanf("%ld",&(e1.empid));
            gotoxy(25,7);
            cprintf("2.ENTER NAME OF EMPLOYEE: ");
            scanf("%s",e1.empnm);
            gotoxy(25,8);
            cprintf("3. ENTER AGE OF EMPLOYEE: ");
            scanf("%d",&(e1.age));
            gotoxy(25,9);
            cprintf("4. ENTER SALARY OF EMPLOYEE: ");
            scanf("%f",&(e1.sal));
            gotoxy(25,10);
            cprintf("5.ENTER PHONE NO OF EMPLOYEE:");
            scanf("%s",e1.phone);
            gotoxy(28,14);
            textcolor(MAGENTA );
            cprintf("SAVE CHANGE (y/n)?");
            ch=getch();
            if(ch=='y'||ch=='Y')  
            {
                fwrite(&e1,sizeof(e1),1,fp);//Details will be updated in  file
                (*n)++;
                fflush(stdin);
            }
            gotoxy(28,15);
            cprintf("ADD ANOTHER EMPLOYEE(Y/N)?");
            fflush(stdin);      //.  the output buffer and move the buffered data to console (in case of stdout) 
            another=getch();
            fflush(stdin);//clear the output buffer of the stream.
            
          }while(another=='Y'|| another=='y');
          getch();
}
void insert_old(FILE *d,int *cnt)
    {
       
        exemp e1; 
        char another,ch;
        
        do
        {
            clrscr();
            fseek(d,0,SEEK_END);
            another='Y';
            gotoxy(25,3);
            cprintf("ADD EXEMPLOYEE RECORD");
            gotoxy(25,6);
            cprintf("1.ENTER EMPLOYEE ID: ");
            scanf("%ld",&(e1.empid));
            gotoxy(25,7);
            cprintf("2.ENTER NAME OF EMPLOYEE: ");
            scanf("%s",e1.empnm);
            gotoxy(25,8);
            cprintf("3. ENTER AGE OF EMPLOYEE: ");
            scanf("%d",&(e1.age));
            gotoxy(25,9);
            cprintf("4. ENTER SALARY OF EMPLOYEE: ");
            scanf("%f",&(e1.sal));
            gotoxy(25,10);
            cprintf("5.ENTER PHONE NO OF EMPLOYEE:");
            scanf("%s",e1.phone);
            gotoxy(28,11);
            cprintf("6.ENTER DATE OF JOINING ");
            scanf("%d",&(e1.date));
            gotoxy(28,12);
            cprintf("7.ENTER MONTH OF JOINING ");
            scanf("%d",&(e1.month));
            gotoxy(28,13);
            cprintf("8.ENTER YEAR OF JOINING ");
            scanf("%d",&(e1.year));
            gotoxy(28,14);
            cprintf("9.ENTER DATE OF RESIGNING ");
            scanf("%d",&(e1.resdate));
            gotoxy(28,15);
            cprintf("10.ENTER MONTH OF RESIGNING ");
            scanf("%d",&(e1.resmon));
             gotoxy(28,16);
            cprintf("11.ENTER YEAR OF RESIGNING ");
            scanf("%d",&(e1.resyear));
             gotoxy(28,17);
            textcolor(MAGENTA );
            cprintf("SAVE CHANGE (y/n)?");
            ch=getch();
            if(ch=='y'||ch=='Y')  
            {
                fwrite(&e1,sizeof(e1),1,d);//Details will be updated in  file
                (*cnt)++;
                fflush(stdin);
            }
            gotoxy(28,22);
            cprintf("ADD ANOTHER EMPLOYEE(Y/N)?");
            fflush(stdin);      //.  the output buffer and move the buffered data to console (in case of stdout) 
            another=getch();
            fflush(stdin);//clear the output buffer of the stream.
            
          }while(another=='Y'|| another=='y');
          getch();
}
void delete_record(FILE *fp,int *n)
{
    int i,flag=0;
    long int employeeId;
    FILE *temp;
    emp e1;
    char another,ch;
    do
    {
        clrscr();
        fseek(fp,0,SEEK_SET);
        rewind(fp);
        textcolor(RED);
        gotoxy(1,1);
        cprintf("DELETE EMPLOYEE RECORD");
        textcolor(GREEN);
        gotoxy(2,2);
        cprintf("ENTER EMPLOYEE ID TO BE DELETED:");
        scanf("%ld",&employeeId);
        while(fread(&e1,sizeof(e1),1,fp)==1)
        {
            if(e1.empid==employeeId)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            (*n)--;
            temp=fopen("tempFileName","wb");
            rewind(fp);
            while(fread(&e1,sizeof(e1),1,fp)==1)
            {
                if(e1.empid!=employeeId)//Copying contents of Emp.txt into temp file except the matched empid data
                    fwrite(&e1,sizeof(e1),1,temp);
            }
            fclose(fp);
            fclose(temp);
            remove("employee.txt");
            rename("tempFileName","employee.txt");
            fp=fopen("employee.txt","rb+");
            gotoxy(6,8);
            cprintf("SUCCESSFULLY DELETED!!!!!");
        }
        else
        {
            gotoxy(2,6);
            cprintf("EMPLOYEE NOT FOUND!!!!!");
        }
        gotoxy(10,20);
        textcolor(RED+BLINK);
        cprintf("DELETE ANOTHER EMPLOYEE(Y/N)?");
        fflush(stdin);
        another=getch();
        fflush(stdin);
        textcolor(WHITE);
        
    }while(another=='Y'|| another=='y');
    getch();
}
void sort(FILE *fp,int n)
{
    emp e1[10];
    emp e2; 
    int i=0,j=0,k=0;
    fseek(fp,0,SEEK_SET);
    fread(&e1,sizeof(e1),n,fp);
    
    for(i=0;i<n-1;i++)
    {
        j=i;
        for(k=i+1;k<n;k++)
            if(e1[k].empid<e1[j].empid)
            {
                j=k; // Finding the min element index
            }
                e2=e1[i]; 
                e1[i]=e1[j];
                e1[j]=e2;   
    }
    rewind(fp);

    fwrite(e1,sizeof(e1),1,fp);//This writes whole array of employee into file
    
}
char first()
{
    char i; int gdriver=DETECT, gmod;
    initgraph(&gdriver,&gmod,"c:\\tc\\bgi");
    setbkcolor(CYAN);
    setcolor(MAGENTA);
    settextstyle(7,0,2);
    outtextxy(130,45,"DISPLAY");
    settextstyle(7,0,3);
    setcolor(YELLOW);
    outtextxy(260,95,"MENU");
    settextstyle(0,0,0);
    setcolor(MAGENTA);
    outtextxy(200,145,"1.DISPLAY EXISTING EMPLOYEE RECORD");
    outtextxy(200,170,"2.DISPLAY OLD EMPLOYEE RECORD");
    outtextxy(200,195,"3.DISPLAY BASED ON AGE");
    outtextxy(200,220,"4.EXIT");
   
    setcolor(RED+BLINK);
    outtextxy(200,360,"ENTER YOUR CHOICE: ");
    i=getch();
    restorecrtmode();//Switch between modes
    return(i);
}


void display(FILE *fp,int n)
{
    emp e1;
    int i=0,j=0;
    sort(fp,n);
    
    fseek(fp,0,SEEK_SET);
    gotoxy(1,1);
    cprintf("LIST OF EMPLOYEE RECORD");
    gotoxy(1,2);
    cprintf("EMP ID");
    gotoxy(14,2);
    cprintf("NAME");
    gotoxy(27,2);
    cprintf("AGE");
    gotoxy(40,2);
    cprintf("SALARY");
    gotoxy(53,2);
    cprintf("PHONE");
    for(i=1;i<=80;i++)
    {
        gotoxy(i,3);
        cprintf("-");   //Construct table
    }
    i=4;

    for(j=0;j<n;j++)
    {
        if(fread(&e1,sizeof(e1),1,fp)==1)
        {
        gotoxy(1,i);
        cprintf("%ld",e1.empid);
        gotoxy(14,i);
        cprintf("%s",e1.empnm);
        gotoxy(27,i);
        cprintf("%d",e1.age);
        gotoxy(40,i);
        cprintf("%f",e1.sal);
        gotoxy(53,i);
        cprintf("%s",e1.phone);
        i++;
        }
    }
    getch();
}
void display_old(FILE *d,int cnt)
{
     exemp e1;  int i=0,j=0; 
    fseek(d,0,SEEK_SET);
    gotoxy(1,1);
    cprintf("LIST OF EMPLOYEE RECORD");
    gotoxy(1,2);
    cprintf("EMP ID");
    gotoxy(10,2);
    cprintf("NAME");
    gotoxy(20,2);
    cprintf("AGE");
    gotoxy(30,2);
    cprintf("SALARY");
    gotoxy(40,2);
    cprintf("PHONE");
    gotoxy(50,2);
    cprintf("DOJ");
    gotoxy(60,2);
    cprintf("DOR");
    for(i=1;i<=80;i++)
    {
        gotoxy(i,3);
        cprintf("-");   //Construct table
    }
    i=4;
    
     for(j=0;j<cnt;j++)
    {
        if(fread(&e1,sizeof(e1),1,d)==1)
         {   gotoxy(1,i);
            cprintf("%ld",e1.empid);
            gotoxy(10,i);
            cprintf("%s",e1.empnm);
            gotoxy(20,i);
            cprintf("%d",e1.age);
            gotoxy(30,i);
            cprintf("%f",e1.sal);
            gotoxy(40,i);
            cprintf("%s",e1.phone);
            gotoxy(50,i);
            cprintf("%d-%d-%d",e1.date,e1.month,e1.year);
            gotoxy(60,i);
            cprintf("%d-%d-%d",e1.resdate,e1.resmon,e1.resyear);
            i++;}
    }
    getch();
}
void display_age(FILE *fp,int n)
{
    int flag=0;int i=0,j=0;
    int Age;
    emp e1;
    char another,ch;
    do
    {
        clrscr();
        fseek(fp,0,SEEK_SET);
        gotoxy(1,1);
        textcolor(RED);
        cprintf("DISPLAY EMPLOYEE RECORD BASED ON AGE");
        gotoxy(5,2);
        textcolor(GREEN);
        cprintf("ENTER THE AGE GROUP  : ");
        scanf("%d",&Age);
        i=4;
        for(j=0;j<n;j++)
        {
            if((fread(&e1,sizeof(e1),1,fp)==1)&&((e1.age)<=Age))
             {   gotoxy(1,i);
                cprintf("empid=%ld",e1.empid);
                gotoxy(10,i);
                cprintf("empnm=%s",e1.empnm);
                gotoxy(25,i);
                cprintf("age=%d",e1.age);
                gotoxy(35,i);
                cprintf("salary=%f",e1.sal);
                gotoxy(50,i);
                cprintf("phone=%s",e1.phone);
                
                i++;
                 
             }
   
            flag=1;
        }
        
        if(flag==0)
        {
            gotoxy(10,8);
            cprintf("EMPLOYEE NOT FOUND!!!!!");
        }
        gotoxy(70,15);
        textcolor(RED+BLINK);
        cprintf("DISPLAY ANOTHER AGE GROUP(Y/N)?");
        fflush(stdin);
        another=getch();
        fflush(stdin);
        textcolor(WHITE);
    }while(another=='Y'|| another=='y');
    getch();
}

void display_record(FILE *fp,int n,FILE *d,int cnt)
{
    char ch,another;
    do 
    {
        ch=first();
        switch(ch)
        {
            case '1':display(fp,n);
                        break;
                        
            case '2':display_old(d,cnt);
                        break;

            case '3':display_age(fp,n);
                    break;

            default: return;
                        
        
        }
        cprintf("Would you view the display menu again\n");
        fflush(stdin);
        another=getch();
        fflush(stdin);
        textcolor(WHITE);
    }while(another=='Y'||another=='y');
    getch();
}
char menu()
{
    char i; int gdriver=DETECT, gmod;
    initgraph(&gdriver,&gmod,"c:\\tc\\bgi");
    setbkcolor(CYAN);
    setcolor(MAGENTA);
    settextstyle(7,0,2);
    outtextxy(130,45,"INSERT");
    settextstyle(7,0,3);
    setcolor(YELLOW);
    outtextxy(260,95,"MENU");
    settextstyle(0,0,0);
    setcolor(MAGENTA);
    outtextxy(200,145,"1.INSERT EXISTING EMPLOYEES");
    outtextxy(200,170,"2.INSERT OLD EMPLOYEES");
    outtextxy(200,195,"3.EXIT");
   
    setcolor(RED+BLINK);
    outtextxy(200,360,"ENTER YOUR CHOICE: ");
    i=getch();
    restorecrtmode();//Switch between modes
    return(i);
}
void insert_record(FILE *fp,int *n,FILE *d,int *cnt)
{
    char ch,another;
    do 
    {
        ch=menu();
        switch(ch)
        {
            case '1':insert(fp,n);
                        break;
                        
            case '2':insert_old(d,cnt);
                        break;
                
            default: return;
                        
        
        }
        cprintf("Would you view the insert menu again\n");
        fflush(stdin);
        another=getch();
        fflush(stdin);
        textcolor(WHITE);
    }while(another=='Y'||another=='y');
    getch();
}
void search_id(FILE *fp)
{
    int i,flag=0;
    long int employeeId;
    emp e1;
    char another,ch;
    do
    {
        clrscr();
        fseek(fp,0,SEEK_SET);
        gotoxy(1,1);
        textcolor(RED);
        cprintf("SEARCH EMPLOYEE RECORD");
        gotoxy(5,2);
        textcolor(GREEN);
        cprintf("ENTER EMPLOYEE ID: ");
        scanf("%ld",&employeeId);
        while(fread(&e1,sizeof(e1),1,fp)==1)
        {
            if(e1.empid==employeeId)
            {
                flag=1;
                break;
            }
        }
        if(flag == 1)
        {
            textcolor(RED);
            gotoxy(4,4);
            cprintf("RECORD OF EMPLOYEE");
            textcolor(GREEN);
            gotoxy(4,5);
            
            gotoxy(4,6);
            cprintf("EMPLOYEE ID :");
            cprintf("%ld",e1.empid);
            gotoxy(4,7);
            cprintf("EMPLOYEE NAME :");
            cprintf("%s",e1.empnm);
            gotoxy(4,8);
            cprintf("EMPLOYEE AGE :");
            cprintf("%d",e1.age);
            gotoxy(4,9);
            cprintf("EMPLOYEE SALARY :");
            cprintf("%f",e1.sal);
            gotoxy(4,10);
            cprintf("Phone number :");
            cprintf("%s",e1.phone);

        }
        else
        {
            gotoxy(10,8);
            cprintf("EMPLOYEE NOT FOUND!!!!!");
        }
        gotoxy(25,15);
        textcolor(RED+BLINK);
        cprintf("SEARCH ANOTHER EMPLOYEE(Y/N)?");
        fflush(stdin);
        another=getch();
        fflush(stdin);
        textcolor(WHITE);
    }while(another=='Y'|| another=='y');
    getch();
}
void search_name(FILE *fp)
{
    int i,flag=0;
    char Empname[1000];
    emp e1;
    char another,ch;
    do
    {
        clrscr();
        fseek(fp,0,SEEK_SET);
        gotoxy(1,1);
        textcolor(RED);
        cprintf("SEARCH EMPLOYEE RECORD");
        gotoxy(5,2);
        textcolor(GREEN);
        cprintf("ENTER EMPLOYEE NAME: ");
        scanf("%s",Empname);
        while(fread(&e1,sizeof(e1),1,fp)==1)
        {
            if(strcmp(e1.empnm,Empname)==0)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            textcolor(RED);
            gotoxy(4,4);
            cprintf("RECORD OF EMPLOYEE");
            textcolor(GREEN);
            gotoxy(4,5);
            
            gotoxy(4,6);
            cprintf("EMPLOYEE ID :");
            cprintf("%ld",e1.empid);
            gotoxy(4,7);
            cprintf("EMPLOYEE NAME :");
            cprintf("%s",e1.empnm);
            gotoxy(4,8);
            cprintf("EMPLOYEE AGE :");
            cprintf("%d",e1.age);
            gotoxy(4,9);
            cprintf("EMPLOYEE SALARY :");
            cprintf("%f",e1.sal);
            gotoxy(4,10);
            cprintf("Phone number :");
            cprintf("%s",e1.phone);

        }
        else
        {
            gotoxy(10,8);
            cprintf("EMPLOYEE NOT FOUND!!!!!");
        }
        gotoxy(25,15);
        textcolor(RED+BLINK);
        cprintf("SEARCH ANOTHER EMPLOYEE(Y/N)?");
        fflush(stdin);
        another=getch();
        fflush(stdin);
        textcolor(WHITE);
    }while(another=='Y'|| another=='y');
    getch();
}
char file()
{
    char i; int gdriver=DETECT, gmod;
    initgraph(&gdriver,&gmod,"c:\\tc\\bgi");
    setbkcolor(CYAN);
    setcolor(MAGENTA);
    settextstyle(7,0,2);
    outtextxy(130,45,"PERSONNEL MANAGEMENT SYSTEM");
    settextstyle(7,0,3);
    setcolor(YELLOW);
    outtextxy(260,95,"MENU");
    settextstyle(0,0,0);
    setcolor(MAGENTA);
    outtextxy(200,145,"1.INSERT EMPLOYEE RECORD.");
    outtextxy(200,170,"2.DISPLAY EMPLOYEE RECORD");
    outtextxy(200,195,"3.SEARCH EMPLOYEE RECORD");
    outtextxy(200,220,"4.ALTER THE EMPLOYEE RECORD");
    outtextxy(200,245,"5.DELETE EMPLOYEE RECORD");
    outtextxy(200,270,"6.EXIT.");
    setcolor(RED+BLINK);
    outtextxy(200,360,"ENTER YOUR CHOICE: ");
    i=getch();
    restorecrtmode();//Switch between modes
    return(i);
}
void alter_record(FILE *fp)
{
    emp e1;
    int i, flag=0,cnt=0;
    long int id;
    char another,ch;
    do
    {
        clrscr();
        fseek(fp,0,SEEK_SET);
        rewind(fp);
        gotoxy(1,1);
        textcolor(RED);
        cprintf("MODIFY EMPLOYEE RECORD");
        textcolor(GREEN);
        gotoxy(2,2);
        cprintf("ENTER EMPLOYEE ID TO BE MODIFIED:");
        scanf("%ld",&id);
        while(fread(&e1,sizeof(e1),1,fp)==1)
        {
            if(e1.empid==id)
            {
                flag=1;
                break;
            }
            cnt++;
        }
        if(flag==1)
        {
            gotoxy(5,3);
            cprintf("Employee id to be modified:");
            scanf("%ld",&(e1.empid)); //All the emp data will be overwritten
            gotoxy(5,4);
            cprintf("Employee name to be modified:");
           scanf("%s",e1.empnm);
            gotoxy(5,5);
            cprintf("Employee age to be modified:");
            scanf("%d",&e1.age);
            gotoxy(5,6);
            cprintf("Employee sal to be modified:");
            scanf("%f",&e1.sal);
            gotoxy(5,7);
            cprintf("Employee phone no to be modified:");
            scanf("%s",e1.phone);
            fseek(fp,sizeof(e1)*(cnt),SEEK_SET);//
            gotoxy(10,9);

            if(fwrite(&e1,sizeof(e1),1,fp)==1)
                cprintf("THE RECORD HAS BEEN MODIFIED!!!!!");
            else
                cprintf("ERROR DURING MODIFICATION!!!!!");
        
        }
        else
        {
                gotoxy(10,9);
                cprintf("EMPLOYEE NOT FOUND!!!!!");
        }
        gotoxy(10,11);
        textcolor(RED+BLINK);
        cprintf("MODIFY ANOTHER EMPLOYEE(Y/N)?");
        fflush(stdin);
        another=getch();
        fflush(stdin);
        textcolor(WHITE);
        }while(another=='Y'||another=='y');
        getch();
}
char list()
{
    char i; 
    int gdriver=DETECT, gmod;
    initgraph(&gdriver,&gmod,"c:\\tc\\bgi");
    setbkcolor(CYAN);
    setcolor(MAGENTA);
    outtextxy(130,45,"SEARCH");
    settextstyle(7,0,3);
    setcolor(YELLOW);
    outtextxy(260,95,"MENU");
    settextstyle(0,0,0);
    setcolor(MAGENTA);
    outtextxy(200,145,"1.SEARCH BASED ON EMPLOYEE ID.");
    outtextxy(200,170,"2.SEARCH BASED ON  EMPLOYEE NAME");
    outtextxy(200,195,"3.EXIT");
    setcolor(RED+BLINK);
    outtextxy(200,360,"ENTER YOUR CHOICE: ");
    i=getch();
    restorecrtmode();//Switch between modes
    return(i);
}
void search_record(FILE *fp)
{
    char ch,another;
    do 
    {
        ch=list();
        switch(ch)
        {
            case '1':search_id(fp);
                        break;
                        
            case '2':search_name(fp);
                        break;
                        
            default: return;
                        
        
        }
        cprintf("SEARCH ANOTHER EMPLOYEE(Y/N)?");
        fflush(stdin);
        another=getch();
        fflush(stdin);
        textcolor(WHITE);
    }while(another=='Y'||another=='y');
    getch();
}
           
void main()
{
   int gd=DETECT,gm,x,y; char i,ch='a';   
   // int gdriver=DETECT, gmod;
    FILE *fp,*d;int n=0; int cnt=0;
    initgraph(&gd,&gm,"c:\\turboc3\\bgi");//Initiate GUI
    clrscr();
    fp=fopen("employee.txt","rb+");
    if(fp==NULL)
    {
        fp=fopen("employee.txt","wb+");
        if(fp==NULL)
        {
            cprintf("File do not exist\n");
            exit();
        }
    }
    d=fopen("exemployee.txt","rb+");
    if(d==NULL)
    {
        d=fopen("exemployee.txt","wb+");
        if(d==NULL)
        {
            cprintf("File do not exist\n");
            exit();
        }
    }
    
    while(ch!='7')
    {
        ch=file();
        switch(ch)
        {
            case '1':insert_record(fp,&n,d,&cnt);
                        break;
                        
            case '2':display_record(fp,n,d,cnt);
                        break;
                       
            case '3':search_record(fp);
                        break;
                        
            case '4':alter_record(fp);
                        break;
                        
            case '5': delete_record(fp,&n);
                        break;
                       
            case '6':
                        exit(0);
                        break;
            default:
                    //testcolor(RED+BLINK);
                    gotoxy(30,10);
                    cprintf("WRONG CHOICE!!!");
                    getch();
                    break;
            }
      }
      
}


