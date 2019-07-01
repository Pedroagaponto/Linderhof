
#ifndef INJECTOR_H
  #define INJECTOR_H

#include <pthread.h>
#include <semaphore.h>
#include "common/common.h"
#include "netuno/netuno.h"

#define MAXINJECTORS 10

typedef struct {
    Packet *pkt;
    int socket;
    bool freeBucket;
    unsigned int bucketMax;
    unsigned int bucketSize;
    unsigned int pktCounter;
    unsigned int pktDroped;
    sem_t sem;
}InjectorNet;

typedef struct {
    pthread_t id;
    InjectorNet net;
}Injector;

/**
 * @brief Start injector.
 *
 * @param p_pkt[in] Packet data.
 * @return Injectors handler struct 
 */
Injector ** StartInjector( Packet *p_pkt, unsigned bucketMax );

/**
 * @brief Destroy injector.
 *
 * @param p_injector[in] Packet data to destroy.
 */
void InjectorDestroy( Injector *p_injector );

#endif          /*INJECTOR_H*/
