create table employee(ename varchar(20) not null, essn int not null, address varchar(30) not null, salary int, superssn int, dno int not null, primary key (essn));

create table department(dname varchar(20) not null, mgrssn int not null, mgrstartdate varchar(20) not null, dno int not null, primary key(dno));

create table project(pname varchar(20) not null, pno varchar(20) not null, plocation varchar(30) not null, dno int not null, primary key(pno));

create table works_on(essn int not null, pno varchar(20) not null, hours int, primary key(essn, pno));

(1)
select ename
from employee, project, works_on
where pname = "SQL Project" and project.pno=works_on.pno and works_on.essn=employee.essn;

(2)
select ename, address
from employee,department
where dname="Research Department" and salary<=4500 and employee.dno=department.dno;

(3)
select ename
from employee, project, works_on
where project.pno <>"P1" and project.pno=works_on.pno and works_on.essn=employee.essn;

(4)
select ename,dname
from employee,department
where (superssn=(select essn
	from employee
	where ename="张红") )and employee.dno=department.dno;

(5)
select essn
from works_on
where pno = "P1" and essn in(
				select essn from works_on
				where works_on.pno = "P2");

(6)
select ename, employee.essn
from (select count(distinct pno) as all_pno from project) t1,
          (select essn, count(pno) as count_pno from works_on group by essn)t2,
          employee
where t1.all_pno = t2.count_pno and t2.essn=employee.essn;

(7)
select dname 
from(select employee.dno, avg(salary) as avgsalary
	from employee,department
	where employee.dno = department.dno
	group by employee.dno)t1, department
where t1.dno = department.dno and t1.avgsalary>4500;

(8)
select ename
from( select essn, count(pno) as coutp, sum(hours) as sumh
	from works_on
	group by essn)t1, employee
where t1.essn = employee.essn and coutp>=1 and sumh<=3;

(9)
select department.dno, department.dname,avg(salary)
from employee,department
where employee.dno = department.dno
group by department.dno;
