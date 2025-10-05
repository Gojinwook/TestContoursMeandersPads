#pragma once

#include <iostream>
#include <vector>
#include <atlstr.h>
#include <fstream>
#include <cmath>

#include <cstring>
#include <string.h>

#include <stdio.h>
#include <basetsd.h>
#include <memory.h>
#include <set>
#include <stdlib.h>
#include <filesystem>

#include "HalconCpp.h"


using namespace HalconCpp;
//using namespace std;
namespace Functions
{
	void DistPointToLineSegmH(HTuple hv_y, HTuple hv_x, HTuple hv_y1, HTuple hv_x1, HTuple hv_y2,
		HTuple hv_x2, HTuple *hv_distance, HTuple *hv_ym, HTuple *hv_xm, HTuple *hv_t);
	void DistPointToLineSegm(float y, float x, float y1, float x1, float y2,
		float x2, float *distance, float *ym, float *xm, float *t);
	void CircularSector(int isz, int n, int ki, int *K);
	void DistanceContours2(float *pRowI, float *pColI, int nI, float *pRowG, float *pColG, int nG,
		int isz, float *pD, int ptop);
	void DistanceContours2H(HTuple hv_RowI, HTuple hv_ColI, HTuple hv_RowG, HTuple hv_ColG,
		HTuple hv_isz, HTuple *hv_D);
	float* ConvertTupleToFloat(HTuple T);
	void FloatToTuple(float *dp, int len, HTuple &tuple);


	void MeasureDisplacementH(HObject ho_Im, HObject ho_RegionInoD, HObject ho_MeanderRects,
		HObject ho_RegionsGrMe, HObject ho_ContourGrsm, HTuple hv_meander, HTuple hv_thr,
		HTuple hv_RowGsm, HTuple hv_ColGsm, HTuple *hv_Displacement);
	void MoveContourH(HObject ho_Contour, HObject *ho_ContourOut, HTuple hv_mr, HTuple hv_mc);
	void Region_Threshold_SubPixH(HObject ho_RegSel, HObject ho_Im, HTuple hv_Thr, HTuple *hv_RowsSub,
		HTuple *hv_ColsSub);
	int Region_Threshold_SubPix(HObject ho_Im, HObject ho_RegSel, int thr, float *rows_sub, float *cols_sub);

	void ReverseContourH(HObject ho_ContourIn, HObject *ho_ContourOut);

	void BuildBorderContour(HObject ho_Bordersi, HObject *ho_Bordercl, HObject *ho_BorderEPs);
	void BuildRealContour(HObject ho_Im, HObject ho_Rectangle5, HObject *ho_ContourOut, HObject *ho_BorderEPs,
		HObject *ho_RegionIR, HTuple hv_ctype, HTuple hv_thr);
}