/**
 *  CTNDBAPI.hpp
 *  CTNSDK
 *
 *  Created by 王海涛 on 2017/8/22.
 *  Copyright 2017年 syswin. All rights reserved.
 */

#ifndef CTNDBAPI_hpp
#define CTNDBAPI_hpp

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <stdint.h>
#include "CTNDBHeader.h"

using namespace std;

namespace toonim {
    
    class ITnImDBChat
    {
    public:
        virtual ~ITnImDBChat(){}
                
#pragma mark ------------------session-----------------
        /**
         addsession

         @param sessions session
         @return true
         */
        virtual bool addSession(vector<CTNSession> &sessions) = 0;
        
        /**
         updateSession

         @param sessions session
         @return true
         */
        virtual bool updateSession(vector<CTNSession> &sessions) = 0;
        
        
        /**
         change session title and avatar, title and avaterid can not be both emtpy.
         @param sessionId sessionId
         @param title title
         @param avatarId avaterid
         @return true
         */
        virtual bool updateSessionTitleAndImage(const char* sessionId, const char* title, const char* avatarId) = 0;
        
        /**
         update session myTmail

         @param sessionId sessionId
         @param myTmail myTmail
         */
        virtual void updateSessionMyTmail(const char* sessionId, const char* myTmail) = 0;
        
        /**
         update session last message content, and deliver time

         @param sessionId sessionId
         @param lastMsg lastMsg
         @param lastTime lastTime
         @return true
         */
        virtual bool updateSessionLastMsgAndLastTime(const char* sessionId, const char* lastMsg, int64_t lastTime) = 0;
        
        /**
         delete session
         
         @param sessionId sessionId
         @return true
         */
        virtual bool deleteSession(const char* sessionId) = 0;
        
        /**
		 get session by myTmail, 
         
         @param myTmail myTmail
         @param status status
         @return sessions
         */
        virtual vector<CTNSession> getSessions(const char* myTmail, toonim::CTNSESSIONSTATUS status)  = 0;
        
        /**
         get stranger list

         @param myTmail myTmail
         */
        virtual vector<CTNSession> getStrangerList(const char* myTmail) = 0;
        
        /**
         get session list by myessage type

         @param type Toon_MSG_TYPE
         @return list
         */
        virtual vector<CTNSession> getSessionListByType(Toon_MSG_TYPE type) = 0;
        
        /**
		 get session by sessionId

         @param sessionId sessionId
         @return session
         */
        virtual CTNSession getSession(const char* sessionId)  = 0;
        
        /**
		 get unread count. search condition myTmail & sessionid & isStranger
		 myTmail can be empty, will search all my tcard sessions.
		 when sessionId is not empty, will bypass this session.

         @param myTmail my tmail, can be empty.
         @param sessionId is sessionId is not empty, will bypass this session's unread count
         @param status status
         @return unread count
         */
        virtual int getUnreadCount(const char* myTmail, const char* sessionId, toonim::CTNSESSIONSTATUS status)  = 0;
        
        /**
		 get unread count not contained under tmail 
		 search un

         @param tmail not contained under tmail
         @param status status
         @return unreadCount
         */
        virtual int getUnreadCountUnContainTmail(const char* tmail, toonim::CTNSESSIONSTATUS status) = 0;
        
        /**
		 mark session as read

         @param sessionId sessionid
         @return true
         */
        virtual bool markSessionRead(const char* sessionId)  = 0;
        
        /**
		 mark session as unread

         @param sessionId sessionid
         @return true
         */
        virtual bool markSessionUnread(const char* sessionId) = 0;
        
        /**
         clear all session unread status

         @return true
         */
        virtual bool clearAllUnreadCount()  = 0;
        
        /**
         search session list

         @param keyWord keywork
         @param list result session list
         */
        virtual void searchSessionList(const char* keyWord, vector<CTNSession> &list) = 0;
        
#pragma mark -----------------message------------------
        /**
         add message list

         @param messages messages
         @return true
         */
        virtual bool addMessages(vector<CTNMessage> &messages)  = 0;
        
        /**
         add message

         @param message message对象
         @return true
         */
        virtual bool addMessage(toonim::CTNMessage &message) = 0;
        
        /**
         replace message

         @param message message
         @return true
         */
        virtual bool replaceMessage(toonim::CTNMessage &message) = 0;
        
