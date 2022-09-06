/****************************************************************
 * Project_Name: 26_FIFO_DataStructer
 * File_name   : fifo.c
 *
 *  Created on: Sep 2, 2022
 *      Author: Eng.Emre ÖZTOKLU
 *
 *****************************************************************/

/*********************  INCLUDES *********************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "fifo.h"

/*********************** TYPEDEF ********************/
/**********************  MACRO **********************/


/******************  DATA_TYPES   ****************/
rx_data_t RX_FIFO[RX_FIFO_SIZE];

volatile rx_data_t * rx_put_pt;
volatile rx_data_t * rx_get_pt;


/*********************  FUNCTIONS ********************/

/* Initialize Fifo*/
void RX_FIFO_init(void){

/*Reset fifo*/
	rx_put_pt = rx_get_pt = &RX_FIFO[0];

}

/* PUT data into RX_FIFO*/
uint8_t put_data_RX_FIFO(rx_data_t data){

	volatile rx_data_t * rx_next_put_pt;  //?

	rx_next_put_pt = rx_put_pt + 1;

	/*Check if at the end*/
	if(rx_next_put_pt ==  &RX_FIFO[RX_FIFO_SIZE]){

		/*Wrap around*/
		rx_next_put_pt = &RX_FIFO[0];
	}

	if(rx_next_put_pt == rx_get_pt){
		return(uint8_t)(RX_FIFO_FAIL);
	}

	/*Put data into fifo*/
	*(rx_put_pt) = data;

	rx_put_pt = rx_next_put_pt;

	return (uint8_t)(RX_FIFO_SUCCESS);
}


/*Get data from fifo*/
uint8_t get_data_RX_FIFO(rx_data_t * data_pt){

	/*Check if fifo is empty*/
	if(rx_put_pt == rx_get_pt){
		/*Fifo empty*/
		return (uint8_t)(RX_FIFO_FAIL);
	}

	/*Get the data*/
	*(data_pt) = *(rx_get_pt++);

	/*Check if at the end*/
	if(rx_get_pt == &RX_FIFO[RX_FIFO_SIZE]){
		/*Wrap around*/
		rx_get_pt = &RX_FIFO[0];
	}

	return (uint8_t) (RX_FIFO_SUCCESS);
}

















