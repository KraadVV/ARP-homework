#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <net/if.h>
#include <unistd.h>
#include <checkmymac.h>

//source from https://www.includehelp.com/cpp-programs/get-mac-address-of-linux-based-network-device.aspx
using namespace std;
checkmyMAC::checkmyMAC(){}
checkmyMAC::~checkmyMAC(){}

void checkmyMAC::getMacAddress(char *uc_Mac, char *iface)
{
    int fd;

    struct ifreq ifr;

    char *mac;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy((char *)ifr.ifr_name , (const char *)iface , IFNAMSIZ-1);

    ioctl(fd, SIOCGIFHWADDR, &ifr);

    close(fd);

    mac = (char *)ifr.ifr_hwaddr.sa_data;

    //display mac address
    sprintf((char *)uc_Mac,(const char *)"your mac address = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n" , mac[0], mac[1], mac[2], 0xFFFFFF00^mac[3], 0xFFFFFF00^mac[4], 0xFFFFFF00^mac[5]);

}

