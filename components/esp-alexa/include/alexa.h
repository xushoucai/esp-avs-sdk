// Copyright 2018 Espressif Systems (Shanghai) PTE LTD
// All rights reserved.

#ifndef _ALEXA_H_
#define _ALEXA_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char *auth_code;
    const char *client_id;
    const char *redirect_uri;
    const char *code_verifier;
} comp_app_config_t;

typedef struct {
    const char *client_id;
    const char *client_secret;
    const char *refresh_token;
} mfg_config_t;

typedef struct {
    const char *client_id;
    const char *refresh_token;
} subsequent_auth_config_t;

/** Auth Delegate Configuration Type
 *
 * Please refer to the documentation for \ref alexa_auth_type_t for more details.
 */
typedef enum {
    auth_type_undecided = 1,
    /** Subsequent authentication */
    auth_type_subsequent,
    /** Authentication tokens from companion app */
    auth_type_comp_app,
    /** Authentication from tokens in manufacturing partition */
    auth_type_static,
} alexa_auth_type_t;

/** Auth Delegate Configuration
 *
 * There can be multiple ways in which the auth delegate can be configured. For example:
 * - comp_app: Authentication was performed by a companion app, we need to exchange these tokens for the real access tokens.
 * - subsequent: We have the real access tokens in NVS, and we should use that for authentication. This step typically happens after the comp_app authentication has been used once.
 * - mfg: Credentials are stored in the 'mfg' partition, read it from there and use them
 */
typedef struct {
    alexa_auth_type_t type;
    union {
        comp_app_config_t comp_app;
        mfg_config_t mfg;
        subsequent_auth_config_t subsequent;
    } u;
} auth_delegate_config_t;

/** Configuration for playback stream
 *  To be set by the application
 *  If the application does not set these values, then the default values are taken
 */
typedef struct {
    size_t stack_size;  //Default task stack size is 5000
    int task_priority;  //Default priority is 5
    size_t buf_size;    //Default buffer size is 512 bytes
} alexa_playback_config_t;

/** The Alexa Configuration Structure
 */
typedef struct {
    /** Configuration for the Auth Delegate */
    auth_delegate_config_t auth_delegate;
    alexa_playback_config_t alexa_playback;
} alexa_config_t;

/** Initialize Alexa
 *
 * This call must be made after the Wi-Fi connection has been established with the configured Access Point.
 *
 * \param[in] cfg The Alexa Configuration
 *
 * \return
 *    - 0 on Success
 *    - an error code otherwise
 */
int alexa_init(alexa_config_t *cfg);

/** Get current Alexa SDK version
 *
 * \return Pointer to version string
 */
const char *alexa_get_sdk_version();

#ifdef __cplusplus
}
#endif

#endif /*_ALEXA_H_ */