        /**
         replace message

         @param messages message
         @return true
         */
        virtual bool replaceMessages(vector<CTNMessage> &messages) = 0;
        
        /**
         deleteMessage，mark message as deleted, not really delete from database.
		 refer to physicalDeletionMessage

         @param sessionId sessionId
         @param msgId msgId
         @return true
         */
        virtual bool deleteMessage(const char* sessionId, const char* msgId)  = 0;
        
        /**
         delete all messages under certain sessionId

         @param sessionId sessionId
         @return true
         */
        virtual bool deleteAllMessage(const char* sessionId)  = 0;
        
        /**
         delete message from database, refer to deleteMessage

         @param sessionId sessionid
         @param msgId msgId
         @return true
         */
        virtual bool physicalDeletionMessage(const char* sessionId, const char* msgId) = 0;
        
        /**
         update message content, status

         @param message message 
         @return true
         */
        virtual bool updateMessage(CTNMessage &message)  = 0;
        
        /**
         update message content

         @param msgId msgid
         @param sessionId sessionId
         @param content content json
         @return true
         */
        virtual bool updateContent(const char* msgId, const char* sessionId, const char* content)  = 0;
        
        /**
         update sendStatus

         @param msgId msgId
         @param sessionId sessionId
         @param sendStatus sendStatus
         @return true
         */
        virtual bool updateSendStatus(const char* msgId, const char* sessionId, int32_t sendStatus)  = 0;
        
        /**
         update addition

         @param msgId msgId
         @param sessionId sessionId
         @param addition addition
         @return true
         */
        virtual bool updateAddition(const char* msgId, const char* sessionId, const char* addition)  = 0;
        
        /**
         get messages from database

         @param sessionId sessionId
         @param seqId seqId
         @param count count
         @return messages 
         */
        virtual vector<CTNMessage> getMessages(const char* sessionId, int64_t seqId, int32_t count)  = 0;
        
        /**
         get messages from database, sequencial by seqId
         
         @param sessionId sessionId
         @param seqId seqId
         @param count count
         @return messages
         */
        virtual vector<CTNMessage> getMessagesAsc(const char*  sessionId, int64_t seqId, int32_t count) = 0;

        /**
         get faulting message

         @param sessionId sessionid
         @param seqId seqId
         @param count count
         @return message
         */
        virtual vector<CTNMessage> getFaultMessages(const char* sessionId, int64_t seqId, int32_t count)  = 0;
        
        /**
		 get message classified by contentType under certain sessionId

         @param sessionId sessionId
         @param contentType contentType
         @return message list
         */
        virtual vector<CTNMessage> getMessagesWithContentType(const char* sessionId, CTNMessageContentType contentType) = 0;
        
        /**
		 get messages based on file content type

         @param sessionId sessionId
         @param contentType contentType
         @param formats file suffix type
         @return message list
         */
        virtual vector<CTNMessage> getFileMessagesWithSessionId(const char*  sessionId, CTNMessageContentType contentType,vector<std::string> formats) = 0;
        
        /**
		 get messages based on contentType and isMySelf
         
         @param sessionId select all message when sessionId is empty
         @param contentType content type
         @param isMySelf whether is myself
         @return message list
         */
        virtual vector<CTNMessage> getMessages(const char* sessionId, CTNMessageContentType contentType, CTNOwner isMySelf) = 0;
        
        /**
		 get messages between two seqId

         @param sessionId sessionId
         @param maxSeqId maxSeqId
         @param minSeqId minSeqId
         @return message list
         */
        virtual vector<CTNMessage> getMessagesWithSeqId(const char* sessionId, int64_t maxSeqId, int64_t minSeqId) = 0;
        
        /**
         getMessage

         @param sessionId sessionId
         @param msgId msgId
         @return message list
         */
        virtual CTNMessage getMessage(const char* sessionId, const char* msgId)  = 0;
        
        /**
		 get the max seqId message under certain sessionId and bizNo

         @param sessionId sessionId
         @param bizNo bizNo
         @return message
         */
        virtual CTNMessage getMaxNoticeMessage(const char* sessionId, const char* bizNo) = 0;
        
