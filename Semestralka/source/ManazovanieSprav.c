/*
 * ManazovanieSprav.c
 *
 *  Created on: 19. 1. 2020
 *      Author: Marek
 */

#include "ManazovanieSprav.h"

void vynulujSpravu() {
	for(uint16_t i = 0; i<MAX_VELKOST_SPRAVY; i++)  {
		prijataSprava[i] = 0;
	}
}

void odosliSpravu(uint8_t * vyslednaSprava, uint16_t velkostSpravy) {
	xfer.data = vyslednaSprava;
	xfer.dataSize = velkostSpravy;
	txOnGoing = true;
	LPSCI_TransferSendDMA(LPSCI, &g_lpsciDmaHandle, &xfer);
	while (txOnGoing){
	}
}

void posliACK(uint8_t * vyslednaSprava) {
	uint8_t velkostSpravy = 5;
	odosliSpravu(vyslednaSprava, velkostSpravy);
}


void rozparsujSpravu(uint8_t* pTyp, uint8_t* pOdosielatel, uint8_t*  pVelkostDat, uint8_t* pData, uint8_t*  pCrc ) {
	*pTyp = prijataSprava[0];
	*pOdosielatel = prijataSprava[2];
	*pVelkostDat = prijataSprava[3];
	uint16_t i;
	for(i = 0; i < *pVelkostDat; i++) {
		pData[i] = prijataSprava[i+4];
	}
	*pCrc = prijataSprava[i+4];
}


/*
uint8_t spravaJeOK() {
	uint8_t jeOK = 0;
	if((prijataSprava[1] == 0xA1 ||prijataSprava[1] == 0xA0 ) && prijataSprava[3] == 0x00) {
			uint8_t dataPreCRC [2]  = {0};
			dataPreCRC[0] = prijataSprava[1];
			dataPreCRC[1] = prijataSprava[2];
			if(generujCRC(dataPreCRC,2) == prijataSprava[4]){
				jeOK = 1;
		}
	}
	return jeOK;
}
*/


