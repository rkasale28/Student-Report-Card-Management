#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <stdio.h>
#include <iomanip>
#include <conio.h>
#include <cmath>
#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"

using namespace std;

MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

int qstate;
string query;
const char *q;

class db_response{
public:
    //For establishing connection between C++ and SQL
    static void getConnection(){
        conn=mysql_init(0);
        cout<<"\n";
        if (conn)
            cout<<setw(60)<<"Connection Object OK"<<endl;
        else
            cout <<"Connection Object Problem :" <<mysql_error(conn)<< endl;

        conn=mysql_real_connect(conn,"localhost","root","","kjsce",0,NULL,0);
        cout<<"\n";
        if (conn){
            cout<<setw(65)<<"Connection to Database done!!!"<<endl;
        }
        else{
            cout <<"Connection Error: " <<mysql_error(conn)<< endl;
        }
        system("pause");
    }
};

void welcome(); //Line No. 58
string getPassword(); //Line No. 66
bool isAuthenticated(); //Line No. 87
void displayMenu(); //Line No. 114
string calculate(float);  //Line No. 156
void error();  //Line No. 170
void insertEntry();  //Line No. 177
void modifyEntry();  //Line No. 326
void changeInformation(); //Line No. 351
void changeMarks();  //Line No. 433
void displayReportCard(); //Line No. 648
void exitSystem();  //Line No. 793

//To display welcome Screen
void welcome(){
    system("color B1");
    cout<<setw(76)<<"Welcome to Student Report Card Management System\n\n";
    cout<<setw(57)<<"L O A D I N G\n";
    cout<<setw(57)<<".............\n";
}

//To input Password in hidden mode
string getPassword(){
    int ch;
    string pwd="";
    while(ch=_getch()){
        if (ch==13){
            return pwd;
        }
        else if(ch==8){
            if (pwd.length()>0){
                cout<<"\b \b";
                pwd.erase(pwd.length()-1);
            }
        }
        else{
            cout<<"*";
            pwd+=ch;
        }
    }
}

//To manage authorization required for modifying and inserting entries
bool isAuthenticated(){
    string id,pass;

    cout<<"\n";
    cout<<UNDERLINE<<" AUTHENTICATION REQUIRED"<<CLOSEUNDERLINE;
    cout<<"\n\n Enter User Id: ";
    cin>>id;
    cout<<"\n Enter Password: ";
    pass=getPassword();  //Line no. 66

    query="SELECT `pass` FROM `administrator` WHERE `id`='"+pass+"';";
    q=query.c_str();

    qstate=mysql_query(conn,q);

    if (!qstate){
        res=mysql_store_result(conn);

        row=mysql_fetch_row(res);

        if (row==0) return false;
        else if(!strcmp(pass.c_str(),row[0])) return true;
        else return false;
    }
}

//To display menu after Welcome Screen
void displayMenu(){
    system("cls");
    system("color 0A");
    int ch;
    cout<<" MENU: \n";
    cout<<" 1. Insert Entry\n";
    cout<<" 2. Modify Entry\n";
    cout<<" 3. Display Report Card\n";
    cout<<" 4. Exit\n";
    cout<<"\n Select Choice: ";
    cin>>ch;
    switch (ch){
        case 1:if (isAuthenticated()){  //Line No.87
            cout<<"\n\n Access Granted \n\n";
            system("pause");
            insertEntry(); //Line No.177
        }
        else {
            cout<<"\n\n Access Denied \n\n";
            system("pause");
            displayMenu();  //Line No. 114
        }
        break;
        case 2:if (isAuthenticated()){  //Line No.87
            cout<<"\n\n Access Granted \n\n";
            system("pause");
            modifyEntry(); //Line No.326
        }
        else {
            cout<<"\n\n Access Denied \n\n";
            system("pause");
            displayMenu();  //Line No. 114
        }
        break;
        case 3:displayReportCard(); //Line No.648
        break;
        case 4:exitSystem();  //Line No. 793
        break;
    }
}

//To calculate marks before inputting in Database
string calculate(float m){
    int marks=round(m);
    if (marks>100) error();  //Line No. 170
    else if (marks>=85 && marks<=100) return "10";
    else if (marks>=75 && marks<85) return "9";
    else if (marks>=70 && marks<75) return "8";
    else if (marks>=60 && marks<70) return "7";
    else if (marks>=50 && marks<60) return "6";
    else if (marks>=45 && marks<50) return "5";
    else if (marks>=40 && marks<45) return "4";
    else if (marks>=0 && marks<40) return "0";
}

