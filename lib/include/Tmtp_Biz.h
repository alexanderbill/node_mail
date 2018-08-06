// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 4.7.1 by WSRD Tencent.
// Generated from `Tmtp_Biz.jce'
// **********************************************************************

#ifndef __TMTP_BIZ_H_
#define __TMTP_BIZ_H_

#include <map>
#include <string>
#include <vector>
#include "jce/Jce.h"
using namespace std;


namespace Toon
{
    struct BizMsg : public taf::JceStructBase
    {
    public:
        static string className()
        {
            return "Toon.BizMsg";
        }
        static string MD5()
        {
            return "1f39ecc31e7939a52b15762e250d9b82";
        }
        BizMsg()
        :contentType(0),content(""),senderName(""),contentFrom("")
        {
        }
        template<typename WriterT>
        void writeTo(taf::JceOutputStream<WriterT>& _os) const
        {
            _os.write(contentType, 0);
            _os.write(content, 1);
            _os.write(senderName, 2);
            _os.write(atTmails, 3);
            _os.write(topics, 4);
            _os.write(contentFrom, 5);
        }
        template<typename ReaderT>
        void readFrom(taf::JceInputStream<ReaderT>& _is)
        {
            _is.read(contentType, 0, false);
            _is.read(content, 1, false);
            _is.read(senderName, 2, false);
            _is.read(atTmails, 3, false);
            _is.read(topics, 4, false);
            _is.read(contentFrom, 5, false);
        }
        ostream& display(ostream& _os, int _level=0) const
        {
            taf::JceDisplayer _ds(_os, _level);
            _ds.display(contentType,"contentType");
            _ds.display(content,"content");
            _ds.display(senderName,"senderName");
            _ds.display(atTmails,"atTmails");
            _ds.display(topics,"topics");
            _ds.display(contentFrom,"contentFrom");
            return _os;
        }
        ostream& displaySimple(ostream& _os, int _level=0) const
        {
            taf::JceDisplayer _ds(_os, _level);
            _ds.displaySimple(contentType, true);
            _ds.displaySimple(content, true);
            _ds.displaySimple(senderName, true);
            _ds.displaySimple(atTmails, true);
            _ds.displaySimple(topics, true);
            _ds.displaySimple(contentFrom, false);
            return _os;
        }
    public:
        taf::Int32 contentType;
        std::string content;
        std::string senderName;
        vector<std::string> atTmails;
        vector<std::string> topics;
        std::string contentFrom;
    };
    inline bool operator==(const BizMsg&l, const BizMsg&r)
    {
        return l.contentType == r.contentType && l.content == r.content && l.senderName == r.senderName && l.atTmails == r.atTmails && l.topics == r.topics && l.contentFrom == r.contentFrom;
    }
    inline bool operator!=(const BizMsg&l, const BizMsg&r)
    {
        return !(l == r);
    }

    struct BizCommand : public taf::JceStructBase
    {
    public:
        static string className()
        {
            return "Toon.BizCommand";
        }
        static string MD5()
        {
            return "a57f8da986bead0d2d4516c7a94ee89c";
        }
        BizCommand()
        :opType(0),msgId(""),operatorTmail(""),operatorName(""),exContent(""),sessionid("")
        {
        }
        template<typename WriterT>
        void writeTo(taf::JceOutputStream<WriterT>& _os) const
        {
            _os.write(opType, 0);
            _os.write(msgId, 1);
            _os.write(operatorTmail, 2);
            _os.write(operatorName, 3);
            _os.write(exContent, 4);
            _os.write(sessionid, 5);
        }
        template<typename ReaderT>
        void readFrom(taf::JceInputStream<ReaderT>& _is)
        {
            _is.read(opType, 0, true);
            _is.read(msgId, 1, false);
            _is.read(operatorTmail, 2, false);
            _is.read(operatorName, 3, false);
            _is.read(exContent, 4, false);
            _is.read(sessionid, 5, false);
        }
        ostream& display(ostream& _os, int _level=0) const
        {
            taf::JceDisplayer _ds(_os, _level);
            _ds.display(opType,"opType");
            _ds.display(msgId,"msgId");
            _ds.display(operatorTmail,"operatorTmail");
            _ds.display(operatorName,"operatorName");
            _ds.display(exContent,"exContent");
            _ds.display(sessionid,"sessionid");
            return _os;
        }
        ostream& displaySimple(ostream& _os, int _level=0) const
        {
            taf::JceDisplayer _ds(_os, _level);
            _ds.displaySimple(opType, true);
            _ds.displaySimple(msgId, true);
            _ds.displaySimple(operatorTmail, true);
            _ds.displaySimple(operatorName, true);
            _ds.displaySimple(exContent, true);
            _ds.displaySimple(sessionid, false);
            return _os;
        }
    public:
        taf::Int32 opType;
        std::string msgId;
        std::string operatorTmail;
        std::string operatorName;
        std::string exContent;
        std::string sessionid;
    };
    inline bool operator==(const BizCommand&l, const BizCommand&r)
    {
        return l.opType == r.opType && l.msgId == r.msgId && l.operatorTmail == r.operatorTmail && l.operatorName == r.operatorName && l.exContent == r.exContent && l.sessionid == r.sessionid;
    }
    inline bool operator!=(const BizCommand&l, const BizCommand&r)
    {
        return !(l == r);
    }

