//
// Created by Sona on 5/3/2026 AD.
//
#ifndef DEBUG_H
#define DEBUG_H

/*
 * -------------------------------------------------------------
 * Public interface for debug module.
 * -------------------------------------------------------------
 */

void set_debug_level(int debug_level);

int dprintf(int debug_level, const char *fmt, ...);

#endif