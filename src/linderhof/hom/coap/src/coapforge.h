
/*
 *  packetforge.h
 *          
 */

#ifndef PACKETFURNACE_H
  #define PACKETFURNACE_H

#include "common/netio.h"

/* Standard well-defined IP protocols.  
 *        netinet/in.h
 
 Protocols RFC 790
 
IPPROTO_IP		    0		dummy for IP
IPPROTO_ICMP		1	    control message protocol 
IPPROTO_GGP		    3		gateway^2 (deprecated) 
IPPROTO_TCP		    6		tcp 
IPPROTO_EGP		    8		exterior gateway protocol 
IPPROTO_PUP		    12		pup 
IPPROTO_UDP		    17		user datagram protocol 
IPPROTO_IDP		    22		xns idp 
IPPROTO_TP		    29 		tp-4 w/ class negotiation 
IPPROTO_EON		    80		ISO cnlp 

IPPROTO_RAW		    255		raw IP packet 
IPPROTO_MAX		    256
*/
//Binary protocol
typedef struct __attribute__((__packed__)) {
    u_int8_t tk_len:4, type:2, version:2; //little endian
    u_int8_t code;
    u_int16_t message_id;
//    u_int16_t token; // tk_len = 0
}BinaryRequestHeader;

typedef struct __attribute__((__packed__)){
    u_int8_t len:4, delta:4;
} CoapOption;


#define CON     0
#define NO_CON  1
#define ACK     2
#define RST     3
#define GET     1
#define URIPATH 11
#define URIPATHCONT 0
#define BLOCK2 12
#define BLOCK1024 6
#define BLOCK2SIZE 2

#define COAP_GET     200


/**
   VALUE OF -CODE- FIELD

   [0]   = "Empty",
   [1]   = "GET",
   [2]   = "POST",
   [3]   = "PUT",
   [4]   = "DELETE",
   [65]  = "2.01 Created",
   [66]  = "2.02 Deleted",
   [67]  = "2.03 Valid",
   [68]  = "2.04 Changed",
   [69]  = "2.05 Content",
   [128] = "4.00 Bad Request",
   [129] = "4.01 Unauthorized",
   [130] = "4.02 Bad Option",
   [131] = "4.03 Forbidden",
   [132] = "4.04 Not Found",
   [133] = "4.05 Method Not Allowed",
   [134] = "4.06 Not Acceptable",
   [140] = "4.12 Precondition Failed",
   [141] = "4.13 Request Entity Too Large",
   [143] = "4.15 Unsupported Content-Format",
   [160] = "5.00 Internal Server Error",
   [161] = "5.01 Not Implemented",
   [162] = "5.02 Bad Gateway",
   [163] = "5.03 Service Unavailable",
   [164] = "5.04 Gateway Timeout",
   [165] = "5.05 Proxying Not Supported"
**/


Packet * ForgeCoap( void *p_arg );

#endif
