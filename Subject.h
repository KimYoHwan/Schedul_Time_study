#include<iostream>
#include"Day.h"
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<iomanip>

using namespace std;

//과목 클래스 : 상속 Day를 상속
class Subject
{
private:
    int Grade_Score;        //학점
    string Name;            //과목 명
    string Type;            //과목 타입 
    vector<Day> Schedule;   //과목 일정
    int Total_Time;      //통합소요시간
    int Count;            //schedule 카운트 수
    bool empty;         //생성여부

public:
    Subject(){
        this->Grade_Score=0;
        this->Total_Time=0;
        this->Count=0;
        this->empty=true;
    }
     
    Subject(int g,string n, string t, vector<Day> day)
    {
        this->Grade_Score=g;
        this->Name=n;
        this->Type=t;
        this->Schedule = day;
        for(int i=0;i<day.size();i++)
            this->Total_Time +=day[i].Get_Total_Time();
        sort(Schedule.begin(),Schedule.end(),Compare);
        this->Count=this->Schedule.size();
        this->empty=false;
    }
    ~Subject(){}

    int Get_GradeScore(){return this->Grade_Score;}
    string Get_name(){return this->Name;}
    string Get_Type(){return this->Type;}
    int Get_Count(){return this->Count;}
    int Get_TotalTime(){return this->Total_Time;}
    void Set_Name(string name){
        this->Name=name;
    }
    Day LastTime(){return this->Schedule[Count-1];}
    vector<Day> Get_DayVecot(){return this->Schedule;}
    void Set_Emptry(){this->empty=false;}
    bool is_emptry()
    {
        return empty;
    }

    int Type_Number()
    {
        if(this->Type== "전필")
            return 1;
        else if(this->Type == "전선")
            return 2;
        else if(this->Type == "교양")
            return 3;
        else if(this->Type == "*")
            return 4;
        else 
            return 0;
    }

    void Info()
    {
        cout<<"Subject Info"<<endl;
        cout<<"학점 :\t"<<Get_GradeScore()<<endl;
        cout<<"과목명 :\t"<<Get_name()<<endl;
        cout<<"과목타입(전필/전선/교양) :\t"<<this->Type<<endl;
        cout<<"과목요일 :"<<endl;
        for(int i=0;i<this->Schedule.size();i++)
        {
            cout<<"<"<<this->Schedule[i].Get_Day()<<", "<<this->Schedule[i].Get_StartTime()<<", "<<this->Schedule[i].Get_EndTime()<<" >"<<endl;
        }
        cout<<"일주일에 수업시간 : "<<this->Total_Time<<endl;
    }

    //I/O 연산자 오버로딩 
    friend ostream& operator<<(ostream& os,const Subject& s1);
    friend istream& operator>>(istream &in, Subject &s1);

    //File I/O 연산자 오버로딩
    friend ofstream& operator<<(ofstream & os , const Subject & s1);
    friend ifstream& operator>>(ifstream & in ,  Subject & s1);
};

//사용자 정의 함수
//체크용 함수
bool Chack(string C)
{
    if(C == "Mon"||C=="월"||C=="Tue"|| C =="화"||C == "Wed"|| C== "수"||C== "Thu" || C == "목" ||C== "Fri" || C == "금")
        return true;
    else 
        return false;
}

//Sort용 함수       //학점(큰)->전선 -> 마지막 시간 -> 총 소요시간 -> 일주일에 수업 일 수
bool Subject_Compare(Subject &s1, Subject &s2)
{
    
    if(s1.Get_GradeScore()==s2.Get_GradeScore())
    {
        if(s1.Type_Number()==s2.Type_Number())
        {
            
            if(s1.LastTime()==s2.LastTime())
            {
                if(s1.Get_TotalTime()==s2.Get_TotalTime())
                {
                    return s1.Get_Count()<s2.Get_Count();
                }else
                {
                    return s1.Get_TotalTime()<s2.Get_TotalTime();
                }
                
            }else
            {
                return s1.LastTime() < s2.LastTime();
            }
            
        }else
        {
            return  s1.Type_Number() < s2.Type_Number();
        }
        
    }else
    {
        return s1.Get_GradeScore()>s2.Get_GradeScore();
    }
    
}


