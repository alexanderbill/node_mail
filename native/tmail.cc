#include <nan.h>

#include "CTNChatAPI.h"
#include "CTNDBAPI.h"
#include "CTNDBHeader.h"
#include "CTNHttpBizApi.h"
#include "CLog.h"
#include <mutex>

using namespace toonim;
using namespace std;
using namespace v8;

struct ShareData
{
    Isolate * isolate;
    Persistent<Function> js_callback;
};


static std::mutex eventSyncMutex;

class CTNImsdkCallbackImpl : public toonim::ITnImSdkCallback {

	uv_async_t uv_async;

public:
	CTNImsdkCallbackImpl(const Nan::FunctionCallbackInfo<v8::Value>& info) {
		uv_async_init(uv_default_loop(), &uv_async, node_event_process);
	}

	virtual void netStatusChanged(int32_t status) {
		TNMPLOG("netStatusChanged status:" << status);
		//TNC_CHECK_EQ(1, 1, "setCallback success");
	}

	virtual void loginResp(int32_t code, vector<int32_t>& contentTypes) {
		if (code == 0) {
			//eventSyncMutex.lock();
			uv_async.data = "loginResp";
			TNMPLOG("===============:" << uv_async.data);
			uv_async_send(&uv_async);
		}
		//TNC_CHECK_EQ(1, 1, "setCallback success");
		//TNC_CHECK_EQ(1, 1, "login success");
	}

	static void node_event_process(uv_async_t *handle){

		string p = (char*)handle->data;
		p = "tmail_callback(\"" + p + "\")";
		TNMPLOG("================" << p);
		//eventSyncMutex.unlock();

		Isolate* isolate = Isolate::GetCurrent();
		Nan::MaybeLocal<Nan::BoundScript> script =
				Nan::CompileScript(v8::String::NewFromUtf8(isolate, p.c_str()));
		Nan::RunScript(script.ToLocalChecked());
	}

	virtual void kickOut() {
		TNMPLOG("kickOut");
		//TNC_CHECK_EQ(1, 1, "setCallback success");
		//TNC_CHECK_EQ(1, 1, "login success");
	}

	virtual void hotSessionResp(set<CTNOffMessageResult> &sessionSet) {
		TNMPLOG("hotSessionResp");
	}

	virtual void offMsgResp(set<CTNOffMessageResult> &sessionSet) {
		TNMPLOG("offMsgResp sessionId:");
	}

	virtual void msgRecv(toonim::CTNMessage *message) {
		TNMPLOG("msgRecv sessionId:" << message->msgId);
	}

	virtual void syncMessage(toonim::CTNMessage *message, int32_t isOnline) {
	}

	virtual void noticeMessage(toonim::CTNMessage *message, const char* broadcast) {
		if (message == nullptr) {
			return;
		}
		TNMPLOG("noticeMessage message:" << message->genBodyJson() << " broadcast:" << broadcast);
		//TNC_CHECK_EQ(1, 1, "addNoticeFilter success");
	}

	virtual void notificationCenter(const char* broadcast, const char* userInfoJson) {
		if (broadcast == NULL || strlen(broadcast) == 0) {
			return;
		}

		TNMPLOG("broadcast:" << broadcast << " userInfoJson:" << userInfoJson);
	}

	virtual void messageOperate(toonim::CTNMessage *message, bool success) {
	}

	virtual void syncSessionStatusResp(const char* sessionId) {
		TNMPLOG("syncSessionStatusResp sessionId:" << sessionId);
	}

	virtual void syncSessionStatusReq(const char* sessionId) {
		TNMPLOG("syncSessionStatusReq sessionId:" << sessionId);
	}

	virtual void msgAck(const char* sessionId, const char* msgId, int64_t seqId, int32_t result) {
		if (sessionId == NULL || strlen(sessionId) == 0 || msgId == NULL || strlen(sessionId) == 0) {
			TNMPLOG("msgAck sessionId or msgId is empty!");
			return;
		}
		TNMPLOG("msgAck sessionId:" << sessionId << " msgId:" << msgId << " result:" << result);
	}

	virtual void userOnlineStatus(std::map<string, int32_t> &mapClientStatus) {};

