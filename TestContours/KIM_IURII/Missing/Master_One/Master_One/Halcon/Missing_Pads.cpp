/**
 * \copyright (C) Synapse Imaging 2023
 *
 * @File Name
		Missing_Pads.cpp
 *
 * @Summary
 *
 * @Description
 *		Scratch detection on conductors
 *
 *
 * @authors Igor Dunin-Barkowski, Iurii Kim
 * @version 1.0
 * @date 2023.05.23
 */
 /* ************************************************************************** */
 /* Section: Included Files                                                    */
 /* ************************************************************************** */
#include "Missing_Pads.h"

/** ---------------------------------------------------------------------------
 * @Summary
 *      An example of using functions
 */
void How_To_Run_Missing_Pads()
{
	HTuple hv_path = "C:/Work/Data/Pads/New/66/";

	// -- Teaching -------------------------------------------------------- 
	HObject  ho_RegionFlash, ho_RegionG, ho_GI_Flash, ho_Gi;
	HObject ho_Padsd, ho_ContoursG, ho_ContoursGsm, ho_CPM, ho_PadsM;

	ReadImage(&ho_GI_Flash, hv_path + "GI_Flash.tif");
	Threshold(ho_GI_Flash, &ho_RegionFlash, 128, 255);
	// ReadObject(&ho_RegionFlash, hv_path + "Pads/RegionFlash.hobj");
	ReadImage(&ho_Gi, hv_path + "Gi.tif");
	Threshold(ho_Gi, &ho_RegionG, 128, 255);
	// ReadObject(&ho_RegionG, hv_path + "Pads/RegionG.hobj");

	HTuple hv_am = 3130;
	HTuple hv_circm = 0.68;
	HTuple hv_dilpadG = 4.5;

	TIMER_CALL(std::cout << "Missing_Pads::Start of training ..." << std::endl);

	TeachPads(ho_RegionFlash, ho_RegionG, &ho_PadsM, &ho_Padsd, &ho_ContoursG, &ho_ContoursGsm,
		&ho_CPM, hv_am, hv_circm, hv_dilpadG);

	TIMER_CALL(std::cout << "Missing_Pads::Training completed.  lead time = " << Get_Delta_Micros() << std::endl);


	// -- Inspect -------------------------------------------------------- 

	HObject ho_Im;
	HObject ho_PadsDefPoint, ho_ContPadDefs, ho_ContPadDefsSP;
	HTuple hv_ndef;

	HTuple hv_thrP = 100;
	HTuple hv_contsmooth = 25;
	HTuple hv_minpadborder = 50;

	HTuple hv_Win_Len = 8;
	HTuple hv_Threshold = 2.5;
	HTuple hv_Move_Avg1 = 24;

	HTuple hv_pad_thresh = 1.10;
	HTuple hv_win_len = 10;
	HTuple hv_voidlen = 7;
	HTuple hv_thrMB = 0.85;
	HTuple hv_thrSP = 0.85;


	ReadImage(&ho_Im, hv_path + "Im.tif");

	TIMER_CALL(std::cout << "Missing_Pads::Start of Inspect ..." << std::endl);


	InspectPads(ho_Im, ho_Padsd, ho_CPM, ho_ContoursGsm, &ho_PadsDefPoint, &ho_ContPadDefs,
		&ho_ContPadDefsSP, hv_thrP, hv_contsmooth, hv_thrMB, hv_thrSP, hv_minpadborder,
		hv_win_len, hv_pad_thresh, hv_voidlen, &hv_ndef);

	TIMER_CALL(std::cout << "Missing_Pads::Inspect completed.  lead time = " << Get_Delta_Micros() << std::endl);

	TEST_CALL_1(WriteObject(ho_ContPadDefs, hv_path + "Test/ContPadDefs.hobj"));
}
/** ---------------------------------------------------------------------------
 * @Summary
 *      Teaching function
 */
