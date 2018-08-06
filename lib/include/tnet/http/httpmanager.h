#ifndef __toon__HTTPMANAGER_H
#define __toon__HTTPMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include <functional>

#include "CTNError.h"

namespace toon {
    
    class HttpManager;
    
    class HttpCallback {
    public:
        typedef std::function<void(const std::string &response)> CTNSuccessCallback;
        typedef std::function<void(const CTNError &error)> CTNFailCallback;
        typedef std::function<void(double total, double now)> CTNProgressCallback;
    
        /**
         * Callback's empty constructor.
         */
        HttpCallback() { mOnSuccess = nullptr; mOnFail = nullptr; mOnProgress = nullptr; }
        
        /**
         * Callback's constructor.
         */
        HttpCallback(CTNSuccessCallback onSuccess, CTNFailCallback onFail, CTNProgressCallback onProgress = nullptr) {
            mOnSuccess = onSuccess;
            mOnFail = onFail;
            mOnProgress = onProgress;
        }
        
    private:
        CTNSuccessCallback mOnSuccess;
        CTNFailCallback mOnFail;
        CTNProgressCallback mOnProgress;
        friend class HttpManagerImpl;
    };

    
    class HttpOperation;
    class TaskQueue;
    class HttpManagerConfig;

    class HttpManager {
    public:
        enum METHOD {
            GET,
            POST,
        };

        typedef std::vector<std::string> CTNHttpHeaders;
        typedef std::map<std::string, std::string> CTNHttpPostFileds;
        
        /**
         * single instance's reference
         */
        static HttpManager&  getInstance();
        
        /**
         * get & set config
         */
        HttpManagerConfig &getConfig();
        
        /**
         * execute http request
         */
        virtual void execute(const std::string &url, METHOD method, const CTNHttpHeaders &headers, const std::string &postFields, const HttpCallback &callback) = 0;
        
        /**
         * upload local file
         * uniqueId is used by cancel operation, if passed "", will use localPath instead.
         */
        virtual void upload(const std::string &url, const std::string &localPath, const CTNHttpHeaders &headers, const HttpCallback &callback, const std::string &uniqueId = "") = 0;
        
        /**
         * download remote url to local file
         * uniqueId is used by cancel operation, if passed "", will use localPath instead.
         */
        virtual void download(const std::string &url, const std::string &localPath, const CTNHttpHeaders &headers, const HttpCallback &callback, const std::string &uniqueId = "") = 0;

        /**
         * cancel upload operation
         */
        virtual void cancelUpload(const std::string &idOrUrl, const std::string &localPath, const std::string &uniqueId) = 0;
        
        /**
         * cancel download operation
         */
        virtual void cancelDownload(const std::string &url, const std::string &uniqueId) = 0;
    };
    
    class HttpManagerConfig {
    public:
        HttpManagerConfig();
        
        /**
         * config download temporary path
         */
        void setDownloadTempDirectory(const std::string &path) { mDownloadTempPath = path;}
        
        /**
         * get download temporary directory
         */
        std::string getDownloadTempDirectory();
        
    private:
        std::string mDownloadTempPath;
    };
}

#endif
