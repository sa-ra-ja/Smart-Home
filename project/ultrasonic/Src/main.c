#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"

#define ARM_MATH_CM4

void GPIO_Init(void);
void TIM2_us_Delay(uint32_t delay); //TIM2 for generating 10us pulse

uint32_t data;
double time, dist;

void GPIO_Init(){
    // Enable GPIOA clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // PA5 = Output (Trig)
    GPIOA->MODER &= ~(3 << (5 * 2));
    GPIOA->MODER |= (1 << (5 * 2)); // Output mode

    // PA6 = Input (Echo)
    GPIOA->MODER &= ~(3 << (6 * 2)); // Input mode

    // PA7 = Output (LED)
    GPIOA->MODER &= ~(3 << (7 * 2));
    GPIOA->MODER |= (1 << (7 * 2)); // Output mode
}

void TIM2_us_Delay(uint32_t delay){
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable Timer2 clock

    TIM2->PSC = 1 - 1; // Prescaler
    TIM2->ARR = delay * 16 - 1; // For 1 us tick at 16 MHz
    TIM2->CNT = 0;
    TIM2->EGR = TIM_EGR_UG; // Generate update
    TIM2->SR &= ~TIM_SR_UIF;
    TIM2->CR1 |= TIM_CR1_CEN; // Enable timer

    while (!(TIM2->SR & TIM_SR_UIF)); // Wait till update
    TIM2->SR &= ~TIM_SR_UIF; // Clear flag
}

int main(){
    GPIO_Init();
    GPIOA->BSRR = (1 << (5 + 16)); // Ensure Trig (PA5) is LOW

    while (1){
        // Send 10us pulse
        GPIOA->BSRR = (1 << (5 + 16)); // PA5 LOW
        TIM2_us_Delay(2);

        GPIOA->BSRR = (1 << 5); // PA5 HIGH
        TIM2_us_Delay(10);
        GPIOA->BSRR = (1 << (5 + 16)); // PA5 LOW again

        // Wait for Echo to go HIGH
        while (!(GPIOA->IDR & (1 << 6))); // Wait for PA6 HIGH

        data = 0;
        while (GPIOA->IDR & (1 << 6)){ // While echo is HIGH
            data++;
            TIM2_us_Delay(1); // Each loop ~1us
        }

        if (data > 0){
            time = data * 1e-6; // Convert to seconds
            dist = ((time * 340.0) / 2.0) * 100.0; // in cm

            if (dist < 10.0){
                GPIOA->BSRR = (1 << 7); // LED ON (PA7)
            } else {
                GPIOA->BSRR = (1 << (7 + 16)); // LED OFF (PA7)
            }
        }

        TIM2_us_Delay(60 * 1000); // Delay between measurements (~60ms)
        data = 0;
    }
}
