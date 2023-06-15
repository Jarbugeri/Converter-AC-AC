/*
 * limiter.h
 *
 *  Created on: 31 de jan de 2023
 *      Author: Jose
 */

#ifndef LIMITER_H_
#define LIMITER_H_

/**************
 *  Includes  *
 **************/

/*************
 *  Defines  *
 *************/

#define limiter_saturation(in, LIMITE_MIN, LIMITE_MAX)  \
                if (in >= LIMITE_MAX)  in = LIMITE_MAX; \
                if (in <= LIMITE_MIN)  in = LIMITE_MIN; \

/*************
 *  Structs  *
 *************/

typedef struct _limiter_t_
{
    //!< Parametros de configuracao do pi
    float fs;       //!< Frequencia de amostragem
    float ts;       //!< Periodo de amostragem, calculado na inicializacao

    //!< Taxa de limite
    float rate;     //!< Taxa de limite para o limitador de taxa
    float limit_min;
    float limit_max;

    //!< Estados
    float input;			//!< Entrada da estrutura
    float output_limited;   //!< Saida da estrutura
    float output;   		//!< Saida da estrutura



}limiter_t;

/************************
 * Functions prototypes *
 ************************/

/**
 * @brief Inicializa limiter
 *
 * @param limiter  Ponteiro para a estrutura do limiter
 * @param fs    Frequencia de atualizacao do limiter
 */
void limiter_initialize(limiter_t *limiter, float fs);

/**
 * @brief Reseta o limiter
 *
 * @param limiter  Ponteiro para a estrutura do limiter
 */
void limiter_reset(limiter_t *limiter);

/**
 * @brief Executa o limiter
 *
 * @param limiter  Ponteiro para a estrutura do limiter
 * @param input    Entrada do limiter
 * @return         Saída do limiter
 */
float limiter_run(limiter_t *limiter, float input);

/**
 * @brief Limitador de taxa.
 *
 * @param[in] limiter Ponteiro para a estrutura do limiter.
 * @param[in] input Entrada para o limitador de taxa.
 * @return Saída limitada pelo limite de taxa.
 */
float limiter_rate_run(limiter_t *limiter, float input);

#endif /* LIMITER_H_ */
