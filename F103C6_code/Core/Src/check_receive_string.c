/*
 * check_receive_string.c
 *
 *  Created on: Dec 3, 2024
 *      Author: PC
 */

#include "check_receive_string.h"



uint8_t dataRx;
uint8_t receive_flag = 0;
uint8_t buffer[BUFFER_LEN];
uint16_t buffer_index;
uint8_t buffer_flag = 0;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == huart2.Instance){
		if(buffer_index == 0 && dataRx == '!')
		{
			receive_flag = 1;
		}

		if(receive_flag){
			buffer[buffer_index++] = dataRx;

			if(dataRx == '#'){
				receive_flag = 0;
				buffer_index = 0;
				buffer_flag = 1;
			}
		}
		HAL_UART_Transmit(&huart2, &dataRx, 1, 10);

		HAL_UART_Receive_IT(&huart2, &dataRx, 1);
	}

}

void uart_init(){
	HAL_UART_Receive_IT(&huart2, &dataRx, 1);
}



uint8_t state = IDLE;
uint16_t current_index = 0;
uint16_t start_index = 0;
uint16_t end_index = 0;

uint8_t cmd_flag = 0;
char* cmd_str;




// find index function
uint8_t find_char(char* str, uint16_t* index, char character){
    if(str[(*index)] == character){
        return 1;
    }
    (*index)++;
    return 0;
}
// cut string function
char* substring(char* str, uint16_t start, uint16_t end){
    uint16_t len = end - start + 1;
    char* sub = (char*)malloc(len+1);// them 1 cho cho '\0'

    strncpy(sub, str + start, len);
    sub[len] = '\0';
    return sub;
}


void check_str_fsm(){
	 switch(state){
	 	 case IDLE:
	 		 if(buffer_flag)
	 		 {
	 			 state = FIND_START;
	 			current_index = 0;
	 		 }
	 		 break;
	 	 case FIND_START:

	 		 if(find_char((char*)buffer, &current_index, '!')){
	 			 start_index = current_index;
	 			 state = FIND_END;
	 			 break;
	 		 }

	 		 // kiem tra het chuoi nhung khogn thay
	 		 if(buffer[current_index] == '\0'){
	 			 state = IDLE;
	 			 buffer_flag = 0;
	 		 }
	 		 break;
	 	 case FIND_END:
	 		 if(find_char((char*)buffer, &current_index, '#')){
	 			 end_index = current_index;
	 			 buffer_flag = 0;
	 			 // cắt cmd_string ra từ string
	 			 cmd_str = substring((char*)buffer, start_index+1, end_index-1);
	 			 cmd_flag = 1;
	 			 state = IDLE;
	 			 break;
	 		 }

	         // kiem tra het chuoi nhung khogn thay
	 		 if(buffer[current_index] == '\0'){
	 			 state = IDLE;
	 			 buffer_flag = 0;
	 		 }
	 		 break;
	 }

}





