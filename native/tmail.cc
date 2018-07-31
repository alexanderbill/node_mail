#include <nan.h>

#include "CTNDBHeader.h"
#include "CTNChatAPI.h"
#include "CLog.h"

using namespace toonim;
using namespace std;
using namespace v8;

class CTNImsdkCallbackImpl : public toonim::ITnImSdkCallback {

	Nan::CopyablePersistentTraits<v8::Function>::CopyablePersistent _cb;

public:
	CTNImsdkCallbackImpl(const Nan::FunctionCallbackInfo<v8::Value>& info) {
		_cb = Nan::Persistent<v8::Function>(info[0].As<v8::Function>());
	}

	virtual void netStatusChanged(int32_t status) {
		TNMPLOG("netStatusChanged status:" << status);
		//TNC_CHECK_EQ(1, 1, "setCallback success");
	}

	virtual void loginResp(int32_t code, vector<int32_t>& contentTypes) {
		TNMPLOG("loginResp code:" << code);
		if (code == 0) {
		}
		//TNC_CHECK_EQ(1, 1, "setCallback success");
		//TNC_CHECK_EQ(1, 1, "login success");

		auto isolate = Isolate::GetCurrent();
		auto context = isolate->GetCurrentContext(); // crashes nwjs here
		auto global = context->Global();

		const int argc = 1;
		Handle<Value> argv[argc];
		argv[0] = Number::New(isolate, code);

		auto fn = Local<Function>::New(isolate, _cb);
		fn->Call(global, argc, argv);
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

CTNClientInfo unpack_CTNClientInfo(const Nan::FunctionCallbackInfo<v8::Value>& args) {
	/*
	clientInfo.clientId = "123456";//clientId
	clientInfo.deviceId = "456";//deviceId
	clientInfo.pushToken = "fjdlsajfld";//pushToken


	clientInfo.deviceType = 1;//iOS
	clientInfo.appPath = "/Users/ouasahikage/code/TNIMSDK/test/";
	clientInfo.pushServiceType = 1;//ios push，android

	//企业证书，还是appstore证书
	clientInfo.apnsType = 1;
	clientInfo.version = "3.7.0";

	clientInfo.feedList.push_back("123123");
	clientInfo.feedList.push_back("321321");
	clientInfo.feedList.push_back("133133");
	*/
	Isolate* isolate = args.GetIsolate();
	CTNClientInfo info;
	Handle<Object> info_obj = Handle<Object>::Cast(args[0]);
	Handle<Value> deviceType =
		info_obj->Get(String::NewFromUtf8(isolate, "deviceType"));
	Handle<Value> pushServiceType =
		info_obj->Get(String::NewFromUtf8(isolate, "pushServiceType"));
	Handle<Value> apnsType =
		info_obj->Get(String::NewFromUtf8(isolate, "apnsType"));
	info.apnsType = apnsType->Int32Value();
	info.deviceType = deviceType->Int32Value();
	info.pushServiceType = pushServiceType->Int32Value();

	/*Handle<Array> array =  Handle<Array>::Cast(
	info_obj->Get(
	String::NewFromUtf8(isolate,"samples")));

	int sample_count = array->Length();
	for ( int i = 0; i < sample_count; i++ ) {
	sample s = unpack_sample(isolate, Handle<Object>::Cast(array->Get(i)));
	info.feedList.push_back(s);
	}*/
	return info;
}

void initIm(const Nan::FunctionCallbackInfo<v8::Value>& info) { //初始化imsdk
	toonim::CTNClientInfo clientInfo = unpack_CTNClientInfo(info);
	imsdk = toonim::initIm(clientInfo);
	gClientInfo = clientInfo;
}

void setCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {//添加对接回调类
	if (callbackImpl == nullptr) {
		callbackImpl = new CTNImsdkCallbackImpl(info);
	}

	imsdk->setCallback(callbackImpl);
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

void login(const Nan::FunctionCallbackInfo<v8::Value>& info) {//登录
	gClientInfo.username = "13777777777";

	if (imsdk == nullptr) {
		TNMPLOG("login imsdk is null!!!!");
		return;
	}

	if (!gClientInfo.isValid()) {
		TNMPLOG("_clientInfo is invalid,don't connect:" << gClientInfo.clientId << " myfeed size:" << gClientInfo.feedList.size());
		return;
	}

	imsdk->login(gClientInfo.username.c_str());
}

void sendMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {//发送消息
	toonim::CTNMessage message;
	message.msgId = toonim::generateMsgId();
	//message.type = CTNIMMessageTypeChat;
	message.fromId = gClientInfo.clientId;
	//message.fromClientId = "2733405";
	message.toId = "c_305309";
	//message.toClientId = "305092";
	message.contentType = CTNChatTypeText;

	message.content = "{\"text\":\"message.from this is a test 1 \"}";

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