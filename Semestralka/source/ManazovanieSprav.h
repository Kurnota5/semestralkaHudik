/*
 * ManazovanieSprav.h
 *
 *  Created on: 19. 1. 2020
 *      Author: Marek
 */

#ifndef MANAZOVANIESPRAV_H_
#define MANAZOVANIESPRAV_H_

#include "Inicializacia.h"
#include "GenerovanieSprav.h"

void vynulujSpravu();
void odosliSpravu(uint8_t * vyslednaSprava, uint16_t velkostSpravy);
void posliACK(uint8_t * vyslednaSprava);
void rozparsujSpravu(uint8_t* pTyp, uint8_t* pOdosielatel, uint8_t*  pVelkostDat, uint8_t* pData, uint8_t*  pCrc );

#endif /* MANAZOVANIESPRAV_H_ */