        /**
         getFaultMessage

         @param sessionId sessionid
         @param priority priority
         @return message
         */
        virtual CTNMessage getFaultMessage(const char* sessionId, int32_t priority)  = 0;
        
        /**
         getLastMessage

         @param sessionId sessionId
         @return message
         */
        virtual CTNMessage getLastMessage(const char* sessionId) = 0;
        
        /**
		 get max seqId under certain sessionId

         @param sessionId sessionId
         @param type priority type: 0 normal, 1 high priority, 2 mixed
         @return message
         */
        virtual int64_t getMaxSeqAllMessage(const char* sessionId, int32_t type) = 0;
        
        /**
		 get max seqId 

         @return seqId
         */
        virtual int64_t getMaxSeqId() = 0;
        
        /**
		 update faulting message
         
         @param sessionId sessionId
         @param msgId msgId
         @param faultSeqId faulting id
         */
        virtual void updateFaultMessage(const char* sessionId, const char* msgId, int64_t faultSeqId) = 0;
        
        /**
		 get notice status type

         @param sessionId sessionId
         @return string
         */
        virtual vector<std::string> getNoticeStatusType(const char* sessionId) = 0;
        
        /**
		 get message list with certain notice type

         @param sessionId sessionId
         @param seqId seqId
         @param count count
         @param noticeStatusType notice status type
         @return message list
         */
        virtual vector<toonim::CTNMessage> getMessageWithNoticeStatusType(const char* sessionId, int64_t seqId, int32_t count, const char* noticeStatusType) = 0;
        
        /**
         search message

         @param keyword keyword
         @param sessionId sessionId
         @param messages message list
         */
        virtual void searchMessage(const char* keyword, const char* sessionId, /*out*/vector<std::vector<std::string> > &messages) = 0;
        
        /**
         get all faulting

         @return faulting sessions
         */
        virtual vector<CTNMessage> getAllFault() = 0;
        
#pragma mark ------------------operateMessage------------
        
        /**
         add operate message

         @param operates operates
         @return true
         */
        virtual bool addOperateMessage(vector<CTNMessageOperate> &operates) = 0;
        
        /**
         delete operate message

         @param msgId msgId
         @return true
         */
        virtual bool deleteOperateMessage(const char* msgId) = 0;
        
        /**
         get operate message

         @param msgId msgId
         @return true
         */
        virtual CTNMessageOperate getOperateMessage(const char* msgId) = 0;
        
        /**
         get all operate message

         @return operateMessage
         */
        virtual vector<CTNMessageOperate> getAllOperateMessages() = 0;
        
        /**
         translate Operate Message

         @param operMessage operMessage
         @return true
         */
        virtual bool translateOperateMessage(CTNMessageOperate operMessage) = 0;//wxy
        
        /**
		 use database version management

         @return void
         */
        virtual uint32_t userVersion() = 0;
        
        /**
         set database version

         @param version version
         */
        virtual void setUserVersion (uint32_t version ) = 0;
    };

   
    class ITnImDBGroupChat
    {
    public:
        virtual ~ITnImDBGroupChat(){}
        
#pragma mark ------------groupInfo--------------
        
        /**
         add groupInfo

         @param groups groups
         @return true
         */
        virtual bool addGroupInfo(vector<CTNGroupInfo> &groups)  = 0;
        
        /**
         delete groupInfo

         @param groupTmail groupTmail
         @return true
         */
        virtual bool deleteGroupInfo(const char* groupTmail)  = 0;
        
        /**
         update groupInfo

         @param groups groups
         @return true
         */
        virtual bool updateGroupInfo(vector<CTNGroupInfo> &groups)  = 0;
        
        /**
         get groupInfo

         @param groupTmail groupTmail
         @return groupInfo list
         */
        virtual CTNGroupInfo getGroupInfo(const char* groupTmail)  = 0;
        
        /**
		 get all joined groups under certain tmail

         @param tmail tmail
         @return group infomation list
         */
        virtual vector<toonim::CTNGroupInfo> getGroupInfoWithMyTmail(const char* tmail) = 0;
        
        /**
		 using keyword, get all joined groups under certain tmail.
		 If tmail is empty, search all joined groups

         @param keyword keyworkd
         @param tmail tmail
         @param groupInofs groupInfos
         */
        virtual void searchGroupInfo(const char* keyword, const char* tmail, /*out*/vector<toonim::CTNGroupInfo> &groupInofs) = 0;
        
