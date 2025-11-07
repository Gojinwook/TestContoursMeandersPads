
// TestContoursDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TestContours.h"
#include "TestContoursDlg.h"
#include "afxdialogex.h"

#include <vector>
#include <complex>
#include <cmath>

#include "Functions.h"

#define WINST 1930


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Functions;

float *pmedo = NULL; // RM buffer
int save = 0;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestContoursDlg dialog



CTestContoursDlg::CTestContoursDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTCONTOURS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestContoursDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestContoursDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestContoursDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestContoursDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestContoursDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestContoursDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_CHECK1, &CTestContoursDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestContoursDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_CHECK2, &CTestContoursDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestContoursDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestContoursDlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &CTestContoursDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CTestContoursDlg::OnEnChangeEdit2)
	ON_WM_MOUSEWHEEL()
	ON_EN_CHANGE(IDC_EDIT3, &CTestContoursDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CTestContoursDlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON8, &CTestContoursDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CTestContoursDlg::OnBnClickedButton9)
	ON_EN_CHANGE(IDC_EDIT5, &CTestContoursDlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON10, &CTestContoursDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_CHECK3, &CTestContoursDlg::OnBnClickedCheck3)
	ON_EN_CHANGE(IDC_EDIT6, &CTestContoursDlg::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON11, &CTestContoursDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CTestContoursDlg::OnBnClickedButton12)
	ON_EN_CHANGE(IDC_EDIT7, &CTestContoursDlg::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_BUTTON13, &CTestContoursDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CTestContoursDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CTestContoursDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CTestContoursDlg::OnBnClickedButton16)
	ON_EN_CHANGE(IDC_EDIT11, &CTestContoursDlg::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT14, &CTestContoursDlg::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, &CTestContoursDlg::OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, &CTestContoursDlg::OnEnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT13, &CTestContoursDlg::OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT17, &CTestContoursDlg::OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, &CTestContoursDlg::OnEnChangeEdit18)
	ON_BN_CLICKED(IDC_BUTTON17, &CTestContoursDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CTestContoursDlg::OnBnClickedButton18)
	ON_EN_CHANGE(IDC_EDIT19, &CTestContoursDlg::OnEnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT22, &CTestContoursDlg::OnEnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, &CTestContoursDlg::OnEnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT21, &CTestContoursDlg::OnEnChangeEdit21)
	ON_BN_CLICKED(IDC_BUTTON19, &CTestContoursDlg::OnBnClickedButton19)
END_MESSAGE_MAP()


// CFFTtestDlg message handlers
FILE* fp_console;
void Init_Console()
{
	if (!AllocConsole())
	{
		AfxMessageBox(_T("Failed AllocConsole()"));
	}
	freopen_s(&fp_console, "CONOUT$", "w", stdout);
	freopen_s(&fp_console, "CONIN$", "r", stdin);
	freopen_s(&fp_console, "CONOUT$", "w", stderr);
	std::cout << "Starting console .... Ok" << std::endl;
}

BOOL CTestContoursDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	Init_Console();

	m_ctype = true;
	m_hv_ctype = (HTuple)m_ctype;
	//GetDlgItem(IDC_CHECK2)->CheckDlgButton(IDC_CHECK2, m_ctype);
	CButton* pCheckbox = (CButton*)GetDlgItem(IDC_CHECK2);
	pCheckbox->SetCheck(BST_CHECKED);

	pmedo = (float *)malloc(200000 * sizeof(float));
	m_hv_thr = 130;
	m_fsz = 21;
	m_fszwa = 15;
	m_fszpad = 15;
	m_hv_meander = 162;
	m_hv_pad = 324;
	m_hv_padc = 26;
	m_hw_absmb = 0.9; m_hw_abssp = 0.9; // abs. defects for meander
	m_hw_absmbwa = 0.7; m_hw_absspwa = 0.7; // abs. defects for meander
	m_hv_wa = 100;
	m_hw_absmbpad = 0.7; m_hw_abssppad = 0.7; // abs. defects for meander
	num = 1;
	disp = 0;

	CString cstr;
	cstr.Format(_T("%d"), m_fsz);
	SetDlgItemText(IDC_EDIT2, cstr);

	cstr.Format(_T("%d"), (int)m_hv_meander);
	SetDlgItemText(IDC_EDIT1, cstr);
	cstr.Format(_T("%.1f"), m_hw_absmb.D());
	SetDlgItemText(IDC_EDIT3, cstr);
	cstr.Format(_T("%.1f"), m_hw_abssp.D());
	SetDlgItemText(IDC_EDIT4, cstr);
	cstr.Format(_T("%d"), num);
	SetDlgItemText(IDC_EDIT5, cstr);
	cstr.Format(_T("%d"), (int)m_hv_pad);
	SetDlgItemText(IDC_EDIT6, cstr);
	cstr.Format(_T("%d"), (int)m_hv_padc);
	SetDlgItemText(IDC_EDIT7, cstr);
	cstr.Format(_T("%d"), (int)m_hv_wa);
	SetDlgItemText(IDC_EDIT11, cstr);

	cstr.Format(_T("%.1f"), m_hw_absmbpad.D());
	SetDlgItemText(IDC_EDIT14, cstr);
	cstr.Format(_T("%.1f"), m_hw_abssppad.D());
	SetDlgItemText(IDC_EDIT15, cstr);
	cstr.Format(_T("%d"), m_fszpad);
	SetDlgItemText(IDC_EDIT13, cstr);

	cstr.Format(_T("%.1f"), m_hw_absmbwa.D());
	SetDlgItemText(IDC_EDIT17, cstr);
	cstr.Format(_T("%.1f"), m_hw_absspwa.D());
	SetDlgItemText(IDC_EDIT18, cstr);
	cstr.Format(_T("%d"), m_fszwa);
	SetDlgItemText(IDC_EDIT16, cstr);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestContoursDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestContoursDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestContoursDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestContoursDlg::OnBnClickedButton1()
{
	HTuple hv_nI, hv_nG, hv_Wout, hv_l;
	
	//ReadTuple("C:\\Temp1\\PWidthP_tuple0.tup", &hv_W);
	ReadObject(&m_ho_CI, "C:\\Temp1\\CI.hobj" );
	ReadObject(&m_ho_CG, "C:\\Temp1\\CG.hobj");
	ReadImage(&m_ho_Im, "C:\\Temp1\\Im.tif");
	printf("***Files Open***" );

	GetContourXld(m_ho_CI, &m_hv_RowI, &m_hv_ColI);
	GetContourXld(m_ho_CG, &m_hv_RowG, &m_hv_ColG);

	TupleLength(m_hv_RowI, &hv_nI);
	TupleLength(m_hv_RowG, &hv_nG);
}


void CTestContoursDlg::OnBnClickedButton2()
{
	HTuple ht1, ht2, ht;
	CountSeconds(&ht1);
	DistanceContoursXld(m_ho_CI, m_ho_CG, &m_ho_Cbj, "point_to_segment");
	GetContourAttribXld(m_ho_Cbj, "distance", &m_hv_DistIG);
	CountSeconds(&ht2);
	ht = ht2 - ht1;
	double msec = ht.D()*1000.;
	printf("\n***Halcon-based dist. found, %f msec***", msec);
	WriteTuple(m_hv_DistIG, "C:\\Temp1\\DHC.tup");
}




void CTestContoursDlg::OnBnClickedButton3()
{
	HTuple hv_isz;
	hv_isz = 21;
	HTuple ht1, ht2, ht;
	CountSeconds(&ht1);
	DistanceContours2H(m_hv_RowI, m_hv_ColI, m_hv_RowG, m_hv_ColG,
		hv_isz, &m_hv_DistIG2);
	CountSeconds(&ht2);
	ht = ht2 - ht1;
	double msec = ht.D()*1000.;
	printf("\n***DistanceContours2H dist. found, %f msec***", msec);

	WriteTuple(m_hv_DistIG2, "C:\\Temp1\\D2HC.tup");
}

void CTestContoursDlg::OnBnClickedButton4() //  finding displacement by DistanceContours2 (C++)
{
	HTuple hv_nI, hv_nG, hv_D;

	float* pRowI = ConvertTupleToFloat(m_hv_RowI);
	float* pColI = ConvertTupleToFloat(m_hv_ColI);
	float* pRowG = ConvertTupleToFloat(m_hv_RowG);
	float* pColG = ConvertTupleToFloat(m_hv_ColG);
	TupleLength(m_hv_RowI, &hv_nI);
	TupleLength(m_hv_RowG, &hv_nG);
	int nI = hv_nI.I();
	int nG = hv_nG.I();
	int isz = 21;
	float *pD = (float *)malloc((nI) * sizeof(float));
	HTuple ht1, ht2, ht;
	CountSeconds(&ht1);

	DistanceContours2(pRowI, pColI, nI, pRowG, pColG, nG,
		isz, pD, 0);

	CountSeconds(&ht2);
	ht = ht2 - ht1;
	double msec = ht.D()*1000.;
	printf("\n***DistanceContours2 C++ dist. found, %f msec***", msec);

	FloatToTuple(pD, nI, hv_D);
	WriteTuple(hv_D, "C:\\Temp1\\D2CPP.tup");

	free(pD);
}





void CTestContoursDlg::OnBnClickedCheck1()
{
	disp = !disp;

	if (!disp)
	{
		if (hWindow.IsHandleValid())
			hWindow.CloseWindow();
	}
}


void CTestContoursDlg::OnBnClickedButton6() // Building real contour 
{
	HObject ho_Rectangle5, ho_ContourOut, ho_RegionIR, ho_Imr, ho_BorderEPs;
	HTuple hv_ctype, hv_thr;
	HTuple ht1, ht2, ht;

	ho_Rectangle5 = m_ho_Rectangle5;
	//ReadObject(&ho_Rectangle5, "C:\\Temp1\\Rectangle5.hobj");
	//printf("***Rectangle5 Open***");
	hv_thr = 150;

	CountSeconds(&ht1);
	ReduceDomain(m_ho_Im, ho_Rectangle5, &ho_Imr);
	for (int i = 0; i < num; i++)
	{
		BuildRealContour(ho_Imr, ho_Rectangle5,  &ho_ContourOut, &ho_BorderEPs,
			&ho_RegionIR, m_hv_ctype, hv_thr);
	}
	CountSeconds(&ht2);
	ht = ht2 - ht1;
	double msec = ht.D()*1000.;
	printf("\n***BuildRealContour #%i , %f msec***", m_ctype, msec);
}


void CTestContoursDlg::OnBnClickedCheck2()
{
	UpdateData(TRUE);
	
	//GetDlgItem(IDC_CHECK2)->EnableWindow(m_ctype);

	m_ctype = !m_ctype;
	m_hv_ctype = m_ctype;
	//SetRegBool("CheckRawImage", m_Raw_Image);

	//if (!m_Auto_Thr)
	//{
	//	//m_local_Im = m_pIm;
	//	//GetImageSize(m_local_Im, &m_hv_Width, &m_hv_Height);

	//}
	//else
	//{
	//}

	//Enable_Inspection_Buttons(!m_ctype);

	UpdateData(FALSE);
}

///////////////////////////////////////////////////////////
//			Running Median Filter
///////////////////////////////////////////////////////////

int compare(const void* a, const void* b)
{
	const int* x = (int*)a;
	const int* y = (int*)b;

	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;

	return 0;
}

// SrunmedSLIExt=SrunmedSLI + Extention
void SrunmedSLIExt(float* yinp, float* y/*extended*/, float* smo, long n1, int bw_tot, int end_rule, int skip) // 2022.08.01 - running median with skipping [skip] values, with linear interpolation
{
	/*
		 *  Computes "Running Median" smoother ("Stuetzle" algorithm) with medians of 'band'

		 *  Input:
		 *	y(n)	- responses in order of increasing predictor values
		 *	n	- number of observations
		 *	bw_tot	- span of running medians (MUST be ODD !!)
		 *	end_rule -- 0: Keep original data at ends {j; j < b2 | j > n-b2}
		 *		     -- 1: Constant ends = median(y[1],..,y[bw]) "robust"
		 *  Output:
		 *	smo(n)	- smoothed responses

		 * NOTE:  The 'end' values are just copied !! this is fast but not too nice !
		 */

		 /* Local variables */
	double rmed, rmin, temp, rnew, yout, yi;
	double rbe, rtb, rse, yin, rts, fa, fb;
	int imin, ismo, i, j, first, last, band2, kminus, kplus, shift, bw, step, num_meds, last_med, a, b, x;
	float v;
	for (i = 0; i < bw_tot; i++)
		y[i] = yinp[0];
	//memcpy(y + bw_tot, yinp, n1 * sizeof(float));
	for (i = 0; i < n1; i++)
		y[bw_tot + i] = yinp[i];
	for (i = 0; i < bw_tot - 1; i++)
		y[bw_tot + n1 + i] = yinp[n1 - 1];
	int n = n1 + 2 * bw_tot;
	step = skip + 1;
	bw = (((bw_tot - 1) / 2) / step) * 2 + 1;
	//std::cout << "new: bw=" << bw << ", radius=" << bw / 2 << ", step=" << step << "\n";

	if (n < bw)
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
		scrat[i] = y[i*step + shift];

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
	band2 = bw / 2;
	rmed = scrat[band2];/* == Median( y[(1:band2)-1] ) */
	/* "malloc" had  free( (char*) scrat);*/ /*-- release scratch memory --*/
	if (shift == 0) {
		if (end_rule == 0) { /*-- keep DATA at end values */
			for (i = 0; i < band2*step; ++i)
				smo[i] = y[i];
		}
		else { /* if(end_rule == 1)  copy median to CONSTANT end values */
			for (i = 0; i < band2*step; ++i)
				smo[i] = (float)rmed;
		}
	}
	smo[band2*step + shift] = (float)rmed;
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
		smo[ismo] = (float)rmed;
		num_meds++;
	} /*     END FOR ------------ big Loop -------------------- */

	free(scrat);

	band2 = bw / 2;
	last_med = band2 * step + (num_meds - 1)*step;

	if (end_rule == 0) { /*-- keep DATA at end values */
		for (i = last_med + 1; i < n; ++i)
			smo[i] = y[i];
	}
	else { /* if(end_rule == 1)  copy median to CONSTANT end values */
		for (i = last_med + 1; i < n; ++i)
			smo[i] = smo[last_med];
	}

	if (skip > 0) {
		for (i = 0; i < num_meds - 1; i++) {
			for (j = 1; j < step; j++) {
				x = (band2 + i)*step + j;
				a = (band2 + i)*step;
				b = (band2 + i + 1)*step;
				fa = smo[a];
				fb = smo[b];
				smo[x] = (float)(fa + j * (fb - fa) / step); //b-a=step, x-a=j
			}
		}
	}
	//memcpy(smo, smo + bw_tot, n * sizeof(float));
	for (i = 0; i < n; i++)
	{
		v = smo[i + bw_tot];
		smo[i] = v;
	}
} /* SrunmedSLIExt */

