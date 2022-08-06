/*
 * app.h
 *
 *  Created on: August 06, 2022
 *      Author: lesly
 */

#ifndef APP_H_
#define APP_H_

void app_get_adc_values(void);
void app_average_adc_value(uint16_t *adc_raw_val, uint16_t *adc_avg_ch1, uint16_t *adc_avg_ch2);
void app_init(void);
void app_loop(void);

#endif /* APP_H_ */
