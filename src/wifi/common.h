/* Protocol constants used between wimon and wictl */

#define CMD_STATUS 1
#define CMD_WIRED  2
#define CMD_WLESS  3
#define CMD_STOP   4
#define CMD_SCAN   5
#define CMD_RECONN 6

#define ATTR_LINK    1
#define ATTR_SCAN    2

#define ATTR_IFI    10
#define ATTR_NAME   11
#define ATTR_FLAGS  12
#define ATTR_LOCAL  13

#define ATTR_FREQ   15
#define ATTR_BSSID  16
#define ATTR_SIGNAL 17
#define ATTR_SSID   18
#define ATTR_AUTH   19
#define ATTR_PSK    20

/* ATTR_TYPE; same as ST_* since the values are exported as is */
#define TYPE_WPS         (1<<0)
#define TYPE_WPA         (1<<1)
#define TYPE_RSN         (1<<3)
#define TYPE_RSN_PSK     (1<<4)
#define TYPE_RSN_P_TKIP  (1<<5)
#define TYPE_RSN_P_CCMP  (1<<6)
#define TYPE_RSN_G_TKIP  (1<<7)
#define TYPE_RSN_G_CCMP  (1<<8)
