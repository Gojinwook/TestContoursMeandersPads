/**
 * \copyright (C) Synapse Imaging 2023
 *
 * @File Name
 *      Scratch_Matching.h
 *
 * @Summary
 *
 * @Description
 *
 *
 * @authors Igor Dunin-Barkowski, Iurii Kim
 * @version 1.0
 * @date 2023.05.23
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
void How_To_Run_Scratch_Matching ();
void Scratch_Matching (HObject *ho_Img_Im, int th_min, int th_max, HObject* ho_Region_Out);

/* ************************************************************************** */
/* End of file                                                                */
/* ************************************************************************** */