	virtual void daInfo(const char* atrNamax, map<string, string> & property) {};
};

toonim::ITnImSdk *imsdk;
CTNImsdkCallbackImpl *callbackImpl;
toonim::CTNClientInfo gClientInfo;

void Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 2) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}

	if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
		Nan::ThrowTypeError("Wrong arguments");
		return;
	}

	double arg0 = info[0]->NumberValue();
	double arg1 = info[1]->NumberValue();
	v8::Local<v8::Number> num = Nan::New(arg0 + arg1);

	info.GetReturnValue().Set(num);
}

void callbackSuccess(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	info.GetReturnValue().Set(true);
}

void callbackFail(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	info.GetReturnValue().Set(false);
}

int getInt32FromInfo(v8::Local<v8::Object> jsonObj, v8::Local<v8::String> prop) {
	if (Nan::HasOwnProperty(jsonObj, prop).FromJust()) {
		v8::Local<v8::Value> fooValue = Nan::Get(jsonObj, prop).ToLocalChecked();
		return fooValue->NumberValue();
	}
	return -1;
}

string getStringFromInfo(v8::Local<v8::Object> jsonObj, v8::Local<v8::String> prop) {
    if (Nan::HasOwnProperty(jsonObj, prop).FromJust()) {
		v8::Local<v8::Value> barValue = Nan::Get(jsonObj, prop).ToLocalChecked();
		return std::string(*Nan::Utf8String(barValue->ToString()));
	}
	return "";
}

CTNClientInfo unpack_CTNClientInfo(const Nan::FunctionCallbackInfo<v8::Value>& args) {
	/*
		clientId: "sjf1ac2z3e3z@syswin.com",
		deviceId: "40-8D-5C-11-F7-A9",
		pushToken: "fjdlsajfld",
		deviceType: 3,
		keyPath: "C:\Users\Administrator\AppData\Roaming\temail\000000\tmail\",
		appPath: "D:\temail\",
		pushServiceType:1,
		apnsType: 1,
		version: "0.2.0"
    */
	CTNClientInfo info;
	v8::Local<v8::Object> jsonObj = args[0]->ToObject();

	info.apnsType = getInt32FromInfo(jsonObj, Nan::New("apnsType").ToLocalChecked());
	info.pushServiceType = getInt32FromInfo(jsonObj, Nan::New("pushServiceType").ToLocalChecked());
	info.deviceType = getInt32FromInfo(jsonObj, Nan::New("deviceType").ToLocalChecked());
	info.clientId = getStringFromInfo(jsonObj, Nan::New("clientId").ToLocalChecked());
	info.deviceId = getStringFromInfo(jsonObj, Nan::New("deviceId").ToLocalChecked());
	info.appPath = getStringFromInfo(jsonObj, Nan::New("appPath").ToLocalChecked());
	info.keyPath = getStringFromInfo(jsonObj, Nan::New("keyPath").ToLocalChecked());
	info.version = getStringFromInfo(jsonObj, Nan::New("version").ToLocalChecked());

	return info;
}

void setCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {//添加对接回调类
	if (callbackImpl == nullptr) {
		callbackImpl = new CTNImsdkCallbackImpl(info);
	}
	imsdk->setCallback(callbackImpl);
}

void initIm(const Nan::FunctionCallbackInfo<v8::Value>& info) { //初始化imsdk
	toonim::appendHttpRouter("api.groupchat.systoon.com", "http://t.email");
	toonim::appendHttpRouter("api.tcard.systoon.com", "http://t.email/card");
	//toonim::appendHttpRouter("api.im.systoon.com", "124.251.118.82:10001");
	toonim::appendHttpRouter("api.tmail.systoon.com", "http://t.email");
	toonim::appendHttpRouter("api.tpushregister.systoon.com", "http://t.email");
	toonim::appendHttpRouter("api.tpush.systoon.com", "http://t.email:11001");
	toonim::appendHttpRouter("api.tmailvframe.systoon.com", "http://tmail.systoon.com/vframeByUrl");
	toonim::appendHttpRouter("api.tmailcloud.systoon.com", "http://t.email/cloudstorage");
	gClientInfo = unpack_CTNClientInfo(info);
	std::string logPath = "D:/temail/log/";
	toonim::initLog(logPath.c_str());
	std::string dBPath = "D:/temail/DB/";
	toonim::initImDB(gClientInfo.clientId.c_str(), dBPath.c_str());
	imsdk = toonim::initIm(gClientInfo);
	imsdk->addHostInfo("124.251.118.82", 10001, false);
	setCallback(info);
	info.GetReturnValue().Set(Nan::New<String>(gClientInfo.clientId).ToLocalChecked());
}

