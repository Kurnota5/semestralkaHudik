/*
 * InitFunctions.h
 *
 *  Created on: 19. 1. 2020
 *      Author: Marek
 */

#ifndef GENEROVANIESPRAV_H_
#define GENEROVANIESPRAV_H_

#include "Inicializacia.h"

uint8_t generujCRC(uint8_t *data, uint8_t len);
void zostavSpravuCRC(uint8_t startByte, uint8_t prijimatel, uint8_t * data, uint8_t * vyslednaSprava, uint8_t odosielatel, uint8_t velkostDat);

#endif /* GENEROVANIESPRAV_H_ */
