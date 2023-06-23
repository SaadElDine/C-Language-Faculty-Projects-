#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
char str[1000][1000];
typedef struct
{
    int year,month,day;
} Date;
typedef struct
{
    int id;
    char last_name[64],first_name[64],email[64],phone_number[12],address[64];
    float salary;
    Date birthdate;
} Employee;
int read_file()
{
    char file_name[64];
    printf("Please, Enter The Name Of The File You Want To Load Followed By '.txt': \n");
    gets(file_name);
    int i=0;
    FILE* f;
    f=fopen(file_name,"r");
    if(f!=NULL)
    {
        while(fgets(str[i],999,f)!=NULL)
        {
            i++;
        }
    }
    else printf("The File Indicated does NOT exist!\nPlease Try Again Using Another File\a\n");
    fclose(f);
    return i;
}
void deserialize_employee(char* s,Employee* x)
{
    char *tok=strtok(s,",-");
    int m=0;
    while (tok)
    {
        switch (m)
        {
        case 0:
            x->id=atoi(tok);
            break;
        case 1:
            strcpy(x->last_name,tok);
            break;
        case 2:
            strcpy(x->first_name,tok);
            break;
        case 3:
            x->salary=atof(tok);
            break;
        case 4:
            x->birthdate.day=atoi(tok);
            break;
        case 5:
            x->birthdate.month=atoi(tok);
            break;
        case 6:
            x->birthdate.year=atoi(tok);
            break;
        case 7:
            strcpy(x->address,tok);
            break;
        case 8:
            strcpy(x->phone_number,tok);
            break;
        case 9:
            strcpy(x->email,tok);
            break;
        }
        m++;
        tok=strtok(NULL,",-\n");
    }
}
void search_employee(Employee* x,int n)
{
    char last_name[40];
    printf("Please, Enter The Last Name Of The Employee you Want To Look For :\n");
    scanf("%s",last_name);
    int flag=0;
    for(int i=0; i<n; i++)
    {
        if(!strcasecmp(last_name,x[i].last_name))
        {
            flag++;
            if(flag==1) printf("Here's The Informations Of The Employees With Last Name '%s' :\n",last_name);
            printf("Information Of The Employee:\n");
            printf("ID : %d\n",x[i].id);
            printf("Last Name : %s\n",x[i].last_name);
            printf("First Name : %s\n",x[i].first_name);
            printf("Birth Date (DD/MM/YYYY): ");
            printf("%s%d / ",x[i].birthdate.day<10?"0":"",x[i].birthdate.day);
            printf("%s%d /",x[i].birthdate.month<10?"0":"",x[i].birthdate.month);
            printf(" %d \n",x[i].birthdate.year);
            printf("Salary : %.4f\n",x[i].salary);
            printf("Address : %s\n",x[i].address);
            printf("Email : %s\n",x[i].email);
            printf("\n");
        }
    }
    if(!flag) printf("No Employee With That Last Name Was Found ! , Please Try Again...\a\n");
}
int validate_email (char* x)
{
    int y=0,m=0;
    int n=(strlen(x));
    for(int i=0; i<n; i++)
    {
        if(x[i]=='@' && x[i+1]!='.')
            y++;
    }
    for(int i=0; i<n; i++)
    {
        if(x[i]=='.')
            m++;
    }
    if(y==1 && m)
        return 1;
    return 0;
}
int validate_date (Date birthdate)
{
    if(!birthdate.day || !birthdate.month || !birthdate.year)
        return 0;
    if (birthdate.day>31 || birthdate.month>12 )
        return 0;
    if(birthdate.year<1962)
    {
        printf("This Employee is Very Old , He Can NOT work here after the 60's\n");
        return 0;
    }
    if (birthdate.year>2004)
    {
        printf("This Boy/Girl Is Underage! \nHe/She MUST be +18\a\n");
        return 0;
    }
    if (birthdate.month==2 && birthdate.day>29)
    {
        printf("February is ONLY 28 days!\n");
        return 0;
    }
    if ((birthdate.month==4 || birthdate.month==6 || birthdate.month==9 || birthdate.month==11) && birthdate.day>30)
    {
        printf("The Entered Month can ONLY be 30 days!\n");
        return 0;
    }
    return 1;
}
int validate_phone_number(char *phone_number)
{
    int n=0;
    for (int i=0; i<strlen(phone_number); i++)
    {
        if (  isdigit(phone_number[i]) )
        {
            n++;
        }
    }
    if (n==11) return 1;
    return 0;

}
int validate_id(int id,Employee* x,int n)
{
    for(int i=0; i<n; i++)
    {
        if(x[i].id == id)
            return 0;
    }
    return 1;
}
void add_employee (Employee* x,int n)
{
    int k=0;
    printf("Please Enter ID Of The New Employee :\n");
    do
    {
        if(k)
            printf("SORRY, This ID Already Belongs To Another Employee\nPlease, Choose Another ID :\n");
        scanf("%d",&x[n].id);
        k++;
    }
    while(!validate_id(x[n].id,x,n));

    printf("Please Enter Last Name Of The New Employee :\n");
    scanf("%s",x[n].last_name);
    printf("Please Enter First Name Of The New Employee :\n");
    scanf("%s",x[n].first_name);
    printf("Please Enter Salary Of The New Employee :\n");
    scanf("%f",&x[n].salary);
    printf("Please Enter Date Of Birth Of The New Employee (DD/MM/YYYY) :\n");
    k=0;
    do
    {
        if(k)
            printf("Please Enter A Valid Birthdate!\a\n");
        printf("Day:");
        scanf("%d",&x[n].birthdate.day);
        printf("Month:");
        scanf("%d",&x[n].birthdate.month);
        printf("Year:");
        scanf("%d",&x[n].birthdate.year);
        k++;
    }
    while(!validate_date(x[n].birthdate));
    printf("Please Enter Address Of The New Employee :\n");
    getchar();
    gets(x[n].address);
    k=0;
    printf("Please Enter Phone Number Of The New Employee :\n");
    do
    {
        if(k)
            printf("Please Enter A Valid Phone Number!\a\n");
        gets(x[n].phone_number);
        k++;
    }
    while(!validate_phone_number(x[n].phone_number));
    k=0;
    printf("Please Enter email Of The New Employee :\n");
    getchar();
    do
    {
        if(k)
            printf("Please Enter A Valid Email!\a\n");
        gets(x[n].email);
        k++;
    }
    while(!validate_email(x[n].email));
    printf("New Employee Was Added! \a\n");
    printf("When You Are Done, Make Sure You Save Or All Your Changes Will Be Discarded!\n");
}
int delete_employee(Employee* x,int n)
{
    int p=0;
    char first_name[40],last_name[40];
    printf("Please, Enter The Last Name Of The Employee you Want To DELETE:\n");
    scanf("%s",last_name);
    printf("Please, Enter The First Name Of The Employee you Want To DELETE:\n");
    scanf("%s",first_name);
    int count=0;
    for(int i=0; i<n; i++)
    {
        if(!(strcasecmp(first_name,x[i].first_name)) && !(strcasecmp(last_name,x[i].last_name)))
        {
            p=1;
            count++;
            for(int j=i; j<n; j++)
            {
                x[j]=x[j+1];
            }
            n--;
            i--;

        }
    }
    if(!p) printf("Sorry,We Don't Recognize This Name!\a\n");
    else
    {
        printf("%d Employee%s %s DELETED!\a\n",count,count<2?"":"s",count<2?"was":"were");
        printf("Choose SAVE if you want to save changes before leaving!!!\a\n");
    }
    return count;
}
void modify_employee (Employee* x,int n)
{
    int modif,iD,flag=0,k=0;
    printf("Please, Enter The Employee's ID To Start Modifications:\n");
    scanf("%d",&iD);
    for(int i=0; i<n; i++)
    {
        if(x[i].id == iD )
        {
            flag++;
            printf("Check The Field That You Would Like to Modify\n");
            printf("Press '1': To Modify the last name.\n");
            printf("Press '2': To Modify the fist name.\n");
            printf("Press '3': To Modify the salary.\n");
            printf("Press '4': To Modify the date of birth.\n");
            printf("Press '5': To Modify the the address.\n");
            printf("Press '6': To Modify the phone number.\n");
            printf("Press '7': To Modify the email.\n");
            scanf("%d",&modif);
            switch (modif)
            {
            case 1:
                printf("Please Enter The Modified Last Name :\n");
                scanf("%s",x[i].last_name);
                printf("Modification Has Been Successfully Done!\n");
                break;
            case 2:
                printf("Please Enter The Modified First Name :\n");
                scanf("%s",x[i].first_name);
                printf("Modification Has Been Successfully Done!\n");
                break;
            case 3:
                printf("Please Enter The Modified Salary :\n");
                scanf("%f",&x[i].salary);
                printf("Modification Has Been Successfully Done!\n");
                break;
            case 4:
                printf("Please Enter The Modified Date Of Birth (DD/MM/YYYY):\n");
                do
                {
                    if(k)
                        printf("Please Enter A Valid Birthdate!\a\n");
                    printf("Day:");
                    scanf("%d",&x[i].birthdate.day);
                    printf("Month:");
                    scanf("%d",&x[i].birthdate.month);
                    printf("Year:");
                    scanf("%d",&x[i].birthdate.year);
                    k++;
                }
                while(!validate_date(x[i].birthdate));
                printf("Modification Has Been Successfully Done!\n");
                break;
            case 5:
                printf("Please Enter The Modified Address :\n");
                getchar();
                gets(x[i].address);
                printf("Modification Has Been Successfully Done!\n");
                break;
            case 6:
                k=0;
                printf("Please Enter The Modified Phone Number :\n");
                getchar();
                do
                {
                    if(k) printf("Please Enter A Valid Phone Number!\a\n");
                    gets(x[i].phone_number);
                    k++;
                }
                while(!validate_phone_number(x[i].phone_number));
                printf("Modification Has Been Successfully Done!\n");
                break;
            case 7:
                k=0;
                printf("Please Enter The Modified email :\n");
                getchar();
                do
                {
                    if(k)
                        printf("Please Enter A Valid Email!\a\n");
                    gets(x[i].email);
                    k++;
                }
                while(!validate_email(x[i].email));
                printf("Modification Has Been Successfully Done!\n");
                break;
            default:
                printf("No Modifications Occurred, The Number You Pressed is Probably Out Of Range\a\n");
                break;
            }
        }
    }
    if (!flag)
        printf("Sorry, We Don't Recognize This ID\nPlease Check your ID and Try Again!\a\n");
    char cond;
    printf("Do You Want To Modify Anything Else? (y/n) \n");
    printf("Press 'y' : If YES!\n");
    printf("Press 'n' : If No !\n");
    scanf(" %c",&cond) ;
    char s=tolower(cond);
    if(s=='y')
        modify_employee(x,n);
    else return;
}
void sort_by_last_name(Employee* x,int n)
{
    int pass,i,sorted=0;
    for(pass=1; pass<n && !sorted; pass++)
    {
        sorted=1;
        for(i=0; i<n-pass; i++)
        {
            if(strcasecmp(x[i].last_name,x[i+1].last_name)>0)
            {
                Employee temp=x[i];
                x[i]=x[i+1];
                x[i+1]=temp;
                sorted=0;
            }
        }
    }
}
void sort_by_salary(Employee* x,int n)
{
    int pass,i,sorted=0;
    for(pass=1; pass<n && !sorted; pass++)
    {
        sorted=1;
        for(i=0; i<n-pass; i++)
        {
            if(x[i].salary > x[i+1].salary)
            {
                Employee temp=x[i];
                x[i]=x[i+1];
                x[i+1]=temp;
                sorted=0;
            }
        }
    }
}
void sort_by_dob(Employee* x,int n)
{
    int pass,i,sorted=0;
    for(pass=1; pass<n && !sorted; pass++)
    {
        sorted=1;
        for(i=0; i<n-pass; i++)
        {
            if(x[i].birthdate.year > x[i+1].birthdate.year)
            {
                Employee temp1=x[i];
                x[i]=x[i+1];
                x[i+1]=temp1;
                sorted=0;
            }
            else if(x[i].birthdate.year == x[i+1].birthdate.year)
            {
                if(x[i].birthdate.month > x[i+1].birthdate.month)
                {
                    Employee temp2=x[i];
                    x[i]=x[i+1];
                    x[i+1]=temp2;
                    sorted=0;
                }
                else if(x[i].birthdate.month == x[i+1].birthdate.month)
                {
                    if(x[i].birthdate.day > x[i+1].birthdate.day)
                    {
                        Employee temp3=x[i];
                        x[i]=x[i+1];
                        x[i+1]=temp3;
                        sorted=0;
                    }
                }
            }
        }
    }
}
void print_sorted_employee(Employee* x,int n)
{
    int sortby=0;
    printf("You would like To List The Employees By...\n");
    printf("Press '1': To List The Employees By Last Name.\n");
    printf("Press '2': To List The Employees By Date Of Birth.\n");
    printf("Press '3': To List The Employees By Salary.\n");
    scanf("%d",&sortby);
    switch (sortby)
    {
    case 1:
        printf("The Following List Is Sorted By Employees' Last Name:\n");
        sort_by_last_name(x,n);
        break;
    case 2:
        printf("The Following List Is Sorted By Employees' Birth Date From Older To Younger:\n");
        sort_by_dob(x,n);
        break;
    case 3:
        printf("The Following List Is Sorted By Employees' Salary From Lower To Higher:\n");
        sort_by_salary(x,n);
        break;
    default:
        printf("No Changes Occurred! The Number You Pressed is Probably Out Of Range\a\n");
        break ;
    }
    for (int i=0; i<n; i++)
    {
        printf("Employee %d ID: %d\n",i+1,x[i].id);
        printf("Employee %d Last Name: %s\n",i+1,x[i].last_name);
        printf("Employee %d First Name: %s\n",i+1,x[i].first_name);
        printf("Employee %d Salary: %.2f\n",i+1,x[i].salary);
        printf("Employee %d Birth Date (DD/MM/YYYY): ",i+1);
        printf("%s%d / ",x[i].birthdate.day<10?"0":"",x[i].birthdate.day);
        printf("%s%d /",x[i].birthdate.month<10?"0":"",x[i].birthdate.month);
        printf(" %d \n",x[i].birthdate.year);
        printf("Employee %d Address: %s\n",i+1,x[i].address);
        printf("Employee %d Phone Number: %s\n",i+1,x[i].phone_number);
        printf("Employee %d Email: %s\n",i+1,x[i].email);
        printf("\n");
    }
    printf("Choose SAVE if you want to save changes before leaving!!!\a\n");
}
void save_employees(Employee* x, int n)
{
    char d=',';
    int o=n-1;
    char file_name[64];
    printf("Enter The Name Of The File You Want To Save In (followed by '.txt'): \n");
    getchar();
    gets(file_name);
    FILE* f;
    f=fopen(file_name,"w");
    for(int i=0; i<o; i++)
    {
        fprintf(f,"%d%c%s%c%s%c%.2f%c%s%d-%s%d-%d%c%s%c%s%c%s\n"
                ,x[i].id,d,x[i].last_name,d,x[i].first_name,d,x[i].salary,d,x[i].birthdate.day<10?"0":""
                ,x[i].birthdate.day,x[i].birthdate.month<10?"0":"",x[i].birthdate.month,x[i].birthdate.year,d,x[i].address,d,x[i].phone_number,d,x[i].email);
    }
    fprintf(f,"%d%c%s%c%s%c%.2f%c%s%d-%s%d-%d%c%s%c%s%c%s"
            ,x[o].id,d,x[o].last_name,d,x[o].first_name,d,x[o].salary,d,x[o].birthdate.day<10?"0":""
            ,x[o].birthdate.day,x[o].birthdate.month<10?"0":"",x[o].birthdate.month,x[o].birthdate.year,d,x[o].address,d,x[o].phone_number,d,x[o].email);
    fclose(f);
    printf("SAVED!\a\n");
}
int main()
{
    printf("********** Welcome To Our Program **********\n");
    printf("PLEASE Read The User Manual Carefully Before Starting The Program!\n");
    printf("Our Program Allows You To : \n");
    printf("1. Load Employees' Data From An External File Of Yours (We Do This By Default...)\n");
    printf("2. Add Employees To Your System\n");
    printf("3. Search Employee Using His Last Name\n");
    printf("4. Delete Employees' Data From Your System\n");
    printf("5. Modify Employees' Data Using Their IDs\n");
    printf("6. Print Employees' Data On Screen In Sorted Order From Your Choice\n");
    printf("7. Save Employees' Data In Your File After Any Modification\n");
    printf("8. Exit At Any Time You Want\n");
    printf("\n");
    printf("Here We Go!");
    printf("\n");
    int n=read_file();
    if(!n) return 0;
    printf("NB Of Employees Found In The File Entered = %d\n",n);
    Employee x[1024];
    for(int i=0; i<n; i++)
    {
        deserialize_employee(*(str+i),x+i);
    }
    int choose;
    char sure;
    for (;;)
    {
        printf("\n");
        printf("Press '1' : To SEARCH An Employee By Last Name\n");
        printf("Press '2' : To ADD An Employee\n");
        printf("Press '3' : To DELETE Employees With Similar Provided Name\n");
        printf("Press '4' : To MODIFY Employees' Data Field By Field\n");
        printf("Press '5' : To PRINT All Employee's Data In A Sorted Order\n");
        printf("Press '6' : To SAVE All Employees' Data In Any Chosen File\n");
        printf("Press '7' : To QUIT Program\n");
        printf("Enter Your Choice:\n");
        scanf("%d",&choose);
        switch (choose)
        {
        case 1:
            search_employee(x,n);
            break;
        case 2:
            add_employee(x,n);
            n++;
            break;
        case 3:
            n=n-delete_employee(x,n);
            break;
        case 4:
            modify_employee(x,n);
            break;
        case 5:
            print_sorted_employee(x,n);
            break;
        case 6:
            save_employees(x,n);
            break;
        case 7:
            printf("Make Sure You SAVED or All Your Changes Will Be Discarded!\a\n");
            printf("Are You Sure You Want To Exit? (y/n)\n");
            scanf(" %c",&sure);
            if(tolower(sure)=='y')
            {
                printf("********** Thank You For Using Our Program **********\a\n");
                return 0;
            }
            else continue;
            break;
        default:
            printf("Please, Enter A Valid Choice!\a\n");
            break;
        }
    }
}
