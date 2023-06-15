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

/****************
 *   Defines	*
 ****************/

#define BT_NUMBERS		4
#define MENU_NUMBERS	4

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
#define GENERATOR_NOMINAL_A		1.0

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
    int menu_selection;
    int x;

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
