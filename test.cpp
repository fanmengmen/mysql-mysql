#include "news.hpp"
#include "tableNews.hpp"
#include<iostream>
#include<mysql++/mysql++.h>
#include<algorithm>

using namespace std;
int main()
{
    mysqlpp::Connection lianjie(false);
    conn sql;
    // News news;
    // sql.db_name,sql.user,sql.password,sql.server
    if(lianjie.connect(sql.db_name,sql.server,sql.user,sql.password));
    {
        cout << "Connect sucessfully ! " << endl;
        COV2019 row;
        vector<COV2019> cov2019;
        mysqlpp::Query query = lianjie.query("select * from COV2019");
        query.storein(cov2019);
        row.id = 3;
        row.news_str = "昨日，全国新冠状肺炎确诊累计17205例，死亡361例，专家提醒闭门不出。";
        row.tittle = "感染人数";
        row.priority = 10;
        row.time = "2020/02/02";
        COV2019 news(4,"昨日，全国新冠状肺炎确诊累计20438例，死亡425例，专家提醒闭门不出。","感染人数",10,"2020/02/03");
        COV2019 news_1(4,"昨日，全国新冠状肺炎确诊累计*例，死亡*例，专家提醒闭门不出。","感染人数",10,"2020/02/04");
        cout << count(cov2019.begin(),cov2019.end(),news) << endl;
        /*如果已经存在，不在插入该条消息，如果不存在，将消息插入到数据库*/
        if(!count(cov2019.begin(),cov2019.end(),news))
        {
            mysqlpp::Query queryInsert = lianjie.query();
            queryInsert.insert(news);

            // Show the query about to be executed.
            cout << "Query: " << queryInsert << endl;

            // Execute the query.  We use execute() because INSERT doesn't
            // return a result set.
            queryInsert.execute();

            // // Retrieve and print out the new table contents.
            // print_stock_table(queryInsert);
        }

        query = lianjie.query("select * from COV2019");
        if (mysqlpp::StoreQueryResult res = query.store()) {

            // 打印每一列数据
            cout << "We have:" << endl;
            mysqlpp::StoreQueryResult::const_iterator it;
            cout.setf(ios::left);
            cout << setw(9) << "ID" <<
                    setw(80) << "news_str" <<
                    setw(30) << "tittle" <<
                    setw(30) << "priority" << 
                    setw(30) << "time" << endl;

            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res.num_rows(); ++i) {
                cout.setf(ios::left);
                cout << setw(9) << res[i]["id"] <<
                        setw(80) << res[i]["news_str"] << 
                        setw(30) << res[i]["tittle"] << 
                        setw(30) << res[i]["priority"] << 
                        setw(30) << res[i]["time"] <<
                        endl;
            }
        }
        mysqlpp::Query queryDelete = lianjie.query();
        queryDelete << "DELETE FROM COV2019 WHERE id = " << 4;
        cout << "Query: " << queryDelete << endl;
        queryDelete.execute();
     
        query = lianjie.query("select * from COV2019");
        if (mysqlpp::StoreQueryResult res = query.store()) {

            // 打印每一列数据
            cout << "We have:" << endl;
            mysqlpp::StoreQueryResult::const_iterator it;
            cout.setf(ios::left);
            cout << setw(9) << "ID" <<
                    setw(80) << "news_str" <<
                    setw(30) << "tittle" <<
                    setw(30) << "priority" << 
                    setw(30) << "time" << endl;

            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res.num_rows(); ++i) {
                cout.setf(ios::left);
                cout << setw(9) << res[i]["id"] <<
                        setw(80) << res[i]["news_str"] << 
                        setw(30) << res[i]["tittle"] << 
                        setw(30) << res[i]["priority"] << 
                        setw(30) << res[i]["time"] <<
                        endl;
            }
            //其他遍历打印方式
            // for (it = res.begin(); it != res.end(); ++it) {
            //     mysqlpp::Row row = *it;

            //     for(int i = 0; i < row.size(); i++)
            //     {
            //         if(i == (row.size()-1))
            //             cout << row[i] << endl;
            //         else
            //         {
            //             cout << row[i] << "\t";
            //         }
                    
            //     }
            // }
            


        }
        else {
            cerr << "Failed to get item list: " << query.error() << endl;
            return 1;
        }
    }
    
    return 0;
}