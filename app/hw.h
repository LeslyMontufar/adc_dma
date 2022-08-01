/*
 * hw.h
 *
 *  Created on: July 21, 2022
 *      Author: lesly
 */

#ifndef HW_H_
#define HW_H_

void hw_timer_adc_start(void);
void hw_pwm_start(void);
void hw_timer_start(TIM_HandleTypeDef *htim);
void hw_set_duty(uint16_t duty);
void hw_cpu_sleep();

#endif /* HW_H_ */
