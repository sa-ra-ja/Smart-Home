#include "ultrasonic.h"

uint32_t data = 0;
double time = 0, dist = 0;

void Ultrasonic_GPIO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~(0x0000FC00);       // Clear MODER5,6,7
    GPIOA->MODER |=  (1 << (5 * 2));     // PA5 Output (Trig)
    GPIOA->MODER |=  (1 << (7 * 2));     // PA7 Output (LED)
    // PA6 remains input (Echo)
}

void TIM2_us_Delay(uint32_t delay)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = 1 - 1;  // Prescaler for 16 MHz (if APB1 = 16 MHz)
    TIM2->ARR = delay * 16 - 1; // Convert µs to ticks (1 µs = 16 ticks)
    TIM2->CNT = 0;
    TIM2->CR1 |= TIM_CR1_CEN;
    while (!(TIM2->SR & TIM_SR_UIF));
    TIM2->SR &= ~TIM_SR_UIF;
    TIM2->CR1 &= ~TIM_CR1_CEN;
}

double Read_Distance(void)
{
    data = 0;
    time = 0;
    dist = 0;

    // 1. Send 10us Trigger Pulse
    GPIOA->BSRR = (1 << (5 + 16)); // PA5 LOW
    TIM2_us_Delay(2);
    GPIOA->BSRR = (1 << 5);        // PA5 HIGH
    TIM2_us_Delay(10);
    GPIOA->BSRR = (1 << (5 + 16)); // PA5 LOW again

    // 2. Wait for Echo to go HIGH
    while (!(GPIOA->IDR & (1 << 6))); // Wait for PA6 HIGH

    // 3. Measure High pulse width
    while (GPIOA->IDR & (1 << 6)) {
        data++;
        TIM2_us_Delay(1); // Measure in microseconds
    }

    // 4. Convert to distance in cm
    if (data > 0)
    {
        time = data * 1e-6; // convert to seconds
        dist = (time * 340.0 / 2) * 100; // cm
    }

    return dist;
}
