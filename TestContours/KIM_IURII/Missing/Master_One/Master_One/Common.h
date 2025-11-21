#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <atlstr.h>

#include <fstream>
#include <cmath>

#include "HalconCpp.h"
#include "HDevThread.h"

using namespace HalconCpp;
using namespace std;

void CString_2_HTuple(CString str, HTuple* tuple);


float* ConvertTupleToFloat(HTuple T);
int* ConvertTupleToInt(HTuple T);
float* Load_Tuple_Bin_F(CString path, CString name, int* tuple_len);
int* Load_Tuple_Bin_I(CString path, CString name, int* tuple_lens);
void Print_Msg(char* str, ...);
uint64_t Get_Micros();
void Get_Micros_Delay(int num);
uint64_t Get_Delta_Micros();


 

