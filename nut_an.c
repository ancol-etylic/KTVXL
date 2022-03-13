#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define BUTTON              GPIO_Pin_0
#define PORT_BUTTON         GPIOB
#define PORT_BUTTON_CLOCK   RCC_APB2Periph_GPIOB

#define LED0             GPIO_Pin_0
#define LED1             GPIO_Pin_1
#define LED2             GPIO_Pin_2
#define LED3             GPIO_Pin_3
#define LED4             GPIO_Pin_4
#define LED5             GPIO_Pin_5
#define LED6             GPIO_Pin_6
#define LED7             GPIO_Pin_7

#define PORT_LED         GPIOC
#define PORT_LED_CLOCK   RCC_APB2Periph_GPIOC

//#define LED_ON           GPIO_ResetBits(PORT_LED, LED);
//#define LED_OFF          GPIO_SetBits(PORT_LED, LED);

void Delay(uint32_t);
void GPIO_Config(void);
void Clock_Config(void);

int main(void)
{
    Clock_Config(); // configuraion clock
    SystemCoreClockUpdate(); // update SystemCoreClock varibale
    GPIO_Config();

    while(1){
        
        if(GPIO_ReadInputDataBit(PORT_BUTTON, BUTTON)==0){
            //LED_ON;
					GPIO_Write(PORT_LED, 0x00);
        }
        else{
            //LED_OFF;
					GPIO_Write(PORT_LED, 0xFF);
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
    GPIO_InitStructure.GPIO_Pin  = BUTTON;
    GPIO_Init(PORT_BUTTON,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin  = LED0 | LED1| LED2| LED3| LED4| LED5| LED6| LED7;
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