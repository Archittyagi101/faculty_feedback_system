#include<conio.h>
#include<iostream>
#include <iomanip>
using namespace std;

void get_feedback_data();
void write_Faculty();
void display_all();
void display_specific(int n);
void update_faculty();
void delete_faculty();
void faculty_record();
void record();
void intro();
void entry_menu();
int checkCriteria(int n);

struct Faculty
{
 int id_no,punctuality,aud_cla,teach,stu_int,command;
 char name[50],grade;
 float gpa;
};

struct Faculty faculty;
FILE *fptr;

void get_feedback_data()
{
    start:
    cout<<"\n\nENTER THE FEEDBACK FOR THIS FACULTY\n";
    cout<<"Number out of 10 : 1 for Poor and 10 for Excellent for each Criteria";
    cout<<"\n\nPunctuality in Class and Subject : ";
    cin>>faculty.punctuality;
    cout<<"\nAudibility and Clarity : ";
    cin>>faculty.aud_cla;
    cout<<"\nTeaching Methodology : ";
    cin>>faculty.teach;
    cout<<"\nStudents Interaction : ";
    cin>>faculty.stu_int;
    cout<<"\nCommand over Class and Subject : ";
    cin>>faculty.command;

    if (checkCriteria(faculty.punctuality) && checkCriteria(faculty.aud_cla) && checkCriteria(faculty.teach) && checkCriteria(faculty.stu_int) && checkCriteria(faculty.command))
    {
        faculty.gpa=(faculty.punctuality+faculty.aud_cla+faculty.teach+faculty.stu_int+faculty.command)/5.0;
    if(faculty.gpa>=8)
       faculty.grade='A';
    else if(faculty.gpa>=6 &&faculty.gpa<8)
      faculty.grade='B';
    else if(faculty.gpa>=4 &&faculty.gpa<6)
      faculty.grade='C';
    else
     faculty.grade='F';
    }
    else
    {cout<<"Enter correct range of values!";
    goto start;
    }
}
int checkCriteria(int n)
{
    if(n>=1 && n<=10)
        return 1;
    return 0;
}
void write_Faculty()
{
    fptr=fopen("Faculty.dat","ab");
    cout<<"\nPlease Enter the Details of New Faculty \n";
    cout<<"\nEnter The Identity number of Faculty : ";
    cin>>faculty.id_no;
    fflush(stdin);
    cout<<"\nEnter The Name of Faculty : ";
    gets(faculty.name);
    get_feedback_data();
    fwrite(&faculty,sizeof(faculty),1,fptr);
    fclose(fptr);
    cout<<"\n\nFaculty Record Created Successfully !";
    getch();
}
//***************************************************************
//        function to read all records from file
//****************************************************************
void display_all()
{
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fptr=fopen("Faculty.dat","rb");
    while((fread(&faculty,sizeof(faculty),1,fptr))>0)
    {
      cout<<"\nIdentity Number of Faculty : "<<faculty.id_no;
      faculty.name[0]=toupper(faculty.name[0]);
      cout<<"\nName of Faculty : "<<faculty.name;
      cout<<"\nRemarks for Punctuality in class and subject : "<<faculty.punctuality;
      cout<<"\nRemarks for Audibility and Clarity : "<<faculty.aud_cla;
      cout<<"\nRemarks for Teaching Methodology : "<<faculty.teach;
      cout<<"\nRemarks for Students Interaction  : "<<faculty.stu_int;
      cout<<"\nRemarks for Command over class and Subject : "<<faculty.command;
      cout<<"\nAverage Remark : "<<fixed<<setprecision(2)<<faculty.gpa;
      cout<<"\nGrade of Faculty is : "<<faculty.grade;
      cout<<"\n\n==================================\n";
      getch();
    }
    fclose(fptr);
    getch();
}
//***************************************************************
//        READING SPECIFIC FACULTY RECORD
//***************************************************************
void display_specific(int n)
{
    int flag=0;
    fptr=fopen("Faculty.dat","rb");
    while((fread(&faculty,sizeof(faculty),1,fptr))>0)
    {
     if(faculty.id_no==n)
     {
         cout<<"\nIdentity Number of Faculty : "<<faculty.id_no;
         faculty.name[0]=toupper(faculty.name[0]);
         cout<<"\nName of Faculty : "<<faculty.name;
         cout<<"\nRemarks for Punctuality in class and subject : "<<faculty.punctuality;
         cout<<"\nRemarks for Audibility and Clarity : "<<faculty.aud_cla;
         cout<<"\nRemarks for Teaching Methodology : "<<faculty.teach;
         cout<<"\nRemarks for Students Interaction  : "<<faculty.stu_int;
         cout<<"\nRemarks for Command over class and Subject : "<<faculty.command;
         cout<<"\nAverage Remark : "<<fixed<<setprecision(2)<<faculty.gpa;
         cout<<"\nGrade of Faculty is : "<<faculty.grade;
         cout<<"\n\n=================================\n";
         flag=1;
     }
    }
    fclose(fptr);
    if(flag==0)
    cout<<"\n\nRecord does not exist!";
    getch();
}
//***************************************************************
//        FUNCTION TO UPDATE RECORD OF FILE
//****************************************************************
void update_faculty()
{
    int no,found=0;
    cout<<"\n\n\tPlease Enter The Identity number of Faculty : ";
    cin>>no;
    fptr=fopen("Faculty.dat","rb+");
    while((fread(&faculty,sizeof(faculty),1,fptr))>0 && found==0)
    {
        if(faculty.id_no==no)
        {
            cout<<"\nIdentity Number of Faculty : "<<faculty.id_no;
            faculty.name[0]=toupper(faculty.name[0]);
            cout<<"\nName of Faculty : "<<faculty.name;
            cout<<"\nRemarks for Punctuality in class and subject : "<<faculty.punctuality;
            cout<<"\nRemarks for Audibility and Clarity : "<<faculty.aud_cla;
            cout<<"\nRemarks for Teaching Methodology : "<<faculty.teach;
            cout<<"\nRemarks for Students Interaction  : "<<faculty.stu_int;
            cout<<"\nRemarks for Command over class and Subject : "<<faculty.command;
            cout<<"\nAverage Remark : "<<fixed<<setprecision(2)<<faculty.gpa;
            cout<<"\nGrade of Faculty is : "<<faculty.grade;
            cout<<"\n\n=================================\n";
            fflush(stdin);
            get_feedback_data();
            fseek(fptr,-(long)sizeof(faculty),1);
            fwrite(&faculty,sizeof(faculty),1,fptr);
            cout<<"\n\n\t Record Updated !";
            found=1;
           }
         }
    fclose(fptr);
    if(found==0)
    cout<<"\n\n Record Not Found! ";
    getch();
}
//***************************************************************
//       DELETING FACULTY RECORD OF FILE
//****************************************************************
void delete_faculty()
{
    int no;
    FILE *fptr_;
    cout<<"\n\n\n\tDelete Faculty Record";
    cout<<"\n\nPlease Enter The Identity number of Faculty You Want To Delete : ";
    cin>>no;
    display_specific(no);
    fptr=fopen("Faculty.dat","rb");\
    fptr_=fopen("Temp.dat","wb");
    rewind(fptr);
    while((fread(&faculty,sizeof(faculty),1,fptr))>0)
    {
       if(faculty.id_no!=no)
       {
        fwrite(&faculty,sizeof(faculty),1,fptr_);
       }
    }
    fclose(fptr_);
    fclose(fptr);
    remove("Faculty.dat");
    rename("Temp.dat","Faculty.dat");
    cout<<"\n\n\tRecord Deleted Successfully..";
    getch();
}
//***************************************************************
//        function to display all Faculty feedback report
//****************************************************************
void faculty_record()
{
     fptr=fopen("Faculty.dat","rb");
     if(fptr==NULL)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
       cout<<"\n\n\n Program is closing ....";
       getch();
       exit(0);
     }
     cout<<"\n\n\t\tALL Faculty Feedback Result \n\n";
     cout<<"=====================================================================================================================================\n";
     cout<<"ID.No.    Name       Punctuality   Audibility and Clarity   Teaching Methodology   Students Interaction   Command     GPA      Grade\n";
     cout<<"=====================================================================================================================================\n";
      while((fread(&faculty,sizeof(faculty),1,fptr))>0)
     {
         faculty.name[0]=toupper(faculty.name[0]);
         printf("%-7d %-17s %-15d %-24d %-22d %-19d %-7d %-10.2f  %-4c\n",faculty.id_no,faculty.name,faculty.punctuality,faculty.aud_cla,faculty.teach,faculty.stu_int,faculty.command,faculty.gpa,faculty.grade);
     }
     fclose(fptr);
     getch();
}
//***************************************************************
//        FUNCTION DISPLAYING RECORDS
//****************************************************************
void record()
{
    int ans,no;
    char ch;
    cout<<"\n\n\nRECORD MENU";
    cout<<"\n\n\n1. All Faculty Records\n\n2. Faculty Report Card\n\n3. Back to Main Menu";
    cout<<"\n\n\nEnter Your Choice : ";
    cin>>ans;
    switch(ans)
    {
     case 1 : faculty_record();break;
     case 2 : {
        do{
        again:
        char ans;
        cout<<"\n\nEnter Faculty Identity Number : ";
        try{
        cin>>no;
        }
        catch(int no){
        cout<<no<<" :Enter Integer Number\a";
        goto again;
        }
        display_specific(no);
        cout<<"\n\nDo you want to See More Records (y/n)?";
        cin>>ans;
        }while(ans=='y'||ans=='Y');
        break;
           }
     case 3: break;
     default:  cout<<"Try Again!\a";
    }
}
//***************************************************************
//        INTRO FUNCTION
//****************************************************************
void intro()
{
    char c;
    FILE *p;
    p=fopen("view.txt","r");
    if(p==NULL)
    {
        printf("File not found\n");
        exit(0);
    }
    c=fgetc(p);
    while(c !=EOF)
    {
        printf("%c",c);
        c=fgetc(p);
    }
    fclose(p);
    getch();
}
//***************************************************************
//        CRUD OPERATIONS MENU FUNCTION
//****************************************************************
void entry_menu()
{
    char ch;
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.Create new Faculty Record";
    cout<<"\n\n\t2.Display all Faculty Record";
    cout<<"\n\n\t3.Search Faculty Record";
    cout<<"\n\n\t4.Update Faculty Record";
    cout<<"\n\n\t5.Delete Faculty Record";
    cout<<"\n\n\t6.Back to Main Menu";
    cout<<"\n\n\tPlease Enter Your Choice : ";
    cin>>ch;
    switch(ch)
    {
        case '1':
          write_Faculty();
          break;
        case '2': display_all();break;
        case '3':  {
           int num;
           cout<<"\n\n\tPlease Enter The Identity number : ";
           cin>>num;
           display_specific(num);
           }
           break;
        case '4': update_faculty();break;
        case '5': delete_faculty();break;
        case '6': break;
        default:cout<<"Try Again!\a";entry_menu();
    }
}
//***************************************************************
//        MAIN FUNCTION OF PROJECT PROGRAM
//****************************************************************
int main()
{
    char ch;
    intro();
    do
    {
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t1. RESULT MENU";
        cout<<"\n\n\t2. CRUD OPERATIONS MENU";
        cout<<"\n\n\t3. EXIT";
        cout<<"\n\n\tPlease Enter Your Choice : ";
        ch=getche();
        switch(ch)
        {
            case '1':
               record();
               break;
            case '2': entry_menu();
                break;
            case '3':exit(0);
            default :cout<<"\nTry Again!\a";
        }
    }while(ch!='3');
}


