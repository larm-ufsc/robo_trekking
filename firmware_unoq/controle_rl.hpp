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

#endif