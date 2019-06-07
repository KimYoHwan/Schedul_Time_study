#include "Rul.h"
#include "Subject.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

//전역변수
string week[5] = {"월요일", "화요일", "수요일", "목요일",
                  "금요일"}; //출력용 변수
string Time[9] = {"09:00",  "10:00", "11:00", "12:00", "13:00",
                  "14:00", "15:00", "17:00", "18:00"}; //출력용 변수

//사용자 정의 외부 함수
// Get_SubjectInfo 의 무슨요일 과목인가
int week_number(string week1) {
  for (int i = 0; i < 5; i++) {
    if (week[i] == week1)
      return i;
  }
  return -1;
}

class TimeSchedul {
private:
  vector<Subject> schedul; // todo 과목들의 집합
  vector<Rul> rul;         // todo 공강 집합
  Subject Time_Set[9][5];
  vector<string> log;
  string logs;
public:
  TimeSchedul(){};
  ~TimeSchedul(){};
  TimeSchedul(vector<Subject> set) { schedul = set; };
 
  //! 클래스 내부 함수
  //* 과목 추가
  void ADD_subject();
  void ADD_subject(Subject add_subject);
  //* 과목 변경
  void Chaing_Subject();
  //* 과목 검색
  void Select_Subject();
  //* 과목 삭제
  void Delete_Subject();
  //* 과목 보여주기
  void Show_Subject();
  //* 시간표에 넣기
  void Set_Time(const int &Score);
  //* 시간표에서 검색
  void Show_Subjcect(string week1, int Time);
  //* 시간표 클리어
  void Set_Clear();
  //* 공강 시간 셋팅
  void SetRul();
  //* 공강 시간 추가(Rul)
  void ADD_Rul();
  //* 공강 시간 삭제(Rul Delete)
  void Delete_Rul();
  void Show_Rul();
  //* 로그 추가하기
  void ADD_log(const string s){log.push_back(s);};
  //* 로그 보여주기
  void Show_Log();
  //* 파일 내보내기
  void OutFile();
  //* 파일 가져오기
  void InPutFile();
  
  // Out 결과 출력
  friend ostream &operator<<(ostream &os, const TimeSchedul &t1);
  friend ofstream &operator<<(ofstream &os, const TimeSchedul &t1);
};

// ! 클래스 내부 함수
//* 과목 추가
void TimeSchedul::ADD_subject() {
  Subject s1;
  cin >> s1;
  schedul.push_back(s1);
  logs=s1.Get_name();
  logs.append("과목을 추가하였습니다.");
  log.push_back(logs);
  sort(schedul.begin(), schedul.end(), Subject_Compare);
}
void TimeSchedul::ADD_subject(Subject add_subject) {
  schedul.push_back(add_subject);
  logs=add_subject.Get_name();
  logs.append("과목을 추가하였습니다.");
  log.push_back(logs);
  sort(schedul.begin(), schedul.end(), Subject_Compare);
}
//* 과목 변경
void TimeSchedul::Chaing_Subject() {
  cout << "변경할 과목명 : ";
  string name;
  int i;
  cin >> name;
  for (i = 0; i < schedul.size(); i++) {
    if (schedul[i].Get_name() == name) {
      cout << "변경할 과목을 찾았습니다." << endl;
      Subject sch1;
      cin >> sch1;
      schedul[i]=sch1;
      sort(schedul.begin(), schedul.end(), Subject_Compare);
      logs = name;
      logs.append(" 과목을 변경 했습니다.");
      log.push_back(logs);
      return;
    }
  }
  logs = name;
  logs.append(" 변경할 과목을 찾지 못했습니다.");
  log.push_back(logs);
}
//* 과목 검색
void TimeSchedul::Select_Subject() {
  cout << "검색할 과목명: ";
  string name;
  int i;
  cin >> name;
  for (i = 0; i < schedul.size(); i++) {
    if (schedul[i].Get_name() == name) {
      cout << "데이터를 찾았습니다.";
      logs = name;
      logs.append(" 과목을 검색했습니다.");
      log.push_back(logs);
      schedul[i].Info();
      return;
    }
  }
  cout << "데이터를 찾지 못했습니다." << endl;
  logs = name;
  logs.append(" 과목을 검색에 실패했습니다.");
  log.push_back(logs);
}

//* 과목 삭제
void TimeSchedul::Delete_Subject() {
  string name;
  cout << "삭제할 과목명 : ";
  cin >> name;
  logs = name;

  vector<Subject>::iterator iter1;
  for (iter1 = schedul.begin(); iter1 != schedul.end();) {
    if (iter1->Get_name() == name) {
      cout << name << " 과목을 찾았습니다." << endl;
      iter1 = schedul.erase(iter1);
      logs.append(" 과목을 삭제했습니다.");
      log.push_back(logs);
      return;
    } else {
      iter1++;
    }
  }
  cout << name << "과목을 찾지 못했습니다." << endl;
  logs.append(" 과목을 찾지 못했습니다.");
  log.push_back(logs);
}
//* 과목 보여주기
  void TimeSchedul::Show_Subject()
  {
    for (int i = 0; i < schedul.size(); i++)
      cout << schedul[i] << endl;
  }
