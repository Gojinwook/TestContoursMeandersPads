/**
 * \copyright (C) Synapse Imaging 2023
 *
 * @File Name
 *      Missing_Pads.h
 *
 * @Summary
 *
 * @Description
 *
 *
 * @authors Igor Dunin-Barkowski, Iurii Kim
 * @version 1.0
 * @date 2023.05.24
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
void How_To_Run_Missing_Pads ();
void InspectPads (HObject ho_Im, HObject ho_Padsd, HObject ho_CPM, HObject ho_ContoursGsm,
	HObject *ho_PadsDefPoint, HObject *ho_ContPadDefsMB, HObject *ho_ContPadDefsSP,
	HTuple hv_thrP, HTuple hv_contsmooth, HTuple hv_thrMB, HTuple hv_thrSP, HTuple hv_minpadborder,
	HTuple hv_win_len, HTuple hv_pad_thresh, HTuple hv_voidlen, HTuple *hv_ndef);
void TeachPads(HObject ho_RegionFlash, HObject ho_RegionG, HObject *ho_PadsM, HObject *ho_Padsd,
	HObject *ho_ContoursG, HObject *ho_ContoursGsm, HObject *ho_CPM, HTuple hv_am,
	HTuple hv_circm, HTuple hv_dilpadG);

// PRIVATE
void Filt_AMM_04(HTuple hv_Input, HTuple hv_Win_Len, HTuple hv_Move_Avg, HTuple hv_thrMB,
	HTuple hv_thrSP, HTuple *hv_Tuple_Avg_CMax, HTuple *hv_Tuple_Avg_CMin, HTuple *hv_Tuple_Avg_MM_Th);
double AMM_Span(double* in_biff, int pos_start, int pos_end, double *s_max, double *s_min);


/* ************************************************************************** */
/* End of file                                                                */
/* ************************************************************************** */
