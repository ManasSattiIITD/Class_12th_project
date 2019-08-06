//***-----  OVERVIEW AND INSTRUCTIONS  -----***

// A C++ PROGRAM ON BANK MANAGEMENT
//JOINT PROJECT BY :--

// Name: MANAS                                                 //Name: SANCHIT JAIN
				    //AND
// Roll Number: 21                                             //Roll Number: 31


// CLASS: XII-B

// Computer Science

// DAV Public School, Srestha Vihar, Delhi


//The Program is included in "ultra.cpp".
//Required files must be put in tc/bin before executing:--
// 1). GENT&C.TXT
// 2). CACCT&C.TXT
// 3). NEFTT&C.TXT
// 4). IATMT&C.TXT

//Files Created During Execution :--
//1). O.DAT
//2). LOAN.DAT
//3). TRANS.TXT
//4). "Bank User Notification files"

//LIMITATIONS
//1). The program and files are not encrypted.
//2). The admin password and masterkey can't be hidden or encrypted.
//3). Can't transfer money to bank account of another bank.
//4). Can't enforce payment of loan at the given loan time and keep record of remaining loan time.
//5). In few cases text formatting is not very user friendly due to certain restrictions.

/*******************************************************************************************************************************************/


/*Required Header Files*/
#include<conio.h>
#include<fstream.h>
#include<dos.h>
#include<iomanip.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>



long int tid;
const char chara[16]="admin";
const char chat[16]="dob12052000";
const char ifsc[16]="BDAVSV01357";
const long int masterpass=8158087;
double money=0;
int loandurmonths;
double atmmoney;
int choiceloan;
int jiofi=0;
char neftname[80];
double universe=0.0;
int opt,share=0;
long int cdno;
int manas=0;
float intper=1.05,intprop=0.95,intedu=0.67,intveh=1.084;
#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21

static char *getDtTm (char *buff)
{
    time_t t = time (0);
    strftime (buff, DTTMSZ, DTTMFMT, localtime (&t));
    return buff;
}


void timesave(int tids,double tam,char stp[],long int nom, char comment[]="TYPE NOT AVALABLE!")                //   Function for textual date and time
{   //   and storing transaction history.
    char buff[DTTMSZ];
    char strike[64];
    fstream fr;
    ifstream fr0("trans.txt");
    if(!fr0)
    {
        fr.open("trans.txt",ios::out);
        fr.close();
    }
    fr0.close();
    fr.open("trans.txt", ios::out | ios::app);
    fr<<getDtTm(buff)<<" : ";
    fr<<"\nTransaction Type: ";
    fr<<comment;
    fr<<"\nBank Account Number: "<<nom<<endl;
    fr<<"User Name: ";
    fr<<stp;
    fr<<"\nTransaction ID: ";
    fr<<tids;
    fr<<"\nTransaction Amount: RS ";
    fr<<tam;
    fr<<"\n*****--------------------------------------------------------------*****%\n\n";
    fr.close();
}

void notifwrite(int tids,double tam,char stp[],long int nom,int cheque,char carry[15],char comment[]="COMMENT NOT AVALABLE!")
{
    char buff[DTTMSZ];
    char strike[64];
    fstream fr;
    if(cheque==0)
        fr.open(carry, ios::out);
    else
        fr.open(carry, ios::in | ios::out | ios::app);
    fr<<getDtTm(buff)<<" : ";
    cout<<endl;
    fr<<comment;
    fr<<"\nSender's Bank Account Number: "<<nom<<endl;
    fr<<"Sender's Name: ";
    fr<<stp;
    fr<<"\nTransaction ID: ";
    fr<<tids;
    fr<<"\nTransaction Amount: RS ";
    fr<<tam;
    fr<<"\nNote the details for future ref. as it will be deleted post this instance.";
    fr<<"\n*****--------------------------------------------------------------------*****$\n\n";
    fr.close();
}


void line(int);             //Function to insert blank lines
void line(int n)
{
    for(int i=0; i<n; i++)
        cout<<endl;
}

double returncalc(double , float , int);         //Function to calculate SI to display
double returncalc(double a,float b,int c)
{
    double ia,wa;
    ia=(a*b*c)/100;
    wa=a+ia;
    return ceil(wa);
}

void timeclause()                              //Function to display current time
{
    time_t t=time(0);
    struct tm* now=localtime(&t);
    cout<<"time:"
        <<(now->tm_hour)<<":"
        <<(now->tm_min)<<":"
        <<(now->tm_sec)<<"  "
        <<"date:"
        <<(now->tm_mday)<<'/'
        <<(now->tm_mon+1)<<'/'
        <<(now->tm_year+1900);
}

int randomnumgenerator()                    //Function to generate random integer value
{
    unsigned int seedval;
    time_t t;
    seedval = (unsigned)time(&t);
    srand(seedval);
    return rand();
}

class account                             //Class that stores data about bank user
{

private:

    double balance;
    double loanamt;
    float interest;
    char mainpass[16];
    int status;
    long int num;
    long int atmcdno;
    int limit;
    double returnamt;


public:

    char name[64];
    char notif[15];
    char loanname[32];
    char address[150];
    int loandurmonth,notifs;
    char contactno[11];
    int byear;
    char bmonth[18];
    int bday;
    char filename[12];


    account()                        //Construtor of class account
    {
        balance=0;
        status=0;
        notifs=0;
        limit=30;
    }

    //FUNCTIONS TO HANDLE STATUS OF BANK ACCOUNT

    int returnstatus()
    {
        return status;
    }

    void block()                    //Function to block a bank account
    {
        status=1;
    }

    void unblock()                 //Function to unblock a bank account
    {
        status=0;
    }

    void showstatus()
    {
        cout<<status;
    }

    //------------------------------------------------------------------------------------------------------------------------



    //FUNCTIONS TO HANDLE PASSWORDS


    void setmainpass(char[]);

    char* returnmainpass()
    {
        char* a;
        a=mainpass;
        return a;
    }

    void showmainpass()                                      //Function to show password
    {
        puts(mainpass);
    }


    char* updatepass(account);

    //-------------------------------------------------------------------------------------------------------------------------


    //FUNCTIONS TO HANDLE USER DATA VARIABLES


    void assingatmcdno(void);                                //Function to assign iATM Card Number

    long int returnatmcdno()
    {
        return atmcdno;
    }

    void shownum()
    {
        cout<<num;
    }

    long int returnnum()
    {
        return num;
    }


    void assignacno(void);                                      //Function to assign Bank Account Number


    void getname();                                      //Funtion(prototype) to input name

    void showname()                                        //Function to show name
    {
        cout<<name;
    }


    void createnotif();

    void getphone(void);

    void getdob(void);

    //---------------------------------------------------------------------------------------------------------


    //FUNCTIONS TO HANDLE VARIABLES RELATED TO MONEY AND LOAN

    double returnbalance()
    {
        return balance;
    }

    float returninterest()
    {
        return interest;
    }

    void setinterest(float amkette)
    {
        interest=amkette;
    }

    double loantype(account);

    double updateloan(account);

    void removebal(double w)
    {
        balance=balance-w;
    }

    void assignloanamt(double dude)
    {
        loanamt=dude;
    }

    void setreturnamt(double xyz)
    {
        returnamt=xyz;
    }

    void setbal(double w)
    {
        balance=w;
    }

    double returnloanamt()
    {
        return loanamt;
    }

    double returnreturnamt()
    {
        return returnamt;
    }

    void getbal()                                         //Function to input balance
    {
        cin>>balance;
    }

    void showbal()                                       //Function to show balance
    {
        cout<<balance;
    }

    void addbal(double d)
    {
        balance=balance+d;
    }

    void assignreturnamt(double eye,float ear,int nose)
    {
        double i,w;
        i=(eye*ear*nose)/100;
        w=eye+i;
        returnamt=ceil(w);
    }

    //-------------------------------------------------------------------------------------------------------------

} a;

void account::setmainpass(char book[])
{
    for(int i=0; book[i]!='\0'; ++i)
        mainpass[i]=book[i];
}

void account::assignacno()                                       //Function to assign Bank Account Number
    {
        int flagpost=0;
assign_accno:
        randomize();        
        num=randomnumgenerator()+random(2000)+40000;;
        fstream checkit;
        account tempacc;
        checkit.open("acc.dat",ios::binary | ios::in);
        while(checkit.read((char*)&tempacc,sizeof(tempacc)))
        {
        	if(tempacc.returnnum()==num)
        		{
        			flagpost=1;
        			break;
        		}	
        }
        if(flagpost==1)
        {
        	flagpost=0;
        	checkit.close();
        	goto assign_accno;
        }
    }

void account::assingatmcdno()                           //Function to assign iATM Card Number
    {
        int flagpost=0;
assign_atmcdno:
        randomize();        
        atmcdno=randomnumgenerator()+random(40000)+40000;
        fstream checkit;
        account tempacc;
        checkit.open("acc.dat",ios::binary | ios::in);
        while(checkit.read((char*)&tempacc,sizeof(tempacc)))
        {
        	if(tempacc.returnatmcdno()==atmcdno)
        		{
        			flagpost=1;
        			break;
        		}	
        }
        if(flagpost==1)
        {
        	flagpost=0;
        	checkit.close();
        	goto assign_atmcdno;
        }
    }

void account::getdob()
{
    int ask;
    time_t t=time(0);
    struct tm* now=localtime(&t);
    cout<<"\nEnter Year: ";
    cin>>byear;
    if((byear>((now->tm_year)+1900-10)) || (byear<((now->tm_year)+1900)-168))
    	{
    		cout<<"\nYour birth year do not meet the required criteria.";
    		cout<<"\nGoing Back to the Main Homepage.";
    		jiofi=3;
    		return;
        }
Invalidity1:
    cout<<"\nSelect Birth Month: "<<endl<<endl
        <<"1.  January   2.  February   3.  March"<<endl
        <<"4.  April     5.  May        6.  June"<<endl
        <<"7.  July      8.  August     9.  September"<<endl
        <<"10. October   11. November   12. December"<<endl<<endl
        <<"Mark your response: ";
    cin>>ask;
    if(ask<1 || ask>12)
    {
        cout<<"Invalid Month. Enter again.";
        delay(1500);
        goto Invalidity1;
    }
    switch(ask)
    {
    case 1:
        strcpy(bmonth,"January");
        limit=31;
        break;
    case 2:
        strcpy(bmonth,"February");
        if(byear%4==0)
            limit=29;
        else
            limit=28;
        break;
    case 3:
        strcpy(bmonth,"March");
        limit=31;
        break;
    case 4:
        strcpy(bmonth,"April");
        limit=30;
        break;
    case 5:
        strcpy(bmonth,"May");
        limit=31;
        break;
    case 6:
        strcpy(bmonth,"June");
        limit=30;
        break;
    case 7:
        strcpy(bmonth,"July");
        limit=31;
        break;
    case 8:
        strcpy(bmonth,"August");
        limit=31;
        break;
    case 9:
        strcpy(bmonth,"September");
        limit=30;
        break;
    case 10:
        strcpy(bmonth,"October");
        limit=31;
        break;
    case 11:
        strcpy(bmonth,"November");
        limit=30;
        break;
    case 12:
        strcpy(bmonth,"December");
        limit=31;
        break;
    }

Invalidity2:
    cout<<"\nEnter Day: ";
    cin>>bday;
    cout<<endl;
    if(bday<1 || bday>limit)
    {
        cout<<"\nInvalid Entry.Enter Again";
        goto Invalidity2;
    }

}

void account::getphone()
{

    cout<<"Enter Phone number (*Please do not press enter*): +91 ";
    int i=0;
    char a;
    for(i=0; i<10;)
    {
        a=getch();
        if((a>='0'&&a<='9'))

        {
            contactno[i]=a;
            ++i;
            cout<<a;
        }
        if(a=='\b'&& i>=1)
        {
            cout<<"\b \b";
            --i;
        }
    }
    contactno[11]='\0';
    delay(256);
}