void SrunmedSLI(float* y, float* smo, long n, int bw_tot, int end_rule, int skip) // 2022.08.01 - running median with skipping [skip] values, with linear interpolation
{
	/*
		 *  Computes "Running Median" smoother ("Stuetzle" algorithm) with medians of 'band'

		 *  Input:
		 *	y(n)	- responses in order of increasing predictor values
		 *	n	- number of observations
		 *	bw_tot	- span of running medians (MUST be ODD !!)
		 *	end_rule -- 0: Keep original data at ends {j; j < b2 | j > n-b2}
		 *		     -- 1: Constant ends = median(y[1],..,y[bw]) "robust"
		 *  Output:
		 *	smo(n)	- smoothed data output (should be allocated)

		 * NOTE:  The 'end' values are just copied !! this is fast but not too nice !
		 */

		 /* Local variables */
	double rmed, rmin, temp, rnew, yout, yi;
	double rbe, rtb, rse, yin, rts, fa, fb;
	int imin, ismo, i, j, first, last, band2, kminus, kplus, shift, bw, step, num_meds, last_med, a, b, x;

	step = skip + 1;
	bw = (((bw_tot - 1) / 2) / step) * 2 + 1;
	if (n < bw_tot)
		return;
	//std::cout << "new: bw=" << bw << ", radius=" << bw / 2 << ", step=" << step << "\n";

	if (n < bw)
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
		scrat[i] = y[i*step + shift];

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
	band2 = bw / 2;
	rmed = scrat[band2];/* == Median( y[(1:band2)-1] ) */
	/* "malloc" had  free( (char*) scrat);*/ /*-- release scratch memory --*/
	if (shift == 0) {
		if (end_rule == 0) { /*-- keep DATA at end values */
			for (i = 0; i < band2*step; ++i)
				smo[i] = y[i];
		}
		else { /* if(end_rule == 1)  copy median to CONSTANT end values */
			for (i = 0; i < band2*step; ++i)
				smo[i] = (float)rmed;
		}
	}
	smo[band2*step + shift] = (float)rmed;
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
		smo[ismo] = (float)rmed;
		num_meds++;
	} /*     END FOR ------------ big Loop -------------------- */

	free(scrat);

	band2 = bw / 2;
	last_med = band2 * step + (num_meds - 1)*step;

	if (end_rule == 0) { /*-- keep DATA at end values */
		for (i = last_med + 1; i < n; ++i)
			smo[i] = y[i];
	}
	else { /* if(end_rule == 1)  copy median to CONSTANT end values */
		for (i = last_med + 1; i < n; ++i)
			smo[i] = smo[last_med];
	}

	if (skip > 0) {
		for (i = 0; i < num_meds - 1; i++) {
			for (j = 1; j < step; j++) {
				x = (band2 + i)*step + j;
				a = (band2 + i)*step;
				b = (band2 + i + 1)*step;
				fa = smo[a];
				fb = smo[b];
				smo[x] = (float)(fa + j * (fb - fa) / step); //b-a=step, x-a=j
			}
		}
	}
} /* SrunmedSLI */


void TestRegionPointS(HObject ho_Region, HTuple hv_Row, HTuple hv_Col, HTuple *Isinside)
{
	//void TestRegionPoint(HObject ho_Region, HTuple hv_Row, HTuple hv_Col, HTuple *Isinside)
	HTuple hv_l, hv_row, hv_col, hv_ins, hv_Ins;
	HTuple i, a, r, c;
	HObject R, RI;
	TupleLength(hv_Row, &hv_l);
	int l = hv_l.I();
	for (i = 0; i < l; i=i+1)
	{
		hv_row = hv_Row[i];
		hv_col = hv_Col[i];
		/*GenRegionPoints(&R, hv_row, hv_col);
		Intersection(ho_Region, R, &RI);
		AreaCenter(RI, &a, &r, &c);
		if (a > 0)
			hv_ins = 1;
		else
			hv_ins = 0;*/
		TestRegionPoint(ho_Region, hv_row, hv_col, &hv_ins);

		TupleConcat(hv_Ins, hv_ins, &hv_Ins);
	}
	*Isinside = hv_Ins;

}

HTuple ht1, ht3, ht2, ht4, ht5, ht6;
//extern HObject m_ho_RegionI;
void ProcessMeander(HObject ho_Im, HObject ho_ContoursGrsm, HObject ho_MeanderRects, HObject ho_Gi,
	HObject *ho_MeanderDefects, HObject *ho_Rectangle, HObject *ho_ContourGmv, HObject *ho_ContourI,// defects found as regions
	HTuple hv_thr, HTuple hv_meander, HTuple hw_absmb, HTuple hw_abssp, HTuple hv_ctype, int fsz,
	HTuple *hv_Dout) // Filtered displacement
{
	
	HObject ho_CG, ho_Imr, ho_Imc, ho_Rectangle5, ho_ContourOut, ho_RegionIR, ho_ContourGm, ho_BorderEPs;
	HTuple hv_RowI, hv_ColI, hv_RowG, hv_ColG, hv_ai, hv_rowIc, hv_colIc, hv_poI, hv_ag, hv_rowGc, hv_colGc, hv_poG, hv_mr, hv_mc, Sign, Displacement,
		Isinside, hv_DFilt;// , hv_Dout;
	CountSeconds(&ht1);
	SelectObj(ho_ContoursGrsm, &ho_CG, hv_meander);
	SelectObj(ho_MeanderRects, &ho_Rectangle5, hv_meander);
	//GetContourXld(m_ho_CG, &m_hv_RowG, &m_hv_ColG);
	*ho_Rectangle = ho_Rectangle5;

	ReduceDomain(ho_Im, ho_Rectangle5, &ho_Imr);
	CropDomain(ho_Imr, &ho_Imc);

	BuildRealContour(ho_Imr, ho_Rectangle5, //  building I contour
		&ho_ContourOut, &ho_BorderEPs, &ho_RegionIR,
		hv_ctype, hv_thr);
	HTuple ha, hr, hc;
	AreaCenter(ho_BorderEPs, &ha, &hr, &hc);
	CountSeconds(&ht2);
	GetContourXld(ho_ContourOut, &hv_RowI, &hv_ColI);
	GetContourXld(ho_CG, &hv_RowG, &hv_ColG);

	AreaCenterXld(ho_ContourOut, &hv_ai, &hv_rowIc, &hv_colIc, &hv_poI);
	AreaCenterXld(ho_CG, &hv_ag, &hv_rowGc, &hv_colGc, &hv_poG);
	hv_mr = hv_rowIc - hv_rowGc;
	hv_mc = hv_colIc - hv_colGc;

	// Region-based center
	//HObject RegionGr, RegionGr5, RegionGr5b, ho_RegionIRb;
	//HTuple Area, RowG5, ColG5;
	//GenRegionContourXld(m_ho_CG, &RegionGr, "filled");
	//Intersection(RegionGr, ho_Rectangle5, &RegionGr5);
	//Boundary(RegionGr5, &RegionGr5b, "inner");
	//AreaCenter(RegionGr5b, &Area, &RowG5, &ColG5);

	//HTuple AreaIR, RowIR, ColIR;
	//Boundary(ho_RegionIR, &ho_RegionIRb, "inner");
	//AreaCenter(ho_RegionIRb, &AreaIR, &RowIR, &ColIR);
	//hv_mr = RowIR - RowG5;
	//hv_mc = ColIR - ColG5;

	hv_RowG = hv_RowG + hv_mr;
	hv_ColG = hv_ColG + hv_mc;
	GenContourPolygonXld(&ho_ContourGm, hv_RowG, hv_ColG);
	//GenRegionPolygonXld

	HTuple hv_nI, hv_nG, hv_D;

	float* pRowI = ConvertTupleToFloat(hv_RowI);
	float* pColI = ConvertTupleToFloat(hv_ColI);
	float* pRowG = ConvertTupleToFloat(hv_RowG);
	float* pColG = ConvertTupleToFloat(hv_ColG);
	TupleLength(hv_RowI, &hv_nI);
	TupleLength(hv_RowG, &hv_nG);
	int nI = hv_nI.I();
	int nG = hv_nG.I();
	int isz = 21;
	float *pD = (float *)malloc((nI) * sizeof(float));

	DistanceContours2(pRowI, pColI, nI, pRowG, pColG, nG,
		isz, pD, 0);
	
	//HTuple hv_isz = (HTuple)isz;
	//DistanceContours2H(m_hv_RowI, m_hv_ColI, m_hv_RowG, m_hv_ColG,
	//	hv_isz, &m_hv_DistIG2);
	//hv_D = m_hv_DistIG2;

	FloatToTuple(pD, nI, hv_D);
	//TupleGenConst((HTuple)nI, false, &Isinside);
	CountSeconds(&ht3);
	

	//HObject ho_RegionGm;
	//GenRegionContourXld(ho_ContourGm, &ho_RegionGm, "filled"); // simplified "is inside" check
	//HTuple Row, Beg, End;
	//GetRegionRuns(ho_RegionGm, &Row,&Beg, &End);*/
	//HTuple RowGA1, ColGA1, RowGA2, ColGA2;
	//SmallestRectangle1(ho_RegionGm, &RowGA1, &ColGA1, &RowGA2, &ColGA2);
	//SmallestRectangle1(ho_RegionGm, &RowGA1, &ColGA1, &RowGA2, &ColGA2);
	//HObject ImGA;
	//RegionToBin(ho_RegionGm, &ImGA, 1, 0, ColGA2 - ColGA1, RowGA2 - RowGA1);

	// Gi-based, not working yet (19.09.2025)
	//GetGrayval(ho_Gi, hv_RowI, hv_ColI, &Isinside);

	//Polygon-based.... Working, ~160 msec for 165 meanders (19.09.2025)
	HObject Pol;
	GenPolygonsXld(ho_ContourGm, &Pol, "ramer", 0.25);
	TestXldPoint(Pol, hv_RowI, hv_ColI, &Isinside);
	//Contour-based.... Working, ~470 msec for 165 meanders (19.09.2025)
	//TestXldPoint(ho_ContourGm, hv_RowI, hv_ColI, &Isinside);

	//gen_region_contour_xld(ContourGrsma, RegionGA, 'filled')
	//test_region_point(RegionGA, RowI, ColI, IsInside)

	//GenRegionContourXld(ho_ContourGm, &ho_RegionGm, "filled"); // simplified "is inside" check
	//TestRegionPoint(ho_RegionGm, hv_RowI, hv_ColI, &Isinside);
	CountSeconds(&ht4);
	Sign = Isinside * 2.0 - 1.0;
	Displacement = -Sign * hv_D;

	HTuple hv_DispElong, hv_Wch, hv_Wch1, hv_Def, hv_Def1;
	HTuple hv_sz = 31;
	// making elongation (one side)
	hv_DispElong.Clear();
	hv_DispElong.Append(Displacement.TupleSelectRange((hv_nI - hv_sz) - 0, hv_nI - 1));
	hv_DispElong.Append(Displacement);
	/*FilterFloatMedDef((*hv_DispElong), hv_sz, hv_absmb, hv_abssp, &(*hv_Wfilt), &(*hv_Wch1),
		&(*hv_Def1));*/

	float* pDisp = ConvertTupleToFloat(hv_DispElong);
	int sz = hv_sz.L();
	int nIe = nI + sz;
	float *pFilt = (float *)malloc(nIe * sizeof(float));
	
	SrunmedSLI(pDisp, pFilt, (long)(nIe), fsz, 0, 0);
	FloatToTuple(pFilt, (nIe), hv_DFilt);

	HTuple hv_nIe = nIe;
	hv_Wch1= hv_DispElong - hv_DFilt;
	(*hv_Dout) = hv_Wch1;
	////////////////////////////////

	
	
	HTuple ThrMB, ThrSP, DefSP, DefMB, Def, Def1, DefA, RowD, ColD, nD, Rd;
	HObject CircleD, CircleDu;

	TupleGenConst(hv_nIe, -hw_absmb, &ThrMB);
	TupleGenConst(hv_nIe, hw_abssp, &ThrSP);
	TupleGreaterEqualElem(hv_Wch1, ThrSP, &DefSP);
	TupleLessEqualElem(hv_Wch1, ThrMB, &DefMB);
	Def1 = DefSP - DefMB;
	//TupleAbs(Def1, &DefA);

	hv_Wch.Clear();
	hv_Wch.Append(hv_Wch1.TupleSelectRange(hv_sz, hv_nI - 1));
	hv_Wch.Append(hv_Wch1.TupleSelectRange(0, hv_sz - 1));
	//hv_Def.Clear();
	//hv_Def.Append(hv_Def1.TupleSelectRange(hv_sz, hv_nI - 1));
	//hv_Def.Append(hv_Def1.TupleSelectRange(0, hv_sz - 1));
	hv_Def = Def1.TupleSelectRange(hv_sz, (hv_nI + hv_sz) - 1);
	TupleAbs(hv_Def, &DefA);
	//float* pDisp = ConvertTupleToFloat(Displacement);

	//float *pFilt = (float *)malloc((nI) * sizeof(float));
	//
	//SrunmedSLI(pDisp, pFilt, (long)nI, fsz, 0, 0);

	/*FloatToTuple(pFilt, nI, hv_DFilt);
	(*hv_Dout) = Displacement - hv_DFilt;*/
	CountSeconds(&ht5);
	
	if (save)
	{
		WriteObject(ho_CG, "C:\\Temp1\\m_ho_CG.hobj");
		WriteObject(ho_ContourOut, "C:\\Temp1\\ho_ContourOut.hobj");

		WriteTuple(hv_D, "C:\\Temp1\\hv_D.tup");
		WriteTuple(Displacement, "C:\\Temp1\\hv_Displacement.tup");
		WriteTuple((*hv_Dout), "C:\\Temp1\\hv_Dout.tup");
		WriteTuple((hv_Wch), "C:\\Temp1\\hv_Wch.tup");

		WriteObject(ho_Imr, "C:\\Temp1\\ho_Imr");
		WriteObject(ho_Rectangle5, "C:\\Temp1\\ho_Rectangle5");

		WriteObject(ho_BorderEPs, "C:\\Temp1\\ho_BorderEPs");
	}




	/*HTuple ThrMB, ThrSP, DefSP, DefMB, Def, DefA, RowD, ColD, nD, Rd;
	HObject CircleD, CircleDu;

	TupleGenConst((HTuple)nI, -hw_absmb, &ThrMB);
	TupleGenConst((HTuple)nI, hw_abssp, &ThrSP);
	TupleGreaterEqualElem((*hv_Dout), ThrSP, &DefSP);
	TupleLessEqualElem((*hv_Dout), ThrMB, &DefMB);
	Def = DefSP - DefMB;
	TupleAbs(Def, &DefA);*/
	TupleSelectMask(hv_RowI, DefA, &RowD);
	TupleSelectMask(hv_ColI, DefA, &ColD);
	TupleLength(RowD, &nD);
	if (nD > 1)
	{
		TupleGenConst(nD, 2.5, &Rd);
		GenCircle(&CircleD, RowD, ColD, Rd);
		Union1(CircleD, &CircleDu);
		HObject RInt;
		Intersection(CircleDu, ho_BorderEPs, &RInt);
		AreaCenter(RInt, &ha, &hr, &hc);
		if(ha>0)
			GenEmptyObj(&CircleDu);
	}
	else
		GenEmptyObj(&CircleDu);
	CountSeconds(&ht6);
	//(*ho_ContourOut) = ho_ContourH;
	//CopyObj(CircleDu, ho_MeanderDefects, 0, 1);
	(*ho_MeanderDefects) = CircleDu;
	*ho_ContourGmv = ho_ContourGm;
	*ho_ContourI = ho_ContourOut;
	free(pD);
	free(pRowI);
	free(pColI);
	free(pRowG);
	free(pColG);
	free(pFilt);
}

