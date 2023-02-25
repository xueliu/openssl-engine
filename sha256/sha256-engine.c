#include "openssl/engine.h"
#include "openssl/evp.h"


//#define SHA256_DIGEST_LENGTH    (32U)
#define SHA256_CBLCOK           (64U)

static const char *engine_id = "SHA256";
static const char *engine_name = "A simple sha256 engine for demonstration purposes";

static const int supported_digests[] = {NID_sha256, 0};

static EVP_MD *sha256_digest = NULL;

static int sha256_init(EVP_MD_CTX *ctx) {
    return SHA256_Init( (SHA256_CTX * ) EVP_MD_CTX_md_data(ctx));
}

static int sha256_update(EVP_MD_CTX *ctx, const void *data, size_t count) {

    return SHA256_Update( (SHA256_CTX * )EVP_MD_CTX_md_data(ctx), data, count);
}

static int sha256_final(EVP_MD_CTX *ctx, unsigned char *md) {
    return SHA256_Final(md, (SHA256_CTX*)EVP_MD_CTX_md_data(ctx));
}

int get_digest_info(ENGINE *e, const EVP_MD **digest, const int **nids, int nid) {
    if (nids == NULL) {
        if (nid != NID_sha256) {
            return -1;
        }
        if (sha256_digest == NULL) {
            EVP_MD *md;
            md = EVP_MD_meth_new(NID_sha256, NID_sha1WithRSAEncryption);
            EVP_MD_meth_set_result_size(md, SHA256_DIGEST_LENGTH);
            EVP_MD_meth_set_input_blocksize(md, SHA256_CBLCOK);
            EVP_MD_meth_set_app_datasize(md, sizeof(EVP_MD*) + sizeof(SHA256_CTX)  );
            EVP_MD_meth_set_flags(md, 0);
            EVP_MD_meth_set_init(md, sha256_init);
            EVP_MD_meth_set_update(md, sha256_update);
            EVP_MD_meth_set_final(md, sha256_final);
            sha256_digest = md;
        }
        *digest = sha256_digest;
        return 1;
    } else {
        *nids = supported_digests;
        return 1;
    }
}

static int engine_destroy(ENGINE *e) {
    EVP_MD_meth_free(sha256_digest);
    sha256_digest = NULL;
    return 1;
}

static int engine_init(ENGINE *e) {
    return 1;
}


static int engine_finish(ENGINE *e) {
    return 1;
}

static int bind(ENGINE *e, const char *id) {
    int ret = 0;

    if (!ENGINE_set_id(e, engine_id)) {
        fprintf(stderr, "ENGINE_set_id failed\n");
        goto end;
    }
    if (!ENGINE_set_name(e, engine_name)) {
        fprintf(stderr, "ENGINE_set_name failed\n");
        goto end;
    }

    if (!ENGINE_register_digests(e)) {
        fprintf(stderr, "ENGINE_register_digests failed\n");
        goto end;
    }

    if (!ENGINE_set_digests(e, get_digest_info)) {
        fprintf(stderr, "ENGINE_set_digests failed\n");
        goto end;
    }

    if (!ENGINE_set_destroy_function(e, engine_destroy)) {
        fprintf(stderr, "ENGINE_set_destroy_function failed\n");
        goto end;
    }

    if (!ENGINE_set_init_function(e, engine_init)) {
        fprintf(stderr, "ENGINE_set_init_function failed\n");
        goto end;
    }

    if (!ENGINE_set_finish_function(e, engine_finish)) {
        fprintf(stderr, "ENGINE_set_finish_function failed\n");
        goto end;
    }

    ret = 1;
    end:
    return ret;
}

IMPLEMENT_DYNAMIC_BIND_FN(bind)
IMPLEMENT_DYNAMIC_CHECK_FN()
