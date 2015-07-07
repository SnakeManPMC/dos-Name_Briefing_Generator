LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
void InitializeApplication(HWND);
HINSTANCE hInstance;

char szAppname[60] = "Name Briefing Generator v1.0";
char szClassname[9] = "NBG";

#define MAX_CAMPAIGNS 50
#define MAX_MISSIONS 50

#define ID_RADSIDEBLUFOR 			5000
#define ID_RADSIDEOPFOR 			5001
#define ID_RADSIDECIVILIAN			5002
#define ID_RADSIDEINDEPENDENT		5003
#define ID_CHECKMISSIONASSAULT		5004
#define ID_CHECKMISSIONDEFEND		5005

#define ID_DROPCAMPAIGNNAME			5006
#define ID_DROPMISSIONNAME			5007
#define ID_EDITBRIEFINGPREVIEW		5008
#define ID_BUTTONGENERATEBRIEFING	5009
#define ID_BUTTONSAVEBRIEFING		5010
#define ID_BUTTONQUITPROGRAM		5011

#define ID_STATICCAMPAIGNNAME		5012
#define ID_STATICMISSIONNAME		5013
#define ID_STATICSIDE				5014
#define ID_STATICMISSIONTYPE		5015
#define ID_STATICBRIEFINGPREVIEW	5016
