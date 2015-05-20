#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <cstdio>
#include <stdlib.h>

using namespace std;

string xi[7] = {"赵","钱","孙","李","张","叶","周"};
string mi[8] = {"白","赤","橙","红","黄","绿","蓝","紫"};

void employee(){
    ofstream out ("data.txt");
    int essn = 1001,salary = 3000;
    srand((unsigned)time(NULL));
    for(int i=0;i<7;i++){
        for(int j=0;j<8;j++){
            string ename = xi[i] + mi[j];
            out<<"insert into employee values('"<<ename<<"',"<<essn<<",'";
            for(int k=0;k<15;k++)
                out << (char)(rand()%26+'a');
            out << "',";
            out << salary+rand()%3000 << ',';
            out << 1000+(i+1)*8 << ',' << i+1 << ");\n";
            essn += 1;
        }
    }
    out.close();
}

string de[7] = {"ResearchDepartment","运维部","人事部","企发部","研发部","工程部","外联部"};

void department(){
    fstream out ("de_data.txt");
    srand(time(NULL));
    for(int i=0; i<7; i++){
        out<<"insert into department values ( '"<<de[i]<<"',"<<1000+(i+1)*8<<",'";
        for(int j=0; j<8; j++)
            out<<(char)(rand()%10+'0');
        out<<"',"<<i+1<<");\n";
    }
    out.close();
}

void project(){
    fstream out ("pro_data.txt");
    srand(time(NULL));
    for(int i=0; i<10; i++){
        out << "insert into project values('";
        if(i==2) out << "SQL Project";
        else
            for(int j=0; j<2; j++)
                out<<(char)(rand()%26+'A');
        out << "','" << "P" << (char)(i+'0') << "','";
        for(int j=0; j<15; j++)
            out<<(char)(rand()%26+'a');
        if(i==1 || i==2)
            out << "'," << 5 << ");\n";
        else
            out << "'," << rand()%7+1 << ");\n";
    }
    out.close();
}

void works_on(){
    fstream out("wor_data.txt");
    srand(time(NULL));
    for(int i=0; i<56; i++){
        out << "insert into works_on values(" << 1001+i << ",'";
        out << "P"<<(char)(rand()%10+'0') << "'," << rand()%12 << ");\n";
    }
    out << "insert into works_on values(1036,'P2',5);\n";
    out << "insert into works_on values(1036,'P3',10);\n";
    out.close();
}
int main(){
    employee();
    department();
    project();
    works_on();
    return 0;
}
