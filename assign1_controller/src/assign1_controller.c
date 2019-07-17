#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <errno.h>

#include "../../assign1_display/src/mystruct.h"

void userchoice();
void ls();
void rs();
void ws();
void glu();
void gru();
void lo();
void ro();
void lc();
void gll();
void rc();
void grl();

void (*function) () = userchoice;
void message_to_display();
void exit_program();


int left_or_right = 0;
int rcvid;
int controllerCID;
int connectToDisplay;

Display dis;

int main (int argc, char* argv[]) {

	pid_t displayPid = atoi(argv[1]);

	//	Left is 0 right is  1

	controllerCID = ChannelCreate (0);
	if (controllerCID == -1) {
		perror("\nFailed to create the channel. Exiting. ");
		exit (EXIT_FAILURE);
	}
	connectToDisplay = ConnectAttach (0, displayPid, 1, 0, 0);
	if (connectToDisplay == -1) {
		printf("\nCannot Connect to Display. Exiting ");
		return EXIT_FAILURE;
	}
	printf("The controller is running as PID: %d\n", getpid());
	printf("Waiting for Person...\n");

	while (1) {
		(*function)();
	}

	ChannelDestroy(controllerCID);
	return EXIT_SUCCESS;
}

void userchoice(){

	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);

	if(strcmp("exit" ,dis.person.command) == 0) {
		exit_program();
	}

	if (strcmp("ls" , dis.person.command) == 0){
		left_or_right = 0;
		dis.index = LSCAN;
		message_to_display();
		function = ls;
	}
	else if (strcmp("rs" , dis.person.command) == 0){
		left_or_right = 1;
		dis.index = RSCAN;
		function = rs;
		message_to_display();
	}
	MsgReply(rcvid, EOK, NULL, 0);
}

void ls(){

	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);

	if (strcmp("exit", dis.person.command) == 0){
		exit_program();
	}
	if (strcmp("glu" , dis.person.command) == 0){
		dis.index = G_LEFT_UNL;
		function = glu;
		message_to_display();
	}
	MsgReply(rcvid, EOK, NULL, 0);
}


void glu(){
	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);
	//MsgReply(rcvid, EOK, NULL, 0);
	if (strcmp("exit", dis.person.command) == 0){
		exit_program();
	}
	if (strcmp("lo" , dis.person.command) == 0){
		dis.index = LOPEN;
		function = lo;
		message_to_display();
	}
	MsgReply(rcvid, EOK, NULL, 0);
}


void lo(){
	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);
	if (strcmp("exit", dis.person.command) == 0){
		exit_program();
	}
	if (left_or_right == 0){
		if (strcmp("ws" , dis.person.command) == 0){
			dis.index = WSCALE;
			function = ws;
			message_to_display();
		}
	}
	else if (left_or_right == 1){
		if (strcmp("lc" , dis.person.command) == 0){
			dis.index = LCLOSED;
			function = lc;
			message_to_display();
		}
	}
	MsgReply(rcvid, EOK, NULL, 0);
}

void ws(){
	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);

	if (strcmp("exit", dis.person.command) == 0){
		exit_program();
	}
	if (left_or_right == 0){
		if (strcmp("lc" , dis.person.command) == 0){
			dis.index = LCLOSED;
			function = lc;
			message_to_display();
		}
	}
	else if (left_or_right == 1){
		if (strcmp("rc" , dis.person.command) == 0){
			dis.index = RCLOSED;
			function = rc;
			message_to_display();
		}
	}
	MsgReply(rcvid, EOK, NULL, 0);

}

void lc(){
	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);

	if (strcmp("exit", dis.person.command) == 0){
		exit_program();
	}
	if (strcmp("gll" , dis.person.command) == 0){
		dis.index = G_LEFT_LOCK;
		function = gll;
		message_to_display();
	}
	MsgReply(rcvid, EOK, NULL, 0);
}

void gll(){
	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);

	if (strcmp("exit", dis.person.command) == 0){
		exit_program();
	}
	if (strcmp("gru" , dis.person.command) == 0){
		dis.index = G_RIGHT_UNL;
		function = gru;
		message_to_display();
	}
	MsgReply(rcvid, EOK, NULL, 0);
}

void gru(){
	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);

	if (strcmp("exit", dis.person.command) == 0){
		exit_program();
	}
	if (strcmp("ro" , dis.person.command) == 0){
		dis.index = ROPEN;
		function = ro;
		message_to_display();
	}
	MsgReply(rcvid, EOK, NULL, 0);
}



void rs(){
	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);

	if (strcmp("exit", dis.person.command) == 0){
		exit_program();
	}
	if (strcmp("gru" , dis.person.command) == 0){
		dis.index = G_RIGHT_UNL;
		function = gru;
		message_to_display();
	}
	MsgReply(rcvid, EOK, NULL, 0);
}


void ro(){
	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);

	if (strcmp("exit", dis.person.command) == 0){
		exit_program();
	}
	if (left_or_right == 1){
		if (strcmp("ws" , dis.person.command) == 0){
			dis.index = WSCALE;
			function = ws;
			message_to_display();
		}
	}
	else if (left_or_right == 0){
		if (strcmp("rc" , dis.person.command) == 0){
			dis.index = RCLOSED;
			function = rc;
			message_to_display();
		}
	}
	MsgReply(rcvid, EOK, NULL, 0);
}

void rc(){

	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);
	if (strcmp("exit", dis.person.command) == 0){
			exit_program();
		}
	if (strcmp("grl" , dis.person.command) == 0){
		dis.index = G_RIGHT_LOCK;
		function = grl;
		message_to_display();
		dis.index = WForPer;
		message_to_display();
	}
	MsgReply(rcvid, EOK, NULL, 0);
}



void grl(){

	rcvid = MsgReceive (controllerCID, &dis.person, sizeof (dis.person), NULL);

	if (strcmp("exit", dis.person.command) == 0){
		exit_program();
	}
	if (left_or_right == 0){
		function = userchoice;
		message_to_display();
	}
	else if (left_or_right == 1){
		if (strcmp("glu" , dis.person.command) == 0){
			dis.index = G_LEFT_UNL;
			function = glu;
			message_to_display();
		}
	}
	MsgReply(rcvid, EOK, NULL, 0);
}



void message_to_display(){
	MsgSend (connectToDisplay, &dis, sizeof (dis), NULL, 0);
}

void exit_program(){
	printf("Exiting Controller.\n");
	strcpy(dis.person.command, "exit");
	MsgSend (connectToDisplay, &dis, sizeof (dis), NULL, 0);
	exit(EXIT_SUCCESS);
}

