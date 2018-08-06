//
//  CTNDataProcessThread.hpp
//  TNMP
//
//  Created by 兰怀玉 on 16/4/14.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef CTNDataProcessThread_hpp
#define CTNDataProcessThread_hpp

#include "CThreadEx.h"
#include "CSafeQueue.h"

#include "cdtp.h"
#include "tmtp.h"

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include "TMTPConst.h"
#include "ITNMPResponse.h"
#include "CTNPacket.h"



class CTNSendRecvThread;
class TNPacketBuffer;
class CTcpSocket;
class TMTPHostInfo;
class InflightMessage;


const uint16_t TMTP_PACKET_TYPE_SEND = 1;
const uint16_t TMTP_PACKET_TYPE_RECV = 2;
const uint16_t TMTP_PACKET_TYPE_LOGOUT = 3;
const uint16_t TMTP_PACKET_TYPE_SOKCET_CLOSED = 4;
const uint16_t TMTP_PACKET_TYPE_SOKCET_FAILED = 5;
const uint16_t TMTP_PACKET_TYPE_SOKCET_SUCCESS = 6;


#define REQ_ID toonim::CTNUtils::generateUUID()


class CTNProcessThread : public CThreadEx
{
public:
    CTNProcessThread(ITNMPResponse *resp);
    ~CTNProcessThread();
  
    virtual void run();
    
    void setClientInfo(std::vector<TMTPHostInfo> & vctHostInfo, const char* clientId,int apnsType, const char* version, int deviceType = 0, int pushServiceType = 0);
    void setUserInfo(const char* username, const char* deviceId,const char* pushToken, const char* privFile);
    void setPushToken(const char* pushToken);
    void setAppPath(const char* appPath);
    
    void postPacket(TNPacket &packet);
  
    TNMPNetStatus getNetStatus();
    
    void randomReq();
    void login(int32_t random);
    void logout(bool notifyServer);
    
    void sendMsgReq(int16_t command, Toon::Datagram &datagram, bool inflight);
    void reqSyncSessionStatus(Toon::SyncSessionStatusReq & req);
    void reqPullOffMsg(Toon::PullOffMsgReq & req, std::string reqId);
    void reqHighMessage(int64_t maxSeqId);
    void syncReq(Toon::SyncReq &req);

    void clientReport(Toon::ClientReport & req);
    
private:
    
    bool currSocketValid();
    void createSocketThread();
    void processSuccessRSThread(int theadId);
    void destoryRSThread(bool forceStop);
    void forceDestoryAllThread();
    
    void reconnect();
    bool isLogout();
 
    void sendPacket(TNPacket &packet);
    void sendAck(Toon::Datagram &datagram);
    void checkPing();
    void reqHotSession(int64_t timestamp);

    void forceResendInflight();
    void checkRecvCache();
 
    void processPacketMessage(TNPacket& packet);
    void processRecvMsgReq(Toon::Datagram &datagram);
    void processSessionStatusReq(Toon::Datagram &datagram);
    void processMsgAck(Toon::Datagram &datagram);
    void processConnectResp(Toon::Datagram &datagram);
    void processPullOffMsgResp(Toon::Datagram &datagram);
    void processHighMsgResp(Toon::Datagram &datagram);
    void processHotSessionResp(Toon::Datagram &datagram);
    void processSyncSessionStatusResp(Toon::Datagram &datagram);
    void processUserOnlineStatus(Toon::Datagram &datagram);
  
    void processKickout();
    
    
    void sendPacket();
    
    virtual void setNetStatus(TNMPNetStatus status);
    
    void daInfo(string attrName, map<string, string> propertyJson =  map<string, string>());
    void packetSign(Toon::Datagram &datagram);
    bool packetVerify(Toon::Datagram &datagram);

private:
    
    ITNMPResponse *m_response;
    int64_t m_pingReqTime;
    int m_reconnects[2];//重试次数，连接成功次数；如果重连次数和连接成功次数超过5将终止连接，
    bool m_offMsgCountOk;//离线消息数是否已经获取，断线重连需要复位
    std::string _pubKey;
    std::string _privKey;
 
    std::mutex m_mutexNetStatus;
    TNMPNetStatus m_netStatus;
    
    //跑马策略保存地址
   std::vector<CTNSendRecvThread*> m_vctRSThread;
    CTNSendRecvThread *m_pSRThread;
   
    CSafeQueue<TNPacket> m_queuePacket;
    
    std::vector<InflightMessage*> _recvCache;
    
    
 };

#endif /* CTNDataProcessThread_hpp */
