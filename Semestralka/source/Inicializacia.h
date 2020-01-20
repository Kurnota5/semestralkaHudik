/*
 * Inicializácia.h
 *
 *  Created on: 19. 1. 2020
 *      Author: Marek
 */

#ifndef INICIALIZACIA_H_
#define INICIALIZACIA_H_

#include "board.h"
#include "fsl_lpsci_dma.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "fsl_lptmr.h"

/* LPSCI instance and clock */
#define LPSCI UART0
#define LPSCI_CLKSRC kCLOCK_CoreSysClk
#define LPSCI_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define LPSCI_TX_DMA_CHANNEL 0U
#define LPSCI_RX_DMA_CHANNEL 1U
#define LPSCI_TX_DMA_REQUEST kDmaRequestMux0LPSCI0Tx
#define LPSCI_RX_DMA_REQUEST kDmaRequestMux0LPSCI0Rx
#define EXAMPLE_LPSCI_DMAMUX_BASEADDR DMAMUX0
#define EXAMPLE_LPSCI_DMA_BASEADDR DMA0

#define DVERE 0xF0
#define MOJA_ADRESA 0X00
#define MAX_VELKOST_SPRAVY 266
#define MAX_VELKOST_DAT 255
#define VELKOST_BUFFRA 5
#define DATA_START_BYTE  0xA0
#define ACK_START_BYTE  0xA1

extern lpsci_dma_handle_t g_lpsciDmaHandle;
extern dma_handle_t g_lpsciTxDmaHandle;
extern dma_handle_t g_lpsciRxDmaHandle;
extern lpsci_config_t config;
extern lpsci_transfer_t xfer;
extern lpsci_transfer_t sendXfer;
extern lpsci_transfer_t receiveXfer;

extern uint8_t g_txBuffer[VELKOST_BUFFRA];
extern uint8_t g_rxBuffer[VELKOST_BUFFRA];
extern volatile bool prijataSpravaJePrazdna;
extern volatile bool txBufferFull;
extern volatile bool txOnGoing;
extern volatile bool rxOnGoing;
extern uint8_t spravaACK[5];
extern uint8_t prijataSprava[VELKOST_BUFFRA];

void LPSCI_UserCallback(UART0_Type *base, lpsci_dma_handle_t *handle, status_t status, void *userData);
void delay(uint32_t dlyTicks);
void nastavDMA();

#endif /* INICIALIZACIA_H_ */
