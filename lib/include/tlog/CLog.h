//
//  CLog.hpp
//  TNMP
//
//  Created by 兰怀玉 on 16/5/6.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef CLog_hpp
#define CLog_hpp

#ifdef _WIN32
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#else

#include "TILog.h"
#endif

#include <stdio.h>
#include <string>
#include <fstream>
#include <mutex>
#include <iostream>
#include <sstream>
#include "CSafeQueue.h"
#include "CThreadEx.h"

using namespace std;

//class ITNMPResponse;

/**
 * 用于输出log文件的类.
 */
class CLog : protected CThreadEx
{
private:
    static const int MAX_FILE_LOG_SIZE;
public:
    CLog();
    ~CLog();
    
    static CLog* instance();
    static string getTimeStr();
    static unsigned long getCurrentThreadID();

    void setPath(string path);

    void writeLog(stringstream& logstream);
   
    string getFileName(time_t timestamp = 0);

    void closeClog();

protected:

    virtual void run();

private:
    time_t _lastFileTime;
    mutex _appPathMtx;
    string _appPath;
    
    FILE *_file;
    
    CSafeQueue<string> _logQueue;

    bool open();

    void clearOldFile();
};

#define TNMPINS     CLog::instance()

#define CDTP_DISPLAY(info,t) do{std::stringstream streamcdtp; t.display(streamcdtp);TNMPLOG("[CDTP]"<<info<<" data:"<<streamcdtp.str())}while(0);

#ifndef WIN32
#define TNMPLOG(logstr) {   std::stringstream stream; stream <<logstr; tlog::XLoggerInfo info; \
                                    info.tag="Tmail";\
                                    info.maintid=0;\
                                    info.tid=CLog::getCurrentThreadID();\
                                    info.level=tlog::TLogLevel::Debug;\
                                    gettimeofday(&info.timev,NULL);\
                                    tlog::TLog::get()->logPrint(info,stream.str().c_str()); \
                        }

#define INITLOG(PATH) tlog::TLog::get()->logOpen(PATH,PATH,"Tmail"); \
                      tlog::TLog::get()->setConsoleOpen(true)

#define CLOSELOG() tlog::TLog::get()->logClose()
#else
#define INITLOG(PATH) CLog::instance()->setPath(appPath)
#define CLOSELOG() CLog::instance()->closeClog()
#define TNMPLOG(logstr) try{   std::stringstream stream; stream <<" ["<<CLog::getCurrentThreadID()<<"]"<<CLog::getTimeStr()<<logstr; CLog::instance()->writeLog(stream); }catch(...){std::cout<<"++++Excecption occur on LOG++++++++"<<std::endl;}
#endif


//#define TNMPLOG(logstr)

#endif /* CLog_hpp */
