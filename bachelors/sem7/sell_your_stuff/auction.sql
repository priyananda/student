-- MySQL dump 8.22
--
-- Host: localhost    Database: auction
---------------------------------------------------------
-- Server version	3.23.52

--
-- Table structure for table 'auction'
--

CREATE TABLE auction (
  auctionid int(10) unsigned NOT NULL auto_increment,
  owner varchar(30) NOT NULL default '',
  start_date datetime NOT NULL default '0000-00-00 00:00:00',
  end_date datetime NOT NULL default '0000-00-00 00:00:00',
  nItems smallint(5) unsigned NOT NULL default '0',
  itemid int(10) unsigned NOT NULL default '0',
  description mediumtext NOT NULL,
  auction_value int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (auctionid)
) TYPE=MyISAM;

--
-- Dumping data for table 'auction'
--



--
-- Table structure for table 'bid'
--

CREATE TABLE bid (
  auctionid int(10) unsigned NOT NULL default '0',
  uname varchar(30) NOT NULL default '',
  value int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (auctionid,uname)
) TYPE=MyISAM;

--
-- Dumping data for table 'bid'
--



--
-- Table structure for table 'category'
--

CREATE TABLE category (
  name varchar(20) NOT NULL default '',
  description mediumtext NOT NULL,
  PRIMARY KEY  (name)
) TYPE=MyISAM;

--
-- Dumping data for table 'category'
--


INSERT INTO category VALUES ('sports','All things related to cricket and football');
INSERT INTO category VALUES ('film','Films are the greatest source of entertainment');
INSERT INTO category VALUES ('vehicles','Find the best second hand vehicles');
INSERT INTO category VALUES ('computers','Accessories and consumables for sale');
INSERT INTO category VALUES ('clothes','Nice clothes for all occasions');
INSERT INTO category VALUES ('software','All kinds of free software CD');

--
-- Table structure for table 'item'
--

CREATE TABLE item (
  itemid int(10) unsigned NOT NULL auto_increment,
  name varchar(20) NOT NULL default '',
  cname varchar(20) NOT NULL default '',
  description mediumtext NOT NULL,
  PRIMARY KEY  (itemid)
) TYPE=MyISAM;

--
-- Dumping data for table 'item'
--



--
-- Table structure for table 'session'
--

CREATE TABLE session (
  sessionid varchar(10) NOT NULL default '',
  uname varchar(30) NOT NULL default '',
  expires timestamp(14) NOT NULL,
  PRIMARY KEY  (sessionid)
) TYPE=MyISAM;

--
-- Dumping data for table 'session'
--



--
-- Table structure for table 'users'
--

CREATE TABLE users (
  name varchar(30) NOT NULL default '',
  password varchar(20) NOT NULL default '',
  dob date NOT NULL default '0000-00-00',
  emailid varchar(30) NOT NULL default '',
  creditcard varchar(30) NOT NULL default '',
  points smallint(5) unsigned NOT NULL default '1000',
  autoExpire tinyint(3) unsigned NOT NULL default '5',
  login date NOT NULL default '0000-00-00',
  fname varchar(20) NOT NULL default '',
  sname varchar(20) NOT NULL default '',
  ccdate date NOT NULL default '0000-00-00',
  address tinytext,
  city varchar(20) NOT NULL default '',
  pincode varchar(20) NOT NULL default '',
  occupation varchar(20) NOT NULL default '',
  PRIMARY KEY  (name)
) TYPE=MyISAM;

--
-- Dumping data for table 'users'
--


INSERT INTO users VALUES ('shenoy','asdf','0000-00-00','a@localhost.com','1111111111',1000,5,'0000-00-00','Priyananda','Shenoy','2003-10-10','1/2 Sunshine','Bangalore','560059','student');
INSERT INTO users VALUES ('harish','a','0000-00-00','a@localhost.com','10000',1000,5,'0000-00-00','Harish','Baba','2004-05-06','Home','Bangalore','567897','actor');

