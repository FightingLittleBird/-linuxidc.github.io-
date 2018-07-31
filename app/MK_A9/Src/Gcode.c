#include "Gcode.h"

u8 cmd_type;

float parameter_float[A_PARA]; 														
u16 parameter_int[A_PARA];

static int next_statement(unsigned char *letter, double *float_ptr, u8 *line, u8 *char_counter) ;

/*ִ��һ��G����*/
u8 gc_execute_line(u8 *line)
{
	u8 letter;																											              //��ǰ��Ϣ����
	double value;																															    //����ֵ
	u16 int_value;																														    //����ֵ
	u8 char_counter = 0; 																												  //�����ڵ�ǰ�ڵڼ�λ
	print_pare_s print_pare;
 
/*STEP1.��������*/
	while(next_statement(&letter, &value, line, &char_counter))									  //�ַ���ĩβλ'\0'	
	{	
			int_value=(u16)value;
//			printf("����:%d, ������:%f\n", int_value, value);			
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

 	printf("G1-(���Ŵ�ӡ75��ͷ����)	G2-(���Ŵ�ӡ75��ͷ����)\r\n");
 	printf("G3-(���Ŵ�ӡ30��ͷ����)	G4-(���Ŵ�ӡ30��ͷ����)\r\n");
 	printf("G5-(���Ŵ�ӡhead����  )	G6-(���Ŵ�ӡhead����)\r\n");
  printf("G%d	X%d	Y%d	Z%d\r\n",	cmd_type, parameter_int[X_PARA],
                                parameter_int[Y_PARA], parameter_int[Z_PARA]);	 	
	switch(cmd_type)
	{
		case 1:
			printf("\r\nX-(��ʼ��) [��Χ0-end]\r\n");
			printf("Y-(������) [��Χ0-end]\r\n");
			printf("Z-(���������ʽ)	[0-HEX	1-DEC]\r\n");																
			print_pare.cmd = column_print_75_CMD;
			print_pare.pare1 = parameter_int[X_PARA];																  //������ʼ��
			print_pare.pare2 = parameter_int[Y_PARA];																  //���ý�����
			print_pare.pare3 = parameter_int[Z_PARA];																  //���ô�ӡ���� 0ʮ������ 1ʮ����
			set_print_format(&print_pare);
			break;
			
		case 2:
			printf("\r\nX-(��ӡ���Ż�����) [X1-��ӡ�������� X2-��ӡ���� X3-��ӡ�������ݺ�����]\r\n");
			print_pare.cmd = row_print_75_CMD;
			print_pare.pare1 = parameter_int[X_PARA];
			print_pare.pare2 = parameter_int[Y_PARA];
			set_print_format(&print_pare);
			break;
			
    case 3:
			printf("\r\nX-(��ʼ��) [��Χ0-end]\r\n");
			printf("Y-(������) [��Χ0-end]\r\n");
			printf("Z-(���������ʽ)	[0-HEX	1-DEC]\r\n");														
			print_pare.cmd = column_print_30_CMD;
			print_pare.pare1 = parameter_int[X_PARA];																  //������ʼ��
			print_pare.pare2 = parameter_int[Y_PARA];																  //���ý�����
			print_pare.pare3 = parameter_int[Z_PARA];																  //���ô�ӡ���� 0ʮ������ 1ʮ����
      set_print_format(&print_pare);		
			break;	
			
		case 4:
			printf("\r\nX-(��ӡ���Ż�����) [X1-��ӡ�������� X2-��ӡ���� X3-��ӡ�������ݺ�����]\r\n");
			print_pare.cmd = row_print_30_CMD;
			print_pare.pare1 = parameter_int[X_PARA];
			print_pare.pare2 = parameter_int[Y_PARA];
			set_print_format(&print_pare);

			break;	

		case 5:
			printf("\r\nX-(��ʼ��) [��Χ0-end]\r\n");
			printf("Y-(������) [��Χ0-end]\r\n");
			printf("Z-(���������ʽ)	[0-HEX	1-DEC]\r\n");													
			print_pare.cmd = column_print_head_CMD;
			print_pare.pare1 = parameter_int[X_PARA];																  //������ʼ��
			print_pare.pare2 = parameter_int[Y_PARA];																  //���ý�����
			print_pare.pare3 = parameter_int[Z_PARA];																  //���ô�ӡ���� 0ʮ������ 1ʮ����
			set_print_format(&print_pare);		
			break;	
			
		case 6:
			printf("\r\nX-(��ӡ���Ż�����) [X1-��ӡ�������� X2-��ӡ���� X3-��ӡ�������ݺ�����]\r\n");												
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
	�������� read_float(u8 *line, u8 *char_counter, double *float_ptr)		
	��������:��������������
	����:һ������ͷ��ַ, �ڼ�λ����, ��Ҫ������Ҫ����������ĸ�����������ַ
	����:�Ƿ����������
	������:����
	����:2016,9,10
	����˵��:
*/
/*��ȡ����ֵ*/
u8 read_float(u8 *line, u8 *char_counter, double *float_ptr)		
{
  unsigned char isnegative = 0;	                                                //������־λ
	unsigned char isdecimal = 0;  	                                              //С�����־λ
  u8 ndigit = 0;									                                              //���ֵڼ�λ	
	u32 intval = 0;									                                              //����ֵ����
  double fval = 0;								                                              //����ֵ����
	s8 exp = 0;											                                              //��¼С����λ��
	u8 c;														                                              //���ݻ���
	u8 *ptr = line + *char_counter + 1;	                                          //����ָ�룬���ݴ���ֵָ��line��char_counterλ�õ�ֵ
//	printf("ptr = %d\n", *ptr);		                                              //���Դ�ӡ��ǰ�ַ�ֵ
	
	c = *ptr++;											                                              //���һ���ַ�������ָ��
//	printf("c1 = %d\n", c);				                                              //��ӡ������Ϣcֵ

	if (c == '-') 									                                              //���������������
	{
			//printf("������count = %d\n", *char_counter);
			isnegative = 1;
			c = *ptr++;
	} else if (c == '+')
	{
			//printf("������count = %d\n", *char_counter);		
			c = *ptr++;
	}	

  while(1) 							                                                        //������һֱѭ��
  {		
			c -= '0';  				                                                        //���ַ�ת��Ϊ���ָ�ֵ��C
			if (c <= 9) 			                                                        //���CС��9��ʾ���ܵ�������
			{
					ndigit++;			                                                        //����λ��һ
					if (MAX_INT_DIGITS <= 12) 		
					{ 
					//
							if (isdecimal) 
							{ 
								exp--;
//								printf("С����\n");
							}  
							intval = (((intval << 2) + intval) << 1) + c;                     //�����÷�ʽ�൱��intval*10 + c  
		      } 
					else 
					{
		       		if (!(isdecimal)) 
							{ 
								exp++; 
							}  
		      }
	    }

			/*c����c -= '0'�����,��cΪ��.��ʱ,cʵ����46-48=-2,c���޷������л���254������c == (('.'-'0') & 0xff;*/
			else if (c == (('.'-'0') & 0xff)  &&  !(isdecimal)) 			                //�����ǰ�ַ�ʱС���㲢��֮ǰû��С������루����CΪʮ������Ҫ����ת��Ϊʮ���������Ƚϣ�
			{
					isdecimal = 1;
					//printf("c = %d ��:%d", c, (('.'-'0') & 0xff));				              //c = 254 ��:254
			} 
			else 
			{
					break;
			}
			c = *ptr++;
  }
	
  if (!ndigit) { return(0); };					                                        //û�����ַ���0

//	printf("ֵ=%d, ��=%d", intval, exp);	
  fval = (double)intval; 								                                        //����ǿ��ת���ɸ���
//	printf("����ֵ=%f, ��=%d", fval, exp);
	//Ӧ��С����Ӧִ�еĲ�������������˷� 
  //E0��E-4��Ԥ�ڷ�Χ
	if (fval != 0) 
	{
		while (exp <= -2) 		                                                      //��С�����λ����λ����
		{
				fval *= 0.01; 		                                                      //������λС����
				exp += 2;					
		}
		
		if (exp < 0) 					                                                      //���С�������һλ����
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
//	printf("ת��=%f, ��=%d", fval, exp);	
	if (isnegative)
	{
		*float_ptr = -fval;
	} 
	else 
	{
		*float_ptr = fval;
	}
	
//	printf("ת����Ĵ����򸡵���=%f", *float_ptr);
	
	*char_counter = ptr - line ;
	
  return 1;
}


/*��ȡ����ֵ*/
u8 read_int(u8 *line, u8 *char_counter, u32 *int_ptr, u8 index_bit )				
{
  u8 ndigit = 0;									                                              //���ֵڼ�λ	
	u32 intval = 0;									                                              //����ֵ����

	u8 c;														                                              //���ݻ���
	u8 *ptr = line + *char_counter + index_bit;	                                              //����ָ�룬���ݴ���ֵָ��line��char_counterλ�õ�ֵ
	//printf("ptr = %d\n", *ptr);		                                              //���Դ�ӡ��ǰ�ַ�ֵ
	
	c = *ptr++;											                                              //���һ���ַ�������ָ��
			
//	printf("intval= %c");
	
	while(1) 							                                                        //������һֱѭ��
  {		
			c -= '0';  				                                                        //���ַ�ת��Ϊ���ָ�ֵ��C
			if (c <= 9) 			                                                        //���CС��9��ʾ���ܵ�������
			{
					ndigit++;			                                                        //����λ��һ
					intval = (((intval << 2) + intval) << 1) + c;                         //�����÷�ʽ�൱��intval*10 + c  		
	    }
			else 
			{
					break;
			}
			c = *ptr++;
  }
	
  if (!ndigit) { return(0); };					                                        //û�����ַ���0

	*int_ptr = intval;
	
//	printf("int_ptr = %d\r\n", *int_ptr);

	*char_counter = ptr - line - index_bit;
	
  return 1;
}

/*����һ��
	���룺line, char_conuter
	�����letter, foloat_ptr
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
//    FAIL(STATUS_EXPECTED_COMMAND_LETTER);						                          //�������Χ
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

