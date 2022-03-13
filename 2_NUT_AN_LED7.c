#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define BUTTON0              GPIO_Pin_0
#define BUTTON1              GPIO_Pin_1
#define PORT_BUTTON          GPIOB
#define PORT_BUTTON_CLOCK   RCC_APB2Periph_GPIOB

//#define LED0             GPIO_Pin_1
//#define LED1             GPIO_Pin_2
//#define LED2             GPIO_Pin_3
//#define LED3             GPIO_Pin_4
//#define LED4             GPIO_Pin_5
//#define LED5             GPIO_Pin_6
//#define LED6             GPIO_Pin_7
//#define LED7             GPIO_Pin_7

#define PORT_LED         GPIOA
#define PORT_LED_CLOCK   RCC_APB2Periph_GPIOA

//#define LED_ON           GPIO_ResetBits(PORT_LED, LED);
//#define LED_OFF          GPIO_SetBits(PORT_LED, LED);
uint16_t LED7SEG[10]={0XC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);

int main(void)
{
    Clock_Config(); // configuraion clock
    SystemCoreClockUpdate(); // update SystemCoreClock varibale
    GPIO_Config();
	  GPIO_Write(PORT_LED, LED7SEG[0]);
		int i=0;

    while(1){
        
        if(GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON0)==0){
					if(i<9) i+=1;
						while(GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON0) == 0){
					  if(i==9){
						GPIO_Write(PORT_LED, LED7SEG[9]);}else{
							GPIO_Write(PORT_LED, LED7SEG[i]);
							}}
				}
        if(GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON1)==0){
					if(i>0) i-=1;
						while(GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON1) == 0)
					  if(i==0){
						GPIO_Write(PORT_LED, LED7SEG[0]);}else{
							GPIO_Write(PORT_LED, LED7SEG[i]);
						}
				}
		}
}
/*Delay tuong doi*/
void Delay(uint32_t t){
    unsigned int i,j;
    
    for(i=0;i<t;i++){
        for(j=0;j< 0x2AFF; j++);
    }

}
void GPIO_Config(){
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /*enble clock for GPIOC*/
    RCC_APB2PeriphClockCmd(PORT_BUTTON_CLOCK|PORT_LED_CLOCK, ENABLE);
    
    /*Configuration GPIO pin*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin  = BUTTON0| BUTTON1;
    GPIO_Init(PORT_BUTTON,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_0 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(PORT_LED, &GPIO_InitStructure);
}

void Clock_Config(void)
{
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
    while(RCC_GetSYSCLKSource() != 0x00) {}    
}