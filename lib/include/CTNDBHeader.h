/**
 *  CTNDBHeader.hpp
 *  TNChatLibrary
 *
 *  Created by 王海涛 on 2017/10/11.
 */

#ifndef CTNDBHeader_hpp
#define CTNDBHeader_hpp

#ifdef _WIN32
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#endif

#include <stdio.h>

#include <string>
#include <vector>
#include <set>
#include <stdint.h>
#include <string.h>
#include "CTNIMTypedef.h"

using namespace std;

namespace toonim
{
    enum CTNSESSIONTYPE
    {
        SESSION_TYPE_BACKGROUND = 6,
        SESSION_TYPE_ALLGROUPVERSION = 7,   // all group version, sesionId is "SESSION_TYPE_ALLGROUPVERSION"
        SESSION_TYPE_GROUPMEMBERVERSION = 8,	// group members incremental updated version, sissionId is "SESSION_TYPE_GROUPMEMBERVERSION_groupId" groupId isid
        SESSION_TYPE_USERINFO = 9,			// user info
    };
    
    enum CTNSESSIONSTATUS
    {
        SESSION_TYPE_NORMALL = 0,
        SESSION_TYPE_STRANGER = 1,
        SESSION_TYPE_ALL    =2
    };
    
    enum mapKeyType
    {
        KEY_INT,
        KEY_LONG,
        KEY_DOUBLE,
        KEY_STR
    };
    
    //operate message type
    enum CTNOperateType
    {
        CTNOperateTypeRevoke = 1,
        CTNOperateTypeDelete = 2,
        CTNOperateTypeRelationUpdate = 3
        
    };

    struct CTNClientInfo {
        CTNClientInfo(){
            deviceType =  1;
            apnsType = 100;
            pushServiceType = 1;
        }
        
        int32_t apnsType;
        int32_t deviceType;
        int32_t pushServiceType;
        string username;
        string clientId;
        string deviceId;
        string pushToken;
        string version;
        string appPath;
        string pubKey;
        string priKey;
        string keyPath;
        vector<std::string> feedList;
        
        void setUsername(const char* value){
            if (value == nullptr || strlen(value) == 0){
                return;
            }
            
            this->username = value;
        }
                
        bool isValid(){
            if (clientId.length() == 0 /*|| feedList.size() == 0*/){
                return false;
            }
            
            return true;
        }
    };
    
    struct CTNSession
    {
        CTNSession()
        {
            unreadCount = 0;
            lastTime = 0;
            sortTime = 0;
            readSeqId = 0;
            lastMsgSendStatus = 0;
            type = -1;
            topStatus = 0;
            disturbStatus = 0;
            isStranger = false;
        }
    public:
        std::string sessionId;
        std::string myTmail;
        std::string topic;
        std::string title;
        std::string avatarId;
        int32_t unreadCount;
        int32_t type;
        std::string draft;
        int64_t lastTime;	// session's last message timestamp
        int64_t sortTime;	// session's sort time
        std::string lastMsg;
        std::string lastMsgId;
        int32_t lastMsgSendStatus;
        int64_t readSeqId;
        std::string atMeMsgId;
        int32_t disturbStatus;  //0: for disable NO_DISTURB function, 1: for open NO_DISTURB function, default value is 0.
        int32_t topStatus;		// TOP status, 0 for not set to TOP, 1 for set to TOP, default is 0.
        bool isStranger;		// wheter is stranger, 0 represent NOT, 1 represet YES.
        
        bool isValid () {
            if(topic.length() == 0 || sessionId.length() == 0) {
                //            TNMPLOG("------------Error! add dialoginfo error:session key:" << sessionId << " topic:" << topic << "-------------");
                return false;
            }
            return true;
        }
    };
    
    struct CTNMessage
    {
    public:
        CTNMessage();
        
        // prefer override operator
        static bool greaterSort (CTNMessage &a,CTNMessage &b) { return (a.seqId>b.seqId); }
        static bool lessSort (CTNMessage &a,CTNMessage &b) { return (a.seqId<b.seqId); }
        
        bool isEmpty(){
            if (msgId.length() == 0
                || fromId.length() == 0 || toId.length() == 0){
                return true;
            }
            
            return false;
        }
        
        string getAbstractText();
        
        string genBodyJson();
        string getToToonTypeString();
    private:
        std::string getAbstractText(CTNMessage& message);
        std::string getTextTypeContent(CTNMessage& message);
        std::string getTextTypeVCard(CTNMessage& message);
        std::string getTextTypeNotification(CTNMessage& message);
        std::string getTextTypeGifImage(CTNMessage& message);
        std::string getTextTypeFiles(CTNMessage& message);
        std::string getTextTypeRedEnvelope(CTNMessage& message);
        std::string getTextTypeRecommend(CTNMessage& message);
        std::string getTextTypeCustomizedNotification(CTNMessage& message);
        std::string getTextJson(std::string jsonStr, std::string key);
        
