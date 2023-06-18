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
#include "lcd16x2.h"


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
void app_menu_main(app_t * app){

	lcd16x2_setCursor(0,0);
	lcd16x2_printf(app->menu_name[0]);
	lcd16x2_setCursor(1,0);
	lcd16x2_printf("%d-> ", app->menu_selection);
	lcd16x2_printf(app->menu_name[app->menu_selection]);

	if(BT_PRESS(BT_UP)){
		BT_RESET(BT_UP);
		app->menu_selection ++;
	}
	if(BT_PRESS(BT_DOWN)){
		BT_RESET(BT_DOWN);
		app->menu_selection --;
	}
	limiter_saturation(app->menu_selection, 1, MENU_NUMBERS-1)

	if(BT_PRESS(BT_MENU)){
		BT_RESET(BT_MENU);
		app->menu_function = app->menu_selection;
		lcd16x2_clear();
	}

	if(BT_PRESS(BT_ENTER)){
		BT_RESET(BT_ENTER);
	}
}

/**
 * @brief
 *
 * Descrição mais detalhada da função exemploFuncao.
 *
 * @param parametro Descrição do parâmetro.
 */
void app_menu_monitor(app_t * app){

	lcd16x2_setCursor(0,0);
	lcd16x2_printf(app->menu_name[app->menu_selection]);

	if(BT_PRESS(BT_MENU)){
		BT_RESET(BT_MENU);
		app->menu_function = 0;
		lcd16x2_clear();
	}
}

/**
 * @brief Apresenta os parâmetros do menu e permite ajustá-los.
 *
 * Esta função exibe o nome do menu e o parâmetro selecionado na tela LCD de 16x2.
 * Também exibe o valor do parâmetro na segunda linha da tela.
 * Os botões UP e DOWN são usados para navegar entre os parâmetros.
 * O botão MENU é usado para sair do modo de ajuste de parâmetros.
 *
 * @param app Ponteiro para a estrutura do aplicativo.
 */
void app_menu_parameters(app_t * app){

	lcd16x2_setCursor(0,0);
	lcd16x2_printf(app->menu_name[app->menu_selection]);

	lcd16x2_setCursor(1,0);
	lcd16x2_printf(app->param_name[app->param_index]);

	lcd16x2_setCursor(1,8);
	lcd16x2_printf("%d", (int) * app->param_ptr[app->param_index]);

	if(BT_PRESS(BT_UP)){
		BT_RESET(BT_UP);
		app->param_index ++;
	}
	if(BT_PRESS(BT_DOWN)){
		BT_RESET(BT_DOWN);
		app->param_index --;
	}

	limiter_saturation(app->param_index, 0, PARAMETERS_SIZE-1)

	if(BT_PRESS(BT_MENU)){
		BT_RESET(BT_MENU);
		app->menu_function = 0;
		lcd16x2_clear();
	}
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
	so_filter_update_coeff_lowpass(&app->lpo);
	so_filter_initialize(&app->notch, app->fs, NOTCH_FC, NOTCH_Q, NOTCH_TYPE, NOTCH_WARP);
	so_filter_update_coeff_notch(&app->notch);

    /** Controle V/F **/

	app->ref_freq = 0.0;
	app->modulation_amp = 0.0;
	app->modulation_freq = 0.0;

	limiter_initialize(&app->limiter, app->fs);

	WaveGenerator_update(&app->gerador, app->fs, app->modulation_freq, app->modulation_amp);

    /** Menus **/

	app->menu_selection = 0;
	app->menu_vector[0] = &app_menu_main;
	app->menu_vector[1] = &app_menu_monitor;
	app->menu_vector[2] = &app_menu_parameters;

	strcpy(app->menu_name[0], "Main menu");
	strcpy(app->menu_name[1], "Monitor");
	strcpy(app->menu_name[2], "Parameters");

    /** Parameters **/

	app->param_ptr[0] = &app->lpo.fc;
	strcpy(app->param_name[0], "LPO Fc");

	app->param_ptr[1] = &app->lpo.Q;
	strcpy(app->param_name[1], "LPO Q");

	app->param_ptr[2] = &app->lpo.fc;
	strcpy(app->param_name[2], "Notch Fc");

	app->param_ptr[3] = &app->lpo.Q;
	strcpy(app->param_name[3], "Notch Q");

	app->param_ptr[4] = &app->limiter.rate;
	strcpy(app->param_name[4], "Rate Lim");

	app->param_ptr[5] = &app->ref_freq;
	strcpy(app->param_name[5], "Ref Freq");


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

		app->menu_vector[app->menu_function](app);

		app_isr(app);
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
