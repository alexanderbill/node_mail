#ifndef __RES_STRINGS_H_
#define __RES_STRINGS_H_
#include <string>

namespace toonim {
	class Res {
	public:
		static const char* RES_STRING_VOICE;
		static const char* RES_STRING_PICTURE;
		static const char* RES_STRING_LOCATION;
		static const char* RES_STRING_COLLECTION;
		static const char* RES_STRING_VIDEO;
		static const char* RES_STRING_SHARE;
		static const char* RES_STRING_NOTIFICATION;
		static const char* RES_STRING_MAIL;
		static const char* RES_STRING_UNKNWON_MESSAGE;
		static const char* RES_STRING_CARD;
		static const char* RES_STRING_GROUP;
		static const char* RES_STRING_EMOJI;
		static const char* RES_STRING_FILE;
		static const char* RES_STRING_RED_PACKET;
		static const char* RES_STRING_RECOMMEND;

		static const char *RES_STRING_SSL_ENCRYPT;
		static const char *RES_STRING_NO_ENCRYPT;

		static const char* RES_STRING_YOU_REVOKE_MESSAGE;
		static const char* RES_STRING_REVOKE_MESSAGE;
		static const char* RES_STRING_PEER_REVOKE_MESSAGE;

		static std::string getResString(const std::string& key);


	};
}

#endif

