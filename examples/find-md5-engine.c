#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/engine.h>


int main(int argc, char** argv)
{
    ENGINE *e;
    const char *engine_id = "md5-engine";
    ENGINE_load_builtin_engines();
    e = ENGINE_by_id(engine_id);
    if (!e)
    { /* the engine isn't available */
        printf("Engine not available!\n");
        return 0;
    }
    if (!ENGINE_init(e))
    { /* the engine couldn't initialise, release 'e' */
        printf("Engine cannot be initialized!\n");
        ENGINE_free(e);
        return 0;
    }

    printf("Engine FOUND!\n");

    if (!ENGINE_set_default_digests(e))
    { /* This should only happen when 'e' can't initialise, but the previous
  * statement suggests it did. */
        abort();
    }


    return 0;
}
