/*
 * Inicializacia.c
 *
 *  Created on: 19. 1. 2020
 *      Author: Marek
 */

#include "Prikazy.h"

void ovladajDvere(uint8_t cinnost) {
	uint8_t data[1] = {0};
	uint8_t vyslednaSprava[6] = {0};
	data[0] = cinnost;
	zostavSpravuCRC(DATA_START_BYTE, DVERE, data, vyslednaSprava, MOJA_ADRESA, 0x01);
	uint8_t velkostSpravy = 6;
	odosliSpravu(vyslednaSprava, velkostSpravy);
}
void initVytah() {
	ovladajDvere(1);
	delay(1000);
	ovladajDvere(0);
	delay(1000);
}
