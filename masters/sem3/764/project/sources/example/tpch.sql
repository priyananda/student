create table PART
(
	P_PARTKEY     int,
	P_NAME        varchar(55),
	P_MFGR        char(25),
	P_BRAND       char(10),
	P_TYPE        varchar(25),
	P_SIZE        int,
	P_CONTAINER   char(10),
	P_RETAILPRICE decimal,
	P_COMMENT	  varchar(23)
);

select P_PARTKEY, P_NAME from PART;

select P_NAME from PART where P_SIZE = 0;

update PART set P_NAME='a', P_TYPE=2 where P_SIZE > 0;

create table SUPPLIER
(
  S_SUPPKEY                 int,
  S_NAME                    char(25),
  S_ADDRESS                 varchar(40),
  S_NATIONKEY               int,
  S_PHONE                   char(15),
  S_ACCTBAL                 decimal,
  S_COMMENT                 varchar(101)
);

create table PARTSUPP
(
  PS_PARTKEY                int,
  PS_SUPPKEY                int,
  PS_AVAILQTY               integer,
  PS_SUPPLYCOST             decimal,
  PS_COMMENT                varchar(199)
);
 
create table CUSTOMER
(
  C_CUSTKEY                 int,
  C_NAME                    varchar(25),
  C_ADDRESS                 varchar(40),
  C_NATIONKEY               int,
  C_PHONE                   char(15),
  C_ACCTBAL                 decimal,
  C_MKTSEGMENT              char(10),
  C_COMMENT                 varchar(117)
);
  
create table ORDERS
(
	O_ORDERKEY           int,
	O_CUSTKEY            int,
	O_ORDERSTATUS        char(1),
	O_TOTALPRICE         decimal,
	O_ORDERDATE          date,
	O_ORDERPRIORITY      char(15),
	O_CLERK              char(15),
	O_SHIPPRIORITY       integer,
	O_COMMENT            varchar(79)
);

create table LINEITEM
(
  L_ORDERKEY                     int,
  L_PARTKEY                      int,
  L_SUPPKEY                      int,
  L_LINENUMBER                   integer,
  L_QUANTITY                     decimal,
  L_EXTENDEDPRICE                decimal,
  L_DISCOUNT                     decimal,
  L_TAX                          decimal,
  L_RETURNFLAG                   char(1),
  L_LINESTATUS                   char(1),
  L_SHIPDATE                     date,
  L_COMMITDATE                   date,
  L_RECEIPTDATE                  date,
  L_SHIPINSTRUCT                 char(25),
  L_SHIPMODE                     char(10),
  L_COMMENT                      varchar(44)
);
 
create table NATION
(
	N_NATIONKEY            int,
	N_NAME                 char(25),
	N_REGIONKEY            int,
	N_COMMENT              varchar(152)
);
create table REGION
(
	R_REGIONKEY            int,
	R_NAME                 char(25),
	R_COMMENT			   varchar(152)
);

SELECT
       L_EXTENDEDPRICE , L_DISCOUNT
FROM
       LINEITEM
WHERE
       L_SHIPDATE >= '1981-12-10'
	   and L_TAX  < 0.2;

Select
       l_extendedprice,l_discount
from
       lineitem
where
       l_shipdate >= '1981-11-11'
       and l_shipdate < '1982-11-11'
       and l_discount < 10
	   and l_quantity < 24