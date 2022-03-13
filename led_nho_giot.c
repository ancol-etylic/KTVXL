//dieu khien 8 led
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
uint16_t led8[8]={0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
uint16_t led7[7]={0x7E, 0x7D, 0x7B, 0x77, 0x6F, 0x5F, 0x3F};
uint16_t led6[6]={0x3E, 0x3D, 0x3B, 0x37, 0x2F, 0x1F};
uint16_t led5[5]={0x1E, 0x1D, 0x1B, 0x17, 0x0F};
uint16_t led4[4]={0x0E, 0x0D, 0x0B, 0x07};
uint16_t led3[3]={0x06, 0x05, 0x03};
uint16_t led2[2]={0x02, 0x01};
uint16_t led1[1]={0x00};

void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);

int main(void){
    Clock_Config(); // configuraion clock
    SystemCoreClockUpdate(); // update SystemCoreClock varibale
    GPIO_Config();
    
    while(1){
			int i=0;
        for( i = 0; i < 8; i++){
            GPIO_Write(GPIOC, led8[i]);
            Delay(30);   
        }
				for( i=0; i<7 ; i++){
					GPIO_Write(GPIOC, led7[i]);
            Delay(30); 
				}
				for( i=0; i<6 ; i++){
					GPIO_Write(GPIOC, led6[i]);
            Delay(30); 
				}
				for( i=0; i<5 ; i++){
					GPIO_Write(GPIOC, led5[i]);
            Delay(30); 
				}
				for( i=0; i<4 ; i++){
					GPIO_Write(GPIOC, led4[i]);
            Delay(30); 
				}
				for( i=0; i<3 ; i++){
					GPIO_Write(GPIOC, led3[i]);
            Delay(30); 
				}
				for( i=0; i<2 ; i++){
					GPIO_Write(GPIOC, led2[i]);
            Delay(30); 
				}
				for( i=0; i<1 ; i++){
					GPIO_Write(GPIOC, led1[i]);
            Delay(30); 
				}GPIO_Write(GPIOC, 0xFF);
            Delay(30);
				
		}
}
/*Delay tuong doi*/
void Delay(uint32_t t){
    unsigned int i,j;
    
    for(i=0;i<t;i++){
        for(j=0;j< 0x2AF0; j++);
    }

}
void GPIO_Config(){
    GPIO_InitTypeDef GPIO_InitStructure;
    /*enble clock for GPIOC*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
    /*Configuration GPIO pin*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void Clock_Config(void){
    /* RCC system reset */
    RCC_DeInit();
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div2);
    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);
    /*enable HSI source clock*/
    RCC_HSICmd(ENABLE); 
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET){}
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    /* Wait till PLL is used as system clock source */
		}