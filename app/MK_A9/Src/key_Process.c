#include "key_process.h"

message_package package;					//数据包
key_state key;	
u8 key_IRQHandler_flag  = 0;
  
#define JITTER 50

void delay(u32 count)
{
  int i,j;
  for(i=0; i<count; i++)
  {
    for(j=0; j<65535; j++)
    {
    }
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{   
	key.key_pin = GPIO_Pin;
	key_IRQHandler_flag = 1;
}


void gpio_exti_processing(uint16_t GPIO_Pin)
{
	u8 key_value;

	switch(GPIO_Pin)
	{
		/* C1_KEY */	  
		case C1_KEY_Pin:	 
			key_value = HAL_GPIO_ReadPin(C1_KEY_GPIO_Port, C1_KEY_Pin);
    		HAL_Delay(20);			
			if(key_value == HAL_GPIO_ReadPin(C1_KEY_GPIO_Port, C1_KEY_Pin))
			{
				if(HAL_GPIO_ReadPin(C1_KEY_GPIO_Port, C1_KEY_Pin))
				{
					key.fun_key_press_state= 0; 
					key.dir_key_press_state= 0;
					key.fun_key_uplift_state |= (1 << F_KEY_C1);		        //松开功能区按键状态位 设置
					key.Key_uplift_flag= 1;

				}				
				else
				{
					key.fun_key_press_state|= (1 << F_KEY_C1); 
					key.fun_key_uplift_state = 0;						        //松开功能区按键状态位 清零
					key.dir_key_uplift_state = 0;
					key.Key_press_flag= 1;
				}
			}
			break;  
            
		/* C2_KEY */
		case C2_KEY_Pin:
			key_value = HAL_GPIO_ReadPin(C2_KEY_GPIO_Port, C2_KEY_Pin);
    		HAL_Delay(20);			
			if(key_value == HAL_GPIO_ReadPin(C2_KEY_GPIO_Port, C2_KEY_Pin))
			{
				if(HAL_GPIO_ReadPin(C2_KEY_GPIO_Port, C2_KEY_Pin))
				{	
					key.fun_key_press_state= 0; 						        //按下功能区按键状态位 清零
					key.dir_key_press_state= 0;
					key.fun_key_uplift_state |= (1 << F_KEY_C2);		        //松开功能区按键状态位 设置

					key.Key_uplift_flag= 1; 							        //松开按键标志位
				}				
				else
				{					
					key.fun_key_press_state |= (1 << F_KEY_C2); 		        //按下功能区按键状态位 设置
					key.fun_key_uplift_state = 0;						        //松开功能区按键状态位 清零
					key.dir_key_uplift_state = 0;

					key.Key_press_flag= 1;								        //按下按键标志位
				} 
			}		
			break;

		/* UP_KEY */	  
		case UP_KEY_Pin:
			key_value = HAL_GPIO_ReadPin(UP_KEY_GPIO_Port, UP_KEY_Pin);
    		HAL_Delay(20);
			if(key_value == HAL_GPIO_ReadPin(UP_KEY_GPIO_Port, UP_KEY_Pin))
			{
				if(HAL_GPIO_ReadPin(UP_KEY_GPIO_Port, UP_KEY_Pin))
				{
					key.dir_key_press_state= 0; 						        //按下方位区按键状态位 清零
					key.fun_key_press_state= 0;
					key.dir_key_uplift_state |= (1 << D_KEY_TOP);		        //松开方位区按键状态位 设置

					key.Key_uplift_flag= 1; 							        //松开按键标志位
				}				
				else
				{
					key.dir_key_press_state |= (1 << D_KEY_TOP);		        //按下方位区按键状态位 设置
					key.dir_key_uplift_state = 0;						        //松开方位区按键状态位 清零
					key.fun_key_uplift_state = 0;

					key.Key_press_flag= 1;								        //按下按键标志位
				} 
			}		
			break;

		/* DOWN_KEY */
		case DOWN_KEY_Pin:
			key_value = HAL_GPIO_ReadPin(DOWN_KEY_GPIO_Port, DOWN_KEY_Pin);
    		HAL_Delay(20);			
			if(key_value == HAL_GPIO_ReadPin(DOWN_KEY_GPIO_Port, DOWN_KEY_Pin))
			{
				if(HAL_GPIO_ReadPin(DOWN_KEY_GPIO_Port, DOWN_KEY_Pin))
				{
					key.dir_key_press_state= 0; 						        //按下方位区按键状态位 清零
					key.fun_key_press_state= 0;
					key.dir_key_uplift_state |= (1 << D_KEY_DOWN);		        //松开方位区按键状态位 设置

					key.Key_uplift_flag= 1; 							        //松开按键标志位
				}				
				else
				{
					key.dir_key_press_state |= (1 << D_KEY_DOWN);		        //按下方位区按键状态位 设置
					key.dir_key_uplift_state = 0;						        //松开方位区按键状态位 清零
					key.fun_key_uplift_state = 0;
					key.Key_press_flag= 1;								        //按下按键标志位
				} 
			}		
			break;

		/* LEFT_KEY */
//		case LEFT_KEY_Pin:
//			key_value = HAL_GPIO_ReadPin(LEFT_KEY_GPIO_Port, LEFT_KEY_Pin);
//    		HAL_Delay(20);
//			if(key_value == HAL_GPIO_ReadPin(LEFT_KEY_GPIO_Port, LEFT_KEY_Pin))
//			{
//				if(HAL_GPIO_ReadPin(LEFT_KEY_GPIO_Port, LEFT_KEY_Pin))
//				{
//					key.dir_key_press_state= 0; 						        //按下方位区按键状态位 清零
//					key.fun_key_press_state= 0;
//					key.dir_key_uplift_state |= (1 << D_KEY_LEFT);		        //松开方位区按键状态位 设置
//					key.Key_uplift_flag= 1; 							        //松开按键标志位
//				}				
//				else
//				{
//					key.dir_key_press_state |= (1 << D_KEY_LEFT);		        //按下方位区按键状态位 设置
//					key.dir_key_uplift_state = 0;						        //松开方位区按键状态位 清零
//					key.fun_key_uplift_state = 0;
//					key.Key_press_flag= 1;								        //按下按键标志位
//				} 
//			}		
//			break;			

		/* RIGHT_KEY */
		case RIGHT_KEY_Pin:
			key_value = HAL_GPIO_ReadPin(RIGHT_KEY_GPIO_Port, RIGHT_KEY_Pin);
    		HAL_Delay(20);
			if(key_value == HAL_GPIO_ReadPin(RIGHT_KEY_GPIO_Port, RIGHT_KEY_Pin))
			{
				if(HAL_GPIO_ReadPin(RIGHT_KEY_GPIO_Port, RIGHT_KEY_Pin))
				{
					key.dir_key_press_state= 0; 						        //按下方位区按键状态位 清零
					key.fun_key_press_state= 0;
					key.dir_key_uplift_state |= (1 << D_KEY_RIGHT); 	        //松开方位区按键状态位 设置
					key.Key_uplift_flag= 1; 							        //松开按键标志位
				}				
				else
				{
					key.dir_key_press_state |= (1 << D_KEY_RIGHT);		        //按下方位区按键状态位 设置
					key.dir_key_uplift_state = 0;						        //松开方位区按键状态位 清零
					key.fun_key_uplift_state = 0;
					key.Key_press_flag= 1;								        //按下按键标志位
				} 
			}		
			break; 
		   
	}


}


/* 键盘松开处理 */
void Key_uplift_processing(key_state key_stat)
{	
//	u8 fail_flag = 0;
//	switch(key_stat.fun_key_uplift_state)
//	{ 	
//		case (1 << F_KEY_C1):
//			if(!HAL_GPIO_ReadPin(MODE_KEY_GPIO_Port, MODE_KEY_Pin))
//				fail_flag = 1;
//			break; 
//		  
//		case (1 << F_KEY_C2):
//			if(!HAL_GPIO_ReadPin(RET_KEY_GPIO_Port, RET_KEY_Pin))
//				fail_flag = 2;
//			break;   		  
//	}
//
//	switch(key_stat.dir_key_uplift_state)
//	{ 	
//		case (1 << D_KEY_TOP):
//			if(!HAL_GPIO_ReadPin(TOP_KEY_GPIO_Port, TOP_KEY_Pin))
//				fail_flag = 3;
//			break;
//
//		case (1 << D_KEY_DOWN):
//			if(!HAL_GPIO_ReadPin(DOWN_KEY_GPIO_Port, DOWN_KEY_Pin))
//				fail_flag = 4;
//			break;
//
//		case (1 << D_KEY_LEFT):
//			if(!HAL_GPIO_ReadPin(LEFT_KEY_GPIO_Port, LEFT_KEY_Pin))
//				fail_flag = 5;
//			break;
//
//		case (1 << D_KEY_RIGHT):
//			if(!HAL_GPIO_ReadPin(RIGHT_KEY_GPIO_Port, RIGHT_KEY_Pin))
//				fail_flag = 6;
//			break;   		  
//	}	
//
//	if(fail_flag)
//		return;
		
	memset(&package, 0, sizeof(package));	
	/* 功能按键数字设置 */
	switch(key_stat.fun_key_uplift_state)
	{ 	
		case (1 << F_KEY_C1):
			printf("C1 U	");
			package.function_key_code = F_KEY_C1_UPLIFT; 
			break; 
		  
		case (1 << F_KEY_C2):
			printf("C2 U	");
			package.function_key_code = F_KEY_C2_UPLIFT; 
			break;

		default:
			package.function_key_code = 0xfc;	   		  
	}

	/* 方位按键数字设置 */
	switch(key_stat.dir_key_uplift_state)
	{ 	
		case (1 << D_KEY_TOP):
			printf("TOP U	");
			package.direction_key_code = D_KEY_TOP_UPLIFT; 
			break;

		case (1 << D_KEY_DOWN):
			printf("DOWN U	");
			package.direction_key_code = D_KEY_DOWN_UPLIFT; 
			break;

		case (1 << D_KEY_LEFT):
			printf("LEFT U	");
			package.direction_key_code = D_KEY_LEFT_UPLIFT; 
			break;

		case (1 << D_KEY_RIGHT):
			printf("RIGHT U	");
			package.direction_key_code = D_KEY_RIGHT_UPLIFT; 
			break;

		default:
			package.direction_key_code = 0xff;	   		  
	}	
	
	/* 设置发送包数据 */
	package.wheel_key_code = 0xc0;
	package.wheel2_key_code = 0xc0;

//	printf("U %d, %d	", key_stat.fun_key_uplift_state, key_stat.dir_key_uplift_state);	

	send_package();

}


/* 键盘按下处理 */
void Key_press_processing(key_state key_stat)
{
//	u8 fail_falg = 0;
//	
//	switch(key_stat.fun_key_press_state)
//	{ 	
//		case (1 << F_KEY_C1):
//            if(HAL_GPIO_ReadPin(MODE_KEY_GPIO_Port, MODE_KEY_Pin))
//                fail_falg = 1;
//			break; 
//		  
//		case (1 << F_KEY_C2):
//            if(HAL_GPIO_ReadPin(RET_KEY_GPIO_Port, RET_KEY_Pin))
//                fail_falg = 2;
//			break;   		  
//	}    
//    
//	switch(key_stat.dir_key_press_state)
//	{ 	
//		case (1 << D_KEY_TOP):
//            if(HAL_GPIO_ReadPin(TOP_KEY_GPIO_Port, TOP_KEY_Pin))
//                fail_falg = 3;
//			break;
//
//		case (1 << D_KEY_DOWN):
//            if(HAL_GPIO_ReadPin(DOWN_KEY_GPIO_Port, DOWN_KEY_Pin))
//                fail_falg = 4;
//			break;
//
//		case (1 << D_KEY_LEFT):
//            if(HAL_GPIO_ReadPin(LEFT_KEY_GPIO_Port, LEFT_KEY_Pin))
//                fail_falg = 5;
//			break;
//
//		case (1 << D_KEY_RIGHT):
//            if(HAL_GPIO_ReadPin(RIGHT_KEY_GPIO_Port, RIGHT_KEY_Pin))
//                fail_falg = 6;
//			break;			   		  
//	}
//
//	if(fail_falg)
//		return;

	memset(&package, 0, sizeof(package));	
		
	/* 功能按键数字设置 */
	switch(key_stat.fun_key_press_state)
	{ 	
		case (1 << F_KEY_C1):
			printf("C1 P	");
			package.function_key_code = F_KEY_C1_PRESS; 
			break; 
		  
		case (1 << F_KEY_C2):
			printf("C2 P	");
			package.function_key_code = F_KEY_C2_PRESS; 
			break;

		default:
			package.function_key_code = 0xfc;	   		  
	}
	
	/* 方位按键数字设置 */
	switch(key_stat.dir_key_press_state)
	{ 	
		case (1 << D_KEY_TOP):
			printf("TOP P	");
			package.direction_key_code = D_KEY_TOP_PRESS; 
			break;

		case (1 << D_KEY_DOWN):
			printf("DOWN P	");
			package.direction_key_code = D_KEY_DOWN_PRESS; 
			break;

		case (1 << D_KEY_LEFT):
			printf("LEFT P	");
			package.direction_key_code = D_KEY_LEFT_PRESS; 
			break;

		case (1 << D_KEY_RIGHT):
			printf("RIGHT P	");
			package.direction_key_code = D_KEY_RIGHT_PRESS; 
			break;			

		default:
			package.direction_key_code = 0xff;	   		  
	}	
	
	/* 设置发送包数据 */
	package.wheel_key_code = 0xc0;
	package.wheel2_key_code = 0xc0;

//	printf("P %d, %d	", key_stat.fun_key_press_state, key_stat.dir_key_press_state);

	send_package();
}

void usr_key_process(void)
{
	if(key_IRQHandler_flag)
	{
		key_IRQHandler_flag = 0;
	
		switch(key.key_pin)
		{
			case C1_KEY_Pin:
			case C2_KEY_Pin:
			case UP_KEY_Pin:
			case DOWN_KEY_Pin:
//			case LEFT_KEY_Pin:
			case RIGHT_KEY_Pin:
				gpio_exti_processing(key.key_pin);
				break;
	
			case WMMG2_A_Pin:
			case WMMG2_B_Pin:
				Scan_Shift2_Prog(); 
				break;
		} 	 
//					time_count = 0;
	}
				
	if(key.Key_uplift_flag)
	{ 
			Key_uplift_processing(key);
			key.Key_uplift_flag= 0;
			
//			time_count = 0;
	}
	
	if(key.Key_press_flag)
	{
			Key_press_processing(key);
			key.Key_press_flag= 0;
			
//			time_count = 0;
	} 
	
	if(Shift_Add_FG2)
	{
			Shift_Add_FG2 = 0;
			printf("+\r\n");
	}
	
	if(Shift_Sub_FG2)
	{
			Shift_Sub_FG2 = 0;
			printf("-\r\n");
	} 

}




