void addNoticeFilter(const Nan::FunctionCallbackInfo<v8::Value>& info) {//添加过滤通知
	vector<int32_t> vecSubCatId;
	vecSubCatId.push_back(1);
	vecSubCatId.push_back(2);
	imsdk->addNoticeFilter(0, vecSubCatId, "BROADCAST");
}

void addHostInfo(const Nan::FunctionCallbackInfo<v8::Value>& info) {//添加服务器地址
	bool isSSL = false;
	if (!isSSL) {
		if (imsdk == nullptr) {
			TNMPLOG("addHost imsdk is null!!!!");
			return;
		}
		imsdk->addHostInfo("120.111.122.1", 8080, isSSL);
	}
}

void login(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	if (imsdk == nullptr) {
		TNMPLOG("login imsdk is null!!!!");
		return;
	}

	if (!gClientInfo.isValid()) {
		TNMPLOG("_clientInfo is invalid,don't connect:" << gClientInfo.clientId << " myfeed size:" << gClientInfo.feedList.size());
		return;
	}
	TNMPLOG("login imsdk");
	imsdk->login(gClientInfo.clientId.c_str());
	info.GetReturnValue().Set(Nan::New<String>(gClientInfo.clientId).ToLocalChecked());
}

void sendMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {//发送消息
	toonim::CTNMessage message;
	message.msgId = toonim::generateMsgId();
	//message.type = CTNIMMessageTypeChat;
	message.fromId = gClientInfo.clientId;
	//message.fromClientId = "2733405";
	v8::Local<v8::Object> jsonObj = info[0]->ToObject();
	message.toId = getStringFromInfo(jsonObj, Nan::New("toId").ToLocalChecked());
	//message.toClientId = "305092";
	message.contentType = CTNChatTypeText;

	message.content = getStringFromInfo(jsonObj, Nan::New("content").ToLocalChecked());

	if (imsdk == nullptr) {
		TNMPLOG("sendMessage imsdk is null!!!!");
		return;
	}
	imsdk->sendMessage(&message);
}

void revokeMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {//撤回消息
	string sessionId = "";
	string msgId = "";
	string operatorFeedId = "";
	string operatorName = "";
	imsdk->revokeMessage(sessionId.c_str(), msgId.c_str(), operatorFeedId.c_str(), operatorName.c_str());
}

void getNetStatus(const Nan::FunctionCallbackInfo<v8::Value>& info) {//获取网络状态
	if (imsdk == nullptr) {
		return;
	}
	int ret = imsdk->getNetStatus();
}

void logout(const Nan::FunctionCallbackInfo<v8::Value>& info) {//退出登录
	bool notifyServer = false;
	if (imsdk == nullptr) {
		TNMPLOG("logout imsdk is null!!!!");
		return;
	}
	imsdk->logout(notifyServer);
}

void Init(v8::Local<v8::Object> exports) {
	exports->Set(Nan::New("add").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(Add)->GetFunction());
	exports->Set(Nan::New("initIm").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(initIm)->GetFunction());
	exports->Set(Nan::New("setCallback").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(setCallback)->GetFunction());
	exports->Set(Nan::New("addNoticeFilter").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(addNoticeFilter)->GetFunction());
	exports->Set(Nan::New("addHostInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(addHostInfo)->GetFunction());
	exports->Set(Nan::New("login").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(login)->GetFunction());
	exports->Set(Nan::New("sendMessage").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(sendMessage)->GetFunction());
	exports->Set(Nan::New("revokeMessage").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(revokeMessage)->GetFunction());
	exports->Set(Nan::New("getNetStatus").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(getNetStatus)->GetFunction());
	exports->Set(Nan::New("logout").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(logout)->GetFunction());
}

NODE_MODULE(demo, Init)
