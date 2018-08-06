//
//  CTNExpressionAPI.hpp
//  texpression
//
//  Created by 王海涛 on 2018/7/3.
//  Copyright © 2018年 思源科技. All rights reserved.
//

#ifndef CTNExpressionAPI_hpp
#define CTNExpressionAPI_hpp

#include <stdio.h>
#include <functional>
#include "CTNExpressionHeader.hpp"
#include <vector>

namespace toonexpression {
    class ITnImExpressionDB
    {
    public:
        ITnImExpressionDB(){};
        
        virtual void addExpression(toonexpression::CTNExpressionModel &expression) = 0;
        virtual void addExpressionList(const std::vector<toonexpression::CTNExpressionModel> &expressionList) = 0;
        virtual void updateExpressionStatus(int32_t faceBagId,int32_t status) = 0;
        virtual void updateExpressionDownloadStatus(int32_t faceBagId,int32_t isDownload) = 0;
        virtual void insertOrReplaceExpressionList(std::vector<CTNExpressionModel> &list) = 0;
        virtual void getExpressionShopList(std::vector<toonexpression::CTNExpressionModel> &expressionList) = 0;
        virtual void deleteExpression(int32_t faceBagId) = 0;
        
        /**
         get recommend list

         @param expressionList list
         */
        virtual void getRecommendExpressionList(std::vector<toonexpression::CTNExpressionModel> &expressionList) = 0;
        
        /**
         add my expression

         @param expression CTNExpressionModel
         */
        virtual void addMyExpression(toonexpression::CTNExpressionModel &expression) = 0;
        
        /**
         add my expression list

         @param expressionList list
         */
        virtual void addMyExpressionList(const std::vector<toonexpression::CTNExpressionModel> &expressionList) = 0;
        
        /**
         update my expressin

         @param expression CTNExpression
         */
        virtual void updateMyExpression(toonexpression::CTNExpressionModel &expression) = 0;
        
        /**
         update my expression list

         @param expresspionList list
         */
        virtual void updateMyExpressionList(const std::vector<toonexpression::CTNExpressionModel> &expressionList) = 0;
        
        /**
         update my orderby

         @param expressionList CTNExpressionModel
         */
        virtual void updateOrderby(const std::vector<toonexpression::CTNExpressionModel> &expressionList) = 0;
        
        /**
         delete my expression

         @param faceBagId faceBagId
         */
        virtual void deleteMyExpression(int32_t faceBagId) = 0;
        
        /**
         get my expressionlist

         @param expressionList list
         */
        virtual void getMyExpressionList(std::vector<toonexpression::CTNExpressionModel> &expressionList) = 0;
        
        /**
         get my expression model

         @param faceBagId faceBagId
         @param expression expression
         */
        virtual void getMyExpression(int32_t faceBagId, CTNExpressionModel &expression) = 0;
        
        /**
         get max orderby

         @return orderby
         */
        virtual int32_t getMaxOrderby() = 0;
        
        /**
         add detail

         @param expressionDetail CTNExpressionDetail
         */
        virtual void addExpressionDetail(toonexpression::CTNExpressionDetail &expressionDetail) = 0;
        
        /**
         add detail list

         @param detailList detailList
         */
        virtual void addExpressionDetailList(const std::vector<toonexpression::CTNExpressionDetail> &detailList) = 0;
        
        /**
         update detail

         @param expressionDetail CTNExpressionDetail
         */
        virtual void updateExpressionDetail(toonexpression::CTNExpressionDetail &expressionDetail) = 0;
        
        /**
         delete expressionDetail

         @param faceBagId faceBagId
         */
        virtual void deleteExpressionDetail(int32_t faceBagId) = 0;
        
        /**
         get detail list

         @param faceBagId faceBagId
         @param detailList detailList
         */
        virtual void getExpressionDetailList(int32_t faceBagId, std::vector<toonexpression::CTNExpressionDetail> &detailList) = 0;
                
        /**
         set version

         @param key key
         @param version version
         */
        virtual void replaceExpressionVersion(const char* key, int64_t version) = 0;
        
        /**
         get version

         @param key key
         @return version
         */
        virtual int64_t getExpressionVersion(const char* key) = 0;
        
    };
    
    typedef std::function<void(int flag, const char* response, void *userData)> httpCallback;
    typedef std::function<void(int persent, const char* identifier)> httpProgress;
    
    class ITnImExpressionReq
    {
    public:
        ITnImExpressionReq(){};
        
        /**
         query expressionShop

         @param fetchBegin fetch begin
         @param fetchNum fetch number
         @param response response
         @param userData userData
         */
        virtual void queryFacebagList(int32_t fetchBegin, int32_t fetchNum, httpCallback response, void *userData) = 0;
        
        /**
         query facebag detail

         @param faceBagId faceBagId
         @param response response
         @param userData userData
         */
        virtual void queryFacebagDetail(int32_t faceBagId, httpCallback response, void *userData) = 0;
        
        /**
         query my facebag list

         @param response response
         @param userData userData
         */
        virtual void queryMyFacebagList(httpCallback response, void *userData) = 0;
        
        /**
         query recommend list

         @param response response
         @param userData userData
         */
        virtual void queryRecommendList(httpCallback response, void *userData) = 0;
        
        /**
         remove facebag

         @param faceBagId faceBagId
         @param response response
         @param userData userData
         */
        virtual void removeMyFacebag(int32_t faceBagId, httpCallback response, void *userData) = 0;
        
        /**
         sort my facebag list

         @param facebagList facebagList
         @param response response
         @param userData userData
         */
        virtual void sortMyFacebag(std::vector<toonexpression::CTNExpressionModel> &facebagList, httpCallback response, void *userData) = 0;
        
        /**
         download facebag

         @param faceBagId faceBagId
         @param response response
         @param userData userData
         */
        virtual void downloadFaceBag(int32_t faceBagId, httpCallback response, void *userData) = 0;;
        
    };
    
    void initExpressionDB(const char* clientId, const char* path);
    void initExpressionReq(const char* clientId, const char* token, const char* deviceId,int32_t toonType,const char* version, const char* platformVersion,const char* cerPath);
    void appendHttpDmain(const char* domain, const char* url);
    
    void closeDB();
    
    ITnImExpressionDB* getExpressionDB();
    ITnImExpressionReq* getExpressionReq();
}


#endif /* CTNExpressionAPI_hpp */
