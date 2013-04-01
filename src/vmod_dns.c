#include <stdlib.h>

#include <arpa/inet.h>
#include <netdb.h>

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"

#ifndef   NI_MAXHOST
#define   NI_MAXHOST 1025
#endif

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf) {
	return (0);
}

const char *
vmod_hello(struct sess *sp, const char *name) {
	char *p;
	unsigned u, v;

	u = WS_Reserve(sp->wrk->ws, 0); /* Reserve some work space */
	p = sp->wrk->ws->f;		/* Front of workspace area */
	v = snprintf(p, u, "Hello, %s", name);
	v++;
	if (v > u) {
		/* No space, reset and leave */
		WS_Release(sp->wrk->ws, 0);
		return (NULL);
	}
	/* Update work space with what we've used */
	WS_Release(sp->wrk->ws, v);
	return (p);
}

/*const char *
vmod_resolve(struct sess *sp, const char *str) {

}*/

const char *
vmod_rresolve(struct sess *sp, const char *str) {
    /* do lookup */
    struct sockaddr_in sa;

    sa.sin_family = AF_INET;
    inet_pton(AF_INET, str, &sa.sin_addr);

    char node[NI_MAXHOST];
    int res = getnameinfo((struct sockaddr*) &sa, sizeof(sa), node, sizeof(node), NULL, 0, 0);
    if (res != 0) {
        /* encountered an error, return empty string */
        return "";
    }
    /*#printf("%s", node);*/
}