    public:
        std::string msgId;
        std::string sessionId;
        int32_t type;		// CTNIMMessageType
        int32_t sendType;   // send type
        int64_t seqId;
        // judge existing faulty layer
		//1. hot session also create faulty layer
		// value is local message seqId, messages which seqId between local_message_seqId and server_message_seq
		// classified into faulty layer.
        int64_t faultSeqId;
        std::string fromId;
        std::string toId;
        int64_t timestamp;
        int32_t sendStatus;		//CTNMessageSendStatus
        int32_t status;
        int32_t priority;		//wxy message priority
        int32_t catalogId;
        int32_t subCatalogId;
        int32_t contentType;	
        int64_t expireTime;		//wxy needed by offline message
        std::string content;
        float width;
        float height;
        std::string senderName;
        std::string atTmails;	//'@' all members is TOON_IM_AT_ALL_MEMBERS, '@' some members, data in json content
        std::string fileFormat;
        std::string noticeStatusType;
        int32_t isMyself;		//wxy message source information
        int32_t flags;			//Toon_FLAG_BITS
        std::string addition;   //json format, attachment download status
        std::string bizNo;		//notification bizNo, NOT used for single chat or group chat
    };
    
    struct CTNMessageOperate
    {
    public:
        CTNMessageOperate()
        {
            seqId = 0;
            type = 0;
            timestamp = 0;
            catalogId = 0;
        }
    public:
        std::string msgId;
        int64_t seqId;
        int32_t type;
        std::string mfrom;
        std::string mto;
        int64_t timestamp;
        int32_t catalogId;
        std::string content;
        std::string opMsgId;
        std::string opFeedId;
        std::string opName;
        std::string sessionId;
    };
    
    struct CTNGroupInfo
    {
    public:
        CTNGroupInfo()
        {
            maxNum = 0;
            currNum = 0;
            version = 0;
            status = 0;
            creatorCardId = 0;
        }
    public:
        
        std::string groupTmail;
        std::string creatorTmail;
        int64_t creatorCardId;
        std::string name;
        std::string namePinyin;
        std::string pinyinHeader;
        std::string headerImage;
        std::string myTmail;
        int32_t status;
        int32_t maxNum;
        int32_t currNum;
        int64_t version;
        
        void parse(void *dataValue);
        bool isValid () {
            if(groupTmail.size() <= 0) {
                return false;
            }
            return true;
        }
    };
    
    struct CTNGroupMember
    {
    public:
        CTNGroupMember()
        {
            status = 0;
            timestamp = 0;
            permissionType = 0;
            memberCardId = 0;
        }
    public:
        void parse(void *dataValue);
        
        std::string groupTmail;
        std::string memberTmail;
        std::string name;
        std::string namePinyin;
        std::string namePinyinHeader;
        std::string remarkName;
        std::string remarkNamePinyin;
        std::string remarkNamePinyinHeader;
        std::string headerImage;
        int32_t status;
        int64_t timestamp;
        int32_t permissionType;
        int64_t memberCardId;
        
        bool isValid () {
            if(groupTmail.length() <= 0 || memberTmail.length() <= 0) {
                return false;
            }
            return true;
        }
        
        void serialize(void *writerJson);
    };
    
    struct CTNSessionSetting
    {
    public:
        CTNSessionSetting (){
            type = -1;
        }
        std::string sessionId;
        int32_t type;
        std::string value;
        
        bool isValid () {
            if(sessionId.length() <= 0 || type <= 0) {
                return false;
            }
            return true;
        }
    };
    
    struct CTNNoticeFilter{
        CTNNoticeFilter(){
            catalogId = 0;
        }
        
        CTNNoticeFilter(const CTNNoticeFilter& filter){
            catalogId = filter.catalogId;
            broadcast = filter.broadcast;
            set<int>::iterator iter;
            for (iter=filter.subCatalogIdSet.begin();iter!=filter.subCatalogIdSet.end();++iter){
                subCatalogIdSet.insert(*iter);
            }
        }
        
        CTNNoticeFilter& operator = (const CTNNoticeFilter& filter){
            catalogId = filter.catalogId;
            broadcast = filter.broadcast;
            set<int32_t>::iterator iter;
            for (iter=filter.subCatalogIdSet.begin();iter!=filter.subCatalogIdSet.end();++iter){
                subCatalogIdSet.insert(*iter);
            }
            
            return *this;
        }
        
        int32_t catalogId;
        set<int32_t> subCatalogIdSet;
        string broadcast;
    };
    
    // offline message
    struct CTNOffMessageResult {
        std::string sessionId;
        int64_t maxSeqId;
        int64_t minSeqId;
        
        bool operator < (const CTNOffMessageResult &right) const
        {
            return this->sessionId < right.sessionId;
        }
    };
    
