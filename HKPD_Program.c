/*LIB Layer*/
#include "std_types.h"
#define F_CPU 8000000UL
#include <avr/delay.h>

/*MCAL*/
#include "MDIO_Interface.h"

/*HAL*/
#include "HKPD_Interface.h"
#include "HKPD_Config.h"
#include "HKPD_Private.h"

static u8 HKPD_Au8RowPins[4]={HKPD_u8R0_PIN ,HKPD_u8R1_PIN , HKPD_u8R2_PIN , HKPD_u8R3_PIN};
static u8 HKPD_Au8RowPorts[4]={HKPD_u8R0_PORT ,HKPD_u8R1_PORT , HKPD_u8R2_PORT , HKPD_u8R3_PORT};

static u8 HKPD_Au8ColPins[4]={HKPD_u8C0_PIN ,HKPD_u8C1_PIN , HKPD_u8C2_PIN , HKPD_u8C3_PIN};
static u8 HKPD_Au8ColPorts[4]={HKPD_u8C0_PORT ,HKPD_u8C1_PORT , HKPD_u8C2_PORT , HKPD_u8C3_PORT};

static u8 HKPD_Au8Keys[4][4]= HKPD_Keys;

/*Function to get key*/
u8 HKPD_u8GetKey(u8 * Copy_Pu8RetKey ){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	u8 Local_u8RowCounter ,Local_u8ColCounter ,Local_u8PinValue ,Local_u8Flag=0;
	if(Copy_Pu8RetKey != STD_TYPES_NULL){
		/*Init Value for Key Value*/
		*Copy_Pu8RetKey=HKPD_u8_NO_KEY_PRESSED;
		/*Activate Each row*/
		for(Local_u8RowCounter=0;Local_u8RowCounter<=3;Local_u8RowCounter++ ){
			/*Activate Row*/
			MDIO_u8SetPinValue(HKPD_Au8RowPorts[Local_u8RowCounter]
								,HKPD_Au8RowPins[Local_u8RowCounter],MDIO_u8_LOW);
			/*Check Cols*/
			for(Local_u8ColCounter=0;Local_u8ColCounter<=3;Local_u8ColCounter++){
				MDIO_u8GetPinValue(HKPD_Au8ColPorts[Local_u8ColCounter]
									,HKPD_Au8ColPins[Local_u8ColCounter],&Local_u8PinValue);
				/*Check if pin value = Low*/
				if(Local_u8PinValue==MDIO_u8_LOW){
					/*Wait for debouncing*/
					_delay_ms(20);
					while(Local_u8PinValue==MDIO_u8_LOW){
						MDIO_u8GetPinValue(HKPD_Au8ColPorts[Local_u8ColCounter]
									,HKPD_Au8ColPins[Local_u8ColCounter],&Local_u8PinValue);
					}
					/*Return value*/
					*Copy_Pu8RetKey = HKPD_Au8Keys[Local_u8RowCounter][Local_u8ColCounter];
					Local_u8Flag=1;
					break;

				}
			}
			/*Deactivate Row*/
			MDIO_u8SetPinValue(HKPD_Au8RowPorts[Local_u8RowCounter]
									,HKPD_Au8RowPins[Local_u8RowCounter],MDIO_u8_HIGH);
			if(Local_u8Flag==1){
				break;
			}
		}
	}
	else{
		Local_u8ErrorState=STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}
