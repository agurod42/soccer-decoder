// DISTRIBUTIONS - C header for sampling from common probability distributions.
 
// MIT License

// Copyright (c) 2018 Mark Sheppard
 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// NOTE:
//   These functions all use the C standard library function rand() to generate
//   pseudo-random numbers; you MUST seed this yourself using the C standard
//   library function srand().

#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#ifdef _cplusplus
extern c {
#endif

#include <stdlib.h>
#include <assert.h>
#include <math.h>

int   randomBernoulli   (float p);
float randomBeta        (float alpha, float beta);
int   randomBinomial    (int n, float p);
float randomExponential (float lambda);
float randomGamma       (float alpha, float beta);
float randomNormal      (float mu, float sigma);
int   randomPoisson     (float lambda);
float randomUniform     (float a, float b);

// Returns 1 with probability p and 0 with probability (1 - p)
int randomBernoulli(float p) {
    assert(p >= 0.0f);
    assert(p <= 1.0f);

    float u = randomUniform(0.0f, 1.0f);

    if (p == 0.0f) {
        return 0;
    } else if (p == 1.0f) {
        return 1;
    } else {
        return u < p;
    }
}

// Returns a random float sampled from a beta distribution with shape
// (alpha, beta)
float randomBeta(float alpha, float beta) {
    assert(alpha > 0.0f);
    assert(beta > 0.0f);

    float x = randomGamma(alpha, 1);
    float y = randomGamma(beta, 1);

    return x / (x + y);
}

// Returns a random integer sampled from a binomial distribution with n trials
// and per-trial success probability p
int randomBinomial(int n, float p) {
    assert(n >= 0);
    assert(p >= 0.0f && p <= 1.0f);

    int successes = 0;

    int i;
    for (i = 0; i < n; i++) {
        successes += randomBernoulli(p);
    }

    return successes;
}

// Returns a random float sampled from an exponential distribution with given
// rate lambda.
float randomExponential(float lambda) {
    assert(lambda > 0.0f);

    // Inverse transform sampling

    float u = randomUniform(0.0f, 1.0f);
    return -log(u) / lambda;
}

// Returns a random float sampled from a gamma distribution with shape alpha and
// rate beta
float randomGamma(float alpha, float beta) {
    assert(alpha > 0.0f);
    assert(beta > 0.0f);

    // Use the Marsaglia and Tsang (2000) method to generate Z ~ Gamma(alpha, 1)

    float d = alpha - 1.0f / 3.0f;
    float c = 1.0f / sqrt(9.0f * d);

    float z = 0.0f;

    for (;;) {
        float x = 0.0f;
        float v = 0.0f;

        do {
            x = randomNormal(0, 1);
            v = 1.0f + c * x;
        } while (v <= 0);

        v = pow(v, 3.0f);
        float u = randomUniform(0.0f, 1.0f);

        if (u < 1.0f - 0.0331f * pow(x, 4.0f)) {
            z = d * v;
            break;
        }

        if (log(u) < 0.5 * pow(x, 2.0f) + d * (1 - v + log(v))) {
            z = d * v;
            break;
        }
    }

    // Scale to X ~ Gamma(alpha, beta)

    return z / beta;
}

// Returns a random float sampled from a normal dsitribution with given mean and
// standard deviation
float randomNormal(float mu, float sigma) {

    // Box-Muller transformation from uniform to normal distribution

    float u1 = randomUniform(0.0f, 1.0f);
    float u2 = randomUniform(0.0f, 1.0f);

    float z0 = sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);
    return mu + z0 * sigma;
}

// Returns a random integer sampled from the Poisson distribution with rate
// lambda
int randomPoisson(float lambda) {
    assert(lambda > 0.0f);

    // Use Knuth's algorithm to generate the Poisson value

    float L = exp(-lambda);
    float k = 0;
    float p = 1.0f;

    do {
        k++;
        p *= randomUniform(0.0f, 1.0f);
    } while(p > L);

    return k - 1;
}

// Returns a random float sampled from a uniform distribution within the range
// [a, b]
float randomUniform(float a, float b) {
    assert(a < b);

    float u = (float) rand() / (float) RAND_MAX;
    return a + u * (b - a);
}

#ifdef __cplusplus
}
#endif

#endif