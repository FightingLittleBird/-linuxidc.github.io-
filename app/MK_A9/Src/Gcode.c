#include "Gcode.h"

u8 cmd_type;

float parameter_float[A_PARA]; 														
u16 parameter_int[A_PARA];

static int next_statement(unsigned char *letter, double *float_ptr, u8 *line, u8 *char_counter) ;

/*执行一行G代码*/
u8 gc_execute_line(u8 *line)
{
	u8 letter;																											              //当前信息缓存
	double value;																															    //浮点值
	u16 int_value;																														    //整形值
	u8 char_counter = 0; 																												  //数据在当前在第几位
	print_pare_s print_pare;
 
/*STEP1.解析命令*/
	while(next_statement(&letter, &value, line, &char_counter))									  //字符串末尾位'\0'	
	{	
			int_value=(u16)value;
//			printf("整数:%d, 浮点数:%f\n", int_value, value);			
			switch(letter)
			{
				case 'G':
          cmd_type = int_value;
					     
				case 'M':
					switch(int_value) 
          {
						case 0: case 1: case 2: case 30: 
                
                break;
						case 3: case 4: case 5: 
                
                break;
					}                  
					break;						

				case 'F': 
					if (value <= 0) 
          { 
          } 	
					break;
			
				case 'T': 																					
					if (value < 0) 
          { 
          } 		
					break;

				case 'S': 																						
					if (value < 0) 
          { 
          } 	
					break;
					
				case 'P': 
					break;		
					
				case 'R':  
					break;	
					
				case 'X': 	
					parameter_int[X_PARA] = int_value;
					break;
				
				case 'Y': 
					parameter_int[Y_PARA] = int_value;
					break;
				
				case 'Z': 
					parameter_int[Z_PARA] = int_value;
					break;	
				
				case 'I': 			
					break;	
				
				case 'J': 		
					break;	
				
				case 'K': 
					break;		

				case 'E': 
					break;	
          
				case 'D': 

					break;	
          
				case 'Q': 
				
					break;				
			}						
	}

 	printf("G1-(竖排打印75开头命令)	G2-(横排打印75开头命令)\r\n");
 	printf("G3-(竖排打印30开头命令)	G4-(横排打印30开头命令)\r\n");
 	printf("G5-(竖排打印head命令  )	G6-(横排打印head命令)\r\n");
  printf("G%d	X%d	Y%d	Z%d\r\n",	cmd_type, parameter_int[X_PARA],
                                parameter_int[Y_PARA], parameter_int[Z_PARA]);	 	
	switch(cmd_type)
	{
		case 1:
			printf("\r\nX-(起始行) [范围0-end]\r\n");
			printf("Y-(结束行) [范围0-end]\r\n");
			printf("Z-(进制输出方式)	[0-HEX	1-DEC]\r\n");																
			print_pare.cmd = column_print_75_CMD;
			print_pare.pare1 = parameter_int[X_PARA];																  //设置起始行
			print_pare.pare2 = parameter_int[Y_PARA];																  //设置结束行
			print_pare.pare3 = parameter_int[Z_PARA];																  //设置打印进制 0十六进制 1十进制
			set_print_format(&print_pare);
			break;
			
		case 2:
			printf("\r\nX-(打印横排或竖排) [X1-打印解析内容 X2-打印数据 X3-打印解析内容和数据]\r\n");
			print_pare.cmd = row_print_75_CMD;
			print_pare.pare1 = parameter_int[X_PARA];
			print_pare.pare2 = parameter_int[Y_PARA];
			set_print_format(&print_pare);
			break;
			
    case 3:
			printf("\r\nX-(起始行) [范围0-end]\r\n");
			printf("Y-(结束行) [范围0-end]\r\n");
			printf("Z-(进制输出方式)	[0-HEX	1-DEC]\r\n");														
			print_pare.cmd = column_print_30_CMD;
			print_pare.pare1 = parameter_int[X_PARA];																  //设置起始行
			print_pare.pare2 = parameter_int[Y_PARA];																  //设置结束行
			print_pare.pare3 = parameter_int[Z_PARA];																  //设置打印进制 0十六进制 1十进制
      set_print_format(&print_pare);		
			break;	
			
		case 4:
			printf("\r\nX-(打印横排或竖排) [X1-打印解析内容 X2-打印数据 X3-打印解析内容和数据]\r\n");
			print_pare.cmd = row_print_30_CMD;
			print_pare.pare1 = parameter_int[X_PARA];
			print_pare.pare2 = parameter_int[Y_PARA];
			set_print_format(&print_pare);

			break;	

		case 5:
			printf("\r\nX-(起始行) [范围0-end]\r\n");
			printf("Y-(结束行) [范围0-end]\r\n");
			printf("Z-(进制输出方式)	[0-HEX	1-DEC]\r\n");													
			print_pare.cmd = column_print_head_CMD;
			print_pare.pare1 = parameter_int[X_PARA];																  //设置起始行
			print_pare.pare2 = parameter_int[Y_PARA];																  //设置结束行
			print_pare.pare3 = parameter_int[Z_PARA];																  //设置打印进制 0十六进制 1十进制
			set_print_format(&print_pare);		
			break;	
			
		case 6:
			printf("\r\nX-(打印横排或竖排) [X1-打印解析内容 X2-打印数据 X3-打印解析内容和数据]\r\n");												
			print_pare.cmd = row_print_head_CMD;
			print_pare.pare1 = parameter_int[X_PARA];
			print_pare.pare2 = parameter_int[Y_PARA];
			set_print_format(&print_pare);

			break;	
			

		default:
			break;
			
	}

	cmd_type = 0;
//	memset(parameter_int, 0, sizeof(parameter_int));
 	  
	return 1;		
}

