#ifndef CONTROLE_RL_HPP
#define CONTROLE_RL_HPP

/**
 * @brief Guarda os dados usados pelo controlador RL.
 *
 * As distancias validas serao normalizadas entre 0 e 1:
 * 0 representa zero centimetro e 1 representa 400 centimetros.
 *
 * Tracao e direcao representam comandos suavizados,
 * nao medicoes de velocidade ou angulo das rodas.
 *
 * sensoresValidos indica se as tres leituras podem ser usadas.
 * Enquanto for false, as distancias nao devem alimentar a politica.
 */
struct ObservacaoRL {
    float frente = 0.0f;
    float esquerda = 0.0f;
    float direita = 0.0f;

    float tracaoAplicada = 0.0f;
    float direcaoAplicada = 0.0f;

    bool sensoresValidos = false;
};

/**
 * @brief Calcula o próximo comando por interpolação linear entre o atual e o alvo.
 *
 * @param atual Último comando aplicado.
 * @param alvo Comando que se deseja atingir.
 * @param fator Fração da diferença a percorrer nesta atualização, entre 0 e 1.
 *              Com 0, mantém o valor atual. Com 1, chega ao alvo de uma vez.
 * @return Novo comando interpolado.
 */
inline float lerpRL(float atual, float alvo, float fator) {
    return atual + (alvo - atual) * fator;
}

/**
 * @brief Guarda os últimos comandos suavizados de tração e direção do Nikko.
 */
struct ComandoRL {
    float tracao = 0.0f;   ///< Tração normalizada entre 0 e 1.
    float direcao = 0.0f;  ///< Direção normalizada entre -1 e 1. Zero é o centro.
};

/**
 * @brief Normaliza uma leitura de ultrassom para a escala usada no Webots.
 * @param cm Distância medida em centímetros.
 * @param[out] normalizada Referência à variável onde será armazenada
 *             a distância dividida por 400, ou zero em caso de falha.
 * @return true quando a leitura está entre 4 e 400 cm.
 */
inline bool normalizarDistanciaRL(float cm, float& normalizada) {
    constexpr float alcanceCm = 400.0f;

    if (cm >= 4.0f && cm <= alcanceCm) {
        normalizada = cm / alcanceCm;
        return true;
    }

    normalizada = 0.0f;
    return false;
}

/**
 * @brief Monta a observação com as três distâncias e os dois comandos suavizados.
 * sensoresValidos só fica true quando os três sensores têm leituras válidas.
 */
inline ObservacaoRL montarObservacaoRL(float frenteCm, float esquerdaCm, float direitaCm,
                                      float tracaoAplicada, float direcaoAplicada) {
    ObservacaoRL obs;

    const bool frenteValida   = normalizarDistanciaRL(frenteCm,   obs.frente);
    const bool esquerdaValida = normalizarDistanciaRL(esquerdaCm, obs.esquerda);
    const bool direitaValida  = normalizarDistanciaRL(direitaCm,  obs.direita);

    obs.sensoresValidos = frenteValida && esquerdaValida && direitaValida;
    obs.tracaoAplicada = tracaoAplicada;
    obs.direcaoAplicada = direcaoAplicada;

    return obs;
}

#endif