        /**
		 search group infomation using keyword, keyword is pinyin. 
		 If tmail is empty, search all joined groups.

         @param keyword keyword
         @param tmail tmail
         @param groupInofs groups
         */
        virtual void searchGroupInfoWithPinyin(const char* keyword, const char* tmail, /*out*/vector<toonim::CTNGroupInfo> &groupInofs) = 0;

#pragma mark -------------------groupMember----------------
        
        /**
         add groupMember

         @param members members
         @return true
         */
        virtual bool addGroupMember(vector<CTNGroupMember> &members)  = 0;
        
        /**
         update groupMembers

         @param members members
         @return true
         */
        virtual bool updateGroupMembers(vector<CTNGroupMember> &members)  = 0;
        
        /**
         delete all groupMeber by groupId

         @param groupTmail groupTmail
         @return true
         */
        virtual bool deleteAllGroupMembers(const char* groupTmail)  = 0;
        
        /**
         delete groupMember by groupTmail and tmail

         @param groupTmail groupTmail
         @param tmail tmail
         @return true
         */
        virtual bool deleteGroupMember(const char* groupTmail, const char* tmail)  = 0;
        
        /**
         get groupMembers

         @param groupTmail groupTmail
         @return groupMember list
         */
        virtual vector<CTNGroupMember> getGroupMembers(const char* groupTmail)  = 0;
        
        /**
         get groupMember by groupTmail and tmail

         @param groupTmail groupTmail
         @param tmail tmail
         @return groupMember
         */
        virtual CTNGroupMember getGroupMember(const char* groupTmail, const char* tmail) = 0;
                
        /**
		 get group members account

         @param groupTmail groupTmail
         @return count
         */
        virtual int getGroupMembersCount(const char* groupTmail) = 0;
        
        /**
		 search group member using keyword

         @param keyword keyword
         @param groupIds groupIds
         @param groupMembers groupMembers
         */
        virtual void searchGroupMember(const char* keyword, const vector<std::string> &groupIds, vector<toonim::CTNGroupMember> &groupMembers) = 0;
        
        /**
		 search group member using keyword, keyword is pinyin
         
         @param keyword is pinyin
         @param groupIds groupIds
         @param groupMembers groupMembers
         */
        virtual void searchGroupMemberWithPinyin(const char* keyword, const vector<std::string> &groupIds, vector<toonim::CTNGroupMember> &groupMembers) = 0;
    };

    
    class ITnImDBSettings
    {
    public:
        virtual ~ITnImDBSettings(){}
        
#pragma mark --------------setting-----------
        
        /**
         add setting

         @param sessionId key 
         @param type type
         @param value value
         @return true
         */
        virtual bool addSessionSetting(const char* sessionId, CTNSESSIONTYPE type, const char* value) = 0;
        
        /**
         update setting

         @param sessionId key 
         @param type type
         @param value value
         @return true
         */
        virtual bool updateSessionSetting(const char* sessionId, CTNSESSIONTYPE type, const char* value) = 0;
        
        /**
         get setting

         @param sessionId key 
         @param type type
         @return setting
         */
        virtual CTNSessionSetting getSessionSetting(const char* sessionId, CTNSESSIONTYPE type) = 0;
        
        /**
         delete setting

         @param sessionId key 
         @param type type
         @return true
         */
        virtual bool deleteSessionSetting(const char* sessionId, CTNSESSIONTYPE type) = 0;
        
    };
        
#pragma mark -------------------tmail--------------------
    class ITnImDBTmail
    {
    public:
        virtual ~ITnImDBTmail(){};
        
        /**
         add tmail

         @param ctnTmail CTNTmail
         @return result
         */
        virtual bool addTmail(CTNTmail &ctnTmail) = 0;

        /**
         add tmail list

         @param tmailList tmail
         @return resutl
         */
        virtual bool addTmailList(vector<CTNTmail> &tmailList) = 0;

        /**
         delete tmail

         @param tmail tmail
         @return result
         */
        virtual bool deleteTmail(const char* tmail) = 0;

        /**
         update tmail list

         @param tmailList tmail
         @return result
         */
        virtual bool updateTmailList(vector<CTNTmail> &tmailList) = 0;

