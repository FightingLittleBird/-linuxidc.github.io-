#include "coding_switch2.h"

//static u8 Shift_Add_Cnt;				                                        //正转计数
//static u8 Shift_Sub_Cnt;				                                        //反转计数

u8 Shift_Add_FG2;								                                //正转标志
u8 Shift_Sub_FG2;								                                //反转标志
u8 loop_flag = 1;

/*	new		state A 1bit B 2bit
 *	last	state A 3bit B 4bit
 */
static u8 WMMG1_state;

/* io口软件滤波
	100us扫描一次 
*/
void gpio_filter(void)
{
		
	
}
/* 	1ms扫描一次 
 */
void Scan_Shift2_Prog(void)
{		
	u8 key_value_A;                                                             //A相缓存变量
	u8 key_value_B;                                                             //B相缓存变量
	u8 key_value_A_old;                                                         //上次A相缓存变量
	u8 key_value_B_old;	                                                        //上次A相缓存变量
	
	key_value_A = KEY_ADD2;                                                     //获取电平
	key_value_B = KEY_SUB2;  
	HAL_Delay(1);                                                               //延时防干扰
    
	if(key_value_A == KEY_ADD2)												    //A相数据有效更新数据
	{
		set_WMMG1_state(WMMG1_A_new, key_value_A);	
	}
	if(key_value_B == KEY_SUB2)												    //B相数据有效更新数据
	{
		set_WMMG1_state(WMMG1_B_new, key_value_B);	
	}
	
	key_value_A = get_WMMG1_state(WMMG1_A_new);                                 //获取A相有效电平数据
	key_value_B = get_WMMG1_state(WMMG1_B_new);                                 //获取B相有效电平数据
	key_value_A_old = get_WMMG1_state(WMMG1_A_old);
	key_value_B_old = get_WMMG1_state(WMMG1_B_old);	
	
	if( (key_value_A ^ key_value_B) && loop_flag )											    //A^B = 1 A与B不同表示转动 
	{	
        loop_flag = 0;
//        /* 不执行也可以 */
//		set_WMMG1_state(WMMG1_A_new, key_value_A);			                    //读取数据并设置A电平
//		set_WMMG1_state(WMMG1_B_new, key_value_B);			                    //读取数据并设置B电平
		
		/* 如果AB是从11到01或者是从00到10则为正转 */
		if( (key_value_A_old) && (key_value_B_old) &&                           //AB是从11到01
            (!key_value_A) && (key_value_B))		                                
		{
			Shift_Add_FG2 = 1;
		}
		
		if( (!key_value_A_old) && (!key_value_B_old) &&                         //AB是从00到10
            (key_value_A) && (!key_value_B)) 
		{
			Shift_Add_FG2 = 1;
		}			

		/* 如果AB是从11到10或者是从00到01则为反转 */
		if( (key_value_A_old) && (key_value_B_old) &&                           //AB是从11到10
            (key_value_A) && (!key_value_B))		
		{
			Shift_Sub_FG2 = 1;
		}		
		if( (!key_value_A_old) && (!key_value_B_old) &&                         //AB是从00到01
            (!key_value_A) && (key_value_B)) 
		{
			Shift_Sub_FG2 = 1;
		}	
        

          
        
	}
	else																		//A^B = 0 A与B相同表示静止状态 11 或 00 
	{	
        loop_flag = 1;
        set_WMMG1_state(WMMG1_A_old, key_value_A);		                        //更新A电平 						
        set_WMMG1_state(WMMG1_B_old, key_value_B);		                        //更新B电平	
	}

}

/* 设置编码开关状态 */
void set_WMMG1_state(u8 key, u8 value)
{
	switch(key)
	{
		case WMMG1_A_new:							//设置新值
				if(value)
					WMMG1_state |= (WMMG1_A_new_BIT);
				else
					WMMG1_state &= (~WMMG1_A_new_BIT);
			break;
				
		case WMMG1_B_new:		
				if(value)
					WMMG1_state |= (WMMG1_B_new_BIT);
				else
					WMMG1_state &= (~WMMG1_B_new_BIT);
			break;
				
		case WMMG1_A_old:
				if(value)
					WMMG1_state |= (WMMG1_A_old_BIT);
				else
					WMMG1_state &= (~WMMG1_A_old_BIT);		
			break;
				
		case WMMG1_B_old:
				if(value)
					WMMG1_state |= (WMMG1_B_old_BIT);
				else
					WMMG1_state &= (~WMMG1_B_old_BIT);		
			break;			
	}	
}

/* 读取编码开关状态 */
u8 get_WMMG1_state(u8 key)
{
	u8 value = 0;
	
	switch(key)
	{
		case WMMG1_A_new:							
			if(WMMG1_state & (WMMG1_A_new_BIT))
				value = WMMG_H;
			else
				value = WMMG_L;
			break;
				
		case WMMG1_B_new:		
			if(WMMG1_state & (WMMG1_B_new_BIT))
				value = WMMG_H;
			else
				value = WMMG_L;
			break;
				
		case WMMG1_A_old:
			if(WMMG1_state & (WMMG1_A_old_BIT))
				value = WMMG_H;
			else
				value = WMMG_L;	
			break;
				
		case WMMG1_B_old:
			if(WMMG1_state & (WMMG1_B_old_BIT))
				value = WMMG_H;
			else
				value = WMMG_L;	
			break;	

		default:
			value = WMMG_ERROR;
	}		
	
	return value;
}



