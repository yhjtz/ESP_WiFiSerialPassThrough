#include "UDP.h"
#include "usart.h"
#include "driver/uart.h"
#include "set.h"
void ICACHE_FLASH_ATTR udp_recv_cb(void *arg,char *pdata,unsigned short len);

struct espconn user_udp_espconn;  //声明一个espconn结构体变量

/******************************************************************************
 * 函数名      : AP热点初始化
 * 描述          : 初始化8266为一个AP热点
 * 参数          : 无
 * 返回值      : 无
*******************************************************************************/
void ICACHE_FLASH_ATTR
softap_init(void)
{
	wifi_set_opmode(SOFTAP_MODE);
	//------------------------------------------------------------------------------------
	//声明一个softap_config结构体变量
	struct softap_config config;

	//------------------------------------------------------------------------------------
	//以下代码初始化结构体变量config的成员
	//os_strcpy(config.ssid, "FlySET_Test");           //ssid：AP热点名
	os_strcpy(config.ssid, init_Info.WIFI_Name);           //ssid：AP热点名

	//os_strcpy(config.password, "12345678");     //password：AP热点密码
	os_strcpy(config.password, init_Info.WIFI_Key);     //password：AP热点密码
	config.ssid_len = os_strlen(config.ssid);     //ssid_len：AP热点名ssid的字符串长度
	config.channel = 1;                           //channel：信道选择
	config.authmode = AUTH_WPA_PSK;               //authmode：AP热点加密方式
	config.ssid_hidden = 0;                       //ssid_hidden：是否隐藏AP热点密码
	config.max_connection = 2;                    //max_connection：最大连接次数
	config.beacon_interval = 100;                 //beacon_interval：信标间隔时间


	//------------------------------------------------------------------------------------
	//调用wifi_softap_set_config来设置Wi-Fi SoftAP接口，并保持到Flash
	wifi_softap_set_config(&config);

}

/******************************************************************************
 * 函数名      : UDP通讯初始化函数
 * 描述          : 初始化UDP通讯
 * 参数          : 无
 * 返回值      : 无
*******************************************************************************/
void ICACHE_FLASH_ATTR
udpserver_init(void)
{
	//声明一个常量，表示远程主机的IP地址
	char udp_remote_ip[4] = {init_Info.client_IP[0],init_Info.client_IP[1],init_Info.client_IP[2],init_Info.client_IP[3]};
	//	const char udp_local_ip[4] = {255,255,255,255};

	//给结构体变量user_udp_espconn的成员赋值
	user_udp_espconn.type = ESPCONN_UDP;                                 //通信协议类型为UDP
	user_udp_espconn.proto.udp = (esp_udp *)os_zalloc(sizeof(esp_udp));  //声明一个esp_udp结构体变量
	os_memcpy(user_udp_espconn.proto.udp->remote_ip, udp_remote_ip, 4);  //UDP通讯远程主机IP
	//os_memcpy(user_udp_espconn.proto.udp->local_ip, udp_local_ip, 4);  //UDP通讯本地IP
	user_udp_espconn.proto.udp->local_port=init_Info.Udp_remote_port;                         //UDP通讯本地端口
	user_udp_espconn.proto.udp->remote_port=init_Info.Udp_local_port;                        //UDP通讯远程端口
	//------------------------------------------------------------------------------------
	//注册UDP接收回调函数
	espconn_regist_recvcb(&user_udp_espconn, udp_recv_cb);

	//------------------------------------------------------------------------------------
	//创建UDP通信接口
	espconn_create(&user_udp_espconn);

	//------------------------------------------------------------------------------------
	//创建UDP通信接口完成打印日志
	os_printf("udp is ready!\r\n");

}

/******************************************************************************
 * 函数名      : UDP发送函数
 * 描述          : 通过UDP通信转发串口接收到的数据
 * 参数          : 无
 * 返回值      : 无
*******************************************************************************/
void ICACHE_FLASH_ATTR
UdpRcData_To_uart_rx()
{
	//声明一个变量用来存放接收到的数据长度
    uint32 len = 0;

    //计算接收到的数据长度
    len = rx_buff_deq(uart_buf, UART_BUFF_LENTH); //要调用该函数，需要打开串口buff使能宏（driver/uart.h文件第35行）

    //------------------------------------------------------------------------------------
    //判断接收到的数据长度，如果长度不为零，说明接收到了数据，然后进行UDP转发
    if(len != 0)
    {
    	//UDP转发
    	espconn_sendto(&user_udp_espconn, uart_buf, len);

    	//UDP转发之后清空接收区
		os_memset(uart_buf,0,UART_BUFF_LENTH);

	}


}

uint8 ICACHE_FLASH_ATTR check_wifi_connection() {
    return wifi_station_get_connect_status();
}
/******************************************************************************
 * 函数名      : UDP接收回调函数
 * 描述          : UDP接收到数据后回调此函数
 * 参数          : 无
 * 返回值      : 无
*******************************************************************************/
void ICACHE_FLASH_ATTR
udp_recv_cb(void *arg,char *pdata,unsigned short len)
//接收回调函数定义，指针和数据长度
{
	//调用串口发送函数发送接收到的数据
	uart0_tx_buffer((uint8 *)pdata,  len);
}
