#include <stdlib.h>
#include "net.h"
#include "maps.h"	// page_rand
#include "compat.h"
#include "trinity.h"	// ARRAY_SIZE

#define SOL_SCTP 132

#define NR_SOL_SCTP_OPTS ARRAY_SIZE(sctp_opts)
static const int sctp_opts[] = {
	SCTP_RTOINFO, SCTP_ASSOCINFO, SCTP_INITMSG, SCTP_NODELAY,
	SCTP_AUTOCLOSE, SCTP_SET_PEER_PRIMARY_ADDR, SCTP_PRIMARY_ADDR, SCTP_ADAPTATION_LAYER,
	SCTP_DISABLE_FRAGMENTS, SCTP_PEER_ADDR_PARAMS, SCTP_DEFAULT_SEND_PARAM, SCTP_EVENTS,
	SCTP_I_WANT_MAPPED_V4_ADDR, SCTP_MAXSEG, SCTP_STATUS, SCTP_GET_PEER_ADDR_INFO,
	SCTP_DELAYED_ACK_TIME, SCTP_CONTEXT, SCTP_FRAGMENT_INTERLEAVE, SCTP_PARTIAL_DELIVERY_POINT,
	SCTP_MAX_BURST, SCTP_AUTH_CHUNK, SCTP_HMAC_IDENT, SCTP_AUTH_KEY,
	SCTP_AUTH_ACTIVE_KEY, SCTP_AUTH_DELETE_KEY, SCTP_PEER_AUTH_CHUNKS, SCTP_LOCAL_AUTH_CHUNKS,
	SCTP_GET_ASSOC_NUMBER, SCTP_GET_ASSOC_ID_LIST, SCTP_AUTO_ASCONF, SCTP_PEER_ADDR_THLDS,
	SCTP_SOCKOPT_BINDX_ADD, SCTP_SOCKOPT_BINDX_REM, SCTP_SOCKOPT_PEELOFF, SCTP_SOCKOPT_CONNECTX_OLD,
	SCTP_GET_PEER_ADDRS, SCTP_GET_LOCAL_ADDRS, SCTP_SOCKOPT_CONNECTX, SCTP_SOCKOPT_CONNECTX3,
	SCTP_GET_ASSOC_STATS };

void sctp_setsockopt(struct sockopt *so)
{
	unsigned char val;

	so->level = SOL_SCTP;

	val = rand() % NR_SOL_SCTP_OPTS;
	so->optname = sctp_opts[val];
}
