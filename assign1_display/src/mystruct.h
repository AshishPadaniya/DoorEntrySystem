

#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_


#define NUM_INPUTS 11	// where n equals the number of input commands that drive the FSM.
				// Count those...
typedef enum {
	    LEFTSCAN = 0,
		RIGHTSCAN = 1,
		LEFTOPEN = 2,
		RIGHTOPEN = 3,
		LEFTCLOSED = 4,
		RIGHTCLOSED = 5,
		GUARDLEFTUNLOCK = 6,
		GUARDRIGHTUNLOCK = 7,
		GUARDRIGHTLOCK = 8,
		GUARDLEFTLOCK = 9,
		WEIGHTSCALE = 10,

} Input;

const char *inMessage[NUM_INPUTS] = {
		"ls",
		"rs",//"ls", "rs", "lo", "ro", "lc", "rc", "glu", "gru", "gll", "grl", "ws"
		"lo",
		"ro",
		"lc",
		"rc",
		"glu",
		"gru",
		"gll",
		"grl",
		"ws"

	//TODO :: each input command. For example, "ls"
};

#define NUM_OUTPUTS 12	// where n equals the number of output messages from the FSM.
typedef enum {
	//TODO :: assign an enum value, one for each output message from the FSM
	LSCAN = 0,
	RSCAN = 1,
	LOPEN = 2,
	ROPEN = 3,
	LCLOSED = 4,
	RCLOSED = 5,
	G_LEFT_UNL = 6,
	G_RIGHT_UNL = 7,
	G_RIGHT_LOCK = 8,
	G_LEFT_LOCK = 9,
	WSCALE = 10,
	WForPer = 11

} Output;

const char *outMessage[NUM_OUTPUTS] = {
	//TODO :: each output message. For example, "Person opened left door"
		"Left Scan",
		"Right Scan",
		"Person opened left door",
		"Person opened right door",
		"Left Closed",
		"Right Closed",
		"Left door unlocked by guard",
		"Right door unlocked by guard",
		"Right door locked by guard",
		"Left door locked by guard",
		"Weight Scale",
		"Waiting for Person..."
};


// inputs client sends a Person struct to its server, the controller
typedef struct {
	int person_id;
	int weight;
	char command [128];

	//TODO :: fields for person's ID (int), weight (int), direction (inbound or outbound),
	//			and some way to remember what state the Person is in. Suppose the Person in "Left Scan" state.
	//			You need a way to represent that.
} Person;


// controller client sends a Display struct to its server, the display
typedef struct {
	Person person;
	int index;
	int inUse;
	//TODO :: fields for the output message and the Person. For the output message, I used an int, which
	//			is the index into the outMessages array. That way I don't pass strings in my messages.
	//			The Person field is needed, as some output message require information from the Person.
	//			Specifically, those messages that display the Person's ID and weight.
} Display;

#endif /* DOOR_ENTRY_H_ */
