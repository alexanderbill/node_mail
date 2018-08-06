#ifndef __toon__HTTPAPI_H_
#define __toon__HTTPAPI_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace toon {
    
    typedef std::vector<std::string> HttpHeaders;
    typedef std::map<std::string, std::string> HttpPostFileds;
    typedef std::function<void(double total, double now)> HttpProgressCallback;

    class HttpOperation
    {
    public:
        
        static const long INVALID_PARAM  = -1;
        static const long HTTP_FAILED    = -2;
        static const long CONNECT_FAILED = -3;
        static const long HTTP_TIMEOUT   = -4;
        static const long NEXT_HOST      = -5;
        static const long RETRY_HOST     = -6;
        static const int  DEFUALT_OPT_TIMEOUT = 60;
        static const int  FILE_TRANSFER_TIMEOUT = 300;
        /*!
         @brief
         This constructor is used to create a normal http request.
         */
        HttpOperation(const std::string &url, const std::string &postField, const HttpHeaders &headers, long timeout = DEFUALT_OPT_TIMEOUT);
        
        /*!
         @brief
         This constructor is used to create a file upload/download http request.
         */
        HttpOperation(const std::string &url, const HttpHeaders &headers, const std::string &localPath, long timeout = DEFUALT_OPT_TIMEOUT);
        
        /*!
         @brief
         This constructor is used to create a file upload/download http request with fileName.
         */
        HttpOperation(const std::string &url, const HttpHeaders &headers, const std::string &localPath, const std::string &fileName, long timeout = DEFUALT_OPT_TIMEOUT);
        
        virtual ~HttpOperation() {}
        
        /*!
         @brief
         Perform normal http request.
         */
        long perform(std::string &response);
        
        long performWithMethod(std::string &response, const std::string &method);
        
        /*!
         @brief
         Perform file upload request.
         */
        long upload(std::string &response, const HttpProgressCallback &callback = [](double, double){});
        
        /*!
         @brief
         Perform file download request.
         */
        long download(const HttpProgressCallback &callback = [](double, double){});
        
        /*!
         @brief
         Perform cancel operation.
         */
        void cancel();
        
        /*!
         @brief
         whether has canceled
         */
        bool isCanceled();

        /*!
         @brief
         Get http failure description.
         */
        const std::string& getErrorDesc();
    private:
        std::string mUrl;
        HttpHeaders mHeaders;
        std::string mLocalPath;
        std::string mErrorDesc;
        std::string mFileName;
        std::string mPostField;
        long mTimeout;
        long mConnectionTimeout;
        int mRetryTimes;
        volatile bool mCancel;
    };
    typedef std::shared_ptr<HttpOperation> HttpOperationPtr;
}

#endif
