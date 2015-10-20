drop table zipcodes cascade constraints;
create table zipcodes (
  zip      number(5),
  city     varchar2(30),
  primary key (zip));

drop table workers cascade constraints;
create table workers (
  wno      number(4) not null primary key, 
  wname    varchar2(30),
  zip      number(5) references zipcodes,
  hdate    date);

drop table parts cascade constraints;
create table parts(
  pno      number(5) not null primary key,
  pname    varchar2(30),
  qoh      integer check(qoh >= 0),
  price    number(6,2) check(price >= 0.0),
  olevel   integer);

drop table customers cascade constraints;
create table customers (
  cno      number(5) not null primary key,
  cname    varchar2(30),
  street   varchar2(30),
  zip      number(5) references zipcodes,
  phone    char(12));
 
drop table orders cascade constraints;
create table orders (
  ono      number(5) not null primary key,
  cno      number(5) references customers,
  wno      number(4) references workers,
  received date,
  shipped  date);

drop table odetails cascade constraints;
create table odetails (
  ono      number(5) not null references orders,
  pno      number(5) not null references parts,
  qty      integer check(qty > 0),
  sfee     number(6,2) check(sfee >= 0.0),
  primary key (ono,pno));

insert into  zipcodes values
  (67226,'Wichita');
insert into  zipcodes values
  (60606,'Fort Dodge');
insert into  zipcodes values
  (50302,'Kansas City');
insert into  zipcodes values
  (54444,'Columbia');
insert into  zipcodes values
  (66002,'Liberal');
insert into  zipcodes values
  (61111,'Fort Hays');
insert into  zipcodes values
  (47907,'West Lafayette');

insert into workers values
  (1000,'Jones',67226,'12-DEC-95');
insert into workers values
  (1001,'Smith',60606,'01-JAN-92');
insert into workers values
  (1002,'Brown',50302,'01-SEP-94');

insert into parts values
  (10506,'Land Before Time I',200,19.99,20);
insert into parts values
  (10507,'Land Before Time II',156,19.99,20);
insert into parts values
  (10508,'Land Before Time III',190,19.99,20); 
insert into parts values
  (10509,'Land Before Time IV',60,19.99,20);
insert into parts values
  (10601,'Sleeping Beauty',300,24.99,20);
insert into parts values
  (10701,'When Harry Met Sally',120,19.99,30);
insert into parts values
  (10800,'Dirty Harry',140,14.99,30);
insert into parts values
  (10900,'Dr. Zhivago',100,24.99,30);

insert into customers values
  (1111,'Charles','123 Main St.',67226,'316-636-5555');
insert into customers values
  (2222,'Bertram','237 Ash Avenue',67226,'316-689-5555');
insert into customers values
  (3333,'Barbara','111 Inwood St.',60606,'316-111-1234');
insert into customers values
  (4444,'Jorge','131 State St.',47907,'765-111-1884');
insert into customers values
  (5555,'Jannes','41 1st St.',47907,'765-122-2232');

insert into orders values
  (1020,1111,1000,'10-DEC-94','12-DEC-94');
insert into orders values
  (1021,1111,1000,'12-JAN-95','15-JAN-95');
insert into orders values
  (1022,2222,1001,'13-FEB-95','20-FEB-95');
insert into orders values
  (1023,3333,1000,'20-JUN-97',null);
insert into orders values
  (1024,4444,1002,'13-APR-95','17-APR-95');
insert into orders values
  (1025,4444,1000,'25-APR-95','30-APR-95');
insert into orders values
  (1026,2222,1001,'3-JAN-96','8-JAN-96');

insert into odetails values
  (1020,10506,1,0.0);
insert into odetails values
  (1020,10507,1,4.0);
insert into odetails values
  (1020,10508,2,5.0);
insert into odetails values
  (1020,10509,3,5.0);
insert into odetails values
  (1021,10601,4,0.0);
insert into odetails values
  (1022,10601,1,3.0);
insert into odetails values
  (1022,10701,1,0.0);
insert into odetails values
  (1023,10800,1,0.0);
insert into odetails values
  (1024,10900,1,0.0);
insert into odetails values
  (1024,10506,1,0.0);
insert into odetails values
  (1025,10601,2,5.0);
insert into odetails values
  (1026,10508,1,0.0);
insert into odetails values
  (1026,10509,1,0.0);
insert into odetails values
  (1023,10900,1,0.0);

