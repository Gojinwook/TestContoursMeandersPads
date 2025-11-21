#ifndef __APPLE__
#  include "Halcon.h"
#else
#  ifndef HC_LARGE_IMAGES
#    include <HALCON/Halcon.h>
#  else
#    include <HALCONxl/Halcon.h>
#  endif
#endif

#include "halconcpp/HalconCpp.h"
#include "halconcpp/HTuple.h"
using namespace HalconCpp;

extern "C" {

void Filt_AMM_04 (HTuple hv_Input, HTuple hv_Win_Len, HTuple hv_Move_Avg, HTuple hv_thrMB,
	HTuple hv_thrSP, HTuple *hv_Tuple_Avg_CMax, HTuple *hv_Tuple_Avg_CMin, HTuple *hv_Tuple_Avg_MM_Th);
double AMM_Span (double* in_biff, int pos_start, int pos_end, double *s_max, double *s_min);

 /*****************************************************************************/
 /* Herror CIPUserThreshold(proc_handle)
  *****************************************************************************
  * Supply procedure for IPBThreshold(proc_handle)
  *****************************************************************************/
Herror CIPUserFilt_AMM_04(Hproc_handle proc_handle)
{
#define MEDOSIZE    280000

	// input
	Hcpar chv_Win_Len;       //2
	Hcpar chv_Move_Avg;      //3
	Hcpar chv_thrMB;         //4
	Hcpar chv_thrSP;         //5

	INT4_8 n1;
	HINT t1;
	const double* hvi;

	HGetPElemD(proc_handle, 1, CONV_NONE, &hvi, &n1);
	HTuple hv_Input;

	for (int i = 0; i < n1; ++i)
	{
		hv_Input.Append(hvi[i]);
	}

	HGetSPar(proc_handle, 2, DOUBLE_PAR, &chv_Win_Len, 1);
	HGetSPar(proc_handle, 3, DOUBLE_PAR, &chv_Move_Avg, 1);
	HGetSPar(proc_handle, 4, DOUBLE_PAR, &chv_thrMB, 1);
	HGetSPar(proc_handle, 5, DOUBLE_PAR, &chv_thrSP, 1);

	HTuple hv_Win_Len = chv_Win_Len.par.d;
	HTuple hv_Move_Avg = chv_Move_Avg.par.d;      
	HTuple hv_thrMB = chv_thrMB.par.d;
	HTuple hv_thrSP = chv_thrSP.par.d;

	HTuple hv_Tuple_Avg_CMax = 5.0;
	HTuple hv_Tuple_Avg_CMin = 5.1;
	HTuple hv_Tuple_Avg_MM_Th = 5.2;
	//for (int i = 0; i < n1; ++i)
	//{
	//	hv_Tuple_Avg_CMax.Append(hvi[i]);
	//}

	//hv_Tuple_Avg_CMin.Append(hv_Win_Len);
	//hv_Tuple_Avg_CMin.Append(hv_Move_Avg);
	//hv_Tuple_Avg_CMin.Append(hv_thrMB);
	//hv_Tuple_Avg_CMin.Append(hv_thrSP);

	//hv_Tuple_Avg_MM_Th.Append(hv_Win_Len);
	//hv_Tuple_Avg_MM_Th.Append(hv_Move_Avg);
	//hv_Tuple_Avg_MM_Th.Append(hv_thrMB);
	//hv_Tuple_Avg_MM_Th.Append(hv_thrSP);

	Filt_AMM_04 (hv_Input, hv_Win_Len, hv_Move_Avg, hv_thrMB, hv_thrSP, 
                     &hv_Tuple_Avg_CMax, &hv_Tuple_Avg_CMin, &hv_Tuple_Avg_MM_Th);

	Hcpar out1, out2, out3;
	out1.par.d = hv_Tuple_Avg_CMax;
	out1.type = DOUBLE_PAR;
	out2.par.d = hv_Tuple_Avg_CMin;
	out2.type = DOUBLE_PAR;
	out3.par.d = hv_Tuple_Avg_MM_Th;
	out3.type = DOUBLE_PAR;

	HPutCPar(proc_handle, 1, &out1, 1);
	HPutCPar(proc_handle, 2, &out2, 1);
	HPutCPar(proc_handle, 3, &out3, 1);

	return H_MSG_TRUE;
}

/** ---------------------------------------------------------------------------
 * @Summary
 *      Filt_AMM_04 function
 */
void Filt_AMM_04 (HTuple hv_Input, HTuple hv_Win_Len, HTuple hv_Move_Avg, HTuple hv_thrMB,
	HTuple hv_thrSP, HTuple *hv_Tuple_Avg_CMax, HTuple *hv_Tuple_Avg_CMin, HTuple *hv_Tuple_Avg_MM_Th)
{
	// Local control variables
	HTuple  hv_Input_Avg, hv_FInput, hv_FInputsm;
	HTuple  hv_XValues, hv_Input_Div, hv_threshold;
	HTuple  hv_t_len, hv_T_Tail, hv_win_max, hv_win_maxl;
	HTuple  hv_win_maxr;
	HTuple  hv_Tuple_Avg_CMinl, hv_Tuple_Avg_CMinr;
	HTuple  hv_Tuple_Avg_CMaxl, hv_Tuple_Avg_CMaxr;
	HTuple  hv_Tuple_Avg_MM;
	HTuple  hv_ThrSP, hv_ThrMB;
	HTuple  hv_Tuple_Avg_CMax_Thr, hv_Tuple_Avg_CMin_Thri;
	HTuple  hv_Tuple_Avg_CMin_Thr;

	CreateFunct1dArray (hv_Input, &hv_FInput);
	SmoothFunct1dMean (hv_FInput, hv_Move_Avg, 1, &hv_FInputsm);
	Funct1dToPairs (hv_FInputsm, &hv_XValues, &hv_Input_Avg);

	TupleSub (hv_Input_Avg, hv_Input, &hv_Input_Div);

	//** Search min/max in window
	hv_threshold = hv_thrMB;
	TupleLength (hv_Input_Div, &hv_t_len);
	TupleGenConst (hv_t_len, 0, &(*hv_Tuple_Avg_CMax));
	TupleGenConst (hv_t_len, 0, &(*hv_Tuple_Avg_MM_Th));

	// Let's add a tail for calculations
	TupleGenConst (hv_Win_Len, HTuple(double(hv_Input_Div[hv_t_len - 1])), &hv_T_Tail);
	TupleConcat (hv_Input_Div, hv_T_Tail, &hv_Input_Div);

	HTuple t_test;
	TupleLength (hv_Input_Div, &t_test);
	int i_test = int (t_test);

	// ------
	int t_win_len = static_cast<int>(*hv_Win_Len.DArr());//int t_win_len = int (hv_Win_Len);
	int t_len = int (hv_t_len);
	int t_win_lenD2 = t_win_len / 2;
	int t_win_lenD4 = t_win_len / 4;
	HTuple hv_all_len = hv_t_len + hv_Win_Len;

	TupleReal (hv_Input_Div, &hv_Input_Div);
	double* input_div = hv_Input_Div.DArr ();

	TupleGenConst (hv_all_len, 0.0, &hv_Tuple_Avg_CMinl);
	TupleGenConst (hv_all_len, 0.0, &hv_Tuple_Avg_CMinr);
	TupleGenConst (hv_all_len, 0.0, &hv_Tuple_Avg_CMaxl);
	TupleGenConst (hv_all_len, 0.0, &hv_Tuple_Avg_CMaxr);
	double* avg_cminl = hv_Tuple_Avg_CMinl.DArr ();
	double* avg_cminr = hv_Tuple_Avg_CMinr.DArr ();
	double* avg_cmaxl = hv_Tuple_Avg_CMaxl.DArr ();
	double* avg_cmaxr = hv_Tuple_Avg_CMaxr.DArr ();
	for (int k = 0; k < t_len; k++)
	{
		if (k >= t_win_len)
		{
			double win_maxl, win_maxr, win_minl, win_minr;
			AMM_Span (input_div, k - t_win_lenD2, k, &win_maxl, &win_minl);
			AMM_Span (input_div, k, k + t_win_lenD2, &win_maxr, &win_minr);

			avg_cminl[k - t_win_lenD4] = -input_div[k - t_win_lenD4] + win_minl;
			avg_cminr[k + t_win_lenD4] = -input_div[k + t_win_lenD4] + win_minr;

			avg_cmaxl[k - t_win_lenD4] = -input_div[k - t_win_lenD4] + win_maxl;
			avg_cmaxr[k + t_win_lenD4] = -input_div[k + t_win_lenD4] + win_maxr;
		}
	}

	// ---
	(*hv_Tuple_Avg_CMax) = (hv_Tuple_Avg_CMaxl + hv_Tuple_Avg_CMaxr) / 2.;
	(*hv_Tuple_Avg_CMin) = (hv_Tuple_Avg_CMinl + hv_Tuple_Avg_CMinr) / 2.;
	hv_Tuple_Avg_MM = ((*hv_Tuple_Avg_CMax) + (*hv_Tuple_Avg_CMin)) / 1.0;

	TupleGenConst (hv_all_len, hv_thrSP, &hv_ThrSP);
	TupleGreaterEqualElem (hv_Tuple_Avg_MM, hv_ThrSP, &hv_Tuple_Avg_CMax_Thr);
	TupleGenConst (hv_all_len, hv_thrMB, &hv_ThrMB);
	TupleLessEqualElem (hv_Tuple_Avg_MM, -hv_ThrMB, &hv_Tuple_Avg_CMin_Thri);
	hv_Tuple_Avg_CMin_Thr = hv_Tuple_Avg_CMin_Thri * -1.0;
	(*hv_Tuple_Avg_MM_Th) = (hv_Tuple_Avg_CMax_Thr + hv_Tuple_Avg_CMin_Thr) / 1.0;

	return;
}

/** ---------------------------------------------------------------------------
 * @Summary
 *      Span search function
 */
double AMM_Span (double* in_biff, int pos_start, int pos_end, double *s_max, double *s_min)
{
	*s_max = -FLT_MAX;
	*s_min = FLT_MAX;
	for (int m = pos_start; m <= pos_end; m++)
	{
		if (in_biff[m] > *s_max)
		{
			*s_max = in_biff[m];
		}
		if (in_biff[m] < *s_min)
		{
			*s_min = in_biff[m];
		}
	}
	return *s_max - *s_min;
}
}