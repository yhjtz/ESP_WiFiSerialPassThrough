#include "UDP.h"
#include "usart.h"
#include "driver/uart.h"
#include "set.h"
void ICACHE_FLASH_ATTR udp_recv_cb(void *arg,char *pdata,unsigned short len);

struct espconn user_udp_espconn;  //����һ��espconn�ṹ�����

/******************************************************************************
 * ������      : AP�ȵ��ʼ��
 * ����          : ��ʼ��8266Ϊһ��AP�ȵ�
 * ����          : ��
 * ����ֵ      : ��
*******************************************************************************/
void ICACHE_FLASH_ATTR
softap_init(void)
{
	wifi_set_opmode(SOFTAP_MODE);
	//------------------------------------------------------------------------------------
	//����һ��softap_config�ṹ�����
	struct softap_config config;

	//------------------------------------------------------------------------------------
	//���´����ʼ���ṹ�����config�ĳ�Ա
	//os_strcpy(config.ssid, "FlySET_Test");           //ssid��AP�ȵ���
	os_strcpy(config.ssid, init_Info.WIFI_Name);           //ssid��AP�ȵ���

	//os_strcpy(config.password, "12345678");     //password��AP�ȵ�����
	os_strcpy(config.password, init_Info.WIFI_Key);     //password��AP�ȵ�����
	config.ssid_len = os_strlen(config.ssid);     //ssid_len��AP�ȵ���ssid���ַ�������
	config.channel = 1;                           //channel���ŵ�ѡ��
	config.authmode = AUTH_WPA_PSK;               //authmode��AP�ȵ���ܷ�ʽ
	config.ssid_hidden = 0;                       //ssid_hidden���Ƿ�����AP�ȵ�����
	config.max_connection = 2;                    //max_connection��������Ӵ���
	config.beacon_interval = 100;                 //beacon_interval���ű���ʱ��


	//------------------------------------------------------------------------------------
	//����wifi_softap_set_config������Wi-Fi SoftAP�ӿڣ������ֵ�Flash
	wifi_softap_set_config(&config);

}

/******************************************************************************
 * ������      : UDPͨѶ��ʼ������
 * ����          : ��ʼ��UDPͨѶ
 * ����          : ��
 * ����ֵ      : ��
*******************************************************************************/
void ICACHE_FLASH_ATTR
udpserver_init(void)
{
	//����һ����������ʾԶ��������IP��ַ
	char udp_remote_ip[4] = {init_Info.client_IP[0],init_Info.client_IP[1],init_Info.client_IP[2],init_Info.client_IP[3]};
	//	const char udp_local_ip[4] = {255,255,255,255};

	//���ṹ�����user_udp_espconn�ĳ�Ա��ֵ
	user_udp_espconn.type = ESPCONN_UDP;                                 //ͨ��Э������ΪUDP
	user_udp_espconn.proto.udp = (esp_udp *)os_zalloc(sizeof(esp_udp));  //����һ��esp_udp�ṹ�����
	os_memcpy(user_udp_espconn.proto.udp->remote_ip, udp_remote_ip, 4);  //UDPͨѶԶ������IP
	//os_memcpy(user_udp_espconn.proto.udp->local_ip, udp_local_ip, 4);  //UDPͨѶ����IP
	user_udp_espconn.proto.udp->local_port=init_Info.Udp_remote_port;                         //UDPͨѶ���ض˿�
	user_udp_espconn.proto.udp->remote_port=init_Info.Udp_local_port;                        //UDPͨѶԶ�̶˿�
	//------------------------------------------------------------------------------------
	//ע��UDP���ջص�����
	espconn_regist_recvcb(&user_udp_espconn, udp_recv_cb);

	//------------------------------------------------------------------------------------
	//����UDPͨ�Žӿ�
	espconn_create(&user_udp_espconn);

	//------------------------------------------------------------------------------------
	//����UDPͨ�Žӿ���ɴ�ӡ��־
	os_printf("udp is ready!\r\n");

}

/******************************************************************************
 * ������      : UDP���ͺ���
 * ����          : ͨ��UDPͨ��ת�����ڽ��յ�������
 * ����          : ��
 * ����ֵ      : ��
*******************************************************************************/
void ICACHE_FLASH_ATTR
UdpRcData_To_uart_rx()
{
	//����һ������������Ž��յ������ݳ���
    uint32 len = 0;

    //������յ������ݳ���
    len = rx_buff_deq(uart_buf, UART_BUFF_LENTH); //Ҫ���øú�������Ҫ�򿪴���buffʹ�ܺ꣨driver/uart.h�ļ���35�У�

    //------------------------------------------------------------------------------------
    //�жϽ��յ������ݳ��ȣ�������Ȳ�Ϊ�㣬˵�����յ������ݣ�Ȼ�����UDPת��
    if(len != 0)
    {
    	//UDPת��
    	espconn_sendto(&user_udp_espconn, uart_buf, len);

    	//UDPת��֮����ս�����
		os_memset(uart_buf,0,UART_BUFF_LENTH);

	}


}

uint8 ICACHE_FLASH_ATTR check_wifi_connection() {
    return wifi_station_get_connect_status();
}
/******************************************************************************
 * ������      : UDP���ջص�����
 * ����          : UDP���յ����ݺ�ص��˺���
 * ����          : ��
 * ����ֵ      : ��
*******************************************************************************/
void ICACHE_FLASH_ATTR
udp_recv_cb(void *arg,char *pdata,unsigned short len)
//���ջص��������壬ָ������ݳ���
{
	//���ô��ڷ��ͺ������ͽ��յ�������
	uart0_tx_buffer((uint8 *)pdata,  len);
}
