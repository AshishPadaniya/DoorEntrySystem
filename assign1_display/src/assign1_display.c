#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <errno.h>

#include "mystruct.h"


int main (int argc, char* argv[]) {

	Display msg;
	int displayCID;
	int rplyMsg = 0;
	printf("The display is running as PID: %d\n", getpid());

	displayCID = ChannelCreate(0);

	while (1) {
		int rcid = MsgReceive(displayCID, &msg, sizeof(msg), NULL);
		if (rcid == -1) {
			printf("\nError receiving message from Controller \n");
			return EXIT_FAILURE;
		}
		if(strcmp(msg.person.command, "exit") == 0) {
			printf("Exiting Display.\n");
			break;
		}
		else if(strcmp(msg.person.command, "ls") == 0) {
			printf("Person scanned ID, ID = %d\n", msg.person.person_id);
		}
		else if(strcmp(msg.person.command, "rs") == 0) {
			printf("Person scanned ID, ID = %d\n", msg.person.person_id);
		}
		else if (strcmp(msg.person.command, "ws") == 0){
			printf("Person weight, Weight = %d\n", msg.person.weight);

		}else{
			printf("%s\n", outMessage[msg.index]);
		}

		int rpid = MsgReply(rcid, 1, &rplyMsg, sizeof(rplyMsg));
		if (rpid == -1) {
			printf("\nError replying to Controller \n");
			return EXIT_FAILURE;
		}
	}

	 ChannelDestroy(displayCID);
   return EXIT_SUCCESS;
}
