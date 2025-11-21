/**
 * \copyright (C) Synapse Imaging 2023
 *
 * @File Name
 *      FLT_All.cpp
 *
 * @Summary
 *
 * @Description
 *
 *
 *
 * @authors Igor Dunin-Barkowski, Iurii Kim
 * @version 1.0
 * @date 2023.05.19
 */
 /* ************************************************************************** */
 /* Section: Included Files                                                    */
 /* ************************************************************************** */
#include "FLT_All.h"

/* ************************************************************************** */
/* Section: Functions                                                         */
/* ************************************************************************** */
void Filter_Line_Thickness (
	HTuple hv_pWG_line, 
	HTuple hv_dWmin_line, 
	int line_len, 
    HTuple hv_move_avg_h, 
	HTuple hv_min_len_direct, 
	HTuple *hv_dWmin_Deviation, 
	HTuple *hv_dWmin_Deviation_Avg)
{
	// Local control variables
	HTuple  hv_Median, hv_line_end;
	HTuple  hv_dWmin_flat, hv_Mean;
	HTuple  hv_dWmin_flat_Mean;

	TupleMean (hv_pWG_line, &hv_Median);
	if (line_len > hv_Median * 2)
	{
		TupleInt (line_len - (hv_Median * 2), &hv_line_end);
	}
	else
	{
		hv_line_end = 0;
	}
	int line_end_I = int(hv_line_end);
	//hv_pWG_line = hv_pWG_line.TupleSelectRange (0, hv_line_end);
	//hv_dWmin_line = hv_dWmin_line.TupleSelectRange (0, hv_line_end);

	//** Selecting straight sections
	// First line width
	int64_t* hv_pWG_line_F = hv_pWG_line.LArr();
	int64_t w_size = hv_pWG_line_F[0];
	// Beginning of a straight section
	int w_start = 0;
	// Straight section length
	int w_len = 0;

	// Initialize output tuples
	TupleGenConst(hv_line_end, 0.0, hv_dWmin_Deviation);
	TupleGenConst(hv_line_end, 0.0, hv_dWmin_Deviation_Avg);

	for (int pos = 0; pos < line_end_I; pos++)
	{
		// The line width has changed. End of straight section
		if (w_size != hv_pWG_line_F[pos] || pos == line_end_I - 1)
		{
			// If the length of the straight section is greater than the threshold
			if (w_len > hv_min_len_direct)
			{
				//** Calculation of deviation from the mean
				// Thickness on a straight section
				hv_dWmin_flat = hv_dWmin_line.TupleSelectRange(w_start, (w_start + w_len) - 1);
				//tuple_median (dWmin_flat, Mean)
				TupleMean(hv_dWmin_flat, &hv_Mean);
				//tuple_min (dWmin_flat, Mean)
				TupleSub(hv_dWmin_flat, hv_Mean, &hv_dWmin_flat_Mean);

				TupleDiv(hv_dWmin_flat_Mean, hv_Mean / 100, &hv_dWmin_flat_Mean);
				// TODO: For control, add if necessary to view the curve not clipped by the threshold
				//(*hv_dWmin_Deviation)[HTuple::TupleGenSequence(w_start, (w_start + w_len) - 1, 1)] = hv_dWmin_flat_Mean;

				double* hv_dWmin_flat_Mean_F = hv_dWmin_flat_Mean.DArr();
				double* hv_dWmin_Deviation_Avg_F = hv_dWmin_Deviation_Avg->DArr();

				int move_avg_h = int(hv_move_avg_h);
				int move_pos = int(pos + (hv_move_avg_h / 2) - w_len - hv_move_avg_h);

				// --- Moving Average -------------
				float sum_mov = hv_dWmin_flat_Mean_F[0];
				for (int k = 0; k < w_len; k++)
				{
					if (k >= move_avg_h)
					{
						int avg_pos = move_pos + k;
						hv_dWmin_Deviation_Avg_F[avg_pos] = sum_mov / move_avg_h;
						sum_mov = sum_mov - hv_dWmin_flat_Mean_F[k - move_avg_h];
					}
					sum_mov = sum_mov + hv_dWmin_flat_Mean_F[k];
				}
			}

			// Initializing a new tangent
			w_size = hv_pWG_line_F[pos];
			w_start = pos;
			w_len = 0;
		}
		w_len += 1;
	}
	return;
}

