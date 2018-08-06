//
// Created by juzenhon on 2017/8/30.
//

#ifndef TMTP_CTNHTTPBIZAPI_H
#define TMTP_CTNHTTPBIZAPI_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include <functional>
#include "CTNDBHeader.h"

using namespace std;

namespace toonim {

    /**
     * flag: 0 for success, -1 for error
     * response: returned json content
     * userData: context data pointer
     */
    typedef std::function<void(int flag, const char *response, void *userData)> HttpCallback;

    class ITnGroupChat
    {
    public:
        ITnGroupChat(){}
        virtual ~ITnGroupChat(){}

        /**
         * 创建群聊
         * @param tmail 创建者的tmail model
         * @param groupChatName 群聊名称
         * @param creatorCardId creatorCardId
         * @param member 初始成员
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void createGroupChat(toonim::CTNTmail &tmail, const char* groupTmail, const char *groupChatName, int64_t creatorCardId, vector<toonim::CTNGroupMember> &member, HttpCallback response, void *userData) = 0;

        /**
         * 获取用户已加入的群聊
         * @param userId 用户Id
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void obtainAllGroupChat(const char *userId, HttpCallback response, void *userData) = 0;

        /**
         * 邀请加入群聊
         * @param groupTmail 群聊id
         * @param tmail 我的feedId
         * @param myName 我的名字
         * @param source 来源
         * @param member 邀请加入的来源
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void addGroupChatMember(const char* groupTmail, const char *tmail, const char *myName, int32_t source,vector<toonim::CTNGroupMember> &member, HttpCallback response, void *userData) = 0;
        /**
         * 获取群聊成员列表
         * @param groupTmail 群聊Id
         * @param response 响应回调
         * @param userData 用户数据
         */

        virtual void obtainMembersByGroupChatId(const char *groupTmail, HttpCallback response, void *userData) = 0;

        /**
         * 退出群聊
         * @param groupTmail 群聊Id
         * @param tmail  名片Id
         * @param response 响应回调
         * @param userData 用户数据
         */

        virtual void exitGroupChat(const char* groupTmail, const char *tmail, const char *title,HttpCallback response,void *userData) = 0;

        /**
         * 批量移除群成员
         * @param tmail tmail
         * @param title title
         * @param groupTmail  群聊Id
         * @param removeList 移除成员列表
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void removeGroupChatMembers(const char *tmail, const char *title, const char* groupTmail, vector<toonim::CTNGroupMember> &removeList, HttpCallback response, void *userData) = 0;

        /**
         * 批量移除feed下所有群聊
         * @param tmail 名片Id
         * @param userId 用户Id
         * @param title 名片昵称
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void removeGroupChatMembersByFeedId(const char *tmail, const char *userId, const char *title,  HttpCallback response, void *userData) = 0;

        /**
         * 修改群聊名称
         * @param groupTmail 群聊Id
         * @param newGroupName 群聊名称
         * @param tmail 我自己tmail
         * @param myName 我的名称
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void updateGroupChat(const char* groupTmail, const char *newGroupName, const char *tmail, const char *myName, HttpCallback response, void *userData) = 0;

        /**
         * 批量获取群聊信息
         *
         * @param groupTmailList 要获取的群成员信息
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void obtainGroupChatInfo(vector<string> &groupTmailList, HttpCallback response, void *userData) = 0;
        
        /**
         群主转让

         @param groupTmail 群聊id
         @param tmail 我自己的tmail
         @param title 我自己的title
         @param memberTmail 转让的群成员信息（headImage，memberTmail，name，tuid）
         */
        virtual void groupChatTransferOwner(const char* groupTmail, const char* tmail, const char* title, toonim::CTNGroupMember memberTmail, HttpCallback response, void *userData) = 0;
        
        /**
         dismiss groupchat
         
         @param groupTmail groupTmail
         @param callback callback
         @param userData userData
         */
        virtual void dismissGroupChat(const char* groupTmail,HttpCallback callback, void *userData) = 0;
        
    };

    class ITnTmail {
    public:
        ITnTmail(){}
        virtual ~ITnTmail(){}
        
        /**
         create relation

         @param relation relation model
         @param remark remark
         @param response response
         @param userData userData
         */
        virtual void createRelation(CTNRelation &relation, const char* remark, HttpCallback response, void *userData) = 0;
        
        /**
         添加好友
         
         @param address CTNAddress model
         @param response response
         @param userData userData
         */
        virtual void addAddress(CTNAddress &address, HttpCallback response, void *userData) = 0;
        