    struct BizReceipt : public taf::JceStructBase
    {
    public:
        static string className()
        {
            return "Toon.BizReceipt";
        }
        static string MD5()
        {
            return "a0f7f1c70b82271b1f084e61faf77494";
        }
        BizReceipt()
        :maxSeqId(0),minSeqId(0)
        {
        }
        template<typename WriterT>
        void writeTo(taf::JceOutputStream<WriterT>& _os) const
        {
            _os.write(maxSeqId, 0);
            _os.write(minSeqId, 1);
        }
        template<typename ReaderT>
        void readFrom(taf::JceInputStream<ReaderT>& _is)
        {
            _is.read(maxSeqId, 0, true);
            _is.read(minSeqId, 1, true);
        }
        ostream& display(ostream& _os, int _level=0) const
        {
            taf::JceDisplayer _ds(_os, _level);
            _ds.display(maxSeqId,"maxSeqId");
            _ds.display(minSeqId,"minSeqId");
            return _os;
        }
        ostream& displaySimple(ostream& _os, int _level=0) const
        {
            taf::JceDisplayer _ds(_os, _level);
            _ds.displaySimple(maxSeqId, true);
            _ds.displaySimple(minSeqId, false);
            return _os;
        }
    public:
        taf::Int64 maxSeqId;
        taf::Int64 minSeqId;
    };
    inline bool operator==(const BizReceipt&l, const BizReceipt&r)
    {
        return l.maxSeqId == r.maxSeqId && l.minSeqId == r.minSeqId;
    }
    inline bool operator!=(const BizReceipt&l, const BizReceipt&r)
    {
        return !(l == r);
    }

    struct BizPushInfo : public taf::JceStructBase
    {
    public:
        static string className()
        {
            return "Toon.BizPushInfo";
        }
        static string MD5()
        {
            return "2e45701425f70f0e5c722cbe2c3f508e";
        }
        BizPushInfo()
        :push_url("")
        {
        }
        template<typename WriterT>
        void writeTo(taf::JceOutputStream<WriterT>& _os) const
        {
            _os.write(push_url, 0);
        }
        template<typename ReaderT>
        void readFrom(taf::JceInputStream<ReaderT>& _is)
        {
            _is.read(push_url, 0, false);
        }
        ostream& display(ostream& _os, int _level=0) const
        {
            taf::JceDisplayer _ds(_os, _level);
            _ds.display(push_url,"push_url");
            return _os;
        }
        ostream& displaySimple(ostream& _os, int _level=0) const
        {
            taf::JceDisplayer _ds(_os, _level);
            _ds.displaySimple(push_url, false);
            return _os;
        }
    public:
        std::string push_url;
    };
    inline bool operator==(const BizPushInfo&l, const BizPushInfo&r)
    {
        return l.push_url == r.push_url;
    }
    inline bool operator!=(const BizPushInfo&l, const BizPushInfo&r)
    {
        return !(l == r);
    }


}

#define Toon_BizMsg_JCE_COPY_STRUCT_HELPER   \
        jce_copy_struct(a.contentType,b.contentType);jce_copy_struct(a.content,b.content);jce_copy_struct(a.senderName,b.senderName);jce_copy_struct(a.atTmails,b.atTmails);jce_copy_struct(a.topics,b.topics);jce_copy_struct(a.contentFrom,b.contentFrom);

#define Toon_BizCommand_JCE_COPY_STRUCT_HELPER   \
        jce_copy_struct(a.opType,b.opType);jce_copy_struct(a.msgId,b.msgId);jce_copy_struct(a.operatorTmail,b.operatorTmail);jce_copy_struct(a.operatorName,b.operatorName);jce_copy_struct(a.exContent,b.exContent);jce_copy_struct(a.sessionid,b.sessionid);

#define Toon_BizReceipt_JCE_COPY_STRUCT_HELPER   \
        jce_copy_struct(a.maxSeqId,b.maxSeqId);jce_copy_struct(a.minSeqId,b.minSeqId);

#define Toon_BizPushInfo_JCE_COPY_STRUCT_HELPER   \
        jce_copy_struct(a.push_url,b.push_url);



#endif
