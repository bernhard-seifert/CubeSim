

// ADCS - FLOAT16


#ifndef OBC_FLOAT16_H
#define OBC_FLOAT16_H


#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


// Half-Precision Float
typedef uint16_t float16_t;

// Convert Half-Precision Float to Single-Precision Float
float float16_float(float16_t x);

// Convert Single-Precision Float to Half-Precision Float
float16_t float_float16(const float& x);


#ifdef __cplusplus
}
#endif

#endif
