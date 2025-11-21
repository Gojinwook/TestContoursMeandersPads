/**
 * \copyright (C) Synapse 2023
 *
 * @File Name
 *      FLT_All.h
 *
 * @Summary
 *
 * @Description
 *
 *
 * @authors Igor Dunin-Barkowski, Iurii Kim
 * @version 1.0
 * @date 2024.05.19
 */
#pragma once
 /* ************************************************************************** */
 /* Section: Included Files                                                    */
 /* ************************************************************************** */
#include "Halcon_Common.h"

/* ************************************************************************** */
/* Section: Data types and constants										  */
/* ************************************************************************** */

 
 /* ************************************************************************** */
/* Section: Prototype functions                                               */
/* ************************************************************************** */
// PUBLIC
void Filter_Line_Thickness(HTuple hv_pWG_line, HTuple hv_dWmin_line, int line_len,
	HTuple hv_move_avg_h, HTuple hv_min_len_direct, HTuple *hv_dWmin_Deviation, HTuple *hv_dWmin_Deviation_Avg);
void Filter_Line_Thickness_All(HTuple hv_Pnum, HTuple hv_pWG, HTuple hv_dWmin, HTuple hv_move_avg_h,
	HTuple hv_min_len_direct, HTuple hv_threshold, HTuple hv_threshold_area, 
	std::vector<int64_t>* finde_pos,
	std::vector<double>* finde_val);
// PRIVATE


/* ************************************************************************** */
/* End of file                                                                */
/* ************************************************************************** */
