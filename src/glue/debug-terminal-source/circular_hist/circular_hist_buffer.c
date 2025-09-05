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

#include <string.h>
#include "circular_hist_buffer.h"
#include "dbg_cfg.h"

bool circ_hist_is_full(circ_hist_t *c)
{
	int next = (c->head + 1) % c->maxlen;
	if (next == c->tail)	// if the head + 1 == tail, circular buffer is full
		return true;
	return false;
}

bool circ_hist_is_empty(circ_hist_t *c)
{
	if (c->head == c->tail)  // if the head == tail, we don't have any data to pop
		return true;
	return false;
}

int circ_hist_push(circ_hist_t *c, char_t *data, uint8_t length)
{
	int next;

	next = (c->head + 1) % c->maxlen;	// next is where head will point to after this write.

	if (next == c->tail)	// if the head + 1 == tail, circular buffer is full
		return -1;

	memcpy(c->buffer[c->head].data, data, DBG_CFG_LINE_LENGTH);	// Load data
	c->buffer[c->head].length = length;							// Load data length
	c->head = next;												// Move head to next data offset.
	return 0;  // return success to indicate successful push.
}

int circ_hist_pop(circ_hist_t *c, char_t *data)
{
	int next;

	if (c->head == c->tail)  // if the head == tail, we don't have any data to pop
		return -1;

	next = c->tail + 1;  // next is where tail will point to after this pop.
	if(next >= c->maxlen)
		next = 0;

	uint8_t length = c->buffer[c->tail].length;					// Load data length
	memcpy(data, c->buffer[c->tail].data, DBG_CFG_LINE_LENGTH);	// Load data
	c->tail = next;			 									// Move tail to next data offset.
	return length;  // return non-negative number to indicate successful pop, that number being length.
}

int circ_hist_squash(circ_hist_t *c)
{
	int next;

	if (c->head == c->tail)  // if the head == tail, we don't have any data to squash
		return -1;

	next = c->tail + 1;  // next is where tail will point to after this squash.
	if(next >= c->maxlen)
		next = 0;

	c->tail = next;	// Move tail to next data offset.
	return 0; // return success to indicate successful squash.
}

int circ_hist_read(circ_hist_t *c, char_t *data, uint8_t index)
{
	// Read position. We start with the newest added item and go back as the index increases
	uint8_t read_pos = (c->head + c->maxlen - 1 - index) % c->maxlen;

	if( ( (read_pos < c->tail ) && (c->tail  < c->head ) ) || // If the buffer is contiguous and the read misses below, or
		( (c->tail  < c->head ) && (c->head  < read_pos) ) || // if the buffer is contiguous and the read misses above, or
		( (c->head  < read_pos) && (read_pos < c->tail ) ) )  // if the buffer is wrapping and the read misses in between,
		return -1; // then we don't have any data to read at that spot.

	uint8_t length = c->buffer[read_pos].length;					// Load data length
	memcpy(data, c->buffer[read_pos].data, DBG_CFG_LINE_LENGTH);	// Load data
	return length;  // return non-negative number to indicate successful read, that number being length.
}

line_t* circ_hist_access(circ_hist_t *c, uint8_t index)
{
	// Read position. We start with the newest added item and go back as the index increases
	uint8_t read_pos = (c->head + c->maxlen - 1 - index) % c->maxlen;

	if( ( (read_pos < c->tail ) && (c->tail  < c->head ) ) || // If the buffer is contiguous and the read misses below, or
		( (c->tail  < c->head ) && (c->head  < read_pos) ) || // if the buffer is contiguous and the read misses above, or
		( (c->head  < read_pos) && (read_pos < c->tail ) ) )  // if the buffer is wrapping and the read misses in between,
		return ((line_t *)0); // then we don't have any data to read at that spot.
	
	return &(c->buffer[read_pos]);
}

int circ_hist_length(circ_hist_t *c){
	return (c->head + c->maxlen - c->tail) % c->maxlen;
}