        /**
         更新备注名
         
         @param platformTmail 分配给账号/名片平台的tmail地址
         @param activeTmail 主动方tmail
         @param passiveTmail 被动房tmail
         @param signedData 先用分配给账号/名片平台的私钥加签随机数，再用tmail平台的公钥加密的数据
         @param random 随机数
         @param remark 备注名
         @param response response
         @param userData userData
         */
        virtual void updateRemark(const char* platformTmail, const char* activeTmail, const char* passiveTmail, const char *signedData, const char* random, const char* remark, HttpCallback response, void *userData) = 0;
        
        /**
         查询关系

         @param platformTmail 分配给账号/名片平台的tmail地址
         @param activeTmail 主动方tmail
         @param passiveTmail 被动房tmail
         @param signedData 先用分配给账号/名片平台的私钥加签随机数，再用tmail平台的公钥加密的数据
         @param response response
         @param userData userData
         */
        virtual void queryRelation(const char* platformTmail, const char* activeTmail, const char* passiveTmail, const char* signedData, HttpCallback response, void *userData) = 0;
        
        /**
         查询user的所有关系，增量更新接口

         */
        virtual void queryUserRelation() = 0;
        
        /**
         update relaiton cardid

         @param address CTNAddress  activeTmail  passiveTmail activeCardId passiveCardId
         @param callback callback
         @param userData userData
         */
        virtual void updateRelationReq(toonim::CTNAddress &address, HttpCallback callback, void* userData) = 0;
        
        /**
         好友列表查询
         
         @param tuid tuid
         @param signedData 先用分配给账号/名片平台的私钥加签随机数，再用tmail平台的公钥加密的数据
         @param response response
         @param userData userData
         */
        virtual void queryAddressByTmail(const char* tuid, const char* signedData, HttpCallback response, void *userData) = 0;
        
        /**
         更新好友信息

         @param platformTmail 分配给账号/名片平台的tmail地址
         @param activeTmail 主动方tmail
         @param passiveTmail 被动方tmail
         @param msgMap 需要更新的信息，key值为phones、emails、star等
         @param signedData 认证信息
         @param random 随机数
         @param response response
         @param userData userData
         */
        virtual void updateFriendMessage(const char* platformTmail, const char* activeTmail, const char* passiveTmail, map<std::string, std::string> msgMap, const char* signedData, const char* random, HttpCallback response, void *userData) = 0;
        
        /**
         删除联系人

         @param activeTmail 主动方tmail，我自己的tmail
         @param passiveTmail 好友的tmail
         @param response response
         @param userData userData
         */
        virtual void deleteConnectPeople(const char* activeTmail, const char* passiveTmail, HttpCallback response, void *userData) = 0;
        
        /**
         set blacklist

         @param activeTmail activeTmail
         @param passiveTmail passiveTmail
         @param status status
         @param callback callback
         @param userData userData
         */
        virtual void setBlackList(const char* activeTmail, const char* passiveTmail, bool status, HttpCallback callback, void *userData) = 0;
        
        /**
         set top status

         @param activeTmail activeTmail
         @param passiveTmail passiveTmail
         @param sessionId sessionId
         @param status status, 0 no, 1 yes
         @param callback callback
         @param userData userData
         */
        virtual void setTopStatus(const char* activeTmail, const char* passiveTmail, const char* sessionId, bool status, HttpCallback callback, void *userData) = 0;
        
        /**
         set disturbStatus

         @param activeTmail avtiveTmail
         @param passiveTmail passiveTmail
         @param callback callback
         @param status status, 0 no, 1 yes
         @param userData userData
         */
        virtual void setDisturbStatus(const char* activeTmail, const char* passiveTmail,bool status,  HttpCallback callback, void *userData) = 0;
        
        /**
         query all disturb

         @param callback callback
         @param userData userdata
         */
        virtual void queryAllDisturb(HttpCallback callback, void *userData) = 0;
        
        /**
         query balcklist

         @param callback callback
         @param userData userData
         */
        virtual void queryAllBlacklist(HttpCallback callback, void *userData) = 0;
        
        /**
         query top

         @param callback callback
         @param userData userData
         */
        virtual void queryAllTop(HttpCallback callback, void *userData) = 0;
        
        /**
         查询联系人信息

         @param platformTmail 分配给账号/名片平台的tmail地址
         @param activeTmail 主动方tmail
         @param passiveTmail 被动方tmail
         @param signedData 认证信息
         @param response response
         @param userDatanst userData
         */
        virtual void queryContactInfo(const char* platformTmail, const char* activeTmail, const char* passiveTmail, const char* signedData, HttpCallback response, void *userDatanst) = 0;
        
        /**
         查询tmail的详情

         @param tmail tmail
         @param response response
         @param userData userData
         */
        virtual void queryTmailDetail(const char* tmail, HttpCallback response, void *userData) = 0;

