/*
 * check_receive_string.h
 *
 *  Created on: Dec 3, 2024
 *      Author: PC
 */

#ifndef INC_CHECK_RECEIVE_STRING_H_
#define INC_CHECK_RECEIVE_STRING_H_

#include "main.h"
#include "string.h"
#include "stdio.h"
#include <stdint.h>
#include <stdlib.h>

#define BUFFER_LEN 50

#define IDLE        0
#define FIND_START  1
#define FIND_END    2

extern UART_HandleTypeDef huart2;
extern uint8_t cmd_flag;
extern char* cmd_str;


void uart_init();


void check_str_fsm();










#endif /* INC_CHECK_RECEIVE_STRING_H_ */
