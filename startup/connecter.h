#ifndef CONNECTER
#define CONNECTER
#include <stdio.h>
#include <string.h>
#include "ohos_init.h"
#include "cmsis_os2.h"

#include "sta.h"

static void WifiConnectTask(void *arg)
{
    (void)arg;

    osDelay(10);

    // setup your AP params
    WifiDeviceConfig apConfig = {0};
    strcpy(apConfig.ssid, "9x");
    strcpy(apConfig.preSharedKey, "12345678");
    apConfig.securityType = WIFI_SEC_TYPE_PSK;

    int netId = ConnectToHotspot(&apConfig);

    int timeout = 600;
    while (timeout--) {
        printf("After %d seconds I will disconnect with AP!\r\n", timeout);
        osDelay(100);
    }

    DisconnectWithHotspot(netId);
}

static void WifiConnectDemo(void)
{
    osThreadAttr_t attr;

    attr.name = "WifiConnectTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 10240;
    attr.priority = osPriorityNormal;

    if (osThreadNew(WifiConnectTask, NULL, &attr) == NULL) {
        printf("[WifiConnectDemo] Falied to create WifiConnectTask!\n");
    }
}
#endif CONNECTER