int ipad;
void ProcessPads(HObject ho_Im, HObject ho_ContoursGrsm, HObject ho_PadRects, HObject ho_Gi, HObject ho_RegionI, HObject ho_RegionGPad,
	HObject *ho_PadDefects, HObject *ho_Rectangle, HObject *ho_ContourGmv, HObject *ho_ContourI, HObject *ho_RegionIR, HObject *ho_RBEp, // defects found as regions
	HTuple hv_thr, HTuple hv_pad, HTuple hw_absmb, HTuple hw_abssp, HTuple hv_ctype, int fsz, HTuple hv_pdil,
	HTuple *hv_Dout) // Filtered displacement
{
	int nopad = 0;
	HObject ho_CG, ho_Imr, ho_Imc, ho_Rectangle5, ho_ContourOut,  ho_ContourGm, ho_BorderEPs;
	HTuple hv_RowI, hv_ColI, hv_RowG, hv_ColG, hv_ai, hv_rowIc, hv_colIc, hv_poI, hv_ag, hv_rowGc, hv_colGc, hv_poG, hv_mr, hv_mc, Sign, Displacement,
		Isinside, hv_DFilt;// , hv_Dout;
	CountSeconds(&ht1);
	ipad = hv_pad.I();

	SelectObj(ho_ContoursGrsm, &ho_CG, hv_pad);
	SelectObj(ho_PadRects, &ho_Rectangle5, hv_pad);
	//GetContourXld(m_ho_CG, &m_hv_RowG, &m_hv_ColG);
	*ho_Rectangle = ho_Rectangle5;
	//if (ipad == 105)
	//	ipad = ipad;
	//Dilation
	//FillUp(ho_Rectangle5, &ho_Rectangle5);
	//OpeningCircle(ho_Rectangle5, &ho_Rectangle5, 20);
	
	ReduceDomain(ho_Im, ho_Rectangle5, &ho_Imr);
	CropDomain(ho_Imr, &ho_Imc);
	if (save)
	{
		WriteObject(ho_Rectangle5, "C:\\Temp1\\ho_Rectangle5.hobj");
		WriteObject(ho_Imr, "C:\\Temp1\\ho_Imr.hobj");
		//WriteObject(ho_Rectangle5, "C:\\Temp1\\ho_Rectangle5.hobj");
	}

	BuildRealContourI(ho_Imr, ho_Rectangle5, ho_RegionI, ho_RegionGPad,//  building I contour
		&ho_ContourOut, &ho_BorderEPs, ho_RegionIR, ho_RBEp,
		hv_ctype, hv_thr, hv_pdil);
	HTuple ha, hr, hc, hl;
	//AreaCenter(ho_BorderEPs, &ha, &hr, &hc);
	CountSeconds(&ht2);
	GetContourXld(ho_ContourOut, &hv_RowI, &hv_ColI);
	GetContourXld(ho_CG, &hv_RowG, &hv_ColG);
	TupleLength(hv_RowI, &hl);

	HTuple hv_nI, hv_nG, hv_D;
	HTuple hv_DispElong, hv_Wch, hv_Wch1, hv_Def, hv_Def1;
	HTuple hv_sz = 31;

	HTuple ThrMB, ThrSP, DefSP, DefMB, Def, Def1, DefA, RowD, ColD, nD, Rd;
	HObject CircleD, CirclesD, CircleDu;
	HObject RBI, RBG;
	HObject ho_ObjectD;

	TupleLength(hv_RowI, &hv_nI);
	TupleLength(hv_RowG, &hv_nG);
	int nI = hv_nI.I();
	int nG = hv_nG.I();
	int isz = 10;

	if (hv_nI > hv_sz + 1) // normal case
	{
		//goto norealcontour;

		
		
		GenRegionPoints(&RBG, hv_RowG, hv_ColG);
		GenRegionPoints(&RBI, hv_RowI, hv_ColI);
	
		AreaCenterXld(ho_ContourOut, &hv_ai, &hv_rowIc, &hv_colIc, &hv_poI);
		AreaCenterXld(ho_CG, &hv_ag, &hv_rowGc, &hv_colGc, &hv_poG);
		if (hv_poI != hv_poG)
		{
			ReverseContourH(ho_ContourOut, &ho_ContourOut);
			AreaCenterXld(ho_ContourOut, &hv_ai, &hv_rowIc, &hv_colIc, &hv_poI);
		}
		AreaCenter(RBG, &hv_ag, &hv_rowGc, &hv_colGc);
		AreaCenter(RBI, &hv_ai, &hv_rowIc, &hv_colIc);
		hv_mr = hv_rowIc - hv_rowGc;
		hv_mc = hv_colIc - hv_colGc;

	//hv_mr = -3.58;
	//hv_mc = -4.5;

	// Region-based center
	//HObject RegionGr, RegionGr5, RegionGr5b, ho_RegionIRb;
	//HTuple Area, RowG5, ColG5;
	//GenRegionContourXld(m_ho_CG, &RegionGr, "filled");
	//Intersection(RegionGr, ho_Rectangle5, &RegionGr5);
	//Boundary(RegionGr5, &RegionGr5b, "inner");
	//AreaCenter(RegionGr5b, &Area, &RowG5, &ColG5);

	//HTuple AreaIR, RowIR, ColIR;
	//Boundary(ho_RegionIR, &ho_RegionIRb, "inner");
	//AreaCenter(ho_RegionIRb, &AreaIR, &RowIR, &ColIR);
	//hv_mr = RowIR - RowG5;
	//hv_mc = ColIR - ColG5;

		hv_RowG = hv_RowG + hv_mr;
		hv_ColG = hv_ColG + hv_mc;
		GenContourPolygonXld(&ho_ContourGm, hv_RowG, hv_ColG);
		//GenRegionPolygonXld

		//HTuple hv_nI, hv_nG, hv_D;

		float* pRowI = ConvertTupleToFloat(hv_RowI);
		float* pColI = ConvertTupleToFloat(hv_ColI);
		float* pRowG = ConvertTupleToFloat(hv_RowG);
		float* pColG = ConvertTupleToFloat(hv_ColG);
		
		float *pD = (float *)malloc((nI) * sizeof(float));

		DistanceContours2(pRowI, pColI, nI, pRowG, pColG, nG,
			isz, pD, 0);

	//HTuple hv_isz = (HTuple)isz;
	//DistanceContours2H(m_hv_RowI, m_hv_ColI, m_hv_RowG, m_hv_ColG,
	//	hv_isz, &m_hv_DistIG2);
	//hv_D = m_hv_DistIG2;

		FloatToTuple(pD, nI, hv_D);
		//TupleGenConst((HTuple)nI, false, &Isinside);
		CountSeconds(&ht3);


	//HObject ho_RegionGm;
	//GenRegionContourXld(ho_ContourGm, &ho_RegionGm, "filled"); // simplified "is inside" check
	//HTuple Row, Beg, End;
	//GetRegionRuns(ho_RegionGm, &Row,&Beg, &End);*/
	//HTuple RowGA1, ColGA1, RowGA2, ColGA2;
	//SmallestRectangle1(ho_RegionGm, &RowGA1, &ColGA1, &RowGA2, &ColGA2);
	//SmallestRectangle1(ho_RegionGm, &RowGA1, &ColGA1, &RowGA2, &ColGA2);
	//HObject ImGA;
	//RegionToBin(ho_RegionGm, &ImGA, 1, 0, ColGA2 - ColGA1, RowGA2 - RowGA1);

	// Gi-based, not working yet (19.09.2025)
	//GetGrayval(ho_Gi, hv_RowI, hv_ColI, &Isinside);

	//Polygon-based.... Working, ~160 msec for 165 meanders (19.09.2025)
		HObject Pol;
		GenPolygonsXld(ho_ContourGm, &Pol, "ramer", 0.25);
		TestXldPoint(Pol, hv_RowI, hv_ColI, &Isinside);
		//Contour-based.... Working, ~470 msec for 165 meanders (19.09.2025)
		//TestXldPoint(ho_ContourGm, hv_RowI, hv_ColI, &Isinside);

		//gen_region_contour_xld(ContourGrsma, RegionGA, 'filled')
		//test_region_point(RegionGA, RowI, ColI, IsInside)

		//GenRegionContourXld(ho_ContourGm, &ho_RegionGm, "filled"); // simplified "is inside" check
		//TestRegionPoint(ho_RegionGm, hv_RowI, hv_ColI, &Isinside);
		CountSeconds(&ht4);
		Sign = Isinside * 2.0 - 1.0;
		//Sign = 1.0;
		Displacement = -Sign * hv_D;

		
		float *pFilt = (float *)malloc(1 * sizeof(float));
		nD = 0;
	
		// making elongation (one side)
		hv_DispElong.Clear();
		hv_DispElong.Append(Displacement.TupleSelectRange((hv_nI - hv_sz) - 0, hv_nI - 1));
		hv_DispElong.Append(Displacement);
		/*FilterFloatMedDef((*hv_DispElong), hv_sz, hv_absmb, hv_abssp, &(*hv_Wfilt), &(*hv_Wch1),
			&(*hv_Def1));*/

		float* pDisp = ConvertTupleToFloat(hv_DispElong);
		int sz = hv_sz.L();
		int nIe = nI + sz;
		pFilt = (float *)malloc(nIe * sizeof(float));

		SrunmedSLI(pDisp, pFilt, (long)(nIe), fsz, 0, 0);
		FloatToTuple(pFilt, (nIe), hv_DFilt);

		HTuple hv_nIe = nIe;
		hv_Wch1 = hv_DispElong - hv_DFilt;
		(*hv_Dout) = hv_Wch1;
		////////////////////////////////

		TupleGenConst(hv_nIe, -hw_absmb, &ThrMB);
		TupleGenConst(hv_nIe, hw_abssp, &ThrSP);
		TupleGreaterEqualElem(hv_Wch1, ThrSP, &DefSP);
		TupleLessEqualElem(hv_Wch1, ThrMB, &DefMB);
		Def1 = DefSP - DefMB;
		//TupleAbs(Def1, &DefA);

		hv_Wch.Clear();
		hv_Wch.Append(hv_Wch1.TupleSelectRange(hv_sz, hv_nI - 1));
		hv_Wch.Append(hv_Wch1.TupleSelectRange(0, hv_sz - 1));
		//hv_Def.Clear();
		//hv_Def.Append(hv_Def1.TupleSelectRange(hv_sz, hv_nI - 1));
		//hv_Def.Append(hv_Def1.TupleSelectRange(0, hv_sz - 1));
		hv_Def = Def1.TupleSelectRange(hv_sz, (hv_nI + hv_sz) - 1);
		TupleAbs(hv_Def, &DefA);
		TupleSelectMask(hv_RowI, DefA, &RowD);
		TupleSelectMask(hv_ColI, DefA, &ColD);
		TupleLength(RowD, &nD);

		free(pD);
		free(pRowI);
		free(pColI);
		free(pRowG);
		free(pColG);
		free(pFilt);
	}
	else // missing pad case
	{
		CircleD = ho_Rectangle5;
		*ho_ContourGmv = ho_Rectangle5;
		*ho_ContourI = ho_Rectangle5;
		*ho_PadDefects = ho_Rectangle5;
		ho_ObjectD = ho_Rectangle5;
		//nDef = 1;
		CountSeconds(&ht3);
		CountSeconds(&ht4);
			nD = -1;
			nopad = 1;
	}
//norealcontour:
//	;
	//float* pDisp = ConvertTupleToFloat(Displacement);

	//float *pFilt = (float *)malloc((nI) * sizeof(float));
	//
	//SrunmedSLI(pDisp, pFilt, (long)nI, fsz, 0, 0);

	/*FloatToTuple(pFilt, nI, hv_DFilt);
	(*hv_Dout) = Displacement - hv_DFilt;*/
	CountSeconds(&ht5);

	if (save)
	{
		WriteObject(ho_CG, "C:\\Temp1\\m_ho_CG.hobj");
		//WriteObject(ho_CI, "C:\\Temp1\\m_ho_CI.hobj");
		WriteObject(ho_ContourOut, "C:\\Temp1\\ho_ContourOut.hobj");

		WriteTuple(hv_D, "C:\\Temp1\\hv_D.tup");
		WriteTuple(Displacement, "C:\\Temp1\\hv_Displacement.tup");
		WriteTuple((*hv_Dout), "C:\\Temp1\\hv_Dout.tup");
		WriteTuple((hv_Wch), "C:\\Temp1\\hv_Wch.tup");

		WriteObject(ho_Imr, "C:\\Temp1\\ho_Imr");
		WriteObject(ho_Rectangle5, "C:\\Temp1\\ho_Rectangle5");

		//WriteObject(ho_BorderEPs, "C:\\Temp1\\ho_BorderEPs");
	}
	/*HTuple ThrMB, ThrSP, DefSP, DefMB, Def, DefA, RowD, ColD, nD, Rd;
		HObject CircleD, CircleDu;

		TupleGenConst((HTuple)nI, -hw_absmb, &ThrMB);
		TupleGenConst((HTuple)nI, hw_abssp, &ThrSP);
		TupleGreaterEqualElem((*hv_Dout), ThrSP, &DefSP);
		TupleLessEqualElem((*hv_Dout), ThrMB, &DefMB);
		Def = DefSP - DefMB;
		TupleAbs(Def, &DefA);*/
	/*TupleSelectMask(hv_RowI, DefA, &RowD);
	TupleSelectMask(hv_ColI, DefA, &ColD);
	TupleLength(RowD, &nD);*/
	if (nD > 1)
	{
		HObject RGEP, RBE, CircleDc, ho_RegionIntersection1;
		HTuple RowG, ColG, nDc, hv_k, hv_a, hv_Row, hv_Column;
		GetContourXld(ho_CG, &RowG, &ColG);
		GenRegionLine(&RGEP, HTuple(RowG[0]), HTuple(ColG[0]), HTuple(RowG[nG - 2]),
			HTuple(ColG[nG - 2]));
		TupleGenConst(nD, 4.5, &Rd);
		GenCircle(&CirclesD, RowD, ColD, Rd);
		Union1(CirclesD, &CircleD);
		Connection(CircleD, &CircleDc);
		CountObj(CircleDc, &nDc);
		GenEmptyObj(&CircleD);
		{
			HTuple end_val17 = nDc;
			HTuple step_val17 = 1;
			for (hv_k = 1; hv_k.Continue(end_val17, step_val17); hv_k += step_val17)
			{
				SelectObj(CircleDc, &ho_ObjectD, hv_k);
				Union2(*ho_RBEp, RGEP, &RBE);

				//intersection (ObjectD, RBEp3, RegionIntersection1)
				Intersection(ho_ObjectD, RBE, &ho_RegionIntersection1);
				//union2 (RBEp3, RGEP, RBE)
				AreaCenter(ho_RegionIntersection1, &hv_a, &hv_Row, &hv_Column);
				if (0 != (hv_a == 0) || nopad == 1)
				{
					if (save)
					{
						WriteObject(ho_ContourGm, "C:\\Temp1\\ho_ContourGm.hobj");
						WriteObject(RBI, "C:\\Temp1\\ho_RBI.hobj");
						WriteObject(ho_CG, "C:\\Temp1\\ho_CG.hobj");
						WriteObject(ho_ObjectD, "C:\\Temp1\\ho_ObjectD.hobj");
						WriteObject(RBE, "C:\\Temp1\\RBE.hobj");
					}
					ConcatObj(CircleD, ho_ObjectD, &CircleD);
				}
			}
		}
		//CountObj(CircleD, &hv_nDef);

			//GenRegionLine(&RGEP, RowG[0], ColG[0], RowG[nG - 2], ColG[nG - 2]);
			//TupleGenConst(nD, 2.5, &Rd);
			//GenCircle(&CirclesD, RowD, ColD, Rd);
			//Union1(CirclesD, &CircleD);
			//HObject RInt;
			//Intersection(CircleDu, ho_BorderEPs, &RInt);
			//// ecp 251031 11:06
			//AreaCenter(RInt, &ha, &hr, &hc);
			//if (ha > 0)
			//	GenEmptyObj(&CircleDu);
	}
	else if (nD == -1)
		//GenCircle(&CircleD, hv_rowGc, hv_colGc, 10);
		CircleD = ho_Rectangle5;
	else
		GenEmptyObj(&CircleD);
	CountSeconds(&ht6);
	//(*ho_ContourOut) = ho_ContourH;
	//CopyObj(CircleDu, ho_MeanderDefects, 0, 1);
	(*ho_PadDefects) = CircleD;
	*ho_ContourGmv = ho_ContourGm;
	*ho_ContourI = ho_ContourOut;
	
}

