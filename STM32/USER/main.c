#include "main.h"

void radar_init_config(void);


int main(void)
{
	uint8_t i = 0;

	// 外设串口初始化
	hc_init();
	esp_init();
	radar_usart_init();
	
	// 舵机初始化
	Servo_Init();
	
	// 小车初始化
	Car_Init();
	
	// LED初始化
	LED_Init();
	delay_init(168);
	
	esp_prinf("hello,esp\r\n");
	hc_prinf("hello,hc\r\n");
	
	//radar_init_config();
	//start_engineer();.
	esp_prinf("engineer model: %d\r\n",engineer_state);
	while(1)
	{
		Get_data_len();
		if(radar_receive_ok_flag){
			radar_receive_ok_flag=0;
			esp_prinf("%x\r\n",radar_Serial_Buffer[0]);
			esp_prinf("%x\r\n",radar_Serial_Buffer[1]);
			LED1=0;
			LED2=0;
			
		}
		
		// 处理esp32得到数据
		if(esp_receive_ok_flag){
			esp_receive_ok_flag=0;
			i=0;
			while(esp_counter--){
				USART_SendData(USART3,esp_Serial_Buffer[i++]);
				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
			}
			esp_counter=0;
		}
		
		// freertos_demo();
	}
}

void radar_init_config(void){
	radar_enable_config();
	
	esp_prinf("start config: %d\r\n",enable_config);
	
	// 设置分辨率   	0:75cm  --  1:50cm -- 3:25cm
	//radar_speed[4]=0x01;
	radar_setting(8,radar_speed);
	
	// 设置运动和静止的灵敏度
	radar_setting(16,action_ling_config);
	radar_setting(16,static_ling_config);
	
	radar_disable_config();
	esp_prinf("finish config: %d\r\n",enable_config);
}

// 处理蓝牙发送内容
void USART2_IRQHandler(void){
	  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
			hc_data = USART_ReceiveData(USART2);
			
			if(hc_data == '1'){			// receive 49-'0'
				LED1=0;
			}
			else if(hc_data=='0'){
				LED1=1;
			}
			else if(hc_data=='2'){
				LED2=1;
			}
			else if(hc_data=='3'){
				LED2=0;
			}
			else if(hc_data=='4'){
				
			}
		}
}