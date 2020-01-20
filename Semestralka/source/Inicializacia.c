/*
 * Inicializacia.c
 *
 *  Created on: 19. 1. 2020
 *      Author: Marek
 */

#include "Inicializacia.h"

uint8_t g_txBuffer[VELKOST_BUFFRA] = {0};
uint8_t g_rxBuffer[VELKOST_BUFFRA] = {0};
volatile bool prijataSpravaJePrazdna = true;
volatile bool txBufferFull = false;
volatile bool txOnGoing = false;
volatile bool rxOnGoing = false;
uint8_t spravaACK[5] = {0};
uint8_t prijataSprava[VELKOST_BUFFRA] = {0};

lpsci_dma_handle_t g_lpsciDmaHandle;
dma_handle_t g_lpsciTxDmaHandle;
dma_handle_t g_lpsciRxDmaHandle;

lpsci_config_t config;
lpsci_transfer_t xfer;
lpsci_transfer_t sendXfer;
lpsci_transfer_t receiveXfer;

void delay(uint32_t dlyTicks) {
	dlyTicks = dlyTicks * 48000;
	while (dlyTicks--)
	{
		__NOP();
	}
}

void LPSCI_UserCallback(UART0_Type *base, lpsci_dma_handle_t *handle, status_t status, void *userData) {
    userData = userData;

    if (kStatus_LPSCI_TxIdle == status)
    {
        txBufferFull = false;
        txOnGoing = false;
    }

    if (kStatus_LPSCI_RxIdle == status)
    {
    	prijataSpravaJePrazdna = false;
        rxOnGoing = false;
    }
}

void nastavDMA() {
    LPSCI_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    config.enableTx = true;
    config.enableRx = true;

    LPSCI_Init(LPSCI, &config, LPSCI_CLK_FREQ);

    /* Init DMAMUX */
    DMAMUX_Init(EXAMPLE_LPSCI_DMAMUX_BASEADDR);

    /* Set channel for LPSCI  */
    DMAMUX_SetSource(EXAMPLE_LPSCI_DMAMUX_BASEADDR, LPSCI_TX_DMA_CHANNEL, LPSCI_TX_DMA_REQUEST);
    DMAMUX_EnableChannel(EXAMPLE_LPSCI_DMAMUX_BASEADDR, LPSCI_TX_DMA_CHANNEL);
    DMAMUX_SetSource(EXAMPLE_LPSCI_DMAMUX_BASEADDR, LPSCI_RX_DMA_CHANNEL, LPSCI_RX_DMA_REQUEST);
    DMAMUX_EnableChannel(EXAMPLE_LPSCI_DMAMUX_BASEADDR, LPSCI_RX_DMA_CHANNEL);

    /* Init the DMA module */
    DMA_Init(EXAMPLE_LPSCI_DMA_BASEADDR);
    DMA_CreateHandle(&g_lpsciTxDmaHandle, EXAMPLE_LPSCI_DMA_BASEADDR, LPSCI_TX_DMA_CHANNEL);
    DMA_CreateHandle(&g_lpsciRxDmaHandle, EXAMPLE_LPSCI_DMA_BASEADDR, LPSCI_RX_DMA_CHANNEL);

    /* Create LPSCI DMA handle. */
    LPSCI_TransferCreateHandleDMA(LPSCI, &g_lpsciDmaHandle, LPSCI_UserCallback, NULL, &g_lpsciTxDmaHandle,
                          &g_lpsciRxDmaHandle);
}

