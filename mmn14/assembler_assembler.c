#include "assembler.h"

void do_assembler(FILE * fd_input)
{
	/* images (re)initialization */
	 instruction_image = NULL;
	 data_image = NULL;

	/* counters (re)initialization */
	IC = 100; /* instruction counter */
	DC = 0; /* data counter */

	/* do run 1 run 2 */

	/* print into files */

	/* free images */
	free_image(INSTRUCTION_TABLE_TYPE);
	free_image(DATA_TABLE_TYPE);
}
