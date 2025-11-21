
// Master_OneDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Master_One.h"
#include "Master_OneDlg.h"
#include "afxdialogex.h"

#include "Halcon/Halcon_Common.h"
#include "Halcon/Scratch_Matching.h"
#include "Halcon/Missing_Pads.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMasterOneDlg dialog



CMasterOneDlg::CMasterOneDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MASTER_ONE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMasterOneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUT_FWM_LOW_SLOPE, But_FWM_Low_Slope);
	DDX_Control(pDX, IDC_BUT_FWM_RUN, But_FWM_Run);
	DDX_Control(pDX, IDC_BUT_FWM_SAVE, But_FWM_Save);
}

BEGIN_MESSAGE_MAP(CMasterOneDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_SCRATCHES, &CMasterOneDlg::OnBnClickedButScratches)
	ON_BN_CLICKED(IDC_BUT_MISSING_PADS, &CMasterOneDlg::OnBnClickedButMissingPads)
	ON_BN_CLICKED(IDC_BUT_FWM_LOAD, &CMasterOneDlg::OnBnClickedButFwmLoad)
	ON_BN_CLICKED(IDC_BUT_FWM_RUN, &CMasterOneDlg::OnBnClickedButFwmRun)
	ON_BN_CLICKED(IDC_BUT_FWM_SAVE, &CMasterOneDlg::OnBnClickedButFwmSave)
	ON_BN_CLICKED(IDC_BUT_FWM_LOW_SLOPE, &CMasterOneDlg::OnBnClickedButFwmLowSlope)
END_MESSAGE_MAP()


// CMasterOneDlg message handlers

BOOL CMasterOneDlg::OnInitDialog()
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

#ifdef _DEBUG
	// --- Open console
	if (!AllocConsole())
	{
		AfxMessageBox(_T("Failed AllocConsole()"));
	}
	freopen_s(&fp_console, "CONOUT$", "w", stdout);
	//freopen_s(&fp_console, "CONIN$", "r", stdin);
	//freopen_s(&fp_console, "CONOUT$", "w", stderr);

	std::cout << "Starting program Master ..." << std::endl;

	// --- Close console
	//fclose(fp_console);
	//if (!FreeConsole())
	//{
	//	AfxMessageBox(_T("Failed FreeConsole()"));
	//}
