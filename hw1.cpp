#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int N;
class Waggon;class Train;class Human;
class Train{
        int totalWaggons;
        class Waggon **WaggonTable;
    public:
        void setdata(int);
        class Waggon *get_WTable(int);
        void Operate(int);
        void inStation(int);
        int betweenStation(int);
        void printStatistics(int);
        void Print(int,int);
        Train(int,int);
        ~Train();
};

class Waggon{
        int Capacity;
        int maxCapacity;
        int money;
        int Peoplegotten;
        int Peoplenotgotten;
        class Human **HumanTable;
        int *HumanFlagTable;
    public: 
        Waggon(int);
        ~Waggon();
        void setdata(int,int);
        void setmoney(int);
        void setpeoplegotten();
        void setpeoplenotgotten();
        void set_HumanFlagTable(int,int);
        class Human *get_HTable(int);
        int get_mCapacity();
        int get_Capacity();
        int get_Money();
        int getpeoplegotten();
        int getpeoplenotgotten();
        int get_HumanFlagTable(int);
};

class Human{
        int Ticket_Property;
        int LowerPrice;
    public:
        void setdata(int,int);
        int get_TicketP();
        int get_LowerP();
        
};

Train::Train(int totalWaggons,int maxCapacity):totalWaggons(totalWaggons)
{  
    cout<<"A metro train with "<<totalWaggons<<" waggons, was created"<<endl;
    WaggonTable=new Waggon*[maxCapacity];
    totalWaggons=totalWaggons;
    for(int i=0 ; i<totalWaggons ; i++)
    {
        WaggonTable[i]=new Waggon(maxCapacity);
        WaggonTable[i]->setdata(maxCapacity,0);
    }
}

Train::~Train(void)
{
    for(int i=0 ; i<totalWaggons ; i++)
        delete WaggonTable[i];
    delete[] WaggonTable;
    cout << "A metro train was destroyed "<<endl;
}

void Train::setdata(int Waggons)
{
    totalWaggons=Waggons;
}

void Train::inStation(int j)
{
    int tmp=0;
    
    if((get_WTable(j)->get_Capacity()) > 0)                                                     //as long as passengers exist
    {
        tmp=rand()%( (get_WTable(j)->get_Capacity()+1) );                                       //how many will leave
        get_WTable(j)->setdata(get_WTable(j)->get_mCapacity(),(-tmp));
        for (int i=0 ; i<tmp ; i++)                                                             //passengers_wannaleave times
        {
            int tmp2;
            while(get_WTable(j)->get_HumanFlagTable(tmp2=(rand()%(get_WTable(j)->get_mCapacity()+1)))==1)   //find someone random inside
            get_WTable(j)->set_HumanFlagTable(tmp2,1);                                                      //and throw him out
        }

    }
    if((get_WTable(j)->get_Capacity()) < get_WTable(j)->get_mCapacity())                        //as long as there is free space
    {
        tmp=rand()%(( ( get_WTable(j)->get_mCapacity()-get_WTable(j)->get_Capacity() )+1 ));    //people to add
        get_WTable(j)->setdata(get_WTable(j)->get_mCapacity(),+tmp);
        int a,b,p=0;
        for (int i=0 ; i<tmp ; i++)                                                             //passengers_entered times
        {
            for(int l=p ; l<get_WTable(j)->get_mCapacity() ; l++)
            {
                if(get_WTable(j)->get_HumanFlagTable(l)==1)                                     //If position empty
                {
                    get_WTable(j)->set_HumanFlagTable(l,0);                                     //put the extra passenger here
                    a=rand()%2;         //Checks if the person has a ticket
                    b=rand()%2;         //Checks if the person deserve a lower price ticket
                    get_WTable(j)->get_HTable(l)->setdata(a,b);
                    p=l+1;
                    break;
                }
            }
        }
    }
}

int Train::betweenStation(int j)
{
    int check;
    check=rand()%2;

        for(int k=0 ; k< get_WTable(j)->get_mCapacity() ; k++)              //Checks every place in the waggon
        {
            if(get_WTable(j)->get_HumanFlagTable(k)==0)                     //If a passenger exists in this place
            {
                if(get_WTable(j)->get_HTable(k)->get_TicketP()==1)          //Human doesn't have a ticket
                {        
                    if(get_WTable(j)->get_HTable(k)->get_LowerP()==1)       //Human doesn't deserve lower price
                    {
                            get_WTable(j)->setmoney(2*10);                  //pay 10 times the ticket
                            get_WTable(j)->setpeoplegotten();               //illegals++
                    }
                    else                                                    //Human deserve lower price
                    {
                            get_WTable(j)->setmoney(1*10);                  //pay 10 times the lower-price ticket
                            get_WTable(j)->setpeoplegotten();               //illegals++
                    }
                    if(check==0)
                            get_WTable(j)->setpeoplegotten();               //illegals++
                    else
                            get_WTable(j)->setpeoplenotgotten();            //illegals not gotten++
                    get_WTable(j)->set_HumanFlagTable(k,1);                 //Get the illegal out of the train!
                    int max=get_WTable(j)->get_mCapacity(); 
                    get_WTable(j)->setdata(max,-1);                         //Capacity--
                }
            }
        }         
}

