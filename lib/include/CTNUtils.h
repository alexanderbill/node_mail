#ifndef __toon__utils_h
#define __toon__utils_h

#include <string>
#include "json/json.h"
#include "json/json-forwards.h"

#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"

using namespace std;

namespace toonim {

    template <class T>
    void ignore_unused(T&) {}

    class CTNStringUtils {
    public:
        static std::string safeString(const char*str) { return str != nullptr ? str : ""; }
        static std::string stringFromInt32(int32_t n);
        static std::string stringFromInt64(int64_t n);
        static std::string stringFromDouble(double n);
        static int32_t stringToInt32(string s);
        static int64_t stringToInt64(string s);
        static double stringToDouble(string s);
        static std::string getMD5String(const string s);
        static std::string getMd5String(const string s, bool isFilePath = false);
        static std::string generateEncryptKey(string s);
        static std::string getSHA256String(const unsigned char* s, int64_t length);
#ifdef _WIN32
		static int utf8ToUnicode(const char* utf8, std::wstring &unicode);
		static int unicodeToUtf8(const wchar_t* unicode, std::string &utf8);
#endif
    };

    class CTNUtils {
    public:
    
        static bool isEqualAOE(string s);
        
        /**
         * gerernate random digit, result range from 0, to max
         */
        static int getRandom(int max);
        
        /**
         * parse json using JsonCpp
         */
        static bool parseJson(const char* string, /*out*/Json::Value &value, /*out*/JSONCPP_STRING &err);
        
        /**
         * parse json using rapidjson
         */
        static bool parseRapidJson(const char *data, int len, /*out*/rapidjson::Document &doc,
                /*out*/rapidjson::Value &value, /*out*/int &errCode, /*out*/std::string &err);
        
#ifndef WIN32
        /**
         * zip compress
         */
        static bool zlibCompress(const std::string& data, std::string& result);
        
        /**
         * zip decompress
         */
        static bool zlibDecompress(const std::string& data, std::string& result);
#endif
        
        /**
         base64 encode

         @param bytes_to_encode 
         @param in_len 
         @return encode result
         */
        static std::string base64Encode(unsigned char const* bytes_to_encode, unsigned int in_len);
        
        /**
         base64解码

         @param encoded_string  
         @return 
         */
        static std::string base64Decode(std::string const& encoded_string);
        
        /**
         url encode

         @param url url
         @return url
         */
        static std::string urlEncode(const std::string& url);
        
        /**
         url decode

         @param url url
         @return url
         */
        static std::string urlDecode(const std::string& url);
        
        static std::string generateUUID();
    };
    
    class CTNTimeUtils {
    public:
        static std::string localTime();
    };
    
    class CTNPathUtils {
    public:
        static std::string getPathSeperator();
        static bool renameFile(const std::string &from, const std::string& to);
        static bool isFileExist(const std::string &path);
        static bool isDirectory(const std::string &path);
        static bool removeFile(const std::string &path);
        static long fileSize(const std::string &path);
        static bool mkdir(const std::string&path);
        static void saveTextToFile(const char* filename, const char *text);
        static void readTextFromFile(const char* filename, std::string &content);
        static bool copy(const std::string &srcFile, const std::string &dstFile);
    };

}

#endif
