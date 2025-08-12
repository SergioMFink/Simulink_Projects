#ifndef ABSCONTROLLER_HPP
#define ABSCONTROLLER_HPP

#include "main.h"

class ABSController {
public:
    ABSController(TIM_HandleTypeDef* htim_handle);
    void run();

private:
    TIM_HandleTypeDef* pwm_timer_handle;
    const uint16_t DUTY_CYCLE_NORMAL = 90; // 90% para Counter Period 99
    const uint16_t DUTY_CYCLE_ACTIVE = 30; // 30% para Counter Period 99

    void setDutyCycle(uint16_t duty);
};

#endif // ABSCONTROLLER_HPP