#define MND_NONE	0

#define MND_MB_ABS	2
#define MND_MB_PRC	3
#define MND_SP_ABS	4
#define MND_SP_PRC	5



void MND_PostProcCPU(float *pcd, float *pcx, float *pcy, float *medo, int n, int sz1, int skip, float wg,
	float mprc, float sprc, float mabs, float pabs,// defects pars
	float *pDefMB, float *pDefMBprc, float *pXdefMB, float *pYdefMB, float *pDefSP, float *pDefSPprc, float *pXdefSP, float *pYdefSP, int *MBnum, int *SPnum)
{	/// processing of single contour displacement part of length=n, RMed window=sz1, CAD width = wg

	int j;
	int spnum = 0, mbnum = 0;
	//	float *medo;
	//int bw = min (sz1, n);
	int bw = sz1;
	//int wgmed;
	//int *pbuf;

	//float prcG, prcReal;

	float dp, dfilt, dif, dprc;
	//float dg, dgprc; // deviation from CAD
	//float dn, dnprc; // deviation from neighbor
	float def, defprc; // defect size


	int deftype, defin;
	float defx, defy;

	float defw; // defect width
	float wnorm;



	//nc = 1; // to save 1st coil data
	int caddrb, caddre, cnum;
	for (int j = 0; j < n - 0; j++)
	{

		/*caddrb = *(pPaddr + j + 0);
		if (j + 1 < nc)
			caddre = *(pPaddr + j + 1) - 1;
		else
			caddre = n - 1;
		cnum = (caddre - caddrb);*/

		int bw = min(sz1, n / 2);


		SrunmedSLI(pcd, medo, n, bw, 0, 0);
		defin = 0;
		//SrunmedSLI(pw + caddrb + 0, medo + MEDOSIZE * j / 2, cnum - 0, bw, 0, skip); /// saving both profiles for testing
		int cnt = 0;
		//for (j = caddrb + bw / 2; j < caddre - bw / 2; j++)
		//for (int jj = bw / 2; jj < cnum - bw / 2; jj++)
		for (int jj = 3; jj < n - 3; jj++)
		{
			if (j == 1 && jj == 6612)
				j = j;
			dp = *(pcd + jj);


			dfilt = (float)*(medo + jj);

			dif = dp - dfilt;
			/*if (w < 2.0)
				w = w;*/




			dprc = (float)(dif * 100. / (dfilt + 0.001));

			if (dif < pabs) // % (rel.) criterion 
			{
				defin = 0;
				if (dprc <= -mprc)
				{
					def = -dif;
					defprc = dprc;
					deftype = MND_MB_PRC;
					defin = 1;
				}
				else if (dprc >= sprc)
				{
					def = dif;
					defprc = dprc;
					deftype = MND_SP_PRC;
					defin = 1;

				}
			}
			else if (dif >= pabs) // small spur
			{
				def = dif;
				defprc = 100.;
				deftype = MND_SP_ABS;
				defin = 1;
			}
			else if (/*wg < minthp*/1) //abs.criterion ... if width is smaller than minmbs, then can't use % based detection!
			{
				if (dif <= -mabs)
				{
					def = -dif;
					defprc = 100.;
					deftype = MND_MB_ABS;
					defin = 1;
				}
				else if (dif >= pabs)
				{
					def = dif;
					defprc = 100.;
					deftype = MND_SP_ABS;
					defin = 1;

				}
			}

		}

	}

	if (deftype == MND_MB_ABS || deftype == MND_MB_PRC)
	{
		*(pDefMB + mbnum) = def;
		*(pDefMBprc + mbnum) = dprc;
		/**(pXdefMB + mbnum) = defx;
		*(pYdefMB + mbnum) = defy;*/
		mbnum++;
	}
	else if (deftype == MND_SP_ABS || deftype == MND_SP_PRC)
	{
		*(pDefSP + spnum) = def;
		*(pDefSPprc + spnum) = dprc;
		/**(pXdefSP + spnum) = defx;
		*(pYdefSP + spnum) = defy;*/
		spnum++;
	}

	*SPnum = spnum;
	*MBnum = mbnum;
	//free(medo);
	//free(buf);
}

void ProcessMeanderC(HObject ho_Im, HObject ho_ContoursGrsm, HObject ho_MeanderRects,
	HObject *ho_MeanderDefects, HObject *ho_Rectangle, HObject *ho_ContourGmv, HObject *ho_ContourI,// defects found as regions
	HTuple hv_thr, HTuple hv_meander, HTuple hw_absmb, HTuple hw_abssp, HTuple hv_ctype, int fsz,
	HTuple *hv_Dout) // Filtered displacement
{

	HObject ho_CG, ho_Imr, ho_Imc, ho_Rectangle5, ho_ContourOut, ho_RegionIR, ho_ContourGm, ho_BorderEPs;
	HTuple hv_RowI, hv_ColI, hv_RowG, hv_ColG, hv_ai, hv_rowIc, hv_colIc, hv_poI, hv_ag, hv_rowGc, hv_colGc, hv_poG, hv_mr, hv_mc, Sign, Displacement,
		Isinside, hv_DFilt;// , hv_Dout;
	CountSeconds(&ht1);
	SelectObj(ho_ContoursGrsm, &ho_CG, hv_meander);
	SelectObj(ho_MeanderRects, &ho_Rectangle5, hv_meander);
	//GetContourXld(m_ho_CG, &m_hv_RowG, &m_hv_ColG);
	*ho_Rectangle = ho_Rectangle5;

	ReduceDomain(ho_Im, ho_Rectangle5, &ho_Imr);
	CropDomain(ho_Imr, &ho_Imc);

	BuildRealContour(ho_Imr, ho_Rectangle5, //  building I contour
		&ho_ContourOut, &ho_BorderEPs, &ho_RegionIR,
		hv_ctype, hv_thr);
	CountSeconds(&ht2);
	GetContourXld(ho_ContourOut, &hv_RowI, &hv_ColI);
	GetContourXld(ho_CG, &hv_RowG, &hv_ColG);

	AreaCenterXld(ho_ContourOut, &hv_ai, &hv_rowIc, &hv_colIc, &hv_poI);
	AreaCenterXld(ho_CG, &hv_ag, &hv_rowGc, &hv_colGc, &hv_poG);
	hv_mr = hv_rowIc - hv_rowGc;
	hv_mc = hv_colIc - hv_colGc;

	// Region-based center
	//HObject RegionGr, RegionGr5, RegionGr5b, ho_RegionIRb;
	//HTuple Area, RowG5, ColG5;
	//GenRegionContourXld(m_ho_CG, &RegionGr, "filled");
	//Intersection(RegionGr, ho_Rectangle5, &RegionGr5);
	//Boundary(RegionGr5, &RegionGr5b, "inner");
	//AreaCenter(RegionGr5b, &Area, &RowG5, &ColG5);

	//HTuple AreaIR, RowIR, ColIR;
	//Boundary(ho_RegionIR, &ho_RegionIRb, "inner");
	//AreaCenter(ho_RegionIRb, &AreaIR, &RowIR, &ColIR);
	//hv_mr = RowIR - RowG5;
	//hv_mc = ColIR - ColG5;

	hv_RowG = hv_RowG + hv_mr;
	hv_ColG = hv_ColG + hv_mc;
	GenContourPolygonXld(&ho_ContourGm, hv_RowG, hv_ColG);
	HTuple hv_nI, hv_nG, hv_D;

	float* pRowI = ConvertTupleToFloat(hv_RowI);
	float* pColI = ConvertTupleToFloat(hv_ColI);
	float* pRowG = ConvertTupleToFloat(hv_RowG);
	float* pColG = ConvertTupleToFloat(hv_ColG);
	TupleLength(hv_RowI, &hv_nI);
	TupleLength(hv_RowG, &hv_nG);
	int nI = hv_nI.I();
	int nG = hv_nG.I();
	int isz = 21;
	float *pD = (float *)malloc((nI) * sizeof(float));

	DistanceContours2(pRowI, pColI, nI, pRowG, pColG, nG,
		isz, pD, 0);
	CountSeconds(&ht3);
	//HTuple hv_isz = (HTuple)isz;
	//DistanceContours2H(m_hv_RowI, m_hv_ColI, m_hv_RowG, m_hv_ColG,
	//	hv_isz, &m_hv_DistIG2);
	//hv_D = m_hv_DistIG2;

	FloatToTuple(pD, nI, hv_D);
	TestXldPoint(ho_ContourGm, hv_RowI, hv_ColI, &Isinside);
	Sign = Isinside * 2.0 - 1.0;
	Displacement = -Sign * hv_D;

	float* pDisp = ConvertTupleToFloat(Displacement);
	float* pcy = ConvertTupleToFloat(hv_RowI);
	float* pcx = ConvertTupleToFloat(hv_ColI);

	int wg = 6;
	float mprc=30, sprc=30;
	float mabs = hw_absmb.D();
	float pabs = hw_abssp.D();
	float *pDefMB;
	pDefMB= (float *)malloc(100 * sizeof(float));
	float *pDefMBprc;
	pDefMBprc = (float *)malloc(100 * sizeof(float));
	float *pXdefMB;
	pXdefMB = (float *)malloc(100 * sizeof(float));
	float *pYdefMB;
	pYdefMB = (float *)malloc(100 * sizeof(float));

	float *pDefSP;
	pDefSP = (float *)malloc(100 * sizeof(float));
	float *pDefSPprc;
	pDefSPprc = (float *)malloc(100 * sizeof(float));
	float *pXdefSP;
	pXdefSP = (float *)malloc(100 * sizeof(float));
	float *pYdefSP;
	pYdefSP = (float *)malloc(100 * sizeof(float));

	int MBnum, SPnum;

	MND_PostProcCPU(pDisp, pcx, pcy, pmedo, nI, fsz, 0, wg,
		mprc, sprc, mabs, pabs,// defects pars
		pDefMB, pDefMBprc, pXdefMB, pYdefMB, pDefSP, pDefSPprc, pXdefSP, pYdefSP, &MBnum, &SPnum);

	HTuple hv_pDefMBprc, hv_pDefSPprc, hv_pDefMB, hv_pDefSP;
	hv_pDefMBprc = HTuple(pDefMBprc, MBnum);
	hv_pDefSPprc = HTuple(pDefSPprc, SPnum);
	hv_pDefMB = HTuple(pDefMB, MBnum);
	hv_pDefSP = HTuple(pDefSP, SPnum);

	/*float *pFilt = (float *)malloc((nI) * sizeof(float));
	SrunmedSLI(pDisp, pFilt, (long)nI, fsz, 0, 0);
	FloatToTuple(pFilt, nI, hv_DFilt);
	(*hv_Dout) = Displacement - hv_DFilt;*/
	int save = 0;
	if (save)
	{
		WriteObject(ho_CG, "C:\\Temp1\\m_ho_CG.hobj");
		WriteObject(ho_ContourOut, "C:\\Temp1\\ho_ContourOut.hobj");

		WriteTuple(hv_D, "C:\\Temp1\\hv_D.tup");
		WriteTuple(Displacement, "C:\\Temp1\\hv_Displacement.tup");
		WriteTuple((*hv_Dout), "C:\\Temp1\\hv_Dout.tup");

	}

	// -------------------------------------------------------------------
	HObject m_ho_RegionsMB, m_ho_RegionsSP;
	{
		HTuple PMBx_tuple;
		HTuple PMBy_tuple;
		FloatToTuple(pXdefMB, MBnum, PMBx_tuple);
		FloatToTuple(pYdefMB, MBnum, PMBy_tuple);

		GenEmptyObj(&m_ho_RegionsMB);
		//HTuple  hv_nMB = HTuple(m_pFWM->MBnum);
		TupleSelectMask(PMBy_tuple, PMBy_tuple, &PMBy_tuple);
		TupleSelectMask(PMBx_tuple, PMBx_tuple, &PMBx_tuple);
		HTuple  hv_nMB;
		TupleLength(PMBx_tuple, &hv_nMB);
		if (hv_nMB > 0)
		{
			HTuple hv_TR;
			TupleGenConst(hv_nMB, 30, &hv_TR);
			GenCircle(&m_ho_RegionsMB, PMBy_tuple, PMBx_tuple, hv_TR);
		}

	}

	// -------------------------------------------------------------------
	{
		HTuple PSPx_tuple;
		HTuple PSPy_tuple;
		FloatToTuple(pXdefSP, SPnum, PSPx_tuple);
		FloatToTuple(pYdefSP, SPnum, PSPy_tuple);

		GenEmptyObj(&m_ho_RegionsSP);
		//HTuple  hv_nSP = HTuple(m_pFWM->SPnum);
		TupleSelectMask(PSPy_tuple, PSPy_tuple, &PSPy_tuple);
		TupleSelectMask(PSPx_tuple, PSPx_tuple, &PSPx_tuple);
		HTuple  hv_nSP;
		TupleLength(PSPx_tuple, &hv_nSP);



		if (hv_nSP > 0)
		{
			HTuple hv_TR;
			TupleGenConst(hv_nSP, 30, &hv_TR);
			//DistancePr(m_ho_RegNoProc, PSPy_tuple, PSPx_tuple, &hv_DistNmin, &hv_DistNmax);
			GenCircle(&m_ho_RegionsSP, PSPy_tuple, PSPx_tuple, hv_TR);

			//VerifySPregnoproc(m_ho_RegNoProc, m_pFWM->ho_RegionInoD, m_ho_RegionsSP,
			//	&m_ho_RegionsSP, 20);
		}
	}

	/*HTuple ThrMB, ThrSP, DefSP, DefMB, Def, DefA, RowD, ColD, nD, Rd;
	HObject CircleD, CircleDu;

	TupleGenConst((HTuple)nI, -hw_absmb, &ThrMB);
	TupleGenConst((HTuple)nI, hw_abssp, &ThrSP);
	TupleGreaterEqualElem((*hv_Dout), ThrSP, &DefSP);
	TupleLessEqualElem((*hv_Dout), ThrMB, &DefMB);
	Def = DefSP - DefMB;
	TupleAbs(Def, &DefA);
	TupleSelectMask(hv_RowI, DefA, &RowD);
	TupleSelectMask(hv_ColI, DefA, &ColD);
	TupleLength(RowD, &nD);
	if (nD > 1)
	{
		TupleGenConst(nD, 2.5, &Rd);
		GenCircle(&CircleD, RowD, ColD, Rd);
		Union1(CircleD, &CircleDu);
	}
	else
		GenEmptyObj(&CircleDu);*/
	CountSeconds(&ht4);
	//(*ho_ContourOut) = ho_ContourH;
	//CopyObj(CircleDu, ho_MeanderDefects, 0, 1);
	(*ho_MeanderDefects) = m_ho_RegionsSP;
	*ho_ContourGmv = ho_ContourGm;
	*ho_ContourI = ho_ContourOut;
	free(pD);
	free(pRowI);
	free(pColI);
	free(pRowG);
	free(pColG);
	//free(pFilt);
}