        /**
         update tmail

         @param ctnTamil CTNTmail
         @return result
         */
        virtual bool updateTmail(CTNTmail &ctnTamil) = 0;

        /**
         get tmail

         @param tmail tmail
         @return CTNTmail
         */
        virtual CTNTmail getTmail(const char* tmail) = 0;

        /**
         get all tmail list

         @param tmailList tmail list
         */
        virtual void getTmailList(vector<CTNTmail> &tmailList) = 0;

        /**
         get tmail detail list

         @param tmailVct timail list
         @param tmailList CTNTmail
         */
        virtual void getTmailDetailList(vector<std::string> &tmailVct, vector<CTNTmail> &tmailList) = 0;
        
        /**
         add relation list

         @param relationList relation
         */
        virtual void addRelationList(vector<CTNRelation> &relationList) = 0;
        
        /**
         update relation

         @param relationList relationList
         */
        virtual void updateRelationList(vector<CTNRelation> &relationList) = 0;
        
        /**
         update relation

         @param relation CTNRelation
         */
        virtual void updateRelation(CTNRelation &relation) = 0;
        
        /**
         delete relation

         @param activeTmail activeTmail
         @param passiveTmail passiveTmail
         @param relationType relationType
         */
        virtual void deleteRelation(const char* activeTmail, const char* passiveTmail, int32_t relationType) = 0;
        
        /**
		 get relation status

         @param activeTmail active tmail
         @param passiveTmail passive tmail
         @param relationType relation type
         @return int
         */
        virtual int getRelationStatus(const char* activeTmail, const char* passiveTmail, int32_t relationType) = 0;
        
        /**
         get relation between two

         @param activeTmail active tmail
         @param passiveTmail passive tmail
         @return CTNRelation
         */
        virtual CTNRelation getRelation(const char* activeTmail, const char* passiveTmail) = 0;
        
        /**
		 get all relations under certain tmail classified by relationType
         
         @param relationType relation
         @param relationList relationList
         */
        virtual void getAllRelationList(int32_t relationType, const char* myTmail, /*out*/vector<CTNRelation> &relationList) = 0;
        
        /**
         get top status

         @param activeTmail activeTmail
         @param sessionId sessionId
         @return bool
         */
        virtual bool getTopStatus(const char* activeTmail, const char* sessionId) = 0;
                
        /**
         add userTmail

         @param userTmail CTNUser
         */
        virtual void addUserTmail(CTNUserTmail &userTmail) = 0;
        
        /**
         add tmail list

         @param tmailList tmailList
         */
        virtual void addUserTmailList(vector<toonim::CTNUserTmail> &tmailList) = 0;
        
        /**
         update userTamil

         @param userTamil CTNUser
         */
        virtual void updateUserTmail(CTNUserTmail &userTamil) = 0;
        
        /**
         get tmail information

         @param tmail tmail
         @return CTNUser
         */
        virtual CTNUserTmail getUserTmail(const char* tmail) = 0;
        
        /**
		 get all user infomation classified by tmailType
         
         @param tmailType tmail type: 1 normal, 3 user, 6 organization
         @return CTNUser list
         */
        virtual vector<CTNUserTmail> getAllUserTmail(int32_t tmailType) = 0;
        
        /**
		 get all my tmail infomation

         @param typeVct tmail type: 1 normal, 3 user, 6 organization
         @return result
         */
        virtual vector<CTNUserTmail> getMyTmails(vector<int32_t> typeVct) = 0;
        
        /**
		 whether is my tmail

         @param tmail tmail
         @return result
         */
        virtual bool isMySelfTmail(const char* tmail) = 0;

        /*
		get my tmail list

         @return tmails
         */
        virtual vector<string> getMyAllTmailList() = 0;
        
        /**
		 delete tmail information

         @param tmail tmail
         */
        virtual void deleteUserTmail(const char* tmail) = 0;
        
        /**
         add friend information

         @param addressTmail addressTmail
         */
        virtual void addAddress(CTNAddress &addressTmail) = 0;
        
        /**
		 add friend information list

         @param addressList addressList
         */
        virtual void addAddressList(vector<CTNAddress> &addressList) = 0;
        
        /**
         update friend information 

         @param addressTmail addressTmail
         */
        virtual void updateAddress(CTNAddress &addressTmail) = 0;
        
