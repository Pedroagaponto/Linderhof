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
    //char path[] = ".well-known/core";
    char path[] = "l";
    

    int packetSize = sizeof( BinaryRequestHeader ) + strlen(path) + BLOCK2SIZE;
    
    memalloc( (void *)&pac, sizeof(Packet) );

    memalloc( (void *)&mem_packet, packetSize );

    mem_header = ( BinaryRequestHeader *) mem_packet;

    mem_header->version = 1;
    mem_header->type = CON;
    mem_header->tk_len = 0;
    mem_header->code = GET;
    mem_header->message_id = 0xadde;
    //mem_header->token = 0xefbe;
    int pac_written = sizeof(BinaryRequestHeader);

    CoapOption opt;
    opt.delta = URIPATH;
    char *spath = strtok(path, "/");
    while (spath) {
        opt.len = strlen(spath);
        memcpy(mem_packet + pac_written, &opt, sizeof(CoapOption));
        pac_written += sizeof(CoapOption);

        memcpy(mem_packet + pac_written, spath, opt.len);
        pac_written += opt.len;

        opt.delta = URIPATHCONT;
        spath = strtok(NULL, "/");
    }

    opt.delta = BLOCK2;
    opt.len = 1;
    memcpy(mem_packet + pac_written, &opt, sizeof(CoapOption));
    pac_written += sizeof(CoapOption);
    mem_packet[pac_written++] = BLOCK1024;


    pac->packet_ptr = mem_packet;
    pac->pkt_size = pac_written;

    return pac;
}