#endif


	// TODO: Add extra initialization here
	m_FWM = new FWM();

	But_FWM_Low_Slope.EnableWindow(false);
	But_FWM_Run.EnableWindow(false);
	But_FWM_Save.EnableWindow(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMasterOneDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMasterOneDlg::OnPaint()
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
HCURSOR CMasterOneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMasterOneDlg::OnBnClickedButScratches()
{
	How_To_Run_Scratch_Matching ();
}

void CMasterOneDlg::OnBnClickedButMissingPads()
{
	How_To_Run_Missing_Pads ();
}

void CMasterOneDlg::OnBnClickedButFwmLoad()
{
	static CString mInit_Dir = _T("E:/Synapse/Data/Narrow Pattern/367/");

	TCHAR mStr_Filter[] = _T("Img Files (*.tif)|*.tif|All Files (*.*)|*.*||");
	CFileDialog mFileDlg (TRUE, _T(".tif"), NULL, OFN_OVERWRITEPROMPT, mStr_Filter);
	mFileDlg.m_ofn.lpstrInitialDir = mInit_Dir;
	if (mFileDlg.DoModal () == IDOK)
	{
		CString mRet_File = mFileDlg.GetPathName ();

		int pos = mRet_File.ReverseFind ('\\');
		m_folderPath = mRet_File.Left (pos);
		CString_2_HTuple(m_folderPath, &t_folderPath);

		// ¬©¬Ñ¬Ô¬â¬å¬Ù¬Ú¬Þ ¬Ú¬Ù¬à¬Ò¬â¬Ñ¬Ø¬Ö¬ß¬Ú¬ñ
		m_FWM->m_pIm.ReadImage (t_folderPath + "\\Im.tif");
		m_FWM->m_pImIRB.ReadImage (t_folderPath + "\\ImIRBo.tif");
		m_FWM->m_pImCLC.ReadImage (t_folderPath + "\\ImCLC.tif");
		m_FWM->m_pImIRBS.ReadImage (t_folderPath + "\\ImIRBS.tif");

		// ¬©¬Ñ¬Ô¬â¬å¬Ù¬Ú¬Þ BIN ¬Õ¬Ñ¬ß¬ß¬í¬Ö ¬ã¬Ö¬ß¬ã¬à¬â¬à¬Ó
		int tuple_len;
		m_FWM->pP1x = Load_Tuple_Bin_F (m_folderPath, _T("X1"), &tuple_len);
		m_FWM->pP1y = Load_Tuple_Bin_F (m_folderPath, _T("Y1"), &tuple_len);
		m_FWM->pP2x = Load_Tuple_Bin_F (m_folderPath, _T("X2"), &tuple_len);
		m_FWM->pP2y = Load_Tuple_Bin_F (m_folderPath, _T("Y2"), &tuple_len);
		//m_FWM->pP3x = Load_Tuple_Bin_F (m_folderPath, _T("XC"), &tuple_len);
		//m_FWM->pP3y = Load_Tuple_Bin_F (m_folderPath, _T("YC"), &tuple_len);
		m_FWM->m_tuple_len = tuple_len;

		m_FWM->pPnum = Load_Tuple_Bin_I (m_folderPath, _T("Pnum"), &tuple_len);
		m_FWM->pPaddrR = Load_Tuple_Bin_I (m_folderPath, _T("PaddrR"), &tuple_len);
		m_FWM->mmNa = tuple_len;
		m_FWM->pPaddrC = Load_Tuple_Bin_I (m_folderPath, _T("PaddrC"), &tuple_len);
		m_FWM->mmNaC = tuple_len;
		m_FWM->pWG = Load_Tuple_Bin_I (m_folderPath, _T("WG"), &tuple_len);

		// -----------------------------
		ReadRegion(&m_FWM->ho_SkelsEPUver, t_folderPath + "\\CircsAPver.hobj");
		ReadRegion(&m_FWM->ho_Rd, t_folderPath + "\\Rd.hobj");


		// ---------------------------------
		MessageBox (_T("Data loading completed"), _T("FWM"));

		But_FWM_Low_Slope.EnableWindow(false);
		But_FWM_Run.EnableWindow(true);
		But_FWM_Save.EnableWindow(false);
	}
}

void CMasterOneDlg::OnBnClickedButFwmRun()
{
	m_FWM->Proc ();
	MessageBox (_T("FWM - Proc completed"), _T("FWM"));

	m_FWM->PostProc ();
	MessageBox (_T("FWM - Post Proc completed"), _T("FWM"));

	But_FWM_Low_Slope.EnableWindow (true);
	But_FWM_Save.EnableWindow (true);
}

void CMasterOneDlg::OnBnClickedButFwmSave()
{
	CreateDirectory(m_folderPath + _T("\\Out"), NULL);

	HTuple dW ((float *)m_FWM->dW, m_FWM->m_tuple_len);
	WriteTuple (dW, t_folderPath + "\\Out\\dW.tup");

	HTuple dWmin ((float *)m_FWM->dWmin, m_FWM->m_tuple_len);
	WriteTuple (dWmin, t_folderPath + "\\Out\\dWmin.tup");

	HTuple dShift ((float *)m_FWM->dShift, m_FWM->m_tuple_len);
	WriteTuple (dShift, t_folderPath + "\\Out\\dShift.tup");

	HTuple dPint1x ((float *)m_FWM->dPint1x, m_FWM->m_tuple_len);
	WriteTuple (dPint1x, t_folderPath + "\\Out\\dPint1x.tup");

	HTuple dPint2x ((float *)m_FWM->dPint2x, m_FWM->m_tuple_len);
	WriteTuple (dPint2x, t_folderPath + "\\Out\\dPint2x.tup");

	HTuple dPint1y ((float *)m_FWM->dPint1y, m_FWM->m_tuple_len);
	WriteTuple (dPint1y, t_folderPath + "\\Out\\dPint1y.tup");

	HTuple dPint2y ((float *)m_FWM->dPint2y, m_FWM->m_tuple_len);
	WriteTuple (dPint2y, t_folderPath + "\\Out\\dPint2y.tup");

	HTuple dPuseint ((float *)m_FWM->dPuseint, m_FWM->m_tuple_len);
	WriteTuple (dPuseint, t_folderPath + "\\Out\\dPuseint.tup");


	CreateDirectory(m_folderPath + _T("\\PATTERN"), NULL);
	// if (m_FWM->mmSPnum > 0)
	{
		WriteObject(m_FWM->mmCircleSPs, t_folderPath + "\\PATTERN\\CircleSPcc.hobj");
		WriteObject(m_FWM->mmRegSPs, t_folderPath + "\\PATTERN\\RegSPcc.hobj");
	}

	// if (m_FWM->mmMBnum > 0)
	{
		WriteObject(m_FWM->mmCircleMBs, t_folderPath + "\\PATTERN\\CircleMBcc.hobj");
		WriteObject(m_FWM->mmRegMBs, t_folderPath + "\\PATTERN\\RegMBcc.hobj");
	}

	// --- Missing ---
	WriteObject(m_FWM->mmCircleMISS, t_folderPath + "\\PATTERN\\CircleMISScc.hobj");
	WriteObject(m_FWM->mmRegMISS, t_folderPath + "\\PATTERN\\RegMISScc.hobj");


	MessageBox (_T("FWM - Save completed"), _T("FWM"));
}


void CMasterOneDlg::OnBnClickedButFwmLowSlope()
{
	//HTuple hv_Pnum, hv_pWG;
	//ReadTuple((LPCTSTR)(m_folderPath + _T("/Pnum.tup")), &hv_Pnum);
	//ReadTuple((LPCTSTR)(m_folderPath + _T("/WG.tup")), &hv_pWG);

	// We use the data from the algorithm FWM
	HTuple hv_dWmin((float*)m_FWM->dWmin, m_FWM->m_tuple_len);
	HTuple hv_Pnum((int*)m_FWM->pPnum, m_FWM->m_tuple_len);
	HTuple hv_pWG((int*)m_FWM->pWG, m_FWM->m_tuple_len);

	// Search Options
	HTuple move_avg_h = 30;
	HTuple min_len_direct = 10;
	HTuple threshold = 15;
	HTuple threshold_area = 10;

	// Estimated data
	std::vector<int64_t> m_finde_pos; // Position number
	std::vector<double> m_finde_val;

	// Algorithm implementations
	Filter_Line_Thickness_All(
		hv_Pnum,
		hv_pWG,
		hv_dWmin,
		move_avg_h,
		min_len_direct,
		threshold,
		threshold_area,
		&m_finde_pos,
		&m_finde_val);

	// Formation of thickening highlight regions
	HTuple hv_t_X = HTuple();
	HTuple hv_t_Y = HTuple();
	HTuple hv_cnt = 0;
	for (int v = 0; v < m_finde_pos.size(); v++)
	{
		int tuple_pos = m_finde_pos[v];
		hv_t_X[hv_cnt] = HTuple((m_FWM->pP1x[tuple_pos] + m_FWM->pP2x[tuple_pos]) / 2);
		hv_t_Y[hv_cnt] = HTuple((m_FWM->pP1y[tuple_pos] + m_FWM->pP2y[tuple_pos]) / 2);
		hv_cnt += 1;
	}

	HTuple hv_radius;
	HObject ho_mark_circle;
	TupleGenConst(hv_cnt, 5.0, &hv_radius);
	GenCircle(&ho_mark_circle, hv_t_Y, hv_t_X, hv_radius);
	// *** ho_mark_circle contains circles on the thickenings

	// Save the regions to check in Halkon
	TEST_CALL_1(WriteObject(ho_mark_circle, t_folderPath +"/Out/mark_circle"));
}
