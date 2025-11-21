#pragma once
/**
 * \copyright (C) Synapse 2023
 *
 * @File Name
 *      FWM.h
 *
 * @Summary
 *
 * @Description
 *
 *
 * @authors Igor Dunin-Barkowski, Iurii Kim
 * @version 1.0
 * @date 2024.04.21
 */

#pragma once

 /* ************************************************************************** */
 /* Section: Included Files                                                    */
 /* ************************************************************************** */
#include <iostream>
#include <vector>
#include <fstream>
#include <atlstr.h>

#include "HalconCpp.h"
#include "HDevThread.h"

using namespace std;
using namespace HalconCpp;

#define ND						1024 // Max. number of MB and SP per skeleton part
#define MAX_FWM_DEFECT			10000
#define MEDOSIZE				280000


class FWM
{
public:
	// ¬ª¬Ù¬à¬Ò¬â¬Ñ¬Ø¬Ö¬ß¬Ú¬ñ
	HImage m_pIm;
	HImage m_pImIRB;
	HImage m_pImCLC;
	HImage m_pImIRBS;

	// ¬³¬Ö¬ß¬ã¬à¬â¬Ñ
	float *pP1x;
	float *pP1y;
	float *pP2x;
	float *pP2y;
	int *pPnum, *pWG;
	int *pPaddrR, *pPaddrC;
	//int *pPaddrR, *pPaddrC;
	int m_tuple_len;

	HObject ho_SkelsEPUver;
	HObject ho_Rd;
	HObject *mmpho_SkelsEPUver;
	HObject *mmpho_Rd;

	int mmNaC;		// number contours
	int mmNa;		// number of addresses (for all SkeletonsFWM regions)

	int mmlMB;
	int mmlSP;		// defect length for MB and SP
	int mmSPnum, mmMBnum;

	// Output data
	float *dW;
	float *dWmin;
	float *dPint1x;
	float *dPint1y;
	float *dPint2x;
	float *dPint2y;
	float *dShift;
	int *dPuseint;

	float mmpXdefMB[ND * MAX_FWM_DEFECT];	// defect coordinates x MB
	float mmpYdefMB[ND * MAX_FWM_DEFECT];	// defect coordinates y MB
	float mmpDefMB[ND * MAX_FWM_DEFECT];	// defects MB

	float mmpXdefSP[ND * MAX_FWM_DEFECT];	// defect coordinates x 
	float mmpYdefSP[ND * MAX_FWM_DEFECT];	// defect coordinates y 
	float mmpDefSP[ND * MAX_FWM_DEFECT];	// defects SP

	// Missing
	float mmpXdefMIS[ND * MAX_FWM_DEFECT];	
	float mmpYdefMIS[ND * MAX_FWM_DEFECT];	
	float mmpDefMIS[ND * MAX_FWM_DEFECT];	


	HObject mmRegMB;
	HObject mmRegSP;
	HObject mmRegMBs;
	HObject mmRegSPs;
	HObject mmRegMISS;
	HObject mmCircleSPs, mmCircleMBs, mmCircleMISS;

	int SPnum = 0, MBnum = 0, MISnum = 0;