//To generate error if marks are greater than 100
void error(){
    cout<<"\n !!!...Error...!!! \n\n"<<endl;
    system("pause");
    displayMenu();  //Line No. 114
}

//To insert records
void insertEntry(){
    string roll,fname,faname,mname,lname,g[12];
    int ese,ca,tw;
    system("cls");
    system("color 0A");
    cout<<" Enter Roll No. : ";
    cin>>roll;

    cout<<"\n Enter First Name: ";
    cin>>fname;

    cout<<" Enter Father's Name: ";
    cin>>faname;

    cout<<" Enter Mother's Name: ";
    cin>>mname;

    cout<<" Enter Last Name: ";
    cin>>lname;

    cout<<UNDERLINE<<"\n Applied Mathematics-IV\n"<<CLOSEUNDERLINE;
    cout<<" Enter ESE Marks (Out of 100): ";
    cin>>ese;

    cout<<" Enter CA Marks (Out of 40) : ";
    cin>>ca;

    g[0]=calculate((ese*0.6)+ca);  //Line No. 156

    cout<<" Enter Term Work Marks (Out of 25) : ";
    cin>>tw;

    g[1]=calculate(tw*4); //Line No. 156

    cout<<UNDERLINE<<"\n Data Communications And Networking\n"<<CLOSEUNDERLINE;
    cout<<" Enter ESE Marks (Out of 100) : ";
    cin>>ese;

    cout<<" Enter CA Marks (Out of 40) : ";
    cin>>ca;

    g[2]=calculate((ese*0.6)+ca);  //Line No. 156

    cout<<UNDERLINE<<"\n Analysis of Algorithms\n"<<CLOSEUNDERLINE;
    cout<<" Enter ESE Marks (Out of 100) : ";
    cin>>ese;

    cout<<" Enter CA Marks (Out of 40) : ";
    cin>>ca;

    g[3]=calculate((ese*0.6)+ca); //Line No. 156

    cout<<" Enter Term Work Marks (Out of 25) : ";
    cin>>tw;

    g[4]=calculate(tw*4); //Line No. 156

    cout<<UNDERLINE<<"\n Computer Organization And Architecture\n"<<CLOSEUNDERLINE;
    cout<<" Enter ESE Marks (Out of 100) : ";
    cin>>ese;

    cout<<" Enter CA Marks (Out of 40) : ";
    cin>>ca;

    g[5]=calculate((ese*0.6)+ca);  //Line No. 156

    cout<<" Enter Term Work Marks (Out of 25) : ";
    cin>>tw;

    g[6]=calculate(tw*4); //Line No. 156

    cout<<UNDERLINE<<"\n Web Programming-I\n"<<CLOSEUNDERLINE;
    cout<<" Enter ESE Marks (Out of 100) : ";
    cin>>ese;

    cout<<" Enter CA Marks (Out of 40) : ";
    cin>>ca;

    g[7]=calculate((ese*0.6)+ca);  //Line No. 156

    cout<<UNDERLINE<<"\n PCS\n"<<CLOSEUNDERLINE;
    cout<<" Enter Term Work Marks (Out of 50) : ";
    cin>>tw;

    g[8]=calculate(tw*2);  //Line No. 156

    cout<<UNDERLINE<<"\n Data Communications And Networking Laboratory\n"<<CLOSEUNDERLINE;
    cout<<" Enter Term Work Marks (Out of 25) : ";
    cin>>ese;

    cout<<" Enter Oral Marks (Out of 25) : ";
    cin>>ca;

    g[9]=calculate((ese+ca)*2);  //Line No. 156

    cout<<UNDERLINE<<"\n Web Programming-I Laboratory\n"<<CLOSEUNDERLINE;
    cout<<" Enter Term Work Marks (Out of 25) : ";
    cin>>ese;

    cout<<" Enter Practical Marks (Out of 25) : ";
    cin>>ca;

    cout<<" Enter Oral Marks (Out of 25) : ";
    cin>>tw;

    g[10]=calculate((ese+ca+tw)*4/3);  //Line No. 156

    cout<<UNDERLINE<<"\n Programming Laboratory-II\n"<<CLOSEUNDERLINE;
    cout<<" Enter Term Work Marks (Out of 50) : ";
    cin>>ese;

    cout<<" Enter Practical Marks (Out of 25) : ";
    cin>>ca;

    cout<<" Enter Oral Marks (Out of 25) : ";
    cin>>tw;

    g[11]=calculate(ese+ca+tw);  //Line No. 156

    query="INSERT INTO `student` (`roll_no`, `fname`, `faname`, `mname`, `lname`, `g1`, `g2`, `g3`, `g4`, `g5`, `g6`,";
    query+=" `g7`, `g8`, `g9`, `g10`, `g11`, `g12`) VALUES ('"+roll+"','"+fname+"','"+faname+"','"+mname+"','"+lname+"','";
    query+=g[0]+"','"+g[1]+"','"+g[2]+"','"+g[3]+"','"+g[4]+"','"+g[5]+"','"+g[6]+"','"+g[7]+"','"+g[8]+"','"+g[9]+"','";
    query+=g[10]+"','"+g[11]+"')";

    q = query.c_str();

    qstate = mysql_query(conn,q);

    if(!qstate)
        cout<<"\n Record inserted successfully...\n"<<endl;
    else
        cout<<"\n Record can't be inserted... \n\n"<<mysql_error(conn)<<endl;

    char choice;
    cout<<"Insert Another Entry? (Y / N): ";
    cin>>choice;
    switch(choice){
    case 'Y':
    case 'y':
        insertEntry();  //Line No. 177
        break;
    case 'N':
    case 'n':
        displayMenu();  //Line No. 114
        break;
    }
}

