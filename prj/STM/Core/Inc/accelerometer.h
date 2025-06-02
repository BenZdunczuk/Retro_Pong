#ifndef INC_ACCELEROMETER_H_
#define INC_ACCELEROMETER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "lsm303c.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_compass.h"
#include <stdio.h>
#include "main.h"

/**
* \file
* \brief Plik nagłówkowy funkcji obsługujących działanie akcelerometru
*
*/

	/**
     * @brief Funkcja inicjalizująca działania akcelerometru
     */
uint8_t accInit(void);

	/**
     * @brief Funkcja kalibrująca działanie akcelerometru
     */
void accel_calibrate(int16_t offset_cb[3], uint16_t samples);

	/**
     * @brief Funkcja filtrująca dane z akcelerometru
     */
int16_t accel_lpf_int(int16_t in, int16_t *prev, uint8_t alpha);

	/**
     * @brief Funkcja zwracająca dane z akcelerometru
     */
void AccGetData(int16_t out[3]);

#ifdef __cplusplus
}
#endif

#endif /* INC_ACCELEROMETER_H_ */