        /**
         update friend information list

         @param addressList addressList
         */
        virtual void updateAddressList(vector<CTNAddress> &addressList) = 0;
        
        /**
         delete friend information 

         @param myTmail my tmail
         @param friendTmail friend tmail
         */
        virtual void deleteAddress(const char* myTmail, const char* friendTmail) = 0;
        
        /**
         get friend tmail

         @param myTmail 我的tmail
         @param friendTmail 好友的tmail
         @return CTNAddress
         */
        virtual CTNAddress getFriendTmail(const char* myTmail, const char* friendTmail) = 0;
        
        /**
		 get friend list under certain tmail

         @param myTmail if myTmail is empty, get all friend list 
         @param addressList addressList
         */
        virtual void getAddressList(const char* myTmail, vector<CTNAddress> &addressList) = 0;
        
        /**
         search friend based on keyword

         @param keyword keyword
         @param myTmail myTmail
         @param tmailList CTNTmail list
         */
        virtual void searchMyFriendList(const char* keyword, const char* myTmail, vector<toonim::CTNAddress> &tmailList) = 0;

        /**
		 get friend information list

         @param tmailVct tmailList
         @param tmailList CTNTmail list
         */
        virtual void getContactTmailDetailWithTmail(vector<std::string> &tmailVct, vector<toonim::CTNAddress> &tmailList) = 0;

		/**
		 judge is my friend

         @param myTmail myTmail
         @param friendTmail peer tmail
         @return bool
         */
        virtual bool isMyFriend(const char* myTmail, const char* friendTmail) = 0;
        
        /**
		add menu config list
         
         @param menuList menuList
         */
        virtual void addMenuConfigList(vector<CTNMenuConfig> &menuList) = 0;
        
        /**
		 delete menu config
         
         @param menuId menuId
         */
        virtual void deleteMenuConfig(int64_t menuId) = 0;
        
        /**
		 get left corner menu config list
         */
        virtual void getLeftMenuConfigList(vector<CTNMenuConfig> &leftMenuList) = 0;
        
        /**
		 get right corner menu config list
         */
        virtual void getRightMenuConfigList(vector<CTNMenuConfig> &rightMenuList) = 0;
        
        /**
		 add setting

         @param key key
         @param value value
         */
        virtual void addSetting(const char* key, const char* value) = 0;
        
        /**
		 update config information

         @param key key
         @param value value
         */
        virtual void updateSetting(const char* key, const char* value) = 0;
        
        /**
         delete config information

         @param key key
         */
        virtual void deleteSetting(const char* key) = 0;
        
        /**
		 get tmail setting

         @param key key
         @return value
         */
        virtual std::string getTmailSetting(const char* key) = 0;

        /**
         add app NO info

         @param appNoInfo appNoInfo
         @return bool
         */
        virtual bool addAppNoInfo(CTNAppNoInfo &appNoInfo) = 0;

        /**
         add app NO info list

         @param appNoInfoList appNoInfoList
         @return bool
         */
        virtual bool addAppNoInfoList(vector<CTNAppNoInfo> &appNoInfoList) = 0;

        /**
         update app NO info isSubscribe

         @param isSubscribe isSubscribe
         @param appId appId
         @return bool
         */
        virtual bool updateAppInfoIsSubscribe(bool isSubscribe, int64_t appId) = 0;

        /**
         add app NO menu list

         @param appNoMenuList appNoMenuList
         @return bool
         */
        virtual bool addAppNoMenuList(vector<CTNAppNoMenu> &appNoMenuList) = 0;


        /**
         get app NO menu list

         @param tmail bind tmail
         @param appNoMenuList appNoMenuList
         */
        virtual void getAppNoMenuList(const char* tmail, vector<CTNAppNoMenu> &appNoMenuList) = 0;
    };
    
    void resetDB();
    
    //@todo may have concurrent issue add by lanhuaiyu@20171014
  
    void initImDB(const char* clientId, const char* appPath);
    
    ITnImDBChat* getChatDB();
    
    ITnImDBGroupChat* getGroupChatDB();
    
    ITnImDBSettings* getSettingsDB();
    
    ITnImDBTmail* getTmailDB();
    
}


#endif /* CTNDBAPI_hpp */
