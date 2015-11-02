#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/times.h>
#include <pthread.h>
#include "fifo.h"

fifo_t queue;
int nbytes;

char *buffer[255];

void error(char *s){
	perror(s);
	exit(EXIT_FAILURE);
}

void* counter_func(){
	while(1){
		char *message[255];
		/*pthread_mutex_lock(&queue.resource_mutex);
		printf("%i\n",(queue.blocked_id[queue.blockedHead]!=0));
		printf("SSTRING: %i\n", fifo_status(&queue));
		if ((queue.blocked_id[queue.blockedHead]!=0) && fifo_status(&queue)){
			printf("BLOCKED AND NEW MESSAGE\n");
			//fifo_rem_string(&queue, &message);
		  	MsgReply(fifo_rem_blocked_id(&queue), 0, &queue.fifo[queue.fifoHead], strlen(queue.fifo[queue.fifoHead]));
		}
		pthread_mutex_unlock(&queue.resource_mutex);*/
		delay(1000);
	}
}

int io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb){
	char *buf;

	// Set number of bytes
	_IO_SET_WRITE_NBYTES(ctp, msg->i.nbytes);

	buf = (char *) malloc(msg->i.nbytes+1);
	if (buf == NULL){
		return(ENOMEM);
	}

	resmgr_msgread(ctp, buf, msg->i.nbytes, sizeof(msg->i));
	buf [msg->i.nbytes] = '\0';
	//printf("Received %d bytes = '%s'\n", msg->i.nbytes, buf);

	pthread_mutex_lock(&queue.resource_mutex);
	if ((queue.blocked_id[queue.blockedHead]!=0)){
		MsgReply(fifo_rem_blocked_id(&queue), 0, buf, msg->i.nbytes+1);
	}else{
		fifo_add_string(&queue, buf);
		printf("STRING ADDED\n");
	}
	pthread_mutex_unlock(&queue.resource_mutex);

	free(buf);

	return(_RESMGR_NPARTS(0));
}

int io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb){
	int nleft, nparts, status;//nbytes
	int nonblock;
	//char *buffer[255];

	pthread_mutex_lock(&queue.resource_mutex);
	if (!fifo_status(&queue)){
		pthread_mutex_unlock(&queue.resource_mutex);
		if((status = iofunc_read_verify(ctp, msg, ocb, &nonblock)) != EOK)
			return(status);

		if(nonblock){
			return(EAGAIN);
		}else{
			printf("BLOCKED ADDED\n");
			fifo_add_blocked_id(&queue, ctp->rcvid);
			return(_RESMGR_NOREPLY);
		}
	}

	fifo_rem_string(&queue, &buffer);
	pthread_mutex_unlock(&queue.resource_mutex);

	//printf(buffer);

	nleft = ocb->attr->nbytes - ocb->offset;
	nbytes = min(msg->i.nbytes, nleft);
	if (nbytes > 0){
		SETIOV(ctp->iov, buffer + ocb->offset, 255);
		_IO_SET_READ_NBYTES(ctp, 255);

		ocb->offset += nbytes;
		nparts = 1;
	}else{
		_IO_SET_READ_NBYTES(ctp, 0);
		nparts = 0;
	}

	return (_RESMGR_NPARTS(nparts));
}

int main(int argc, char *argv[]) {
     dispatch_t              *dpp;
     resmgr_attr_t           resmgr_attr;
     dispatch_context_t      *ctp;
     resmgr_connect_funcs_t  connect_funcs;
     resmgr_io_funcs_t       io_funcs;
     iofunc_attr_t           io_attr;

     pthread_t counter_thread;
     init_fifo(&queue);
     pthread_create(&counter_thread, NULL, &counter_func, NULL);

     printf("Start resource manager\n");



     // create dispatch.
     if (!(dpp = dispatch_create()))
    	 error("dispatch_create()");

     // initialize resource manager attributes.
     memset(&resmgr_attr, 0, sizeof(resmgr_attr));
     resmgr_attr.nparts_max = 1;
     resmgr_attr.msg_max_size = 2048;

     // set standard connect and io functions.
     iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_funcs,
    		 	 	  _RESMGR_IO_NFUNCS, &io_funcs);
     iofunc_attr_init(&io_attr, S_IFNAM | 0666, 0, 0);
     io_attr.nbytes = strlen(buffer)+1;

     io_funcs.write = io_write;
     io_funcs.read = io_read;

     // establish resource manager
     if (resmgr_attach(dpp, &resmgr_attr, "/dev/myresource",
         _FTYPE_ANY, 0, &connect_funcs, &io_funcs, &io_attr) < 0)
    	 error("resmgr_attach()");

     // wait forever, handling messages.
     ctp = dispatch_context_alloc(dpp);
     while(1)
     {
        if (!(ctp = dispatch_block(ctp)))
        	error("dispatch_block()");
        dispatch_handler(ctp);
     }

     pthread_join(&counter_thread, NULL);

     exit(EXIT_SUCCESS);
}