void TeachPads (HObject ho_RegionFlash, HObject ho_RegionG, HObject *ho_PadsM, HObject *ho_Padsd,
	HObject *ho_ContoursG, HObject *ho_ContoursGsm, HObject *ho_CPM, HTuple hv_am,
	HTuple hv_circm, HTuple hv_dilpadG)
{
	// Local iconic variables
	HObject  ho_RegionsFlash, ho_RFl, ho_PadsMu, ho_CPMd;
	HObject  ho_Padsi, ho_RegionGB, ho_PadsRCont;

	// Local control variables
	HTuple  hv_nFl, hv_Cf, hv_Af, hv_j, hv_af, hv_rf;
	HTuple  hv_cf, hv_circf, hv_AreaPM, hv_RowPM, hv_ColPM;
	HTuple  hv_nCGsm;

	Connection(ho_RegionFlash, &ho_RegionsFlash);
	CountObj(ho_RegionsFlash, &hv_nFl);
	hv_Cf = HTuple();
	hv_Af = HTuple();

	GenEmptyObj(&(*ho_PadsM));
	{
		HTuple end_val6 = hv_nFl;
		HTuple step_val6 = 1;
		for (hv_j = 1; hv_j.Continue(end_val6, step_val6); hv_j += step_val6)
		{
			//if (j==3345)
				//stop ()
			//endif

			SelectObj(ho_RegionsFlash, &ho_RFl, hv_j);
			AreaCenter(ho_RFl, &hv_af, &hv_rf, &hv_cf);
			Circularity(ho_RFl, &hv_circf);
			TupleConcat(hv_Cf, hv_cf, &hv_Cf);
			TupleConcat(hv_Af, hv_af, &hv_Af);
			if (0 != (HTuple(((hv_af - hv_am).TupleAbs()) < 200).TupleAnd(((hv_circf - hv_circm).TupleAbs()) < 0.05)))
			{
				ConcatObj((*ho_PadsM), ho_RFl, &(*ho_PadsM));
			}
		}
	}
	//*******************************
	Union1((*ho_PadsM), &ho_PadsMu);
	AreaCenter((*ho_PadsM), &hv_AreaPM, &hv_RowPM, &hv_ColPM);
	GenRegionPoints(&(*ho_CPM), hv_RowPM, hv_ColPM);
	DilationCircle((*ho_CPM), &ho_CPMd, 10.5);

	Union1((*ho_PadsM), &ho_Padsi);
	DilationCircle(ho_Padsi, &(*ho_Padsd), hv_dilpadG);
	Boundary(ho_RegionG, &ho_RegionGB, "inner");
	Intersection(ho_RegionGB, (*ho_Padsd), &ho_PadsRCont);
	//gen_contour_region_xld (PadsRCont, Contours, 'center')
	GenContoursSkeletonXld(ho_PadsRCont, &(*ho_ContoursG), 1, "filter");
	SmoothContoursXld((*ho_ContoursG), &(*ho_ContoursGsm), 7);
	CountObj((*ho_ContoursGsm), &hv_nCGsm);
	return;
}
/** ---------------------------------------------------------------------------
 * @Summary
 *      InspectPads function
 */
