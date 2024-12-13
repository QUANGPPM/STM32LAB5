/*
 * handle.h
 *
 *  Created on: Dec 3, 2024
 *      Author: PC
 */

#ifndef INC_HANDLE_H_
#define INC_HANDLE_H_

#include "check_receive_string.h"

#define IDLE 0
#define CMD_CHECK 1
#define SEND 2
#define ACK 3
#define RESEND 4

void handle_fsm();


#endif /* INC_HANDLE_H_ */
