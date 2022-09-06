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

float32_t signal_mean(float32_t *sig_src_arr, uint32_t sig_length);
float32_t signal_variance(float32_t* sig_src_arr, float32_t sig_mean, uint32_t sig_length);
float32_t signal_std(float32_t sig_variance);

/*Number of points mean_filter*/
void moving_average(float32_t * sig_src_arr, float32_t* sig_out_arr, uint32_t signal_length, uint32_t filter_points);


#ifdef __cplusplus
}
#endif

#endif /* FILTERS_H_ */
