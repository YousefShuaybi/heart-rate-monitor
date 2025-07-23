#include "spo2_algorithm.h"

void maxim_heart_rate_and_oxygen_saturation(uint32_t *ir_buffer, int32_t *red_buffer, int32_t buffer_length,
                                            int32_t *spo2, int8_t *spo2_valid,
                                            int32_t *heart_rate, int8_t *hr_valid) {
  // نسخة مختصرة لمحاكاة النتيجة فقط (قابلة للتبديل بخوارزمية حقيقية)
  *spo2 = 97 + (rand() % 3); // قيمة تقريبية
  *heart_rate = 75 + (rand() % 5);
  *spo2_valid = 1;
  *hr_valid = 1;
}
