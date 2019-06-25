/*
 *  strix_defines.h
 *    
 */

#ifndef STRIX_DEFINES_H
#define STRIX_DEFINES_H

#include "venus.h"

//#define COAP_DEFAULT_PORT 10000
#define COAP_DEFAULT_PORT 5683
#define THROUGHPUT_DEFAULT 0

#define COAP_DRAFT_ERROR -10

typedef enum { STAT, GETSET } CoapAtk;

typedef struct {
    Packet * getPacket;
    LhfDraft *draft;
}AttackPlan;

#endif
