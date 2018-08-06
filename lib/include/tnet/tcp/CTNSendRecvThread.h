//
//  CTNSendRecvThread.hpp
//  TNMP
//
//  Created by 兰怀玉 on 16/4/15.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef CTNSendRecvThread_hpp
#define CTNSendRecvThread_hpp

#include "TMTPConst.h"

#include "CThreadEx.h"
#include "cdtp.h"
#include "CSafeQueue.h"
#include "CTNPacket.h"
#include "CTcpSocket.h"
#include "CBasicQueue.h"
#include "CTNMPConfig.h"
#include "CTNPacket.h"
//#include "CTNSocketBreaker.h"
#include "CTNNetUtils.h"

#if SSLSocketBuild
#include "CTcpSSLSocket.h"

#else
#endif


const int RECONN_MAX = 6;
const int RECONN_STEP[RECONN_MAX] = {0,1,2,4,8,16};

const int  RECONN_INDEX = 0;
const int  CONNOK_INDEX = 1;



class CTNProcessThread;

struct TNPacketBuffer{
    int32 length;//payload length
    int16 command;
    int16 version;
    char payload[0];
    
    TNPacketBuffer(){
        length = 0;
        command = 0;
        version = 1;
    }
    
    void decode(){
        length = ntohl(length);
        command = ntohs(command);
        version = ntohs(version);
    }
    
    void encode(){
        length = htonl(length);
        command = htons(command);
        version = htons(version);
    }
    
    TNPacketBuffer* clone(){
        TNPacketBuffer* packetBuffer = NEW_PACKET(TMTP_HLEN + this->length);
        packetBuffer->length = this->length;
        if (packetBuffer->length > 0) {
            memcpy(packetBuffer->payload, this->payload, this->length);
        }
        
        return packetBuffer;
    }
};

class CTNSendRecvThread : public CThreadEx
{
public:
    CTNSendRecvThread(CTNProcessThread* processThread);
    ~CTNSendRecvThread();
    
    void run();
    
    void sendPacket(TNPacket &packet);
    
    virtual void stop();

    void setHostInfo(TMTPHostInfo &hostInfo){
        _hostInfo = hostInfo;
    }
    
    const TMTPHostInfo& hostInfo(){
        return _hostInfo;
    }
    
protected:
    void connect();
    
    void processRecvData();
    
    void postRecvPacketBuffer(TNPacketBuffer * packetBuffer);
    
    void socketClosed();
    
private:
    CBasicQueue<char> _recvByteQueue;
    CSafeQueue<TNPacket> _queuePacket;
   
    CTNProcessThread* _processThread;
    
    TMTPHostInfo _hostInfo;
    CTcpSocket* _pSocket;
    
    CTNSocketBreaker _rwBreaker;

    int _reconnectTimes;// = 0;
 };

#endif /* CTNSendRecvThread_hpp */
