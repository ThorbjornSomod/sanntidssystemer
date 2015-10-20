/*
 * server.h
 *
 *  Created on: 20. okt. 2015
 *      Author: thorbjos
 */

#ifndef SERVER_H_
#define SERVER_H_

void* create_server();
void* create_client();
void* create_client_A();
void* create_client_B();
void* create_client_C();
void* create_client_D();
int set_priority();
int get_priority();

#endif /* SERVER_H_ */