void CTestContoursDlg::OnBnClickedButton7()  // Building real contour + finding displacement
{
	HObject ho_Rectangle5, ho_ContourOut, ho_RegionIR, ho_Imr, ho_Imc, ho_ContourGrsm, ho_MeanderRect, ho_ContourGm, ho_BorderEPs;
	HTuple hv_ctype, hv_thr, hv_mr, hv_mc, hv_rowIc, hv_colIc, hv_poI, hv_ai, hv_rowGc, hv_colGc, hv_poG, hv_ag;
	HTuple ht1, ht3, ht2, ht, Isinside, Sign, Displacement, hv_DFilt, hv_Dout;
	HTuple r51, c51, r52, c52, ww, wh, wcx, wcy;
	/*if (hWindow.IsHandleValid())
	{
		hWindow.CloseWindow();
		return;
	}*/
	int save = 0;
	//hWindow.InvalidateHandle();
	ReadObject(&ho_Rectangle5, "C:\\Temp1\\Rectangle5.hobj");
	printf("***Rectangle5 Open***");
	hv_thr = 150;

	CountSeconds(&ht1);


	SelectObj(m_ho_ContoursGrsm, &m_ho_CG, m_hv_meander);
	SelectObj(m_ho_MeanderRects, &ho_Rectangle5, m_hv_meander);
	//GetContourXld(m_ho_CG, &m_hv_RowG, &m_hv_ColG);


	ReduceDomain(m_ho_Im, ho_Rectangle5, &ho_Imr);
	CropDomain(ho_Imr, &ho_Imc);

	BuildRealContour(ho_Imr, ho_Rectangle5, //  building I contour
		&ho_ContourOut, &ho_BorderEPs, &ho_RegionIR,
		m_hv_ctype, hv_thr);

	GetContourXld(ho_ContourOut, &m_hv_RowI, &m_hv_ColI);
	GetContourXld(m_ho_CG, &m_hv_RowG, &m_hv_ColG);

	AreaCenterXld(ho_ContourOut, &hv_ai, &hv_rowIc, &hv_colIc, &hv_poI);
	AreaCenterXld(m_ho_CG, &hv_ag, &hv_rowGc, &hv_colGc, &hv_poG);
	hv_mr = hv_rowIc - hv_rowGc;
	hv_mc = hv_colIc - hv_colGc;

	// Region-based center
	//HObject RegionGr, RegionGr5, RegionGr5b, ho_RegionIRb;
	//HTuple Area, RowG5, ColG5;
	//GenRegionContourXld(m_ho_CG, &RegionGr, "filled");
	//Intersection(RegionGr, ho_Rectangle5, &RegionGr5);
	//Boundary(RegionGr5, &RegionGr5b, "inner");
	//AreaCenter(RegionGr5b, &Area, &RowG5, &ColG5);

	//HTuple AreaIR, RowIR, ColIR;
	//Boundary(ho_RegionIR, &ho_RegionIRb, "inner");
	//AreaCenter(ho_RegionIRb, &AreaIR, &RowIR, &ColIR);
	//hv_mr = RowIR - RowG5;
	//hv_mc = ColIR - ColG5;

	m_hv_RowG = m_hv_RowG + hv_mr;
	m_hv_ColG = m_hv_ColG + hv_mc;
	GenContourPolygonXld(&ho_ContourGm, m_hv_RowG, m_hv_ColG);
	HTuple hv_nI, hv_nG, hv_D;
	CountSeconds(&ht2);
	float* pRowI = ConvertTupleToFloat(m_hv_RowI);
	float* pColI = ConvertTupleToFloat(m_hv_ColI);
	float* pRowG = ConvertTupleToFloat(m_hv_RowG);
	float* pColG = ConvertTupleToFloat(m_hv_ColG);
	TupleLength(m_hv_RowI, &hv_nI);
	TupleLength(m_hv_RowG, &hv_nG);
	int nI = hv_nI.I();
	int nG = hv_nG.I();
	int isz = 21;
	float *pD = (float *)malloc((nI) * sizeof(float));

	DistanceContours2(pRowI, pColI, nI, pRowG, pColG, nG,
		isz, pD, 0);
	//HTuple hv_isz = (HTuple)isz;
	//DistanceContours2H(m_hv_RowI, m_hv_ColI, m_hv_RowG, m_hv_ColG,
	//	hv_isz, &m_hv_DistIG2);
	//hv_D = m_hv_DistIG2;
	CountSeconds(&ht3);
	ht = ht3 - ht1;
	double msec1 = ht.D()*1000.;
	

	FloatToTuple(pD, nI, hv_D);
	TestXldPoint(ho_ContourGm, m_hv_RowI, m_hv_ColI, &Isinside);
	Sign = Isinside * 2.0 - 1.0;
	Displacement = -Sign * hv_D;

	float* pDisp = ConvertTupleToFloat(Displacement);

	float *pFilt = (float *)malloc((nI) * sizeof(float));
	SrunmedSLI(pDisp , pFilt, (long)nI, m_fsz, 0, 0);
	FloatToTuple(pFilt, nI, hv_DFilt);
	hv_Dout = Displacement - hv_DFilt;
	if (save)
	{
		WriteObject(m_ho_CG, "C:\\Temp1\\m_ho_CG.hobj");
		WriteObject(ho_ContourOut, "C:\\Temp1\\ho_ContourOut.hobj");

		WriteTuple(hv_D, "C:\\Temp1\\hv_D.tup");
		WriteTuple(Displacement, "C:\\Temp1\\hv_Displacement.tup");
		WriteTuple(hv_Dout, "C:\\Temp1\\hv_Dout.tup");

		//WriteTuple(hv_D, "C:\\Temp1\\D2CPP_r.tup");
		//WriteTuple(Displacement, "C:\\Temp1\\Displacement_r.tup");
		//WriteTuple(hv_DFilt, "C:\\Temp1\\hv_Filt_r.tup");
		//WriteTuple(hv_Dout, "C:\\Temp1\\Dout_r.tup");
	}

	

	HTuple ThrMB, ThrSP, DefSP, DefMB, Def, DefA, RowD, ColD, nD, Rd;
	HObject CircleD, CircleDu;

	TupleGenConst((HTuple)nI, -m_hw_absmb, &ThrMB);
	TupleGenConst((HTuple)nI, m_hw_abssp, &ThrSP);
	TupleGreaterEqualElem(hv_Dout, ThrSP, &DefSP);
	TupleLessEqualElem(hv_Dout, ThrMB, &DefMB);
	Def = DefSP - DefMB;
	TupleAbs(Def, &DefA);
	TupleSelectMask(m_hv_RowI, DefA, &RowD);
	TupleSelectMask(m_hv_ColI, DefA, &ColD);
	TupleLength(RowD, &nD);
	if(nD>1)
	{
		TupleGenConst(nD, 2.5, &Rd);
		GenCircle(&CircleD, RowD, ColD, Rd);
		Union1(CircleD, &CircleDu);
	}
	free(pD);
	free(pRowI);
	free(pColI);
	free(pRowG);
	free(pColG);
	free(pFilt);

	ht = ht3 - ht2;
	double msec2 = ht.D()*1000.;
	
	printf("\n***Building real contour+finding displacement+RM filter, %f msec***", msec1);
	printf("\n***BuildRealContour #%i , %f msec***", m_ctype, msec2);

	

	SmallestRectangle1(ho_Rectangle5, &r51, &c51, &r52, &c52);
	ww = (c52 - c51);
	wh = (r52 - r51);
	HTuple ks, kx, ky;
	kx = 1920 / ww;
	ky = 1080 / wh;
	TupleMin2(kx, ky, &ks);
	if (ks > 8)
		ks = 8;
	ww = ww * ks;
	wh = wh * ks;

	wcy = r51 + wh / 2;
	wcx = c51 + ww / 2;
	//hWindow.MoveRectangle();

	if (hWindow.IsHandleValid())
		hWindow.CloseWindow();

	hWindow.OpenWindow(0, 3835, ww, wh, 0, "visible", "");
	hWindow.SetPart((Hlong)r51, (Hlong)c51, (Hlong)r52, (Hlong)c52);
	hWindow.DispImage(m_ho_Im);
	if (nD > 1)
		hWindow.SetColor("coral");
	else
		hWindow.SetColor("green");
	hWindow.SetLineWidth(3);
	hWindow.DispObj(ho_ContourOut);

	hWindow.SetColor("blue");
	hWindow.SetLineWidth(1);
	hWindow.DispObj(m_ho_CG);

	hWindow.SetColor("cyan");
	hWindow.SetLineWidth(2);
	hWindow.DispObj(ho_ContourGm);

	if (nD > 1)
	{
		hWindow.SetDraw("margin");
		hWindow.SetColor("red");
		hWindow.SetLineWidth(3);
		hWindow.DispObj(CircleDu);
	}
	// Keep the window open until a key is pressed
	//hWindow.Click();

	// Close the window
	//hWindow.CloseWindow();
}


void CTestContoursDlg::OnBnClickedButton5()
{
	//OnBnClickedButton1();
	ReadObject(&m_ho_CI, "C:\\Temp1\\CI.hobj");
	ReadObject(&m_ho_CG, "C:\\Temp1\\CG.hobj");
	ReadImage(&m_ho_Im, "C:\\Temp1\\Im.tif");
	ReadObject(&m_ho_Gi, "C:\\Temp1\\Gi.hobj");
	Threshold(m_ho_Im, &m_ho_RegionI, m_hv_thr, 255);
	printf("***Files Open***");

	ReadObject(&m_ho_ContoursGrsm, "C:\\Temp1\\ContoursGrsmc.hobj");
	ReadObject(&m_ho_MeanderRects, "C:\\Temp1\\MeanderRects.hobj");
	ReadObject(&m_ho_RegionGPad, "C:\\Temp1\\RegionGPad.hobj");
	HTuple tnum;
	CString cstr;
	CountObj(m_ho_MeanderRects, &tnum);
	cstr.Format(_T("(%d)"), (int)tnum);
	SetDlgItemText(IDC_EDIT10, cstr);

	printf("\n***ContoursGrsm.hobj and MeanderRects.hobj read***");
	//ReadObject(&m_ho_ContoursGrsmPi, "C:\\Temp1\\ContoursGrsmPi.hobj");
	ReadObject(&m_ho_ContoursGPadsIsol, "C:\\Temp1\\ContoursGPadsIsol.hobj");
	ReadObject(&m_ho_RegionsGPadsIsol, "C:\\Temp1\\RegionsGPadsIsol.hobj");
	CountObj(m_ho_RegionsGPadsIsol, &tnum);
	cstr.Format(_T("(%d)"), (int)tnum);
	SetDlgItemText(IDC_EDIT8, cstr);
	printf("\n***ContoursGPadsCon.hobj and RegionsGPadsIsol.hobj read***");
	//ReadObject(&m_ho_ContoursGrsmPc, "C:\\Temp1\\ContoursGrsmPc.hobj");
	ReadObject(&m_ho_ContoursGPadsCon, "C:\\Temp1\\ContoursGPadsCon.hobj");
	//ReadObject(&m_ho_RectanglesPadsCon, "C:\\Temp1\\RectanglesPadsCon.hobj");//
	ReadObject(&m_ho_RegionsGPadsCon, "C:\\Temp1\\RegionsGPadsCon.hobj");
	CountObj(m_ho_RegionsGPadsCon, &tnum);
	cstr.Format(_T("(%d)"), (int)tnum);
	SetDlgItemText(IDC_EDIT9, cstr);
	printf("\n***ContoursGrsmPc.hobj and RectanglesPadsCon.hobj read***");

	ReadObject(&m_ho_ContoursWireAngles, "C:\\Temp1\\ContoursWireAngles.hobj");
	ReadObject(&m_ho_RectanglesWireAngles, "C:\\Temp1\\RectanglesWireAngles.hobj");
	CountObj(m_ho_RectanglesWireAngles, &tnum);
	cstr.Format(_T("(%d)"), (int)tnum);
	SetDlgItemText(IDC_EDIT12, cstr);
	printf("\n***ContoursWireAngles.hobj and RectanglesWireAngles.hobj read***");
}


void CTestContoursDlg::OnEnChangeEdit1()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT1, cstr);
	m_hv_meander = (int)_tstof(cstr);
}


void CTestContoursDlg::OnEnChangeEdit2()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT2, cstr);
	m_fsz = (int)_tstof(cstr);
}


float g_zoomFactor = 1.0f;
POINT g_origin = { 0, 0 }; // Represents the top-left of the view in world coordinates

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOUSEWHEEL:
	{
		// Get the wheel delta
		short zDelta = GET_WHEEL_DELTA_WPARAM(wParam);

		// Determine zoom direction
		float zoomChange = (zDelta > 0) ? 1.1f : 0.9f; // Zoom in or out factor

		// Get mouse position relative to the client area
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(hwnd, &mousePos);

		// Calculate the new origin to zoom around the mouse cursor
		g_origin.x = (int)(mousePos.x - (mousePos.x - g_origin.x) * zoomChange);
		g_origin.y = (int)(mousePos.y - (mousePos.y - g_origin.y) * zoomChange);

		// Apply zoom factor
		g_zoomFactor *= zoomChange;

		// Redraw the window
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// Example: Draw a rectangle that scales and moves with zoom
		// Adjust drawing coordinates based on zoom factor and origin
		int rectX = (int)((100 - g_origin.x) * g_zoomFactor);
		int rectY = (int)((100 - g_origin.y) * g_zoomFactor);
		int rectWidth = (int)(50 * g_zoomFactor);
		int rectHeight = (int)(50 * g_zoomFactor);

		Rectangle(hdc, rectX, rectY, rectX + rectWidth, rectY + rectHeight);

		EndPaint(hwnd, &ps);
		return 0;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Register the window class
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"ZoomWindow";
	RegisterClass(&wc);

	// Create the window
	HWND hwnd = CreateWindowEx(
		0,
		L"ZoomWindow",
		L"Mouse Wheel Zoom Example",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// Message loop
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

BOOL CTestContoursDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	//WindowProc();
	//short zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
	// Determine zoom direction
	float zoomChange = (zDelta > 0) ? 1.1f : 0.9f; // Zoom in or out factor

	// Get mouse position relative to the client area
	HTuple mrow, mcol, but;
	GetMpositionSubPix(hWindow, &mrow, &mcol, &but);
	POINT mousePos;
	GetCursorPos(&mousePos);
	//ScreenToClient(hwnd, &mousePos);

	// Calculate the new origin to zoom around the mouse cursor
	g_origin.x = (int)(mousePos.x - (mousePos.x - g_origin.x) * zoomChange);
	g_origin.y = (int)(mousePos.y - (mousePos.y - g_origin.y) * zoomChange);

	// Apply zoom factor
	g_zoomFactor *= zoomChange;

	// Redraw the window
	//InvalidateRect(hwnd, NULL, TRUE);
	//return 0;

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CTestContoursDlg::OnEnChangeEdit3()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT3, cstr);
	m_hw_absmb = _tstof(cstr);
}


void CTestContoursDlg::OnEnChangeEdit4()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT4, cstr);
	m_hw_abssp = _tstof(cstr);
}

