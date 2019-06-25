#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "strix.h"
#include "coapforge.h"


Packet * ForgeCoap( void *p_arg )
{
    //int *opcode = (int *)p_arg;
    Packet *pac = NULL;
    char * mem_packet;
    BinaryRequestHeader * mem_header = NULL;
    char path[] = "time";

    int packetSize = sizeof( BinaryRequestHeader ) + strlen(path);
    
    memalloc( (void *)&pac, sizeof(Packet) );

    memalloc( (void *)&mem_packet, packetSize );

    mem_header = ( BinaryRequestHeader *) mem_packet;

    mem_header->version = 1;
    mem_header->type = CON;
    mem_header->tk_len = 4;
    mem_header->code = GET;
    mem_header->message_id = 0xcdab;
    mem_header->token = 0xdeadbeef;
    mem_header->opt_delta = 11; //uri-path
    mem_header->opt_len = strlen(path);
    memcpy(mem_packet + sizeof(BinaryRequestHeader), path, strlen(path));


    pac->packet_ptr = mem_packet;
    pac->pkt_size = packetSize;

    return pac;
}
