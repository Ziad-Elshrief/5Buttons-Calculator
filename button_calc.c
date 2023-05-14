/*LIB Layer*/
#include "std_types.h"
#define F_CPU 8000000UL
#include <avr/delay.h>

/*MCAL*/
#include "MDIO_Interface.h"

/*HAL*/
#include "HKPD_Interface.h"
#include "HLCD_interface.h"

int main(void){
	u8 Local_u8KeyVal;
	u8 Local_u8Postion=0;
	u8 Local_u8FirstNum=0;
	u8 Local_u8SecondNum=0;
	u8 Local_u8Res=0;
	u8 Local_u8Count=0;
	u8 LocalAu8Sign[4]={'+','-','*','/'};
	MDIO_u8Init();
	HLCD_u8Init();
	HLCD_u8SetCursor(HLCD_u8_Line_1,0);
	HLCD_u16WriteNum(Local_u8FirstNum);
	HLCD_u8WriteChar(LocalAu8Sign[0]);
	HLCD_u16WriteNum(Local_u8SecondNum);
	HLCD_u8WriteChar('=');
	HLCD_u16WriteNum(Local_u8Res);
	HLCD_u8SetCursor(HLCD_u8_Line_1,Local_u8Postion);
	while(1){
		HKPD_u8GetKey(&Local_u8KeyVal);
				if(Local_u8KeyVal=='>'){
					if(Local_u8Postion<2){
						Local_u8Postion++;
						HLCD_u8SetCursor(HLCD_u8_Line_1,Local_u8Postion);
					}
				}
		if(Local_u8KeyVal=='<'){
			if(Local_u8Postion>0){
				Local_u8Postion--;
				HLCD_u8SetCursor(HLCD_u8_Line_1,Local_u8Postion);
			}
		}
		if(Local_u8KeyVal=='V'){
			if(Local_u8Postion==0){
				if(Local_u8FirstNum>0){
					Local_u8FirstNum--;
				}
				else{
					Local_u8FirstNum=9;
				}
				HLCD_u16WriteNum(Local_u8FirstNum);
				HLCD_u8SetCursor(HLCD_u8_Line_1,Local_u8Postion);
			}
			else if(Local_u8Postion==1){
				if(Local_u8Count>0){
					Local_u8Count--;
					LocalAu8Sign[Local_u8Count];
				}
				else{
					Local_u8Count=3;
				}
				HLCD_u8WriteChar(LocalAu8Sign[Local_u8Count]);
				HLCD_u8SetCursor(HLCD_u8_Line_1,Local_u8Postion);
			}
			else if(Local_u8Postion==2){
				if(Local_u8SecondNum>0){
					Local_u8SecondNum--;
				}
				else{
					Local_u8SecondNum=9;
				}
				HLCD_u16WriteNum(Local_u8SecondNum);
				HLCD_u8SetCursor(HLCD_u8_Line_1,Local_u8Postion);
			}
		}
		if(Local_u8KeyVal=='^'){
			if(Local_u8Postion==0){
				if(Local_u8FirstNum<9){
					Local_u8FirstNum++;
				}
				else{
					Local_u8FirstNum=0;
				}
				HLCD_u16WriteNum(Local_u8FirstNum);
				HLCD_u8SetCursor(HLCD_u8_Line_1,Local_u8Postion);
			}
			else if(Local_u8Postion==1){
				if(Local_u8Count<3){
					Local_u8Count++;
					LocalAu8Sign[Local_u8Count];
				}
				else{
					Local_u8Count=0;
				}
				HLCD_u8WriteChar(LocalAu8Sign[Local_u8Count]);
				HLCD_u8SetCursor(HLCD_u8_Line_1,Local_u8Postion);
			}
			else if(Local_u8Postion==2){
				if(Local_u8SecondNum<9){
					Local_u8SecondNum++;
				}
				else{
					Local_u8SecondNum=0;
				}
				HLCD_u16WriteNum(Local_u8SecondNum);
				HLCD_u8SetCursor(HLCD_u8_Line_1,Local_u8Postion);
			}
		}
		if(Local_u8KeyVal=='O'){
			HLCD_u8SetCursor(HLCD_u8_Line_1,4);
			HLCD_u8WriteString("0  ");
			if(LocalAu8Sign[Local_u8Count]=='+'){
				Local_u8Res=Local_u8FirstNum+Local_u8SecondNum;
			}
			if(LocalAu8Sign[Local_u8Count]=='-'){
							Local_u8Res=Local_u8FirstNum-Local_u8SecondNum;
						}
			if(LocalAu8Sign[Local_u8Count]=='*'){
							Local_u8Res=Local_u8FirstNum*Local_u8SecondNum;
						}
			if(LocalAu8Sign[Local_u8Count]=='/'){
					if(Local_u8SecondNum!=0){

							Local_u8Res=Local_u8FirstNum/Local_u8SecondNum;

					if(Local_u8FirstNum%Local_u8SecondNum!=0){
								u8 local_u8Rem= Local_u8FirstNum%Local_u8SecondNum;
								HLCD_u8SetCursor(HLCD_u8_Line_1,5);
								HLCD_u8WriteChar('.');
								HLCD_u8SetCursor(HLCD_u8_Line_1,6);
								local_u8Rem=(((float)local_u8Rem/Local_u8SecondNum)*10);
								HLCD_u16WriteNum(local_u8Rem);
							}
					}
					else{
						HLCD_u8SetCursor(HLCD_u8_Line_2,1);
						HLCD_u8WriteString("Error Div by 0");
						_delay_ms(2000);
						HLCD_u8SetCursor(HLCD_u8_Line_2,1);
						HLCD_u8WriteString("              ");
					}
						}
			HLCD_u8SetCursor(HLCD_u8_Line_1,4);
			HLCD_u16WriteNum(Local_u8Res);
			HLCD_u8SetCursor(HLCD_u8_Line_1,Local_u8Postion);
		}
	}
	return 0;
}