void CTestContoursDlg::OnBnClickedButton9() // Meander Insp.cyc.func.(single meander, cycle num)
{
	//int fsz = 21;
	m_hv_thr = 150;
	HObject ho_MeanderDefect, ho_Rect;
	HTuple hv_DOut;
	HTuple lht1, lht3, lht2, lht, hv_meander;
	
	SelectObj(m_ho_MeanderRects, &m_ho_Rectangle5, m_hv_meander);
	SelectObj(m_ho_ContoursGrsm, &m_ho_CG, m_hv_meander);
	CountSeconds(&lht1);
	for(int i=0; i<num; i++)
		ProcessMeander(m_ho_Im, m_ho_ContoursGrsm, m_ho_MeanderRects, m_ho_Gi,
		&ho_MeanderDefect, &ho_Rect, &m_ho_CG, &m_ho_CI,
		m_hv_thr, m_hv_meander, m_hw_absmb, m_hw_abssp, m_hv_ctype, m_fsz,
		&hv_DOut);
	//m_ho_CI=
	CountSeconds(&lht3);
	lht = lht3 - lht1;
	double msec1 = lht.D()*1000.;

	//printf("\n***Meadner single cycle ended ***" );
	printf("\n***Meadner single cycle ended (%d)-->%.2f msec***",  num, msec1);
	
	lht1 = ht2 - ht1;
	msec1 = lht1.D()*1000.;
	lht1 = ht3 - ht2;
	double msec2 = lht1.D()*1000.;
	lht1 = ht4 - ht3;
	double msec3 = lht1.D()*1000.;
	lht1 = ht5 - ht4;
	double msec4 = lht1.D()*1000.;
	lht1 = ht6 - ht5;
	double msec5 = lht1.D()*1000.;
	printf("\n***Meadner single cycle ended (%d)-->%.2f + %.2f + (IsInside)%.2f + %.2f + %.2f  msec***", num, msec1, msec2, msec3, msec4, msec5);
	if (disp)
	{
		HTuple r51, c51, r52, c52, ww, wh, wcx, wcy;

		SmallestRectangle1(ho_Rect, &r51, &c51, &r52, &c52);
		ww = (c52 - c51);
		wh = (r52 - r51);
		HTuple ks, kx, ky;
		kx = 1920 / ww;
		ky = 1080 / wh;
		TupleMin2(kx, ky, &ks);
		if (ks > 8)
			ks = 8;
		ww = ww * ks;
		wh = wh * ks;

		wcy = r51 + wh / 2;
		wcx = c51 + ww / 2;
		//hWindow.MoveRectangle();

		if (hWindow.IsHandleValid())
			hWindow.CloseWindow();

		hWindow.OpenWindow(0, WINST, ww, wh, 0, "visible", "");
		hWindow.SetPart((Hlong)r51, (Hlong)c51, (Hlong)r52, (Hlong)c52);
		hWindow.DispImage(m_ho_Im);
		HTuple hv_a, r, c;
		CountObj(ho_MeanderDefect, &hv_a);
		//AreaCenter(ho_MeanderDefects, &a, &r, &c);
		if (hv_a.I() > 0)
		{
			hWindow.SetColor("blue");
			hWindow.SetLineWidth(1);
			hWindow.DispObj(m_ho_CG);
			//}
				/*hWindow.SetColor("coral");
			else
				hWindow.SetColor("green");*/
				/*hWindow.SetLineWidth(3);
				hWindow.DispObj(ho_ContourOut);*/



				/*hWindow.SetColor("cyan");
				hWindow.SetLineWidth(2);
				hWindow.DispObj(ho_ContourGm);*/

				//if (a.I() > 1)
				//{
			hWindow.SetDraw("margin");
			hWindow.SetColor("red");
			hWindow.SetLineWidth(3);
			hWindow.DispObj(ho_MeanderDefect);
		}
		else
			//hWindow.SetFont("Courier-Bold-14");
			hWindow.DispText("No defects found", "window", "center", "center", "green", "shadow", "true");
		// Keep the window open until a key is pressed
		//WriteTuple(Displacement, "C:\\Temp1\\hv_Displacement.tup");
		WriteTuple(hv_DOut, "C:\\Temp1\\hv_Dout.tup");
		//hWindow.Click();

		// Close the window
		//hWindow.CloseWindow();
	}
}

void CTestContoursDlg::OnBnClickedButton8()
{
	HObject ho_Rectangle5, ho_ContourOut, ho_RegionIR, ho_Imr, ho_Imc, ho_ContourGrsm, ho_MeanderRect, ho_ContourGm, ho_Defects, ho_BorderEPs;
	HTuple hv_ctype, hv_thr, hv_mr, hv_mc, hv_rowIc, hv_colIc, hv_poI, hv_ai, hv_rowGc, hv_colGc, hv_poG, hv_ag;
	HTuple ht1, ht3, ht2, ht, Isinside, Sign, Displacement, hv_DFilt, hv_Dout, hv_nObj, hv_i;
	HTuple r51, c51, r52, c52, ww, wh, wcx, wcy;
	/*if (hWindow.IsHandleValid())
	{
		hWindow.CloseWindow();
		return;
	}*/
	//hWindow.InvalidateHandle();
	ReadObject(&ho_Rectangle5, "C:\\Temp1\\Rectangle5.hobj");
	//printf("***Rectangle5 Open***");
	hv_thr = 150;
	CountObj(m_ho_ContoursGrsm, &hv_nObj);
	GenEmptyObj(&ho_Defects);
	CountSeconds(&ht1);
	int nObj = hv_nObj.I();
	for (int i = 1; i <= nObj; i++)
	{
		m_hv_meander = (HTuple)i;
		SelectObj(m_ho_ContoursGrsm, &m_ho_CG, m_hv_meander);
		SelectObj(m_ho_MeanderRects, &ho_Rectangle5, m_hv_meander);
		//GetContourXld(m_ho_CG, &m_hv_RowG, &m_hv_ColG);


		ReduceDomain(m_ho_Im, ho_Rectangle5, &ho_Imr);
		//CropDomain(ho_Imr, &ho_Imc);

		BuildRealContour(ho_Imr, ho_Rectangle5, &ho_ContourOut, &ho_BorderEPs,
			&ho_RegionIR, m_hv_ctype, hv_thr);
		//WriteObject(ho_ContourOut, "C:\\Temp1\\ho_ContourOut.hobj");
		//WriteObject(m_ho_CG, "C:\\Temp1\\m_ho_CG.hobj");

		GetContourXld(ho_ContourOut, &m_hv_RowI, &m_hv_ColI);
		GetContourXld(m_ho_CG, &m_hv_RowG, &m_hv_ColG);

		/*AreaCenterXld(ho_ContourOut, &hv_ai, &hv_rowIc, &hv_colIc, &hv_poI);
		AreaCenterXld(m_ho_CG, &hv_ag, &hv_rowGc, &hv_colGc, &hv_poG);*/

		HObject RegionGr, RegionGr5, RegionGr5b, ho_RegionIRb;
		HTuple Area, RowG5, ColG5;
		GenRegionContourXld(m_ho_CG, &RegionGr, "filled");
		Intersection(RegionGr,ho_Rectangle5, &RegionGr5);
		Boundary(RegionGr5, &RegionGr5b, "inner");
		AreaCenter(RegionGr5b, &Area, &RowG5, &ColG5);

		HTuple AreaIR, RowIR, ColIR;
		Boundary(ho_RegionIR, &ho_RegionIRb, "inner");
		AreaCenter(ho_RegionIRb, &AreaIR, &RowIR, &ColIR);

		//hv_mr = hv_rowIc - hv_rowGc;
		//hv_mc = hv_colIc - hv_colGc;

		hv_mr = RowIR - RowG5;
		hv_mc = ColIR - ColG5;

		m_hv_RowG = m_hv_RowG + hv_mr;
		m_hv_ColG = m_hv_ColG + hv_mc;
		//GenContourPolygonXld(&ho_ContourGm, m_hv_RowG, m_hv_ColG);
		HTuple hv_nI, hv_nG, hv_D;
		//CountSeconds(&ht2);
		float* pRowI = ConvertTupleToFloat(m_hv_RowI);
		float* pColI = ConvertTupleToFloat(m_hv_ColI);
		float* pRowG = ConvertTupleToFloat(m_hv_RowG);
		float* pColG = ConvertTupleToFloat(m_hv_ColG);
		TupleLength(m_hv_RowI, &hv_nI);
		TupleLength(m_hv_RowG, &hv_nG);
		int nI = hv_nI.I();
		int nG = hv_nG.I();
		int isz = 21;
		float *pD = (float *)malloc((nI) * sizeof(float));

		//CountSeconds(&ht1);

		DistanceContours2(pRowI, pColI, nI, pRowG, pColG, nG,
			isz, pD, 0);

		
		FloatToTuple(pD, nI, hv_D);
		TestXldPoint(m_ho_CG, m_hv_RowI, m_hv_ColI, &Isinside);
		Sign = Isinside * 2.0 - 1.0;
		Displacement = -Sign * hv_D;

		float* pDisp = ConvertTupleToFloat(Displacement);

		float *pFilt = (float *)malloc((nI) * sizeof(float));
		SrunmedSLI(pDisp, pFilt, (long)nI, m_fsz, 0, 0);
		FloatToTuple(pFilt, nI, hv_DFilt);
		hv_Dout = Displacement - hv_DFilt;
		/*ht = ht3 - ht2;
		double msec2 = ht.D()*1000.;*/

		HTuple ThrMB, ThrSP, DefSP, DefMB, Def, DefA, RowD, ColD, nD, Rd;
		HObject CircleD, CircleDu;

		TupleGenConst((HTuple)nI, -m_hw_absmb, &ThrMB);
		TupleGenConst((HTuple)nI, m_hw_abssp, &ThrSP);
		TupleGreaterEqualElem(hv_Dout, ThrSP, &DefSP);
		TupleLessEqualElem(hv_Dout, ThrMB, &DefMB);
		Def = DefSP - DefMB;
		TupleAbs(Def, &DefA);
		TupleSelectMask(m_hv_RowI, DefA, &RowD);
		TupleSelectMask(m_hv_ColI, DefA, &ColD);
		TupleLength(RowD, &nD);
		if (nD > 1)
		{
			TupleGenConst(nD, 2.5, &Rd);
			GenCircle(&CircleD, RowD, ColD, Rd);
			Union1(CircleD, &CircleDu);
			ConcatObj(ho_Defects, CircleDu, &ho_Defects);
		}
	} // for nObj
	CountSeconds(&ht3);
	ht = ht3 - ht1;
	double msec1 = ht.D()*1.;


	printf("\n***Meadner cycle, %d-->%.2f sec***", nObj,msec1);

	WriteObject(ho_Defects, "C:\\Temp1\\ho_Defects.hobj");
	//printf("\n***BuildRealContour #%i , %f msec***", m_ctype, msec2);
	//HTuple GnuplotFileID, FD;
	//GnuplotOpenPipe(&GnuplotFileID);
	//CreateFunct1dArray(hv_D, &FD);
	////HGnuplot::GnuplotOpenPipe();
	//GnuplotPlotFunct1d(GnuplotFileID, FD);
	//GnuplotClose(GnuplotFileID);

	//WriteTuple(hv_D, "C:\\Temp1\\D2CPP_r.tup");
	/*WriteTuple(Displacement, "C:\\Temp1\\Displacement_r.tup");
	WriteTuple(hv_DFilt, "C:\\Temp1\\hv_Filt_r.tup");
	WriteTuple(hv_Dout, "C:\\Temp1\\Dout_r.tup");*/

	/*free(pD);
	free(pRowI);
	free(pColI);
	free(pRowG);
	free(pColG);
	free(pFilt);*/

	//SmallestRectangle1(ho_Rectangle5, &r51, &c51, &r52, &c52);
	//ww = (c52 - c51);
	//wh = (r52 - r51);
	//HTuple ks, kx, ky;
	//kx = 1920 / ww;
	//ky = 1080 / wh;
	//TupleMin2(kx, ky, &ks);
	//if (ks > 8)
	//	ks = 8;
	//ww = ww * ks;
	//wh = wh * ks;

	//wcy = r51 + wh / 2;
	//wcx = c51 + ww / 2;
	////hWindow.MoveRectangle();
	//hWindow.OpenWindow(0, 0, ww, wh, 0, "visible", "");
	//hWindow.SetPart((Hlong)r51, (Hlong)c51, (Hlong)r52, (Hlong)c52);
	//hWindow.DispImage(m_ho_Im);
	///*if (nD > 1)
	//	hWindow.SetColor("coral");
	//else*/
	//	hWindow.SetColor("green");
	//hWindow.SetLineWidth(3);
	//hWindow.DispObj(ho_ContourOut);

	//hWindow.SetColor("blue");
	//hWindow.SetLineWidth(1);
	//hWindow.DispObj(m_ho_CG);

	//hWindow.SetColor("cyan");
	//hWindow.SetLineWidth(2);
	//hWindow.DispObj(ho_ContourGm);

	///*if (nD > 1)
	//{
	//	hWindow.SetDraw("margin");
	//	hWindow.SetColor("red");
	//	hWindow.SetLineWidth(3);
	//	hWindow.DispObj(CircleDu);
	//}*/
	//// Keep the window open until a key is pressed
	//hWindow.Click();

	//// Close the window
	//hWindow.CloseWindow();
}





void CTestContoursDlg::OnEnChangeEdit5()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT5, cstr);
	num = (int)_tstof(cstr);
}


void CTestContoursDlg::OnBnClickedButton10()  //Meander Insp.cyc.func.(all meanders)
{
	
	HObject ho_MeanderDefect, ho_MeanderDefects, ho_Rect;
	HTuple hv_DOut, hv_nObj;
	HTuple ht1, ht3, ht2, ht;
	HTuple Ad, Rd, Cd, ti, pn;

	CountObj(m_ho_ContoursGrsm, &hv_nObj);
	int nObj = hv_nObj.I();
	HTuple Padnum;
	Padnum.Clear();
	

	CountObj(m_ho_ContoursGrsm, &hv_nObj);
	GenEmptyObj(&ho_MeanderDefects);
	CountSeconds(&ht1);
//	int nObj = hv_nObj.I();

	CountSeconds(&ht1);
	for (int i = 1; i <= nObj; i++)
	{
		m_hv_meander = (HTuple)i;
		ProcessMeander(m_ho_Im, m_ho_ContoursGrsm, m_ho_MeanderRects, m_ho_Gi,
			&ho_MeanderDefect, &ho_Rect, &m_ho_CG, &m_ho_CI,
			m_hv_thr, m_hv_meander, m_hw_absmb, m_hw_abssp, m_hv_ctype, m_fsz,
			&hv_DOut);
		ConcatObj(ho_MeanderDefects, ho_MeanderDefect, &ho_MeanderDefects);
		AreaCenter(ho_MeanderDefect, &Ad, &Rd, &Cd);
		if (Ad > 0)
			TupleConcat(Padnum, (HTuple)i, &Padnum);
	}
	CountSeconds(&ht3);
	ht = ht3 - ht1;
	double msec1 = ht.D()*1000.;

	HTuple DefMnum;
	ConcatObj(ho_MeanderDefects, ho_MeanderDefect, &ho_MeanderDefects);
	CountObj(ho_MeanderDefects, &DefMnum);

	HTuple W, H, srow, scol;
	GetImageSize(m_ho_Im,&W, &H);
	
	HTuple ks, kx, ky;
	kx = 1920. / W;
	ky = 1080. / H;
	TupleMin2(kx, ky, &ks);
	///*if (ks > 8)
	//	ks = 8;*/
	TupleInt(W * ks*0.9, &W);
	TupleInt(H * ks*0.9, &H);
	//H = int(H * ks);

	printf("\n***Meadner cycle, (%d)-->%.2f sec***", nObj, msec1);
	//HTuple r51, c51, r52, c52, ww, wh, wcx, wcy;
	WriteObject(ho_MeanderDefects, "C:\\Temp1\\ho_MeanderDefects.hobj");
	if (disp)
	{
		if (hWindow.IsHandleValid())
			hWindow.CloseWindow();

		hWindow.OpenWindow(0, WINST, W, H, 0, "visible", "");
		hWindow.DispImage(m_ho_Im);
		hWindow.SetDraw("margin");
		hWindow.SetColor("red");
		hWindow.SetLineWidth(5);
		if (DefMnum > 0)
		{
			hWindow.DispObj(ho_MeanderDefects);
			hWindow.DispText("Defected meanders " + (DefMnum), "window", "center", "center", "red", "shadow", "true");
			for (ti = 1; ti <= DefMnum; ti = ti + 1)
			{
				SelectObj(ho_MeanderDefects, &ho_MeanderDefect, ti);
				AreaCenter(ho_MeanderDefect, &Ad, &Rd, &Cd);
				pn = HTuple(Padnum[ti - 1]);
				hWindow.DispText((pn), "image", Rd, Cd, "red", "box", "false");
			}
		}
		else
			hWindow.DispText("No defected meanders found" + (DefMnum), "window", "center", "center", "forest green", "shadow", "true");
//		hWindow.Click();

		// Close the window
//		hWindow.CloseWindow();
	}
	

	//printf("\n***Meadner single cycle ended ***" );
	//printf("\n***Meadner single cycle ended-->%.2f msec***", msec1);
	
}


