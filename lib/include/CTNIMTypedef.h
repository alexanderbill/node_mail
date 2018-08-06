/**
 *   CTNIMTypedef_h
 *
 *
 *  Created by 兰怀玉 on 2017/12/20.
 *
 */

#ifndef CTNIMTypedef_h
#define CTNIMTypedef_h

#include "TMTPConst.h"
#include "tmtp_type.h"


typedef enum Toon_MSG_TYPE  CTNIMMessageType;

enum CTNMessageSendStatus
{
    CTNMessageDraft = 0,
    CTNMessageSending = 1,
    CTNMessageSuccess = 2,
    CTNMessageFailed = 3,
};

enum CTNMessageFileStatus
{
    CTNFileStatusNotDownload = 1,
    CTNFileStatusDownloading = 2,
    CTNFileStatusDownloaded = 3,
    CTNFileStatusDownloadFailed = 4,
    CTNFileStatusDownloadCancel = 5,
    
    CTNFileStatusSended = 6,
    CTNFileStatusSending = 7,
    CTNFileStatusSendCancel = 8,
    CTNFileStatusSendFailed = 9
};

enum CTNMessageContentType{
    CTNChatTypeNone = 0,
    CTNChatTypeText = 1,
    CTNChatTypeVoice = 2,
    CTNChatTypeImage = 3,
    CTNChatTypeVcard = 4,
    CTNChatTypeLocation = 5,
//    CTNChatTypeNotification = 6,    //old notification
    CTNChatTypeSystem = 7,			// system message, similar with text
    CTNChatTypeCollect = 8,
    CTNChatTypeVedio = 10,
    CTNChatTypeGifImage = 12,
    CTNChatTypeFiles = 14,			
    CTNChatTypeShare = 15,
    CTNChatTypeRedEnvelope = 16,	// red packet
    CTNChatTypeRichMedia = 17,		// rich media
    CTNChatTypeCustomizedNotification = 20, //new customized notification
    CTNChatTypeRecommend = 21,
    CTNChatTypeEmail = 22, //邮件
    CTNChatTypeTime = 1001,
    CTNChatTypeSeparate = 1007,
    CTNChatTypeRevoked = 2000
};

enum CTNSyncMessageContentType {
    CTNSyncTypeCreateTmail = 1,		// new created tmail
    CTNSyncTypeAddFriend = 2,		// add friend
    CTNSyncTypeDeleteFriend = 3,    // delete friend
    CTNSyncTypeBlackList = 4,       // black list
    CTNSyncTypeDisturb = 5,         // disturb
    CTNSyncTypeGroupInfo = 6,		// group infomation changed
    CTNSyncTypeGroupMember = 7,		// group member changed
    CTNSyncTypeTopStatus = 8        // top status
};

enum CTNIMMessageStatus{
    CTNIMMessageNormal = 0,
    CTNIMMessageRevoked = 1,		// revoke message
    CTNIMMessageDeleted = 2,		// delete 
    CTNIMMessageNoSession = 3,		// don't handle in local module
};


enum CTNOwner{
    CTNOwnerOther = 0,				// peer
    CTNOwnerMyself = 1,				// myself
    CTNOwnerUnkown = 2,				// unknown, need update
};

enum CTNAtType{
    CTNAtTypeNone = 0,
    CTNAtTypeAll = 1,				// all
    CTNAtTypeSome = 2,				// some
};

//@ all members
#define TOON_IM_AT_ALL_MEMBERS      "TOON_IM_AT_ALL_MEMBERS"

//sendtype, single and group 
#define TYPE_SINGLE_DISPATCH_REQ    TYPE_SINGLE_DISPATCH_REQ
#define TYPE_GROUP_DISPATCH_REQ    TYPE_GROUP_DISPATCH_REQ

//functional disabled flag 
#define IM_SINGLECHAT_SEND_DISABLE      "IM_SINGLECHAT_SEND_DISABLE"
#define IM_GROUCHAT_SEND_DISABLE        "IM_GROUCHAT_SEND_DISABLE"
#define IM_GROUPCHAT_CREATE_DISABLE     "IM_GROUPCHAT_CREATE_DISABLE"
#define IM_GROUPCHAT_ADDMEMBER_DISABLE  "IM_GROUPCHAT_ADDMEMBER_DISABLE"
#define IM_GROUPCHAT_RMMEMBER_DISABLE   "IM_GROUPCHAT_RMMEMBER_DISABLE"


#define BIT0 (1)
#define BIT1 (BIT0 << 1)
#define BIT2 (BIT0 << 2)
#define BIT3 (BIT0 << 3)
#define BIT4 (BIT0 << 4)
#define BIT5 (BIT0 << 5)
#define BIT6 (BIT0 << 6)
#define BIT7 (BIT0 << 7)


#endif /* CTNDIMTypedef_h */
