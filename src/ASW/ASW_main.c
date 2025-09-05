#include "ASW_main.h"
#include "glue.h"

static SYS_DESC_t sys_desc; /*!< Static definition of the system description parent module*/


void cyclic_activities(void)
{
    while(1){
        dbg_terminal_cyclic();
    }
}

/**
 * Initializes the system description structure.
 * 
 * This function initializes the system description structure by calling the initialization functions of all child modules.
 * It sets the value of the pointers to link to the child structures in an object oriented fashion.
 * 
 * @return SYS_DESC_t* Pointer to the system description structure.
*/
SYS_DESC_t* init_sys_desc(void)
{
    sys_desc.operational_sm = OperationalSmCreate(&sys_desc);
    if (FwSmCheckRec(sys_desc.operational_sm) != smSuccess) {
		sys_desc.err_operational_sm = EXIT_FAILURE;
        return &sys_desc;
	}
    sys_desc.err_operational_sm = EXIT_SUCCESS;

    FwSmStart(sys_desc.operational_sm);
    return &sys_desc;
}


/**
 * Main function of the ASW.
 * 
 * This function initializes the system description structure and calls the cyclic function of the thermal control module.
 * 
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * 
 * @return int Exit code of the program.
*/
int main(void)
{
    printf("Hello, ASW!\n");

    /* Initialize the system module tree pointers and data*/
    SYS_DESC_t *sys_desc = init_sys_desc();
    if (sys_desc->err_operational_sm != EXIT_SUCCESS) {
        return EXIT_FAILURE; /* Exit with failure if the operational state machine initialization failed */
    }

    glue_main_init(&sys_desc->sys_1ms_tick);

    cyclic_activities();

    return 0;
}

