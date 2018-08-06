//
// Created by juzenhon on 2017/9/7.
//

#ifndef TMTP_CTNBASECALLBACK_H
#define TMTP_CTNBASECALLBACK_H

#include "CTNNetWork.h"
#include "CHttpConfig.h"
#include "BizMeta.h"
#include "rapidjson/prettywriter.h"
#ifdef __linux__
#include <functional>
#endif

class BaseInputBean {

	public:
		virtual ~BaseInputBean(){};
		virtual void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) = 0;
};


typedef std::function<void(rapidjson::Value &,BaseInputBean* )> HandleResponseFun;

typedef std::function<void(int, const char *, void *)> RequestCallbackFun;

typedef std::function<void(void *)> CanceledFun;

class BizJsonRequest : public HttpRequest {

public:
    BizJsonRequest();

    BizJsonRequest(BaseInputBean *bean, HttpMethod method = Post);

    ~BizJsonRequest();

    /**
     *
     * @param responseFun 业务处理函数
     * @param callbackFun 原数据往上层回调处理
     * @param userData 自定义指针,会通过callbackFun回传给你,用来做标识
     * @param canceledFun 请求处理函数
     */
    void setCallback(HandleResponseFun responseFun, RequestCallbackFun callbackFun,void *userData,CanceledFun canceledFun = nullptr);

    const char *getPostBody(int64_t &size);

    void handResponse(HttpResponse &response);

private:
    void initCommonHeader();

private:

    HandleResponseFun _handleResponseFun;

    RequestCallbackFun _callbackFun;

    CanceledFun _cancelFun;

    void *_userData;

    BaseInputBean* _inputContext;
};

#endif //TMTP_CTNBASECALLBACK_H
