//
//  CTNToonYunAPI.h
//  ToonYunSDK
//
//  Created by 王旭影 on 2017/12/20.
//  Copyright © 2017年 syswin. All rights reserved.
//

#ifndef CTNToonYunAPI_h
#define CTNToonYunAPI_h

#include "CTNToonYunHeader.h"
#include <map>

namespace toonyun {
    
    typedef std::function<void(bool)> completion;
    
    class ITNToonYunSdk {
    public:
        virtual void uploadFile(const char* localPath, ToonUploadFile& model, UploadResultCb resultCallback, UploadProgCb progCallback) = 0;
        
        virtual bool pauseUpload(const char* identifier) = 0;
        
        virtual void cancelUpload(const char* path) = 0; 
        
        virtual void downloadFile(const char *url, const char *identifier, const char *cachePath, DownloadResultCb resultCallback, DownloadProgCb progCallback) = 0;
        
        virtual void cancelDownload(const char* url) = 0;
        virtual void cancelDownloadWithUrl(const char* url, completion complet) = 0;
        
        virtual void cancelAllTask() = 0;
        
        virtual void getToonYunToken(tokenCallback callBack) = 0;
        
        virtual bool downloadFileWithUrl(const char* url, const char* dowloadPath,DownloadCb callBack,  void* userData) = 0;
        
        /**
         * upload file
         * @param filePath local file path
         * @param callBack callback function
         * @param userData user context
         */
        virtual bool uploadFileByFilestream(const char* filePath, UploadCb callBack, void* userData) = 0;
    };
    
    ITNToonYunSdk* getToonYunSdk();
}
#endif /* CTNToonYunAPI_h */