void InspectPads (HObject ho_Im, HObject ho_Padsd, HObject ho_CPM, HObject ho_ContoursGsm,
	HObject *ho_PadsDefPoint, HObject *ho_ContPadDefsMB, HObject *ho_ContPadDefsSP,
	HTuple hv_thrP, HTuple hv_contsmooth, HTuple hv_thrMB, HTuple hv_thrSP, HTuple hv_minpadborder,
	HTuple hv_win_len, HTuple hv_pad_thresh, HTuple hv_voidlen, HTuple *hv_ndef)
{
	// Local iconic variables
	HObject  ho_ImagePads, ho_Borderi, ho_BorderPads;
	HObject  ho_RegionBPC, ho_CircBPC, ho_CBM, ho_ContourPad;
	HObject  ho_ContPbeg, ho_ContPend, ho_ContourPadsm, ho_PadDefP;

	// Local control variables
	HTuple  hv_ColsPsm, hv_RowsPsm, hv_nBp, hv_AreaBP;
	HTuple  hv_RowBPC, hv_ColBPC, hv_Dist, hv_Baddr, hv_dind;
	HTuple  hv_winsz, hv_j, hv_rowBPC, hv_colBPC, hv_aCBM, hv_rCBM;
	HTuple  hv_cCBM, hv_RowsP, hv_ColsP, hv_DistancePsm, hv_nP;
	HTuple  hv_Rc, hv_Cc, hv_DistancePC, hv_Difi, hv_Difii;
	HTuple  hv_Dif, hv_Tuple_Avg_Max1, hv_Tuple_Avg_Min, hv_Tuple_Avg_Max_Th1;
	HTuple  hv_tmax, hv_tmin, hv_TIndices, hv_TInverted;

	ReduceDomain(ho_Im, ho_Padsd, &ho_ImagePads);
	ThresholdSubPix(ho_ImagePads, &ho_Borderi, hv_thrP);
	SelectShapeXld(ho_Borderi, &ho_BorderPads, (HTuple("contlength").Append("anisometry")),
		"and", hv_minpadborder.TupleConcat(0.0), (HTuple(99999).Append(3.2)));
	CountObj(ho_BorderPads, &hv_nBp);
	AreaCenterPointsXld(ho_BorderPads, &hv_AreaBP, &hv_RowBPC, &hv_ColBPC);

	//PADS CENTERS
	GenRegionPoints(&ho_RegionBPC, hv_RowBPC, hv_ColBPC);
	//* 2 ***

	//*************************

	hv_Dist = HTuple();
	hv_Baddr = HTuple();
	GenEmptyObj(&(*ho_PadsDefPoint));

	(*hv_ndef) = 0;
	hv_dind = 0;
	hv_winsz = 100;
	GenEmptyObj(&(*ho_ContPadDefsMB));
	{
		HTuple end_val24 = hv_nBp;
		HTuple step_val24 = 1;
		for (hv_j = 1; hv_j.Continue(end_val24, step_val24); hv_j += step_val24)
		{
			hv_rowBPC = HTuple(hv_RowBPC[hv_j - 1]);
			hv_colBPC = HTuple(hv_ColBPC[hv_j - 1]);
			GenCircle(&ho_CircBPC, hv_rowBPC, hv_colBPC, 20);
			Intersection(ho_CircBPC, ho_CPM, &ho_CBM);
			AreaCenter(ho_CBM, &hv_aCBM, &hv_rCBM, &hv_cCBM);

			SelectObj(ho_BorderPads, &ho_ContourPad, hv_j);

			//    test_xld_point(BorderPadsCl,
			GetContourXld(ho_ContourPad, &hv_RowsP, &hv_ColsP);

			//distance_pp (RowsP, ColsP, RowsPsmOut, ColsPsmOut, DistancePsm)
			TupleLength(hv_RowsP, &hv_nP);
			// GenRegionPoints(&ho_ContPbeg, HTuple(hv_RowsP[0]), HTuple(hv_ColsP[0]));
			// GenRegionPoints(&ho_ContPend, HTuple(hv_RowsP[hv_nP - 1]), HTuple(hv_ColsP[hv_nP - 1]));


			TupleGenConst(hv_nP, hv_rCBM, &hv_Rc);
			TupleGenConst(hv_nP, hv_cCBM, &hv_Cc);
			DistancePp(hv_RowsP, hv_ColsP, hv_Rc, hv_Cc, &hv_DistancePC);

			SmoothContoursXld(ho_ContourPad, &ho_ContourPadsm, hv_contsmooth);
			GetContourXld(ho_ContourPadsm, &hv_RowsPsm, &hv_ColsPsm);

			DistancePp(hv_Rc, hv_Cc, hv_RowsPsm, hv_ColsPsm, &hv_DistancePsm);


			hv_Difi = hv_DistancePC - hv_DistancePsm;
			TupleFirstN(hv_Difi, hv_nP - hv_voidlen, &hv_Difii);
			TupleLastN(hv_Difii, hv_voidlen, &hv_Dif);

			Filt_AMM_04(hv_Dif, hv_win_len, 10, hv_thrMB, hv_thrSP, &hv_Tuple_Avg_Max1, &hv_Tuple_Avg_Min, &hv_Tuple_Avg_Max_Th1);

			TupleMax(hv_Tuple_Avg_Max_Th1, &hv_tmax);
			TupleMin(hv_Tuple_Avg_Max_Th1, &hv_tmin);

			//******************
			if (0 != (HTuple(hv_tmax > 0).TupleOr(hv_tmin < 0)))
			{
				(*hv_ndef) += 1;

				//ConcatObj((*ho_PadsDefPoint), ho_ContourPad, &(*ho_PadsDefPoint));

				//TupleSortIndex(hv_Tuple_Avg_Max_Th1, &hv_TIndices);
				//TupleInverse(hv_TIndices, &hv_TInverted);
				//hv_dind = ((const HTuple&)hv_TInverted)[0];
				//GenRegionPoints(&ho_PadDefP, HTuple(hv_RowsP[hv_dind + 2]), HTuple(hv_ColsP[hv_dind + 2]));
				ConcatObj((*ho_ContPadDefsMB), ho_ContourPad, ho_ContPadDefsMB);

			}
			//******************
		}
	}
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
	HTuple  hv_t_len, hv_T_Tail, hv_k, hv_win_max, hv_win_maxl;
	HTuple  hv_win_maxr, hv_win_min, hv_win_minl, hv_win_minr;
	HTuple  hv_cminl, hv_Tuple_Avg_CMinl, hv_cminr, hv_Tuple_Avg_CMinr;
	HTuple  hv_cmaxl, hv_Tuple_Avg_CMaxl, hv_cmaxr, hv_Tuple_Avg_CMaxr;
	HTuple  hv_lmax, hv_lmin, hv_l, hv_Tuple_Avg_CMaxrc, hv_Tuple_Avg_CMinrc;
	HTuple  hv_Tuple_Avg_CMaxlc, hv_Tuple_Avg_CMinlc, hv_Tuple_Avg_MM;
	HTuple  hv_ThrSP, hv_Tuple_Avg_CMax_Thr, hv_ThrMB, hv_Tuple_Avg_CMin_Thri;
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
	int t_win_len = int (hv_Win_Len);
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

	// --- Function test Filt_AMM_04 ------------------------------------------
	TEST_CALL_2(HTuple hv_path = "C:/Work/Data/Pads/66/Test/");
	TEST_CALL_2(WriteTuple (hv_Tuple_Avg_CMaxl, hv_path + "Tuple_Avg_CMaxl.tup"));
	TEST_CALL_2(WriteTuple (hv_Tuple_Avg_CMaxr, hv_path + "Tuple_Avg_CMaxr.tup"));
	TEST_CALL_2(WriteTuple (hv_Tuple_Avg_CMinl, hv_path + "Tuple_Avg_CMinl.tup"));
	TEST_CALL_2(WriteTuple (hv_Tuple_Avg_CMinr, hv_path + "Tuple_Avg_CMinr.tup"));
	TEST_CALL_2(WriteTuple (*hv_Tuple_Avg_MM_Th, hv_path + "Tuple_Avg_MM_Th.tup"));

	return;
}
/* ************************************************************************** */
/* End of file                                                                */
/* ************************************************************************** */