//* 시간표에 넣기
void TimeSchedul::Set_Time(const int &Score) {
  // todo 유효성 변수 1: 검사통과, 0; 검사 실패
  int check = 1;
  // todo 최대학점까지 왔는지 체크
  int Count = 0;
  //? 유효성 검사
  for (int i = 0; i < schedul.size(); i++) {

    //? 학점이 들어갈 수 있나 없나.
    if (Count + schedul[i].Get_GradeScore() > Score) {
      continue;
    } else if (Count == Score) {
      break;
    }
    vector<Day> day = schedul[i].Get_DayVecot();
    //? 과목의 유효성은 : 해당 과목의 day안에 있는 시간들이 들어갈 수 있나
    //없나로 판단
    for (int j = 0; j < day.size(); j++) {
      for (int k = day[j].Get_StartTime(); k < day[j].Get_EndTime(); k++) {
        if (Time_Set[k - 9][day[j].Name_Number() - 1].is_emptry() != 1) {
          check = 0;
          break;
        }
      }
      if (check == 0)
        break;
    }
    if (check == 0) {
      check = 1;
      continue;
    }
    //? 해당과목이 유효성검사를 통과하면 넣기
    for (int j = 0; j < day.size(); j++) {
      for (int k = day[j].Get_StartTime(); k < day[j].Get_EndTime(); k++) {
        Time_Set[k - 9][(day[j].Name_Number()) - 1] = schedul[i];
      }
    }

    Count += schedul[i].Get_GradeScore();
  }
}

//* 시간표 클리어
void TimeSchedul::Set_Clear() {
  sort(schedul.begin(),schedul.end(),Subject_Compare);
  Subject Temp;
  
  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 5; k++)
      Time_Set[i][k] = Temp;
  }
}

//* 일정 확인
void TimeSchedul::Show_Subjcect(string week1, int Time) {
  if (week_number(week1) == -1) {
    cout << "해당요일이 없습니다." << endl;
  } else {
    if (Time >= 9 && Time < 19) {
      if (Time_Set[Time - 9][week_number(week1)].is_emptry()) {
        cout << "해당 시간에는 과목이 없습니다.\n";
      } else {
        cout << Time_Set[Time - 9][week_number(week1)] << endl;
      }
    } else {
      cout << "찾을 시간을 잘못 입력하셨습니다." << endl;
    }
  }
}

//* 공강시간 넣기(Rul)
void TimeSchedul::SetRul() {

  for (int i = 0; i < rul.size(); i++) {
    if (rul[i].Get_Day() == "*") {
      for (int j = 0; j < 5; j++) {
        for (int k = rul[i].Get_StartTime(); k < rul[i].Get_EndTime(); k++) {
          Time_Set[k-9][j].Set_Name("공강");
          Time_Set[k - 9][j].Set_Emptry();
        }
      }
    } else {
      for (int k = rul[i].Get_StartTime(); k < rul[i].Get_EndTime(); k++) {
        Time_Set[k - 9][rul[i].Name_Number() - 1].Set_Name("공강");
        Time_Set[k - 9][rul[i].Name_Number() - 1].Set_Emptry();
      }
    }
  }
}
//* 공강 시간 추가(Rul)
void TimeSchedul::ADD_Rul() {
  Rul day;
  cin >> day;
  rul.push_back(day);
  string name = day.Get_Day();
  logs = name;
  logs.append(" 조건이 추가되었습니다.");
  cout << logs << endl;
  log.push_back(logs);
}