void Train::Operate(int j)
{
    inStation(j);
    int ch;
    ch=betweenStation(j);
    printStatistics(j);
}

void Train::Print(int Stations,int Waggons)
{
    int totalMoney=0,Illegals=0,Illegals_survived=0;
    for(int i=0 ; i<Stations ; i++)
    {
        for(int j=0 ; j<Waggons ; j++)
        {
            totalMoney+=get_WTable(j)->get_Money();
            Illegals+=get_WTable(j)->getpeoplegotten();
            Illegals_survived+=get_WTable(j)->getpeoplenotgotten();
        }
    }
    cout<<"Total Money gotten from illegal passengers: "<<totalMoney<<"$"<<endl;
    cout<<"Total illegal passengers: "<<Illegals<<endl;
    cout<<"Total times passengers not checked: "<<Illegals_survived<<endl;
}

void Train::printStatistics(int j)
{
    cout<<"Money gotten from this waggon: "<<get_WTable(j)->get_Money()<<endl;
    cout<<"People gotten without ticket: "<<get_WTable(j)->getpeoplegotten()<<endl;
    cout<<"People not checked without ticket: "<<get_WTable(j)->getpeoplenotgotten()<<endl;
}

class Waggon *Train::get_WTable(int num)
{
    return WaggonTable[num];
}

Waggon::Waggon(int maxCapacity):maxCapacity(maxCapacity),money(0),Peoplegotten(0),Peoplenotgotten(0),Capacity(0)
{
    cout<<"A waggon with capacity for "<<maxCapacity<<" passengers, was created"<<endl;
    HumanTable=new Human*[maxCapacity];
    HumanFlagTable=new int[maxCapacity];
    for(int i=0 ; i<maxCapacity ; i++)
    {
        HumanTable[i]=new Human;
        HumanFlagTable[i]=1;
    }
}

Waggon::~Waggon()
{

    for(int i=0 ; i<maxCapacity ; i++)
        delete HumanTable[i];
    delete[] HumanTable;
    delete[] HumanFlagTable;
    cout<<"A waggon was destroyed"<<endl;
}

void Waggon::set_HumanFlagTable(int k,int flag)
{
    HumanFlagTable[k]=flag;
}

int Waggon::get_HumanFlagTable(int k)
{
    return HumanFlagTable[k];
}

void Waggon::setdata(int maxCap,int Cap)
{
    maxCapacity=maxCap;
    Capacity+=Cap;    
}

int Waggon::get_mCapacity()
{
    return maxCapacity;
}

int Waggon::get_Capacity()
{
    return Capacity;
}

void Waggon::setmoney(int num)
{
    money+=num;
}

void Waggon::setpeoplegotten()
{
    Peoplegotten++;
}

void Waggon::setpeoplenotgotten()
{
    Peoplenotgotten++;
}

int Waggon::getpeoplegotten()
{
    return Peoplegotten;
}

int Waggon::getpeoplenotgotten()
{
    return Peoplenotgotten;
}

int Waggon::get_Money()
{
    return money;
}

class Human *Waggon::get_HTable(int num)
{
    return HumanTable[num];
}

void Human::setdata(int ticket,int low)
{
    Ticket_Property=ticket;                     
    LowerPrice=low;
}

int Human::get_TicketP()
{
    return Ticket_Property;                     //Get if he has a ticket
}

int Human::get_LowerP()
{
    return LowerPrice;                          //Get if he deserves a lower price ticket
}


int main(int argc,char *argv[])
{
    
    N=atoi(argv[1]);                            //Read from command line the number

    int wagg,cap;
    cout<<"Give me the totalWaggons"<<endl;
    cin>>wagg;                                  //totalWaggons
    cout<<"Give me the MaxCapacity"<<endl;
    cin>>cap;                                   //MaxCapacity
    Train Metro(wagg,cap);                      //Create a train
    srand(time(NULL));
    int i,j,totalMoney=0;
    
    for (i=0 ; i<N ; i++)
    {
        cout<<"Station: "<<i+1<<endl<<endl;
        for(j=0 ; j<wagg ; j++)
        {
            cout<<"Waggon: "<<j+1<<endl;
            Metro.Operate(j);       //Operate the Train
        } 
        cout<<endl<<endl;
    }
    Metro.Print(N,wagg);
    return 0;
}