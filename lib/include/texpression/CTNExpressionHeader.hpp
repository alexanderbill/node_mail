//
//  CTNExpressionHeader.hpp
//  texpression
//
//  Created by 王海涛 on 2018/7/3.
//  Copyright © 2018年 思源科技. All rights reserved.
//

#ifndef CTNExpressionHeader_hpp
#define CTNExpressionHeader_hpp

#include <stdio.h>
#include <string>

using namespace std;

namespace toonexpression {
    
    struct CTNExpressionDetail
    {
    public:
        CTNExpressionDetail(){}
        bool isValid() {
            if (faceBagId == 0) {
                return false;
            }
            return true;
        }
        
        void parse(void *dataValue);
        
    public:
        std::string dynamicFileName;
        std::string dynamicPicUrl;
        int32_t faceBagId;
        int32_t faceId;
        std::string faceName;
        int32_t sequence;
        std::string staticFileName;
        std::string staticPicUrl;
    };
    
    struct CTNExpressionModel
    {
    public:
        CTNExpressionModel(){
            faceBagId = 0;
            orderBy = 0;
            status = 0;
            isDownload = 2;
            recommend = 0;
        }
        bool isValid() {
            if (faceBagId == 0) {
                return false;
            }
            return true;
        }
        
        void parse(void *dataValue);
        
    public:
        
        int32_t faceBagId;
        std::string name;       //facebag name
        std::string slogan;
        std::string intro;
        int32_t orderBy;
        std::string picUrl;     //pic url
        int32_t status;         //whether has been pulled off shelf
        int32_t isDownload;     //whether has downlaod, 1 yes, 2 no
        std::string zipUrl;     //download zipurl
        int32_t recommend;      //recommend status 0 no, 1 yes
        std::string zipId;
    };
}


#endif /* CTNExpressionHeader_hpp */