        /**
         批量查询tmail详情接口

         @param tmails tmail拼接字符串，以逗号相隔
         @param response response
         @param userData userdata
         */
        virtual void queryTmailsInfoByTmails(const char* tmails, HttpCallback response, void *userData) = 0;
        
        /**
         更新tmailinfo

         @param tmailMap 更新的字段对应CTNUserTmail字段
         @param response response
         @param userData userData
         */
        virtual void updateTmailInfo(map<string, std::pair<mapKeyType, string>> &tmailMap, HttpCallback response, void *userData) = 0;
        
//        /**
//         更新tmail是否被搜索开关
//
//         @param tmail 我的tmail
//         @param status 状态
//         @param response response
//         @param userData userdata
//         */
//        virtual void updateTmailSearchSwitch(const char* tmail, int32_t status, HttpCallback response, void* userData) = 0;
        
        /**
         初始化账户级tmail

         @param userTmail userTmail
         @param path 公钥存储路径
         @param response response
         @param userData userData
         */
        virtual void initUcmail(CTNUserTmail &userTmail, const char* path, HttpCallback response, void *userData) = 0;
        
        /**
         初始化普通tmail信息

         @param userTmail userTmail
         @param tuid tuid
         @param path path
         @param response response
         @param userData userData
         */
        virtual void initTcmail(CTNUserTmail &userTmail, const char* tuid, const char* path, HttpCallback response, void *userData) = 0;
        
        /**
         userId 桥接绑定tmail
         
         @param userId 用户的userId
         @param tmail 桥接的tmail
         @param response response
         @param userData userData
         */
        virtual void userIdBindTmail(const char* userId, const char* tmail, HttpCallback response, void *userData) = 0;
        
        /**
         校验tmail是否合法

         @param tmail tmail
         @param tmailType tmailType
         @param response response
         @param userData userData
         */
        virtual void checkTmail(const char* tmail, int32_t tmailType, HttpCallback response, void *userData) = 0;
        
        /**
         获取首页menu

         @param appVersion appVersion
         @param appType appType
         @param response response
         @param userData userData
         */
        virtual void queryFirstMenuConfig(const char* appVersion, const char* appType, HttpCallback response, void *userData) = 0;
        
        /**
         获取输入板配置

         @param appVersion appVersion
         @param appType appType
         @param response response
         @param userData userData
         */
        virtual void queryComplexMenuConfig(const char* appVersion, const char* appType, HttpCallback response, void *userData) = 0;
        
    };

    class TINAppAccount {
    public:
        TINAppAccount(){}
        virtual ~TINAppAccount(){}

        /**
         查询应用号

         @param type 0 全查， 1查已订阅
         @param name 搜索的名称或者tmail地址
         @param pageNum 页码
         @param pageSize 每页的数量
         @param response response
         @param userData userData
         */
        virtual void queryAppNo(int32_t type, const char* name, int32_t pageNum, int32_t pageSize, HttpCallback response, void *userData) = 0;

        /**
         关注应用号

         @param isSubscribe 0 取消关注， 1添加关注
         @param appNoId 应用ID
         @param appNoTmail 应用tmail
         @param response response
         @param userData userData
         */
        virtual void subscribeAppNo(bool isSubscribe, int32_t appNoId, const char* appNoTmail, HttpCallback response, void *userData) = 0;

        /**
         查询应用号菜单

         @param tmail 应用号绑定的tmail
         @param response response
         @param userData userData
         */
        virtual void queryAppNoMenu(const char* tmail, HttpCallback response, void *userData) = 0;
    };
    
    /**
     * 初始化http业务接口
     * @param clientId userId
     * @param token 用户登录token
     * @param deviceId deviceId
     * @param toonType toonType
     * @param version app版本号
     * @param platformVersion  系统版本号"iOS 10.2.1"
     * @param cerPath 公钥保存路径
     */
    void initHttpBiz(const char* clientId, const char* token, const char* deviceId,
                              int32_t toonType, const char* version, const char* platformVersion,const char* cerPath);
    
    
    /**
     * 添加HTTP 业务用到的MLB
     * @param domain 域名
     * @param url 对应的真实URL
     */
     void appendHttpRouter(const char* domain, const char* url);
        
    ITnGroupChat* getGroupChat();
    ITnTmail *getTmail();
    TINAppAccount *getAppAccount();

#define TNCBIZ_GROUPCHAT  toonim::getGroupChat()
#define TNCBIZ_TMAIL      toonim::getTmail()
#define TNCBIZ_APPACCOUNT toonim::getAppAccount()
}

#endif //TMTP_CTNHTTPBIZAPI_H
