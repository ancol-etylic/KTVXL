#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "lcd16x2.h"
#include "delay.h"

int main(void)
{
    // Delay initialization
    DelayInit();
    // LCD initialization
    LCD_Init();
	while(1){
        LCD_Gotoxy(0,0);
        
				LCD_Puts("STT 01 Nhom 02");
				LCD_SendCommand(0x01); // xoa toan bo khung hinh
				LCD_Gotoxy(1,0);
        LCD_Puts("PHAM THANH AN");
				LCD_Gotoxy(1,1);
        LCD_Puts("NGO NGOC QUY");
				DelayMs(100);
		
//        LCD_Puts("0123456789ABCDEF");
//				DelayMs(100);
//				for(int i=0;i<16;i++){
//						LCD_SendCommand(0x18);
//				DelayMs(30);}
//				LCD_SendCommand(0x03);
//				DelayMs(30);
//				for(int i=0;i<16;i++){
//						LCD_SendCommand(0x1C);
//				DelayMs(30);}
				LCD_SendCommand(0x01); // xoa toan bo khung hinh
	}
}