	double *dThickness;

public:
	void PostProc()
	{
		int caddrb, caddre, cnum, j, jj;
		int spnum, mbnum;

		HObject  ho_Regsps, ho_CircleSP, ho_CircleMB, RegMBs;

		// Local control variables
		HTuple  hv_thr, hv_nMB, hv_nSP, hv_AreaSPs, hv_RowSPs;
		HTuple  hv_ColumnSPs, hv_TR, hv_AreaMBs, hv_RowMBs, hv_ColumnMBs;

		int dlen = 1;  // defect length
		float *mmpWidth = dW;
		int *mmpWG = pWG;

		// ??????
		float *mmpmedo;
		mmpmedo = (float*) malloc (MEDOSIZE * 1 * sizeof (float));

		float *mmpPInt1x, *mmpPInt1y;
		mmpPInt1x = dPint1x;
		mmpPInt1y = dPint1y;

		int* mmpPaddrC = pPaddrC;

		int nvoid = 7;

		// --- MB and Sup detection parameters

		// Running median sizes for FWM and FWMS
		int mmsz1 = 25;			
		int mmsz2 = 25;		

		int mmrmskip = 0;		// skip in run. med.
		float mmang = 3.;		// angle for defect 

		// Prc. for MB ans SP
		float mmprcMB = 40.;
		float mmprcSP = 40.;		

		// abs. width dif for MB and SP
		float mmabsMB = 10.; 
		float mmabsSP = 10.;

		// Missing threshold
		int th_miss = 40;

		// --- fwm.CPU_PP_MemReAlloc();
		for (int i = 0; i < (ND * mmNaC); i++)
		{
			mmpDefMB[i] = 0;	// defects MB
			mmpXdefMB[i] = 0;	// defect coordinates x MB
			mmpYdefMB[i] = 0;	// defect coordinates y MB

			mmpDefSP[i] = 0;	// defects SP
			mmpXdefSP[i] = 0;	// defect coordinates x 
			mmpYdefSP[i] = 0;	// defect coordinates y 

			// Missing
			mmpDefMIS[i] = 0;	
			mmpXdefMIS[i] = 0;	
			mmpYdefMIS[i] = 0;	
		}
	
		FWM_PostProc(
			mmpWidth, mmpWG, mmpmedo, mmpPInt1x, mmpPInt1y, mmNaC, nvoid, mmpPaddrC, mmsz1, 
			mmsz2, mmrmskip, mmang, mmprcMB, mmprcSP, mmabsMB, mmabsSP, dlen, 
			mmpDefMB, mmpXdefMB, mmpYdefMB, 
			mmpDefSP, mmpXdefSP, mmpYdefSP, 
			&MBnum, &SPnum,
			th_miss, mmpDefMIS, mmpXdefMIS, mmpYdefMIS, &MISnum);


		// ??????
		mmpho_SkelsEPUver = &ho_SkelsEPUver;
		mmpho_Rd = &ho_Rd;

		mmlMB = 1;
		mmlSP = 1;
		PostProcFWMCondLen(); // Condensing defects from FWM CUDA and checking their length

		free(mmpmedo);
	}

private:
	void PostProcFWMCondLen() // Condensing defects from FWM CUDA and checking their length
	{
		HObject ho_SkelsEPUver;
		HTuple TMBx, TSPx, TMBy, TSPy, hlx, hly;
		INT64 *Px = ConvertFloatToINT64(mmpXdefMB, ND * mmNa);
		INT64 *Py = ConvertFloatToINT64(mmpYdefMB, ND * mmNa);
		HTuple PMBx_tuple((Hlong *)Px, ND*mmNa);
		HTuple PMBy_tuple((Hlong *)Py, ND*mmNa);

		GenRegionPoints(&mmRegMB, PMBy_tuple, PMBx_tuple);

		// Local control variables
		HTuple  hv_nMB, hv_nSP, hv_AreaSPs, hv_RowSPs, a, row, col;
		HTuple  hv_ColumnSPs, hv_TR, hv_AreaMBs, hv_RowMBs, hv_ColumnMBs;

		//GenEmptyObj(&mmho_RegionsSpur);
		//GenEmptyObj(&mmho_RegionsMB);

		INT64 *PxSP = ConvertFloatToINT64(mmpXdefSP, ND * mmNa);
		INT64 *PySP = ConvertFloatToINT64(mmpYdefSP, ND * mmNa);
		HTuple PSPx_tuple((Hlong *)PxSP, ND*mmNa);
		HTuple PSPy_tuple((Hlong *)PySP, ND*mmNa);

		GenRegionPoints(&mmRegSP, PSPy_tuple, PSPx_tuple);
		Union1(*mmpho_SkelsEPUver, &ho_SkelsEPUver);		// ??????

		Connection(mmRegMB, &mmRegMBs);
		//checking MB defect length (as number of skeleton points)

		Difference(mmRegMBs, *mmpho_Rd, &mmRegMBs);
		SelectShape(mmRegMBs, &mmRegMBs, "area", "and", mmlMB, 99999);
		CountObj(mmRegMBs, &hv_nMB);

		Connection(mmRegSP, &mmRegSPs);
		// checking SP defect length (as number of skeleton points)
		SelectShape(mmRegSPs, &mmRegSPs, "area", "and", mmlSP, 99999);
		Difference(mmRegSPs, ho_SkelsEPUver, &mmRegSPs);
		Difference(mmRegSPs, *mmpho_Rd, &mmRegSPs);
		Union1(mmRegSPs, &mmRegSPs);
		Connection(mmRegSPs, &mmRegSPs);
		CountObj(mmRegSPs, &hv_nSP);
		AreaCenter(mmRegSP, &a, &row, &col);

		if (row == 0 && col == 0)
			mmSPnum = 0;
		else
			mmSPnum = hv_nSP.L();

		AreaCenter(mmRegMB, &a, &row, &col);

		if (row == 0 && col == 0)
			mmMBnum = 0;
		else
			mmMBnum = hv_nMB.L();

		if (mmSPnum > 0)
		{
			HalconCpp::AreaCenter(mmRegSPs, &hv_AreaSPs, &hv_RowSPs, &hv_ColumnSPs);
			TupleGenConst(hv_nSP, 5, &hv_TR);
			GenCircle(&mmCircleSPs, hv_RowSPs, hv_ColumnSPs, hv_TR);
		}
		else
		{
			GenEmptyObj(&mmCircleSPs);
		}

		if (mmMBnum > 0)
		{
			HalconCpp::AreaCenter(mmRegMBs, &hv_AreaMBs, &hv_RowMBs, &hv_ColumnMBs);
			TupleGenConst(hv_nMB, 3, &hv_TR);
			GenCircle(&mmCircleMBs, hv_RowMBs, hv_ColumnMBs, hv_TR);
		}
		else
		{
			GenEmptyObj(&mmCircleMBs);
		}

		// --- Missing ------------------
		INT64 *MISx = ConvertFloatToINT64(mmpXdefMIS, MISnum);
		INT64 *MISy = ConvertFloatToINT64(mmpYdefMIS, MISnum);
		HTuple MISx_tuple((Hlong*)MISx, MISnum);
		HTuple MISy_tuple((Hlong*)MISy, MISnum);

		GenRegionPoints(&mmRegMISS, MISy_tuple, MISx_tuple);

		if (MISnum > 0)
		{
			TupleGenConst(MISnum, 3, &hv_TR);
			GenCircle(&mmCircleMISS, MISy_tuple, MISx_tuple, hv_TR);
		}
		else
		{
			GenEmptyObj(&mmCircleMISS);
		}
		free(MISx);
		free(MISy);



		free(Px);
		free(Py);
		free(PxSP);
		free(PySP);
	}

private:
	INT64* ConvertFloatToINT64(float *dp, int len)
	{
		INT64 *dptr;
		int d;
		int itl = len;

		dptr = (INT64 *)malloc(itl * sizeof(INT64));
		for (int i = 0; i < itl; i++)
		{
			d = *(dp + i);
			*(dptr + i) = d;
		}
		return dptr;
	}

private:
	void FWM_PostProc(float *pw, int *pwg, float *medo, float *pXC, float *pYC, int na, int nvoid, int *pPaddr, 
		int sz1, int sz2, int skip, float ang, float mprc, float sprc, float mabs, float sabs, int dlen, 
		float *pDefMB, float *pXdefMB, float *pYdefMB, float *pDefSP, float *pXdefSP, float *pYdefSP, int *MBnum, int *SPnum,
		int th_miss, float *pDefMIS, float *pXdefMIS, float *pYdefMIS, int *MISnum)
	{
		int caddrb, caddre, cnum;
		int mbnum, spnum, misnum, j;
		//j = 188-1;
		for (j = 1; j < na - 1; j++)
		{
			caddrb = *(pPaddr + j + 0);
			caddre = *(pPaddr + j + 1) - 1;
			cnum = (caddre - caddrb);
			if (cnum > 20)
			{
				// int nvoid = 7;
				FilterRMed(pw + caddrb, pwg + caddrb, medo, pXC + caddrb, pYC + caddrb, cnum, sz1, skip, mprc, sprc, mabs, 
					sabs, dlen, 
					pDefMB + *MBnum, pXdefMB + *MBnum, pYdefMB + *MBnum, pDefSP + *SPnum, pXdefSP + *SPnum, pYdefSP + *SPnum, &mbnum, &spnum, 
					th_miss, pDefMIS + *MISnum, pXdefMIS + *MISnum, pYdefMIS + *MISnum, &misnum,
					0);
				// medo - buffer for RMed
				*SPnum += spnum;
				*MBnum += mbnum;
				*MISnum += misnum;
			}
		}
		j = j;
	}

private:
	void FilterRMed(float *pw, int *pwg, float *medo, float *pXC, float *pYC, int n, int sz1, int skip, float mprc, 
		float sprc, float mabs, float pabs, int dlen, 
		float *pDefMB, float *pXdefMB, float *pYdefMB, float *pDefSP, float *pXdefSP, float *pYdefSP, int *MBnum, int *SPnum, 
		int th_miss, float *pDefMIS, float *pXdefMIS, float *pYdefMIS, int *MISnum,
		int mode)
	{	/// processing of single seleton part of length=n, RMed window=sz1
		/// mode==0  - not using CAD width

		int j;
		int spnum = 0, mbnum = 0, misnum = 0;
		//	float *medo;
		int bw = min(sz1, n);

		float w, wg, wn;
		float dg, dgprc; // deviation from CAD
		float dn, dnprc; // deviation from neighbor
		float def; // defect size
		if (n == 0)
		{
			*SPnum = spnum;
			*MBnum = mbnum;
			return;
		}

		// Running median with Extension at the ends, skip and linear interp (with skip at ends).
		SrunmedSLIExtNoS(pw, medo + MEDOSIZE / 2, medo, n, bw, skip, 10); 

		for (j = 0; j < n - 1; j++)
		{
			w = *(pw + j);
			wg = *(pwg + j);
			wn = *(medo + j);

			dg = w - wg;
			dn = w - wn;

			dgprc = dg * 100. / wg;
			dnprc = dn * 100. / (wn + 0.001);

			def = 0.;
			if (dnprc >= sprc)
				def = dn;

			if (dnprc <= -mprc)
				def = dn;

			if (def > 0.01)
			{
				*(pDefSP++) = def;
				*(pXdefSP++) = *(pXC + j - 1);
				*(pYdefSP++) = *(pYC + j - 1);
				spnum++;
			}
			else if (def < -0.01)
			{
				*(pDefMB++) = def;
				*(pXdefMB++) = *(pXC + j - 1);
				*(pYdefMB++) = *(pYC + j - 1);
				mbnum++;
			}
		}

		// --- FindMissing --------------------------
		int cnt_miss = 0;
		float miss_X, miss_Y;
		for (j = 0; j < n - 1; j++)
		{
			w = *(pw + j);
			if (w <= 0)
			{
				cnt_miss += 1;
				miss_X = *(pXC + j - 1);
				miss_Y = *(pYC + j - 1);
			}
			else break;
		}

		if (cnt_miss >= th_miss)
		{
			*(pDefMIS++) = cnt_miss; 
			*(pXdefMIS++) = miss_X;
			*(pYdefMIS++) = miss_Y;
			misnum += 1;
		}

		cnt_miss = 0;
		for (j = n - 1; j >= 0; j--)
		{
			w = *(pw + j);
			if (w <= 0)
			{
				cnt_miss += 1;
				miss_X = *(pXC + j - 1);
				miss_Y = *(pYC + j - 1);
			}
			else break;
		}

		if (cnt_miss >= th_miss)
		{
			*(pDefMIS++) = cnt_miss; 
			*(pXdefMIS++) = miss_X;
			*(pYdefMIS++) = miss_Y;
			misnum += 1;
		}

		*MISnum = misnum;
		*SPnum = spnum;
		*MBnum = mbnum;
	}

private:
	void SrunmedSLIExtNoS(float* yinp, float* y/*extended*/, float* smo, long n1, int bw_tot, /*int end_rule,*/ int skip, int noskipsz) // 2022.08.01 - running median with skipping [skip] values, with linear interpolation
	{
		/*
			 *  Computes "Running Median" smoother ("Stuetzle" algorithm) with medians of 'band'

			 *  Input:
			 *	yinp(n1)	- responses in order of increasing predictor values
			 *	y(n)		- auxillary array; n = n1 + bw_tot - 1
			 *	n1		- number of observations
			 *	bw_tot		- span of running medians (MUST be ODD !!)
			 //*	end_rule 		-- 0: Keep original data at ends {j; j < b2 | j > n-b2}
			 *		     		-- 1: Constant ends = median(y[1],..,y[bw]) "robust"
			 *	skip		- how many data points to skip between two used points when doing interpolation
			 *	noskipsz	- length of the regions at the beginning and at the end where interpolation is not used; must be no greater than n1/2 and no lesser than bw_tot/2
			 *  Output:
			 *	smo(n)		- smoothed responses

			 //* NOTE:  The 'end' values are just copied !! this is fast but not too nice !
		*/

		/* Local variables */
		int i, rad, rad2n, step, dif;

		rad = (bw_tot - 1) / 2;

		step = skip + 1;
		rad2n = (((bw_tot - 1) / 2) / step) * step;

		dif = n1 - 2 * noskipsz - 1 - ((n1 - 2 * noskipsz - 1) / step)*step;


		for (i = 0; i < rad; i++)
			y[i] = yinp[0];
		//memcpy(y + bw_tot, yinp, n1 * sizeof(float));
		for (i = 0; i < n1; i++)
			y[rad + i] = yinp[i];
		for (i = 0; i < rad; i++)
			y[rad + n1 + i] = yinp[n1 - 1];


		SrunmedProto(y, smo /*- ((bw_tot - 1) / 2)*/, noskipsz + bw_tot - 1, bw_tot, 0);

		SrunmedProto(y + (n1 - noskipsz) - dif, smo + (n1 - noskipsz /*- (bw_tot - 1) / 2*/) - dif, noskipsz + bw_tot - 1 + dif, bw_tot, 0);

		SrunmedProto(y + noskipsz + rad - rad2n, smo + (noskipsz /*- (bw_tot - 1) / 2*/), n1 - 2 * noskipsz + 2 * rad2n, bw_tot, skip);

	} /* SrunmedSLIExt */

private:
	// Prototype
	void SrunmedProto(float* y, float* smo, long n, int bw_tot, int skip) // 2022.08.01 - running median with skipping [skip] values, with linear interpolation
	{
		/* Local variables */
		double rmed, rmin, temp, rnew, yout, yi;
		double rbe, rtb, rse, yin, rts, fa, fb;
		int imin, ismo, i, j, first, last, band2, kminus, kplus, shift, bw, step, num_meds, last_med, a, b, x, rad;

		step = skip + 1;
		bw = (((bw_tot - 1) / 2) / step) * 2 + 1;

		rad = ((bw - 1) / 2)*step;
		//std::cout << "new: bw=" << bw << ", radius=" << bw / 2 << ", step=" << step << "\n";

		if (n < bw_tot)
			return;
		//double *scrat = (double *)malloc(bw, sizeof(double));
		//was
		double *scrat = (double *)malloc((unsigned)bw * sizeof(double));

		//if ((bw-1)*step+1 > n)
		//	error(_("bandwidth/span of running medians is larger than n"));

		/* 1. Compute  'rmed' := Median of the first 'band' values
		   ======================================================== */

		shift = 0;

		for (i = 0; i < bw; ++i)
		{
			scrat[i] = y[i*step + shift];
		}

		/* find minimal value  rmin = scrat[imin] <= scrat[j] */
		rmin = scrat[0]; imin = 0;
		for (i = 1; i < bw; ++i)
			if (scrat[i] < rmin) {
				rmin = scrat[i]; imin = i;
			}
		/* swap scrat[0] <-> scrat[imin] */
		temp = scrat[0]; scrat[0] = rmin; scrat[imin] = temp;
		/* sort the rest of of scrat[] by bubble (?) sort -- */
		for (i = 2; i < bw; ++i) {
			if (scrat[i] < scrat[i - 1]) {/* find the proper place for scrat[i] */
				temp = scrat[i];
				j = i;
				do {
					scrat[j] = scrat[j - 1];
					--j;
				} while (scrat[j - 1] > temp); /* now:  scrat[j-1] <= temp */
				scrat[j] = temp;
			}
		}
		band2 = (bw - 1) / 2;
		rmed = scrat[band2];/* == Median( y[(1:band2)-1] ) */
		/* "malloc" had  free( (char*) scrat);*/ /*-- release scratch memory --*/

		/*
		if (shift == 0) {
			if (end_rule == 0) { //-- keep DATA at end values
				for (i = 0; i < band2*step; ++i)
					smo[i] = y[i];
			}
			else { // if(end_rule == 1)  copy median to CONSTANT end values
				for (i = 0; i < band2*step; ++i)
					smo[i] = rmed;
			}
		}
		*/

		smo[/*band2*step +*/ shift] = rmed;
		num_meds = 1;
		band2++; /* = bw / 2 + 1*/;


		/* Big	FOR Loop: RUNNING median, update the median 'rmed'
		   ======================================================= */
		for (first = step + shift, last = bw * step + shift, ismo = band2 * step + shift;
			last < n;
			first += step, last += step, ismo += step) {

			yin = y[last];
			yout = y[first - step];
			rnew = rmed; /* New median = old one   in all the simple cases --*/

			if (yin < rmed) {
				if (yout >= rmed) {
					kminus = 0;
					if (yout > rmed) {/*	--- yin < rmed < yout --- */
						//if (print_level >= 2) REprintf(": yin < rmed < yout ");
						rnew = yin;/* was -rinf */
						for (i = first; i <= last; i += step) {
							yi = y[i];
							if (yi < rmed) {
								++kminus;
								if (yi > rnew)	rnew = yi;
							}
						}
						if (kminus < band2)		rnew = rmed;
					}
					else {/*		--- yin < rmed = yout --- */
						rse = rts = yin;/* was -rinf */
						for (i = first; i <= last; i += step) {
							yi = y[i];
							if (yi <= rmed) {
								if (yi < rmed) {
									++kminus;
									if (yi > rts)	rts = yi;
									if (yi > rse)	rse = yi;
								}
								else		rse = yi;

							}
						}
						rnew = (kminus == band2) ? rts : rse;
					}
				} /* else: both  yin, yout < rmed -- nothing to do .... */
			}
			else if (yin != rmed) { /* yin > rmed */
				if (yout <= rmed) {
					kplus = 0;
					if (yout < rmed) {/* -- yout < rmed < yin --- */
						rnew = yin; /* was rinf */
						for (i = first; i <= last; i += step) {
							yi = y[i];
							if (yi > rmed) {
								++kplus;
								if (yi < rnew)	rnew = yi;
							}
						}
						if (kplus < band2)	rnew = rmed;
					}
					else { /* -- yout = rmed < yin --- */
						rbe = rtb = yin; /* was rinf */
						for (i = first; i <= last; i += step) {
							yi = y[i];
							if (yi >= rmed) {
								if (yi > rmed) {
									++kplus;
									if (yi < rtb)	rtb = yi;
									if (yi < rbe)	rbe = yi;
								}
								else		rbe = yi;
							}
						}
						rnew = (kplus == band2) ? rtb : rbe;
					}
				} /* else: both  yin, yout > rmed --> nothing to do */
			} /* else: yin == rmed -- nothing to do .... */
			rmed = rnew;
			smo[ismo - rad] = rmed;
			num_meds++;
		} /*     END FOR ------------ big Loop -------------------- */

		free(scrat);

		band2 = (bw - 1) / 2;
		last_med = band2 * step + (num_meds - 1)*step;


		/*if (end_rule == 0) { //-- keep DATA at end values
			for (i = last_med + 1; i < n; ++i)
				smo[i] = y[i];
		}
		else { // if(end_rule == 1)  copy median to CONSTANT end values
			for (i = last_med + 1; i < n; ++i)
				smo[i] = smo[last_med];
		}*/

		if (skip > 0) {
			for (i = 0; i < num_meds - 1; i++) {
				for (j = 1; j < step; j++) {
					x = (band2 + i)*step + j;
					a = (band2 + i)*step;
					b = (band2 + i + 1)*step;
					fa = smo[a - rad];
					fb = smo[b - rad];
					smo[x - rad] = fa + j * (fb - fa) / step; //b-a=step, x-a=j
				}
			}
		}
	}
public:
	void Proc ()
	{
		// --- Image pointers
		HTuple hiptr, h, w, t;
		UINT8 *mmpIm, *mmpImIRB, *mmpImIRBS;
		UINT16 *mmpImCLC;

		GetImagePointer1(m_pIm, &hiptr, &t, &w, &h);
		mmpIm = (UINT8 *)(Hlong *)hiptr.L();

		GetImagePointer1(m_pImIRB, &hiptr, &t, &w, &h);
		mmpImIRB = (UINT8 *)(Hlong *)hiptr.L();

		GetImagePointer1(m_pImIRBS, &hiptr, &t, &w, &h);
		mmpImIRBS = (UINT8 *)(Hlong *)hiptr.L();

		GetImagePointer1(m_pImCLC, &hiptr, &t, &w, &h);
		mmpImCLC = (UINT16 *)(Hlong *)hiptr.L();

		int iw = (int) w.L();
		int ih = (int) h.L();
		int pst = 0;
		float thr = 100;
		int dclcmax = 72;

		// Output data
		if (dW != NULL) free(dW);
		if (dWmin != NULL) free(dWmin);
		if (dPint1x != NULL) free(dPint1x);
		if (dPint1y != NULL) free(dPint1y);
		if (dPint2x != NULL) free(dPint2x);
		if (dPint2y != NULL) free(dPint2y);
		if (dShift != NULL) free(dShift);
		if (dPuseint != NULL) free(dPuseint);

		dW = (float*)malloc(m_tuple_len * sizeof(float));
		dWmin = (float*)malloc(m_tuple_len * sizeof(float));
		dPint1x = (float*)malloc(m_tuple_len * sizeof(float));
		dPint1y = (float*)malloc(m_tuple_len * sizeof(float));
		dPint2x = (float*)malloc(m_tuple_len * sizeof(float));
		dPint2y = (float*)malloc(m_tuple_len * sizeof(float));
		dShift = (float*)malloc(m_tuple_len * sizeof(float));
		dPuseint = (int*)malloc(m_tuple_len * sizeof(int));

		CPU_MSPtProc37 (
			mmpIm, mmpImIRB, mmpImIRBS, mmpImCLC,
			iw, ih, pst, m_tuple_len, thr, dclcmax, 0,
			pP1x, pP1y, pP2x, pP2y, pPnum,
			dW, dWmin, dPint1x, dPint1y, dPint2x, dPint2y, dShift, dPuseint);
	}

