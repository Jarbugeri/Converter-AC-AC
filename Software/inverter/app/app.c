/**
 * @file app.c
 * @brief Header file contendo as funções.
 *
 * Este arquivo contém as funções utilizadas no programa app.
 */

/****************
 *   Includes	*
 ****************/

#include "app.h"

/****************
 *  Functions	*
 ****************/

/**
 * @brief
 *
 * Descrição mais detalhada da função exemploFuncao.
 *
 * @param parametro Descrição do parâmetro.
 */
void menu_1(app_t * app){
	app->x = 1;
}

/**
 * @brief
 *
 * Descrição mais detalhada da função exemploFuncao.
 *
 * @param parametro Descrição do parâmetro.
 */
void menu_2(app_t * app){
	app->x = 2;
}

/**
 * @brief Descrição breve da função exemploFuncao.
 *
 * Descrição mais detalhada da função exemploFuncao.
 *
 * @param parametro Descrição do parâmetro.
 * @return void
 */
void app_init(app_t * app) {

    /** Configs **/

	app->fs = 10000.0;
	app->ts = 1.0 / app->fs;

    /** Bus voltage **/

	so_filter_initialize(&app->lpo  , app->fs, LPO_FC  , LPO_Q  , LPO_TYPE  , LPO_WARP  );
	so_filter_initialize(&app->notch, app->fs, NOTCH_FC, NOTCH_Q, NOTCH_TYPE, NOTCH_WARP);

    /** Controle V/F **/

	app->ref_freq = 0.0;
	app->modulation_amp = 0.0;
	app->modulation_freq = 0.0;

	limiter_initialize(&app->limiter, app->fs);

	WaveGenerator_update(&app->gerador, app->fs, app->modulation_freq, app->modulation_amp);

    /** Menus **/

	app->menu_selection = 0;
	app->menu_vector[0] = &menu_1;
	app->menu_vector[1] = &menu_2;

    /** Buttons **/


}

void app_loop(app_t * app){
	while (1){

		app->button[0].state = HAL_GPIO_ReadPin(BT1_GPIO_Port, BT1_Pin);
		app->button[1].state = HAL_GPIO_ReadPin(BT2_GPIO_Port, BT2_Pin);
		app->button[2].state = HAL_GPIO_ReadPin(BT3_GPIO_Port, BT3_Pin);
		app->button[3].state = HAL_GPIO_ReadPin(BT4_GPIO_Port, BT4_Pin);

		if(!app->button[0].state) app->button[0].flag = 1;
		if(!app->button[1].state) app->button[1].flag = 1;
		if(!app->button[2].state) app->button[2].flag = 1;
		if(!app->button[3].state) app->button[3].flag = 1;

		app->menu_vector[app->menu_selection](app);

	}
}

void app_isr(app_t * app){

    /** Bus voltage **/

	app->vbus.max = fmaxf(app->vbus.raw, app->vbus.max);
	app->vbus.min = fmaxf(app->vbus.raw, app->vbus.min);

	so_filter_run(&app->lpo,   app->vbus.raw);
	app->vbus.filtered = so_filter_run(&app->notch, app->lpo.states.y0);

    /** Controle V/F **/

	limiter_rate_run(&app->limiter, app->ref_freq);

	app->modulation_freq = app->limiter.output;
	app->modulation_amp  = GENERATOR_NOMINAL_FS / app->limiter.output;

	WaveGenerator_update(&app->gerador, app->fs, app->modulation_freq, app->modulation_amp);
	WaveGenerator_sine_run(&app->gerador);

	app->sa = app->gerador.a;
	app->sb = app->gerador.b;
	app->sc = app->gerador.c;

    /** PWM **/
}
