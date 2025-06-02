#ifndef INC_GYROSCOPE_H_
#define INC_GYROSCOPE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "l3gd20.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_gyroscope.h"

/**
* \file
* \brief Plik nagłówkowy funkcji obsługujących działanie żyroskopu
*
*/

	/**
     * @brief Funkcja inicjalizująca działanie żyroskopu
     */
uint8_t GyroInit();

	/**
     * @brief Funkcja pobierająca i wyświetlająca dane z żyroskopu
     */
void GyroGetData(float gyroDataFiltered[3]);


//void gyroFilterData()

#ifdef __cplusplus
}
#endif

#endif /* INC_GYROSCOPE_H_ */