    struct CTNTmail {
        CTNTmail(){
            status = 0;
            tmailType = 0;
        }
        
        std::string tmail;
        std::string title;
        std::string avatar;
        int32_t status;
        int32_t tmailType;
        
        bool isValid() {
            if (tmail.length() <= 0) {
                return false;
            }
            
            return true;
        }
        
        void parse(void *dataValue);
        void serialize(void *writerJson);
    };
    
    struct CTNAddress: public CTNTmail {
        CTNAddress() {
            activeCardId = 0;
            passiveCardId = 0;
            isStranger = 1;
        }
        
        std::string myTmail;
        std::string friendTmail;
        int64_t activeCardId;
        int64_t passiveCardId;
        int32_t isStranger;    //default 0
        
        bool isValid() {
            if (myTmail.size() <= 0 || friendTmail.size() <=0) {
                return false;
            }
            return true;
        }
        
        void parse(void *dataValue);
    };
   
    enum E_Relation {
        RELATION_NONE = 0,
        RELATION_STRANGER,
        RELATION_MUTUAL,
        RELATION_UNKNOWN,
    };

    struct CTNRelation {
#define RELATION_NO_RELATION    0
#define RELATION_STRANGER       BIT0
#define RELATION_FRIEND         BIT1
#define RELATION_IN_BLACK_LIST  BIT2
#define RELATION_NO_DISTURB     BIT3
#define RELATION_FOLLOW         BIT4
#define RELATION_ANCHOR_TOP     BIT5
#define RELATION_STAR           BIT6

        CTNRelation() {
            activeTmail = "";
            passiveTmail = "";
            relationValue = RELATION_NONE;
            relationType = 0;
        }
        
        std::string activeTmail;
        std::string passiveTmail;
        int32_t relationValue;
        int32_t relationType;
        
        bool isValid() {
            if (activeTmail.empty() || passiveTmail.empty()) {
                return false;
            }
            return true;
        }
        
        void parse(void *dataValue);
    };
    
    struct CTNUserTmail {
        CTNUserTmail() {
            tmailType = 1;
            pushswitch = 1;
            pushdetail = 1;
            ringswitch = 1;
            shakeswitch = 1;
        }
        
        std::string tmail;
        std::string pubKey;
        std::string priKey;
        int32_t tmailType;		//card type
        int32_t pushswitch;		//push, 0 open, 1 close
        int32_t pushdetail;     //push detail, 0 detail, 1 abstraction
        int32_t ringswitch;     //ring
        int32_t shakeswitch;    //vibrate
        std::string title;
        
        bool isValid() {
            if (tmail.length() <= 0) {
                return false;
            }
            
            return true;
        }
        
        void parse(void *dataValue);
    };
    
    struct CTNMenuConfig {
        CTNMenuConfig() {
            menuId = 0;
            location = 0;
            state = 0;
            orders = 0;
        }
        
        std::string icon;
        std::string title;
        std::string url;
        std::string itemBg;
        std::string param;
        
        std::string functionId;
        std::string typeName;
        
        int64_t menuId;
        int32_t location;
        int32_t state;
        int32_t orders;
        
        bool isValid() {
            if (icon.length() <= 0 || title.length() <= 0) {
                return false;
            }
            return true;
        }
        
        void parse(void *dataValue);
    };

    struct CTNAppNoInfo {
        CTNAppNoInfo() {
            appId = 0;
            type = 0;
            isMenu = false;
            createTime = 0;
            updateTime = 0;
            isSubscribe = false;
        }

        int64_t appId;
        string tmail;
        string name;
        int32_t type;
        string appBodyInfo;
        string funcDesc;
        string complaintCall;
        string address;
        string email;
        bool isMenu;
        int64_t createTime;
        int64_t updateTime;
        string headImage;
        bool isSubscribe;

        bool isValid() {
            if (appId <= 0 && tmail.length() <= 0) {
                return false;
            }

            return true;
        }

        void parse(void *dataValue);
    };

    struct CTNAppNoMenu {
        CTNAppNoMenu() {
            menuId = 0;
            appNoId = 0;
            type = 0;
            menuOrder = 0;
            parentId = 0;
            createTime = 0;
            updateTime = 0;
        }

        int64_t menuId;
        int64_t appNoId;
        string tmail;
        string name;
        int32_t type;
        string linkUrl;
        int32_t menuOrder;
        int64_t parentId;
        int64_t createTime;
        int64_t updateTime;
        vector<CTNAppNoMenu> subAppNoMenu;

        bool isValid() {
            if (menuId <= 0 && appNoId <= 0) {
                return false;
            }

            return true;
        }

        void parse(void *dataValue);
    };
    
    std::string generateSessionId(int32_t type, std::string from, std::string to, bool isMyself);
    std::string generateMsgId();
    std::string generateTmailId();
}

#endif /* CTNDBHeader_hpp */