void CTestContoursDlg::OnBnClickedCheck3()
{
	save = !save;
}


void CTestContoursDlg::OnEnChangeEdit6()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT6, cstr);
	m_hv_pad = (int)_tstof(cstr);
}


void CTestContoursDlg::OnBnClickedButton11() //Isolated pad single cycle
{
	//int fsz = 21;
	
	HObject ho_PadDefect, ho_Rect, ho_RegionIR, ho_RBEp;
	HTuple hv_DOut;
	HTuple lht1, lht3, lht2, lht, hv_meander;

	SelectObj(m_ho_RegionsGPadsIsol, &m_ho_Rectangle5, m_hv_pad);
	SelectObj(m_ho_ContoursGPadsIsol, &m_ho_CG, m_hv_pad);
	CountSeconds(&lht1);
	HTuple hv_pdil = 5;
	for (int i = 0; i < num; i++)
		ProcessPads(m_ho_Im, m_ho_ContoursGPadsIsol, m_ho_RegionsGPadsIsol, m_ho_Gi, m_ho_RegionI, m_ho_RegionGPad,
			&ho_PadDefect, &ho_Rect, &m_ho_CG, &m_ho_CI, &ho_RegionIR, &ho_RBEp,
			m_hv_thr, m_hv_pad, m_hw_absmbpad, m_hw_abssppad, m_hv_ctype, m_fszpad, hv_pdil,
			&hv_DOut);
	//m_ho_CI=
	CountSeconds(&lht3);
	lht = lht3 - lht1;
	double msec1 = lht.D()*1000.;

	//printf("\n***Meadner single cycle ended ***" );
	printf("\n***Isolated pad single cycle ended (%d)-->%.2f msec***", num, msec1);

	lht1 = ht2 - ht1;
	msec1 = lht1.D()*1000.;
	lht1 = ht3 - ht2;
	double msec2 = lht1.D()*1000.;
	lht1 = ht4 - ht3;
	double msec3 = lht1.D()*1000.;
	lht1 = ht5 - ht4;
	double msec4 = lht1.D()*1000.;
	lht1 = ht6 - ht5;
	double msec5 = lht1.D()*1000.;
	printf("\n***Isolated pad single cycle ended (%d)-->%.2f + %.2f + (IsInside)%.2f + %.2f + %.2f  msec***", num, msec1, msec2, msec3, msec4, msec5);
	if (disp)
	{
		if (hWindow.IsHandleValid())
		{
			//hWindow.DispText("Closing the window", "window", "center", "center", "blue", "shadow", "true");
			//hWindow.Click();
			hWindow.CloseWindow();
			//return;
		}
		//else
		{
			int save = 0;
			//hWindow.InvalidateHandle();

			HTuple r51, c51, r52, c52, ww, wh, wcx, wcy;

			SmallestRectangle1(ho_Rect, &r51, &c51, &r52, &c52);
			ww = (c52 - c51);
			wh = (r52 - r51);
			HTuple ks, kx, ky;
			kx = 1920 / ww;
			ky = 1080 / wh;
			TupleMin2(kx, ky, &ks);
			if (ks > 8)
				ks = 8;
			ww = ww * ks;
			wh = wh * ks;

			wcy = r51 + wh / 2;
			wcx = c51 + ww / 2;
			//hWindow.MoveRectangle();
			hWindow.OpenWindow(0, WINST, ww, wh, 0, "visible", "");
			hWindow.SetPart((Hlong)r51, (Hlong)c51, (Hlong)r52, (Hlong)c52);
			hWindow.DispImage(m_ho_Im);
			//hWindow.SetColor("blue");
			//hWindow.SetLineWidth(1);
			//hWindow.DispObj(m_ho_CG);
			//hWindow.SetColor("green");
			//hWindow.DispObj(m_ho_CI);
			HTuple hv_a, r, c;
			CountObj(ho_PadDefect, &hv_a);
			//AreaCenter(ho_MeanderDefects, &a, &r, &c);
			if (hv_a.I() > 0)
			{
				hWindow.SetColor("blue");
				hWindow.SetLineWidth(1);
				hWindow.DispObj(m_ho_CG);

				hWindow.SetLineWidth(2);
				hWindow.SetColor("coral");
				hWindow.DispObj(m_ho_CI);

				hWindow.SetDraw("margin");
				hWindow.SetColor("red");
				hWindow.SetLineWidth(3);
				hWindow.DispObj(ho_PadDefect);
			}
					//hWindow.SetColor("coral");
			else
			{
				hWindow.SetColor("green");
				hWindow.SetLineWidth(3);
				hWindow.DispObj(m_ho_CI);



				//	hWindow.SetColor("cyan");
				//	hWindow.SetLineWidth(2);
				//	hWindow.DispObj(ho_ContourGm);

				//	//if (a.I() > 1)
				//	//{
				
			//}
			//else
				//hWindow.SetFont("Courier-Bold-14");
				hWindow.DispText("No defects found", "window", "center", "center", "green", "shadow", "true");
			}
			// Keep the window open until a key is pressed
			//WriteTuple(Displacement, "C:\\Temp1\\hv_Displacement.tup");
			//WriteTuple(hv_DOut, "C:\\Temp1\\hv_Dout.tup");
			//hWindow.Click();

			// Close the window
			//hWindow.CloseWindow();
		}
		
	}
}


void CTestContoursDlg::OnBnClickedButton12() //Connected pad single cycle
{
	HObject ho_PadDefectC, ho_Rect, ho_RegionIR, ho_RBEp;
	HTuple hv_DOut;
	HTuple lht1, lht3, lht2, lht, hv_pdil=5;

	SelectObj(m_ho_RegionsGPadsCon, &m_ho_Rectangle5, m_hv_padc);
	SelectObj(m_ho_ContoursGPadsCon, &m_ho_CG, m_hv_padc);
	CountSeconds(&lht1);
	for (int i = 0; i < num; i++)
		/*ProcessPads(m_ho_Im, m_ho_ContoursGrsmPi, m_ho_RectanglesPadsIsol, m_ho_Gi, m_ho_RegionI,
			&ho_PadDefectC, &ho_Rect, &m_ho_CG, &m_ho_CI,
			m_hv_thr, m_hv_padc, m_hw_absmb, m_hw_abssp, m_hv_ctype, m_fsz,
			&hv_DOut);*/
	ProcessPads(m_ho_Im, m_ho_ContoursGPadsCon, m_ho_RegionsGPadsCon, m_ho_Gi, m_ho_RegionI, m_ho_RegionGPad,
		&ho_PadDefectC, &ho_Rect, &m_ho_CG, &m_ho_CI, &ho_RegionIR, &ho_RBEp,
		m_hv_thr, m_hv_padc, m_hw_absmbpad, m_hw_abssppad, m_hv_ctype, m_fszpad, hv_pdil,
		&hv_DOut);
	//m_ho_CI=
	CountSeconds(&lht3);
	lht = lht3 - lht1;
	double msec1 = lht.D()*1000.;

	//printf("\n***Meadner single cycle ended ***" );
	printf("\n***Connected pad single cycle ended (%d)-->%.2f msec***", num, msec1);

	lht1 = ht2 - ht1;
	msec1 = lht1.D()*1000.;
	lht1 = ht3 - ht2;
	double msec2 = lht1.D()*1000.;
	lht1 = ht4 - ht3;
	double msec3 = lht1.D()*1000.;
	lht1 = ht5 - ht4;
	double msec4 = lht1.D()*1000.;
	lht1 = ht6 - ht5;
	double msec5 = lht1.D()*1000.;
	printf("\n***Isolated pad single cycle ended (%d)-->%.2f + %.2f + (IsInside)%.2f + %.2f + %.2f  msec***", num, msec1, msec2, msec3, msec4, msec5);
	if (disp)
	{
		if (hWindow.IsHandleValid())
		{
			//hWindow.DispText("Closing the window", "window", "center", "center", "blue", "shadow", "true");
			//hWindow.Click();
			hWindow.CloseWindow();
			//return;
		}
		//else
		{
			int save = 0;
			//hWindow.InvalidateHandle();

			HTuple r51, c51, r52, c52, ww, wh, wcx, wcy;

			SmallestRectangle1(ho_Rect, &r51, &c51, &r52, &c52);
			ww = (c52 - c51);
			wh = (r52 - r51);
			HTuple ks, kx, ky;
			kx = 1920 / ww;
			ky = 1080 / wh;
			TupleMin2(kx, ky, &ks);
			if (ks > 8)
				ks = 8;
			ww = ww * ks;
			wh = wh * ks;

			wcy = r51 + wh / 2;
			wcx = c51 + ww / 2;
			//hWindow.MoveRectangle();

			if (hWindow.IsHandleValid())
				hWindow.CloseWindow();

			hWindow.OpenWindow(0, WINST, ww, wh, 0, "visible", "");
			hWindow.SetPart((Hlong)r51-10, (Hlong)c51-10, (Hlong)r52+10, (Hlong)c52+10);
			hWindow.DispImage(m_ho_Im);
			HTuple hv_a, r, c;
			CountObj(ho_PadDefectC, &hv_a);
			//AreaCenter(ho_MeanderDefects, &a, &r, &c);
			/// ex. 
			hWindow.SetColor("blue");
			hWindow.SetLineWidth(1);
			hWindow.DispObj(m_ho_CG);
			hWindow.SetColor("green");
			hWindow.DispObj(m_ho_CI);
			if (hv_a.I() > 0)
			{
				
				hWindow.SetLineWidth(2);
					hWindow.SetColor("coral");
					hWindow.DispObj(m_ho_CI);
				/*else
					hWindow.SetColor("green");*/
					/*hWindow.SetLineWidth(3);
					hWindow.DispObj(m_ho_CI);*/



					/*hWindow.SetColor("cyan");
					hWindow.SetLineWidth(2);
					hWindow.DispObj(ho_ContourGm);*/

					//if (a.I() > 1)
					//{
				hWindow.SetDraw("margin");
				hWindow.SetColor("red");
				hWindow.SetLineWidth(3);
				hWindow.DispObj(ho_PadDefectC);
			}
			else
				//hWindow.SetFont("Courier-Bold-14");
				hWindow.DispText("No defects found", "window", "center", "center", "green", "shadow", "true");
			// Keep the window open until a key is pressed
			//WriteTuple(Displacement, "C:\\Temp1\\hv_Displacement.tup");
			WriteTuple(hv_DOut, "C:\\Temp1\\hv_Dout.tup");
			//hWindow.Click();

			// Close the window
			//hWindow.CloseWindow();
		}

	}
	/*if (save)
	{
		WriteTuple(Displacement, "C:\\Temp1\\hv_Displacement.tup");
		WriteTuple(hv_DOut, "C:\\Temp1\\hv_Dout.tup");
	}*/
}


void CTestContoursDlg::OnEnChangeEdit7()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT7, cstr);
	m_hv_padc = (int)_tstof(cstr);
}

//int pnum;
void CTestContoursDlg::OnBnClickedButton13() // Pads isol. cycle
{
	HObject ho_PadIDefect, ho_PadIDefects, ho_Rect, ho_RegionIR, ho_RBEp;
	HTuple hv_DOut, hv_nObj;
	HTuple ht1, ht3, ht2, ht, hv_pdil=5;



	CountObj(m_ho_ContoursGPadsIsol, &hv_nObj);
	GenEmptyObj(&ho_PadIDefects);
	CountSeconds(&ht1);
	int nObj = hv_nObj.I();
	HTuple Padnum;
	Padnum.Clear();
	HTuple Ad, Rd, Cd, ti, pn;

	CountSeconds(&ht1);
	for (int i = 1; i <= nObj; i++)
	{
		m_hv_pad = (HTuple)i;
		WriteTuple(m_hv_meander, "C:/numpad");
		//pnum = i;
		//ProcessPads(m_ho_Im, m_ho_ContoursGrsmPi, m_ho_RectanglesPadsIsol, m_ho_Gi, m_ho_RegionI,
		//	&ho_PadIDefect, &ho_Rect, &m_ho_CG, &m_ho_CI,
		//	m_hv_thr, m_hv_meander, m_hw_absmbpad, m_hw_abssppad, m_hv_ctype, m_fszpad,
		//	&hv_DOut);
		ProcessPads(m_ho_Im, m_ho_ContoursGPadsIsol, m_ho_RegionsGPadsIsol, m_ho_Gi, m_ho_RegionI, m_ho_RegionGPad,
			&ho_PadIDefect, &ho_Rect, &m_ho_CG, &m_ho_CI, &ho_RegionIR, &ho_RBEp,
			m_hv_thr, m_hv_pad, m_hw_absmbpad, m_hw_abssppad, m_hv_ctype, m_fszpad, hv_pdil,
			&hv_DOut);
		ConcatObj(ho_PadIDefects, ho_PadIDefect, &ho_PadIDefects);
		AreaCenter(ho_PadIDefect, &Ad, &Rd, &Cd);
		if (Ad > 0)
			TupleConcat(Padnum, (HTuple)i, &Padnum);
	}
	CountSeconds(&ht3);
	ht = ht3 - ht1;
	double msec1 = ht.D()*1000.;

	HTuple DefPInum;
	ConcatObj(ho_PadIDefects, ho_PadIDefect, &ho_PadIDefects);
	CountObj(ho_PadIDefects, &DefPInum);

	HTuple W, H, srow, scol;
	GetImageSize(m_ho_Im, &W, &H);

	HTuple ks, kx, ky;
	kx = 1920. / W;
	ky = 1080. / H;
	TupleMin2(kx, ky, &ks);
	///*if (ks > 8)
	//	ks = 8;*/
	TupleInt(W * ks*0.9, &W);
	TupleInt(H * ks*0.9, &H);
	//H = int(H * ks);

	printf("\n***Isolated pads cycle, (%d)-->%.2f sec***", nObj, msec1);
	//HTuple r51, c51, r52, c52, ww, wh, wcx, wcy;
	WriteObject(ho_PadIDefects, "C:\\Temp1\\ho_ho_PadIDefects.hobj");
	if (disp)
	{
		if (hWindow.IsHandleValid())
			hWindow.CloseWindow();

		hWindow.OpenWindow(0, WINST, W, H, 0, "visible", "");
		hWindow.DispImage(m_ho_Im);
		hWindow.SetDraw("margin");
		hWindow.SetColor("red");
		hWindow.SetLineWidth(5);
		if (DefPInum > 0)
		{
			hWindow.DispObj(ho_PadIDefects);
			hWindow.DispText("Defected isolated pads: " + (DefPInum), "window", "center", "center", "red", "shadow", "true");

			for (ti = 1; ti <= DefPInum; ti = ti + 1)
			{
				SelectObj(ho_PadIDefects, &ho_PadIDefect, ti);
				AreaCenter(ho_PadIDefect, &Ad, &Rd, &Cd);
				pn = HTuple(Padnum[ti - 1]);
				hWindow.DispText((pn), "image", Rd, Cd, "red", "box", "false");
			}
		}
		else
			hWindow.DispText("No defected isolated pads found" + (DefPInum), "window", "center", "center", "forest green", "shadow", "true");
		//hWindow.Click();

		// Close the window
		//hWindow.CloseWindow();
	}
}


