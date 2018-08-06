//
// Created by juzenhon on 2017/8/31.
//

#ifndef TMTP_META_H_H
#define TMTP_META_H_H

#include <string>
#include <rapidjson/document.h>

class BizMeta {

public:

    static void Parse(rapidjson::Value& value, BizMeta &bean) {
        if (value.HasMember("message") && value["message"].IsString()) {
            bean.message = value["message"].GetString();
        }
        if (value.HasMember("code") && value["code"].IsInt()) {
            bean.code = value["code"].GetInt();
        }
        if (value.HasMember("offset") && value["offset"].IsInt()) {
            bean.offset = value["offset"].GetInt();
        }
        if (value.HasMember("limit") && value["limit"].IsInt()) {
            bean.limit = value["limit"].GetInt();
        }
        if (value.HasMember("total") && value["total"].IsInt()) {
            bean.total = value["total"].GetInt();
        }
    }
    std::string message;
    int code;
    int offset;
    int limit;
    long total;
};


#endif //TMTP_META_H_H
