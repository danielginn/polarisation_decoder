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
	VRmImage* p_check_img = 0;


	VRmImageFormat target_format;

	target_format.m_width = 1280;
	target_format.m_height = 960;
	target_format.m_color_format = VRM_BGR_3X8;
	target_format.m_image_modifier = 0;

	sprintf(loadFileName1, "../Pictures/Flight Test 2/Raw/image_030a.png");
	sprintf(loadFileName2, "../Pictures/Flight Test 2/Raw/image_030b.png");
	sprintf(loadFileName3, "../Pictures/Flight Test 2/Raw/image_030c.png");
	sprintf(saveFileName1, "../Pictures/Flight Test 2/Converted/image_030a.png");
	sprintf(saveFileName2, "../Pictures/Flight Test 2/Converted/image_030b.png");
	sprintf(saveFileName3, "../Pictures/Flight Test 2/Converted/image_030c.png");

	// Load Images
	cout << "Loading Images" << endl;
	VRM_EXEC_AND_CHECK(VRmUsbCamLoadPNG(loadFileName1, &p_source_img1));
	VRM_EXEC_AND_CHECK(VRmUsbCamLoadPNG(loadFileName2, &p_source_img2));
	VRM_EXEC_AND_CHECK(VRmUsbCamLoadPNG(loadFileName3, &p_source_img3));

	cout << "Images loaded:\nWidth: " << p_source_img1->m_image_format.m_width << endl;
	cout << "Height: " << p_source_img1->m_image_format.m_height << endl;
	const char *source_color_format_str;
	if (!VRmUsbCamGetStringFromColorFormat(p_source_img1->m_image_format.m_color_format,&source_color_format_str))
		return 0;
	cout << "Format: " << source_color_format_str << endl;


	//Wrap target image
	VRM_EXEC_AND_CHECK(VRmUsbCamNewImage(&p_target_img1, target_format));
	VRM_EXEC_AND_CHECK(VRmUsbCamNewImage(&p_target_img2, target_format));
	VRM_EXEC_AND_CHECK(VRmUsbCamNewImage(&p_target_img3, target_format));


	VRmDWORD target_list;
	VRM_EXEC_AND_CHECK(VRmUsbCamGetTargetFormatListSize(&(p_source_img1->m_image_format), &target_list));
	cout << "Target Format list size: " << target_list << endl;
	cout << "Possible Target Formats:" << endl;
	VRmDWORD j;
	for (j=0;j<target_list;j++)
	{
		VRmImageFormat possible_format;
		const char *target_color_format_str;
		VRM_EXEC_AND_CHECK(VRmUsbCamGetTargetFormatListEntry(&(p_source_img1->m_image_format), j, &possible_format));
		VRM_EXEC_AND_CHECK(VRmUsbCamGetStringFromColorFormat(possible_format.m_color_format,&target_color_format_str));
		cout << target_color_format_str << endl;
	}

	// Target Image format
	cout << "Selected target format:" << endl;
	cout << "Width: " << p_target_img1->m_image_format.m_width << endl;
	cout << "Height: " << p_target_img1->m_image_format.m_height << endl;
	const char *target_color_format_str;
	if (!VRmUsbCamGetStringFromColorFormat(p_target_img1->m_image_format.m_color_format,&target_color_format_str))
		return 0;
	cout << "Format: " << target_color_format_str << endl << endl;

	cout << "Converting Images:" << endl;
	// Convert Images
	VRM_EXEC_AND_CHECK(VRmUsbCamConvertImage(p_source_img1,p_target_img1));
	VRM_EXEC_AND_CHECK(VRmUsbCamConvertImage(p_source_img2,p_target_img2));
	VRM_EXEC_AND_CHECK(VRmUsbCamConvertImage(p_source_img3,p_target_img3));

	cout << "Saving Images" << endl;
	// Save Images
	VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(saveFileName1, p_target_img1, 0));
	VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(saveFileName2, p_target_img2, 0));
	VRM_EXEC_AND_CHECK(VRmUsbCamSavePNG(saveFileName3, p_target_img3, 0));

	//Unlocking target wraps
	VRM_EXEC_AND_CHECK(VRmUsbCamFreeImage(&p_target_img1));
	VRM_EXEC_AND_CHECK(VRmUsbCamFreeImage(&p_target_img2));
	VRM_EXEC_AND_CHECK(VRmUsbCamFreeImage(&p_target_img3));
	
	cout << "Saved image was in file format: ";
	VRM_EXEC_AND_CHECK(VRmUsbCamLoadPNG(saveFileName1, &p_check_img));
	const char *check_color_format_str;
	if (!VRmUsbCamGetStringFromColorFormat(p_check_img->m_image_format.m_color_format,&check_color_format_str))
		return 0;
	cout << check_color_format_str << endl;

	return 0;
}