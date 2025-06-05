#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "stm32f4xx.h"

void Ultrasonic_GPIO_Init(void);  // Renamed
void TIM2_us_Delay(uint32_t delay);
double Read_Distance(void);

#endif
