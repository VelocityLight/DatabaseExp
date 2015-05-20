#ifndef __LCC__
#define __LCC__
#endif

#include <iostream>
#include <mysql.h>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include <string.h>

using namespace std;

MYSQL mysql_conn;
MYSQL_RES *mysql_result;
MYSQL_ROW mysql_row;
int row_num, col_num;
string command;
string parameters[5];

string querys[50]={"select essn from works_on where pno = ?",
                    "select ename from employee,project,works_on where pname=? and project.pno=works_on.pno and works_on.essn=employee.essn",
                    "select ename, address from employee, department where dname=? and department.dno = employee.dno",
                    "select ename, address from employee, department where department.dno = employee.dno and dname=? and salary<?",
                    "select ename from employee, project, works_on where project.pno <> ? and project.pno = works_on.pno and works_on.essn=employee.essn",
                    "select ename, dname from employee, department where (superssn = (select essn from employee where ename = ?)) and department.dno = employee.dno",
                    "select essn from works_on where pno = ? and essn in ( select essn from works_on where pno = ?)",
                    "select dname from (select employee.dno, avg(salary) as avgsa from employee group by employee.dno)t1, department where t1.avgsa > ? and t1.dno = department.dno",
                    "select ename from (select essn, count(pno) as pnos, sum(hours) as sumh from works_on group by essn)t1, employee where pnos>=? and sumh <=? and t1.essn = employee.essn",
                    "select * from department",
                    "select dname, max(avg_salary) from (select dno, avg(salary) as avg_salary from employee group by dno)t1 natural join department"
};

bool input(){
	int cnt=0,i,j;
	cout << "Enter>> ";
	getline(cin, command);
	for(i=0; i<5; i++)
        parameters[i] = "";
    if(command == "exit") return false;
	//cout << command << endl << command.length() <<endl;
	for(i=0; i< (signed)command.length(); i++){
		if(command[i] == '<'){
            for(j=i+1; command[j] != '>'; j++)
                parameters[cnt]+=command[j];
            cnt++;
         //   cout<<parameters[cnt-1]<<endl;
		}
		if(command[i] == '\''){
            for(j=i+1; command[j] != '\''; j++){
             //   cout << j << command[j]<<endl;
                parameters[cnt] += command[j];
            }
            i = j+1;
		}
		if(command[i] == ',')
            cnt++;
	}
	/*for(int i=0; i<=cnt; i++)
		cout << parameters[i] << endl;*/
	return true;
}

string &replace_all_distinct(string &str,const string& old_value,const string *new_value)
{
    int i=1;
	for(string::size_type pos(0); pos!=string::npos; pos+=new_value[i].length()){
		if((pos=str.find(old_value,pos))!=string::npos)
			str.replace(pos,old_value.length(),new_value[i++]);
		else break;
	}
	return str;
}

bool connect(){
	return mysql_real_connect(&mysql_conn, "localhost", "root", "agao0930yjc", "company", MYSQL_PORT, NULL, 0);
}

int stringtoint(string s){
    int i,ans=0;
    int len = s.length();
    for(i=0; i<s.length(); i++){
        ans += pow(10,len-1)*(s[i]-'0');
        len--;
    }
    return ans;
}

int main(){
	if(mysql_init(&mysql_conn)){
        if(connect()){
		//PreparedStatement *ps;
            while(input()){
                int choice = stringtoint(parameters[0]);
            //    cout << choice << endl;
                if(choice>=1 && choice<=6) parameters[1] = "'"+parameters[1]+"'";
                else if(choice==7){
                    parameters[1] = "'"+parameters[1]+"'";
                    parameters[2] = "'"+parameters[2]+"'";
                }
                querys[choice-1] = replace_all_distinct(querys[choice-1],"?",parameters);
            //    cout << querys[choice-1] << endl;
                char *str = new char[querys[choice-1].length()];
                strcpy(str, querys[choice-1].data());
                mysql_query(&mysql_conn,"set names gb2312");
                mysql_query(&mysql_conn, str);
                mysql_result = mysql_store_result(&mysql_conn);
                row_num = mysql_num_rows(mysql_result);
                col_num = mysql_num_fields(mysql_result);
                for(int i=0; i<row_num; i++){
                    mysql_row = mysql_fetch_row(mysql_result);
                    for(int j=0; j<col_num; j++){
                        printf("%s ",mysql_row[j]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }else{
                int i = mysql_errno(&mysql_conn);
                const char *s = mysql_error(&mysql_conn);
                printf("Connection fails(ERROR %d): %s\n", i, s);
        }
	}else{
		printf("Init Failed.\n");
	}
	mysql_free_result(mysql_result);
    mysql_close(&mysql_conn);
	return 0;
}

/*
company_query -q <1> -p ['P7']
company_query -q <2> -p ['SQL Project']
company_query -q <3> -p ['Research Department']
company_query -q <4> -p ['Research Department','4500']
company_query -q <5> -p ['P1']
company_query -q <6> -p ['周紫']
company_query -q <7> -p ['P1','P2']
company_query -q <8> -p ['4500']
company_query -q <9> -p ['1','3']
company_query -q <10> -p []
*/