void account::getname()
{
    gets(name);
    for(int start=0; name[start]!='\0'; ++start)
    {
        name[start]=toupper(name[start]);
    }
}

void account::createnotif()
{
    for(int m=0; m<5; ++m)
    {
        notif[m]=name[m];
    }
    notif[5]='n';
    notif[6]='o';
    notif[7]='t';
    notif[8]='i';
    notif[9]='f';
    notif[10]='.';
    notif[11]='t';
    notif[12]='x';
    notif[13]='t';
    notif[14]='\0';
}

char* account::updatepass(account den)
{
    cout<<"\nEnter current password: ";
    char ghoul[17];
    char zeno[17];
    int i=0;
    char a;
    for(i=0; i<17;)
    {
        a=getch();
        if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9')||(a=='@')||(a=='(')||(a==')')||(a=='#')||(a=='!')||(a=='*')||(a=='+')||(a=='-')||(a=='/')||(a==':')||(a=='?')||(a=='='))

        {
            ghoul[i]=a;
            ++i;
            cout<<"*";
        }
        if(a=='\b'&& i>=1)
        {
            cout<<"\b \b";
            --i;
        }
        if(a=='\r')
        {
            ghoul[i]='\0';
            break;
        }
    }
    if(!strcmp(ghoul,mainpass))
    {

        char fmab[17],sher[17];
        do
        {

lenovo2:
            cout<<"\nEnter new password(It) must be between 8 to 16 digits): ";


            for(i=0; i<17;)
            {
                a=getch();
                if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9')||(a=='@')||(a=='(')||(a==')')||(a=='#')||(a=='!')||(a=='*')||(a=='+')||(a=='-')||(a=='/')||(a==':')||(a=='?')||(a=='='))

                {
                    fmab[i]=a;
                    ++i;
                    cout<<"*";
                }
                if(a=='\b'&& i>=1)
                {
                    cout<<"\b \b";
                    --i;
                }
                if(a=='\r')
                {
                    fmab[i]='\0';
                    break;
                }
            }
            if(strlen(fmab)<8)
            {
                cout<<"\nPassword do match required conditions of size!\nPlease enter again"<<endl;
                delay(1500);
                goto lenovo2;
            }
            cout<<"\nConfirm Password: ";
            for(i=0; i<17;)
            {
                a=getch();
                if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9')||(a=='@')||(a=='(')||(a==')')||(a=='#')||(a=='!')||(a=='*')||(a=='+')||(a=='-')||(a=='/')||(a==':')||(a=='?')||(a=='='))

                {
                    sher[i]=a;
                    ++i;
                    cout<<"*";
                }
                if(a=='\b'&& i>=1)
                {
                    cout<<"\b \b";
                    --i;
                }
                if(a=='\r')
                {
                    sher[i]='\0';
                    break;
                }
            }
            if(!strcmp(sher,fmab))
            {
                den.setmainpass(fmab);
                strcpy(zeno,den.returnmainpass());
                clrscr();
                cout<<"\n\tPassword Changed Succesfully."<<endl;
                delay(1400);
                cout<<"\n\tPLEASE LOGIN AGAIN"<<endl;
                delay(1400);
            }
            else
            {
                cout<<"\nPasswords Do Not Match!\nPlease enter again."<<endl;
                delay(1000);
            }
        } while(strcmp(sher,fmab));

        return zeno;
    }
    else
    {
        cout<<"\nPassword is incorret!\nTaking you back to the account home."<<endl;
        delay(1500);
        strcpy(zeno,mainpass);
        return zeno;
    }
}

account b,c,dnd;

