#include "coding_switch2.h"

//static u8 Shift_Add_Cnt;				                                        //��ת����
//static u8 Shift_Sub_Cnt;				                                        //��ת����

u8 Shift_Add_FG2;								                                //��ת��־
u8 Shift_Sub_FG2;								                                //��ת��־
u8 loop_flag = 1;

/*	new		state A 1bit B 2bit
 *	last	state A 3bit B 4bit
 */
static u8 WMMG1_state;

/* io������˲�
	100usɨ��һ�� 
*/
void gpio_filter(void)
{
		
	
}
/* 	1msɨ��һ�� 
 */
void Scan_Shift2_Prog(void)
{		
	u8 key_value_A;                                                             //A�໺�����
	u8 key_value_B;                                                             //B�໺�����
	u8 key_value_A_old;                                                         //�ϴ�A�໺�����
	u8 key_value_B_old;	                                                        //�ϴ�A�໺�����
	
	key_value_A = KEY_ADD2;                                                     //��ȡ��ƽ
	key_value_B = KEY_SUB2;  
	HAL_Delay(1);                                                               //��ʱ������
    
	if(key_value_A == KEY_ADD2)												    //A��������Ч��������
	{
		set_WMMG1_state(WMMG1_A_new, key_value_A);	
	}
	if(key_value_B == KEY_SUB2)												    //B��������Ч��������
	{
		set_WMMG1_state(WMMG1_B_new, key_value_B);	
	}
	
	key_value_A = get_WMMG1_state(WMMG1_A_new);                                 //��ȡA����Ч��ƽ����
	key_value_B = get_WMMG1_state(WMMG1_B_new);                                 //��ȡB����Ч��ƽ����
	key_value_A_old = get_WMMG1_state(WMMG1_A_old);
	key_value_B_old = get_WMMG1_state(WMMG1_B_old);	
	
	if( (key_value_A ^ key_value_B) && loop_flag )											    //A^B = 1 A��B��ͬ��ʾת�� 
	{	
        loop_flag = 0;
//        /* ��ִ��Ҳ���� */
//		set_WMMG1_state(WMMG1_A_new, key_value_A);			                    //��ȡ���ݲ�����A��ƽ
//		set_WMMG1_state(WMMG1_B_new, key_value_B);			                    //��ȡ���ݲ�����B��ƽ
		
		/* ���AB�Ǵ�11��01�����Ǵ�00��10��Ϊ��ת */
		if( (key_value_A_old) && (key_value_B_old) &&                           //AB�Ǵ�11��01
            (!key_value_A) && (key_value_B))		                                
		{
			Shift_Add_FG2 = 1;
		}
		
		if( (!key_value_A_old) && (!key_value_B_old) &&                         //AB�Ǵ�00��10
            (key_value_A) && (!key_value_B)) 
		{
			Shift_Add_FG2 = 1;
		}			

		/* ���AB�Ǵ�11��10�����Ǵ�00��01��Ϊ��ת */
		if( (key_value_A_old) && (key_value_B_old) &&                           //AB�Ǵ�11��10
            (key_value_A) && (!key_value_B))		
		{
			Shift_Sub_FG2 = 1;
		}		
		if( (!key_value_A_old) && (!key_value_B_old) &&                         //AB�Ǵ�00��01
            (!key_value_A) && (key_value_B)) 
		{
			Shift_Sub_FG2 = 1;
		}	
        

          
        
	}
	else																		//A^B = 0 A��B��ͬ��ʾ��ֹ״̬ 11 �� 00 
	{	
        loop_flag = 1;
        set_WMMG1_state(WMMG1_A_old, key_value_A);		                        //����A��ƽ 						
        set_WMMG1_state(WMMG1_B_old, key_value_B);		                        //����B��ƽ	
	}

}

/* ���ñ��뿪��״̬ */
void set_WMMG1_state(u8 key, u8 value)
{
	switch(key)
	{
		case WMMG1_A_new:							//������ֵ
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

/* ��ȡ���뿪��״̬ */
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



