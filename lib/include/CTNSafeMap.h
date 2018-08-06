//
//  CTNSafeMap.hpp
//  tmailsdk
//
//  Created by lanhy on 2018/5/14.
//  Copyright © 2018年 syswin. All rights reserved.
//

#ifndef CTNSafeMap_hpp
#define CTNSafeMap_hpp

#include <map>
#include <mutex>

namespace toonim {

template <typename S, typename T>
class CSafeMap {
    std::map<S, T> m_map;
    
    //        std::condition_variable m_condition;
    std::mutex m_mutex;
public:
    inline CSafeMap() {}
    inline ~CSafeMap() {}
    
    inline T& operator [] (S s) {
        std::unique_lock<std::mutex> unilock(m_mutex);
        T& t = m_map[s];
        return t;
    }
    
    inline T operator = (T t) {
        std::unique_lock<std::mutex> unilock(m_mutex);
        T tt = t;
        return tt;
    }
    
    inline size_t size() {
        std::unique_lock<std::mutex> unilock(m_mutex);
        return m_map.size();
    }
    
    inline bool empty(){
        std::unique_lock<std::mutex> unilock(m_mutex);
        return m_map.empty();
    }
    
    inline void clear() {
        std::unique_lock<std::mutex> unilock(m_mutex);
        return m_map.clear();
    }
    
    inline void erase(typename std::map<S,T>::iterator s) {
        std::unique_lock<std::mutex> unilock(m_mutex);
        m_map.erase(s);
        //            m_condition.notify_all();
    }
    
    inline void erase(S s) {
        std::unique_lock<std::mutex> unilock(m_mutex);
        m_map.erase(s);
    }
    
    inline typename std::map<S, T>::iterator find(S s) {
        std::unique_lock<std::mutex> unilock(m_mutex);
        typename std::map<S, T>::iterator iter = m_map.find(s);
        return iter;
    }
    
    inline typename std::map<S, T>::iterator end() {
        std::unique_lock<std::mutex> unilock(m_mutex);
        typename std::map<S, T>::iterator iter = m_map.end();
        return iter;
    }
    
    inline CSafeMap<S, T>& operator= (const CSafeMap<S, T>& mp){
        std::unique_lock<std::mutex> unilock(m_mutex);
        m_map = mp.m_map;
        return *this;
    }
};
}


#endif /* CTNSafeMap_hpp */
