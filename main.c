#include "main.h"

// === DEFINIÇÕES DE PINOS ===
#define KL30_ON                        HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)
#define Comando_Farol_Baixo            HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)
#define Comando_Farol_Baixo_Automatico HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)
#define KL15_ON                        HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)
#define Engine_ON                      HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)

// LED na Bluepill → PC13 é ligado com nível BAIXO
#define LED_ON()   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)
#define LED_OFF()  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void loop_logic(void)
{
    uint8_t saida = 0;

    if (
        (KL30_ON && Comando_Farol_Baixo && KL15_ON && Engine_ON) ||
        (KL30_ON && Comando_Farol_Baixo && !KL15_ON && Engine_ON) ||
        (KL30_ON && Comando_Farol_Baixo_Automatico && KL15_ON && Engine_ON) ||
        (KL30_ON && Comando_Farol_Baixo_Automatico && !KL15_ON && Engine_ON) ||
        (KL30_ON && Comando_Farol_Baixo && KL15_ON && !Engine_ON) ||
        (KL30_ON && Comando_Farol_Baixo_Automatico && KL15_ON && !Engine_ON)
    )
    {
        saida = 1;
    }

    if (saida)
        LED_ON();
    else
        LED_OFF();
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1)
    {
        loop_logic();
        HAL_Delay(10); // Debounce simples
    }
}
