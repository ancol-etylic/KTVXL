//dieu khien 8 led
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
uint16_t led3[3]={0xffe0, 0xfc1f, 0x03ff};
uint16_t led2[2]={0x03e0, 0x001f};
uint16_t led1[1]={0x0000};

void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);

int main(void){
    Clock_Config(); // configuraion clock
    SystemCoreClockUpdate(); // update SystemCoreClock varibale
    GPIO_Config();
    GPIO_Write(GPIOA, 0xffff);
    Delay(30);
		while(1){int i;
			GPIO_Write(GPIOA, 0xffff);
    Delay(30);
		for( i=0; i<3 ; i++){
					GPIO_Write(GPIOA, led3[i]);
            Delay(30);}
		for( i=0; i<2 ; i++){
					GPIO_Write(GPIOA, led2[i]);
            Delay(30);}
		for( i=0; i<1 ; i++){
					GPIO_Write(GPIOA, led1[i]);
            Delay(30);}
		GPIO_Write(GPIOA, 0x0000);
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
    /*Configuration GPIO pin*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
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