//To update records
void modifyEntry(){
    system("cls");
    system("color 0A");
    int ch;
    cout<<" MENU: \n";
    cout<<" 1. Update Information\n";
    cout<<" 2. Update Marks\n";
    cout<<" 3. Back\n";
    cout<<" 4. Exit\n";
    cout<<"\n Select Choice: ";
    cin>>ch;

    switch(ch){
        case 1:changeInformation();  //Line No.351
        break;
        case 2:changeMarks();  //Line No.433
        break;
        case 3:displayMenu();  //Line No.114
        break;
        case 4:exitSystem();  //Line No. 793
        break;
    }
}

//To update fields related to personal information
void changeInformation(){
   string roll,fname,faname,mname,lname;
   int ch;
   cout<<"\n Enter Roll No.: ";
   cin>>roll;

   system("cls");
   system("color 0A");
   cout<<" MENU: \n";
   cout<<" 1. First Name\n";
   cout<<" 2. Father's Name\n";
   cout<<" 3. Mother's Name\n";
   cout<<" 4. Last Name\n";
   cout<<" 5. Back\n";
   cout<<" 6. Exit\n";
   cout<<"\n Select Field:";
   cin>>ch;

   switch (ch){
   case 1: cout<<"\n Enter First Name: ";
    cin>>fname;
    query="UPDATE `student` SET `fname` = '"+fname+"' WHERE `student`.`roll_no` = "+roll+";";
    q=query.c_str();

    qstate=mysql_query(conn,q);

    if (!qstate)
        cout<<"\n Record Modified Successfully... \n\n";
    else
        cout<<"\n Record can't be Modified... \n\n";
    break;

    case 2:cout<<"\n Enter Father's Name: ";
    cin>>faname;
    query="UPDATE `student` SET `faname` = '"+faname+"' WHERE `student`.`roll_no` = "+roll+";";
    q=query.c_str();

    qstate=mysql_query(conn,q);

    if (!qstate)
        cout<<"\n Record Modified Successfully... \n\n";
    else
        cout<<"\n Record can't be Modified... \n\n";
    break;

    case 3:cout<<"\n Enter Mother's Name: ";
    cin>>mname;
    query="UPDATE `student` SET `mname` = '"+mname+"' WHERE `student`.`roll_no` = "+roll+";";
    q=query.c_str();

    qstate=mysql_query(conn,q);

    if (!qstate)
        cout<<"\n Record Modified Successfully... \n\n";
    else
        cout<<"\n Record can't be Modified... \n\n";
    break;

    case 4:cout<<"\n Enter Last Name: ";
    cin>>lname;
    query="UPDATE `student` SET `lname` = '"+lname+"' WHERE `student`.`roll_no` = "+roll+";";
    q=query.c_str();

    qstate=mysql_query(conn,q);

    if (!qstate)
        cout<<"\n Record Modified Successfully... \n\n";
    else
        cout<<"\n Record can't be Modified... \n\n";
    break;

    case 5:modifyEntry();  //Line No.326
    break;

    case 6:exitSystem();  //Line No. 793
    break;
   }
   system("pause");
   modifyEntry();  //Line No.326
}

