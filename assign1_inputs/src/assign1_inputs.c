#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <errno.h>

#include "../../assign1_display/src/mystruct.h"

Person per;

int main(int argc, char *argv[]) {

	pid_t controllerPid = atoi(argv[1]);

	int cidToController = ConnectAttach (0, controllerPid, 1, 0, 0);


	if (cidToController == -1) {
		printf("Cannot Connect to Server. Please try again\n");
		return EXIT_FAILURE;
	}
	while (1) {

		printf("\nEnter the device (ls= left scan, rs= right scan, ws= weight scale, lo =left open, ro=right open, lc = "
				"left closed, rc = right closed , gru = guard right unlock, grl = guard right lock, gll=guard left lock,"
				"glu = guard left unlock)\n");

		scanf("%s", per.command);


		if(strcmp(per.command, "exit") == 0) {
			strcpy(per.command, "exit");
			MsgSend (cidToController, &per, sizeof (per), NULL, 0);
			break;

		}

		else if(strcmp(per.command, "ws") == 0) {

			printf("Enter the Person's weight: \n");
			scanf("%d", &per.weight);
		}



		else if(strcmp(per.command, "ls") == 0 || strcmp(per.command, "rs") == 0) {

			printf("Enter the Person's ID: \n");
			scanf("%d", &per.person_id);

		}

		MsgSend (cidToController, &per, sizeof (per), NULL, 0);

	}
	ConnectDetach(cidToController);
	return EXIT_SUCCESS;
}