/*
	函数名： read_float(u8 *line, u8 *char_counter, double *float_ptr)		
	功能描述:解析浮点型数据
	输入:一行数据头地址, 第几位数据, 需要传入需要输出解析出的浮点数变量地址
	返回:是否解析出数字
	创建人:胡明
	日期:2016,9,10
	函数说明:
*/
/*读取浮点值*/
u8 read_float(u8 *line, u8 *char_counter, double *float_ptr)		
{
  unsigned char isnegative = 0;	                                                //正负标志位
	unsigned char isdecimal = 0;  	                                              //小数点标志位
  u8 ndigit = 0;									                                              //数字第几位	
	u32 intval = 0;									                                              //整形值缓存
  double fval = 0;								                                              //浮点值缓存
	s8 exp = 0;											                                              //记录小数点位数
	u8 c;														                                              //数据缓存
	u8 *ptr = line + *char_counter + 1;	                                          //定义指针，根据传入值指向line在char_counter位置的值
//	printf("ptr = %d\n", *ptr);		                                              //调试打印当前字符值
	
	c = *ptr++;											                                              //设第一个字符和增量指针
//	printf("c1 = %d\n", c);				                                              //打印调试信息c值

	if (c == '-') 									                                              //捕获最初的正负号
	{
			//printf("负符号count = %d\n", *char_counter);
			isnegative = 1;
			c = *ptr++;
	} else if (c == '+')
	{
			//printf("正符号count = %d\n", *char_counter);		
			c = *ptr++;
	}	

  while(1) 							                                                        //有数字一直循环
  {		
			c -= '0';  				                                                        //将字符转化为数字赋值给C
			if (c <= 9) 			                                                        //如果C小于9表示接受的是数字
			{
					ndigit++;			                                                        //数字位加一
					if (MAX_INT_DIGITS <= 12) 		
					{ 
					//
							if (isdecimal) 
							{ 
								exp--;
//								printf("小数点\n");
							}  
							intval = (((intval << 2) + intval) << 1) + c;                     //用作用方式相当于intval*10 + c  
		      } 
					else 
					{
		       		if (!(isdecimal)) 
							{ 
								exp++; 
							}  
		      }
	    }

			/*c经过c -= '0'运算过,当c为‘.’时,c实际是46-48=-2,c是无符号所有会变成254，所以c == (('.'-'0') & 0xff;*/
			else if (c == (('.'-'0') & 0xff)  &&  !(isdecimal)) 			                //如果当前字符时小数点并且之前没有小数点进入（当心C为十进制需要‘’转换为十进制再做比较）
			{
					isdecimal = 1;
					//printf("c = %d 点:%d", c, (('.'-'0') & 0xff));				              //c = 254 点:254
			} 
			else 
			{
					break;
			}
			c = *ptr++;
  }
	
  if (!ndigit) { return(0); };					                                        //没有数字返回0

//	printf("值=%d, 点=%d", intval, exp);	
  fval = (double)intval; 								                                        //整数强制转换成浮点
//	printf("浮点值=%f, 点=%d", fval, exp);
	//应用小数，应执行的不超过两个浮点乘法 
  //E0至E-4的预期范围
	if (fval != 0) 
	{
		while (exp <= -2) 		                                                      //有小数点后位数两位以上
		{
				fval *= 0.01; 		                                                      //保留两位小数点
				exp += 2;					
		}
		
		if (exp < 0) 					                                                      //如果小数点后有一位进入
		{ 
				fval *= 0.1; 
		} 
		else if (exp > 0) 
		{
				do 
				{
						fval *= 10.0;
				} while (--exp > 0);
		} 
	}   	
//	printf("转浮=%f, 点=%d", fval, exp);	
	if (isnegative)
	{
		*float_ptr = -fval;
	} 
	else 
	{
		*float_ptr = fval;
	}
	
//	printf("转换后的带方向浮点数=%f", *float_ptr);
	
	*char_counter = ptr - line ;
	
  return 1;
}


