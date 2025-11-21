
// TestContoursDlg.h : header file
//

#pragma once

#include "HalconCpp.h"
#include "FWMFuncs.h"

using namespace HalconCpp;


// CTestContoursDlg dialog
class CTestContoursDlg : public CDialogEx
{
// Construction
public:
	CTestContoursDlg(CWnd* pParent = nullptr);	// standard constructor

	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTCONTOURS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support



// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	HObject m_ho_CG, m_ho_CI, m_ho_Cbj, m_ho_ContoursGrsm, m_ho_MeanderRects, m_ho_RegionG, m_ho_RegionI, m_ho_RegionGPad;
	HObject m_ho_ContoursGPadsIsol, m_ho_RegionsGPadsIsol, m_ho_ContoursGPadsCon, m_ho_RegionsGPadsCon, m_ho_ContoursWireAngles, m_ho_RectanglesWireAngles;
	HTuple m_hv_ColG, m_hv_RowG, m_hv_ColI, m_hv_RowI, m_hv_DistIG, m_hv_DistIG2;
	HObject m_ho_Im, m_ho_Iminv, m_ho_Gi;
	HTuple m_hv_thr, m_hv_ctype, m_hv_meander, m_hw_absmb, m_hw_abssp, m_hw_absmbwa, m_hw_absspwa, m_hw_absmbpad, m_hw_abssppad;
	HTuple  m_hv_pad, m_hv_padc, m_hv_wa;
	bool m_ctype;
	float *medo;
	//float *pmedo = NULL;
	int m_fsz, m_fszwa, m_fszpad;
	int num; // repeat number
	int disp; // display results
	HObject m_ho_Rectangle5;
	HWindow hWindow;
	HTuple m_hv_pathModel;

	HObject m_ho_ImIRBP, m_ho_ImIRBS;
	HObject m_ho_RegProc, m_ho_RegNoProc, m_ho_RegionCut, m_ho_SkeletonsFWM, m_ho_RegionsPNPi, m_ho_SkeletonsFWMS, m_ho_RegionsPNSi, m_ho_ImCLC;
	HObject m_ho_RegionPH;
	HObject m_ho_RegionsIsl;
	HObject m_ho_RegionISnoIslnoPh, m_ho_RegionInoIslnoPh;
	HTuple m_hv_Width, m_hv_Height, m_hv_threshold, m_hv_thresholdS, m_hv_PHrmin, m_hv_PHamin,
		m_hv_Islrmin, m_hv_Islamin, m_hv_PHrminS, m_hv_PHaminS,
		m_hv_IslrminS, m_hv_IslaminS;
	// FWM
	CFWM* m_pFWM;
	HTuple hv_P1x, hv_P1y, hv_P2x, hv_P2y, hv_P3x, hv_P3y, hv_Pnum, hv_Pnum2, hv_PaddrR, hv_PaddrC, hv_WG, hv_Wi, hv_Puseint;
	
	int *pPnum, *pPaddrR, *pPaddrC, *pPuseint;
	float *pP1x, *pP1y, *pP2x, *pP2y, *pP3x, *pP3y; // measurement tool points arrays
	// proc. results:
	float *pWidth, *pWmin, *pmedo, *pmedoe;
	float *pPInt1x, *pPInt1y, *pPInt2x, *pPInt2y, *pPInt3x, *pPInt3y, *pPInt4x, *pPInt4y;	// intersection points arrays
	float *pShift;
	// post proc. results:
	float *pDefMB, *pXdefMB, *pYdefMB, *pDefSP, *pXdefSP, *pYdefSP;
	int  *pWG;
	int Np;		// number of MSs
	int Na;		// number of addresses (SkeletonsGthin regions)
	int NaC;		// number of addresses (contours)