void main()
{
    clrscr();

    fstream x1,x2,x3,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,code,geass,temp,dbs,loa;
    ifstream fin;
    int resp2,countx=0,i3=0,i4=0,i5=0,i6=0,i7=0,i8=0,i9=0,i10,i11=0,i13=0,count,count1,adac,resp3,resp4,resp5,resp6,resp7;
    long int i2,i12;
    streampos n,n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12,n13,n14;
    double amt,f1=0.0;
    char str[128],iit[32],ask;

    long int upass,uac;
    int countxy= 0;
    void line(int);

home:
    clrscr();
    line(3);

    cout<<"                BHARAT BANK ACCOUNT SERVICE DATABASE               "<<endl;
    cout<<"       -----------------------------------------------------        "<<endl;

    line(2);

    cout <<"1. SIGN IN"<<endl
         <<"2. SIGN UP"<<endl
         <<"3. iATM SERVICE"<<endl
         <<"4. ADMIN ACCESS ZONE"<<endl
         <<"5. READ TERMS & CONDITIONS"<<endl
         <<"6. QUIT"<<endl<<endl
         <<"Please select an option: ";


    int resp1;
    cin >> resp1;

    clrscr();

    switch (resp1)
    {
    case 1:

retry:

        line(3);
        cout<<"Enter your account number: ";
        cin>>uac;

        count = 0;
        x13.open("o.dat", ios::binary | ios::in);
        while(x13.read((char*)&a,sizeof(a)))
        {
            if(uac==a.returnnum())
            {
                ++count;
            }
        }
        x13.close();

        if (count==0)
        {
            cout<<"Account does not exists!";
            delay(700);
            goto home;
        }


        //SIGN IN

        clrscr();
        line(4);


        x2.open("o.dat", ios::binary | ios::in | ios::out | ios::app);
        while (x2.read((char*)&a, sizeof(a)))
        {
            if (uac==a.returnnum())
            {
                cout<<"Enter password to continue: ";
                char checkpass2[17];
                int i=0;

                char a2;
                for(i=0; i<17;)
                {
                    a2=getch();
                    if((a2>='a'&& a2<='z')||(a2>='A'&&a2<='Z')||(a2>='0'&&a2<='9')||(a2=='@')||(a2=='(')||(a2==')')||(a2=='#')||(a2=='!')||(a2=='*')||(a2=='+')||(a2=='-')||(a2=='/')||(a2==':')||(a2=='?')||(a2=='='))

                    {
                        checkpass2[i]=a2;
                        ++i;
                        cout<<"*";
                    }
                    if(a2=='\b'&& i>=1)
                    {
                        cout<<"\b \b";
                        --i;
                    }
                    if(a2=='\r')
                    {
                        checkpass2[i]='\0';
                        break;
                    }
                }
                if((!strcmp(checkpass2,a.returnmainpass())) && a.returnstatus()==0)
                {
                    clrscr();
                    line(3);

                    cout<<setw(8)<<" WELCOME ";
mat:
                    a.showname();
                    cout<<setw(8)<<"\n\nAccount Number: ";
                    cout<<a.returnnum();
                    cout<<endl;
                    x2.close();
                    delay(2000);

                }
                else if(a.returnstatus()==1)
                {
                    cout<<"\nACCOUNT BLOCKED !" << endl;
                    x2.close();
                    delay(1500);
                    goto home;
                }
                else
                {
                    cout<<"\nWRONG PASSWORD !"<<endl;
                    x2.close();
                    delay(1500);
                    goto home;
                }
                break;
            }
        }

bat:
        clrscr();
        cout<<"              ACCOUNT HOME             "<< endl;
        cout<<"         -----------------------       "<< endl;
        line(1);
        code.open("o.dat"  , ios::binary | ios::in );
        code.seekg(0);
        while(code.read((char*)&dnd,sizeof(dnd)))
        {
            if(dnd.returnnum()==uac)
            {
                if(dnd.notifs==0)
                {
                    cout<<"No New Notification(s)"<<endl;
                }
                else
                {
                    cout<<dnd.notifs<<" UNSEEN Notifications"<<endl;
                }

                line(2);
                cout<<"\n1. DEPOSIT"<<endl
                    <<"2. NEFT TRANSACTION"<<endl
                    <<"3. GET LOAN"<<endl
                    <<"4. PAYBACK LOAN"<<endl
                    <<"5. CHANGE ACCOUNT PASSWORD"<<endl
                    <<"6. GET ACCOUNT & LOAN DETAILS"<<endl;
                if(dnd.notifs!=0)
                {
                    cout<<"7. View Notifications"<<endl
                        <<"8. SIGN OUT"<<endl<<endl;
                }
                else if(dnd.notifs==0)
                {
                    cout<<"7. SIGN OUT"<<endl<<endl;
                }

                cout<<"Please select an option: ";
            }
        }
        code.close();

        cin>>resp2;
        cout<<endl;
        switch(resp2)
        {


        case 1:       //DEPOSIT


            x7.open("o.dat", ios::binary | ios::in);
            while(x7.read((char*)&a, sizeof(a)))
            {
                if(a.returnnum()==uac)
                {
                    break;
                }
                ++i9;
            }

            n2=i9*sizeof(a);
            x7.close();
            x8.open("o.dat", ios::binary | ios::in | ios::out);
            x8.seekp(n2);
dell:
            do
            {
                cout<<"Enter amount to deposit: Rs. ";
                cin>>amt;
                if(amt<100)
                {
                    cout<<"Minimum amount to deposit = Rs 100"<<endl;
                    char apple;
                    cout<<"Do you want to try again ?(Y/N)"<<endl;
                    cin>>apple;
                    if(apple=='Y'||apple=='y')
                        goto dell;
                    else
                    {
                        i9=0;
                        break;
                    }
                }
            } while(amt<100);
            a.addbal(amt);
            x8.write((char*)&a, sizeof(a));
            i9=0;
            cout<<amt<<" have been deposited to your account." << endl;
            x9.open("loan.dat",ios::binary | ios::in);
            while(x9.read((char*)&c, sizeof(c)))
            {
                if(c.returnnum()==uac)
                {
                    break;
                }
                ++i6;
            }
            n8=i6*sizeof(c);
            int asphalt=0;
            x9.close();
            x9.open("loan.dat",ios::binary | ios::in);
            while(x9.read((char*)&b,sizeof(b)))
            {
                if(uac==b.returnnum())
                    asphalt=5;
            }
            x9.close();
            if(asphalt==5)
            {
                x14.open("loan.dat",ios::binary | ios::out | ios::in);
                x14.seekg(n8);
                x14.read((char*)&b,sizeof(b));
                b.addbal(amt);
                x14.seekp(n8);
                x14.write((char*)&b,sizeof(b));
                x14.close();
            }
            i6=0;
            asphalt=0;
            randomize();
            tid=random(9)+random(99)+random(999)+random(9999)+random(468676);
            cout<<"\nTransaction successful.\nTransaction ID: "<<tid<<endl;
            cout<<"New Balance: ";
            a.showbal();
            line(2);
            timesave(tid,amt,a.name,a.returnnum(),"Money Deposit");
            x8.close();
            system("pause");
            clrscr();
            goto bat;



        case 2:              //NEFT TRANSACTION


            clrscr();
            line(1);
            cout<<setw(5)<<"           NEFT TRANSFER WINDOW     "<<endl;
            cout<<"*****---------------------------------------*****"<<endl;
            line(3);
            x9.open("o.dat", ios::binary | ios::in );
            while (x9.read((char*)&a, sizeof(a)))
            {
                if(uac==a.returnnum())
                {
                    break;
                }
                i11++;
            }
            n3=i11*sizeof(a);
            x9.close();
            geass.open("o.dat", ios::binary | ios::in);
            geass.seekg(n3);
            geass.read((char*)&c,sizeof(c));
            char punt;
            do
            {

                cout<<setw(10)<<"\n Enter amount to transfer: RS ";
                cin>>f1;
                if(f1>(c.returnbalance()-1001))
                {
                    clrscr();
                    line(1);
                    cout<<"\n         INSUFFICIENT BALANCE !\nAmount to be transfered should be Rs 1001 less than account balance.";
                    cout<<"\n\nTRY AGAIN  or  EXIT from NEFT Transfer Window.";
                    cout<<"\nWant to exit(Y/N): ";
                    cin>>punt;
                    line(1);
                    if((punt=='Y')||(punt=='y'))
                    {
                        geass.close();
                        i11=0;
                        goto bat;
                    }
                }
            } while(f1>(c.returnbalance()-1001));
            geass.close();
            cout<<"\nEnter Recipient Name: ";
            gets(neftname);
            do
            {


                cout<<"\nEnter Recipient Account Number: ";
                cin>>i12;
                cout<<"Confirm  Account  Number :      ";
                cin>>i2;


                if(i12!=i2)
                {
                    cout<<"\nAccount Numbers don't match!\nPlease enter AGAIN  or  EXIT."<<endl;
                    delay(310);
                    cout<<"\nWant to Exit from NEFT Transfer Window(Y/N): ";
                    cin>>ask;
                    if((ask=='Y')||(ask=='y'))
                        goto bat;
                }
            } while(i12!=i2);
            cout<<"\nEnter Recipient IFSC code: ";
            gets(iit);

            x10.open("o.dat", ios::binary | ios::in | ios::out);
            x10.seekg(n3);
            x10.read((char*)&a, sizeof(a));
            a.removebal(f1);
            x10.seekp(n3);
            x10.write((char*)&a, sizeof(a));
            x10.close();

            int asphalt2=0;
            int asphalt3=0;

            x9.open("loan.dat",ios::binary | ios::in);
            while(x9.read((char*)&b, sizeof(b)))
            {
                if(uac==b.returnnum())
                {
                    asphalt2=5;
                    break;
                }
                ++i5;
            }
            n10=i5*sizeof(b);
            x9.close();

            if(asphalt2==5)
            {
                x14.open("loan.dat",ios::binary | ios::out | ios::in);
                x14.seekg(n10);
                x14.read((char*)&b,sizeof(b));
                b.removebal(f1);
                x14.seekp(n10);
                x14.write((char*)&b,sizeof(b));
                x14.close();
            }
            i5=0;
            asphalt2=0;

            x11.open("o.dat", ios::binary | ios::in | ios::out );
            while(x11.read((char*)&c, sizeof(c)))
            {
                if(i12==c.returnnum())
                {
                    share=1;
                    break;
                }
                i13++;
            }
            n4=i13*sizeof(c);
            x11.close();
            if(share==1)
            {

                x12.open("o.dat", ios::binary | ios::out | ios::in);
                x12.seekg(n4);
                x12.read((char*)&c,sizeof(c));
                x12.seekp(n4);
                c.addbal(f1);
                randomize();
                tid=random(9)+random(99)+random(999)+random(9999)+random(468676);
                x12.write((char*)&c,sizeof(c));
                x12.close();
                x10.open("o.dat",ios::binary | ios::in);
                x10.seekg(n3);
                x10.read((char*)&a,sizeof(a));
                notifwrite(tid,f1,a.name,a.returnnum(),c.notifs,c.notif,"MONEY RECIEVED FROM NEFT TRANSACTION");
                x10.close();
                x12.open("o.dat", ios::binary | ios::out | ios::in);
                x12.seekg(n4);
                x12.read((char*)&c,sizeof(c));
                ++c.notifs;
                x12.seekp(n4);
                x12.write((char*)&c,sizeof(c));
                x12.close();

                i13=0;
                i11=0;

                x9.open("loan.dat",ios::binary | ios::in);
                while(x9.read((char*)&b, sizeof(b)))
                {
                    if(i12==b.returnnum())
                    {
                        asphalt3=5;
                        break;
                    }
                    ++i3;
                }
                n12=i3*sizeof(b);
                x9.close();

                if(asphalt3==5)
                {
                    x14.open("loan.dat",ios::binary | ios::out | ios::in);
                    x14.seekg(n12);
                    x14.read((char*)&b,sizeof(b));
                    b.addbal(f1);
                    x14.seekp(n12);
                    x14.write((char*)&b,sizeof(b));
                    x14.close();
                }
                i3=0;
                asphalt3=0;

                x10.open("o.dat",ios::binary | ios::in);
                x10.seekg(n3);
                x10.read((char*)&a,sizeof(a));
                timesave(tid,f1,a.name,a.returnnum(),"NEFT TRANSACTION");
                timesave(tid,f1,neftname,i12,"MONEY RECIEVED FROM NEFT");
                x10.close();
                cout<<"\nTransaction successful.\nTransaction ID: "<<tid<<endl;
                cout<<"New Balance: ";
                a.showbal();
                line(2);
                system("pause");
                clrscr();
                share=0;
                goto bat;
            }
            else
            {
                share=0;
                tid=random(9)+random(99)+random(999)+random(9999)+random(468676);
                cout<<"Transaction successful.\nAmount Transfered to bank account of another bank.\nTransaction ID: "<<tid<<endl;
                cout<<"\nPlease Note the Transaction ID for future reference as it will not be stored in our system.";
                line(2);
                system("pause");
                clrscr();
                goto bat;
            }



        case 3:  //GET LOAN


            int flag=0;
            code.open("loan.dat",ios::binary | ios::in);
            while(code.read((char*)&a,sizeof(a)))
            {
                if(a.returnnum()==uac)
                    flag=1;
            }
            code.close();
            if(flag==1)
            {
                clrscr();
                cout<<"You have already taken a loan. Please pay off the curent loan to take another."<<endl;
                delay(2000);
                goto bat;
            }
            else
            {
                int instinct=0; 
                code.open("o.dat",ios::binary | ios::in);                                          //Copying Data from o.dat to loan.dat
                geass.open("loan.dat",ios::binary | ios::in | ios::out | ios::app);
                while(code.read((char*)&a,sizeof(a)))
                {
                    if(uac==a.returnnum())
                    {
                        geass.write((char*)&a,sizeof(a));
                        break;
                    }
                }
                code.close();
                geass.close();
                code.open("loan.dat",ios::binary | ios::in |ios::out);
                while(code.read((char*)&a,sizeof(a)))
                {
                    if(uac==a.returnnum())
                    {
                        break;
                    }
                    ++instinct;
                }
                code.close();
                code.open("loan.dat",ios::binary | ios::in |ios::out);
                n1=instinct*sizeof(a);
                code.seekp(n1);
                a.assignloanamt(a.loantype(a));
                if(a.returnloanamt()>0)
                {
                    switch(choiceloan)
                    {
                    case 1:
                        strcpy(a.loanname,"PERSONAL LOAN");
                        break;
                    case 2:
                        strcpy(a.loanname,"EDUCATIONAL LOAN");
                        break;
                    case 3:
                        strcpy(a.loanname,"PROPERTY LOAN");
                        break;
                    case 4:
                        strcpy(a.loanname,"VEHICLE LOAN");
                        break;
                    }
                    a.loandurmonth=loandurmonths;
                    switch(choiceloan)
                    {
                    case 1:
                        a.setinterest(intper);
                        break;
                    case 2:
                        a.setinterest(intedu);
                        break;
                    case 3:
                        a.setinterest(intprop);
                        break;
                    case 4:
                        a.setinterest(intveh);
                        break;
                    }
                    a.assignreturnamt(a.returnloanamt(),a.returninterest(),a.loandurmonth);
                    code.write((char*)&a,sizeof(a));
                    clrscr();
                    cout<<"\nLoan Taken Succesfully"<<endl;
                    cout<<"*----------------------------------------*"<<endl;
                    line(3);
                    cout<<"NAME:             ";
                    puts(a.name);
                    cout<<"ACCOUNT NUMBER:   "<<a.returnnum()<<endl
                        <<"LOAN TYPE:        ";
                    puts(a.loanname);
                    cout<<"LOAN PRINCIPLE:   Rs "<<a.returnloanamt()<<endl
                        <<"INTEREST RATE:    "<<(a.returninterest()*12)<<" per annum"<<endl
                        <<"LOAN DURATION:    "<<a.loandurmonth<<" months";
                    cout<<"\nLOAN AMOUNT:      Rs "<<a.returnreturnamt()<<endl;
                    line(2);
                    system("pause");
                    code.close();
                    goto bat;
                }
                else
                {
                    code.close();
                    code.open("ltemp.dat",ios::binary | ios::in | ios::out);
                    geass.open("loan.dat",ios::binary | ios::in);
                    while(geass.read((char*)&a,sizeof(a)))
                    {
                        if(uac!=a.returnnum())
                        {
                            code.write((char*)&a,sizeof(a));
                        }
                    }
                    code.close();
                    geass.close();
                    remove("loan.dat");
                    rename("ltemp.dat","loan.dat");
                    char spd[40];
                    clrscr();
                    line(3);
                    strcpy(spd,"Returning back to the Account Home.");
                    for(int i=0; spd[i]!='\0'; ++i)
                    {
                        cout<<spd[i];
                        delay(111);
                    }
                    delay(531);
                    goto bat;
                }
            }

        case 4:  //PAYBACK LOAN

            int flag2=0;
            int faded=0;
            x17.open("loan.dat",ios::binary | ios::in);
            while(x17.read((char*)&a,sizeof(a)))
            {
                if(uac==a.returnnum())
                {
                    flag2=1;
                    break;
                }
                ++faded;
            }
            x17.close();
            if(flag2==0)
            {
                clrscr();
                cout<<setw(4)<<"\n\n\n***---There is NO ONGOING LOAN PAYMENT against you.---***"<<endl;
                delay(2000);
                flag2=0;
                goto bat;
            }
            else
            {
                int chand=0;
                n5=faded*sizeof(a);
                loa.open("loan.dat",ios::binary | ios::in | ios::out);
                loa.seekg(n5);
                loa.read((char*)&a,sizeof(a));
                a.setreturnamt(a.updateloan(a));
                a.removebal(universe);
                loa.seekp(n5);
                loa.write((char*)&a,sizeof(a));
                x11.open("o.dat",ios::binary | ios::in);
                while(x11.read((char*)&b,sizeof(b)))
                {
                    if(uac==b.returnnum())
                    {
                        break;
                    }
                    ++ chand;
                }
                n7=chand*sizeof(b);
                x11.close();
                x12.open("o.dat",ios::binary | ios::in | ios::out );
                x12.seekg(n7);
                x12.read((char*)&b,sizeof(b));
                b.removebal(universe);
                x12.seekp(n7);
                x12.write((char*)&b,sizeof(b));
                loa.close();
                x12.close();
                universe=0.0;
                if(manas==1)
                {
                    x17.open("loan.dat", ios::binary | ios::in );
                    temp.open("pop.dat",ios::binary | ios::out);
                    while(x17.read((char*)&a,sizeof(a)))
                    {
                        if(uac!=a.returnnum())
                            temp.write((char*)&a,sizeof(a));
                    }
                    x17.close();
                    temp.close();
                    remove("loan.dat");
                    rename("pop.dat","loan.dat");
                }
                else if(manas==55)
                {
                    flag2=0;
                    goto bat;
                }
                flag2=0;
                goto bat;
            }

        case 5:

            //CHANGE PASSWORD

            x3.open("o.dat", ios::binary | ios::in | ios::out | ios::app);
            while(x3.read((char*)&a,sizeof(a)))
            {
                if(uac==a.returnnum())
                {
                    break;
                }
                ++i7;
            }
            x3.close();
            n=i7*sizeof(a);
            x5.open("o.dat", ios::binary | ios::in | ios::out);
            x5.seekp(n);
            a.setmainpass(a.updatepass(a));
            x5.write((char*)&a, sizeof(a));
            x5.close();
            goto home;


        case 6: //ACCOUNT DETAILS
        {

            dbs.open("o.dat",ios::binary | ios::in | ios::out);
            while (dbs.read((char*)&a, sizeof(a)))
            {
                if(uac==a.returnnum())
                {
                    int flag3=0;
                    int logic=0;
                    code.open("loan.dat",ios::binary | ios::in);
                    code.seekp(0);
                    while(code.read((char*)&b,sizeof(b)))
                    {
                        if(uac==b.returnnum())
                        {
                            flag3=1;
                            break;
                        }
                        ++logic;
                    }
                    n6=logic*sizeof(b);
                    code.seekg(n6);         
                    clrscr();
                    cout<<"         *******USER DETAILS PAGE********"<<endl;
                    cout<<"*****----------------------------------------------*****"<<endl;
                    line(1);
                
                    cout<<"User Name: ";
                    puts(a.name);
                    
                    cout<<"DOB: "<<a.bday<<" "<<a.bmonth<<" "<<a.byear<<endl;
                    cout<<"Contact Number: +91 ";
                    for(int pacman=0; pacman<10; ++pacman)
                    {
                        cout<<a.contactno[pacman];
                    }
                    cout<<"\nAddress: ";
                    puts(a.address);
                    cout<<"Account Number: "<<a.returnnum()<<endl;
                    cout<<"iATM CARD Number: "<<a.returnatmcdno()<<endl;
                    cout<<"Withdrawlable Balance: "<<a.returnbalance()-1001<<endl;
                    cout<<"Security Deposit: "<<1001<<endl;
                    if(flag3==1)
                    {
                        line(1);
                        cout<<setw(5)<<"\nLOAN DETAILS"<<endl<<endl;
                        cout<<"LOAN TYPE:               ";
                        puts(b.loanname);
                        cout<<"LOAN PRINCIPLE:          Rs "<<b.returnloanamt()<<endl
                            <<"INTEREST RATE:           "<<b.returninterest()*12<<" per annum"<<endl
                            <<"LOAN DURATION:           "<<b.loandurmonth<<" months";
                        cout<<"\nLOAN AMOUNT REMAINING:   Rs "<<b.returnreturnamt()<<endl;
                        cout<<"***----------------------------------------***"<<endl;
                        line(2);
                        system("pause");
                        code.close();
                        dbs.close();
                        goto bat;
                    }
                    else
                    {
                        cout<<"\nNO LOAN AGAINST YOU."<<endl;
                        line(2);
                        system("pause");
                        code.close();
                        dbs.close();
                        goto bat;
                    }
                }

            }

        }
        case 7:    //VIEW NOTIFICATIONS

        {
            int w=0;
            streampos water;
            x14.open("o.dat",ios::binary | ios::in);
            while(x14.read((char*)&a,sizeof(a)))
            {
                if(a.returnnum()==uac)
                    break;
                ++w;
            }
            water=w*sizeof(a);
            x14.close();
            x9.open("o.dat",ios::binary | ios::in |ios::out);
            x9.seekg(water);
            x9.read((char*)&a,sizeof(a));
            if(a.notifs==0)
                goto home;
            else
            {

                clrscr();
show_n_again:
                char cha;
                fin.open(a.notif);
                cha=fin.get();
                while(!fin.eof())
                {
                    cout<<cha;
                    if(cha=='$')
                    {

                        cout<<endl;
                        line(1);
                        system("pause");
                        cout<<endl;
                    }
                    cha=fin.get();
                }
                fin.close();
                x9.close();
                clrscr();
                line(2);
                cout<<"All Notifications Shown."<<endl;
                x9.open("o.dat",ios::binary | ios::in | ios::out );
                x9.seekg(water);
                x9.read((char*)&a,sizeof(a));
                a.notifs=0;
                x9.seekp(water);
                x9.write((char*)&a,sizeof(a));
                x9.close();
                cout<<"Want to view again(Y/N) ?"<<endl;
                ask=getch();
                if(ask=='Y'||ask=='y')
                {
                    clrscr();
                    goto show_n_again;
                }
                fin.open(a.notif, ios::out | ios::trunc);
                fin.close();
                goto bat;
            }
        }


        case 8:
            int f=0;
            streampos food;
            x14.open("o.dat",ios::binary | ios::in);
            while(x14.read((char*)&a,sizeof(a)))
            {
                if(a.returnnum()==uac)
                    break;
                ++f;
            }
            food=f*sizeof(a);
            x14.close();
            x14.open("o.dat",ios::binary | ios::in);
            x14.seekg(food);
            x14.read((char*)&a,sizeof(a));
            if(a.notifs!=0)
            {
                x14.close();
                goto home;
            }
            else
            {
                x14.close();
                goto go8;
            }

        default:

go8:
            cout << "Invalid response!";
            delay(1000);
            goto bat;

        }

    case 2:

        //ACCOUNT SETUP/SIGN UP

        clrscr();
        line(3);

        cout<<"              SIGNING UP         "<< endl;
        cout<<"          ------------------     "<< endl;

        line(2);

        x1.open("o.dat",ios::binary | ios::in | ios::out);                               //Copying Data from o.dat to temporary file acc.dat
        x2.open("acc.dat",ios::binary | ios::in | ios::out);                                          
        while(x1.read((char*)&a,sizeof(a)))
        {
            x2.write((char*)&a,sizeof(a));
            break;
        }
        x1.close();
        x2.close();


        x1.open("o.dat", ios::binary | ios::in | ios::out | ios::app);
  tommy:     
        
        cout<<"\n***--ACCOUNT CREATION PAGE--***"<<endl<<endl;
        delay(64);
        a.assignacno();
        int hilfiger=0;
        if(hilfiger==1)
           clrscr();
        hilfiger=0;     
        cout<<"\nEnter name: ";
        a.getname();
        for(int iname=0 ; a.name[iname]!='\0'; ++iname)
         {
         	if((!isalpha(a.name[iname]) && (a.name[iname]!=' ') ) || (a.name[0]==' '))
         		hilfiger=1;
         }
         if(hilfiger==1)
         {
         	cout<<"\nInvalid Name Type !";
         	delay(1300);
         	clrscr();
         	goto tommy;
         }
        delay(256);
        clrscr();
        cout<<"\n***----- Date of Birth Entry -----***";
        a.getdob();
        if(jiofi==3)
        {
            jiofi=0;
            system("pause");
            x1.close();
        	goto home;
        }
        a.getphone();                                                   //Function gets phone number from user
        cout<<"\nEnter Address: ";
        char a55;
        for(int i=0; i<150;)
            {
                a55=getch();
			if((a55>='a'&&a55<='z')||(a55>='A'&&a55<='Z')||((a55==' ')&&i>=1)||(a55>='0'&&a55<='9')||(a55=='@')||(a55==',')||(a55=='(')||(a55==')')||(a55=='#')||(a55=='!')||(a55=='*')||(a55=='+')||(a55=='-')||(a55=='/')||(a55==':')||(a55=='?')||(a55=='='))
                {
                    a.address[i]=a55;
                    ++i;
                    cout<<a55;
                }
                if(a55=='\b'&& i>=1)
                {
                    cout<<"\b \b";
                    --i;
                }
                if(a55=='\r' && i>=1)
                {
                    a.address[i]='\0';
                    break;
                }
            }
        clrscr();
        line(2);
        char checkpass[16],checkpass3[16];

        do
        {

lenovo:
            clrscr();
            line(2);
            cout<<"Enter Password(Password must be between 8-16 digits): ";
            char a3;
            for(int i=0; i<17;)
            {
                a3=getch();
                if((a3>='a'&&a3<='z')||(a3>='A'&&a3<='Z')||(a3>='0'&&a3<='9')||(a3=='@')||(a3=='(')||(a3==')')||(a3=='#')||(a3=='!')||(a3=='*')||(a3=='+')||(a3=='-')||(a3=='/')||(a3==':')||(a3=='?')||(a3=='='))

                {
                    checkpass[i]=a3;
                    ++i;
                    cout<<"*";
                }
                if(a3=='\b'&& i>=1)
                {
                    cout<<"\b \b";
                    --i;
                }
                if(a3=='\r')
                {
                    checkpass[i]='\0';
                    break;
                }
            }
            if(strlen(checkpass)<8)
            {
                cout<<"\nPassword do match required conditions of size!\nPlease enter again."<<endl;
                delay(1500);
                goto lenovo;
            }
            cout<<"\nConfirm Password:  ";
	    for(i=0; i<17;)
	    {
		a3=getch();
		if((a3>='a'&&a3<='z')||(a3>='A'&&a3<='Z')||(a3>='0'&&a3<='9')||(a3=='@')||(a3=='(')||(a3==')')||(a3=='#')||(a3=='!')||(a3=='*')||(a3=='+')||(a3=='-')||(a3=='/')||(a3==':')||(a3=='?')||(a3=='='))

		{
		    checkpass3[i]=a3;
		    ++i;
                    cout<<"*";
                }
                if(a3=='\b'&& i>=1)
                {
                    cout<<"\b \b";
                    --i;
                }
                if(a3=='\r')
                {
                    checkpass3[i]='\0';
                    break;
                }
            }
            if(!strcmp(checkpass3,checkpass))
                a.setmainpass(checkpass);
            else
            {
                clrscr();
                cout<<"\nPasswords Do Not Match!\nPlease enter again or exit."<<endl;
                delay(1000);
                cout<<"Want to exit(Y/N): ";
                char intel;
                cin>>intel;
                if(intel=='y'||intel=='Y')
                    {
                    	x1.close();
                    	remove("acc.dat");
                    	goto home;
                    }	
            }
        } while(strcmp(checkpass3,checkpass));

        clrscr();
        line(3);
        do
        {
            cout<<"\nPlease deposit Rs 1001 as security money.\nYou can deposit more than this amount."
                <<"\nYour account balance must be more than Rs 1000 always."<<endl
                <<"\nAmount to be deposited: Rs. ";
            cin>>money;
            line(1);
            char comp;
            if(money>1000)
            {
                a.setbal(0.0);
                a.addbal(money);
                cout<<"\nAmount added successfully to balance."<<endl
                    <<"You can only withdraw this amount on closing the bank account."<<endl;
                randomize();
                tid=random(9)+random(99)+random(999)+random(9999)+random(468676);
                cout<<"\nTransaction successful.\nTransaction ID: "<<tid<<endl;
                timesave(tid,money,a.name,a.returnnum(),"MONEY DEPOSITION AT ACC CREATION");
                system("pause");
            }
            else
            {
                cout<<"\nPlease deposit an amount of more than Rs. 1000"<<endl;
                cout<<"Want to exit?(Y/N)"<<endl;
                cin>>comp;
                if(comp=='Y'||comp=='y')
                {
                    x1.close();
                    remove("acc.dat");
                    goto home;
                }
            }
        } while(money<=1000);
        a.assingatmcdno();
        a.createnotif();
        line(2);
        code.open(a.notif,ios::out);
        code.close();
        clrscr();
        x1.write((char*)&a,sizeof(a));
        clrscr();
        cout<<"    ********-----WELCOME TO BHARAT BANK-----*******"<<endl<<endl;
        cout <<"\nAccount creation successfull."
             <<"\nYour account number is: ";
        a.shownum();
        cout<<"\nYour IFSC code is : ";
        puts(ifsc);
        cout<<"YOUR ATM CARD NUMBER: "<<a.returnatmcdno();
        cout<<"\nUse the password for iATM also."<<endl;
        cout<<"\nPlease remember your password, account number and iATM card number."<<endl;
        cout<<endl;
        x1.close();
        system("pause");
        remove("acc.dat");
        goto home;

    case 3:       //ELECTRONIC ATM SERVICE

comedy:
        clrscr();
        cout<<"******BHARAT BANK ATM SERVICE******"<<endl
            <<"-----------------------------------"<<endl;
        line(2);
        cout<<"1. Withdraw Money"<<endl
            <<"2. Check Account Balance"<<endl
            <<"3. Exit"<<endl;
        cout<<"Chose an option: ";
        cin>>opt;
        cout<<endl;
        switch(opt)
        {
        case 1: {
            clrscr();
            countx=1;
            cout<<"\n\tEnter your atm card number: ";
	    cin>>cdno;
            geass.open("o.dat",ios::binary || ios::in ||ios::out);
            while(geass.read((char*)&a,sizeof(a)))
            {
                if(cdno==a.returnatmcdno())
                {
                    countx=0;
                    break;
                }
            }
            geass.close();
            if(countx==1)
            {
                cout<<"\n\tEntered Card Number is not associated to any account!";
                delay(1500);
                goto comedy;
            }
            line(1);

            code.open("o.dat", ios::binary | ios::in);
            while(code.read((char*)&a,sizeof(a)))
            {
                if(a.returnatmcdno()==cdno)
                {
                    break;
                }
                ++i8;
            }
            n11=i8*sizeof(a);
            code.close();
            code.open("o.dat",ios::binary | ios::in | ios::out);
            while (code.read((char*)&a, sizeof(a)))
            {

                char atmpass[17];

                if (cdno == a.returnatmcdno())
                {
                    cout<<"\n\tEnter password to continue: ";
                    char a5;
                    for(int i=0; i<17;)
                    {
                        a5=getch();
                        if((a5>='a'&&a5<='z')||(a5>='A'&&a5<='Z')||(a5>='0'&&a5<='9')||(a5=='@')||(a5=='(')||(a5==')')||(a5=='#')||(a5=='!')||(a5=='*')||(a5=='+')||(a5=='-')||(a5=='/')||(a5==':')||(a5=='?')||(a5=='='))

                        {
                            atmpass[i]=a5;
                            ++i;
                            cout<<"*";
                        }
                        if(a5=='\b'&& i>=1)
                        {
                            cout<<"\b \b";
                            --i;
                        }
                        if(a5=='\r')
                        {
                            atmpass[i]='\0';
                            break;
                        }
                    }
                    if ((!strcmp(atmpass,a.returnmainpass())) && a.returnstatus()==0)
                    {
                        clrscr();
                        line(3);
                        char gamma;
                        do
                        {
                        	cout<<setw(4)<<"   ***MONEY WITHDRAWL***"<<endl
                            <<"--------------------------------------"<<endl<<endl;
                            cout<<"\nName: ";
                            puts(a.name);
                            cout<<"Account Number: "<<a.returnnum()<<endl;
                            cout<<"ATM Card Number: "<<a.returnatmcdno();
                            line(3);
                            cout<<"Enter amount to withdraw: ";
                            cin>>atmmoney;
                            cout<<endl;
                            if ((atmmoney<a.returnbalance()-1000)&&(atmmoney<=15000))
                            {
                                code.seekg(n11);
                                a.removebal(atmmoney);
                                code.write((char*)&a,sizeof(a));
                                x9.open("loan.dat",ios::binary | ios::in);
                                while(x9.read((char*)&b, sizeof(b)))
                                {
                                    if(b.returnatmcdno()==cdno)
                                    {
                                        break;
                                    }
                                    ++i4;
                                }
                                n0=i4*sizeof(b);
                                int asphalt3=0;
                                x9.close();
                                x9.open("loan.dat",ios::binary | ios::out | ios::in);
                                while(x9.read((char*)&b,sizeof(b)))
                                {
                                    if(b.returnatmcdno()==cdno)
                                        asphalt3=5;
                                }
                                x9.close();
                                if(asphalt3==5)
                                {
                                    x14.open("loan.dat",ios::binary | ios::out | ios::in);
                                    x14.seekg(n0);
                                    x14.read((char*)&b,sizeof(b));
                                    b.removebal(atmmoney);
                                    x14.seekp(n0);
                                    x14.write((char*)&b,sizeof(b));
                                    x14.close();
                                }
                                i4=0;
                                asphalt3=0;
                                cout<<"Amount Withdrawn successfully."<<endl;
                                randomize();
                                tid=randomnumgenerator()+random(531);
                                cout<<"Transaction ID: "<<tid<<endl;
                                timesave(tid,atmmoney,a.name,a.returnnum(),"ATM WITHDRAWL");
				cout<<"Remaining Balance: Rs "<<a.returnbalance()<<endl;
                                system("pause");
                                i8=0;
                                code.close();
                                goto home;
                            }
                            else if((atmmoney>a.returnbalance()-1001)&&(atmmoney<=15000))
                            {
                                clrscr();
                                cout<<"\nInsufficient Balance!";
                                delay(500);
                                cout<<"\nWant to exit(Y/N): ";
                                cin>>gamma;
                                code.close();
                                if(gamma=='Y'||gamma=='y')
                                    goto comedy;
                            }
                            else
                            {
                                cout<<"Per day withdrawl cap is Rs 15000.";
                                code.close();
                                delay(300);
                                cout<<"\nWant to exit(Y/N): ";
                                cin>>gamma;
                                if(gamma=='Y'||gamma=='y')
                                    goto home;
                            }
                        } while((atmmoney>a.returnbalance()-1001)&&(atmmoney>15000));

                    }
                    else
                    {
			cout <<"\n\nWrong password or Account blocked!" << endl;
                        code.close();
                        delay(1500);
                        goto comedy;
                    }
                    break;
                }
            }
        }
        case 2: {
            clrscr();

            char atmpass[16];
            cout<<"Enter your atm card number: ";
            cin>>cdno;
            cout<<endl;
            geass.open("o.dat",ios::binary || ios::in ||ios::out ||ios::app);
            while(geass.read((char*)&a,sizeof(a)))
            {
                if (cdno == a.returnatmcdno())
                {
                    ++countxy;
                }
            }
            geass.close();

            if (countxy==0)
            {
                cout << "Entered Card Number is not associated to any account!";
                delay(1500);
                goto comedy;
            }
            line(1);
            code.open("o.dat", ios::binary | ios::in | ios::out | ios::app);
            while (code.read((char*)&a, sizeof(a)))
            {
                if (cdno == a.returnatmcdno())
                {
                    cout << "\nEnter password to continue: ";
                    char a7;
                    for(int i=0; i<17;)
                    {
                        a7=getch();
                        if((a7>='a'&&a7<='z')||(a7>='A'&&a7<='Z')||(a7>='0'&&a7<='9')||(a7=='@')||(a7=='(')||(a7==')')||(a7=='#')||(a7=='!')||(a7=='*')||(a7=='+')||(a7=='-')||(a7=='/')||(a7==':')||(a7=='?')||(a7=='='))

                        {
                            atmpass[i]=a7;
                            ++i;
                            cout<<"*";
                        }
                        if(a7=='\b'&& i>=1)
                        {
                            cout<<"\b \b";
                            --i;
                        }
                        if(a7=='\r')
                        {
                            atmpass[i]='\0';
                            break;
                        }
                    }
                    if ((!strcmp(atmpass,a.returnmainpass())) && a.returnstatus()==0)
                    {
                        clrscr();
                        line(2);
                        cout<<setw(4)<<"***BALANCE ENQUIRY***"<<endl
                            <<"---------------------------"<<endl<<endl;
                        cout<<"Account Holder Name: ";
                        puts(a.name);
                        cout<<"Account Number: "<<a.returnnum()<<endl;
                        cout<<"ATM Card Number: "<<a.returnatmcdno();
                        cout<<"\nAccount balance as on ";
                        timeclause();
                        cout<<" is: Rs ";
                        a.showbal();
                        line(3);
                        cout<<"\n*****--------------------------------------------------*****"<<endl;
                        line(2);
                        system("pause");
                        code.close();
                    }
                    else
                    {
                        cout << "Wrong password or Account blocked!" << endl;
                        code.close();
                        delay(1500);
                        goto comedy;
                    }
                    break;
                }
            }
        }

        case 3 :    //QUIT FROM ATM
            goto home;


        default:
            cout << "Invalid response!" << endl;
            break;
        }


    case 4: {
        //USER/ADMIN SETION

admin:
        clrscr();
        line(3);
        delay(50);
        char getid[64];
        char getpass[17];
        cout<<"Enter ADMIN ID: ";
        gets(getid);
        cout<<"\nPassword required for access.\nNote: Password is case sensitive."<<"\n\nENTER PASSWORD: ";
        int i=0;
        char a0;
        for(i=0; i<17;)
        {
            a0=getch();
            if((a0>='a'&&a0<='z')||(a0>='A'&&a0<='Z')||(a0>='0'&&a0<='9')||(a0=='@')||(a0=='(')||(a0==')')||(a0=='#')||(a0=='!')||(a0=='*')||(a0=='+')||(a0=='-')||(a0=='/')||(a0==':')||(a0=='?')||(a0=='='))

            {
                getpass[i]=a0;
                ++i;
                cout<<"*";
            }
            if(a0=='\b'&& i>=1)
            {
                cout<<"\b \b";
                --i;
            }
            if(a0=='\r')
            {
                getpass[i]='\0';
                break;
            }
        }
        int hei=0;
        if(!(strcmpi(getid,chara)) && !(strcmp(getpass,chat)))
        {
            cout<<"\nACCESS GRANTED."<<endl;
            delay(700);
            ++hei;
        }
        else
        {
            cout<<"\nACCESS DENIED"<<"\nYou are not authorized."<<endl;
            delay(1000);
            goto home;
        }
        if(hei>0)
        {
            clrscr();

            cout<<"          USER: ADMINISTRATOR             "<< endl;
            cout<<"       -------------------------       "<< endl;


            line(2);

            //Total number of accounts
hell:
            int count1=0;
            x14.open("o.dat", ios::binary | ios::in);
            while(x14.read((char*)&a,sizeof(a)))
            {
                ++count1;
            }
            x14.close();
            clrscr();
            cout<<setw(8)<<"\nTOTAL NUMBER OF ACCOUNTS: "<<count1;
            line(4);
            cout<<"1. DISPLAY ACCOUNTS"<<endl
                <<"2. CLOSE AN ACCOUNT"<<endl
                <<"3. BLOCK AN ACCOUNT"<<endl
                <<"4. VIEW TRANSACTION HISTORY"<<endl
                <<"5. CLEAR ALL TRANSACTION HISTORY"<<endl
                <<"6. DELETE ENTIRE DATABASE"<<endl
                <<"7. QUIT ADMIN ZONE"<<endl
                <<"8. QUIT FROM PROGRAM"<<endl;
            line(1);
            cout<<"\nChose an option: ";
            cin >> resp4;
            cout<<endl<<endl;
            switch(resp4)
            {

            case 1:    //Display all accounts

            {
                if(count1>0)
                {
desc:
                    clrscr();
                    line(1);
                    cout<<"\t          DISPLAY ACCOUNT WINDOW   "<<endl
                        <<"\t   -----------------------------------"<<endl;
                    line(2);
                    cout<<"\t1. Display Particular Account"<<endl
                        <<"\t2. Display All Accounts"<<endl
                        <<"\t3. Go back to ADMIN HOME"<<endl;
                    int user_select;
                    line(1);
                    cout<<"\tMark Your Response: ";
                    cin>>user_select;

                    if(user_select==2)
                    {

show_acc_again:
                        x6.open("o.dat", ios::binary | ios::in );
                        while (x6.read((char*)&a, sizeof(a)))
                        {
                            clrscr();
                            line(1);
                            cout<<"           DISPLAY ACCOUNT WINDOW   "<<endl
                                <<"    -----------------------------------"<<endl;
                            line(1);
                            cout<<setw(4)<<"\nName: ";
                            a.showname();
                            cout<<setw(4)<<"\nAC no.: ";
                            a.shownum();
                            cout<<setw(4)<<"\niATM Card Number: "<<a.returnatmcdno();
                            cout<<setw(4)<<"\nIFSC Code: ";
                            puts(ifsc);
                            cout<<setw(4)<<"\nBalance: ";
                            a.showbal();
                            line(1);
                            int flag5=0;
                            int einstein=0;
                            code.open("loan.dat",ios::binary | ios::in);
                            while(code.read((char*)&b,sizeof(b)))
                            {
                                if(b.returnnum()==a.returnnum())
                                {
                                    flag5=1;
                                    break;
                                }
                                ++einstein;
                            }
                            n9=einstein*sizeof(b);
                            code.seekg(n9);
                            if(flag5==1)
                            {
                                line(1);
                                cout<<setw(7)<<"***LOAN DETAILS***"<<endl<<endl;
                                cout<<setw(4)<<"LOAN TYPE:               ";
                                puts(b.loanname);
                                cout<<setw(4)<<"LOAN PRINCIPLE:          Rs "<<b.returnloanamt()<<endl
                                    <<setw(4)<<"INTEREST RATE:           "<<b.returninterest()*12<<" per annum"<<endl
                                    <<setw(4)<<"LOAN DURATION:           "<<b.loandurmonth<<" months";
                                cout<<setw(4)<<"\nLOAN AMOUNT REMAINING:   Rs "<<b.returnreturnamt()<<endl;
                                code.close();
                            }
                            else
                            {
                                cout<<"\nNO LOAN AGAINST THIS ACCOUNT."<<endl;
                                code.close();
                            }

                            cout<<setw(4)<<"\nAccount Status: ";
                            a.showstatus();
                            cout<<"\n*------------------------------------------*"<<endl;
                            cout<<"Note: Account Status is 1 if blocked."<<endl;
                            cout<<"Want to exit now(Y/N): ";
                            ask=getch();
                            if(ask=='y'||ask=='Y')
                                goto hell;
                            clrscr();
                        }
                        x6.close();
                        clrscr();
                        line(2);
                        cout<<"\tALL ACCOUNTS DISPLAYED."<<endl;
                        line(1);
                        cout<<"Want to view again(Y/N) ?"<<endl;
                        cin>>ask;
                        if(ask=='Y'||ask=='y')
                        {
                            clrscr();
                            goto show_acc_again;
                        }
                        else
                        {
                            clrscr();
                            goto desc;
                        }
                    }


                    else if(user_select==1)
                    {

                        clrscr();
                        line(1);
                        cout<<"           DISPLAY ACCOUNT WINDOW   "<<endl
                            <<"    -----------------------------------"<<endl;
                        line(2);
                        cout<<" Enter Account No. of account to Display: ";
                        long int acc_temp;
                        streampos n13;
                        int acc_count=0,loan_count=0,flag6=0,act_count=0;
                        cin>>acc_temp;
                        x10.open("o.dat",ios::binary | ios::in);
                        while(x10.read((char*)&c,sizeof(c)))
                        {
                            if(c.returnnum()==acc_temp)
                            {
                                act_count=5;
                                break;
                            }

                            ++acc_count;
                        }
                        n13=sizeof(c)*acc_count;
                        x10.close();
                        x10.open("loan.dat",ios::binary | ios::in);
                        while(x10.read((char*)&c,sizeof(c)))
                        {
                            if(c.returnnum()==acc_temp)
                            {
                                flag6=1;
                                break;
                            }
                            ++loan_count;
                        }
                        n14=sizeof(c)*loan_count;
                        x10.close();
                        if(act_count==0)
                        {
                            clrscr();
                            line(4);
                            cout<<"\tNo Valid Account Found in database with given Account Number !"<<endl;
                            delay(321);
                            cout<<"\tTaking you back.";
                            delay(1881);
                            clrscr();
                            goto desc;
                        }
                        else
                        {
                            clrscr();
                            line(1);
                            x9.open("o.dat",ios::binary | ios::in);
                            x9.seekg(n13);
                            x9.read((char*)&a,sizeof(a));
                            cout<<setw(4)<<"\nName: ";
                            a.showname();
                            cout<<setw(4)<<"\nAC no.: ";
                            a.shownum();
                            cout<<setw(4)<<"\niATM Card Number: "<<a.returnatmcdno();
                            cout<<setw(4)<<"\nIFSC Code: ";
                            puts(ifsc);
                            cout<<setw(4)<<"\nBalance: ";
                            a.showbal();

                            x17.open("loan.dat",ios::binary | ios::in);

                            if(flag6==1)
                            {
                                x17.seekg(n14);
                                x17.read((char*)&b,sizeof(b));
                                line(1);
                                cout<<setw(7)<<"***LOAN DETAILS***"<<endl<<endl;
                                cout<<setw(4)<<"LOAN TYPE:               ";
                                puts(b.loanname);
                                cout<<setw(4)<<"LOAN PRINCIPLE:          Rs "<<b.returnloanamt()<<endl
                                    <<setw(4)<<"INTEREST RATE:           "<<b.returninterest()*12<<" per annum"<<endl
                                    <<setw(4)<<"LOAN DURATION:           "<<b.loandurmonth<<" months";
                                cout<<setw(4)<<"\nLOAN AMOUNT REMAINING:   Rs "<<b.returnreturnamt()<<endl;
                                x17.close();
                            }
                            else
                            {
                                cout<<"\nNO LOAN AGAINST THIS ACCOUNT."<<endl;
                                x17.close();
                            }

                            cout<<setw(4)<<"\nAccount Status: ";
                            a.showstatus();
                            cout<<"\n*----------------------------------------------*"<<endl;
                            cout<<"Note: Account Status is 1 if blocked."<<endl;
                            system("pause");
                            x9.close();
                            goto desc;
                        }
                    }

                    else if(user_select==3)
                    {
                        clrscr();
                        goto hell;
                    }

                    else
                    {
                        clrscr();
                        line(3);
                        cout<<"\n\tINVALID CHOICE !"<<endl;
                        cout<<"Please Enter again."<<endl;
                        delay(1881);
                        goto desc;
                    }

                }

                else

                {

                    clrscr();

                    cout<<setw(7)<<"\n****No accounts to display.****"<<endl;

                }

                cout<<endl<<endl;

                cout<<"1. GO TO ADMIN HOME"<< endl <<"2. QUIT FROM ADMIN ZONE"<< endl << endl;

                cout<<"Mark your response: ";

                cin>>resp7;

                if(resp7==1)

                    goto hell;

                else

                    goto home;

            }



            case 2:      // Close an account

            {
                if(count1>0)
                {
                    int ramps=0;
                    long int tempint;
                    cout<<"Enter account number of the account to be closed: ";
                    cin>>tempint;
                    cout<<endl;
                    x10.open("loan.dat",ios::binary | ios::in);
                    while(x10.read((char*)&a,sizeof(a)))
                    {
                        if(a.returnnum()==tempint)
                            ++ramps;
                    }
                    x10.close();
                    if(ramps==0)
                    {
                        int ramp=0;
                        x17.open("o.dat", ios::binary | ios::in );
                        x14.open("loan.dat", ios::binary | ios::in );
                        temp.open("pop.dat",ios::binary | ios::out);
                        x15.open("del.dat",ios::binary | ios::out);
                        x17.seekg(0);
                        temp.seekg(0);
                        while(x17.read((char*)&a,sizeof(a)))
                        {
                            if(a.returnnum()!=tempint)
                                temp.write((char*)&a,sizeof(a));
                            else
                                ++ramp;
                        }
                        x17.close();
                        temp.close();
                        remove("o.dat");
                        rename("pop.dat","o.dat");
                        if(ramp>0)
                        {
                            while(x14.read((char*)&b,sizeof(b)))
                            {
                                if(b.returnnum()!=tempint)
                                    x15.write((char*)&b,sizeof(b));
                            }
                            x14.close();
                            x15.close();
                            remove("loan.dat");
                            rename("del.dat","loan.dat");
                            clrscr();
                            line(3);
                            cout<<setw(5)<<"ACCOUNT CLOSED SUCCESSSFULLY.\nPlease collect your Rs 1001 security deposit."<<endl<<endl;
                        }
                        else
                        {
                            clrscr();
                            cout<<"No such account found.\nReturning to admin zone."<<endl;
                            delay(1500);
                            goto hell;
                        }
                        cout<<"1. GO ADMIN HOME"<< endl
                            <<"2. QUIT FROM ADMIN ZONE"<<endl<<endl;
                        cout<<"Chose an option: ";
                        cin>>resp7;
                        if(resp7==1)
                            goto hell;
                        else
                            goto home;
                    }
                    else
                    {
                        clrscr();
                        line(4);
                        cout<<setw(3)<<"\nCan't Close Account!.\nThere is a loan payment due against this account."
                            <<setw(3)<<"\nUser must pay back the loan to close the account."<<endl;
                        delay(4000);
                        ramps=0;
                        goto hell;
                    }
                }
                else
                {
                    clrscr();
                    line(3);
                    cout<<setw(7)<<"\n****No Accounts found in Database.****"<<endl;
                }
            }


            case 3:       //Block an account


                if(count1>0)
                {
                    clrscr();
                    line(4);
                    cout<<setw(4)<<"Enter account number to block/unblock account: ";
                    cin>>adac;
                    x15.open("o.dat", ios::binary | ios::in | ios::out | ios::app);
                    while (x15.read((char*)&a, sizeof(a)))
                    {
                        if (adac==a.returnnum())
                        {

                            line(2);
                            cout<<"Chose an option: " << endl
                                <<"1. Block the account" << endl
                                <<"2. Unblock the account" << endl;
                            cin>>resp3;
                            if (resp3 == 1)
                            {
                                a.block();
                                clrscr();
                                line(3);
                                cout<<"ACCOUNT BLOCKED SUCCESSSFULLY."<<endl;
                            }
                            else if(resp3 == 2)
                            {
                                a.unblock();
                                clrscr();
                                line(3);
                                cout<<"ACCOUNT UNBLOCKED SUCCESSSFULLY."<<endl;
                            }
                        }
                    }

                }
                else
                {
                    clrscr();
                    line(3);
                    cout<<setw(7)<<"\n****No Accounts found in Database.****"<<endl;
                }
                line(2);
                cout<<"\n1. GO ADMIN HOME"<< endl
                    <<"2. QUIT FROM ADMIN ZONE"<<endl;
                line(2);
                cout<<"Mark your response: ";
                cin>>resp7;
                if(resp7==1)
                    goto hell;
                else
                    goto home;



            case 4:          //VIEW TRANSACTION HISTORY

                clrscr();
                char chan;
                int strange=0;
                ifstream fine("trans.txt");
                if(!fine)
                {
                    clrscr();
                    cout<<setw(7)<<"\n\n\t\t****No Transaction(s) to display.****"<<endl;
                    delay(1000);
                    fine.close();
                    goto hell;
                }
                else
                {
                    fine.close();
                    fin.open("trans.txt");
                    while(!fin.eof())
                    {
                        ++strange;
                        if(strange==10)
                            break;
                    }

                    if(strange==0)
                    {
                        clrscr();
                        cout<<setw(7)<<"\n\n\t\t****No Transaction(s) to display.****"<<endl;
                        delay(1000);
                        fine.close();
                        goto hell;
                    }
                    else
                    {

show_t_again:

                        fin.get(chan);
                        while(!fin.eof())
                        {
                            cout<<chan;
                            if(chan=='%')
                            {

                                cout<<endl;
                                line(1);
                                cout<<"Want to exit now(Y/N): ";
                                ask=getch();
                                if(ask=='y'||ask=='Y')
                                {
                                    fin.close();
                                    goto hell;
                                }
                                cout<<endl;
                            }
                            fin.get(chan);
                        }
                        fin.close();
                        cout<<"ALL TRANSACTION SHOWN."<<endl;
                        cout<<"Want to view again(Y/N) ?"<<endl;
                        ask=getch();
                        if(ask=='Y'||ask=='y')
                        {
                            clrscr();
                            goto show_t_again;
                        }
                        fin.close();
                        delay(2000);
                        clrscr();
                    }
                }


                cout<<endl<<endl;

                cout<<"\t1. GO ADMIN HOME"<< endl <<"\t2. QUIT FROM ADMIN ZONE"<< endl << endl;

                cout<<"Mark your response: ";

                cin>>resp7;

                if(resp7==1)

                    goto hell;

                else

                    goto home;


            case 5:  //CLEAR TRANSACTION HISTORY

            {
                clrscr();
                line(3);
                char engg[30];
                cout<<setw(4)<<"  ENTER ADMINISTRATOR PASSWORD TO CONTINUE: ";
                int i=0;
                char a;
                for(i=0; i<17;)
                {
                    a=getch();
                    if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9')||(a=='@')||(a=='(')||(a==')')||(a=='#')||(a=='!')||(a=='*')||(a=='+')||(a=='-')||(a=='/')||(a==':')||(a=='?')||(a=='='))

                    {
                        engg[i]=a;
                        ++i;
                        cout<<"*";
                    }
                    if(a=='\b'&& i>=1)
                    {
                        cout<<"\b \b";
                        --i;
                    }
                    if(a=='\r')
                    {
                        engg[i]='\0';
                        break;
                    }
                }
                if(!(strcmp(engg,chat)))
                {

                    clrscr();
                    line(2);
                    cout<<"\n\nYou are going to delete the entire Transaction History.\nIt can't be restored after deletion."<<endl;
                    cout<<"Confirm to delete Transaction History(Y/N): ";
                    cin>>ask;
                    if(ask=='Y'||ask=='y')
                    {
                        x17.open("trans.txt",ios::out | ios::trunc);
                        x17.close();
                        clrscr();
                        line(3);
                        cout<<"\n     Succesfully Cleared Transaction History."<<endl;
                        cout<<"\n     Taking you back to admin zone."<<endl;
                        delay(2600);
                        goto hell;
                    }
                    else
                        goto hell;
                }
                else
                {
                    clrscr();
                    line(4);
                    cout<<setw(8)<<" WRONG PASSWORD ! "<<endl;
                    delay(1000);
                    clrscr();
                    goto hell;
                }

            }



            case 6: //DELETE ENTIRE DATABASE

                clrscr();
                line(3);
                char engg2[30];
                long int mpass;
                cout<<"  ENTER MASTER KEY TO CONTINUE: ";
                cin>>mpass;
                if(mpass==masterpass)
                {
                    cout<<setw(4)<<"  ENTER ADMINISTRATOR PASSWORD TO CONTINUE: ";
                    char a8;
                    for(int i=0; i<17;)
                    {
                        a8=getch();
                        if((a8>='a'&&a8<='z')||(a8>='A'&&a8<='Z')||(a8>='0'&&a8<='9')||(a8=='@')||(a8=='(')||(a8==')')||(a8=='#')||(a8=='!')||(a8=='*')||(a8=='+')||(a8=='-')||(a8=='/')||(a8==':')||(a8=='?')||(a8=='='))

                        {
                            engg2[i]=a8;
                            ++i;
                            cout<<"*";
                        }
                        if(a8=='\b'&& i>=1)
                        {
                            cout<<"\b \b";
                            --i;
                        }
                        if(a8=='\r')
                        {
                            engg2[i]='\0';
                            break;
                        }
                    }
                    if(!(strcmp(engg2,chat)))
                    {

                        cout<<"\n\nYou are going to delete the entire database.\nIt can't be restored after deletion."<<endl;
                        delay(800);
                        cout<<"\nPlease Think Carefully about this step."<<endl;
                        delay(500);
                        cout<<"Confirm to delete entire DATABASE(Y/N): ";
                        cin>>ask;
                        if(ask=='Y'||ask=='y')
                        {
                            x1.open("o.dat",ios::binary | ios::in);
			                while(x1.read((char*)&a,sizeof(a)))
                            {
                                remove(a.notif);
                                x1.close();
                            }
                            remove("o.dat");
                            remove("loan.dat");
                            x14.open("trans.txt",ios::out | ios::trunc);
                            x14.close();
                            clrscr();
                            char spdf[30]="EXITING PROGRAM........... ";
                            clrscr();
                            line(5);
                            cout<<"    Deletion SUCCESSSFUL. You have DELETED the entire database."<<endl<<endl;
                            delay(500);
                            for(int i=0; spdf[i]!='\0'; ++i)
                            {
                                cout<<spdf[i];
                                delay(150);
                            }
                            exit(0);
                        }
                        else
                            goto hell;
                    }
                    else
                    {
                        clrscr();
                        line(4);
                        cout<<setw(8)<<"     WRONG MASTER KEY !\nExiting Program. "<<endl;
                        delay(2000);
                        exit(0);
                    }
                }
                else
                {
                    clrscr();
                    line(4);
                    cout<<setw(8)<<" WRONG PASSWORD !\nExiting Program. "<<endl;
                    delay(2000);
                    exit(0);
                }



            case 7:   //RETURN HOME

                goto home;


            case 8:   //EXIT PROGRAM

                exit(0);

            default :

                clrscr();
                line(3);
                cout<<"\t\tINVALID CHOICE!"<<endl;
                delay(1200);
                clrscr();
                goto hell;
            }
        }
    }



    case 5:    //Read Terms and Conditions

home2:
        clrscr();
        int tc;
        line(3);
        cout<<setw(4)<<"   ***--- TERMS & CONDITIONS ---***"<<endl
            <<"*--------------------------------------------------------------------*"<<endl;
        line(3);
        cout<<"1. GENERAL T&C"<<endl
            <<"2. ACCOUNT T&C"<<endl
            <<"3. iATM T&C"<<endl
            <<"4. NEFT T&C"<<endl
            <<"5. EXIT T&C WINDOW"<<endl
            <<"\nMark your response: ";
        cin>>tc;
        switch(tc)
        {
        case 1:
            clrscr();
            char ch1;
            fin.open("gent&c.txt");
            ch1=fin.get();
            int counter1=0;
            while(!fin.eof())
            {

                if((ch1=='%')&&(counter1<=4))
                {
                    cout<<endl;
                    ++counter1;
                }
                else if((ch1=='%')&&(counter1>4))
                {
                    line(2);
                    system("pause");
                    clrscr();
                    cout<<endl;
                    counter1=0;
                }
                else
                {
                    cout<<ch1;
                }
                ch1=fin.get();
            }
            fin.close();
            line(3);
            cout<<"*****------------------------------------------*****"<<endl;
            system("pause");
            clrscr();
            goto home2;


        case 2:
            clrscr();
            char ch2;
            fin.open("cacct&c.txt");
            ch2=fin.get();
            int counter2=0;
            while(!fin.eof())
            {

                if((ch2=='%')&&(counter2<=4))
                {
                    cout<<endl;
                    ++counter2;
                }
                else if((ch2=='%')&&(counter2>4))
                {
                    line(2);
                    system("pause");
                    clrscr();
                    cout<<endl;
                    counter2=0;
                }
                else
                {
                    cout<<ch2;
                }
                ch2=fin.get();
            }
            fin.close();
            line(3);
            cout<<"*****------------------------------------------*****"<<endl;
            system("pause");
            clrscr();
            goto home2;


        case 3:
            clrscr();
            char ch3;
            fin.open("iatmt&c.txt");
            ch3=fin.get();
            int counter3=0;
            while(!fin.eof())
            {

                if((ch3=='%')&&(counter3<=4))
                {
                    cout<<endl;
                    ++counter3;
                }
                else if((ch3=='%')&&(counter3>4))
                {
                    line(2);
                    system("pause");
                    clrscr();
                    cout<<endl;
                    counter3=0;
                }
                else
                {
                    cout<<ch3;
                }
                ch3=fin.get();
            }
            fin.close();
            line(3);
            cout<<"*****------------------------------------------*****"<<endl;
            system("pause");
            clrscr();
            goto home2;

        case 4:
            clrscr();
            char ch4;
            fin.open("neftt&c.txt");
            ch4=fin.get();
            int counter4=0;
            while(!fin.eof())
            {

                if((ch4=='%')&&(counter4<=4))
                {
                    cout<<endl;
                    ++counter4;
                }
                else if((ch4=='%')&&(counter4>4))
                {
                    line(2);
                    system("pause");
                    clrscr();
                    cout<<endl;
                    counter4=0;
                }
                else
                {
                    cout<<ch4;
                }
                ch4=fin.get();
            }
            fin.close();
            line(3);
            cout<<"*****-----------------------------------------*****"<<endl;
            system("pause");
            clrscr();
            goto home2;



        case 5:
            goto home;

        default :
            line(3);
            cout<<"\t\tINVALID CHOICE!"<<endl;
            delay(1300);
            clrscr();
            goto home2;
        }


    case 6:    //QUIT

        exit(0);

    default:
        cout << "Invalid response!"<<endl;
        delay(1579);
        goto home;
    }

}