//To update marks
void changeMarks(){
    string g[2],roll;
    int ch,ese,ca,tw;
    cout<<"\n Enter Roll No.: ";
    cin>>roll;
    system("cls");
    system("color 0A");
    cout<<" MENU: \n";
    cout<<" 1. Applied Mathematics\n";
    cout<<" 2. Data Communication And Networking\n";
    cout<<" 3. Analysis of Algorithms\n";
    cout<<" 4. Computer Organization and Architecture\n";
    cout<<" 5. Web Programming-I\n";
    cout<<" 6. Professional Communication Skills\n";
    cout<<" 7. Programming Laboratory-II\n";
    cout<<" 8. Back\n";
    cout<<" 9. Exit\n";
    cout<<"\n Select Subject: ";
    cin>>ch;
    switch (ch){
    case 1:
        cout<<UNDERLINE<<"\n Applied Mathematics-IV\n"<<CLOSEUNDERLINE;
        cout<<" Enter ESE Marks (Out of 100): ";
        cin>>ese;

        cout<<" Enter CA Marks (Out of 40) : ";
        cin>>ca;

        g[0]=calculate((ese*0.6)+ca);  //Line No. 156

        cout<<" Enter Term Work Marks (Out of 25) : ";
        cin>>tw;

        g[1]=calculate(tw*4);  //Line No. 156

        query="UPDATE `student` SET `g1` = '"+g[0]+"', `g2` = '"+g[1]+"' WHERE "
        "`student`.`roll_no` = "+roll+";";
        q=query.c_str();

        qstate=mysql_query(conn,q);

        if (!qstate)
            cout<<"\n Record Modified Successfully... \n\n";
        else
            cout<<"\n Record can't be Modified... \n\n";
        break;

    case 2:
        cout<<UNDERLINE<<"\n Data Communications and Networking\n"<<CLOSEUNDERLINE;
        cout<<" Enter ESE Marks (Out of 100) : ";
        cin>>ese;

        cout<<" Enter CA Marks (Out of 40) : ";
        cin>>ca;

        g[0]=calculate((ese*0.6)+ca);  //Line No. 156

        cout<<" Enter Term Work Marks (Out of 25) : ";
        cin>>ese;

        cout<<" Enter Oral Marks (Out of 25) : ";
        cin>>ca;

        g[1]=calculate((ese+ca)*2);  //Line No. 156

        query="UPDATE `student` SET `g3` = '"+g[0]+"', `g10` = '"+g[1]+"' WHERE "
        "`student`.`roll_no` = "+roll+";";
        q=query.c_str();

        qstate=mysql_query(conn,q);

        if (!qstate)
            cout<<"\n Record Modified Successfully... \n\n";
        else
            cout<<"\n Record can't be Modified... \n\n";
        break;

    case 3:
        cout<<UNDERLINE<<"\n Analysis of Algorithms\n"<<CLOSEUNDERLINE;
        cout<<" Enter ESE Marks (Out of 100) : ";
        cin>>ese;

        cout<<" Enter CA Marks (Out of 40) : ";
        cin>>ca;

        g[0]=calculate((ese*0.6)+ca);  //Line No. 156

        cout<<" Enter Term Work Marks (Out of 25) : ";
        cin>>tw;

        g[1]=calculate(tw*4);  //Line No. 156

        query="UPDATE `student` SET `g4` = '"+g[0]+"', `g5` = '"+g[1]+"' WHERE "
        "`student`.`roll_no` = "+roll+";";
        q=query.c_str();

        qstate=mysql_query(conn,q);

        if (!qstate)
            cout<<"\n Record Modified Successfully... \n\n";
        else
            cout<<"\n Record can't be Modified... \n\n";
        break;

    case 4:
        cout<<UNDERLINE<<"\n Computer Organization And Architecture\n"<<CLOSEUNDERLINE;
        cout<<" Enter ESE Marks (Out of 100) : ";
        cin>>ese;

        cout<<" Enter CA Marks (Out of 40) : ";
        cin>>ca;

        g[0]=calculate((ese*0.6)+ca);  //Line No. 156

        cout<<" Enter Term Work Marks (Out of 25) : ";
        cin>>tw;

        g[1]=calculate(tw*4);  //Line No. 156

        query="UPDATE `student` SET `g6` = '"+g[0]+"', `g7` = '"+g[1]+"' WHERE "
        "`student`.`roll_no` = "+roll+";";
        q=query.c_str();

        qstate=mysql_query(conn,q);

        if (!qstate)
            cout<<"\n Record Modified Successfully... \n\n";
        else
            cout<<"\n Record can't be Modified... \n\n";
        break;

    case 5:
        cout<<UNDERLINE<<"\n Web Programming-I\n"<<CLOSEUNDERLINE;
        cout<<" Enter ESE Marks (Out of 100) : ";
        cin>>ese;

        cout<<" Enter CA Marks (Out of 40) : ";
        cin>>ca;

        g[0]=calculate((ese*0.6)+ca);  //Line No. 156

        cout<<" Enter Term Work Marks (Out of 25) : ";
        cin>>ese;

        cout<<" Enter Practical Marks (Out of 25) : ";
        cin>>ca;

        cout<<" Enter Oral Marks (Out of 25) : ";
        cin>>tw;

        g[1]=calculate((ese+ca+tw)*4/3);  //Line No. 156

        query="UPDATE `student` SET `g8` = '"+g[0]+"', `g11` = '"+g[1]+"' WHERE "
        "`student`.`roll_no` = "+roll+";";
        q=query.c_str();

        qstate=mysql_query(conn,q);

        if (!qstate)
            cout<<"\n Record Modified Successfully... \n\n";
        else
            cout<<"\n Record can't be Modified... \n\n";
        break;

    case 6:
        cout<<UNDERLINE<<"\n Professional Communication Skills\n"<<CLOSEUNDERLINE;
        cout<<" Enter Term Work Marks (Out of 50) : ";
        cin>>tw;

        g[0]=calculate(tw*2);  //Line No. 156

        query="UPDATE `student` SET `g9` = '"+g[0]+"' WHERE `student`.`roll_no` = "+roll+";";
        q=query.c_str();

        qstate=mysql_query(conn,q);

        if (!qstate)
            cout<<"\n Record Modified Successfully... \n\n";
        else
            cout<<"\n Record can't be Modified... \n\n";
        break;

    case 7:
        cout<<UNDERLINE<<"\n Programming Laboratory-II\n"<<CLOSEUNDERLINE;
        cout<<" Enter Term Work Marks (Out of 50) : ";
        cin>>ese;

        cout<<" Enter Practical Marks (Out of 25) : ";
        cin>>ca;

        cout<<" Enter Oral Marks (Out of 25) : ";
        cin>>tw;

        g[0]=calculate(ese+ca+tw);  //Line No. 156

        query="UPDATE `student` SET `g12` = '"+g[0]+"' WHERE `student`.`roll_no` = "+roll+";";
        q=query.c_str();

        qstate=mysql_query(conn,q);

        if (!qstate)
            cout<<"\n Record Modified Successfully... \n\n";
        else
            cout<<"\n Record can't be Modified... \n\n";
        break;
    case 8:modifyEntry();  //Line No.326
        break;
    case 9:exitSystem();  //Line No. 793
        break;
    }
    system("pause");
    modifyEntry();  //Line No. 326
}

