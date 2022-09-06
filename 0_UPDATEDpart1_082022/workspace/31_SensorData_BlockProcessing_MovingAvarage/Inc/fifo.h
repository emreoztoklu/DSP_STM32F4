/**********************************************************
* project_name : 26_FIFO_DataStructer
* file_name    : fifo.h
*
* date         : Sep 2, 2022
* file_path    : /26_FIFO_DataStructer/Inc/fifo.h
*
* Autor        : Eng.Emre ÖZTOKLU
***********************************************************/
#ifndef FIFO_H_
#define FIFO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************  INCLUDES   *******************/
#include <stdint.h>

/*******************  DEFINES   *******************/
#define RX_FIFO_SIZE	300
#define RX_FIFO_FAIL	 0
#define RX_FIFO_SUCCESS  1


/*******************  TYPEDEF   *******************/
typedef uint32_t rx_data_t;



/******************  DATA_TYPES   ****************/





/****************  function prototypes  *************/

/* Initialize Fifo*/
void RX_FIFO_init(void);

/* PUT data into RX_FIFO*/
uint8_t put_data_RX_FIFO(rx_data_t data);

/*Get data from fifo*/
uint8_t get_data_RX_FIFO(rx_data_t * data_pt);




#ifdef __cplusplus
}
#endif

#endif /* FIFO_H_ */
