//
// Created by juzenhon on 2017/8/28.
//

#ifndef TMTP_CTNHTTPCLIENT_H
#define TMTP_CTNHTTPCLIENT_H

#include <string>
#include <map>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include "curl/curl.h"

using namespace std;


enum HttpMethod {
    Get,
    Post,
    POST_BY_FILESTREM,
};

typedef int (*ProgressCallback)(void* progress_data, double t, double d, double ultotal, double ulnow);

class HttpResponse {

public:
    string _url;

    map<string, string> _headers;

    string _errStr;

    double _dns_time;

    double _connect_time;

    double _ssl_connect_time;

    double _transfer_time;

    double _http_version;

    int _httpCode;
};

class HttpRequest {

    friend class CTNNetWork;

public:

    HttpRequest();

    virtual ~HttpRequest();

    map<string, string> &getHeaders();
    
    std::map<std::string, std::string> &getFormdataList();
    
    void setFormdataList(std::map<std::string, std::string> formlist);

    HttpMethod getMethod();

    string &getUrl();

    void setUrl(const char *url);
    
    ProgressCallback getProgressCallback();
    
    void setProgressCallback(ProgressCallback pCb);
    
    void setIdentifier(char* identifier);
    
    char* getIdentifier();
    
    void setDownloadRange(std::string range);
    
    std::string getDownloadRange();

    void cancel();

    /**
     * 入队开始执行
     */
    void enqueue();

    /**
     * 获取请求body中的数据
     * @param size 数据长度
     * @return  bufPtr body数据
     */
    virtual const char *getPostBody(int64_t &size);

    /**
     * 数据写到本地
     * @param dataPtr data
     * @param len len
     * @return 实际处理的长度
     */
    virtual int32_t writeTo(const char *dataPtr, int32_t len);
    
    HttpResponse& getResponse();

protected:

    /**
   * 处理response
     * @param response 响应代码
   */
    virtual void handResponse(HttpResponse &response) = 0;

protected:

    map<string, string> _headers;
    
    std::map<std::string, std::string> _formdataList;//wxy 上传
    char** _name;
    char** _content;

    ProgressCallback _proCb;
    
    HttpMethod _method = Get;

    string _url;

    string _postBody;

    string _result;

    bool _cancel;

    HttpResponse _response;

private:
    bool _running;
    void *_userP1;
    CURL *_requestHandle;
    char* _identifier;
    std::string _downloadRange;
};

class CTNNetWork {

public:

    static CTNNetWork *getClient() {
        static CTNNetWork sInstance;
        return &sInstance;
    }

    ~CTNNetWork();

public:

    void setTimeout(int seconds);

    void setCerPath(const char *cerPath);
    
    int64_t getDownloadFileLength(const char *url);

private:

    friend class HttpRequest;

    void enqueue(HttpRequest *request);

    CURL *initReqForHandle(HttpRequest *request);

    void loopRequests();

    /**
     * 把队列中的请求加入client执行
     * @param multi_handle handle
     * @return int
     */
    int joinRequestForExec(CURLM *multi_handle);

    void readResponseInfo(CURLM *cm_handle);

    void cancelRequest(HttpRequest *request);

private:
    CTNNetWork();

    CTNNetWork(const CTNNetWork &rhs);

    const CTNNetWork operator=(const CTNNetWork &rhs);

    int _timeout;

    std::string _cerPath;

    queue<HttpRequest *> _requestQueue;

    mutex _queueMutex;

    std::condition_variable _condition;

    bool _net_running;

    int _exec_count;

    CURLM *_multi_handle;
	
	CURLSH* _shareHandle;

    const static int MAX_EXEC_COUNT = 4;
};


#endif //TMTP_CTNHTTPCLIENT_H
