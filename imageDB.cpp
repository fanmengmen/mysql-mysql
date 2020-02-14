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
        IMAGE james;
        // vector<IMAGE> nba;
        // mysqlpp::Query query = lianjie.query("select * from IMAGE");
        // query.storein(nba);      
        string image_name = "250.jpg";
        FILE *fp = NULL;
        char* buffer;
        int img_len = 0;
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
        james.id = 1;
        james.data.data.assign(buffer, img_len);
        james.img_len = img_len;
        /*如果已经存在，不在插入该条消息，如果不存在，将消息插入到数据库*/
        // if(!count(nba.begin(),nba.end(),james))
        // {
            try
            {
                mysqlpp::Query queryInsert = lianjie.query();
                queryInsert.insert(james);
                // queryInsert << "INSERT INTO `IMAGE` (`id`,`data`) VALUES (" << 1 << "," << james.data.data << ");";
                // Show the query about to be executed.
                // cout << "Query: " << queryInsert << endl;

                // Execute the query.  We use execute() because INSERT doesn't
                // return a result set.
                mysqlpp::SimpleResult res = queryInsert.execute();
                // Report successful insertion
                cout << "Inserted \"" << image_name <<
                        "\" into images table, " << james.data.data.size() <<
                        " bytes, ID " << res.insert_id() << endl;
                cout << "Insert info: " << res.info() << endl;
                /* code */
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        mysqlpp::Query query = lianjie.query("select * from IMAGE");
        mysqlpp::StoreQueryResult out = query.store();


        fp = fopen("250_new.jpg","wb");
        fwrite(out[0]["data"],1,img_len,fp);
        fclose(fp);
            
       
    }
    
    return 0;
}