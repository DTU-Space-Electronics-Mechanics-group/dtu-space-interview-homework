/*
 * Copyright (c) 2020-2024 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Original source:
 * https://embedjournal.com/implementing-circular-buffer-embedded-c/
 * https://github.com/goToMain/c-utils/blob/master/src/circbuf.c
 *
 * Modifications by Luca Victoria Bune Jensen <lcbje@dtu.dk>
 * Copyright (C) 2025 Technical University of Denmark
 */

#ifndef CIRCULAR_HIST_BUFFER_H_
#define CIRCULAR_HIST_BUFFER_H_

#include <stdbool.h>
#include "dbg_types.h"

typedef struct {
	char_t * const data;
	uint8_t length;
} line_t;

typedef struct {
	line_t * const buffer;
	int head;
	int tail;
	const int maxlen;
} circ_hist_t;

extern bool circ_hist_is_full(circ_hist_t *c);
extern bool circ_hist_is_empty(circ_hist_t *c);
extern int circ_hist_push(circ_hist_t *c, char_t *data, uint8_t length);
extern int circ_hist_pop(circ_hist_t *c, char_t *data);
extern int circ_hist_squash(circ_hist_t *c);
extern int circ_hist_read(circ_hist_t *c, char_t *data, uint8_t index);
extern line_t* circ_hist_access(circ_hist_t *c, uint8_t index);
extern int circ_hist_length(circ_hist_t *c);

#endif
