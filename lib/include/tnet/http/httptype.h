#ifndef __toon__HTTP_TYPE_H
#define __toon__HTTP_TYPE_H

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace toon {
    
    typedef std::vector<std::string> HttpHeaders;
    typedef std::map<std::string, std::string> HttpPostFileds;
    typedef std::function<void(long total, long now)> HttpProgressCallback;
 
    typedef std::function<void()> CTNSuccessCallback;
    typedef std::function<void(CTNError)> CTNFailCallback;
    typedef std::function<void(long total, long now)> CTNProgressCallback;
    
    class HttpCallback {
    public:
        
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
    };
}

#endif
