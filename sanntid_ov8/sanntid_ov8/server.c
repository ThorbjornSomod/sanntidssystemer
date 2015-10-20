#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/dispatch.h>
#include <sys/mman.h>
#include <sys/times.h>
#include <server.h>
#include <shared_memory.h>

int set_priority(int priority){

	int policy;

	struct sched_param param;

	//check priority in range

	if (priority < 1 || priority > 63) return 1;

	//set priority

	pthread_getschedparam(pthread_self(), &policy, &param);

	param.sched_priority = priority;

	return pthread_setschedparam(pthread_self(), policy, &param);

}

int get_priority(){

	int policy;

	struct sched_param param;

	//get priority

	pthread_getschedparam(pthread_self(), &policy, &param);

	return param.sched_curpriority;

}

void* create_server(){

	set_priority(3);
	int msg[1];
	int chan_id = ChannelCreate(_NTO_CHF_FIXED_PRIORITY);
	printf("Server: Channel Created (%d) \n", chan_id);
	struct _msg_info* mi;
	while(1){
		int msg_id = MsgReceive(chan_id, msg, sizeof(msg), mi);
		printf("Server: Message id: %i\n", msg_id);
		printf("Server: Message received serverside: %i \n", msg[0]);
		int reply = 5;

		MsgReply(msg_id, 0, &reply, sizeof(reply));
	}
}

void* create_client(){

	int buf[1];

	int pid = read_memory();
	printf("Client: %i\n", pid);

	int chan_id = ConnectAttach(0, pid, 1, 0, 0);
	printf("Client: Connected to server (%i) \n", chan_id);

	sleep(1);

	int msg = 8;
	int status = MsgSend(chan_id, &msg, sizeof(msg), buf, sizeof(buf));

	printf("Client: Message received clientside: %i (%i)\n", buf[0], status);

	ConnectDetach(chan_id);

}

void* create_client_A(){

	int buf[1];

	set_priority(1);
	int pid = read_memory();
	printf("Client: %i\n", pid);

	int chan_id = ConnectAttach(0, pid, 1, 0, 0);
	printf("Client A: Connected to server (%i) \n", chan_id);

	sleep(1);

	int msg = 10;
	int status = MsgSend(chan_id, &msg, sizeof(msg), buf, sizeof(buf));

	printf("Client: Message received at client A: %i (%i)\n", buf[0], status);

	ConnectDetach(chan_id);

}

void* create_client_B(){

	int buf[1];
	set_priority(2);
	int pid = read_memory();
	printf("Client: %i\n", pid);

	int chan_id = ConnectAttach(0, pid, 1, 0, 0);
	printf("Client B: Connected to server (%i) \n", chan_id);

	sleep(1);

	int msg = 9;
	int status = MsgSend(chan_id, &msg, sizeof(msg), buf, sizeof(buf));

	printf("Client: Message received at client B: %i (%i)\n", buf[0], status);

	ConnectDetach(chan_id);

}

void* create_client_C(){

	int buf[1];
	set_priority(4);
	int pid = read_memory();
	printf("Client: %i\n", pid);

	int chan_id = ConnectAttach(0, pid, 1, 0, 0);
	printf("Client C: Connected to server (%i) \n", chan_id);

	sleep(1);

	int msg = 8;
	int status = MsgSend(chan_id, &msg, sizeof(msg), buf, sizeof(buf));

	printf("Client: Message received at client C: %i (%i)\n", buf[0], status);

	ConnectDetach(chan_id);

}

void* create_client_D(){

	int buf[1];
	set_priority(5);
	int pid = read_memory();
	printf("Client: %i\n", pid);

	int chan_id = ConnectAttach(0, pid, 1, 0, 0);
	printf("Client C: Connected to server (%i) \n", chan_id);

	sleep(1);

	int msg = 7;
	int status = MsgSend(chan_id, &msg, sizeof(msg), buf, sizeof(buf));

	printf("Client: Message received at client D: %i (%i)\n", buf[0], status);

	ConnectDetach(chan_id);

}































