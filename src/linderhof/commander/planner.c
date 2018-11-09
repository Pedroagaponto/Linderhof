#include "venus.h"
#include "commander/planner.h"
#include "hom/memcached.h"
#include "hom/mirrortest.h"

LhfPlan * Planner( LhfDraft *p_draft )
{
    LhfPlan *plan = NULL;

    memalloc(&plan, sizeof(LhfPlan));
    memalloc(&(plan->atkData), sizeof(LhfDraft));

    switch (p_draft->type)
    {
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
      case TEST:
      default:
        plan->type = TEST;
        memcpy( plan->atkData, p_draft, sizeof(LhfDraft));
        plan->atk_cmd = ExecuteTestMirror;
        break;
    }

    return plan;
}