//I/O 연산자 오버로딩 
//출력 연산
ostream& operator<<(ostream& os,const Subject& s1)
{
    os<<s1.Grade_Score<<"\t"<<s1.Name<<"\t"<<s1.Type<<"\t";
    for(int i=0;i<s1.Schedule.size();i++)
        os<<s1.Schedule[i];
    return os;
}


//입력 연산
//중복제거 여지;
istream& operator>>(istream &in, Subject &s1)
{
    cout<<"-Subject Input-"<<endl;
    do{
        cout<<"학점 : ";
        in>>s1.Grade_Score;
        in.clear();
        in.ignore(100,'\n');
    }while(s1.Grade_Score>3 || s1.Grade_Score <=0);
    cout<<"과목명 : ";in>>s1.Name;
    do{
        cout<<"과목타입(전필/전선/교양) : ";in>>s1.Type;
        in.clear();
        in.ignore(100,'\n');
    }while(s1.Type_Number()==0);

    char check ='N';
    do{
        Day day ;
        in>>day;
        in.clear();
        in.ignore(100,'\n');
        s1.Schedule.push_back(day);
        cout<<"날짜 추가 ? (Y/N)";in>>check;
        in.clear();
        in.ignore(100,'\n');
    }while(check=='Y');
    sort(s1.Schedule.begin(),s1.Schedule.end(),Compare);

    s1.Total_Time=0;
    for(int i=0;i<s1.Schedule.size();i++)
    {
        s1.Total_Time+=s1.Schedule[i].Get_Total_Time();
    }
    s1.Count=s1.Schedule.size();
    s1.empty=false;
    return in;
}



//File I/O 연산자 오버로딩
ofstream& operator<<(ofstream & os , const Subject & s1)
{
    os<<s1.Grade_Score<<"\t"<<s1.Name<<"\t"<<s1.Type<<"\t";
    for(int i=0;i<s1.Schedule.size();i++)
        os<<s1.Schedule[i];
    return os;
}
ifstream& operator>>(ifstream & in ,  Subject & s1)
{
    in>>s1.Grade_Score;
    in>>s1.Name;
    if(s1.Grade_Score<1 || s1.Grade_Score>3)
    {
        cout<<s1.Name<<"학점 입력 실패! 1~3"<<endl;
        exit(1);
    }
    
    in>>s1.Type;
    if(!(s1.Type_Number()))
    {
        cout<<s1.Name<<"전선|전필|교양 Error"<<endl;
        exit(1);
    }
    
    while(1)
    {
        string Check;
        int Cur = in.tellg();
        in>>Check;
        in.seekg(Cur,ios::beg);
        if(!Chack(Check))
        {
            break;
        }
        Day day;
        in>>day;
        s1.Schedule.push_back(day);
        s1.Total_Time+=day.Get_Total_Time();
    }
    sort(s1.Schedule.begin(),s1.Schedule.end(),Compare);
    s1.Count=s1.Schedule.size();
    s1.empty=false;
    return in;
}



// //Test.cpp
// int main(void)
// {
//     vector<Subject> Sch1;
//     ifstream in("Test.txt");
//     ofstream os("Test1.txt");
//     int Cur = in.tellg();

//     while(Cur!=-1)
//     {
        
//         Subject sub1;
//         in>>sub1;
//         Sch1.push_back(sub1);
//         cout<<sub1<<endl;
//         Cur=in.tellg();
//     }

//     sort(Sch1.begin(),Sch1.end(),Subject_Compare);
//     for(int i=0;i<Sch1.size();i++)
//     {
//         os<<Sch1[i]<<endl;
//     }
    
//     os.close();
//     in.close();
//     return 0;
// }