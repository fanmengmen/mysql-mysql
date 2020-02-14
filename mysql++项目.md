# C++ mysql实践

### 1、本项目基于windows10的wsl ubuntu18.04系统，安装了mysql8.0.19.

在安装过程中遇到问题，

参考<https://blog.csdn.net/Dylan_543/article/details/100511759>

**出现的问题：**

[ERROR] [MY-012585] [InnoDB] Linux Native AIO interface is not supported on this platform. Please check your OS documentation and install appropriate binary of InnoDB.

**解决方案：**

**1、删除mysql 8.x** 

```shell
sudo apt-get purge mysql-server mysql-client 

sudo apt-get -y autoremove
```

2、更改Mysql 5.x 为安装首选

```shell
sudo dpkg -i mysql-apt-config_0.8.12-1_all.deb 

sudo apt-get update
```

3、安装Mysql 5.x

```shell
sudo apt-get -y install mysql-server

sudo service mysql start
```

(启动看看是否可以运行成功)

4、更改Mysql 8.x为安装首选

```shell
sudo dpkg -i mysql-apt-config_0.8.12-1_all.deb 

sudo apt-get update
```

5、修改脚本文件

```
sudo vi /etc/init.d/mysql 
```


（搜索一行“./ usr / share / mysql / mysql-helpers”并将其更改为
“./usr/share/mysql-8.0 / MySQL的帮助程序“）

6、启动Mysql

```
Service mysql start
```





2、该项目使用mysql++库用C++使用mysql数据库

参考<https://tangentsoft.com/mysqlpp/home>

下载源代码并编译。

Mysql++是对mysql C API的封装，需要通过下面命令安装mysql-client

```
sudo apt-get install libmysqlclient-dev
```

如果已经安装了仍然找不到mysql-client，通过下面命令知名位置

```shell
locate mysqlclient

./configure --prefix=/usr --with-mysql-lib=/usr/lib/x86_64-linux-gnu


```

具体配置自行查看configure文件，让后make，make install完成编译。





### 3、该项目使用CMAKE编译。

具体find mysql++库的cmake语言如下：

```cmake
FIND_PATH(MYSQLPP_INCLUDE_PATH mysql++.h /usr/include/mysql++/)

FIND_PATH(MYSQL_INCLUDE_PATH mysql.h /usr/include/mysql/)

IF(MYSQL_INCLUDE_PATH AND MYSQLPP_INCLUDE_PATH)

  SET(MYSQLPP_INCLUDE_DIR

​    ${MYSQLPP_INCLUDE_PATH}

​    ${MYSQL_INCLUDE_PATH}

  )

ENDIF(MYSQL_INCLUDE_PATH AND MYSQLPP_INCLUDE_PATH)

FIND_LIBRARY(MYSQLPP_LIBRARIES mysqlpp)

IF (MYSQLPP_INCLUDE_DIR AND MYSQLPP_LIBRARIES)

   SET(MYSQLPP_FOUND TRUE)

ELSE (MYSQLPP_INCLUDE_DIR AND MYSQLPP_LIBRARIES)

   SET(MYSQLPP_FOUND FALSE)

ENDIF (MYSQLPP_INCLUDE_DIR AND MYSQLPP_LIBRARIES)

IF(MYSQLPP_FIND_REQUIRED)

  IF(MYSQLPP_FOUND)

  ELSE(MYSQLPP_FOUND)

​    MESSAGE(FATAL_ERROR "Could not find mysqlpp")

  ENDIF(MYSQLPP_FOUND)

ENDIF(MYSQLPP_FIND_REQUIRED)

MARK_AS_ADVANCED(MYSQLPP_LIBRARIES MYSQLPP_INCLUDE_DIR)
```

最后将程序链接动态链接库



### 4、该项目实现mysql数据库对table各种数据类型的增删查改

常用数据库语言

```shell
mysql -u username -p databasename #进入数据库服务器
```

