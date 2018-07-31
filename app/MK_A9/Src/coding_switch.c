#include "coding_switch.h"

//static u8 Shift_Ram = 0;
static u8 Shift_Old = 0;

static u8 Shift_Add_Cnt;
static u8 Shift_Sub_Cnt;

u8 Shift_Add_FG;
u8 Shift_Sub_FG;

//#define KEY_SUB STM_EVAL_PBGetState(BUTTON5_SUB)
//#define KEY_ADD STM_EVAL_PBGetState(BUTTON7_ADD)


void Scan_Shift_Prog()
{	
	u8 tShift;
	
	tShift = 0;
	if(HAL_GPIO_ReadPin(WMMG2_A_GPIO_Port, WMMG2_A_Pin))  tShift |= 0x01;		//A按下时，状态为置位	
	if(HAL_GPIO_ReadPin(WMMG2_B_GPIO_Port, WMMG2_B_Pin))  tShift |= 0x02;	    //B按下时，状态为置位	


//  if(tShift != Shift_Ram)				                                        //不相等时退出
//  {
//    Shift_Ram = tShift;		
//    return;
//  }

  if(Shift_Old != tShift)				                                        //有按键动作时
  {
//	osDelay(20);
	if(Shift_Old == tShift)  
		return;
    if(((0x8D>>(Shift_Old<<1)) & 0x03) == tShift)				                //A键按下
    {
      if(Shift_Add_Cnt < 4)										                //防干扰
      {
        Shift_Add_Cnt++;										                //计数值加一
      }
      else
      {
        Shift_Add_Cnt = 0;
      }
    }
    else if(((0x72>>(Shift_Old<<1)) & 0x03) == tShift)			                //B键按下
    {
      if(Shift_Sub_Cnt < 4)
      {
        Shift_Sub_Cnt++;										
      }
      else
      {
        Shift_Sub_Cnt = 0;
      }
    }

    Shift_Old = tShift;											                //设置新值								

    if(Shift_Add_Cnt >= 4)						
    {
      Shift_Add_FG = 1;
      Shift_Sub_FG = 0;
      Shift_Add_Cnt = 0;
    }

    if(Shift_Sub_Cnt >= 4)
    {
      Shift_Add_FG = 0;
      Shift_Sub_FG = 1;
      Shift_Sub_Cnt = 0;
    }
  }
}

void wheel_add_processing(void)
{
	printf("+   ");
	package.function_key_code = 0xfc;
	package.direction_key_code = 0xff;
	package.wheel_key_code ++;
	
	if(package.wheel_key_code >= 0xff)
		package.wheel_key_code = 0xff;

	package.wheel2_key_code = 0xc0;	

	key.dir_key_press_state = 0; 						        
	key.fun_key_press_state = 0;
	key.dir_key_uplift_state = 0;
	key.fun_key_uplift_state = 0;

	send_package();
}

void wheel_sub_processing(void)
{
	printf("-   ");
	package.function_key_code = 0xfc;
	package.direction_key_code = 0xff;	
	package.wheel_key_code --;
	
	if(package.wheel_key_code <= 0x0)
		package.wheel_key_code = 0x0;
		
	package.wheel2_key_code = 0xc0;		

	key.dir_key_press_state = 0; 						        
	key.fun_key_press_state = 0;
	key.dir_key_uplift_state = 0;
	key.fun_key_uplift_state = 0;

	send_package();
}


