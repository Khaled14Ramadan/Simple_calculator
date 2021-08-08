/*
 * challenge.c
 *
 *  Created on: Apr 24, 2019
 *      Author: Metro
 */

#include"lcd.h"
#include"keypad.h"



int main(void)
{
	LCD_init();

	uint32 first_num;/*this first number to this operator*/
	uint8 operator;/* any operator ( * - + / ) */
	uint8 equal_operator;
	uint32 second_num=0;/*this second number to this operator*/


	for(;;)
	{
		code:

		first_num=Key_getPressedKey();
		while(!(first_num >= 0 && first_num <= 9))
		{
			first_num=Key_getPressedKey();
		}
		_delay_ms(500);
		LCD_intgerToString(first_num);


		operator=Key_getPressedKey();
		while((operator >= 0 && operator <= 9) )
		{
			/* this if user want to clear screen */
			if(operator==13)
			{
				LCD_clearScreen();
				goto code;
			}
			_delay_ms(500);
			LCD_intgerToString(operator);
			first_num = (first_num*10) + operator;
			operator=Key_getPressedKey();
		}
		LCD_displayCharacter(operator);
/************************************************************************/

		/* this part of code to take the second number */
		equal_operator=Key_getPressedKey();
		while(!(equal_operator =='='))
		{
			/* this if user want to clear screen */
			if(equal_operator==13)
			{
				LCD_clearScreen();
				second_num=0;
				goto code;
			}
			/* this part of code to take the second number */
			if(equal_operator <=9 && equal_operator >=0)
			{

				_delay_ms(500);
				LCD_intgerToString(equal_operator);
				second_num = (second_num*10) + equal_operator;

			}

			equal_operator=Key_getPressedKey();
		}
		/*this when write =*/
		LCD_displayCharacter(equal_operator);

/***********************************************************************/
		switch(operator)
		{
		case '+':
			LCD_intgerToString((first_num +second_num));
			break;

		case '-':
			LCD_intgerToString((first_num -second_num));
			break;

		case '*':
			LCD_intgerToString((first_num *second_num));
			break;
		case '/':
			LCD_intgerToString((first_num /second_num));
			break;
		}

		/* press enter to clear screen*/
		while(Key_getPressedKey()!= 13);

		LCD_clearScreen();
		second_num=0;

	}
}
