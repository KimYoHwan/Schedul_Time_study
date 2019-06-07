#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// Time Min
#define Min 9
// Time Max
#define Max 19

//날짜에 대한 클래스 "Day"

class Day {
private:
  //수정여부
  string DayName;      //요일
  pair<int, int> Time; //시간 타임
  int Total_Time = 0;  //시간 소요

public:
  Day() {
    this->DayName = "NULL";
    this->Time = make_pair(0, 0);
    this->Total_Time = 0;
  } //기본 생성자
  Day(string Name, int Start, int End) {
    this->DayName = Name;
    Time = make_pair(Start, End);
    this->Total_Time = End - Start;
  }         //클래스 생성자
  ~Day() {} //디폴트 소멸자

  string Get_Day() { return DayName; }              //요일 이름 반환
  int Get_StartTime() { return this->Time.first; }  //스타트 시간 반환
  int Get_EndTime() { return this->Time.second; }   //끝나는 시간 반환
  int Get_Total_Time() { return this->Total_Time; } //총 소요 시간 반환

  //기본 연산자 오버로딩
  //== != < > <= >=
  bool operator==(const Day &p) const {
    if (this->DayName == p.DayName && this->Time == p.Time &&
        this->Total_Time == this->Total_Time)
      return true;
    else
      return false;
  }
  bool operator!=(const Day &p) const { return !(*this == p); }

  //수정여부
  bool operator<(Day p) {
    if (this->Name_Number() == p.Name_Number()) {
      if (this->Time.first == p.Time.first) {
        return this->Time.second < p.Time.second;
      } else {
        return this->Time.first < p.Time.first;
      }
    } else {
      return this->Name_Number() < p.Name_Number();
    }
  }

  bool operator<=(Day p) {
    if (this->Name_Number() > p.Name_Number()) {
      return false;
    } else if (this->Name_Number() == this->Name_Number()) {
      if (this->Time > p.Time)
        return false;
    }
    return true;
  }

  //사용자 정의 함수
  // Mon = 1   Tue = 2 Wed = 3 Thu =4 Fri =5 not exist 0
  int Name_Number() {
    if (this->DayName == "Mon" || this->DayName == "월")
      return 1;
    else if (this->DayName == "Tue" || this->DayName == "화")
      return 2;
    else if (this->DayName == "Wed" || this->DayName == "수")
      return 3;
    else if (this->DayName == "Thu" || this->DayName == "목")
      return 4;
    else if (this->DayName == "Fri" || this->DayName == "금")
      return 5;
    else
      return 0;
  }

  // I/O 연산자 오버로딩
  friend ostream &operator<<(ostream &os, const Day &day);
  friend istream &operator>>(istream &in, Day &day);

  // File I/O 연산자 오버로딩

  friend ofstream &operator<<(ofstream &os, const Day &day);
  friend ifstream &operator>>(ifstream &in, Day &day);
};

// Vector 사용을 위한 Compare
bool Compare(Day day1, Day day2) {
  if (day1.Name_Number() == day2.Name_Number())
    return day1.Get_StartTime() < day2.Get_StartTime();
  else
    return day1.Name_Number() < day2.Name_Number();
}

//기본 Out Stream
ostream &operator<<(ostream &os, const Day &day) {
  os << day.DayName << "\t" << day.Time.first << "\t" << day.Time.second
     << "\t";
  return os;
}
//기본 Input Stream
istream &operator>>(istream &in, Day &day) {
  int s = 0;
  int e = 0;

  do {
    // Day Name 입력값 제어
    cout << "Day (Mon~Fri or 월 ~ 금 ) : ";
    in >> day.DayName;
  } while (day.Name_Number() == 0);

  do {
    // Start Time 입력값 제어
    cout << "Start_Time 9~18 : ";
    in >> s;
  } while (!(s >= Min && s <= Max - 1));

  do {
    // End_Time 입력값 제어
    cout << "End_Time is " << (s + 1) << " ~ 19 : ";
    in >> e;
  } while (!(e > s && e <= Max));

  day.Time = make_pair(s, e);
  day.Total_Time = e - s;
  return in;
}

// File Out Stream
ofstream &operator<<(ofstream &os, const Day &day) {
  os << day.DayName << "\t" << day.Time.first << "\t" << day.Time.second
     << "\t";
  return os;
}

// File Input Stream
ifstream &operator>>(ifstream &in, Day &day) {
  in >> day.DayName;
  if (day.Name_Number() == 0) {
    cout << "File Error" << endl;
    exit(1);
  }
  int s, e;
  in >> s;
  in >> e;
  if (!(s >= Min && s <= Max - 1)) {
    cout << "Start_Time Error" << endl;
    exit(1);
  }
  if (!(e > s && e <= Max)) {
    cout << "End Time Error" << endl;
    exit(1);
  }
  day.Time = make_pair(s, e);
  day.Total_Time = e - s;
  return in;
}

// int main(void)
// {
//     ifstream in("Test.txt");
//     ofstream out("ReadTest.txt");
//     vector<Day> M;

//     for(int i=0;!in.eof();i++)
//     {
//         Day day;
//         in>>day;
//         M.push_back(day);
//     }
//     for(int i=0;i<M.size();i++)
//     {
//         cout<<M[i]<<endl;
//     }
//     for(int i=0;i<M.size();i++)
//     {
//         out<<M[i]<<endl;
//     }

//     return 0;
// }