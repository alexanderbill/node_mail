//
//  CTNPacket_hpp
//  TNMP
//
//  Created by 兰怀玉 on 16/4/13.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef CTNPacket_hpp
#define CTNPacket_hpp

#include <stdio.h>
#include "cdtp.h"

#ifdef _WIN32

#include <Winsock2.h>
typedef __int32 int32;
typedef uint32_t uint32;
typedef __int16 int16;

#else

#include <sys/types.h>

typedef __int32_t int32;
typedef __int16_t int16;
typedef __uint32_t uint32;


#endif

#define NEW_PACKET(len) ((TNPacketBuffer *)new char[len])

#define DELETE_PACKET(p) if (p != NULL) {delete [] (char*)p; p = NULL;}


const size_t TMTP_HLEN = 8;//header length

//消息头标记定义
struct TNPacket{
    int16_t type;
    int64_t param;
    int16_t command;
    bool needDatagram;
    Toon::Datagram datagram;

    TNPacket(){
        type  = 0;
        param = 0;
        command = 0;
        needDatagram = true;
    }
    
};



#endif /* CTNPacketBase_hpp */
