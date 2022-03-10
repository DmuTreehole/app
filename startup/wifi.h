#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifi_hotspot.h"
#include "wifi_hotspot_config.h"

#include "lwip/netifapi.h"

int g_hotspotStarted = 0;

static struct netif* g_iface = NULL;

static void PrintStationInfo(StationInfo* info)
{
    if (!info) return;
    static char macAddress[32] = {0};
    unsigned char* mac = info->macAddress;
    snprintf(macAddress, sizeof(macAddress), "%02X:%02X:%02X:%02X:%02X:%02X",
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    printf(" PrintStationInfo: mac=%s, reason=%d.\r\n", macAddress, info->disconnectedReason);
}

static void OnHotspotStaJoin(StationInfo* info)
{
    PrintStationInfo(info);
    printf("Device ++ \n");
}

static void OnHotspotStaLeave(StationInfo* info)
{   
    PrintStationInfo(info);
    printf("Device -- \n");
}
static void OnHotspotStateChanged(int state)
{
    if (state == WIFI_HOTSPOT_ACTIVE) {
        g_hotspotStarted = 1;
    } else {
        g_hotspotStarted = 0;
    }

}
WifiEvent g_defaultWifiEventListener = {
    .OnHotspotStaJoin = OnHotspotStaJoin,
    .OnHotspotStaLeave = OnHotspotStaLeave,
    .OnHotspotStateChanged = OnHotspotStateChanged,
};

static void WifiHotspotTask(void *arg)
{
    printf("[demo]创建WIFi进程成功");
    (void)arg;
    HotspotConfig config = {0};
    // 准备AP的配置参数
    strcpy(config.ssid, "OS");
    strcpy(config.preSharedKey, "12345678");
    config.securityType = WIFI_SEC_TYPE_PSK;
    config.band = HOTSPOT_BAND_TYPE_2G;
    config.channelNum = 7;
    //开启AP模式
    RegisterWifiEvent(&g_defaultWifiEventListener);
    printf("[demo]事件绑定成功");
    SetHotspotConfig(&config);
    printf("[demo]配置成功");
    g_hotspotStarted = 0;
    EnableHotspot();
    printf("[demo]热点开启成功");
    if(IsHotspotActive() == ERROR_WIFI_UNKNOWN){
        printf("WIFI 开启失败了 这可咋整");
    }
    while(!g_hotspotStarted){
        osDelay(10);
    }
    g_iface = netifapi_netif_find("ap0");

    if (g_iface) {
        ip4_addr_t ipaddr;
        ip4_addr_t gateway;
        ip4_addr_t netmask;

        IP4_ADDR(&ipaddr,  192, 168, 1, 1);     /* input your IP for example: 192.168.1.1 */
        IP4_ADDR(&gateway, 192, 168, 1, 1);     /* input your gateway for example: 192.168.1.1 */
        IP4_ADDR(&netmask, 255, 255, 255, 0);   /* input your netmask for example: 255.255.255.0 */
        err_t ret = netifapi_netif_set_addr(g_iface, &ipaddr, &netmask, &gateway);
        printf("netifapi_netif_set_addr: %d\r\n", ret);

        ret = netifapi_dhcps_start(g_iface, 0, 0);
        printf("netifapi_dhcp_start: %d\r\n", ret);
    }

}
//开启热点
void RunHotspot(void)
{
    osThreadAttr_t attr;
    attr.name = "WifiHotspotTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 1024;
    attr.priority = osPriorityNormal;

    if (osThreadNew(WifiHotspotTask, NULL, &attr) == NULL) {
        printf("[WifiHotspotDemo] Falied to create WifiHotspotTask!\n");
    }
}
//关闭热点
void StopHotspot(void)
{
    printf("[WIFI]WIFI停喽！");
    if (g_iface) {
        err_t ret = netifapi_dhcps_stop(g_iface);
        printf("netifapi_dhcps_stop: %d\r\n", ret);
    }

    WifiErrorCode errCode = UnRegisterWifiEvent(&g_defaultWifiEventListener);
    printf("UnRegisterWifiEvent: %d\r\n", errCode);

    errCode = DisableHotspot();
    printf("EnableHotspot: %d\r\n", errCode);
}