void CTestContoursDlg::OnBnClickedButton14() /// Pads con. full cycle
{
	HObject ho_PadCDefect, ho_PadCDefects, ho_Rect, ho_RegionIR, ho_RBEp;
	HTuple hv_DOut, hv_nObj;
	HTuple ht1, ht3, ht2, ht, hv_pdil=3;

	HTuple DefPCnum;

	CountObj(m_ho_ContoursGPadsCon, &hv_nObj);
	GenEmptyObj(&ho_PadCDefects);
	CountSeconds(&ht1);
	int nObj = hv_nObj.I();

	CountSeconds(&ht1);
	HTuple Padnum;
	Padnum.Clear();
	HTuple Ad, Rd, Cd, ti, pn;
	CountObj(ho_PadCDefects, &DefPCnum);
	
	for (int i = 1; i <= nObj; i++)
	{
		m_hv_pad = (HTuple)i;
		//ProcessPads(m_ho_Im, m_ho_ContoursGrsmPi, m_ho_RectanglesPadsIsol, m_ho_Gi, m_ho_RegionI,
		//	&ho_PadCDefect, &ho_Rect, &m_ho_CG, &m_ho_CI,
		//	m_hv_thr, m_hv_meander, m_hw_absmb, m_hw_abssp, m_hv_ctype, m_fsz,
		//	&hv_DOut);
		ProcessPads(m_ho_Im, m_ho_ContoursGPadsCon, m_ho_RegionsGPadsCon, m_ho_Gi, m_ho_RegionI, m_ho_RegionGPad,
			&ho_PadCDefect, &ho_Rect, &m_ho_CG, &m_ho_CI, &ho_RegionIR, &ho_RBEp,
			m_hv_thr, m_hv_pad, m_hw_absmbpad, m_hw_abssppad, m_hv_ctype, m_fszpad, hv_pdil,
			&hv_DOut);
		Union1(ho_PadCDefect, &ho_PadCDefect);
		AreaCenter(ho_PadCDefect, &Ad, &Rd, &Cd);
		if (Ad > 0)
		{
			ConcatObj(ho_PadCDefects, ho_PadCDefect, &ho_PadCDefects);
			CountObj(ho_PadCDefects, &DefPCnum);
			TupleConcat(Padnum, (HTuple)i, &Padnum);
		}
		    
	}
	CountSeconds(&ht3);
	ht = ht3 - ht1;
	double msec1 = ht.D()*1000.;

	//HTuple DefPCnum;
	//ConcatObj(ho_PadCDefects, ho_PadCDefect, &ho_PadCDefects);
	CountObj(ho_PadCDefects, &DefPCnum);

	HTuple W, H, srow, scol;
	GetImageSize(m_ho_Im, &W, &H);

	HTuple ks, kx, ky;
	kx = 1920. / W;
	ky = 1080. / H;
	TupleMin2(kx, ky, &ks);
	///*if (ks > 8)
	//	ks = 8;*/
	TupleInt(W * ks*0.9, &W);
	TupleInt(H * ks*0.9, &H);
	//H = int(H * ks);

	printf("\n***Connected pads cycle, (%d)-->%.2f msec***", nObj, msec1);
	//HTuple r51, c51, r52, c52, ww, wh, wcx, wcy;
	WriteObject(ho_PadCDefects, "C:\\Temp1\\ho_ho_PadCDefects.hobj");
	if (disp)
	{
		if (hWindow.IsHandleValid())
			hWindow.CloseWindow();

		hWindow.OpenWindow(0, WINST, W, H, 0, "visible", "");
		hWindow.DispImage(m_ho_Im);
		hWindow.SetDraw("margin");
		hWindow.SetColor("red");
		hWindow.SetLineWidth(5);
		if (DefPCnum > 0)
		{
			hWindow.DispObj(ho_PadCDefects);
			hWindow.DispText("Defected connected pads: " + (DefPCnum), "window", "center", "center", "red", "shadow", "true");
			HTuple nn;
			TupleLength(Padnum, &nn);
			for (ti = 1; ti <= DefPCnum; ti = ti + 1)
			{
				SelectObj(ho_PadCDefects, &ho_PadCDefect, ti);
				AreaCenter(ho_PadCDefect, &Ad, &Rd, &Cd);
				//pn = m_hv_pad;
				pn = HTuple(Padnum[ti - 1]);
				hWindow.DispText((pn), "image", Rd, Cd, "red", "box", "false");
			}
			/*hWindow.SetLineWidth(2);
			hWindow.SetColor("coral");
			hWindow.DispObj(m_ho_CI);*/
			   
		}
		else
			hWindow.DispText("No defected connected pads found" + (DefPCnum), "window", "center", "center", "forest green", "shadow", "true");
		//hWindow.Click();

		// Close the window
		//hWindow.CloseWindow();
	}
}


void CTestContoursDlg::OnBnClickedButton15()
{
	HObject ho_WADefect, ho_Rect;
	HTuple hv_DOut;
	HTuple lht1, lht3, lht2, lht;
	//m_hv_wa = 720;
	SelectObj(m_ho_RectanglesWireAngles, &m_ho_Rectangle5, m_hv_wa);
	SelectObj(m_ho_ContoursWireAngles, &m_ho_CG, m_hv_wa);
	CountSeconds(&lht1);
	for (int i = 0; i < num; i++)
		ProcessMeander(m_ho_Im, m_ho_ContoursWireAngles, m_ho_RectanglesWireAngles, m_ho_Gi,
			&ho_WADefect, &ho_Rect, &m_ho_CG, &m_ho_CI,
			m_hv_thr, m_hv_wa, m_hw_absmbwa, m_hw_absspwa, m_hv_ctype, m_fszwa,
			&hv_DOut);

	CountSeconds(&lht3);
	lht = lht3 - lht1;
	double msec1 = lht.D()*1000.;

	printf("\n***Angled wire single cycle ended (%d)-->%.2f msec***", num, msec1);

	lht1 = ht2 - ht1;
	msec1 = lht1.D()*1000.;
	lht1 = ht3 - ht2;
	double msec2 = lht1.D()*1000.;
	lht1 = ht4 - ht3;
	double msec3 = lht1.D()*1000.;
	lht1 = ht5 - ht4;
	double msec4 = lht1.D()*1000.;
	lht1 = ht6 - ht5;
	double msec5 = lht1.D()*1000.;
	printf("\n***Angled wire single cycle ended (%d)-->%.2f + %.2f + (IsInside)%.2f + %.2f + %.2f  msec***", num, msec1, msec2, msec3, msec4, msec5);
	if (disp)
	{
		if (hWindow.IsHandleValid())
		{

			hWindow.CloseWindow();

		}
		//else
		{
			int save = 0;


			HTuple r51, c51, r52, c52, ww, wh, wcx, wcy;

			SmallestRectangle1(ho_Rect, &r51, &c51, &r52, &c52);
			ww = (c52 - c51);
			wh = (r52 - r51);
			HTuple ks, kx, ky;
			kx = 1920 / ww;
			ky = 1080 / wh;
			TupleMin2(kx, ky, &ks);
			if (ks > 8)
				ks = 8;
			ww = ww * ks;
			wh = wh * ks;

			wcy = r51 + wh / 2;
			wcx = c51 + ww / 2;

			if (hWindow.IsHandleValid())
				hWindow.CloseWindow();

			hWindow.OpenWindow(0, WINST, ww, wh, 0, "visible", "");
			hWindow.SetPart((Hlong)r51 - 10, (Hlong)c51 - 10, (Hlong)r52 + 10, (Hlong)c52 + 10);
			hWindow.DispImage(m_ho_Im);
			HTuple hv_a, r, c;
			CountObj(ho_WADefect, &hv_a);
			//AreaCenter(ho_MeanderDefects, &a, &r, &c);
			hWindow.SetColor("blue");
			hWindow.SetLineWidth(1);
			hWindow.DispObj(m_ho_CG);
			hWindow.SetColor("green");
			hWindow.DispObj(m_ho_CI);
			if (hv_a.I() > 0)
			{

				hWindow.SetLineWidth(2);
				hWindow.SetColor("coral");
				hWindow.DispObj(m_ho_CI);
				
				hWindow.SetDraw("margin");
				hWindow.SetColor("red");
				hWindow.SetLineWidth(3);
				hWindow.DispObj(ho_WADefect);
			}
			else

				hWindow.DispText("No defects found", "window", "center", "center", "green", "shadow", "true");

			//WriteTuple(hv_DOut, "C:\\Temp1\\hv_Dout.tup");
		}

	}
}


void CTestContoursDlg::OnBnClickedButton16()
{
	HObject ho_WADefect, ho_WADefects, ho_Rect;
	HTuple hv_DOut, hv_nObj;
	HTuple ht1, ht3, ht2, ht;



	CountObj(m_ho_ContoursWireAngles, &hv_nObj);
	GenEmptyObj(&ho_WADefects);
	CountSeconds(&ht1);
	int nObj = hv_nObj.I();

	CountSeconds(&ht1);
	HTuple WAnum;
	WAnum.Clear();
	HTuple Ad, Rd, Cd, ti, pn;

	for (int i = 1; i <= nObj; i++)
	{
		m_hv_meander = (HTuple)i;
		ProcessMeander(m_ho_Im, m_ho_ContoursWireAngles, m_ho_RectanglesWireAngles, m_ho_Gi,
			&ho_WADefect, &ho_Rect, &m_ho_CG, &m_ho_CI,
			m_hv_thr, m_hv_meander, m_hw_absmbwa, m_hw_absspwa, m_hv_ctype, m_fszwa,
			&hv_DOut);
		ConcatObj(ho_WADefects, ho_WADefect, &ho_WADefects);
		AreaCenter(ho_WADefect, &Ad, &Rd, &Cd);
		if (Ad > 0)
			TupleConcat(WAnum, (HTuple)i, &WAnum);
	}
	CountSeconds(&ht3);
	ht = ht3 - ht1;
	double msec1 = ht.D()*1000.;

	HTuple DefWAnum;
	ConcatObj(ho_WADefects, ho_WADefect, &ho_WADefects);
	CountObj(ho_WADefects, &DefWAnum);

	HTuple W, H, srow, scol;
	GetImageSize(m_ho_Im, &W, &H);

	HTuple ks, kx, ky;
	kx = 1920. / W;
	ky = 1080. / H;
	TupleMin2(kx, ky, &ks);
	///*if (ks > 8)
	//	ks = 8;*/
	TupleInt(W * ks*0.9, &W);
	TupleInt(H * ks*0.9, &H);
	//H = int(H * ks);

	printf("\n***Wire angles cycle, (%d)-->%.2f msec***", nObj, msec1);
	//HTuple r51, c51, r52, c52, ww, wh, wcx, wcy;
	WriteObject(ho_WADefects, "C:\\Temp1\\ho_ho_ho_WADefects.hobj");
	if (disp)
	{
		if (hWindow.IsHandleValid())
			hWindow.CloseWindow();

		hWindow.OpenWindow(0, WINST, W, H, 0, "visible", "");
		hWindow.DispImage(m_ho_Im);
		hWindow.SetDraw("margin");
		hWindow.SetColor("red");
		hWindow.SetLineWidth(5);
		if (DefWAnum > 0)
		{
			hWindow.DispObj(ho_WADefects);
			hWindow.DispText("Defected wire angles: " + (DefWAnum), "window", "center", "center", "red", "shadow", "true");

			for (ti = 1; ti <= DefWAnum; ti = ti + 1)
			{
				SelectObj(ho_WADefects, &ho_WADefect, ti);
				AreaCenter(ho_WADefect, &Ad, &Rd, &Cd);
				pn = HTuple(WAnum[ti - 1]);
				/*HTuple hrd;
				TupleRand(1,&hrd);
				hrd = (int)(hrd * 10);*/
				hWindow.DispText((pn), "image", Rd, Cd, "red", "box", "false");
			}
			hWindow.SetLineWidth(2);
			hWindow.SetColor("coral");
			hWindow.DispObj(m_ho_CI);

		}
		else
			hWindow.DispText("No defected wire angles found" + (DefWAnum), "window", "center", "center", "forest green", "shadow", "true");
		//hWindow.Click();

		// Close the window
		//hWindow.CloseWindow();
	}
}


void CTestContoursDlg::OnEnChangeEdit11()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT11, cstr);
	m_hv_wa = (int)_tstof(cstr);
}


void CTestContoursDlg::OnEnChangeEdit14()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT14, cstr);
	m_hw_absmbpad = _tstof(cstr);
}


void CTestContoursDlg::OnEnChangeEdit15()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT15, cstr);
	m_hw_abssppad = _tstof(cstr);
}


void CTestContoursDlg::OnEnChangeEdit16()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT16, cstr);
	m_fszwa = (int)_tstof(cstr);
}


void CTestContoursDlg::OnEnChangeEdit13()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT13, cstr);
	m_fszpad = (int)_tstof(cstr);
}


void CTestContoursDlg::OnEnChangeEdit17()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT17, cstr);
	m_hw_absmbwa = _tstof(cstr);
}


void CTestContoursDlg::OnEnChangeEdit18()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT18, cstr);
	m_hw_absspwa = _tstof(cstr);
}


void CTestContoursDlg::OnBnClickedButton17()
{
	// TODO: Add your control notification handler code here
}


void CTestContoursDlg::OnBnClickedButton18()
{
	// TODO: Add your control notification handler code here
}


void CTestContoursDlg::OnEnChangeEdit19()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CTestContoursDlg::OnEnChangeEdit22()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CTestContoursDlg::OnEnChangeEdit23()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CTestContoursDlg::OnEnChangeEdit21()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CTestContoursDlg::OnBnClickedButton19()
{
	HTuple tnum;
	CString cstr;

	ReadImage(&m_ho_Im, "C:\\Temp1\\Im.tif");
	ReadObject(&m_ho_Gi, "C:\\Temp1\\Gi.hobj");
	Threshold(m_ho_Im, &m_ho_RegionI, m_hv_thr, 255);
	printf("***Image Files Open***");

	ReadObject(&m_ho_ContoursGPadsIsol, "C:\\Temp1\\ContoursGPadsIsol.hobj");
	ReadObject(&m_ho_RegionsGPadsIsol, "C:\\Temp1\\RegionsGPadsIsol.hobj");
	CountObj(m_ho_RegionsGPadsIsol, &tnum);
	cstr.Format(_T("(%d)"), (int)tnum);
	SetDlgItemText(IDC_EDIT8, cstr);
	printf("\n***ContoursGPadsIsol.hobj and RegionsPadsIsol.hobj read***");
	ReadObject(&m_ho_ContoursGPadsCon, "C:\\Temp1\\ContoursGPadsCon.hobj");
	ReadObject(&m_ho_RegionsGPadsCon, "C:\\Temp1\\RegionsGPadsCon.hobj");
	CountObj(m_ho_RegionsGPadsCon, &tnum);
	cstr.Format(_T("(%d)"), (int)tnum);
	SetDlgItemText(IDC_EDIT9, cstr);
	printf("\n***ContoursGPadsCon.hobj and RegionsPadsCon.hobj read***");
}
