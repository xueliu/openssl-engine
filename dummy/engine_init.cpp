
#include <iostream>

#include <openssl/crypto.h>
#include <openssl/engine.h>
#include <openssl/ossl_typ.h>

#include <string.h>

/**
 * @brief engine_stsafe_id
 */
static const char *engine_dummy_id = "dummy";

/**
 * @brief engine_stsafe_name
 */
static const char *engine_dummy_name = "dummy engine for OpenSSL";


#ifdef __cplusplus
extern "C"
{
#endif


/** OpenSSL's method to bind an engine.
 *
 * Initializes the name, id and function pointers of the engine.
 * @brief bind_helper
 * @param e The STSAFE engine to initialize
 * @param id The identifier of the engine
 * @retval 0 if binding failed
 * @retval 1 on success
 */
static int
bind_helper(ENGINE * e, const char *id)
{
    int ret = 0;

    fprintf(stdout, "ENGINE> %s: Engine id = %s\n", __func__, id);
    if (id && (strcmp(id, engine_dummy_id) != 0)) { // not safe ?
        fprintf(stderr, "ENGINE> %s: Engine id lookup failed\n", __func__);
        goto end;
    }

    if (!ENGINE_set_id(e, engine_dummy_id)) {
        fprintf(stderr, "ENGINE> %s: ENGINE_set_id failed\n", __func__);
        goto end;
    }
    fprintf(stdout, "ENGINE> %s: ENGINE_set_id completed\n", __func__);

    if (!ENGINE_set_name(e, engine_dummy_name)) {
        fprintf(stderr, "ENGINE> %s: ENGINE_set_name failed\n", __func__);
        goto end;
    }
    fprintf(stdout, "ENGINE> %s: ENGINE_set_name completed\n", __func__);

    ret = 1;
end:
    return ret;
}
IMPLEMENT_DYNAMIC_CHECK_FN();
IMPLEMENT_DYNAMIC_BIND_FN(bind_helper);

static ENGINE* ENGINE_dummy(void)
{
    fprintf(stdout, "ENGINE> %s:\n", __func__);
    ENGINE *eng = ENGINE_new();

    if (!eng) {
        return NULL;
    }
    fprintf(stdout, "Before calling bind_helper.");
    if (!bind_helper(eng, engine_dummy_id)) {

        fprintf(stdout, "After failed calling bind_helper.");

        ENGINE_free(eng);
        return NULL;
    }

    fprintf(stdout, "After calling bind_helper.");

    return eng;
}

void ENGINE_load_dummy(void)
{
    fprintf(stdout, "ENGINE> %s:\n", __func__);
    ENGINE *toadd = ENGINE_dummy();
    if (!toadd) {
        fprintf(stderr, "DUMMY> %s: Engine failed to load\n", __func__);
        return;
    }
    ENGINE_add(toadd);
    ENGINE_free(toadd);
    ERR_clear_error();
}

#ifdef __cplusplus
}
#endif
