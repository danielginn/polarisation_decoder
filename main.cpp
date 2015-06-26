// This program will decode the raw polarisation images saved during flight,
// and will calculate the orientation of the aircraft


using namespace std;

#include <vrmusbcam2.h>
#include <stdio.h>
#include <iostream>

#define VRM_EXEC_AND_CHECK(function)\
{\
	if (!function)\
	return 0;\
}

int main(int argc, char** argv)
{
	char loadFileName1[255];
	char loadFileName2[255];
	char loadFileName3[255];
	char saveFileName1[255];
	char saveFileName2[255];
	char saveFileName3[255];

	VRmImage* p_source_img1 = 0;
	VRmImage* p_source_img2 = 0;
	VRmImage* p_source_img3 = 0;
	VRmImage* p_target_img1 = 0;
	VRmImage* p_target_img2 = 0;
	VRmImage* p_target_img3 = 0;

	VRmImageFormat source_format;
	VRmImageFormat target_format;

	//source_format.m_width = 1280;
	//source_format.m_height = 960;
	//source_format.m_color_format = BAYER_GRGB_8;
	//source_format.m_image_modifier = 0;

	//target_format.m_width = 1280;
	//target_format.m_height = 960;
	//target_format.m_color_format = VRM_ARGB_4X8;
	//target_format.m_image_modifier = 0;

	int i = 0;
	sprintf(loadFileName1, "../Pictures/Flight Test 1/Raw/image_00%da.png",i);
	sprintf(loadFileName2, "../Pictures/Flight Test 1/Raw/image_00%db.png",i);
	sprintf(loadFileName3, "../Pictures/Flight Test 1/Raw/image_00%dc.png",i);
	sprintf(saveFileName1, "../Pictures/Flight Test 1/Converted/image_00%da.png",i);
	sprintf(saveFileName2, "../Pictures/Flight Test 1/Converted/image_00%db.png",i);
	sprintf(saveFileName3, "../Pictures/Flight Test 1/Converted/image_00%dc.png",i);

	// Load Images
	cout << "Loading Images" << endl;
	VRM_EXEC_AND_CHECK(VRmUsbCamLoadPNG(loadFileName1, &p_source_img1));
	VRM_EXEC_AND_CHECK(VRmUsbCamLoadPNG(loadFileName2, &p_source_img2));
	VRM_EXEC_AND_CHECK(VRmUsbCamLoadPNG(loadFileName3, &p_source_img3));

	cout << "Images loaded:\nWidth: " << p_source_img1->m_image_format.m_width << endl;
	cout << "Height: " << p_source_img1->m_image_format.m_height << endl;
	const char *target_color_format_str;
	if (!VRmUsbCamGetStringFromColorFormat(p_source_img1->m_image_format.m_color_format,&target_color_format_str))
		return 0;
	cout << "Format: " << target_color_format_str << endl;

	// Target Image format

	// Convert Images
	//VRM_EXEC_AND_CHECK(VRmUsbCamConvertImage(p_source_img1,p_target_img1));
	//VRM_EXEC_AND_CHECK(VRmUsbCamConvertImage(p_source_img2,p_target_img2));
	//VRM_EXEC_AND_CHECK(VRmUsbCamConvertImage(p_source_img3,p_target_img3));

	// Save Images
	//VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(saveFileName1, p_target_img1, 0));
	//VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(saveFileName2, p_target_img2, 0));
	//VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(saveFileName3, p_target_img3, 0));

	return 0;
}