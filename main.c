/*
 * main.c
 *
 *  Created on: 2016 Feb 16 21:58:10
 *  Author: DominikH
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdlib.h>

/*
 * >>> ["0x%x"%(x*64) for x in range(31)]
 ['0x0', '0x40', '0x80', '0xc0', '0x100', '0x140', '0x180', '0x1c0', '0x200', '0x240', '0x280', '0x2c0', '0x300', '0x340', '0x380', '0x3c0', '0x400', '0x440', '0
 x480', '0x4c0', '0x500', '0x540', '0x580', '0x5c0', '0x600', '0x640', '0x680', '0x6c0', '0x700', '0x740', '0x780']
 */

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

typedef enum
{
	NOT_ACTIVATED, ACTIVATED
} sendCanFrames_t;
sendCanFrames_t sendCanFrames = NOT_ACTIVATED;

int main(void)
{

#define messageObjectsMax (30)

	const CAN_NODE_LMO_t * messageObjects[31] =
	{ NULL, &CAN_NODE_0_LMO_01_Config, &CAN_NODE_0_LMO_02_Config,
			&CAN_NODE_0_LMO_03_Config, &CAN_NODE_0_LMO_04_Config,
			&CAN_NODE_0_LMO_05_Config, &CAN_NODE_0_LMO_06_Config,
			&CAN_NODE_0_LMO_07_Config, &CAN_NODE_0_LMO_08_Config,
			&CAN_NODE_0_LMO_09_Config, &CAN_NODE_0_LMO_10_Config,
			&CAN_NODE_0_LMO_11_Config, &CAN_NODE_0_LMO_12_Config,
			&CAN_NODE_0_LMO_13_Config, &CAN_NODE_0_LMO_14_Config,
			&CAN_NODE_0_LMO_15_Config, &CAN_NODE_0_LMO_16_Config,
			/* &CAN_NODE_0_LMO_17_Config,*/ &CAN_NODE_0_LMO_18_Config,
			&CAN_NODE_0_LMO_19_Config, &CAN_NODE_0_LMO_20_Config,
			&CAN_NODE_0_LMO_21_Config, &CAN_NODE_0_LMO_22_Config,
			&CAN_NODE_0_LMO_23_Config, &CAN_NODE_0_LMO_24_Config,
			&CAN_NODE_0_LMO_25_Config, &CAN_NODE_0_LMO_26_Config,
			&CAN_NODE_0_LMO_27_Config, &CAN_NODE_0_LMO_28_Config,
			&CAN_NODE_0_LMO_29_Config, &CAN_NODE_0_LMO_30_Config,
			&CAN_NODE_0_LMO_31_Config
	};

	DAVE_STATUS_t status;

	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if (status == DAVE_STATUS_FAILURE)
	{
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while (1U)
		{

		}
	}

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while (1U)
	{
		if (sendCanFrames == ACTIVATED)
		{
			sendCanFrames = NOT_ACTIVATED;

			DIGITAL_IO_SetOutputHigh(&LED1);
			for (int messageObject = 2; messageObject < messageObjectsMax;
					messageObject++)
			{
				CAN_NODE_MO_Transmit(messageObjects[messageObject]);
			}
			DIGITAL_IO_SetOutputLow(&LED1);
		}
		else if (!DIGITAL_IO_GetInput(&Button1) )
		{
			sendCanFrames = ACTIVATED;
		}
	}
}

void CanRxInterruptHandler(void)
{
	/* Check for Node error */
	if (CAN_NODE_GetStatus(&CAN_NODE_0) & XMC_CAN_NODE_STATUS_LAST_ERROR_CODE)
	{
		XMC_DEBUG("Something failed\n");
	}
	else if (CAN_NODE_MO_GetStatus(&CAN_NODE_0_LMO_01_Config)
			& XMC_CAN_MO_STATUS_RX_PENDING)
	{
		static int oldCommand = 0x42;
		int currentCommand;
		/* Read the received Message object and stores in Request_Node_LMO_02_Config*/
		CAN_NODE_MO_Receive(&CAN_NODE_0_LMO_01_Config);
		currentCommand = CAN_NODE_0_LMO_01_Config.mo_ptr->can_data_byte[7];

		if ( currentCommand != oldCommand )
		{
			oldCommand = currentCommand;
			sendCanFrames = ACTIVATED;
		}
	}
}