	HObject m_ho_RegionsSP, m_ho_RegionsMB;
	// FWM Parameters
	int fwmw; // wire to save
	int lMB = 1;			// MB length
	float prcMB = 50.; 		// MB % // % nearby for MB (Pattern)
	float absMB = 3.;		//  absolute MB value (Pattern)(in pixels)
	float minMB = 4.5;		//  minimal MB value (in pixels)
	float prcSP = 40.; 		// % nearby  for spur (Pattern)
	float absSP = 1.5;		//  absolute spur value (in pixels)
	float minSP = 10;		//  minimal spur value (in pixels)
	float narrowwp = 0.7;	//  pattern width to detect as narrow
	float widewp = 10.;	//  pattern width to detect as too wide

	float minwp = 4.;		//  minimal pattern width to use %
	int sz1 = 15;			// Running median sizes for FWM 
	HTuple hv_dilFWM = 10;			// dilation value for FWM (used in SkeletonsCheckPrep() )

	// FWMS
	//CFWM* m_pFWM;
	HTuple hv_P1xS, hv_P1yS, hv_P2xS, hv_P2yS, hv_P3xS, hv_P3yS, hv_PnumS, hv_Pnum2S, hv_PaddrRS, hv_PaddrCS, hv_WGS, hv_WiS, hv_PuseintS;

	int *pPnumS, *pPaddrRS, *pPaddrCS, *pPuseintS;
	float *pP1xS, *pP1yS, *pP2xS, *pP2yS, *pP3xS, *pP3yS; // measurement tool points arrays
	// proc. results:
	float *pWidthS, *pWminS, *pmedoS, *pmedoeS;
	float *pPInt1xS, *pPInt1yS, *pPInt2xS, *pPInt2yS, *pPInt3xS, *pPInt3yS, *pPInt4xS, *pPInt4yS;	// intersection points arrays
	float *pShiftS;
	// post proc. results:
	float *pDefMBS, *pXdefMBS, *pYdefMBS, *pDefSPS, *pXdefSSP, *pYdefSPS;
	int  *pWGS;
	int NpS;		// number of MSs
	int NaS;		// number of addresses (space skeleton regions)
	int NaCS;		// number of addresses (contours)

	HObject m_ho_RegionsSPS, m_ho_RegionsMBS;
	// FWMS Parameters
	int fwmwS=10;
	int lMBS = 1;			// MB length
	float prcMBS = 50.; 		// MB % // % nearby for MB (Space)
	float absMBS = 3.;		//  absolute Space MB value (Space)(in pixels)
	float minMBS = 4.5;		//  minimal Space MB value (in pixels)
	float prcSPS = 40.; 		// % nearby  for spur (Space)
	float absSPS = 1.5;		//  absolute Space spur value (in pixels)
	float minSPS = 10;		//  minimal Space spur value (in pixels)
	float narrowwS = 0.7;	//  Space width to detect as narrow
	float widewS = 10.;	//  Space width to detect as too wide

	float minwS = 4.;		//  minimal pattern width to use %
	int sz2 = 15;			// Running median sizes for FWMS 
	HTuple hv_dilFWMS = 10;			// dilation value for FWMS (used in SkeletonsCheckPrep() )
	

	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnEnChangeEdit15();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit17();
	afx_msg void OnEnChangeEdit18();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnEnChangeEdit19();
	afx_msg void OnEnChangeEdit22();
	afx_msg void OnEnChangeEdit23();
	afx_msg void OnEnChangeEdit21();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnEnChangeEdit31();
	afx_msg void OnEnChangeEdit32();
	afx_msg void OnEnChangeEdit34();
	afx_msg void OnEnChangeEdit33();
	afx_msg void OnEnChangeEdit35();
	afx_msg void OnEnChangeEdit36();
	afx_msg void OnEnChangeEdit37();
	afx_msg void OnEnChangeEdit38();
	afx_msg void OnEnChangeEdit39();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit40();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnEnChangeEdit41();
	afx_msg void OnEnChangeEdit42();
	afx_msg void OnEnChangeEdit43();
	afx_msg void OnEnChangeEdit44();
	afx_msg void OnEnChangeEdit45();
	afx_msg void OnEnChangeEdit46();
	afx_msg void OnEnChangeEdit47();
	afx_msg void OnEnChangeEdit48();
};
