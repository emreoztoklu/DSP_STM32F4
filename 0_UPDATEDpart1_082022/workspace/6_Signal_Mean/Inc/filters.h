/**********************************************************
* project_name : 6_Signal_Mean
* file_name    : filters.h
*
* date         : Aug 18, 2022
* file_path    : /6_Signal_Mean/Inc/filters.h
*
* Autor        : Eng.Emre ÖZTOKLU
***********************************************************/

#ifndef FILTERS_H_
#define FILTERS_H_

#ifdef __cplusplus
extern "C" {
#endif





/*********************************************************/
/*Data types*/
/*********************************************************/





/*********************************************************/
/*function prototypes*/
/*********************************************************/

float32_t mean_filter(float32_t *sig_src_arr, uint32_t sig_length);



#ifdef __cplusplus
}
#endif

#endif /* FILTERS_H_ */
