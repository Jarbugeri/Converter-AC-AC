/**
 * @file app.h
 * @brief Header file contendo as declarações de funções.
 *
 * Este arquivo contém as declarações de funções utilizadas no programa app.
 */

#ifndef APP_H
#define APP_H

/****************
 *   Includes	*
 ****************/

#include "math.h"
#include "main.h"
#include "libs.h"
#include <string.h>
#include <stdio.h>
#include "lcd16x2.h"
#include "stm32f1xx_hal_adc.h"		// ADC functions

/****************
 *   Defines	*
 ****************/

#define BT_NUMBERS		4
#define MENU_NUMBERS	3

#define BT_ENTER		0
#define BT_UP			1
#define BT_DOWN			2
#define BT_MENU			3

#define BT_PRESS(BT)	app->button[BT].state && app->button[BT].flag
#define BT_RESET(BT)	app->button[BT].flag = 0

#define PARAMETERS_SIZE	7
/** Filter  **/

#define LPO_FC				30.0
#define LPO_Q				1.0
#define LPO_TYPE			SO_FILTER_LOWPASS
#define LPO_WARP			PRE_WARP_OFF

#define NOTCH_FC			120.0
#define NOTCH_Q				12.0
#define NOTCH_TYPE			SO_FILTER_NOTCH
#define NOTCH_WARP			PRE_WARP_ON

#define GENERATOR_NOMINAL_FS	60.0
#define GENERATOR_NOMINAL_TS	1.0 / GENERATOR_NOMINAL_FS
#define GENERATOR_NOMINAL_A		1.0

/**  ADC gains  **/

#define ADC_REF_VOLTAGE 	3.3f
#define ADC_BITS_NUMBER		12
#define ADC_SCALE_FACTOR 	(ADC_REF_VOLTAGE / ((1 << ADC_BITS_NUMBER) - 1))
#define ADC_AMPOP_GAIN		168.0f
#define ADC_VOLTAGE_GAIN	ADC_SCALE_FACTOR * ADC_AMPOP_GAIN



/****************
 *   Extern 	*
 ****************/

extern ADC_HandleTypeDef hadc1;

/****************
 *   Structs	*
 ****************/

typedef struct _button_t_{
    int flag; 		//!< Indicador de sinalização do botão
    int state; 		//!< Estado atual do botão
} button_t;

typedef struct _measurement_t_{
    float raw; 		//!< Valor cru da medição
    float max; 		//!< Valor máximo da medição
    float min; 		//!< Valor mínimo da medição
    float filtered; //!< Valor filtrado da medição
} measurement_t;

typedef struct _app_t_
{
    /** Configs **/

    float fs;       //!< Frequencia de amostragem
    float ts;       //!< Periodo de amostragem, calculado na inicializacao
    float timer;

    /** Bus voltage **/

    measurement_t 	vbus;
    so_filter_t		lpo;
    so_filter_t		notch;

    /** Controle V/F **/

    WaveGenerator_t gerador;
    limiter_t	    limiter;
    float 			ref_freq;
    float			modulation_amp;
    float			modulation_freq;
    float			sa;
    float			sb;
    float			sc;

    /** Menus **/

    void (*menu_vector[MENU_NUMBERS])();
    char menu_name[MENU_NUMBERS][16];
    int menu_selection;
    int menu_function;

    /** Parameters **/
    int		param_index;
    float* 	param_ptr[PARAMETERS_SIZE];
    char 	param_name[PARAMETERS_SIZE][16];
    /** Buttons **/

    button_t button[BT_NUMBERS];
}app_t;

/****************
 *   Functions	*
 ****************/

void app_init(app_t * app);

void app_loop(app_t * app);

void app_isr(app_t * app);

#endif /* APP_H */
