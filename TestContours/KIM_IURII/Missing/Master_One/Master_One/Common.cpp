#include "Common.h"
#include <chrono>
#include <ctime>


// --------------------------------------------------------------------------
void CString_2_HTuple(CString str, HTuple* tuple)
{
	CStringA s(str);
	*tuple = (LPSTR)s.GetBuffer();
}
// --------------------------------------------------------------------------
float* ConvertTupleToFloat(HTuple T)
{
	double *dptr, d;
	//float f;
	HTuple tl;
	float *dp;

	TupleLength(T, &tl);
	int itl = tl.L();

	dptr = T.ToDArr();
	//iptr = hv_tst.ToIArr();
	dp = (float *)malloc(itl * sizeof(float));
	for (int i = 0; i < itl; i++)
	{
		d = *(dptr + i);
		*(dp + i) = d;
	}
	return dp;
}
// --------------------------------------------------------------------------
int* ConvertTupleToInt(HTuple T)
{
	int *iptr, id;
	Hlong *hlptr;
	//float f;
	HTuple tl;
	int *ip;

	TupleLength(T, &tl);
	int itl = tl.L();

	hlptr = T.ToLArr();
	//iptr = hv_tst.ToIArr();
	ip = (int *)malloc(itl * sizeof(int));
	for (int i = 0; i < itl; i++)
	{
		id = (int)*(hlptr + i);
		*(ip + i) = id;
	}
	return ip;
}
/** **************************************************************************
* @Summary
*		¬©¬Ñ¬Ô¬â¬å¬Ø¬Ñ¬Ö¬Þ bin ¬æ¬Ñ¬Û¬Ý, ¬Ö¬ã¬Ý¬Ú ¬Ö¬ã¬ä¬î.
*		¬¦¬ã¬Ý¬Ú ¬ß¬Ö¬ä, ¬ä¬à ¬Ù¬Ñ¬Ô¬â¬å¬Ø¬Ñ¬Ö¬Þ Tuple, ¬Ü¬à¬ß¬Ó¬Ö¬â¬ä¬Ú¬â¬å¬Ö¬Þ ¬Ú ¬ã¬à¬ç¬â¬Ñ¬ß¬ñ¬Ö¬Þ
*/
float* Load_Tuple_Bin_F(CString path, CString name, int* tuple_len)
{
	float *data;
	CStdioFile stdFile;

	if (stdFile.Open(path + _T("\\Bin\\") + name + _T(".dat"), CFile::modeRead | CFile::typeBinary))
	{
		data = (float*)malloc(stdFile.GetLength());
		stdFile.Read(data, stdFile.GetLength());
		*tuple_len = stdFile.GetLength() / sizeof(float);
		stdFile.Close();
	}
	else
	{
		HTuple tuple;
		HTuple t_name, t_path;
		CString_2_HTuple(name, &t_name);
		CString_2_HTuple(path, &t_path);

		ReadTuple(t_path + "\\" + t_name + ".tup", &tuple);
		data = ConvertTupleToFloat(tuple);
		*tuple_len = tuple.Length();
		CreateDirectory(path + _T("\\Bin"), NULL);
		if (stdFile.Open(path + _T("\\Bin\\") + name + _T(".dat"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
		{
			stdFile.Write(data, sizeof(float) * tuple.Length());
			stdFile.Close();
		}
	}

	return data;
}
int* Load_Tuple_Bin_I(CString path, CString name, int* tuple_len)
{
	int *data;
	CStdioFile stdFile;

	if (stdFile.Open(path + _T("\\Bin\\") + name + _T(".dat"), CFile::modeRead | CFile::typeBinary))
	{
		data = (int*)malloc(stdFile.GetLength());
		stdFile.Read(data, stdFile.GetLength());
		*tuple_len = stdFile.GetLength() / sizeof(int);
		stdFile.Close();
	}
	else
	{
		HTuple tuple;
		HTuple t_name, t_path;
		CString_2_HTuple(name, &t_name);
		CString_2_HTuple(path, &t_path);

		ReadTuple(t_path + "\\" + t_name + ".tup", &tuple);
		data = ConvertTupleToInt(tuple);
		*tuple_len = tuple.Length();
		CreateDirectory(path + _T("\\Bin"), NULL);
		if (stdFile.Open(path + _T("\\Bin\\") + name + _T(".dat"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
		{
			stdFile.Write(data, sizeof(float) * tuple.Length());
			stdFile.Close();
		}
	}

	return data;
}



/** ----------------------------------------------------------------------
 * @Summary
 *      Adding a message for asynchronous output
 */
void Print_Msg(char* str, ...)
{
	va_list	listp;
	va_start(listp, str);
	try
	{
		CString print_str("PADS: ");
		print_str += str;

		char* str_next = va_arg(listp, char*);
		while (*str_next != '\n')
		{
			print_str += " ";
			print_str += str_next;
			str_next = va_arg(listp, char*);
		}
		//prind_msg.push_back(print_str);
	}
	catch (...)
	{

	}
	va_end(listp);
}

uint64_t Get_Micros()
{
	uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch())
		.count();
	return us;
}
void Get_Micros_Delay(int num)
{
	static uint64_t end_time = Get_Micros();
	static uint64_t start_time = Get_Micros();

	end_time = Get_Micros();
	std::cout << "Filter_Line_Thickness " << num  << ": " << end_time - start_time << std::endl;
	start_time = Get_Micros();
}
uint64_t Get_Delta_Micros()
{
	static uint64_t end_time = Get_Micros();
	static uint64_t start_time = Get_Micros();

	end_time = Get_Micros();
	uint64_t ret = end_time - start_time;
	start_time = Get_Micros();
	return ret;
}




