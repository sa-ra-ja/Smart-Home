#include "stm32f4xx.h"
#include "sensors.h"

void GPIO_Init(void) {
    // Enable GPIOA clock
    RCC->AHB1ENR |= (1 << 0);

    // PA0, PA1 - Input (Water & Gas sensors)
    GPIOA->MODER &= ~((3 << (0 * 2)) | (3 << (1 * 2))); // Input mode for PA0, PA1

    // PA5 - Output (LED)
    GPIOA->MODER &= ~(3 << (5 * 2));
    GPIOA->MODER |= (1 << (5 * 2)); // Output mode

    // Push-pull output, no pull-up/down
    GPIOA->OTYPER &= ~(1 << 5);
    GPIOA->PUPDR &= ~((3 << (0 * 2)) | (3 << (1 * 2)) | (3 << (5 * 2)));
}

int Read_Water_Sensor(void) {
    return (GPIOA->IDR & (1 << 0)) ? 1 : 0;
}

int Read_Gas_Sensor(void) {
    return (GPIOA->IDR & (1 << 1)) ? 1 : 0;
}
