//#include <sRessourceLock.hpp>

//RessourceLock        guid_lock;
//int32                guid_count = 0;
struct __guid_string {
                  char   id;
                  char   sep0;
                  char   date[8];
                  char   sep1;
                  char   time[8];
                  char   sep2;
                  char   sid[4];
                  char   sep3;
                  char   num1[4];
                  char   sep4;
                  char   num2[8];
                  char   end;
                };