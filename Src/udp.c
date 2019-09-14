#include <stdio.h>
#include <string.h>

#include "lwip/err.h"
#include "lwip/udp.h"

#define CAN_ID_NUM 10

ip4_addr_t forward_ip;
const uint16_t port_list[CAN_ID_NUM] = {
		0x201 + 10000,
		0x202 + 10000,
		0x203 + 10000,
		0x204 + 10000,
		0x211 + 10000,
		0x212 + 10000,
		0x213 + 10000,
		0x214 + 10000,
		0x215 + 10000,
		0x216 + 10000
};

struct udp_pcb *broadcast_pcb[CAN_ID_NUM];


void UdpSendData(uint8_t id, uint8_t* send_data, uint8_t send_data_size)
{
	// Send UDP data
	struct pbuf * p = pbuf_alloc(PBUF_TRANSPORT, send_data_size * sizeof(uint8_t), PBUF_REF);
	p->payload = send_data;

	udp_sendto(broadcast_pcb[id], p, &forward_ip, port_list[id]); //

	pbuf_free(p);

}

void UdpRecvData(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port)
{
	int i;
      if (p != NULL) {
    	udp_sendto(pcb, p, &forward_ip, port); //dest port
            pbuf_free(p);
      }
}

void StartUdp(uint8_t* ip_addr)
{
	int i;
	for(i=0;i<CAN_ID_NUM;i++){
//		struct udp_pcb *ptel_pcb = udp_new();
//		int port = port_list[i];
//
//		udp_bind(ptel_pcb, IP_ADDR_ANY, port);
		IP4_ADDR(&forward_ip, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);

		//udp_recv(ptel_pcb, UdpRecvData, NULL);

		broadcast_pcb[i] = udp_new();
	}


}
