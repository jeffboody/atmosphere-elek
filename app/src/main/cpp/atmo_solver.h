/*
 * Copyright (c) 2025 Jeff Boody
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef atmo_solver_H
#define atmo_solver_H

#include "libcc/cc_jobq.h"
#include "libvkk/vkk_platform.h"
#include "libvkk/vkk.h"

typedef enum
{
	ATMO_SOLVER_STATUS_STOPPED  = 0,
	ATMO_SOLVER_STATUS_RUNNING  = 1,
	ATMO_SOLVER_STATUS_STOPPING = 2,
} atmo_solverStatus_e;

typedef struct atmo_solverParam_s
{
	float Rp;
	float Ra;

	float density_scale_height_rayleigh;
	float density_scale_height_mie;

	float phase_g_mie;

	float beta_r_rayleigh;
	float beta_g_rayleigh;
	float beta_b_rayleigh;

	float beta_mie;

	float spectral_irradiance_r;
	float spectral_irradiance_g;
	float spectral_irradiance_b;

	float exposure;

	float spectral_to_rgb_r;
	float spectral_to_rgb_g;
	float spectral_to_rgb_b;

	uint32_t integration_steps;

	uint32_t k; // base-1

	uint32_t texture_width;
	uint32_t texture_height;
	uint32_t texture_depth;
} atmo_solverParam_t;

typedef struct atmo_solver_s
{
	vkk_engine_t* engine;

	atmo_solverStatus_e status;

	float progress;

	vkk_image_t** image_array;

	atmo_solverParam_t param;

	pthread_mutex_t mutex;
	cc_jobq_t* jobq;
} atmo_solver_t;

atmo_solver_t*      atmo_solver_new(vkk_engine_t* engine);
void                atmo_solver_delete(atmo_solver_t** _self);
void                atmo_solver_defaultParam(atmo_solver_t* self,
                                             atmo_solverParam_t* param);
void                atmo_solver_currentParam(atmo_solver_t* self,
                                             atmo_solverParam_t* param);
vkk_image_t*        atmo_solver_image(atmo_solver_t* self,
                                      uint32_t k);
atmo_solverStatus_e atmo_solver_status(atmo_solver_t* self,
                                       float* _progress);
int                 atmo_solver_solve(atmo_solver_t* self,
                                      atmo_solverParam_t* param);
void                atmo_solver_stop(atmo_solver_t* self);

#endif
