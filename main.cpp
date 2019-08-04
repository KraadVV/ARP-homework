#include <pcap.h>
#include <stdio.h>//still in love with printf
#include <checkmyip.h>
#include <checkmymac.h>
#include <iostream>//cout function
using namespace std;

//base PCAPTEST
void usage() {
  printf("syntax: ARP_test <interface>\n");
  printf("sample: ARP_test wlan0 se.nd.er.ip ta.rg.et.ip \n");
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    usage();
    return -1;
  }

  char* dev = argv[1];
  char* senderIP = argv[2];
  //printf(senderIP);
  char* targetIP = argv[3];

  //checkmyIP
  checkmyIP cIP;

  unsigned char myIPaddr[4] = {0,};
  printf("checking your IP Address...");

  if (cIP.s_getIpAddress(dev, myIPaddr) > 0) {
      printf("your ip addr:=%d.%d.%d.%d", (int)myIPaddr[0], (int)myIPaddr[1], (int)myIPaddr[2], (int)myIPaddr[3]);
  }
  cIP.~checkmyIP();

  //checkmyMAC
  checkmyMAC cMAC;

  char mymac[32]={0};
  cMAC.getMacAddress (mymac,dev);
  cout<<endl<<"Mac Address : "<<mymac;

  cMAC.~checkmyMAC();


  //pcap open live
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
  if (handle == NULL) {
    fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
    return -1;
  }

  //send spoofing packet
  pcap_sendpacket();


  //redirect spoofed packet to victim
  while (true) {
    struct pcap_pkthdr* header;
    const u_char* packet;
    int res = pcap_next_ex(handle, &header, &packet);
    if (res == 0) continue;
    if (res == -1 || res == -2) break;
    printf("%u bytes captured\n", header->caplen);


  }














  //end of code
  pcap_close(handle);
  return 0;
}