double account::updateloan(account f)
{
    clrscr();
    double future=0;
    if(returnamt>7000)
    {
good_life:
        cout<<"Enter amount to payback. Amount must be greater than 7000 and less than loan amount"<<endl;
        cout<<"Amount to payback: ";
        cin>>future;
        if(future<=f.returnbalance()-1001)
        {
            line(1);
            if((future>7000)&&(future<returnamt))
            {
                returnamt=returnamt-future;
                universe=future;
                cout<<"\n\nAmount paid successfully";
                randomize();
                tid=random(9)+random(99)+random(999)+random(9999)+random(468676);
                cout<<"\nTransaction successful.\nTransaction ID: "<<tid<<endl;
                cout<<"\nRemaining Balance to payback: ";
                cout<<returnamt<<endl;
                timesave(tid,future,f.name,f.num,"LOAN PAYBACK");
                system("pause");
                manas=0;
                return returnamt;
            }
            else if((future<7000)&&(future<returnamt))
            {
                char castle;
                cout<<"Amount must be greater than Rs 7000.\nPlease Try Again or Exit."<<endl;
                line(2);
                cout<<"Want to Continue: ";
                cin>>castle;
                if(castle=='Y'||castle=='y')
                    goto good_life;
                else
                {
                    manas=0;
                    return returnamt;
                }
            }
            else if(future>returnamt)
            {
                cout<<"Amount Should Not Exceed The Loan Amount!\nLoan Amount Remaining: Rs. "<<returnamt<<endl;
                cout<<"Please TRY AGAIN or EXIT."<<endl;
                line(2);
                char hill;
                cout<<"Want to Continue: ";
                cin>>hill;
                if(hill=='Y'||hill=='y')
                    goto good_life;
                else
                {
                    manas=0;
                    return returnamt;
                }
            }
            else if(future==returnamt)
            {
                returnamt=0.0;
                universe=returnamt;
                cout<<"\n\nAmount paid successfully";
                randomize();
                tid=random(9)+random(99)+random(999)+random(9999)+random(468676);
                cout<<"\nTransaction successful.\nTransaction ID: "<<tid<<endl;
                cout<<setw(4)<<"YOU HAVE PAID BACK YOUR LOAN and INTEREST SUCCESSSFULLY.\nYou can now take another loan."<<endl;
                line(3);
                timesave(tid,returnamt,f.name,f.num,"LOAN PAYBACK");
                system("pause");
                manas=1;
                return 0.0;
            }
        }
        else
        {
            cout<<"\nInsufficient Balance!\nPlease Deposit Money to continue."<<endl;
            manas=55;
            delay(2000);
            return returnamt;
        }
    }
    else
    {
muzmo:
        if(returnamt<=f.returnbalance()-1001)
        {
            cout<<"Pay Rs "<<returnamt<<" to complete loan payment: ";
            cin>>future;
            line(1);
            if((future==returnamt))
            {
                returnamt=0.0;
                universe=returnamt;
                cout<<"\n\nAmount paid successfully";
                randomize();
                tid=random(9)+random(99)+random(999)+random(9999)+random(468676);
                cout<<"\nTransaction successful.\nTransaction ID: "<<tid<<endl;
                cout<<setw(4)<<"YOU HAVE PAID BACK YOUR LOAN and INTEREST SUCCESSSFULLY.\nYou can now take another loan."<<endl;
                line(3);
                timesave(tid,returnamt,f.name,f.num,"LOAN PAYBACK");
                system("pause");
                manas=1;
                return 0.0;
            }
            else
            {
                char castle2;
                cout<<"Amount must be equal to Rs "<<returnamt<<" .\nPlease Try Again or Exit."<<endl;
                line(2);
                cout<<"Want to Continue: ";
                cin>>castle2;
                if(castle2=='Y'||castle2=='y')
                    goto muzmo;
                else
                {
                    manas=0;
                    return returnamt;
                }
            }
        }
        else
        {
            cout<<"\nYou have insufficient balance to proceed forward.\nPlease Deposit money in your account."<<endl;
            manas=55;
            delay(2000);
            return returnamt;
        }
    }
    return returnamt;

}

