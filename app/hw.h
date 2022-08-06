/*
 * hw.h
 *
 *  Created on: August 06, 2022
 *      Author: lesly
 */

#ifndef HW_H_
#define HW_H_

void hw_adc_start(uint16_t *values, uint32_t size);
void hw_adc_stop(void);
void hw_adc_calibration(void);
void hw_timer_start(TIM_HandleTypeDef *htim);
void hw_adc_timer_start(void);
void hw_blink_timer_start(void);
void hw_toggle_led(void);
void hw_set_delay(uint16_t delay);

#endif /* HW_H_ */
