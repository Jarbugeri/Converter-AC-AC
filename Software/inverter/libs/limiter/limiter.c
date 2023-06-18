/*
 * limiter.c
 *
 *  Created on: 31 de jan de 2023
 *      Author: Jose
 */

/**************
 *  Includes  *
 **************/

#include "limiter.h"

/*************
 * Functions *
 *************/

/**
 * @brief Inicializa limiter
 *
 * @param limiter  Ponteiro para a estrutura do limiter
 * @param fs    Frequencia de atualizacao do limiter
 */
void limiter_initialize(limiter_t *limiter, float fs, float rate)
{
    limiter->fs = fs;
    limiter->ts = 1.0 / fs;
    limiter->input = 0.0;
    limiter->output = 0.0;
    limiter->rate = rate;
}

/**
 * @brief Reseta o limiter
 *
 * @param limiter  Ponteiro para a estrutura do limiter
 */
void limiter_reset(limiter_t *limiter)
{
    limiter->input = 0.0;
    limiter->output = 0.0;
}

/**
 * @brief Executa o limiter
 *
 * @param limiter  Ponteiro para a estrutura do limiter
 * @param input    Entrada do limiter
 * @return         Saída do limiter
 */
float limiter_run(limiter_t *limiter, float input)
{
    limiter->input = 0.0;

    // Aplica a saturação nos limites mínimo e máximo
    limiter_saturation(limiter->input, limiter->limit_min, limiter->limit_max);

    // Atualiza a saída do limiter
    limiter->output = limiter->input;

    return limiter->output;
}

/**
 * @brief Limitador de taxa.
 *
 * @param[in] limiter Ponteiro para a estrutura do limiter.
 * @param[in] input Entrada para o limitador de taxa.
 * @return Saída limitada pelo limite de taxa.
 */
float limiter_rate_run(limiter_t *limiter, float input)
{
    float delta    = input - limiter->output;
    float maxDelta = limiter->rate * limiter->ts;

    if (delta > maxDelta) {
        input = limiter->output + maxDelta;
    } else if (delta < -maxDelta) {
        input = limiter->output - maxDelta;
    }

    limiter->output = input;
    return limiter->output;
}
