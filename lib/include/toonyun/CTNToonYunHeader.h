//
//  CTNToonYunHeader.h
//  ToonYunSDK
//
//  Created by 王旭影 on 2017/12/20.
//  Copyright © 2017年 syswin. All rights reserved.
//

#ifndef CTNToonYunHeader_h
#define CTNToonYunHeader_h

#include <stdint.h>
#include <string>
#include <stdio.h>
#include <functional>

namespace toonyun {

	/**
     * param0 int32_t flag: 0 success, -1 failed
     * param1 const char* localPath
     * param2 void * context
     */
    typedef std::function<void(int32_t, const char*, void*)> DownloadCb;

    /**
     * param0 int32_t flag: 0 success, -1 failed
     * param1 const char* published url
     * param2 void * context
     */
    typedef std::function<void(int32_t, const char*, void*)> UploadCb;
    
    /**
     * param0 int32_t flag: 0 success, -1 failed
     * param1 const char* published url
     * param2 const char* uploadFile(ToonUploadFile.identifier)
     */
    typedef std::function<void(int32_t, const char*, const char*)> UploadResultCb;

    /**
     * param0: int32_t percent
     * param1: const char* identifier
     */
    typedef std::function<void(int32_t, const char*)> UploadProgCb;

    /**
     * param0: int32_t flag: 0 success, -1 failed
     * param1: const char* localpath
     * param2: const char* identifier
     */
    typedef std::function<void(int32_t, const char*, const char*)> DownloadResultCb;

    /**
     * param0: int32_t progress
     * param1: identifier
     */
    typedef std::function<void(int32_t, const char*)> DownloadProgCb;
    
    struct ToonUploadFile{
        std::string url;
        std::string identifier; //identifier, to denote the upload operation, usefull for the cancel operation
//        bool pub;				// open to public
        std::string suffix;		// file suffix
        std::string clientIp;	// user's IP for last uploaded slice data
        std::string location;	// user location
        
        ToonUploadFile(){
//            pub = false;
        }
    };
    
    enum ToonFileState{
        TOON_FILE_STATE_NONE = 0,
        TOON_FILE_STATE_NONE_WAITING = 1,       
        TOON_FILE_STATE_NONE_PROCESSING = 2,    
        TOON_FILE_STATE_NONE_RUNNING = 3,       
        TOON_FILE_STATE_NONE_SUSPENDED = 4,     
		TOON_FILE_STATE_NONE_CANCELING = 5,     
        TOON_FILE_STATE_NONE_COMPLETED = 6,     
        TOON_FILE_STATE_NONE_FAILURE = 7,       
    };
    
    struct TNCCloudTokenModel{
        std::string domain;
        std::string stoken;
        int64_t startDateTime;
        int64_t endDateTime;
        TNCCloudTokenModel(){
            startDateTime = 0;
            endDateTime = 0;
        }
    };
    
    typedef std::function<void(TNCCloudTokenModel)> tokenCallback;

	//#define UPLOADBYFILESTREAMPATH "http://172.31.68.93:9083/file/upload"

#define UPLOADBYFILESTREAMPATH "http://172.31.68.93:9083/yun/upload"

#define DOWNLOADPATH "http://172.31.68.93:9083/file/download?filename="


}


#endif /* CTNToonYunHeader_h */
