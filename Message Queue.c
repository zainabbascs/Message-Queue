#include <sys/wait.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#define TRUE 1
#define FALSE 0
#define BLOCKING 0 // blocking send/receive, msgflg value
#define MYPORT 12345 // unique value to create key
#define FIRST_MSG 0 // receive first message in queue
#define DATA_T 1 // type code for a data message
#define PERMS 0644 // access permission
#define MSG_SIZE 100 // max. size of message
int ret_code;

// the message buffer record
typedef struct msgbuffer{
long mtype; // message type (must be > 0)
char the_message[MSG_SIZE]; // the message
}Message, *Messageptr;
// message queue parameters
key_t myKey; // unique key
int queueId; // message queue identifier
int flags;
size_t msgsize = sizeof(Message);
int main(int argc, char *argv[]){
Messageptr message1;
char msg[MSG_SIZE];
char *msgptr;

// the message buffer record
typedef struct msgbuffer{
long mtype; // message type (must be > 0)
char the_message[MSG_SIZE]; // the message
}Message, *Messageptr;
// message queue parameters
key_t myKey; // unique key
int queueId; // message queue identifier
int flags;
size_t msgsize = sizeof(Message);
int main(int argc, char *argv[]){
Messageptr message1;
char msg[MSG_SIZE];
char *msgptr;

// fork a new process
if(fork()){
// Parent: send a message to the queue
message1 = (Messageptr)malloc(msgsize);
message1->mtype = DATA_T;
strncpy(message1->the_message, msgptr, MSG_SIZE-1);
ret_code = msgsnd(queueId, message1, msgsize, BLOCKING);
printf("Message sent\n");
sleep(2); // sleep before parent cleans up the message queue
}

else{ // Child: read message from queue
sleep(1);
printf("Inside child process\n");
message1 = (Messageptr)malloc(msgsize);
msgrcv(queueId, message1, msgsize, 
FIRST_MSG, BLOCKING);
printf("Child process read message type %d %s",
message1->mtype, message1->the_message);
exit(0);
}
// close the message queue
msgctl(queueId, IPC_RMID, NULL);
return 0;
} /* end main */