//* 공강 시간 삭제(Rul Delete)
void TimeSchedul::Delete_Rul() {
  int index;
  Rul rus;
  for (int i = 0; i < rul.size(); i++) {
    cout << i + 1 << " \t" << rul[i] << endl;
  }
  cout << "몇 번째 조건을 삭제 하겠습니까? : ";
  cin >> index;
  cin.clear();
  cin.ignore(100,'\n');
  index--;
  if (index < 0 || index >= rul.size()) {
    cout << "없는 조건입니다." << endl;
    logs = "조건을 삭제하지 못했습니다.";
    log.push_back(logs);
    return;
  }
  rus = rul[index];

  vector<Rul>::iterator iter;
  for (iter = rul.begin(); iter != rul.end();) {
    if (*iter == rus) {
      iter = rul.erase(iter);
      logs = "조건을 삭제했습니다.";
      log.push_back(logs);
      return;
    } else {
      iter++;
    }
  }
}
//* 룰 보여주기
void TimeSchedul::Show_Rul(){
  for(int i=0;i<rul.size();i++)
  {
    cout<<rul[i]<<endl;
  }
}
//* 로그 보여주기
void TimeSchedul::Show_Log() {
  if(log.size()<=10)
  {
    for(int i=0;i<log.size();i++)
      cout<<log[i]<<endl;
  }else{
   for (int i = (log.size() - 10); i < log.size(); i++) {
      cout << log[i] << endl;
    }
  }
}
//* 파일 내보내기
void TimeSchedul::OutFile() {
  string name;
  cout << "결과를 출력할 파일명 : ";
  cin >> name;
  ofstream outs;
  outs.open(name);
  cout<<"4"<<endl;
  outs << "-------------------------------------------------------------------"
       << endl;
  outs << "출력된 시간표 " << endl;
  outs << "-------------------------------------------------------------------"
       << endl;
  outs << *this;
  outs << "--------------------------------------------------------------------"
       << endl;
        cout<<"3"<<endl;
  outs << "*과목" << endl;
  for (int i = 0; i < schedul.size(); i++) {
    outs << schedul[i] << endl;
  }
   cout<<"2"<<endl;
  outs << "--------------------------------------------------------------------"
       << endl;
  outs << "* 제외 룰" << endl;
  for (int i = 0; i < rul.size(); i++) {
    outs << rul[i] << endl;
  }
  cout<<"1"<<endl;
  outs << "--------------------------------------------------------------------"
       << endl;
  outs.close();
}
//* 파일 가져오기
void TimeSchedul::InPutFile() {
  string name;
  cout << "가져올 파일명 : ";
  cin >> name;
  ifstream in(name);
  int Cur = in.tellg();

  while (Cur != -1) {

    Subject sub1;
    in >> sub1;
    schedul.push_back(sub1);
    Cur = in.tellg();
  }
  in.close();
  logs = "파일을 적용했습니다.";
  log.push_back(logs);
}
//! 사용자가 사용하는 인터페이스 시작
void Time_START() {
  TimeSchedul Sch1;
  int x;
  int input;
  cout<<"------------------------------------------------------------------------------"<<endl;
  cout<<"프로그램을 시작했습니다. 원하시는 시간표가 제작되기를 바랍니다. Good Luck! "<<endl;
  cout<<"사용자가 최대로 들을 수 있는 학점을 입력해주세여! : ";cin>>x;
  while (1) {
    Sch1.Set_Clear();
    Sch1.SetRul();
    Sch1.Set_Time(x);
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"현재 시간표!"<<endl;
    cout<<Sch1;
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"과목"<<endl;
    Sch1.Show_Subject();
    cout<<"------------------------------------------------------------------------------"<<endl;;
    cout<<"사용자가 지정한 공강 Rul"<<endl;
    Sch1.Show_Rul();
    cout<<"------------------------------------------------------------------------------"<<endl;;
    cout<<"사용자 이용 내역 "<<endl;
    Sch1.Show_Log();
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"기능 : [1] 과목 추가 [2]과목 삭제 [3] 과목 검색 [4] 과목 변경 [5] 공강 추가 \n[6] 공강 삭제 [7] 파일 내보내기 [8] 파일 가져오기 [9]끝내기" <<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"선택화면 : "; cin>>input;cin.clear();cin.ignore(100,'\n');
    switch (input) {
      case 1: //과목 추가:
        Sch1.ADD_subject();
        system("clear");
        break;
      case 2: 
        Sch1.Delete_Subject();
        system("clear");
        break;
      case 3:
        Sch1.Select_Subject();
        cin.ignore(100,'\n');
        char ch;
        cin>>ch;
        cin.ignore(100,'\n');
        system("clear");
        break;
      case 4:
        Sch1.Chaing_Subject();
        system("clear");
        break;
      case 5:
        Sch1.ADD_Rul();
        system("clear");
        break;
      case 6:
        Sch1.Delete_Rul();
        system("clear");
        break;
      case 7:
        Sch1.OutFile();
        system("clear");
        break;
      case 8:
         Sch1.InPutFile();
         system("clear");
        break;
      case 9:
        cout<<"프로그램을 종료하겠습니다. 시간표 프로그램을 이용해주셔셔 감사합니다."<<endl;
        exit(1);
      default:
        Sch1.ADD_log("Not Coomand");
        system("clear");
        break;
    }
  }
}

// Out 결과 출력
ostream &operator<<(ostream &os, const TimeSchedul &t1) {
 os << "\t\t";
  for (int i = 0; i < 5; i++) {
    //os.width(20);
    os << week[i]<<"\t\t";
  }
  os << endl;os << endl;

  for (int i = 0; i < 9; i++) {
    os << Time[i]<<"\t\t";
    for (int j = 0; j < 5; j++) {
      Subject a = t1.Time_Set[i][j];
     
      os << a.Get_name()<<"\t\t";
      
    }
    os << endl;os << endl;
  }
  return os;
}


ofstream &operator<<(ofstream &os, const TimeSchedul &t1) {
os << "\t\t\t";
  for (int i = 0; i < 5; i++) {
    //os.width(20);
    os << week[i]<<"\t\t";
  }
  os << endl;os << endl;

  for (int i = 0; i < 9; i++) {
    os << Time[i]<<"\t\t";
    for (int j = 0; j < 5; j++) {
      Subject a = t1.Time_Set[i][j];
     
      os << a.Get_name()<<"\t\t";
      
    }
    os << endl;os << endl;
  }
  return os;
}

