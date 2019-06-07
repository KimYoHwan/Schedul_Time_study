#include<iostream>
#include<fstream>
#include<string>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;

//Time Min
#define Min 9
//Time Max
#define Max 19

//날짜에 대한 클래스 "Day"

class Rul{   
private:
    //수정여부
    string DayName;         //요일
    pair<int,int> Time;      //시간 타임
public:
    Rul(){  this->DayName="NULL";this->Time=make_pair(0,0);} //기본 생성자
    Rul(string Name, int Start, int End){ this->DayName=Name; Time=make_pair(Start,End); } //클래스 생성자
    ~Rul(){}    //디폴트 소멸자

    string Get_Day(){return DayName;}   //요일 이름 반환
    int Get_StartTime(){return this->Time.first;}   //스타트 시간 반환  
    int Get_EndTime(){return this->Time.second;}    //끝나는 시간 반환  

    //기본 연산자 오버로딩
    //== != < > <= >=
    bool operator==(const Rul &p)const
    {
        if(this->DayName==p.DayName&&this->Time==p.Time) return true;
        else return false;
    }
    bool operator!=(const Rul &p)const
    {   return !(*this==p);}


    //사용자 정의 함수
    //Mon = 1   Tue = 2 Wed = 3 Thu =4 Fri =5 not exist 0
    int Name_Number(){
        if(this->DayName == "Mon"||this->DayName=="월")
            return 1;
        else if(this->DayName == "Tue"|| this->DayName =="화")
            return 2;
        else if(this->DayName == "Wed"|| this->DayName == "수")
            return 3;
        else if(this->DayName == "Thu" || this->DayName == "목")
            return 4;
        else if(this->DayName == "Fri" || this->DayName == "금")
            return 5;
        else if(this->DayName == "*" )
            return 6;
        else 
            return 0;
    }
    
    //I/O 연산자 오버로딩 
    friend ostream& operator<<(ostream& os,const Rul& day);
    friend istream& operator>>(istream &in,Rul &day);


};

//기본 Out Stream
ostream& operator<<(ostream& os,const Rul& day)
{
    os<<day.DayName<<"\t"<<day.Time.first<<"\t"<<day.Time.second<<"\t";
    return os;
}
//기본 Input Stream
istream& operator>>(istream &in,Rul &day)
{
    int s=0;int e=0;
    do{
        //Day Name 입력값 제어
        cout<<"Day (Mon~Fri or 월 ~ 금 ) : ";
        in>>day.DayName;
        in.clear();
        in.ignore(100,'\n');
    }while(day.Name_Number()==0);
   
    do{
        //Start Time 입력값 제어
        cout<<"Start_Time 9~18 : ";in>>s;
        in.clear();
        in.ignore(100,'\n');
    }while(!(s>=Min&&s<=Max-1));
    
    do{
        //End_Time 입력값 제어
        cout<<"End_Time is "<<(s+1)<<" ~ 19 : "; in>>e;
        in.clear();
        in.ignore(100,'\n');
    } while (!(e>s && e<=Max));

    day.Time=make_pair(s,e);
    return in;
}

