#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include "venus.h"
#include "netuno/injector.h"
#include "netuno/logger.h"
#include "common/pthreadHelper.h"

#define THPINCREMENT 1

#define SAMPLING 10
#define DEFAULT_SIZE 1

static void *_injectorHandler( void *p_arg )
{
    Injector *injector = (Injector *)p_arg;

    printf("th %lu, ip: %s\n", injector->id, injector->net.pkt->ip_dest );
    while(1)
    {
        while( injector->net.bucketSize || injector->net.freeBucket )
        {
            printf("send %lu, ip: %s\n", injector->id, injector->net.pkt->ip_dest );
            if( ERROR_NET != SendPacket(injector->net.socket, injector->net.pkt) )
            {
                //Packet was sent
                injector->net.pktCounter++;
                injector->net.bucketSize--;
            }
            else
            {
                injector->net.pktDroped++;
            }
        }
    };
    return NULL; //Keep compiler quiet
}

void injectorBootstrap( Injector *injector )
{
    if( ERROR_THREAD == (injector->id = CreateThread(LVL_HIGH, _injectorHandler, injector)) )
    {
        Efatal( ERROR_INJECTOR, "Cannot create thread: ERROR_INJECTOR\n");
    }

}

Injector ** StartInjector( Packet *p_pkt )
{
    Injector **injector = NULL;
    int n = 1;

    //FILE *listReflect = fopen("refletors.csv", "r");
    #define NN 3
    //struct sockaddr_in saddr[MAXINJECTORS];
    char addrs[NN][16] = {"192.168.0.64", "192.168.0.63", "192.168.0.61"};
    // char addrs[3][16] = {"192.168.0.63", "192.168.0.63", "192.168.0.63"};
    void *pack_rot[NN] = {0};

    memalloc(&injector, sizeof(Injector *)*MAXINJECTORS);


    for(int i = 0; i < MAXINJECTORS; i++)
    {
        Injector *inj = NULL;
        Packet *pkt_fan_out = NULL;

        memalloc(&inj, sizeof(Injector));
        
        memalloc(&pkt_fan_out, sizeof(Packet));
        memcpy(pkt_fan_out, p_pkt, sizeof(Packet));
        memcpy(pkt_fan_out->ip_dest, addrs[i%NN], 16);
        pkt_fan_out->saddr.sin_addr.s_addr = inet_addr(addrs[i%NN]);
        if(pack_rot[i%NN] == 0){
            memalloc(&pack_rot[i%NN], pkt_fan_out->pkt_size);
            memcpy(pack_rot[i%NN], (pkt_fan_out->packet_ptr), pkt_fan_out->pkt_size);

        }
        pkt_fan_out->packet_ptr = pack_rot[i%NN];


        struct ip *ip_header = (struct ip *)(pkt_fan_out->packet_ptr);
        inet_pton(AF_INET, addrs[i%NN], (struct in_addr *)&ip_header->ip_dst);

        inj->net.pkt = pkt_fan_out;


        inj->net.socket = CreateSocket( RAW, BLOCK );
        SetSocketFlag(inj->net.socket, SO_BROADCAST);
        SetSocketFlag(inj->net.socket, SO_PRIORITY); 
        Setup_sendbuffer( inj->net.socket, n );
        
        inj->net.freeBucket = false;
        inj->net.bucketSize = 0;
        inj->net.pktCounter = 0;
        inj->net.pktDroped = 0;

        injectorBootstrap(inj);
        injector[i] = inj;
    }
    return injector;
}

void InjectorDestroy( Injector *p_injector )
{
    pthread_cancel(p_injector->id);
    memfree(&p_injector);
}
