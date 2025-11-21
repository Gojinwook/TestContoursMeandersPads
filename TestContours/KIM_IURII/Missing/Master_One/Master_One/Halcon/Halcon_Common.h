/**
 * \copyright (C) Synapse Imaging 2023
 *
 * @File Name
 *      Halcon_Common.h
 *
 * @Summary
 *
 * @Description
 *
 *
 * @authors Iurii Kim
 * @version 1.0
 * @date 2023.05.25
 */
#pragma once
 /* ************************************************************************** */
 /* Section: Included Files                                                    */
 /* ************************************************************************** */
#define _DATA_TEST_1_
// #define _DATA_TEST_2_
// #define _DATA_TEST_3_

#ifdef _MASTER_ONE_TEST
	#ifdef _DATA_TEST_1_
		#define TEST_CALL_1(x) x;
	#else
		#define TEST_CALL_1(x)
	#endif

	#ifdef _DATA_TEST_2_
		#define TEST_CALL_2(x) x;
	#else
		#define TEST_CALL_2(x)
	#endif

	#ifdef _DATA_TEST_3_
		#define TEST_CALL_3(x) x;
	#else
		#define TEST_CALL_3(x)
	#endif

	#include "..\Common.h"
	#define TIMER_CALL(x) x; Get_Delta_Micros();
#else
	#include "HalconCpp.h"
	#include "HDevThread.h"
	#define DEBUG_CALL(x)
	#define TEST_CALL_1(x)
	#define TEST_CALL_2(x)
	#define TEST_CALL_3(x)

	using namespace HalconCpp;
	using namespace std;
#endif


#define M_PI_P2       6.28318530717958647692f



/* ************************************************************************** */
/* Section: Data types and constants										  */
/* ************************************************************************** */




/* ************************************************************************** */
/* End of file                                                                */
/* ************************************************************************** */
