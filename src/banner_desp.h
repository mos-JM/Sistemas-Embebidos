/*****************************************************************************
* Filename:          C:\hlocal\hlocal\prac2\prac2/drivers/banner_desp_v1_00_a/src/banner_desp.h
* Version:           1.00.a
* Description:       banner_desp Driver Header File
* Date:              Mon Nov 26 17:30:02 2018 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef BANNER_DESP_H
#define BANNER_DESP_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"

/************************** Constant Definitions ***************************/


/**
 * User Logic Slave Space Offsets
 */
#define BANNER_DESP_USER_SLV_SPACE_OFFSET (0x00000000)

/**
 * Write Packet FIFO Register/Data Space Offsets
 * -- WRFIFO_RST  : write packet fifo reset register
 * -- WRFIFO_SR   : write packet fifo status register
 * -- WRFIFO_DATA : write packet fifo data
 */
#define BANNER_DESP_WRFIFO_REG_SPACE_OFFSET (0x00000100)
#define BANNER_DESP_WRFIFO_RST_OFFSET (BANNER_DESP_WRFIFO_REG_SPACE_OFFSET + 0x00000000)
#define BANNER_DESP_WRFIFO_SR_OFFSET (BANNER_DESP_WRFIFO_REG_SPACE_OFFSET + 0x00000004)
#define BANNER_DESP_WRFIFO_DATA_SPACE_OFFSET (0x00000200)
#define BANNER_DESP_WRFIFO_DATA_OFFSET (BANNER_DESP_WRFIFO_DATA_SPACE_OFFSET + 0x00000000)

/**
 * Write Packet FIFO Masks
 * -- WRFIFO_FULL_MASK  : write packet fifo full condition
 * -- WRFIFO_AF_MASK    : write packet fifo almost full condition
 * -- WRFIFO_DL_MASK    : write packet fifo deadlock condition
 * -- WRFIFO_SCL_MASK   : write packet fifo vacancy scaling enabled
 * -- WRFIFO_WIDTH_MASK : write packet fifo encoded data port width
 * -- WRFIFO_DREP_MASK  : write packet fifo DRE present
 * -- WRFIFO_VAC_MASK   : write packet fifo vacancy
 * -- WRFIFO_RESET      : write packet fifo reset
 */
#define WRFIFO_FULL_MASK (0x80000000UL)
#define WRFIFO_AF_MASK (0x40000000UL)
#define WRFIFO_DL_MASK (0x20000000UL)
#define WRFIFO_SCL_MASK (0x10000000UL)
#define WRFIFO_WIDTH_MASK (0x0E000000UL)
#define WRFIFO_DREP_MASK (0x01000000UL)
#define WRFIFO_VAC_MASK (0x00FFFFFFUL)
#define WRFIFO_RESET (0x0000000A)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a BANNER_DESP register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the BANNER_DESP device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void BANNER_DESP_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define BANNER_DESP_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a BANNER_DESP register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the BANNER_DESP device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 BANNER_DESP_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define BANNER_DESP_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Reset write packet FIFO of BANNER_DESP to its initial state.
 *
 * @param   BaseAddress is the base address of the BANNER_DESP device.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void BANNER_DESP_mResetWriteFIFO(Xuint32 BaseAddress)
 *
 */
#define BANNER_DESP_mResetWriteFIFO(BaseAddress) \
 	Xil_Out32((BaseAddress)+(BANNER_DESP_WRFIFO_RST_OFFSET), WRFIFO_RESET)

/**
 *
 * Check status of BANNER_DESP write packet FIFO module.
 *
 * @param   BaseAddress is the base address of the BANNER_DESP device.
 *
 * @return  Status is the result of status checking.
 *
 * @note
 * C-style signature:
 * 	bool BANNER_DESP_mWriteFIFOFull(Xuint32 BaseAddress)
 * 	Xuint32 BANNER_DESP_mWriteFIFOVacancy(Xuint32 BaseAddress)
 *
 */
#define BANNER_DESP_mWriteFIFOFull(BaseAddress) \
 	((Xil_In32((BaseAddress)+(BANNER_DESP_WRFIFO_SR_OFFSET)) & WRFIFO_FULL_MASK) == WRFIFO_FULL_MASK)
#define BANNER_DESP_mWriteFIFOVacancy(BaseAddress) \
 	(Xil_In32((BaseAddress)+(BANNER_DESP_WRFIFO_SR_OFFSET)) & WRFIFO_VAC_MASK)

/**
 *
 * Write 32 bit data to BANNER_DESP write packet FIFO module.
 *
 * @param   BaseAddress is the base address of the BANNER_DESP device.
 * @param   DataOffset is the offset from the data port to write to.
 * @param   Data is the value to be written to write packet FIFO.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void BANNER_DESP_mWriteToFIFO(Xuint32 BaseAddress, unsigned DataOffset, Xuint32 Data)
 *
 */
#define BANNER_DESP_mWriteToFIFO(BaseAddress, DataOffset, Data) \
 	Xil_Out32((BaseAddress) + (BANNER_DESP_WRFIFO_DATA_OFFSET) + (DataOffset), (Xuint32)(Data))

/************************** Function Prototypes ****************************/


/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the BANNER_DESP instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus BANNER_DESP_SelfTest(void * baseaddr_p);

#endif /** BANNER_DESP_H */
