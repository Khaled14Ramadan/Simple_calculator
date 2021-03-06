/*
 * khaled.c
 *
 *  Created on: Jun 22, 2019
 *      Author: M e t r o
 */

/*
 * calculator.c
 *
 *  Created on: May 8, 2019
 *      Author: Metro
 */
#include"lcd.h"
#include"keypad.h"



void operation(float32 *ptr_num , uint8 *ptr_operation , const uint8 size)
{
	uint8 i=0,x=0;
	uint8 count=0;
	for(;i<size-count;i++)
	{
		if(ptr_operation[i]=='*' || ptr_operation[i]=='/')
		{
			switch(ptr_operation[i])
			{
			case '*':
				ptr_num[i]=ptr_num[i] * ptr_num[i+1];
				break;
			case '/':
				ptr_num[i]=ptr_num[i] / ptr_num[i+1];
				break;
			}
			count++;/*this count to count number of operation(* or /) */
			for(uint8 j=i;j<size-count;j++)
			{
				ptr_num[j+1]=ptr_num[j+2];
				ptr_operation[j]=ptr_operation[j+1];

			}
			i--;/*to start from the same index of operation*/

		}

	}
	for(;x<size-count;x++)
	{

		switch(ptr_operation[x])
		{
		case '+':
			ptr_num[x] = ptr_num[x] + ptr_num[x+1];
			break;
		case '-':
			ptr_num[x] = ptr_num[x] - ptr_num[x+1];
			break;
		}
		count++;/*to add number of operation (+ or -)*/
		for(uint8 j=x;j<size-count;j++)
		{
			ptr_num[j+1]=ptr_num[j+2];
			ptr_operation[j]=ptr_operation[j+1];

		}
		x--;/*to start from the same index of operation*/
	}

	//return ptr_num[0];
	for(uint8 t=0;t<size;t++)
	{
		ptr_num[t+1]=0;
		ptr_operation[t]=0;
	}

}


/*********************************************************************/
int main(void)
{
	code:

	LCD_init();
	float32 arr_num[10]={0};
	uint8 arr_operation[10]={0} , count_operation=0 , check=0;

	for(;;)
	{
		arr_num[count_operation]=Key_getPressedKey();

		while(!(arr_num[count_operation] >= 0 && arr_num[count_operation] <= 9))
		{
			arr_num[count_operation]=Key_getPressedKey();
		}

		_delay_ms(500);
		LCD_intgerToString(arr_num[count_operation]);


		arr_operation[count_operation]=Key_getPressedKey();
		_delay_ms(500);
		newnumber:
		while((arr_operation[count_operation] >= 0 && arr_operation[count_operation] <= 9) )
		{
			/* this if user want to clear screen
			if(arr_operation[count_operation]==13)
			{
				LCD_clearScreen();

				goto code;
			}
			*/

			LCD_intgerToString(arr_operation[count_operation]);
			arr_num[count_operation] = (arr_num[count_operation]*10) + arr_operation[count_operation];
			arr_operation[count_operation]=Key_getPressedKey();
			_delay_ms(500);
		}

		if(arr_operation[count_operation]=='=' || arr_operation[count_operation]==13)
		{
			LCD_clearScreen();

			goto code;
		}

		LCD_displayCharacter(arr_operation[count_operation]);
		count_operation++;
		/************************************************************************/

		/* this part of code to take the second number */
		arr_operation[count_operation]=Key_getPressedKey();
		_delay_ms(500);
		if(arr_operation[count_operation]=='=' || arr_operation[count_operation]==13)
		{
			LCD_clearScreen();

			goto code;
		}
		operation:
		while(!(arr_operation[count_operation] =='='))
		{
			/* this if user want to clear screen
			if(arr_operation[count_operation]==13)
			{
				LCD_clearScreen();

				goto code;
			}
			*/
			/* this part of code to take the second number */
			if(arr_operation[count_operation] <=9 && arr_operation[count_operation] >=0)
			{

				LCD_intgerToString(arr_operation[count_operation]);

				arr_num[count_operation] = (arr_num[count_operation]*10) + arr_operation[count_operation];

				check++;

			}
			else if(check !=0)
			{
				check=0;

				LCD_displayCharacter(arr_operation[count_operation]);

				count_operation++;
			}

			arr_operation[count_operation]=Key_getPressedKey();
			_delay_ms(500);
		}
		/*this when write =*/
		LCD_displayCharacter(arr_operation[count_operation]);

		/***********************************************************************/

		operation(arr_num , arr_operation , count_operation);
		/*display result on LCD*/
		{
			float32 fresult= (arr_num[0] - (int)arr_num[0])*1000;//to hold fraction to float number
			LCD_intgerToString((int)arr_num[0]);
			LCD_displayCharacter('.');
			LCD_intgerToString(fresult);
		}



		/* press enter to clear screen*/
		count_operation=0;
		arr_operation[count_operation]=Key_getPressedKey();
		_delay_ms(500);

		if((arr_operation[count_operation] >= 0 && arr_operation[count_operation] <= 9))
		{
			arr_num[0]=0;
			LCD_clearScreen();
			goto newnumber;
		}
		else if(arr_operation[count_operation] ==13 || arr_operation[count_operation]=='=')
		{
			count_operation=0;
			LCD_clearScreen();
		}
		else
		{
			LCD_clearScreen();
			/*display result on LCD*/
			{
				float32 fresult= (arr_num[0] - (int)arr_num[0])*1000;
				LCD_intgerToString((int)arr_num[0]);
				LCD_displayCharacter('.');
				LCD_intgerToString(fresult);
			}
			goto operation;

		}
		/*while(Key_getPressedKey()!= 13);
		count_operation=0;
		LCD_clearScreen();
		 */

	}
}
