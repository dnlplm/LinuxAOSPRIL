#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <syslog.h>

#include <ril.h>
#include <log.h>
#include <ril_linux.h>

static sem_t mutex_response;
static sem_t mutex_unsolicited;

int transaction_id = 0;

static const RIL_RadioFunctions *ril_callbacks;

void OnRequestComplete(RIL_Token t, RIL_Errno e,
                       void *response, size_t responselen)
{
    int tid = *((int *)t);

    RLOGI("%s", resultToString(e));

    if (tid != 0)
        RLOGE("Unexpected transaction id\n");

    sem_post(&mutex_response);
}

void OnUnsolicitedResponse(int unsolResponse, const void *data, size_t datalen)
{
    RLOGI("%s arrived\n", requestToString(unsolResponse));

    if (unsolResponse == RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED) {
        if (ril_callbacks->onStateRequest() == RADIO_STATE_ON)
            sem_post(&mutex_unsolicited);
    }
}

void RequestTimedCallback(RIL_TimedCallback callback,
                          void *param, const struct timeval *relativeTime)
{
    RLOGI("RequestTimedCallback called\n");
    callback(NULL);
}

void OnRequestAck(RIL_Token t)
{
    RLOGI("OnRequestAck called\n");
}

static struct RIL_Env ril_env = {
    OnRequestComplete,
    OnUnsolicitedResponse,
    RequestTimedCallback,
    OnRequestAck
};

void test_request_radio_power(int radio_power)
{
    int radio_power_tmp = radio_power;

    ril_callbacks->onRequest(RIL_REQUEST_RADIO_POWER, &radio_power_tmp, sizeof(radio_power_tmp), &transaction_id);
}

int main(int argc, char **argv)
{
    int ret = EXIT_SUCCESS;

    if (sem_init(&mutex_response, 0, 0)) {
        strerror(errno);
        ret = EXIT_FAILURE;
        goto end;
    }

    if (sem_init(&mutex_unsolicited, 0, 0)) {
        strerror(errno);
        ret = EXIT_FAILURE;
        goto end;
    }

    ril_callbacks = RIL_Init(&ril_env, argc, argv);
    if (!ril_callbacks) {
        RLOGE("Failed to get ril_callbacks\n");
        ret = EXIT_FAILURE;
        goto end;
    }

    RLOGI("%s\n", ril_callbacks->getVersion());

    /* Waiting for radio to change state */
    if (sem_wait(&mutex_unsolicited)) {
        strerror(errno);
        ret = EXIT_FAILURE;
        goto end;
    }

    test_request_radio_power(1);

    if (sem_wait(&mutex_response)) {
        strerror(errno);
        ret = EXIT_FAILURE;
        goto end;
    }

end:
    return ret;
}
