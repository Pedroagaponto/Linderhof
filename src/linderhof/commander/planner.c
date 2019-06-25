#include "venus.h"
#include "commander/planner.h"
#include "hom/coap.h"
#include "hom/memcached.h"
#include "hom/ssdp.h"
#include "hom/dns.h"
#include "hom/ntp.h"

LhfPlan * Planner( LhfDraft *p_draft )
{
    LhfPlan *plan = NULL;

    memalloc(&plan, sizeof(LhfPlan));
    memalloc(&(plan->atkData), sizeof(LhfDraft));

    switch (p_draft->type)
    {
        case COAP:
            plan->type = COAP;
            memcpy( plan->atkData, p_draft, sizeof(LhfDraft));
            plan->atk_cmd = ExecuteCoapMirror;
            break;
        case MEMCACHED_GETSET:
            plan->type = MEMCACHED_GETSET;
            memcpy( plan->atkData, p_draft, sizeof(LhfDraft));
            plan->atk_cmd = ExecuteMemcachedMirror;
            break;
        case MEMCACHED_STATS:
            plan->type = MEMCACHED_STATS;
            memcpy( plan->atkData, p_draft, sizeof(LhfDraft));
            plan->atk_cmd = ExecuteMemcachedMirror;
            break;
        case NTP:
            plan->type = NTP;
            memcpy( plan->atkData, p_draft, sizeof(LhfDraft));
            plan->atk_cmd = ExecuteNtpMirror;
            break;                
        case SSDP:
            plan->type = SSDP;
            memcpy( plan->atkData, p_draft, sizeof(LhfDraft));
            plan->atk_cmd = ExecuteSsdpMirror;
            break;

        //Colocar em ordem alfabética ao implementar            
        case DNS:
        default:
            Efatal(ERROR_PLANNER, "Mirror not implemented\n");
    }

    return plan;
}
