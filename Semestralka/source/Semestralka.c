
#include "Inicializacia.h"
#include "GenerovanieSprav.h"
#include "ManazovanieSprav.h"
#include "Prikazy.h"

void spracujSpravu(uint8_t pTyp, uint8_t pOdosielatel, uint8_t  pVelkostDat, uint8_t* pData, uint8_t  pCrc ) {
	if(pTyp == DATA_START_BYTE && pOdosielatel == 0xC4) {
		ovladajDvere(1);
	}
	if(pTyp == DATA_START_BYTE && pOdosielatel == 0xC3) {
		ovladajDvere(0);
	}
}


int main(void) {
    BOARD_InitPins();
    BOARD_BootClockRUN();
    CLOCK_SetLpsci0Clock(0x1U);

    nastavDMA();

    sendXfer.data = g_txBuffer;
    sendXfer.dataSize = VELKOST_BUFFRA;
    receiveXfer.data = prijataSprava;
    receiveXfer.dataSize = VELKOST_BUFFRA;

    uint8_t typ;
    uint8_t odosielatel;
    uint8_t velkostDat;
    uint8_t data[MAX_VELKOST_DAT] = {0};
    uint8_t crc;

    while (1) {
    	/* If RX is idle and g_rxBuffer is empty, start to read data to g_rxBuffer. */
    	if ((!rxOnGoing) && prijataSpravaJePrazdna) {
    		rxOnGoing = true;
    		LPSCI_TransferReceiveDMA(LPSCI, &g_lpsciDmaHandle, &receiveXfer);
    	}

    	/* If TX is idle and g_txBuffer is full, start to send data. */
    	if ((!txOnGoing) && txBufferFull) {
    		rozparsujSpravu(&typ, &odosielatel, &velkostDat, data, &crc ); //zistenie co je v sprave
    		zostavSpravuCRC(ACK_START_BYTE, DVERE, MOJA_ADRESA, spravaACK,0 , 0);	//zostavenie ack. Je mozne ze sa neposle ak mi prave prislo ack ale pripravim si ho dopredu
    		if(typ == DATA_START_BYTE){
    			posliACK(spravaACK);
    		}
    		spracujSpravu(typ, odosielatel, velkostDat, data, crc );
    	}

    	/* If g_txBuffer is empty and g_rxBuffer is full, copy g_rxBuffer to g_txBuffer. */
    	if ((!prijataSpravaJePrazdna) && (!txBufferFull)) {
    		prijataSpravaJePrazdna = true;
    		txBufferFull = true;
    	}
    }
}

