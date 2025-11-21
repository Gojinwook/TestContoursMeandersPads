/**
 * \copyright (C) Synapse Imaging 2023
 *
 * @File Name
		Scratch_Matching.cpp
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
#include "Scratch_Matching.h"

void How_To_Run_Scratch_Matching ()
{
	HTuple path;
	path = "C:/Work/Data/Scratch & Other/249/";

	HImage ho_Img_Im;
	ho_Img_Im.ReadImage (path + "Im.tif");

	// The method is very, very sensitive to thresholds!!!!
	int min_gray = 252;
	int max_gray = 255;
	HObject ho_Region_Out;
	GenEmptyRegion(&ho_Region_Out);

	// --- Finding the coordinates of the scratches
	Scratch_Matching (&ho_Img_Im, min_gray, max_gray, &ho_Region_Out);

	// TEST. Save to a file to upload to Halcon and check 
	WriteRegion(ho_Region_Out, path + "/Out/scratch.reg");

}

// Main procedure 
void Scratch_Matching (HObject *ho_Img_Im, int th_min, int th_max, HObject* ho_Region_Out)
{
	TIMER_CALL(std::cout << "Scratch_Matching::Pre-processing ..." << std::endl);

	// ------------ Search preliminary ------------------
	HObject  ho_Reg_Im, ho_REG_Eyes0, ho_REG_Eyes1, ho_REG_Eyes2, ho_REG_Eyes3;
	Threshold (*ho_Img_Im, &ho_Reg_Im, th_min, th_max);
	ErosionCircle (ho_Reg_Im, &ho_REG_Eyes0, 1.1);
	Connection (ho_REG_Eyes0, &ho_REG_Eyes1);
	SelectShape(ho_REG_Eyes1, &ho_REG_Eyes2, "area", "or", 16, 100000);
	SelectShape (ho_REG_Eyes2, &ho_REG_Eyes3, "struct_factor", "or", 12, 300);

	// New filter
	SelectShape(ho_REG_Eyes3, &ho_REG_Eyes3, (HTuple("rectangularity").Append("ra")),
		"and", (HTuple(0.3).Append(15)), (HTuple(1.0).Append(1500)));

	TIMER_CALL(std::cout << "Scratch_Matching::Pre-processing.  Lead time = " << Get_Delta_Micros() << std::endl);

	// ------------ Search for objects on the same line -----------
	// --- We go through all the objects of the regions and look for those that lie on the same line

	// We form rectangles around the found regions
	HObject ho_ERec;
	HTuple hv_Length1, hv_Length2, hv_rec_row, hv_rec_col, hv_rec_phi;
	HTuple hv_rec_len;
	SmallestRectangle2 (ho_REG_Eyes3, &hv_rec_row, &hv_rec_col, &hv_rec_phi, &hv_Length1, &hv_Length2);
	GenRectangle2 (&ho_ERec, hv_rec_row, hv_rec_col, hv_rec_phi, hv_Length1, hv_Length2);
	TupleLength (hv_rec_phi, &hv_rec_len);

	// --- Preparing data for processing
	int64_t t_len = int (hv_rec_len);
	// Getting Pointers to Values
	double* ptr_phi = hv_rec_phi.DArr ();
	double* ptr_row = hv_rec_row.DArr ();
	double* ptr_col = hv_rec_col.DArr ();

	// Skip regions array
	int *arr_skip = new int[t_len];
	for (int i = 0; i < t_len; i++)
	{
		arr_skip[i] = 0;
	}

	HTuple  hv_line_row1, hv_line_col1;
	HTuple hv_line_len;

	// For all regions
	for (int pos = 0; pos < t_len; pos++)
	{
		if (arr_skip[pos]) continue; // Skip the marked rectangles

		hv_line_len = 0;
		hv_line_row1 = HTuple();
		hv_line_col1 = HTuple();

		double cur_phi = ptr_phi[pos];
		double cur_y = ptr_row[pos];
		double cur_x = ptr_col[pos];

		// Viewing all regions relative to the current
		for (int i = pos + 1; i < t_len; i++)
		{
			if (arr_skip[i]) continue; // Skip the marked rectangles

			// Angle calculation, relative to the first point
			double phi = 3.14 - fmod (atan2(ptr_row[i] - cur_y, ptr_col[i] - cur_x), M_PI_P2);
			// Difference between current angle and angle before region
			double delta_phi_point = phi - cur_phi;	
			// Difference between current angle and rectangle angle
			double delta_phi_rect = ptr_phi[i] - cur_phi; 
			// Distance between rectangles
			float rect_len = sqrt (pow ((ptr_row[i] - cur_y), 2) + pow ((ptr_col[i] - cur_x), 2));

			// If the rectangle lies on a line parallel to the rectangle
			// If the corner of the rectangle is the same as the corner of the current rectangle
			// If the distance between the rectangles is less than the threshold
			if (abs (delta_phi_point) < 0.09 &&  abs (delta_phi_rect) < 0.07 && rect_len < 1000)
			{
				TupleLength(hv_line_row1, &hv_line_len);
				if (int (hv_line_len) == 0)
				{
					// Adding the first point
					TupleConcat(hv_line_row1, cur_y, &hv_line_row1);
					TupleConcat(hv_line_col1, cur_x, &hv_line_col1);
				}

				cur_y = ptr_row[i];
				cur_x = ptr_col[i];
				TupleConcat(hv_line_row1, cur_y, &hv_line_row1);
				TupleConcat(hv_line_col1, cur_x, &hv_line_col1);

				arr_skip[i] = 1; // Mark the rectangle as processed
			}
		}

		// If more than 4 rectangles are found that lie on a line
		if (int (hv_line_len) >= 4)
		{
			// Save the found objects
			HObject  ho_Region1, ho_Region1_DIL;
			GenRegionPolygon(&ho_Region1, hv_line_row1, hv_line_col1);
			DilationCircle(ho_Region1, &ho_Region1_DIL, 6.5);
			Union2(*ho_Region_Out, ho_Region1_DIL, ho_Region_Out);
		}
	}

	delete[] arr_skip;

	TIMER_CALL(std::cout << "Scratch_Matching::Scratch_Matching.  Lead time = " << Get_Delta_Micros() << std::endl);
}



/* ************************************************************************** */
/* End of file                                                                */
/* ************************************************************************** */