double account::loantype(account g)
{
quote:
    clrscr();
    cout<<"                       LOAN WINDOW"<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    line(2);
    cout<<"Name: ";
    puts(g.name);
    cout<<"Account Number: "<<g.num<<endl;
    cout<<"*---------------------------------------------*"<<endl;
    line(1);
    cout<<"You MUST HAVE BALANCE MORE than 80 percent of LOAN PRINCIPLE to GET LOAN."<<endl;
    line(2);
    cout<<"Please Select a loan type from the list."<<endl;
    cout<<"\n1. Personal Loan"
        <<"\n2. Educational Loan"
        <<"\n3. PROPERTY Loan"
        <<"\n4. VEHICLE Loan"
        <<"\n5. EXIT From LOAN WINDOW"
        <<"\n\nMark your response: ";
    cin>>choiceloan;
    cout<<endl;
    switch(choiceloan)
    {
    case 1:
        clrscr();
        cout<<"\n         PERSONAL LOAN"
            <<"\n*------------------------------*";
        line(2);
        cout<<"\nPlease select an amount"
            <<"\n\n1. Rs 100000"
            <<"\n2. Rs 150000"
            <<"\n3. Rs 200000"<<endl;
        int ch;
        cin>>ch;
        switch(ch)
        {
        case 1:
            char chrome;
            cout<<"PRINCIPLE: Rs 100000"<<endl
                <<"Interest: "<<1.05*12<<" per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(100000,1.05,9)<<endl
                <<"Loan Duration: 9 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome;
            if(chrome=='Y'||chrome=='y')
            {
                if(g.balance>0.80*100000)
                {
                    g.assignloanamt(100000);
                    loandurmonths=9;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;
        case 2:
            char chrome2;
            cout<<"PRINCIPLE: Rs 150000"<<endl
                <<"Interest: "<<12*1.05<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(150000,1.05,13)<<endl
                <<"Loan Duration: 13 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome2;
            if(chrome2=='Y'||chrome2=='y')
            {
                if(g.balance>0.80*150000)
                {
                    g.assignloanamt(150000);
                    loandurmonths=13;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;
        case 3:
            char chrome3;
            cout<<"PRINCIPLE: Rs 200000"<<endl
                <<"Interest: "<<1.05*12<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(200000,1.05,16)<<endl
                <<"Loan Duration: 16 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome3;
            if(chrome3=='Y'||chrome3=='y')
            {
                if(g.balance>0.80*200000)
                {
                    g.assignloanamt(200000);
                    loandurmonths=16;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;

        default :
            cout<<"Invalid response!";
            goto quote;
        }
    case 2:
        clrscr();
        cout<<"\n        EDUCATIONAL LOAN"
            <<"\n*------------------------------*";
        line(2);
        cout<<"\nPlease select an amount"
            <<"\n\n1. Rs 600000"
            <<"\n2. Rs 1000000"
            <<"\n3. Rs 1500000"<<endl;
        int cht;

        cin>>cht;
        switch(cht)
        {
        case 1:
            char chrome4;
            cout<<"PRINCIPLE: Rs 600000"<<endl
                <<"Interest: "<<12*0.67<<" per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(600000,0.67,48)<<endl
                <<"Loan Duration: 4 years"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome4;
            if(chrome4=='Y'||chrome4=='y')
            {
                if(g.balance>0.80*600000)
                {
                    g.assignloanamt(600000);
                    loandurmonths=48;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;
        case 2:
            char chrome5;
            cout<<"PRINCIPLE: Rs 1000000"<<endl
                <<"Interest: "<<12*0.67<<" per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(1000000,0.67,48)<<endl
                <<"Loan Duration: 4 years"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome5;
            if(chrome5=='Y'||chrome5=='y')
            {
                if(g.balance>0.80*1000000)
                {
                    g.assignloanamt(1000000);
                    loandurmonths=48;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;
        case 3:
            char chrome6;
            cout<<"PRINCIPLE: Rs 1500000"<<endl
                <<"Interest: "<<12*0.67<<" per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(1500000,0.67,48)<<endl
                <<"Loan Duration: 4 years"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome6;
            if(chrome6=='Y'||chrome6=='y')
            {
                if(g.balance>0.80*1500000)
                {
                    g.assignloanamt(1500000);
                    loandurmonths=48;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;

        default :
            cout<<"Invalid response!";
            goto quote;
        }

    case 3:
        clrscr();
        cout<<"\n         PROPERTY LOAN"
            <<"\n*------------------------------*";
        line(2);
        cout<<"\nPlease select an amount"
            <<"\n\n1. Rs 1500000"
            <<"\n2. Rs 2100000"
            <<"\n3. Rs 3200000"
            <<"\n4. Rs 5000000"
            <<"\n5. RS 10000000"
            <<endl;
        int chg;
        cin>>chg;
        switch(chg)
        {
        case 1:
            char chrome7;
            cout<<"PRINCIPLE: Rs 1500000"<<endl
                <<"Interest: "<<12*0.95<<"per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(1500000,0.95,130)<<endl
                <<"Loan Duration: 10 years and 10 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome7;
            if(chrome7=='Y'||chrome7=='y')
            {
                if(g.balance>=0.80*1500000)
                {
                    g.assignloanamt(1500000);
                    loandurmonths=130;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;
        case 2:
            char chrome8;
            cout<<"PRINCIPLE: Rs 2100000"<<endl
                <<"Interest: "<<12*0.95<<"per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(2100000,0.95,150)<<endl
                <<"Loan Duration: 12 years and 12 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome8;
            if(chrome8=='Y'||chrome8=='y')
            {

                if(g.balance>0.80*2100000)
                {
                    g.assignloanamt(2100000);
                    loandurmonths=150;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;
        case 3:

            char chrome9;
            cout<<"PRINCIPLE: Rs 3200000"<<endl
                <<"Interest: "<<12*0.95<<"per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(3200000,0.95,180)<<endl
                <<"Loan Duration: 15 years"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome9;
            if(chrome9=='Y'||chrome9=='y')
            {
                if(g.balance>0.80*3200000)
                {
                    g.assignloanamt(3200000);
                    loandurmonths=180;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;
        case 4:

            char chrome10;
            cout<<"PRINCIPLE: Rs 5000000"<<endl
                <<"Interest: "<<12*0.95<<"per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(5000000,0.95,200)<<endl
                <<"Loan Duration: 16 years and 8 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome10;
            if(chrome10=='Y'||chrome10=='y')
            {
                if(g.balance>0.80*5000000)
                {
                    g.assignloanamt(5000000);
                    loandurmonths=200;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;

        case 5:

            char chrome11;
            cout<<"PRINCIPLE: Rs 10000000"<<endl
                <<"Interest: "<<12*0.95<<"per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(10000000,0.95,225)<<endl
                <<"Loan Duration: 18 years and 9 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome11;
            if(chrome11=='Y'||chrome11=='y')
            {
                if(g.balance>0.80*10000000)
                {
                    g.assignloanamt(10000000);
                    loandurmonths=225;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;
        default :
            cout<<"Invalid response!";
            goto quote;
        }

    case 4:
        clrscr();
        cout<<"\n         VEHICLE LOAN"
            <<"\n*------------------------------*";
        line(2);
        cout<<"\nPlease select an amount"
            <<"\n\n1. Rs 100000"
            <<"\n2. Rs 500000"
            <<"\n3. Rs 1500000"
            <<"\n4. Rs 3500000"
            <<"\n5. Rs 5000000"
            <<endl;
        int chj;
        cin>>chj;
        switch(chj)
        {
        case 1:
            char chrome12;
            cout<<"PRINCIPLE: Rs 100000"<<endl
                <<"Interest: "<<1.084*12<<"per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(100000,1.084,12)<<endl
                <<"Loan Duration: 12 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome12;
            if(chrome12=='Y'||chrome12=='y')
            {
                if(g.balance>0.80*100000)
                {
                    g.assignloanamt(100000);
                    loandurmonths=12;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;

        case 2:
            char chrome0;
            cout<<"PRINCIPLE: Rs 500000"<<endl
                <<"Interest: "<<1.084*12<<"per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(500000,1.084,24)<<endl
                <<"Loan Duration: 24 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome0;
            if(chrome0=='Y'||chrome0=='y')
            {
                if(g.balance>0.80*500000)
                {
                    g.assignloanamt(500000);
                    loandurmonths=24;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;

        case 3:
            char chromes;
            cout<<"PRINCIPLE: Rs 1500000"<<endl
                <<"Interest: "<<1.084*12<<"per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(1500000,1.084,40)<<endl
                <<"Loan Duration: 3 years and 4 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chromes;
            if(chromes=='Y'||chromes=='y')
            {
                if(g.balance>0.80*1500000)
                {
                    g.assignloanamt(1500000);
                    loandurmonths=40;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;

        case 4:
            char chrome13;
            cout<<"PRINCIPLE: Rs3500000"<<endl
                <<"Interest: "<<1.084*12<<"per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(3500000,1.084,60)<<endl
                <<"Loan Duration: 5 years"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome13;
            if(chrome13=='Y'||chrome13=='y')
            {
                if(g.balance>0.80*3500000)
                {
                    g.assignloanamt(3500000);
                    loandurmonths=60;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds";
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;

        case 5:
            char chrome14;
            cout<<"PRINCIPLE: Rs 5000000"<<endl
                <<"Interest: "<<1.084*12<<"per annum"<<endl
                <<"LOAN AMOUNT: Rs "<<returncalc(5000000,1.084,78)<<endl
                <<"Loan Duration: 6 years and 6 months"<<endl;
            cout<<"Confirm to take this loan(Y/N): ";
            cin>>chrome14;
            if(chrome14=='Y'||chrome14=='y')
            {
                if(g.balance>0.80*5000000)
                {
                    g.assignloanamt(5000000);
                    loandurmonths=78;
                    return g.loanamt;
                }
                else
                {
                    cout<<"\nCan't Initiate Loan to your account due to insufficient funds !!!"<<endl;
                    delay(1357);
                    return g.loanamt=0;
                }
            }
            else
                goto quote;


        default :
            cout<<"Invalid response !";
            goto quote;
        }



    case 5:
        return g.loanamt=0;


    default :
        cout<<"Invalid response!";
        goto quote;
    }

}