	// new version for Pattern 230308 - fixed neighboring same region wires, wmin (not finished), 0 inside pnum
	void CPU_MSPtProc37(
		UINT8 *pIm, UINT8 *pImIRB, UINT8 *pImIRBS, UINT16 *pImCLC,
		int imw, int imh, int pst, int pn, float thr, int dclcmax, int pat0space1,
		float *dP1x, float *dP1y, float *dP2x, float *dP2y, int *dPnum,
		float *dW, float *dWmin, float *dPint1x, float *dPint1y, float *dPint2x, float *dPint2y, float *dShift, int *dPuseint)
	{
		int x1, y1, x2, y2, xc, yc, pnum, useint;
		int v, vp, vn, v1, v2, i, j;
		float wmin, wmax;		 // for width calculation
		float shift = 0.0, xmid, ymid; // for shift calculation
		int PPx[128];  // Bresenham's MS points array
		int PPy[128];
		int Pval[128]; // pnum values array for all MS points


		int g, gp; // current and previous gray values
		int jSPdn;
		int jSPup;
		int jMBdn;
		int jMBup;
		int cIdx; // MS index

		float M1[8] = { -1.,-1.,-1.,-1.,-1.,-1.,-1.,-1. };
		int iM1[8] = { -1.,-1.,-1.,-1.,-1.,-1.,-1.,-1. };
		int iM0[8] = { 0,0,0,0,0,0,0,0 };
		float PIntX[8] = { -1.,-1.,-1.,-1.,-1.,-1.,-1.,-1. }; // intersection points coordinates
		float PIntY[8] = { -1.,-1.,-1.,-1.,-1.,-1.,-1.,-1. };
		float FIntX[8] = { -1.,-1.,-1.,-1.,-1.,-1.,-1.,-1. }; // intersection points coordinates (subpixel)
		float FIntY[8] = { -1.,-1.,-1.,-1.,-1.,-1.,-1.,-1. };
		float fIntX, fIntY; // subpix coord. measured by 
		int Psubpix[8] = { 0,0,0,0,0,0,0,0 };
		int PInti[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };	  // index array of intersection points 
		int PCLC[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };   // CLC array of intersection points 
		int PType[8] = { 0,0,0,0,0,0,0,0 };
		int Pnums[8] = { 0,0,0,0,0,0,0,0 };
		int vpnums;
		//** Intersection point IRBS val,
		int	PIRBS[8] = { -1.,-1.,-1.,-1.,-1.,-1.,-1.,-1. };
		int irbs;
		float ixc;
		float iyc;
		int ptype = 0, begtype = 0, pnfound = 0, btype;
		int PB[8];
		int PE[8];
		int ib = 0;
		int ie = 0;
		//int cIdx = threadIdx.x + blockIdx.x*blockDim.x;
		//int tid = blockDim.x * blockIdx.x + threadIdx.x;
		for (cIdx = pst; cIdx < pst + pn; cIdx++)
		{
			ib = 0;
			ie = 0;
			if (cIdx == 63056)
				cIdx = cIdx;
			memcpy(&PIntX[0], &M1[0], 8 * sizeof(float));
			memcpy(&PIntY[0], &M1[0], 8 * sizeof(float));
			memcpy(&FIntX[0], &M1[0], 8 * sizeof(float));
			memcpy(&FIntY[0], &M1[0], 8 * sizeof(float));
			memcpy(&PInti[0], &iM1[0], 8 * sizeof(int));
			memcpy(&PCLC[0], &iM1[0], 8 * sizeof(int));
			memcpy(&Psubpix[0], &iM0[0], 8 * sizeof(int));
			memcpy(&PType[0], &iM0[0], 8 * sizeof(int));
			//fw = *(d_P1xl + cIdx);
			//*(d_Wl + cIdx) = fw;
			//if (cIdx == 1883423)
			//if (cIdx == 157421)
			/*if (cIdx == 162006)
				cIdx = cIdx;*/
				//int ii = 0;

			int ii = 0, clc, pclc = -2, fi1 = 0;
			pnum = (*(dPnum + cIdx));
			//useint = (*(dPuseint + cIdx));
			x1 = round(*(dP1x + cIdx)); // getting measurement sensor endpoints
			y1 = round(*(dP1y + cIdx));
			x2 = round(*(dP2x + cIdx));
			y2 = round(*(dP2y + cIdx));
			ixc = (x1 + x2) / 2.;
			iyc = (y1 + y2) / 2.;
			//pnum = (*(dPnum + cIdx)) % 250 + 3;
			int deltaX = abs(x2 - x1);
			int deltaY = abs(y2 - y1);
			int signX = x1 < x2 ? 1 : -1;
			int signY = y1 < y2 ? 1 : -1;
			int error = deltaX - deltaY;
			int error2;
			int intind = 0; // intersection index (0 or 1)
			int pind = 0;   // B's point index [0...63]
			int xintc = x1, yintc = y1; // current and previous intersection points
			//v1 = *(pIm + y1 * imw + x1);  // 1st IRB pixel

			// --- ¬¬¬à¬à¬â¬Õ¬Ú¬ß¬Ñ¬ä¬í ¬á¬Ú¬Ü¬ã¬Ö¬Ý¬Ö¬Û ¬ß¬Ñ ¬á¬â¬ñ¬Þ¬à¬Û
			vp = 0;  // previous pixel
			/// filling in Bresenham's array
			while (x1 != x2 || y1 != y2)
			{
				PPx[pind] = x1;
				PPy[pind] = y1;
				v = *(pImIRB + y1 * imw + x1);
				Pval[pind] = v;
				error2 = error * 2;
				if (error2 > -deltaY)
				{
					error -= deltaY;
					x1 += signX;
				}
				if (error2 < deltaX)
				{
					error += deltaX;
					y1 += signY;
				}
				if (pind < 127)
					pind++;
				else
					break;
			} // while
			// Going forward from PS1

			// --- 
			ptype = begtype = pnfound = 0;
			vp = Pval[0];
			for (i = 1; i <= pind - 2; i++)
			{
				xc = PPx[i]; yc = PPy[i];
				v = Pval[i];
				vn = Pval[i + 1];
				//irbs = *(pImIRBS + yc * imw + xc);  // IRBSC pixel value
				if (i == 1 && v == 1) // ¬±¬Ö¬â¬Ó¬í¬Û ¬Ó¬ß¬å¬ä¬â¬Ú 
				{
					ptype = 1;
					PIntY[ii] = yc;
					PIntX[ii] = xc;
					PInti[ii] = i;
					PCLC[ii] = -2;		// ???
					begtype = 1;
					ii = ii + 1;
				}
				if (v == 0)
				{
					begtype = 0;
					pnfound = 0;
				}
				if (v > 1 && v != pnum && begtype == 1)
				{
					begtype = 0;
					pnfound = 0;
					ii = ii - 1;
				}
				btype = 0;
				if (v == pnum)
				{
					if (vp == 0 && (vn == pnum || vn == 1 || vn == 0))
						btype = 1;
					else if ((vp == 1 && vp != pnum) || (vn == 0 && vp != 0))

						btype = -1;
					else
					{
						btype = 0;
						continue;
					}
					PType[ii] = btype;		// ???
					pnfound = 1;
					PIntY[ii] = yc;			// ¬¬¬à¬à¬â¬Õ¬Ú¬ß¬Ñ¬ä¬í ¬á¬Ö¬â¬Ö¬ã¬Ö¬é¬Ö¬ß¬Ú¬ñ
					PIntX[ii] = xc;
					PInti[ii] = i;			// ¬²¬Ñ¬ã¬ã¬ä¬à¬ñ¬ß¬Ú¬Ö
					Psubpix[ii] = 1;		// ---
					if (ii < 7)
						ii = ii + 1;
				}
				if (i == pind - 1 && v == 1 && pnfound == 1)
				{
					PIntY[ii] = yc;
					PIntX[ii] = xc;
					PInti[ii] = i;
					PCLC[ii] = -2;
					ii = ii + 1;
				}
				vp = v;
			}
			//********************************************************************
			int ga[3]; // array of 3 neighboring g
			int nmwc = 0;//*number of MW (main wire) candidates
			int mw = -1;//* MW segment
			int dclc, dmin = 55555; // min CLC distance
			int d, d1, d2; // CLC distances
			int intnum = ii; /// number of intersection points found
			jSPdn = 0;
			float dif0, dif1;
			//if (ii < 7)
			//{
			intnum = ii;
			jSPdn = 0;
			jSPup = ii - 1;
			//}
			/*else
			{
				intnum = 7;
				jSPup = 7;
			}*/

			if (intnum <= 1) //** single pix. space case
			{
				wmin = -1.;
				wmax = -1.;
				jSPdn = 0;
				jSPup = 0;
				
			}
			else
			{ ///**** NORMAL CASE ******

				for (j = 0; j < ii; j++)
				{
					if (PType[j] == 1)
						PB[ib++] = j;
					//ib : = ib + 1
					else if (PType[j] == -1)
						PE[ie++] = j;
					//ie : = ie + 1

				}
				jSPdn = PB[0];
				jSPup = PE[ie - 1];
				if (jSPup == 0 || jSPup == 1 || jSPup == 2)
				{
					jSPup = jSPup;
				}
				else
				{
					jSPup = intnum - 1;
				}
				//*****
				if (intnum < 3)
				{
					jMBdn = jSPdn;
					jMBup = jSPup;
				}
				else if (intnum == 4)
				{
					dif0 = abs(PCLC[PB[0]] - PCLC[PE[0]]);
					dif1 = abs(PCLC[PB[1]] - PCLC[PE[1]]);
					if (dif0 > dif1)
					{
						jMBdn = PB[0];
						jMBup = PE[0];
					}
					else
					{
						jMBdn = PB[1];
						jMBup = PE[1];
					}
				}
				else
				{
					jMBdn = jSPdn;
					jMBup = jSPup;
				}
				//*******

				//* *************** SUBPIX COORD. ******************************
				for (j = 0; j < intnum; j++)
				{
					if (PInti[j] >= 0)
					{
						ga[1] = *(pIm + PPy[PInti[j]] * imw + PPx[PInti[j]]);
						if (PInti[j] > 0)
							ga[0] = *(pIm + PPy[PInti[j] - 1] * imw + PPx[PInti[j] - 1]);
						else
							ga[0] = ga[1];
						if (PInti[j] < pind - 1)
							ga[2] = *(pIm + PPy[PInti[j] + 1] * imw + PPx[PInti[j] + 1]);
						else
							ga[2] = ga[1];
						if (PInti[j] < pind - 1 && PInti[j]>0)
						{
							SubPixCrdP(ga, PInti[j], PPx, PPy, &fIntX, &fIntY, thr);
						}
						else
						{
							fIntX = PPx[PInti[j]];
							fIntY = PPy[PInti[j]];
						}
						FIntX[j] = fIntX;
						FIntY[j] = fIntY;

					}
				}

				//*************************************************
				wmax = sqrt((FIntX[jSPup] - FIntX[jSPdn])*(FIntX[jSPup] - FIntX[jSPdn]) + (FIntY[jSPup] - FIntY[jSPdn])*(FIntY[jSPup] - FIntY[jSPdn]));
				//* wmax : = sqrt((FIntX[intnum - 1] - FIntX[0])*(FIntX[intnum - 1] - FIntX[0]) + (FIntY[intnum - 1] - FIntY[0])*(FIntY[intnum - 1] - FIntY[0]))
				//wmin = sqrt((FIntX[mw] - FIntX[mw + 1])*(FIntX[mw] - FIntX[mw + 1]) + (FIntY[mw] - FIntY[mw + 1])*(FIntY[mw] - FIntY[mw + 1]));
				wmin = sqrt((FIntX[jMBup] - FIntX[jMBdn])*(FIntX[jMBup] - FIntX[jMBdn]) + (FIntY[jMBup] - FIntY[jMBdn])*(FIntY[jMBup] - FIntY[jMBdn]));
				if (wmax > 3.0)
				{ // calculating shift
					xmid = (FIntX[jSPup] + FIntX[jSPdn]) / 2.;
					ymid = (FIntY[jSPup] + FIntY[jSPdn]) / 2.;
					shift = sqrt((ixc - xmid)*(ixc - xmid) + (iyc - ymid)*(iyc - ymid));
				}

				//} // **** normal case end ***


			}

			*(dW + cIdx) = wmax;
			*(dWmin + cIdx) = wmin;
			*(dShift + cIdx) = shift; // ¬³¬Þ¬Ö¬ë¬Ö¬ß¬Ú¬Ö ¬à¬ä ¬ã¬Ö¬ß¬ã¬à¬â¬Ñ???
			if (intnum <= 1)
			{
				*(dPint1x + cIdx) = ixc; // ¬´¬à¬é¬Ü¬Ú ¬á¬Ö¬â¬Ö¬ã¬Ö¬é¬Ö¬ß¬Ú¬ñ 
				*(dPint1y + cIdx) = iyc;
				*(dPint2x + cIdx) = ixc;
				*(dPint2y + cIdx) = iyc;
			}
			else
			{
				*(dPint1x + cIdx) = PIntX[jSPup]; // ¬´¬à¬é¬Ü¬Ú ¬á¬Ö¬â¬Ö¬ã¬Ö¬é¬Ö¬ß¬Ú¬ñ 
				*(dPint2x + cIdx) = PIntX[jSPdn];
				*(dPint1y + cIdx) = PIntY[jSPup];
				*(dPint2y + cIdx) = PIntY[jSPdn];
			}


			/// saving number of intersection points ( 2 points) (left name Puseint for simplicity of changes)
			*(dPuseint + cIdx) = intnum;
			//********************************************	
		} // index cycle end
	}

private:
	// new version for pattern 20220914
	void SubPixCrdP(int *g0, int i0, int *PPx, int *PPy, float *pIntX, float *pIntY, float thr)
	{
		//int PIntX[4], PIntY[4];
		int gmin, gmid, gmax, jmin, jmid, jmax; // points values and numbers
		int Px[3], Py[3];						// 3 conseq. points coordinates
		int dg;
		float dd;

		Px[1] = PPx[i0];
		Px[0] = PPx[i0 - 1];
		Px[2] = PPx[i0 + 1];
		Py[1] = PPy[i0];
		Py[0] = PPy[i0 - 1];
		Py[2] = PPy[i0 + 1];

		jmid = 1;
		gmid = g0[1];

		if (g0[0] > g0[2])
		{
			jmax = 0;
			gmax = g0[0];
			jmin = 2;
			gmin = g0[2];
		}
		else
		{
			jmax = 2;
			gmax = g0[2];
			jmin = 0;
			gmin = g0[0];
		}

		if (gmax < thr)
		{
			*pIntX = Px[jmax];
			*pIntY = Py[jmax];
		}
		else if (gmin > thr)
		{
			*pIntX = Px[jmin];
			*pIntY = Py[jmin];
		}
		//* * normal interpolation case
		else if (gmid >= thr)
		{
			dg = gmid - gmin;
			if (dg != 0)
			{
				dd = (g0[jmid] - thr) / dg;
				*pIntX = Px[jmid] - (Px[jmid] - Px[jmin])*dd;
				*pIntY = Py[jmid] - (Py[jmid] - Py[jmin])*dd;
			}
			else
			{
				*pIntX = (Px[jmid] + Px[jmin]) / 2.;
				*pIntX = (Py[jmid] + Py[jmin]) / 2.;
			}

		}
		else if (gmid < thr)
		{
			dg = gmax - gmid;
			if (dg != 0)
			{
				dd = (g0[jmax] - thr) / dg;
				*pIntX = Px[jmax] - (Px[jmid] - Px[jmax])*dd;
				*pIntY = Py[jmax] - (Py[jmid] - Py[jmax])*dd;
			}
			else
			{
				*pIntX = (Px[jmid] + Px[jmax]) / 2.;
				*pIntY = (Py[jmid] + Py[jmax]) / 2.;
			}
		}
	}

};

