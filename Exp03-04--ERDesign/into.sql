create table user(
	username varchar(50) not null,
	sex varchar(10),
	birthday varchar(20),
	address varchar(50),
	password varchar(30),
	primary key(username)
);
create table experience(
	username varchar(50) not null,
	degree varchar(20),
	school varchar(50),
	working_place varchar(50),
	foreign key(username) references user(username)
);
create table hobbies(
	username varchar(50) not null,
	hobby varchar(20),
	foreign key(username) references user(username)
);
create table friend(
	username varchar(50) not null,
	friend_name varchar(50) not null,
	list_name varchar(50) not null,
	foreign key(username) references user(username)
);
create table friend_list(
	username varchar(50) not null,
	list_name varchar(50) not null,
	foreign key(username) references user(username)
);
create table state(
	username varchar(50) not null,
	content varchar(200),
	state_index int,
	foreign key(username) references user(username)
);
create table reply(
	username varchar(50) not null,
	state_index int,
	relpy_name varchar(50) not null,
	reply_content varchar(200),
	foreign key(username) references user(username)
);
create table message(
	username varchar(50) not null,
	message_content varchar(200),
	message_name varchar(50) not null,
	foreign key(username) references user(username)
);
insert into experience(username,degree,school,working_place) VALUES('mine','bach','hit','haerbin');
insert into experience(username,degree,school,working_place) VALUES('mine','tech','shouning','fujian');
insert into hobbies(username,hobby) values('mine','playing pingpang');
insert into hobbies(username,hobby) values('mine','loving computer');
insert into message(username,message_content,message_name) values('mine','hello,nice of you','tim');
insert into message(username,message_content,message_name) values('mine','java is nice','whl');
insert into friend_list(username,list_name) values ('mine','campus');
insert into friend_list(username,list_name) values ('mine','senius');
insert into friend(username,friend_name,list_name) values ('mine','timzxz','campus');
insert into friend(username,friend_name,list_name) values ('mine','foolsin','senius');
insert into friend(username,friend_name,list_name) values ('mine','shiling','campus');
insert into hobbies(username,hobby) values('timzxz','watching something');
insert into hobbies(username,hobby) values('timzxz','loving eating');
insert into experience(username,degree,school,working_place) VALUES('timzxz','seniu','xiaoxue','guangzhou');
insert into experience(username,degree,school,working_place) VALUES('timzxz','suoshi','daxue','heilongjian');
insert into state(username,content) values('timzxz','heiheiheiheihei');
insert into friend(username,friend_name,list_name) values('timzxz','mine','campus');
insert into reply(username,relpy_name,reply_content) values('timzxz','mine','hahahahaha');
