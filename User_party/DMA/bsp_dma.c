#include "bsp_dma.h"
 uint16_t SourceBuffer[8],DestBuffer[8];
 uint16_t DMAControlTable[1024];
void Dma_config(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	uDMAEnable();
	uDMAControlBaseSet(&DMAControlTable[0]);
	uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT,UDMA_SIZE_8 | UDMA_SRC_INC_8 |UDMA_DST_INC_8 | UDMA_ARB_8);
	uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT,UDMA_MODE_AUTO,SourceBuffer, DestBuffer,sizeof(DestBuffer));
	uDMAChannelEnable(UDMA_CHANNEL_SW);
	uDMAChannelRequest(UDMA_CHANNEL_SW);
}