```mysql
1、说明：创建数据库
CREATE DATABASE database-name
2、说明：删除数据库
drop database dbname
3、说明：备份sql server
--- 创建 备份数据的 device
USE master
EXEC sp_addumpdevice 'disk', 'testBack', 'c:\mssql7backup\MyNwind_1.dat'
--- 开始 备份
BACKUP DATABASE pubs TO testBack
4、说明：创建新表
create table tabname(col1 type1 [not null] [primary key],col2 type2 [not null],..)
根据已有的表创建新表：
A：create table tab_new like tab_old (使用旧表创建新表)
B：create table tab_new as select col1,col2… from tab_old definition only
5、说明：删除新表
drop table tabname
6、说明：增加一个列
Alter table tabname add column col type
注：列增加后将不能删除。DB2中列加上后数据类型也不能改变，唯一能改变的是增加varchar类型的长度。
7、说明：添加主键： Alter table tabname add primary key(col)
说明：删除主键： Alter table tabname drop primary key(col)
8、说明：创建索引：create [unique] index idxname on tabname(col….)
删除索引：drop index idxname
注：索引是不可更改的，想更改必须删除重新建。
9、说明：创建视图：create view viewname as select statement
删除视图：drop view viewname
10、说明：几个简单的基本的sql语句
选择：select * from table1 where 范围
插入：insert into table1(field1,field2) values(value1,value2)
删除：delete from table1 where 范围
更新：update table1 set field1=value1 where 范围
查找：select * from table1 where field1 like ’%value1%’ ---like的语法很精妙，查资料!
排序：select * from table1 order by field1,field2 [desc]
总数：select count as totalcount from table1
求和：select sum(field1) as sumvalue from table1
平均：select avg(field1) as avgvalue from table1
最大：select max(field1) as maxvalue from table1
最小：select min(field1) as minvalue from table1
11、说明：几个高级查询运算词
A： UNION 运算符
UNION 运算符通过组合其他两个结果表（例如 TABLE1 和 TABLE2）并消去表中任何重复行而派生出一个结果表。当 ALL 随 UNION 一起使用时（即 UNION ALL），不消除重复行。两种情况下，派生表的每一行不是来自 TABLE1 就是来自 TABLE2。
B： EXCEPT 运算符
EXCEPT 运算符通过包括所有在 TABLE1 中但不在 TABLE2 中的行并消除所有重复行而派生出一个结果表。当 ALL 随 EXCEPT 一起使用时 (EXCEPT ALL)，不消除重复行。
C： INTERSECT 运算符
INTERSECT 运算符通过只包括 TABLE1 和 TABLE2 中都有的行并消除所有重复行而派生出一个结果表。当 ALL 随 INTERSECT 一起使用时 (INTERSECT ALL)，不消除重复行。
注：使用运算词的几个查询结果行必须是一致的。
12、说明：使用外连接
A、left （outer） join：
左外连接（左连接）：结果集几包括连接表的匹配行，也包括左连接表的所有行。
SQL: select a.a, a.b, a.c, b.c, b.d, b.f from a LEFT OUT JOIN b ON a.a = b.c
B：right （outer） join:
右外连接(右连接)：结果集既包括连接表的匹配连接行，也包括右连接表的所有行。
C：full/cross （outer） join：
全外连接：不仅包括符号连接表的匹配行，还包括两个连接表中的所有记录。
12、分组:Group by:
  一张表，一旦分组完成后，查询后只能得到组相关的信息。
 组相关的信息：（统计信息） count,sum,max,min,avg  分组的标准)
    在SQLServer中分组时：不能以text,ntext,image类型的字段作为分组依据
 在selecte统计函数中的字段，不能和普通的字段放在一起；
13、对数据库进行操作：
 分离数据库： sp_detach_db; 附加数据库：sp_attach_db 后接表明，附加需要完整的路径名
14.如何修改数据库的名称:
sp_renamedb 'old_name', 'new_name'
```

更高阶的mysql语言参考：<https://www.cnblogs.com/bchjazh/p/5997728.html>

在mysqlpp中可以通过

```c++
 mysqlpp::Connection lianjie(false);

lianjie.connect(sql.db_name,sql.server,sql.user,sql.password)

mysqlpp::Query query = lianjie.query("select * from IMAGE");

query << " mysql语言"；
```

的方式实现mysql数据库的操作，

也可以用下面的函数构建表结构体类型。

```
/*往名为COV2019的table中添加数据*/

sql_create_5(COV2019,

1, 5, // The meaning of these values is covered in the user manual

mysqlpp::sql_int, id,

mysqlpp::sql_char, news_str,

mysqlpp::sql_char, tittle,

mysqlpp::sql_int, priority,

mysqlpp::sql_char, time)
```

具体参见<https://tangentsoft.com/mysqlpp/doc/html/userman/>

### 5、mysql服务器重启后，mysql服务启动失败

出现mysqld_safe Directory ‘/var/run/mysqld’ for UNIX socket file don’t exists

由于/var/run/mysqld 是在临时文件夹中，当关机以后，该文件夹会消失。

暂时解决办法，

```shell
mkdir -p /var/run/mysqld
chown mysql:mysql /var/run/mysqld
/usr/bin/mysqld_safe --skip-grant-tables &
```



### 6、C语言读写二进制文件到内存中

c语言中用fread()，和fwrite()读写二进制文件。

```c
 fp = fopen(image_name.c_str(),"rb");

​        if(fp!=NULL)

​        {

​            fseek( fp, 0, SEEK_END );

​            img_len = ftell( fp );

​            fseek( fp, 0, SEEK_SET );

​            buffer = new char[img_len];

​            fread(buffer,1,img_len,fp);

​            fclose(fp);

​        }
```

  

```
      fp = fopen("250_new.jpg","wb");

​        fwrite(out[0]["data"],1,img_len,fp);

​        fclose(fp);
```

