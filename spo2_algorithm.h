#ifndef SPO2_ALGORITHM_H_
#define SPO2_ALGORITHM_H_

#include <Arduino.h>

void maxim_heart_rate_and_oxygen_saturation(uint32_t *ir_buffer, int32_t *red_buffer, int32_t buffer_length,
                                            int32_t *spo2, int8_t *spo2_valid,
                                            int32_t *heart_rate, int8_t *hr_valid);

#endif /* SPO2_ALGORITHM_H_ */
