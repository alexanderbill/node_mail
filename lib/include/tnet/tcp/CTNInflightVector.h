//
//  CTNInflightVector.hpp
//  TNMP
//
//  Created by lanhy on 16/11/3.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef CTNInflightVector_hpp
#define CTNInflightVector_hpp

#include <stdio.h>

#include "cdtp.h"

#include <vector>
#include <mutex>
#ifdef __linux__
#include <functional>
#endif

#endif /* CTNInflightVector_hpp */


struct InflightMessage{
//    int size;
//    int type;
//    bool isDup;
    long timestamp;
    int retryTimes;
    int16_t command;
    Toon::Datagram datagram;
//    Toon::MsgReq* req;
    
    InflightMessage(){
//        req = NULL;
//        isDup = false;
        retryTimes = 0;
//        size = 0;
    }
    
    InflightMessage(InflightMessage& other){
//        this->type = other.type;
//        this->isDup = other.isDup;
        this->retryTimes = other.retryTimes;
//        this->size = other.size;
        this->datagram = other.datagram;
//        this->req = new Toon::MsgReq();
//        (*req) = *(other.req);
    }
    
    ~InflightMessage(){
//        if (req != NULL){
//            delete req;
//        }
    }
};


class CTNInflightVector
{
public:
    CTNInflightVector();
    ~CTNInflightVector();
    
    static CTNInflightVector* instance(){
        if (m_instance == NULL) {
            m_instance = new CTNInflightVector();
        }
        
        return m_instance;
    }
    
    void addToInflight(InflightMessage* req);
    int removeInflightMutex(std::string & msgId);
    int removeInflight(std::string & msgId);
    
    //
    void checkInflight(bool isOffline, std::function<void(bool isResend, InflightMessage* msg)> callback);
    bool inflightIsEmpty();
    
    void forceResend(std::function<void(InflightMessage* msg)> callback);
    
private:
    std::vector<InflightMessage*> m_vctInflight;
    std::mutex m_mutexInflight;
    
    static CTNInflightVector* m_instance;

};

#define RESEND_FAILED_TIMER  180 //重发时间：20s
#define RESEND_TIMER  20 //重发时间：20s
#define RETRY_MAXTIMES  (RESEND_FAILED_TIMER/RESEND_TIMER) //重发最大时间：180s

#define INFLIGHT_VECTOR     CTNInflightVector::instance()

