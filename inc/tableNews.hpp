#pragma once 
#include "news.hpp"
#include <mysql++/mysql++.h>
#include <iomanip>



class conn
{
    public:
        const char* db_name = "news";
        const char* user = "gf";
        const char* password = "123";
        const char* server = "localhost";
};

class newsTable
{
    public:
        newsTable();
        ~newsTable();

        /*table 的增删更新查看*/
        int Add();

};