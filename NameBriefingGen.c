#include <windows.h>
#include <stdio.h>
#include "NameBriefingGen.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    MSG msg ;
    WNDCLASSEX wndclass ;

	/* Dialog location */
	const short xPosition = 320;
	const short yPosition = 240;

	/* Dialog size */
	const short xSize = 400;
	const short ySize = 450;

    wndclass.cbSize = sizeof (wndclass);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance ;
    wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) (COLOR_WINDOW+11);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szClassname;
    wndclass.hIconSm = LoadIcon (NULL, IDI_APPLICATION);

    RegisterClassEx (&wndclass);

    HWND hwnd = CreateWindow (szClassname,
        szAppname,
        WS_DLGFRAME|WS_SYSMENU|WS_EX_TOPMOST,
        xPosition,
        yPosition,
        xSize,
        ySize,
        NULL,
        NULL,
        hInstance,
        NULL) ;

    ShowWindow (hwnd, iCmdShow);

    while (GetMessage (&msg, NULL, 0, 0) == TRUE)
    {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }

    return msg.wParam;
}

/* INITIALIZE CONTROL AND APPLICATION DATA HERE ...  :D */
void InitializeApplication(HWND hwnd) {

	/*	Campaign names here, max length is 256,
		Maximum campaign amount defined in .h file */
	unsigned char CampaignName[MAX_CAMPAIGNS][256] = {
		"str1",
		"str2",
		"str3",
		"str4",
		"str5",
		"str6",
		"str7",
		"str8",
		"str9",
		"str10",
		"str11",
		"str12",
		"str13",
		"str14",
		"str15",
		"str16",
		"str17",
		"str18",
		0
	};

	/*	Mission names here. Max lenght 256,
		Max mission amount defined in .h file */
	unsigned char MissionName[MAX_MISSIONS][256] = {
		"str1",
		"str2",
		"str3",
		"str4",
		"str5",
		"str6",
		"str7",
		"str8",
		"str9",
		0
	};

	/* throw campaign names in Combobox */
	for(int i = 0 ; i < MAX_CAMPAIGNS; i++) {

		if( strlen(CampaignName[i]) > 0 ) {
			SendDlgItemMessage(hwnd, ID_DROPCAMPAIGNNAME, CB_ADDSTRING, (WPARAM)0, (LPARAM)CampaignName[i]);
		}
		else {
			break;
		}

	}

	/* throw mission names in Combobox */
	for(int i = 0 ; i < MAX_MISSIONS; i++) {

		if( strlen(MissionName[i]) > 0 ) {
			SendDlgItemMessage(hwnd, ID_DROPMISSIONNAME, CB_ADDSTRING, (WPARAM)0, (LPARAM)MissionName[i]);
		}
		else {
			break;
		}
	}

	SendDlgItemMessage(hwnd,ID_CHECKMISSIONASSAULT, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);

}

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HFONT hFont;
	static HWND hwndRadSideBluFor;
	static HWND hwndRadSideOpFor;
	static HWND hwndRadSideCivilian;
	static HWND hwndRadSideIndependent;
	static HWND hwndCheckMissionAssault;
	static HWND hwndCheckMissionDefend;

	static HWND hwndDropCampaignName;
	static HWND hwndDropMissionName;
	static HWND hwndEditBriefingPreview;
	static HWND hwndButtonGenerateBriefing;
	static HWND hwndButtonSaveBriefing;
	static HWND hwndButtonQuitProgram;

	static HWND hwndStaticCampaignName;
	static HWND hwndStaticMissionName;
	static HWND hwndStaticSide;
	static HWND hwndStaticMissionType;
	static HWND hwndStaticBriefingPreview;

    switch (iMsg)
    {
	    case WM_DESTROY:
    	    PostQuitMessage (0);
	        return 0;

		case WM_CREATE:

			hFont = GetStockObject(DEFAULT_GUI_FONT);

			hwndStaticCampaignName = CreateWindowEx(0, "static", "Campaign Name", WS_CHILD | WS_VISIBLE, 5, 5, 150, 20, hwnd, (HMENU)ID_STATICCAMPAIGNNAME, hInstance, NULL);
			SendMessage(hwndStaticCampaignName, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndDropCampaignName = CreateWindowEx(0, "COMBOBOX", "", WS_CHILD | WS_HSCROLL| WS_VSCROLL | WS_VISIBLE | CBS_DROPDOWN | CBS_SORT, 5, 23, 150, 150, hwnd, (HMENU)ID_DROPCAMPAIGNNAME, hInstance, NULL);
			SendMessage(hwndDropCampaignName, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndStaticMissionName = CreateWindowEx(0, "static", "Mission Name", WS_CHILD | WS_VISIBLE, 5, 60, 150, 20, hwnd, (HMENU)ID_STATICMISSIONNAME, hInstance, NULL);
			SendMessage(hwndStaticMissionName, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndDropMissionName = CreateWindowEx(0, "COMBOBOX", "", WS_CHILD | WS_HSCROLL| WS_VSCROLL | WS_VISIBLE | CBS_DROPDOWN | CBS_SORT, 5, 78, 150, 150, hwnd, (HMENU)ID_DROPMISSIONNAME, hInstance, NULL);
			SendMessage(hwndDropMissionName, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndStaticSide = CreateWindowEx(0, "static", "Side", WS_CHILD | WS_VISIBLE, 190, 5, 150, 20, hwnd, (HMENU)ID_STATICSIDE, hInstance, NULL);
			SendMessage(hwndStaticSide, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndRadSideBluFor = CreateWindowEx(0, "button", "BLUFOR", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 190, 25, 100, 20, hwnd, (HMENU)ID_RADSIDEBLUFOR, hInstance, NULL);
			SendMessage(hwndRadSideBluFor, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndRadSideOpFor = CreateWindowEx(0, "button", "OPFOR", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 190, 45, 100, 20, hwnd, (HMENU)ID_RADSIDEOPFOR, hInstance, NULL);
			SendMessage(hwndRadSideOpFor, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndRadSideCivilian = CreateWindowEx(0, "button", "Civilian", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 190, 65, 100, 20, hwnd, (HMENU)ID_RADSIDECIVILIAN, hInstance, NULL);
			SendMessage(hwndRadSideCivilian, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndRadSideIndependent = CreateWindowEx(0, "button", "Independent", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 190, 85, 100, 20, hwnd, (HMENU)ID_RADSIDEINDEPENDENT, hInstance, NULL);
			SendMessage(hwndRadSideIndependent, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndButtonSaveBriefing = CreateWindowEx(WS_EX_CLIENTEDGE, "button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 25, 80, 25, hwnd, (HMENU)ID_BUTTONSAVEBRIEFING, hInstance, NULL);
			SendMessage(hwndButtonSaveBriefing, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndButtonQuitProgram = CreateWindowEx(WS_EX_CLIENTEDGE, "button", "Quit", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 60, 80, 25, hwnd, (HMENU)ID_BUTTONQUITPROGRAM, hInstance, NULL);
			SendMessage(hwndButtonQuitProgram, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndButtonGenerateBriefing = CreateWindowEx(WS_EX_CLIENTEDGE, "button", "Generate Briefing", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 5, 140, 150, 25, hwnd, (HMENU)ID_BUTTONGENERATEBRIEFING, hInstance, NULL);
			SendMessage(hwndButtonGenerateBriefing, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndStaticBriefingPreview = CreateWindowEx(0, "static", "Briefing Preview", WS_CHILD | WS_VISIBLE, 5, 180, 150, 20, hwnd, (HMENU)ID_STATICBRIEFINGPREVIEW, hInstance, NULL);
			SendMessage(hwndStaticBriefingPreview, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndEditBriefingPreview = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE |ES_WANTRETURN, 5, 200, 383, 210, hwnd, (HMENU)ID_EDITBRIEFINGPREVIEW, hInstance, NULL);
			SendMessage(hwndEditBriefingPreview, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndStaticMissionType = CreateWindowEx(0, "static", "Mission Type", WS_CHILD | WS_VISIBLE, 190, 112, 150, 20, hwnd, (HMENU)ID_STATICMISSIONTYPE, hInstance, NULL);
			SendMessage(hwndStaticMissionType, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndCheckMissionAssault = CreateWindowEx(0, "button", "Assault", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 190, 130, 100, 20, hwnd, (HMENU)ID_CHECKMISSIONASSAULT, hInstance, NULL);
			SendMessage(hwndCheckMissionAssault, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			hwndCheckMissionDefend = CreateWindowEx(0, "button", "Defend", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 190, 148, 100, 20, hwnd, (HMENU)ID_CHECKMISSIONDEFEND, hInstance, NULL);
			SendMessage(hwndCheckMissionDefend, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE,0));

			InitializeApplication(hwnd);
			return 0;


		case WM_COMMAND:

			switch(LOWORD(wParam)){

				case ID_BUTTONGENERATEBRIEFING:
					return 0;

				case ID_BUTTONSAVEBRIEFING:
					return 0;

				case ID_BUTTONQUITPROGRAM:
						PostQuitMessage(0);
					return 0;

				case ID_CHECKMISSIONASSAULT:
					SendDlgItemMessage(hwnd, ID_CHECKMISSIONASSAULT, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
					SendDlgItemMessage(hwnd, ID_CHECKMISSIONDEFEND, BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);
					return 0;

				case ID_CHECKMISSIONDEFEND:
					SendDlgItemMessage(hwnd, ID_CHECKMISSIONDEFEND, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
					SendDlgItemMessage(hwnd, ID_CHECKMISSIONASSAULT, BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);
					return 0;

			}

		return(DefWindowProc(hwnd,iMsg,wParam,lParam));
	}

    return DefWindowProc (hwnd, iMsg, wParam, lParam);
}
