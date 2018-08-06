#ifndef __toon__CTNERROR_H
#define __toon__CTNERROR_H

#include <string>

namespace toon {
    
    enum CTNErrorCode {
        // TODO:
        CTN_ERROR_NO_ERROR = 0,
        CTN_ERROR_NETWORK_CATALOG,
        CTN_ERROR_NO_REGISTER_CATALOG,
        CTN_ERROR_NO_LOGIN_CATALOG,
        CTN_ERROR_NO_HTTP_CATALOG,
    };

    class CTNError {
    public:
        CTNError() { mErrorCode = CTN_ERROR_NO_ERROR; mDescription = ""; }
        CTNError(int code, const std::string& str) { mErrorCode = code; mDescription = str; }
        int getCode() const { return mErrorCode; }
        std::string getDescription() const { return mDescription; }
        
    private:
        int mErrorCode;
        std::string mDescription;
        
    };
    
}

#endif