//To display Report Card
void displayReportCard(){
    string id,credits[12],marks[12],grade[12];

    cout<<"\n Enter Roll No.: ";
    cin>>id;

    system("cls");
    system("color F0");
    query="SELECT * FROM `student` WHERE roll_no='"+id+"'";
    q=query.c_str();

    qstate=mysql_query(conn,q);

    if (!qstate){
        res=mysql_store_result(conn);

        cout<<std::setw(69)<<"UNIVERSITY OF MUMBAI\n";
        cout<<std::setw(77)<<"K. J. SOMAIYA COLLEGE OF ENGINEERING\n";
        cout<<std::setw(79)<<"Vidyanagar, Vidyavihar, Mumbai - 400 077\n";
        cout<<"-------------------------------------------------------------------------------";
        cout<<"------------------------------\n";

        cout<<std::setw(68)<<"Autonomous College\n";
        cout<<std::setw(76)<<"Affiliated to University of Mumbai\n";
        cout<<"-------------------------------------------------------------------------------";
        cout<<"------------------------------\n";

        cout<<std::setw(68)<<"GRADE CARD\n";
        cout<<"-------------------------------------------------------------------------------";
        cout<<"------------------------------\n";

        while (row=mysql_fetch_row(res)){
            int temp=atoi (row[0]);
            if (temp<10)
                printf("%-20s : 171400%s\n"," ROLL NO./GR. NO.",row[0]);
            else if (temp<100)
                printf("%-20s : 17140%s\n"," ROLL NO./GR. NO.",row[0]);
            else
                printf("%-20s : 1714%s\n"," ROLL NO./GR. NO.",row[0]);

            printf("%-20s : %s %s %s %s\n"," NAME",row[4],row[1],row[2],row[3]);

            printf("%-20s : %s\n"," PROGRAMME","Bachelor Of Technology");

            printf("%-20s : %s\n"," BRANCH","Information Technology");

            printf("%-20s : %s\n"," EXAMINATION","May 2019");

            printf("%-20s : %s\n"," YEAR & SEMESTER","Second Year Semester-IV");
            cout<<"------------------------------------------------------------------------------";
            cout<<"-------------------------------\n";

            for(int i=5;i<17;i++){
                marks[i-5]=row[i];
            }
        }
    }
    else{
        cout <<"Query Execution Problem " <<mysql_error(conn)<< endl;
    }

    printf("%-10s | %-50s | %-10s | %-6s | %-10s | %-6s |\n","  Course",
           "                   Course Title","  Course","Grade","  Grade","C * G");

    printf("%-10s | %-50s | %-10s | %-6s | %-10s | %-6s |\n","   Code",
           "","  Credits","","  Points","");
    cout<<"-------------------------------------------------------------------------------";
    cout<<"------------------------------\n";

    for (int i=0;i<12;i++){
        query="SELECT grade FROM `grade` WHERE grade_point='"+marks[i]+"'";
        q=query.c_str();

        qstate=mysql_query(conn,q);

        if (!qstate){
            res=mysql_store_result(conn);
            while (row=mysql_fetch_row(res)){
                grade[i]=row[0];
            }
        }
        else{
            cout <<"Query Execution Problem " <<mysql_error(conn)<< endl;
        }
    }

    qstate=mysql_query(conn,"Select * from course");
    int j=0,sum=0,temp;
    if (!qstate){
        res=mysql_store_result(conn);
        while (row=mysql_fetch_row(res)){
            temp=(atoi(marks[j].c_str()))*(atoi(row[2]));
            sum+=temp;
            if (atoi(marks[j].c_str())<10)
                printf("   %-7s | %-50s |     %-6s |   %-4s |     0%-5s |   %02d   |\n",row[0],
                       row[1],row[2],grade[j].c_str(),marks[j].c_str(),temp);
            else
                printf("   %-7s | %-50s |     %-6s |   %-4s |     %-6s |   %02d   |\n",row[0],
                       row[1],row[2],grade[j].c_str(),marks[j].c_str(),temp);
            j++;
        }
    }
    else{
        cout <<"Query Execution Problem " <<mysql_error(conn)<< endl;
    }

    cout<<"------------------------------------------------------------------------------";
    cout<<"-------------------------------\n";

    qstate=mysql_query(conn,"SELECT SUM(course_credits) from course");

    cout<<setw(65)<<"TOTAL |";

    if (!qstate){
        res=mysql_store_result(conn);
        while (row=mysql_fetch_row(res)){
                printf("     %-6s |",row[0]);
        }
    }
    printf(" %-19s |   %-4d |\n","",sum);

    cout<<"------------------------------------------------------------------------------";
    cout<<"-------------------------------\n";

    int count=0;
    for (int i=0;i<12;i++){
        if (!strcmp(grade[i].c_str(),"FF*")) count++;
    }

    cout<<"\n\nRESULT: ";
    if (count==0) cout<<UNDERLINE<<"  Successful  "<<CLOSEUNDERLINE;
    else if (count<=3) cout<<UNDERLINE<<" Successful*** "<<CLOSEUNDERLINE;
    else cout<<UNDERLINE<<" Unsuccessful "<<CLOSEUNDERLINE;

    cout<<"\t\t\t SGPI: ";
    cout<<std::fixed;
    cout<<std::setprecision(2);
    cout<<UNDERLINE<<"  "<<sum/24.0<<"  "<<CLOSEUNDERLINE;
    cout<<"\n\n";
    system("pause");
    displayMenu();  //Line No. 114
}

//To display screen while exiting
void exitSystem(){
    system("cls");
    system("color B1");
    cout<<setw(55)<<"THANK YOU\n\n";
    cout<<setw(62)<<"for using this software\n\n";
    cout<<setw(54)<<"MADE BY:\n\n";
    cout<<setw(58)<<"Rohit R. Kasale\n\n";
    cout<<setw(68)<<"K. J. Somaiya College Of Engineering\n\n";
    system("pause");
    exit(0);
}

int main(){
    system("cls");
    system("title Student Report Card System");

    welcome(); //Line No.58
    db_response::getConnection();  //Line No. 21

    displayMenu();  //Line No. 114
    return 0;
}