void Filter_Line_Thickness_All (
	HTuple hv_Pnum, HTuple hv_pWG, HTuple hv_dWmin, HTuple hv_move_avg_h, 
    HTuple hv_min_len_direct, HTuple hv_threshold, HTuple hv_threshold_area, 
	std::vector<int64_t>* finde_pos,
	std::vector<double>* finde_val)
{
	// Local control variables
	HTuple  hv_t_len;
	HTuple  hv_Pnum_line, hv_pWG_line, hv_dWmin_line;
	HTuple  hv_dWmin_Deviation, hv_dWmin_Deviation_Avg;
	HTuple  hv_m_len;

	int64_t* hv_Pnum_I = hv_Pnum.LArr();

	//** --- All lines test--------------------------------------------------------------------------
	TupleLength(hv_Pnum, &hv_t_len);
	// Initialization
	int64_t hv_curr_num = hv_Pnum_I[0];
	int64_t hv_t_len_I = int(hv_t_len);
	int hv_pos_start = 0;

	// Let's look at the whole dull and select all the lines
	for (int t = 0; t < hv_t_len_I; t++)
	{
		// Discovery of a new line
		if (hv_Pnum_I[t] != hv_curr_num)
		{
			int hv_pos_end = t - 1;

			//** --- Get the line we need ------------------------------------------------
			hv_Pnum_line = hv_Pnum.TupleSelectRange(hv_pos_start, hv_pos_end);
			hv_pWG_line = hv_pWG.TupleSelectRange(hv_pos_start, hv_pos_end);
			hv_dWmin_line = hv_dWmin.TupleSelectRange(hv_pos_start, hv_pos_end);
			int hv_line_len = hv_pos_end - hv_pos_start;

			Filter_Line_Thickness (
				hv_pWG_line, 
				hv_dWmin_line, 
				hv_line_len, 
				hv_move_avg_h, 
				hv_min_len_direct, 
				&hv_dWmin_Deviation, 
				&hv_dWmin_Deviation_Avg);

			//** --- We consider the area if there is an excess of the threshold -----------------------------
			TupleLength(hv_dWmin_Deviation_Avg, &hv_m_len);
			int hv_th_area = 0;
			int hv_th_area_start = 0;
			int hv_th_area_end = 0;

			int hv_m_len_I = int(hv_m_len);
			int hv_threshold_I = int(hv_threshold);
			double* hv_dWmin_Deviation_Avg_F;
			if (hv_m_len_I)									// If there is data, then we take the pointer. Avoiding the Exception
			{
				hv_dWmin_Deviation_Avg_F = hv_dWmin_Deviation_Avg.DArr();

				for (int m = 0; m < hv_m_len_I; m++)
				{
					//Get_Micros_Delay(42);
					float val = fabs(hv_dWmin_Deviation_Avg_F[m]);
					//Get_Micros_Delay(431);

					if (val < hv_threshold_I || m == hv_m_len_I - 1)
					{
						// If the threshold is greater than the sum threshold
						if (0 != (hv_th_area > hv_threshold_area))
						{
							//Get_Micros_Delay(43);
							hv_th_area_end = m;
							int hv_th_area_pos = hv_th_area_start + ((hv_th_area_end - hv_th_area_start) / 2);
							//Get_Micros_Delay(44);

							finde_pos->push_back(int64_t((hv_pos_end + hv_th_area_pos) - hv_line_len));
							finde_val->push_back(double(hv_th_area));
							//Get_Micros_Delay(45);
						}
						hv_th_area = 0;
						hv_th_area_start = m;
					}
					else
					{
						// Sum everything that is greater than the threshold
						// th_area := th_area + abs(dWmin_Deviation_Avg[m])
						hv_th_area += 1;
					}
				}
			}
			hv_curr_num = hv_Pnum_I[t];
			hv_pos_start = t;
		}
	}
	return;
}
/* ************************************************************************** */
/* End of file                                                                */
/* ************************************************************************** */


