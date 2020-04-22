#include "stdafx.h"
#include "cApp.h"
#include "player.h"
#include "position.h"
#include <wx/log.h> 

#include <iostream>

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}


cApp::~cApp()
{
}

bool cApp::OnInit()
{
	m_frame1 = new cMain();
	m_frame1->Show();
	return true;
	
	
}