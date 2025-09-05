/**
 * @file IDHUOperationalModes.c
 *
 * @author FW Profile code generator version 6.0
 * @date Created on: Aug 6 2025 14:27:9
 */

/* IDHUOperationalModes function definitions */
#include "ASW_main.h"

#include <stdlib.h>

/**
 * Action on the transition from Initial State to CHOICE1.
 * init system
 * @param smDesc the state machine descriptor
 */
void init_function(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;

}

/**
 * Action on the transition from STANDBY to Final State.
 * enter safe mode
 * @param smDesc the state machine descriptor
 */
void go_to_safe(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;
	
}

/**
 * Action on the transition from MEMORY_MANAGEMENT to Final State.
 * enter boot
 * @param smDesc the state machine descriptor
 */
void go_to_boot(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;
	
}

/**
 * Guard on the transition from STANDBY to CALIBRATION.
 * CALIB TC flag
 * @param smDesc the state machine descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwSmBool_t guard_calib_mode(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;

	//This guard should check if the CALIB TC flag is set via telecommand
	return 0; // Placeholder for actual condition check
	
}

/**
 * Guard on the transition from STANDBY to OBSERVATION.
 * OBS TC flag
 * @param smDesc the state machine descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwSmBool_t guard_obs_mode(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;

	//This guard should check if the OBS TC flag is set via telecommand
	return 0; // Placeholder for actual condition check
	
}

/**
 * Guard on the transition from STANDBY to TEST.
 * TEST TC flag
 * @param smDesc the state machine descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwSmBool_t guard_test_mode(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;

	//This guard should check if the TEST TC flag is set via telecommand
	return 0; // Placeholder for actual condition check
	
}

/**
 * Guard on the transition from CHOICE1 to MEMORY_MANAGEMENT.
 * MEM MGT TC flag
 * @param smDesc the state machine descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwSmBool_t guard_mem_mgt(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;

	//This guard should check if the MEM MGT TC flag is set via telecommand
	return 0; // Placeholder for actual condition check
	
}

/**
 * Guard on the transition from CHOICE1 to STANDBY.
 * TC/AUTO
 * @param smDesc the state machine descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwSmBool_t guard_standby_mode(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;

	//This guard should either check if the STANDBY TC flag is set via telecommand or if the system just started up
	return 1; // Placeholder for actual condition check, it will autmatically transition to STANDBY upon startup
	
}

/**
 * Guard on the transition from MEMORY_MANAGEMENT to Final State.
 * FDIR flag
 * @param smDesc the state machine descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwSmBool_t guard_fdir(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;

	//This guard should check if the FDIR flag has been set
	return 0; // Placeholder for actual condition check
	
}

/**
 * Guard on the transition from MEMORY_MANAGEMENT to Final State.
 * BOOT TC flag
 * @param smDesc the state machine descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwSmBool_t guard_boot(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;

	//This guard should check if the BOOT TC flag is set via telecommand
	return 0; // Placeholder for actual condition check
	
}

/**
 * Guard on the transition from CHOICE2 to STANDBY.
 * low severity FDIR
 * @param smDesc the state machine descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwSmBool_t guard_fdir_severity(FwSmDesc_t smDesc)
{(void)smDesc;

	SYS_DESC_t* sys_desc = (SYS_DESC_t*) smDesc->smData;

	//This guard should check if the FDIR low severity flag has been set (meaning that the system can still operate in STANDBY mode) otherwise it will go to SAFE mode
	return 0; // Placeholder for actual condition check
	
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwSmDesc_t OperationalSmCreate(void* smData)
{
	const FwSmCounterU2_t N_OUT_OF_STANDBY = 5;	/* The number of transitions out of state STANDBY */
	const FwSmCounterU2_t N_OUT_OF_CALIBRATION = 2;	/* The number of transitions out of state CALIBRATION */
	const FwSmCounterU2_t N_OUT_OF_OBSERVATION = 2;	/* The number of transitions out of state OBSERVATION */
	const FwSmCounterU2_t N_OUT_OF_TEST = 2;	/* The number of transitions out of state TEST */
	const FwSmCounterU2_t CHOICE1 = 1;		/* The identifier of choice pseudo-state CHOICE1 in State Machine IDHUOperationalModes */
	const FwSmCounterU2_t N_OUT_OF_CHOICE1 = 2;	/* The number of transitions out of the choice-pseudo state CHOICE1 */
	const FwSmCounterU2_t N_OUT_OF_MEMORY_MANAGEMENT = 3;	/* The number of transitions out of state MEMORY_MANAGEMENT */
	const FwSmCounterU2_t CHOICE2 = 2;		/* The identifier of choice pseudo-state CHOICE2 in State Machine IDHUOperationalModes */
	const FwSmCounterU2_t N_OUT_OF_CHOICE2 = 2;	/* The number of transitions out of the choice-pseudo state CHOICE2 */

	/** Create state machine smDesc */
	FW_SM_INST(smDesc,
		5,	/* NSTATES - The number of states */
		2,	/* NCPS - The number of choice pseudo-states */
		19,	/* NTRANS - The number of transitions */
		3,	/* NACTIONS - The number of state and transition actions */
		8	/* NGUARDS - The number of transition guards */
	);
	FwSmInit(&smDesc);

	/** Configure the state machine smDesc */
	FwSmSetData(&smDesc, smData);
	FwSmAddState(&smDesc, IDHUOperationalModes_STANDBY, N_OUT_OF_STANDBY, NULL, NULL, NULL, NULL);
	FwSmAddState(&smDesc, IDHUOperationalModes_CALIBRATION, N_OUT_OF_CALIBRATION, NULL, NULL, NULL, NULL);
	FwSmAddState(&smDesc, IDHUOperationalModes_OBSERVATION, N_OUT_OF_OBSERVATION, NULL, NULL, NULL, NULL);
	FwSmAddState(&smDesc, IDHUOperationalModes_TEST, N_OUT_OF_TEST, NULL, NULL, NULL, NULL);
	FwSmAddChoicePseudoState(&smDesc, CHOICE1, N_OUT_OF_CHOICE1);
	FwSmAddState(&smDesc, IDHUOperationalModes_MEMORY_MANAGEMENT, N_OUT_OF_MEMORY_MANAGEMENT, NULL, NULL, NULL, NULL);
	FwSmAddChoicePseudoState(&smDesc, CHOICE2, N_OUT_OF_CHOICE2);
	FwSmAddTransIpsToCps(&smDesc, CHOICE1, &init_function);
	FwSmAddTransStaToSta(&smDesc, GUARD_CALIB_TC, IDHUOperationalModes_STANDBY, IDHUOperationalModes_CALIBRATION, NULL, &guard_calib_mode);
	FwSmAddTransStaToSta(&smDesc, GUARD_OBS_TC, IDHUOperationalModes_STANDBY, IDHUOperationalModes_OBSERVATION, NULL, &guard_obs_mode);
	FwSmAddTransStaToSta(&smDesc, GUARD_TEST_TC, IDHUOperationalModes_STANDBY, IDHUOperationalModes_TEST, NULL, &guard_test_mode);
	FwSmAddTransStaToSta(&smDesc, GUARD_MEM_MGT_TC, IDHUOperationalModes_STANDBY, IDHUOperationalModes_MEMORY_MANAGEMENT, NULL, &guard_mem_mgt);
	FwSmAddTransStaToFps(&smDesc, GUARD_FDIR, IDHUOperationalModes_STANDBY, &go_to_safe, &guard_fdir);
	FwSmAddTransStaToSta(&smDesc, GUARD_STANDBY_TC, IDHUOperationalModes_CALIBRATION, IDHUOperationalModes_STANDBY, NULL, &guard_standby_mode);
	FwSmAddTransStaToCps(&smDesc, GUARD_FDIR, IDHUOperationalModes_CALIBRATION, CHOICE2, NULL, &guard_fdir);
	FwSmAddTransStaToSta(&smDesc, GUARD_STANDBY_TC, IDHUOperationalModes_OBSERVATION, IDHUOperationalModes_STANDBY, NULL, &guard_standby_mode);
	FwSmAddTransStaToCps(&smDesc, GUARD_FDIR, IDHUOperationalModes_OBSERVATION, CHOICE2, NULL, &guard_fdir);
	FwSmAddTransStaToSta(&smDesc, GUARD_STANDBY_TC, IDHUOperationalModes_TEST, IDHUOperationalModes_STANDBY, NULL, &guard_standby_mode);
	FwSmAddTransStaToCps(&smDesc, GUARD_FDIR, IDHUOperationalModes_TEST, CHOICE2, NULL, &guard_fdir);
	FwSmAddTransCpsToSta(&smDesc, CHOICE1, IDHUOperationalModes_MEMORY_MANAGEMENT, NULL, &guard_mem_mgt);
	FwSmAddTransCpsToSta(&smDesc, CHOICE1, IDHUOperationalModes_STANDBY, NULL, &guard_standby_mode);
	FwSmAddTransStaToSta(&smDesc, GUARD_STANDBY_TC, IDHUOperationalModes_MEMORY_MANAGEMENT, IDHUOperationalModes_STANDBY, NULL, &guard_standby_mode);
	FwSmAddTransStaToFps(&smDesc, GUARD_FDIR, IDHUOperationalModes_MEMORY_MANAGEMENT, &go_to_safe, &guard_fdir);
	FwSmAddTransStaToFps(&smDesc, GUARD_BOOT_TC, IDHUOperationalModes_MEMORY_MANAGEMENT, &go_to_boot, &guard_boot);
	FwSmAddTransCpsToSta(&smDesc, CHOICE2, IDHUOperationalModes_STANDBY, NULL, &guard_fdir_severity);
	FwSmAddTransCpsToFps(&smDesc, CHOICE2, &go_to_safe, &guard_fdir_severity);

	return &smDesc;
}

