#include "ABSController.hpp"

// Construtor da classe
ABSController::ABSController(TIM_HandleTypeDef* htim_handle) {
    pwm_timer_handle = htim_handle;
    // Inicia o PWM
    HAL_TIM_PWM_Start(pwm_timer_handle, TIM_CHANNEL_2);
    // Define o estado inicial do duty cycle
    setDutyCycle(DUTY_CYCLE_NORMAL);
}

// Método principal que executa a lógica
void ABSController::run() {
    // A lógica de leitura é a mesma
    // Lembre-se que as labels dos pinos que você definiu na IDE se tornam os nomes para as macros!
    // A IDE deve gerar algo como `front_left_wheel_signal_Pin`, `front_right_wheel_signal_Pin`, etc.
    if (HAL_GPIO_ReadPin(front_left_wheel_signal_GPIO_Port, front_left_wheel_signal_Pin) == GPIO_PIN_RESET ||
        HAL_GPIO_ReadPin(front_right_wheel_signal_GPIO_Port, front_right_wheel_signal_Pin) == GPIO_PIN_RESET ||
        HAL_GPIO_ReadPin(back_left_wheel_signal_GPIO_Port, back_left_wheel_signal_Pin) == GPIO_PIN_RESET ||
        HAL_GPIO_ReadPin(back_right_wheel_signal_GPIO_Port, back_right_wheel_signal_Pin) == GPIO_PIN_RESET) {

        setDutyCycle(DUTY_CYCLE_ACTIVE);
    } else {
        setDutyCycle(DUTY_CYCLE_NORMAL);
    }
}

// Método privado para ajustar o duty cycle
void ABSController::setDutyCycle(uint16_t duty) {
    __HAL_TIM_SET_COMPARE(pwm_timer_handle, TIM_CHANNEL_2, duty);
}
