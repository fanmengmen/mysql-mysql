#pragma once
#include<iostream>
#include<string>
#include<ctime>
#include <mysql++/mysql++.h>
#include <mysql++/ssqls.h>
#include <iomanip>
#include <fstream>


using namespace std;
class News
{
    public:
        News();
        ~News();
        int getNewsId();
        int getTittle();
        int getNews_str();
        int getTime();


        void setId(int num);
        void setNews(std::string str);
        void setTime();
        void setPriority(int );


    private:
        
        int id;
        /*新闻消息*/
        std::string news_str;
        /*新闻标题*/
        std::string tittle;
        tm time;
        /*设置优先级分1-10*/
        int priority;
        /*写成字符串的形式方便存储在数据库中*/
        std::string news_Id;               
        std::string news_time;
        std::string news_priority;

    public:


};

// The following is calling a very complex macro which will create
// "struct stock", which has the member variables:
//
//   sql_char item;
//   ...
//   sql_mediumtext_null description;
//
// plus methods to help populate the class from a MySQL row.  See the
// SSQLS sections in the user manual for further details.
// sql_create_5(stock,
//     1, 5, // The meaning of these values is covered in the user manual
//     mysqlpp::sql_int, id,
//     mysqlpp::sql_char, news_str,
//     mysqlpp::sql_char, tittle,
//     mysqlpp::sql_int, priority,
//     mysqlpp::sql_char, time,           // SSQLS isn't case-sensitive!
// )


/*往名为COV2019的table中添加数据*/
sql_create_5(COV2019,
1, 5, // The meaning of these values is covered in the user manual
mysqlpp::sql_int, id,
mysqlpp::sql_char, news_str,
mysqlpp::sql_char, tittle,
mysqlpp::sql_int, priority,
mysqlpp::sql_char, time)


/*往名为IMAGES的表中插入二进制图片数据*/
sql_create_3(IMAGE,
	1, 3,
	mysqlpp::sql_int, id,
	mysqlpp::sql_blob_null, data,
    mysqlpp::sql_int, img_len)
/*创建表*/




void readImage(const string image_name, char* buffer, int &img_len)
{
    FILE *fp = NULL;
    fp = fopen(image_name.c_str(),"rb");
    if(fp!=NULL)
    {
        fseek( fp, 0, SEEK_END );
        img_len = ftell( fp );
        fseek( fp, 0, SEEK_SET );
        buffer = new char[img_len];
        fread(buffer,1,img_len,fp);
        fclose(fp);
        }
}


void writeImage(const string &image_name, const void * buffer, const int &img_len)
{
    FILE *fp = NULL;
    fp = fopen(image_name.c_str(),"wb");
    fwrite(buffer,1,img_len,fp);
    fclose(fp);
}
