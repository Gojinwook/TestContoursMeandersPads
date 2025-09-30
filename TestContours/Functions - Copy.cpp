
/* ************************************************************************** */
 /* Section: Included Files                                                    */
 /* ************************************************************************** */


#include "Functions.h"
#include "pch.h"
#include "framework.h"
#include "TestContours.h"
#include "TestContoursDlg.h"
#include "afxdialogex.h"

#include <vector>
#include <complex>
#include <cmath>

using namespace HalconCpp;
//using namespace std;


	// Procedures 
	void DistPointToLineSegmH(HTuple hv_y, HTuple hv_x, HTuple hv_y1, HTuple hv_x1, HTuple hv_y2,
		HTuple hv_x2, HTuple *hv_distance, HTuple *hv_ym, HTuple *hv_xm, HTuple *hv_t)
	{

		// Local iconic variables

		// Local control variables
		HTuple  hv_td;

		hv_td = ((hv_x2 - hv_x1)*(hv_x2 - hv_x1)) + ((hv_y2 - hv_y1)*(hv_y2 - hv_y1));
		if (0 != (hv_td != 0.0))
		{
			(*hv_t) = (((hv_x - hv_x1)*(hv_x2 - hv_x1)) + ((hv_y - hv_y1)*(hv_y2 - hv_y1))) / hv_td;
		}
		else
		{
			(*hv_t) = 111;
		}

		if (0 != ((*hv_t) >= 1.))
		{
			//distance := sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2))
			(*hv_xm) = hv_x2;
			(*hv_ym) = hv_y2;
		}
		else if (0 != ((*hv_t) <= 0.))
		{
			(*hv_xm) = hv_x1;
			(*hv_ym) = hv_y1;
			//distance := sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1))
		}
		else
		{
			(*hv_xm) = hv_x1 + ((*hv_t)*(hv_x2 - hv_x1));
			(*hv_ym) = hv_y1 + ((*hv_t)*(hv_y2 - hv_y1));
		}
		(*hv_distance) = (((hv_x - (*hv_xm))*(hv_x - (*hv_xm))) + ((hv_y - (*hv_ym))*(hv_y - (*hv_ym)))).TupleSqrt();
		return;
	}

	void DistPointToLineSegm(float y, float x, float y1, float x1, float y2,
		float x2, float *distance, float *ym, float *xm, float *t)
	{

		// Local iconic variables

		// Local control variables
		float td;

		td = ((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1));
		if (td != 0.)
		{
			(*t) = (((x - x1)*(x2 - x1)) + ((y - y1)*(y2 - y1))) / td;
		}
		else
		{
			(*t) = 111.;
		}

		if (*t >= 1.)
		{
			//distance := sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2))
			(*xm) = x2;
			(*ym) = y2;
		}
		else if (*t <= 0.)
		{
			(*xm) = x1;
			(*ym) = y1;
			//distance := sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1))
		}
		else
		{
			(*xm) = x1 + ((*t)*(x2 - x1));
			(*ym) = y1 + ((*t)*(y2 - y1));
		}
		(*distance) = sqrt(((x - *xm)*(x - *xm)) + ((y - *ym)*(y - *ym)));
		return;
	}

	void CircularSector(int isz, int n, int ki, int *K)
	{

		// Local iconic variables

		// Local control variables
		int kb, ke;

		//***CircularSector 03.09.2025
		kb = ki - isz;
		if (kb < 0)
			kb = n + kb;
		ke = ki + isz - 1;
		if (ke >= n)
			ke = ke - n;

		if (kb <= ke)
		{
			int m = ke - kb;
			for (int j = 0; j < m; j++)
				*(K + j) = kb + j;
			//(*hv_K) = HTuple::TupleGenSequence(hv_kb, hv_ke, 1);

		}
		else
		{
			int m1 = ke + 1;
			int m2 = n - kb;
			for (int j = 0; j < m1; j++)
				*(K + j) = j;
			for (int j = 0; j < m2; j++)
				*(K + m1 + j) = kb + j;
			/*(*hv_K).Clear();
			(*hv_K).Append(HTuple::TupleGenSequence(0, hv_ke, 1));
			(*hv_K).Append(HTuple::TupleGenSequence(hv_kb, hv_n - 1, 1));*/
		}

		return;
	}
	void DistanceContours2(float *pRowI, float *pColI, int nI, float *pRowG, float *pColG, int nG,
		int isz, float *pD, int ptop)
	{
		float *pColGS, *pRowGS;
		int *pK;

		float digs, digc, digr, digsmin;
		int kmin;
		int nS = isz * 2;

		//pColGS = (float *)malloc((isz*2) * sizeof(float));
		//pRowGS = (float *)malloc((isz * 2) * sizeof(float));
		pK = (int *)malloc((isz * 2) * sizeof(int));

		int ki = 0;
		float colI, rowI;

		float rowGm1, colGm1, t1, d1, d, dd;
		float rowGm2, colGm2, t2, d2;

		for (int i = 0; i < nI; i++)
		{
			CircularSector(isz, nG, ki, pK);

			/*if (i == 876)
				i = i;*/
			colI = *(pColI + i);
			rowI = *(pRowI + i);

			digsmin = 9999.;
			for (int k = 0; k < nS; k++)
			{
				digr = *(pRowG + *(pK + k)) - rowI;
				digc = *(pColG + *(pK + k)) - colI;
				//digc = *(pColGS+k) - colI;
				digs = sqrt(digr*digr + digc * digc);
				if (digs < digsmin)
				{
					digsmin = digs;
					kmin = k;
				}
			}

			ki = *(pK + kmin);

			float rowG = *(pRowG + ki);
			float colG = *(pColG + ki);

			if (ptop == 1)
			{
				d = sqrt((colI - colG)*(rowI - rowG));

			}
			else
			{
				int ki1 = ki - 1;
				if (ki1 < 0)
					ki1 = ki1 + nG;

				float colG1 = *(pColG + ki1);
				float rowG1 = *(pRowG + ki1);

				int ki2 = ki + 1;
				if (ki2 >= nG)
					ki2 = ki2 - nG;

				float colG2 = *(pColG + ki2);
				float rowG2 = *(pRowG + ki2);


				DistPointToLineSegm(rowI, colI, rowG, colG, rowG1, colG1, &d1,
					&rowGm1, &colGm1, &t1);
				DistPointToLineSegm(rowI, colI, rowG, colG, rowG2, colG2, &d2,
					&rowGm2, &colGm2, &t2);

				if (d1 < d2)
					d = d1;
				else d = d2;
				dd = d;

				if ((t1 < 0 && t2 < 0) || (t1 > 1 && t2 > 1))
				{
					int kim2 = ki - 2;
					if (kim2 < 0)
						kim2 = kim2 + nG;
					float colGm1 = *(pColG + kim2);
					float rowGm1 = *(pRowG + kim2);

					float dm1, tm1, dp2, tp2;
					DistPointToLineSegm(rowI, colI, rowGm1, colGm1, rowG1, colG1, &dm1,
						&rowGm1, &colGm1, &tm1);

					if ((tm1 < 0) || (tm1 > 1))
					{
						int kip2 = ki + 2;
						if (kip2 >= nG)
							kip2 = kip2 - nG;

						float colGp2 = *(pColG + kip2);
						float rowGp2 = *(pRowG + kip2);

						DistPointToLineSegm(rowI, colI, rowG2, colG2, rowGp2, colGp2, &dp2,
							&rowGp2, &colGp2, &tp2);

						dd = dp2;
					}
					else
					{
						dd = dm1;
					}
				}
				if (dd < d)
					d = dd;
			}

			*(pD + i) = d;

		}
		free(pK);
	}

	void DistanceContours2H(HTuple hv_RowI, HTuple hv_ColI, HTuple hv_RowG, HTuple hv_ColG,
		HTuple hv_isz, HTuple *hv_D)
	{

		// Local iconic variables
		HObject  ho_CI, ho_CG, ho_CG1, ho_CG2;

		// Local control variables
		HTuple  hv_nI, hv_nG, hv_ki, hv_i, hv_colI, hv_rowI;
		HTuple  hv_kb, hv_ke, hv_ColGs, hv_RowGs, hv_K, hv_num;
		HTuple  hv_DIGcOut, hv_DIGr, hv_DIGs, hv_minD, hv_k, hv_IndicesD;
		HTuple  hv_rowG, hv_colG, hv_ki1, hv_colG1, hv_rowG1, hv_ki2;
		HTuple  hv_colG2, hv_rowG2, hv_d1, hv_rowm1, hv_colGm1;
		HTuple  hv_t1, hv_d2, hv_rowm2, hv_colGm2, hv_t2, hv_d;
		HTuple  hv_dd, hv_kim2, hv_rowGm1, hv_dm1, hv_tm1, hv_kip2;
		HTuple  hv_colGp2, hv_rowGp2, hv_dp2, hv_tp2;

		//***** DistanceContours2 (RowI, ColI, RowG, ColG, isz, DistIG)
		//*** finding distance betweel contours given as points
		//*** 02.09.2025

		hv_nI = hv_RowI.TupleLength();
		hv_nG = hv_RowG.TupleLength();
		hv_ki = 0;
		{
			HTuple end_val7 = hv_nI - 1;
			HTuple step_val7 = 1;
			for (hv_i = 0; hv_i.Continue(end_val7, step_val7); hv_i += step_val7)
			{

				//if (i==613)
				  //stop ()
				//endif
				hv_colI = HTuple(hv_ColI[hv_i]);
				hv_rowI = HTuple(hv_RowI[hv_i]);

				hv_kb = hv_ki - hv_isz;
				if (0 != (hv_kb < 0))
				{
					hv_kb = hv_nG + hv_kb;
				}
				hv_ke = (hv_ki + hv_isz) - 1;
				if (0 != (hv_ke >= hv_nG))
				{
					hv_ke = hv_ke - hv_nG;
				}

				if (0 != (hv_kb <= hv_ke))
				{
					hv_ColGs = hv_ColG.TupleSelectRange(hv_kb, hv_ke);
					hv_RowGs = hv_RowG.TupleSelectRange(hv_kb, hv_ke);
					hv_K = HTuple::TupleGenSequence(hv_kb, hv_ke, 1);
				}
				else
				{
					hv_ColGs.Clear();
					hv_ColGs.Append(hv_ColG.TupleSelectRange(0, hv_ke));
					hv_ColGs.Append(hv_ColG.TupleSelectRange(hv_kb, hv_nG - 1));
					hv_RowGs.Clear();
					hv_RowGs.Append(hv_RowG.TupleSelectRange(0, hv_ke));
					hv_RowGs.Append(hv_RowG.TupleSelectRange(hv_kb, hv_nG - 1));
					hv_K.Clear();
					hv_K.Append(HTuple::TupleGenSequence(0, hv_ke, 1));
					hv_K.Append(HTuple::TupleGenSequence(hv_kb, hv_nG - 1, 1));
					hv_num = hv_RowGs.TupleLength();
					//DIGcs := DIGcOut[kb:nG-1]
				}
				//***** ????? ****
				//ColGs := ColG
				//RowGs := RowG
				//***** ????? ****
				hv_DIGcOut = hv_ColGs - hv_colI;
				hv_DIGr = hv_RowGs - hv_rowI;
				hv_DIGs = ((hv_DIGcOut*hv_DIGcOut) + (hv_DIGr*hv_DIGr)).TupleSqrt();
				//DIG := DIGcOut+DIGr
				//tuple_min_ind (DIGs, minD, k)
				TupleSortIndex(hv_DIGs, &hv_IndicesD);

				TupleMin(hv_DIGs, &hv_minD);
				//stop ()

				hv_k = ((const HTuple&)hv_IndicesD)[0];
				hv_ki = HTuple(hv_K[hv_k]);
				hv_rowG = HTuple(hv_RowG[hv_ki]);
				hv_colG = HTuple(hv_ColG[hv_ki]);
				//gen_region_points (PGs, RowG, ColG)

				//distance_pp (rowG, colG, rowI, colI, Distance)
				hv_ki1 = hv_ki - 1;
				if (0 != (hv_ki1 < 0))
				{
					hv_ki1 = hv_nG + hv_ki1;
				}
				hv_colG1 = HTuple(hv_ColG[hv_ki1]);
				hv_rowG1 = HTuple(hv_RowG[hv_ki1]);
				hv_ki2 = hv_ki + 1;
				if (0 != (hv_ki2 >= hv_nG))
				{
					hv_ki2 = (-hv_nG) + hv_ki2;
				}
				hv_colG2 = HTuple(hv_ColG[hv_ki2]);
				hv_rowG2 = HTuple(hv_RowG[hv_ki2]);



				DistPointToLineSegmH(hv_rowI, hv_colI, hv_rowG, hv_colG, hv_rowG1, hv_colG1, &hv_d1,
					&hv_rowm1, &hv_colGm1, &hv_t1);
				DistPointToLineSegmH(hv_rowI, hv_colI, hv_rowG, hv_colG, hv_rowG2, hv_colG2, &hv_d2,
					&hv_rowm2, &hv_colGm2, &hv_t2);
				hv_d = hv_d1.TupleMin2(hv_d2);
				hv_dd = hv_d;
				if (0 != (HTuple(HTuple(hv_t1 < 0).TupleAnd(hv_t2 < 0)).TupleOr(HTuple(hv_t1 > 1).TupleAnd(hv_t2 > 1))))
				{
					hv_kim2 = hv_ki - 2;
					if (0 != (hv_kim2 < 0))
					{
						hv_kim2 = hv_nG + hv_kim2;
					}
					hv_colGm1 = HTuple(hv_ColG[hv_kim2]);
					hv_rowGm1 = HTuple(hv_RowG[hv_kim2]);
					DistPointToLineSegmH(hv_rowI, hv_colI, hv_rowGm1, hv_colGm1, hv_rowG1, hv_colG1,
						&hv_dm1, &hv_rowGm1, &hv_colGm1, &hv_tm1);
					//dev_set_color ('dark turquoise')
					//gen_cross_contour_xld (CG2, rowGm1, colGm1, 0.07, 6)
					if (0 != (HTuple(hv_tm1 < 0).TupleOr(hv_tm1 > 1)))
					{
						hv_kip2 = hv_ki + 2;
						if (0 != (hv_kip2 >= hv_nG))
						{
							hv_kip2 = (-hv_nG) + hv_kip2;
						}
						hv_colGp2 = HTuple(hv_ColG[hv_kip2]);
						hv_rowGp2 = HTuple(hv_RowG[hv_kip2]);
						//dev_set_color ('steel blue')
						//gen_cross_contour_xld (CG2, rowGp2, colGp2, 0.23, 6)
						DistPointToLineSegmH(hv_rowI, hv_colI, hv_rowG2, hv_colG2, hv_rowGp2, hv_colGp2,
							&hv_dp2, &hv_rowGp2, &hv_colGp2, &hv_tp2);
						hv_dd = hv_dp2;
					}
					else
					{
						hv_dd = hv_dm1;
					}
				}
				hv_d = hv_d.TupleMin2(hv_dd);
				//d := DIG[k]
				//D[i] := minD
				(*hv_D)[hv_i] = hv_d;
				//distance_pp (rowI, colI, rowG, colG, d1)
			}
		}
		return;
	}

	float* ConvertTupleToFloat(HTuple T)
	{
		double *dptr, d;
		HTuple tl;
		float *dp;

		TupleLength(T, &tl);
		int itl = (int)tl.L();

		dptr = T.ToDArr();
		dp = (float *)malloc(itl * sizeof(float));
		for (int i = 0; i < itl; i++)
		{
			d = *(dptr + i);
			*(dp + i) = (float)d;
		}
		return dp;
	}


	void FloatToTuple(float *dp, int len, HTuple &tuple)
	{
		tuple = HTuple(dp, len);
		TupleReal(tuple, &tuple);

		//INT64* ptr = ConvertFloatToINT64(dp, len);
		//tuple = HTuple(ptr, len);
	}


	/** ---------------------------------------------------------------------------
	* @Summary
	*	¬±¬à¬Ý¬å¬é¬Ö¬ß¬Ú¬Ö ¬Ù¬ß¬Ñ¬é¬Ö¬ß¬Ú¬ñ ¬ñ¬â¬Ü¬à¬ã¬ä¬Ú ¬á¬Ú¬Ü¬ã¬Ö¬Ý¬ñ
	*/
	UINT8 Get_Gray_Val(UINT8 *pIm, int im_w, int im_h, int y, int x)
	{
		return *(pIm + y * im_w + x);
	}
	/** ---------------------------------------------------------------------------
	* @Summary
	*	¬±¬â¬à¬Ó¬Ö¬â¬Ü¬Ñ, ¬ñ¬Ó¬Ý¬ñ¬Ö¬ä¬ã¬ñ ¬Ý¬Ú ¬â¬Ö¬Ô¬Ú¬à¬ß ¬Õ¬í¬â¬Ü¬à¬Û
	*/
	bool Test_Hole(UINT8 *pIm, int im_w, int im_h, UINT64* rows, UINT64* cols, int count_len, int thr)
	{
		for (int pos = 0; pos < count_len; pos++)
		{
			UINT8 gray0 = Get_Gray_Val(pIm, im_w, im_h, (int)rows[pos], (int)cols[pos]);
			if (gray0 < thr)
			{
				return true;
			}
			else if (gray0 > thr)
			{
				return false;
			}
		}
		return false;
	}

	/** ---------------------------------------------------------------------------
	* @Summary
	*	¬ª¬ß¬ä¬Ö¬â¬á¬à¬Ý¬ñ¬è¬Ú¬ñ. ¬°¬á¬â¬Ö¬Õ¬Ö¬Ý¬Ö¬ß¬Ú¬Ö ¬ã¬å¬Ò¬á¬Ú¬Ü¬ã¬Ö¬Ý¬î¬ß¬à¬Û ¬Ü¬à¬à¬â¬Õ¬Ú¬ß¬Ñ¬ä¬í.
	*/
	bool Interpolation_Sub(bool reg_hole, bool direct, UINT8 gray0, UINT8 gray1, UINT8 gray2, int col_curr, int row_curr, int thr, double &xR, double &yR)
	{
		int x0 = -1, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
		// * ¬ª¬Õ¬Ö¬Þ ¬Ó¬ß¬Ú¬Ù.¬³¬â¬Ñ¬Ó¬ß¬Ú¬Ó¬Ñ¬Ö¬Þ ¬ã ¬á¬à¬Ý¬Ö¬Þ ¬ã¬á¬â¬Ñ¬Ó¬Ñ
		// * ¬ª¬Õ¬Ö¬Þ ¬Ó¬Ý¬Ö¬Ó¬à. ¬³¬â¬Ñ¬Ó¬ß¬Ú¬Ó¬Ñ¬Ö¬Þ ¬ã ¬á¬à¬Ý¬Ö¬Þ ¬ã¬ß¬Ú¬Ù¬å
		if (direct && ((reg_hole && gray1 > thr) || (!reg_hole && gray1 < thr)))
		{
			x0 = thr;
			x1 = gray0;
			x2 = gray1;
			y1 = col_curr;
		}
		// * ¬ª¬Õ¬Ö¬Þ ¬Ó¬Ó¬Ö¬â¬ç. ¬³¬â¬Ñ¬Ó¬ß¬Ú¬Ó¬Ñ¬Ö¬Þ ¬ã ¬á¬à¬Ý¬Ö¬Þ ¬ã¬Ý¬Ö¬Ó¬Ñ
		// * ¬ª¬Õ¬Ö¬Þ ¬Ó¬á¬â¬Ñ¬Ó¬à. ¬³¬â¬Ñ¬Ó¬ß¬Ú¬Ó¬Ñ¬Ö¬Þ ¬ã ¬á¬à¬Ý¬Ö¬Þ ¬ã¬Ó¬Ö¬â¬ç¬å
		else if (!direct && ((reg_hole && gray2 > thr) || (!reg_hole && gray2 < thr)))
		{
			x0 = thr;
			x1 = gray2;
			x2 = gray0;
			y1 = col_curr - 1;
		}

		if (x0 >= 0 && x2 != x1)
		{
			xR = (double)y1 + (double)(x0 - x1) / (double)(x2 - x1);
			yR = row_curr;
			return true;
		}
		else
		{
			return false;
		}
	}
	/* @Summary
	*	¬¶¬à¬â¬Þ¬Ú¬â¬à¬Ó¬Ñ¬ß¬Ú¬Ö ¬ã¬å¬Ò¬á¬Ú¬Ü¬ã¬Ö¬Ý¬î¬ß¬í¬ç ¬Ü¬à¬à¬â¬Õ¬Ú¬ß¬Ñ¬ä ¬Õ¬Ý¬ñ ¬â¬Ö¬Ô¬Ú¬à¬ß¬Ñ
	*/
	int Region_Threshold_SubPix(HObject ho_Im, HObject ho_RegSel, int thr, double *rows_sub, double *cols_sub)
	{
		HTuple tl, h, w, t, hiptr;
		GetImagePointer1(ho_Im, &hiptr, &t, &w, &h);
		UINT8 *pIm = (UINT8 *)(Hlong *)hiptr.L();
		int im_w = (int)w.L();
		int im_h = (int)h.L();


		HTuple hv_Rows, hv_Cols, hv_Cont_Len;
		UINT8 gray0, gray1, gray2;
		int x0 = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
		double xR1, yR1, xR2, yR2;
		int pos_sub = 0;

		GetRegionContour(ho_RegSel, &hv_Rows, &hv_Cols);
		UINT64* rows = (UINT64*)hv_Rows.LArr();
		UINT64* cols = (UINT64*)hv_Cols.LArr();

		TupleLength(hv_Rows, &hv_Cont_Len);
		int count_len = (int)hv_Cont_Len.LArr()[0];

		// ¬´¬Ö¬ã¬ä ¬ß¬Ñ ¬Õ¬í¬â¬Ü¬å
		bool reg_hole = Test_Hole(pIm, im_w, im_h, rows, cols, count_len, thr);

		int pos;
		for (pos = 0; pos < count_len; pos++)
		{
			// * ¬°¬Ü¬â¬å¬Ø¬Ö¬ß¬Ú¬Ö ¬Ú¬ã¬ã¬Ý¬Ö¬Õ¬å¬Ö¬Þ¬à¬Ô¬à ¬á¬Ú¬Ü¬ã¬Ö¬Ý¬ñ
			int pos_next = pos + 1;
			if (pos_next > (count_len - 1))
			{
				pos_next = 0;
			}
			int pos_prev = pos - 1;
			if (pos_prev < 0)
			{
				pos_prev = count_len - 1;
			}
			int row_prev = (int)rows[pos_prev];
			int col_prev = (int)cols[pos_prev];
			int row_next = (int)rows[pos_next];
			int col_next = (int)cols[pos_next];
			int row_curr = (int)rows[pos];
			int col_curr = (int)cols[pos];

			// ¬©¬Ñ ¬á¬â¬Ö¬Õ¬Ö¬Ý¬Ñ¬Þ¬Ú ¬Ú¬Ù¬à¬Ò¬â¬Ñ¬Ø¬Ö¬ß¬Ú¬ñ
			if (row_curr >= im_h - 1 || col_curr >= im_w - 1 || row_curr == 0 || col_curr == 0)
			{
				continue;
			}

			// * ¬¯¬Ñ¬á¬â¬Ñ¬Ó¬Ý¬Ö¬ß¬Ú¬Ö
			bool f_Down, f_Left;
			f_Down = row_curr > row_prev || row_curr < row_next;
			f_Left = col_curr < col_prev || col_curr > col_next;

			gray0 = Get_Gray_Val(pIm, im_w, im_h, (int)rows[pos], (int)cols[pos]);

			// *-- Cols ----------------------------------------------------------------------
			gray1 = Get_Gray_Val(pIm, im_w, im_h, row_curr, col_curr + 1);
			gray2 = Get_Gray_Val(pIm, im_w, im_h, row_curr, col_curr - 1);
			bool f_Cols_Available = Interpolation_Sub(reg_hole, f_Down, gray0, gray1, gray2, col_curr, row_curr, thr, xR1, yR1);

			// *--- Rows ----------------------------------------------------------------------
			gray1 = Get_Gray_Val(pIm, im_w, im_h, row_curr + 1, col_curr);
			gray2 = Get_Gray_Val(pIm, im_w, im_h, row_curr - 1, col_curr);
			bool f_Rows_Available = Interpolation_Sub(reg_hole, f_Left, gray0, gray1, gray2, row_curr, col_curr, thr, yR2, xR2);

			// *--- ¬³¬à¬Ò¬Ú¬â¬Ñ¬Ö¬Þ ¬â¬Ö¬Ù¬å¬Ý¬î¬ä¬Ñ¬ä ------------------------------------------------------
			if (f_Cols_Available && f_Rows_Available)
			{
				if ((xR1 > xR2 && yR1 > yR2) || (xR1 <= xR2 && yR1 < yR2))
				{
					rows_sub[pos_sub] = yR2;
					cols_sub[pos_sub] = xR2;
					pos_sub += 1;

					rows_sub[pos_sub] = yR1;
					cols_sub[pos_sub] = xR1;
					pos_sub += 1;
				}
				else
				{
					rows_sub[pos_sub] = yR1;
					cols_sub[pos_sub] = xR1;
					pos_sub += 1;

					rows_sub[pos_sub] = yR2;
					cols_sub[pos_sub] = xR2;
					pos_sub += 1;
				}
			}
			else if (f_Cols_Available)
			{
				rows_sub[pos_sub] = yR1;
				cols_sub[pos_sub] = xR1;
				pos_sub += 1;
			}
			else if (f_Rows_Available)
			{
				rows_sub[pos_sub] = yR2;
				cols_sub[pos_sub] = xR2;
				pos_sub += 1;
			}
		}

		return pos_sub;
	}