/*读取整数值*/
u8 read_int(u8 *line, u8 *char_counter, u32 *int_ptr, u8 index_bit )				
{
  u8 ndigit = 0;									                                              //数字第几位	
	u32 intval = 0;									                                              //整形值缓存

	u8 c;														                                              //数据缓存
	u8 *ptr = line + *char_counter + index_bit;	                                              //定义指针，根据传入值指向line在char_counter位置的值
	//printf("ptr = %d\n", *ptr);		                                              //调试打印当前字符值
	
	c = *ptr++;											                                              //设第一个字符和增量指针
			
//	printf("intval= %c");
	
	while(1) 							                                                        //有数字一直循环
  {		
			c -= '0';  				                                                        //将字符转化为数字赋值给C
			if (c <= 9) 			                                                        //如果C小于9表示接受的是数字
			{
					ndigit++;			                                                        //数字位加一
					intval = (((intval << 2) + intval) << 1) + c;                         //用作用方式相当于intval*10 + c  		
	    }
			else 
			{
					break;
			}
			c = *ptr++;
  }
	
  if (!ndigit) { return(0); };					                                        //没有数字返回0

	*int_ptr = intval;
	
//	printf("int_ptr = %d\r\n", *int_ptr);

	*char_counter = ptr - line - index_bit;
	
  return 1;
}

/*解析一行
	输入：line, char_conuter
	输出：letter, foloat_ptr
*/
static int next_statement(unsigned char *letter, double *float_ptr, u8 *line, u8 *char_counter) 
{
//	(*char_counter)++;
  *letter = line[*char_counter];
//	printf("data:%d  status code:%d\n",*letter, gc.status_code);
//	printf("counter%d\n",*char_counter);
  if((line[*char_counter] == 0) || (line[*char_counter] == 48) || (line[*char_counter] == 32))
    return(0); // No more statements
	
  if((*letter < 'A') || (*letter > 'Z')) {
//    FAIL(STATUS_EXPECTED_COMMAND_LETTER);						                          //超过命令范围
//		printf("status expected command letter!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! data:%d  status code:%d\n",*letter, gc.status_code);
    return(0);
  }
	
	if (!read_float(line, char_counter, float_ptr)) {
//		FAIL(STATUS_BAD_NUMBER_FORMAT); 
//		printf("status bad number format!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  status code:%d\n", gc.status_code);
		return(0);
	};
	return(1);

}

