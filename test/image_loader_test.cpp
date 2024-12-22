#include <cstdio>
#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <irrlicht.h>
#include <IImage.h>
#include <IVideoDriver.h>

using namespace irr;

struct ImageDesc
{
	const char *name;
	video::ECOLOR_FORMAT format;
	std::vector<u8> data;
};

template <typename T>
std::vector<u8> to_byte_array(std::initializer_list<T> in_data)
{
	std::vector<u8> data;
	data.resize(sizeof(T) * in_data.size());
	memcpy(data.data(), in_data.begin(), data.size());
	return data;
}

static const ImageDesc test_images[] = {
	{"16color-16bpp", video::ECF_A1R5G5B5, to_byte_array<u16>({
		0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xc23f, 0xc23f, 0xd61f, 0xd61f, 0xea3f, 0xea3f, 0xfe5e, 0xfe5e, 0xfe7c, 0xfe7a, 0xfe7a, 0xfe97, 0xfeb5, 0xfeb5, 0xff16,
		0xb6df, 0xb6df, 0xff3f, 0xff3f, 0xc23f, 0xf2df, 0xf2df, 0xf2df, 0xea3f, 0xda7f, 0xda7f, 0xfe5e, 0xfe7a, 0xc23f, 0xbe7f, 0xbe7f, 0xfeb5, 0xfeb5, 0xfb76,
		0xb6df, 0xff9e, 0xc23f, 0xc23f, 0xc23f, 0xf2df, 0xd61f, 0xf2df, 0xea3f, 0xda7f, 0xfe5e, 0xda7f, 0xfe7a, 0xc23f, 0xfe97, 0xfeb5, 0xfeb5, 0xff16, 0xfb76,
		0xb6df, 0xff9e, 0xbe7f, 0xc23f, 0xd61f, 0xfe7c, 0xd61f, 0xf2df, 0xfe5e, 0xf2df, 0xfe7c, 0xda7f, 0xfe7a, 0xda7f, 0xbe7f, 0xfeb5, 0xff16, 0xff16, 0xfb76,
		0xb6df, 0xff9e, 0xc23f, 0xc23f, 0xd61f, 0xff3f, 0xd61f, 0xf2df, 0xfe5e, 0xda7f, 0xfe7c, 0xda7f, 0xfe7a, 0xc23f, 0xfeb5, 0xfeb5, 0xff16, 0xff16, 0xfb76,
		0xb6df, 0xbe7f, 0xff9e, 0xff3f, 0xd61f, 0xff3f, 0xf2df, 0xf2df, 0xfe5e, 0xf2df, 0xda7f, 0xfe97, 0xfe97, 0xda7f, 0xc23f, 0xda7f, 0xfb76, 0xfb76, 0xfb76,
		0xbe7f, 0xc23f, 0xc23f, 0xd61f, 0xd61f, 0xea3f, 0xea3f, 0xfe5e, 0xfe5e, 0xfe7c, 0xfe7c, 0xfe7a, 0xfe97, 0xfeb5, 0xfeb5, 0xfeb5, 0xfb76, 0xfb76, 0xfb76,
		0xbe7f, 0xc23f, 0xd61f, 0xd61f, 0xd61f, 0xea3f, 0xea3f, 0xfe5e, 0xfe5e, 0xfe7c, 0xfe97, 0xfe97, 0xfe97, 0xfeb5, 0xff16, 0xff16, 0xfb76, 0xfb76, 0xfb76,
		0xc23f, 0xff9e, 0xc23f, 0xd61f, 0xff3f, 0xea3f, 0xfe5e, 0xff3f, 0xfe7c, 0xfe7c, 0xf2df, 0xfe97, 0xfeb5, 0xfeb5, 0xda7f, 0xff16, 0xc23f, 0xc23f, 0xbe7f,
		0xc23f, 0xff9e, 0xff9e, 0xd61f, 0xff9e, 0xea3f, 0xff3f, 0xfe5e, 0xff3f, 0xfe7a, 0xf2df, 0xf2df, 0xfeb5, 0xf2df, 0xda7f, 0xfb76, 0xc23f, 0xfb76, 0xfb76,
		0xc23f, 0xff9e, 0xd61f, 0xff9e, 0xff9e, 0xfe5e, 0xff3f, 0xff3f, 0xff3f, 0xfe7a, 0xff3f, 0xfeb5, 0xf2df, 0xff16, 0xda7f, 0xfb76, 0xda7f, 0xda7f, 0xfb76,
		0xc23f, 0xff9e, 0xea3f, 0xea3f, 0xff9e, 0xfe5e, 0xff9e, 0xfe7c, 0xff3f, 0xfe97, 0xf2df, 0xfeb5, 0xfeb5, 0xff16, 0xf2df, 0xfb76, 0xda7f, 0xfb76, 0xfb76,
		0xd61f, 0xff9e, 0xd61f, 0xea3f, 0xff9e, 0xfe5e, 0xff9e, 0xfe7c, 0xff3f, 0xfe97, 0xff3f, 0xfeb5, 0xff16, 0xfb76, 0xda7f, 0xfb76, 0xda7f, 0xda7f, 0xc23f,
		0xd61f, 0xd61f, 0xea3f, 0xea3f, 0xea3f, 0xfe5e, 0xfe7c, 0xfe7a, 0xfe7a, 0xfe97, 0xfeb5, 0xff16, 0xff16, 0xfb76, 0xfb76, 0xfb76, 0xfb76, 0xfb76, 0xfb76,
		0xd61f, 0xd61f, 0xea3f, 0xfe5e, 0xfe5e, 0xfe7c, 0xfe7a, 0xfe7a, 0xfe97, 0xfeb5, 0xfeb5, 0xff16, 0xff16, 0xfb76, 0xfb76, 0xfb76, 0xfb76, 0xfb76, 0xfb76,
	})},

	{"30color-16bpp", video::ECF_A1R5G5B5, to_byte_array<u16>({
		0xbabf, 0xbabf, 0xbabf, 0xbabf, 0xbe3f, 0xbdff, 0xc9ff, 0xda1f, 0xee3f, 0xee3f, 0xfa5f, 0xfe5e, 0xfe7c, 0xfe7b, 0xfe79, 0xfe97, 0xfeb5, 0xfed5, 0xff16,
		0xbabf, 0xbabf, 0xff1f, 0xff1f, 0xbdff, 0xfaff, 0xf2df, 0xeabf, 0xee3f, 0xe27f, 0xda7f, 0xfe5e, 0xfe7b, 0xc25f, 0xbe7f, 0xbe7f, 0xfeb5, 0xfed5, 0xff56,
		0xbabf, 0xff7e, 0xbe7f, 0xc25f, 0xbdff, 0xfaff, 0xda1f, 0xf2df, 0xee3f, 0xda7f, 0xfe5e, 0xce5f, 0xfe79, 0xce5f, 0xfe97, 0xfeb5, 0xfed5, 0xff16, 0xff56,
		0xbabf, 0xff7e, 0xbe7f, 0xbdff, 0xc9ff, 0xfaff, 0xda1f, 0xf2df, 0xfa5f, 0xeabf, 0xfe5e, 0xda7f, 0xfe79, 0xce5f, 0xc25f, 0xfeb5, 0xff16, 0xff16, 0xff76,
		0xbabf, 0xff7e, 0xc25f, 0xbdff, 0xc9ff, 0xff1f, 0xda1f, 0xf2df, 0xfa5f, 0xeabf, 0xfe7c, 0xda7f, 0xfe79, 0xce5f, 0xfeb5, 0xfed5, 0xff16, 0xff56, 0xff97,
		0xbabf, 0xbe7f, 0xff7e, 0xff5e, 0xda1f, 0xff1f, 0xfaff, 0xfaff, 0xfa5f, 0xf2df, 0xeabf, 0xfe79, 0xfe97, 0xda7f, 0xce5f, 0xce5f, 0xff56, 0xff76, 0xff97,
		0xbe7f, 0xc25f, 0xbdff, 0xc9ff, 0xda1f, 0xda1f, 0xee3f, 0xfa5f, 0xfa5f, 0xfe7c, 0xfe7b, 0xfe79, 0xfe97, 0xfeb5, 0xfed5, 0xfed5, 0xff76, 0xff76, 0xff97,
		0xbe7f, 0xbe3f, 0xc9ff, 0xc9ff, 0xda1f, 0xee3f, 0xee3f, 0xfa5f, 0xfe5e, 0xfe7c, 0xfe79, 0xfe97, 0xfe97, 0xfeb5, 0xff16, 0xff16, 0xff76, 0xff97, 0xff97,
		0xbe3f, 0xffbe, 0xc9ff, 0xda1f, 0xff5e, 0xee3f, 0xfa5f, 0xff1f, 0xfe7c, 0xfe7b, 0xf2df, 0xfe97, 0xfeb5, 0xfeb5, 0xda7f, 0xff76, 0xce5f, 0xbe3f, 0xc25f,
		0xbe3f, 0xffbe, 0xffbe, 0xda1f, 0xff7e, 0xfa5f, 0xff5e, 0xfe5e, 0xff1f, 0xfe79, 0xf2df, 0xf2df, 0xfeb5, 0xeabf, 0xda7f, 0xff76, 0xce5f, 0xff97, 0xff97,
		0xbdff, 0xffbe, 0xda1f, 0xff7e, 0xff7e, 0xfa5f, 0xff5e, 0xff1f, 0xff1f, 0xfe79, 0xfaff, 0xfeb5, 0xf2df, 0xff16, 0xe27f, 0xff97, 0xda7f, 0xce5f, 0xff97,
		0xbdff, 0xffbe, 0xda1f, 0xee3f, 0xffbe, 0xfa5f, 0xff7e, 0xfe7b, 0xff1f, 0xfe97, 0xfaff, 0xfeb5, 0xfed5, 0xff56, 0xeabf, 0xff97, 0xda7f, 0xff97, 0xff97,
		0xc9ff, 0xffbe, 0xda1f, 0xee3f, 0xff7e, 0xfa5f, 0xff7e, 0xfe7c, 0xff5e, 0xfe97, 0xfaff, 0xfed5, 0xff16, 0xff56, 0xeabf, 0xff97, 0xda7f, 0xda7f, 0xce5f,
		0xda1f, 0xda1f, 0xee3f, 0xee3f, 0xfa5f, 0xfe5e, 0xfe7c, 0xfe79, 0xfe79, 0xfe97, 0xfeb5, 0xfed5, 0xff16, 0xff56, 0xff97, 0xff97, 0xff97, 0xff97, 0xff97,
		0xda1f, 0xda1f, 0xee3f, 0xfa5f, 0xfe5e, 0xfe7c, 0xfe7b, 0xfe79, 0xfe97, 0xfeb5, 0xfed5, 0xff16, 0xff56, 0xff97, 0xff97, 0xff97, 0xff97, 0xff97, 0xff97,
	})},

	{"30color-24bpp", video::ECF_R8G8B8, {
		0x71, 0xaf, 0xff, 0x71, 0xaf, 0xff, 0x71, 0xaf, 0xff, 0x71, 0xaf, 0xff, 0x7b, 0x8b, 0xff, 0x7a, 0x7f, 0xff, 0x90, 0x7f, 0xff, 0xb6, 0x85, 0xff, 0xd9, 0x8c, 0xff, 0xd9, 0x8c, 0xff, 0xf4, 0x92, 0xfe, 0xfe, 0x96, 0xf0, 0xfd, 0x99, 0xe3, 0xfd, 0x9b, 0xda, 0xfc, 0x9f, 0xca, 0xfc, 0xa4, 0xbc, 0xfb, 0xa9, 0xab, 0xfa, 0xb6, 0xad, 0xf9, 0xc6, 0xb1,
		0x71, 0xaf, 0xff, 0x71, 0xaf, 0xff, 0xff, 0xc6, 0xfc, 0xff, 0xc6, 0xfc, 0x7a, 0x7f, 0xff, 0xf7, 0xbe, 0xff, 0xe4, 0xb2, 0xfe, 0xd4, 0xa9, 0xff, 0xd9, 0x8c, 0xff, 0xc3, 0x98, 0xff, 0xb2, 0x9a, 0xff, 0xfe, 0x96, 0xf0, 0xfd, 0x9b, 0xda, 0x86, 0x93, 0xfe, 0x78, 0x9b, 0xff, 0x78, 0x9b, 0xff, 0xfb, 0xa9, 0xab, 0xfa, 0xb6, 0xad, 0xf8, 0xd2, 0xb3,
		0x71, 0xaf, 0xff, 0xfe, 0xdc, 0xf3, 0x78, 0x9b, 0xff, 0x86, 0x93, 0xfe, 0x7a, 0x7f, 0xff, 0xf7, 0xbe, 0xff, 0xb6, 0x85, 0xff, 0xe4, 0xb2, 0xfe, 0xd9, 0x8c, 0xff, 0xb2, 0x9a, 0xff, 0xfe, 0x96, 0xf0, 0x9a, 0x91, 0xff, 0xfc, 0x9f, 0xca, 0x9a, 0x91, 0xff, 0xfc, 0xa4, 0xbc, 0xfb, 0xa9, 0xab, 0xfa, 0xb6, 0xad, 0xf9, 0xc6, 0xb1, 0xf8, 0xd2, 0xb3,
		0x71, 0xaf, 0xff, 0xfe, 0xdc, 0xf3, 0x78, 0x9b, 0xff, 0x7a, 0x7f, 0xff, 0x90, 0x7f, 0xff, 0xf7, 0xbe, 0xff, 0xb6, 0x85, 0xff, 0xe4, 0xb2, 0xfe, 0xf4, 0x92, 0xfe, 0xd4, 0xa9, 0xff, 0xfe, 0x96, 0xf0, 0xb2, 0x9a, 0xff, 0xfc, 0x9f, 0xca, 0x9a, 0x91, 0xff, 0x86, 0x93, 0xfe, 0xfb, 0xa9, 0xab, 0xf9, 0xc6, 0xb1, 0xf9, 0xc6, 0xb1, 0xf8, 0xd8, 0xb5,
		0x71, 0xaf, 0xff, 0xfe, 0xdc, 0xf3, 0x86, 0x93, 0xfe, 0x7a, 0x7f, 0xff, 0x90, 0x7f, 0xff, 0xff, 0xc6, 0xfc, 0xb6, 0x85, 0xff, 0xe4, 0xb2, 0xfe, 0xf4, 0x92, 0xfe, 0xd4, 0xa9, 0xff, 0xfd, 0x99, 0xe3, 0xb2, 0x9a, 0xff, 0xfc, 0x9f, 0xca, 0x9a, 0x91, 0xff, 0xfb, 0xa9, 0xab, 0xfa, 0xb6, 0xad, 0xf9, 0xc6, 0xb1, 0xf8, 0xd2, 0xb3, 0xf8, 0xe4, 0xb9,
		0x71, 0xaf, 0xff, 0x78, 0x9b, 0xff, 0xfe, 0xdc, 0xf3, 0xff, 0xd0, 0xf7, 0xb6, 0x85, 0xff, 0xff, 0xc6, 0xfc, 0xf7, 0xbe, 0xff, 0xf7, 0xbe, 0xff, 0xf4, 0x92, 0xfe, 0xe4, 0xb2, 0xfe, 0xd4, 0xa9, 0xff, 0xfc, 0x9f, 0xca, 0xfc, 0xa4, 0xbc, 0xb2, 0x9a, 0xff, 0x9a, 0x91, 0xff, 0x9a, 0x91, 0xff, 0xf8, 0xd2, 0xb3, 0xf8, 0xd8, 0xb5, 0xf8, 0xe4, 0xb9,
		0x78, 0x9b, 0xff, 0x86, 0x93, 0xfe, 0x7a, 0x7f, 0xff, 0x90, 0x7f, 0xff, 0xb6, 0x85, 0xff, 0xb6, 0x85, 0xff, 0xd9, 0x8c, 0xff, 0xf4, 0x92, 0xfe, 0xf4, 0x92, 0xfe, 0xfd, 0x99, 0xe3, 0xfd, 0x9b, 0xda, 0xfc, 0x9f, 0xca, 0xfc, 0xa4, 0xbc, 0xfb, 0xa9, 0xab, 0xfa, 0xb6, 0xad, 0xfa, 0xb6, 0xad, 0xf8, 0xd8, 0xb5, 0xf8, 0xd8, 0xb5, 0xf8, 0xe4, 0xb9,
		0x78, 0x9b, 0xff, 0x7b, 0x8b, 0xff, 0x90, 0x7f, 0xff, 0x90, 0x7f, 0xff, 0xb6, 0x85, 0xff, 0xd9, 0x8c, 0xff, 0xd9, 0x8c, 0xff, 0xf4, 0x92, 0xfe, 0xfe, 0x96, 0xf0, 0xfd, 0x99, 0xe3, 0xfc, 0x9f, 0xca, 0xfc, 0xa4, 0xbc, 0xfc, 0xa4, 0xbc, 0xfb, 0xa9, 0xab, 0xf9, 0xc6, 0xb1, 0xf9, 0xc6, 0xb1, 0xf8, 0xd8, 0xb5, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9,
		0x7b, 0x8b, 0xff, 0xff, 0xeb, 0xf2, 0x90, 0x7f, 0xff, 0xb6, 0x85, 0xff, 0xff, 0xd0, 0xf7, 0xd9, 0x8c, 0xff, 0xf4, 0x92, 0xfe, 0xff, 0xc6, 0xfc, 0xfd, 0x99, 0xe3, 0xfd, 0x9b, 0xda, 0xe4, 0xb2, 0xfe, 0xfc, 0xa4, 0xbc, 0xfb, 0xa9, 0xab, 0xfb, 0xa9, 0xab, 0xb2, 0x9a, 0xff, 0xf8, 0xd8, 0xb5, 0x9a, 0x91, 0xff, 0x7b, 0x8b, 0xff, 0x86, 0x93, 0xfe,
		0x7b, 0x8b, 0xff, 0xff, 0xeb, 0xf2, 0xff, 0xeb, 0xf2, 0xb6, 0x85, 0xff, 0xfe, 0xdc, 0xf3, 0xf4, 0x92, 0xfe, 0xff, 0xd0, 0xf7, 0xfe, 0x96, 0xf0, 0xff, 0xc6, 0xfc, 0xfc, 0x9f, 0xca, 0xe4, 0xb2, 0xfe, 0xe4, 0xb2, 0xfe, 0xfb, 0xa9, 0xab, 0xd4, 0xa9, 0xff, 0xb2, 0x9a, 0xff, 0xf8, 0xd8, 0xb5, 0x9a, 0x91, 0xff, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9,
		0x7a, 0x7f, 0xff, 0xff, 0xeb, 0xf2, 0xb6, 0x85, 0xff, 0xfe, 0xdc, 0xf3, 0xfe, 0xdc, 0xf3, 0xf4, 0x92, 0xfe, 0xff, 0xd0, 0xf7, 0xff, 0xc6, 0xfc, 0xff, 0xc6, 0xfc, 0xfc, 0x9f, 0xca, 0xf7, 0xbe, 0xff, 0xfb, 0xa9, 0xab, 0xe4, 0xb2, 0xfe, 0xf9, 0xc6, 0xb1, 0xc3, 0x98, 0xff, 0xf8, 0xe4, 0xb9, 0xb2, 0x9a, 0xff, 0x9a, 0x91, 0xff, 0xf8, 0xe4, 0xb9,
		0x7a, 0x7f, 0xff, 0xff, 0xeb, 0xf2, 0xb6, 0x85, 0xff, 0xd9, 0x8c, 0xff, 0xff, 0xeb, 0xf2, 0xf4, 0x92, 0xfe, 0xfe, 0xdc, 0xf3, 0xfd, 0x9b, 0xda, 0xff, 0xc6, 0xfc, 0xfc, 0xa4, 0xbc, 0xf7, 0xbe, 0xff, 0xfb, 0xa9, 0xab, 0xfa, 0xb6, 0xad, 0xf8, 0xd2, 0xb3, 0xd4, 0xa9, 0xff, 0xf8, 0xe4, 0xb9, 0xb2, 0x9a, 0xff, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9,
		0x90, 0x7f, 0xff, 0xff, 0xeb, 0xf2, 0xb6, 0x85, 0xff, 0xd9, 0x8c, 0xff, 0xfe, 0xdc, 0xf3, 0xf4, 0x92, 0xfe, 0xfe, 0xdc, 0xf3, 0xfd, 0x99, 0xe3, 0xff, 0xd0, 0xf7, 0xfc, 0xa4, 0xbc, 0xf7, 0xbe, 0xff, 0xfa, 0xb6, 0xad, 0xf9, 0xc6, 0xb1, 0xf8, 0xd2, 0xb3, 0xd4, 0xa9, 0xff, 0xf8, 0xe4, 0xb9, 0xb2, 0x9a, 0xff, 0xb2, 0x9a, 0xff, 0x9a, 0x91, 0xff,
		0xb6, 0x85, 0xff, 0xb6, 0x85, 0xff, 0xd9, 0x8c, 0xff, 0xd9, 0x8c, 0xff, 0xf4, 0x92, 0xfe, 0xfe, 0x96, 0xf0, 0xfd, 0x99, 0xe3, 0xfc, 0x9f, 0xca, 0xfc, 0x9f, 0xca, 0xfc, 0xa4, 0xbc, 0xfb, 0xa9, 0xab, 0xfa, 0xb6, 0xad, 0xf9, 0xc6, 0xb1, 0xf8, 0xd2, 0xb3, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9,
		0xb6, 0x85, 0xff, 0xb6, 0x85, 0xff, 0xd9, 0x8c, 0xff, 0xf4, 0x92, 0xfe, 0xfe, 0x96, 0xf0, 0xfd, 0x99, 0xe3, 0xfd, 0x9b, 0xda, 0xfc, 0x9f, 0xca, 0xfc, 0xa4, 0xbc, 0xfb, 0xa9, 0xab, 0xfa, 0xb6, 0xad, 0xf9, 0xc6, 0xb1, 0xf8, 0xd2, 0xb3, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9, 0xf8, 0xe4, 0xb9,
	}},

	{"30color-32bpp", video::ECF_A8R8G8B8, to_byte_array<u32>({
		0xff71afff, 0xff71afff, 0xff71afff, 0xff71afff, 0xff7b8bff, 0xff7a7fff, 0xff907fff, 0xffb685ff, 0xffd98cff, 0xffd98cff, 0xfff492fe, 0xfffe96f0, 0xfffd99e3, 0xfffd9bda, 0xfffc9fca, 0xfffca4bc, 0xfffba9ab, 0xfffab6ad, 0xfff9c6b1,
		0xff71afff, 0xff71afff, 0xffffc6fc, 0xffffc6fc, 0xff7a7fff, 0xfff7beff, 0xffe4b2fe, 0xffd4a9ff, 0xffd98cff, 0xffc398ff, 0xffb29aff, 0xfffe96f0, 0xfffd9bda, 0xff8693fe, 0xff789bff, 0xff789bff, 0xfffba9ab, 0xfffab6ad, 0xfff8d2b3,
		0xff71afff, 0xfffedcf3, 0xff789bff, 0xff8693fe, 0xff7a7fff, 0xfff7beff, 0xffb685ff, 0xffe4b2fe, 0xffd98cff, 0xffb29aff, 0xfffe96f0, 0xff9a91ff, 0xfffc9fca, 0xff9a91ff, 0xfffca4bc, 0xfffba9ab, 0xfffab6ad, 0xfff9c6b1, 0xfff8d2b3,
		0xff71afff, 0xfffedcf3, 0xff789bff, 0xff7a7fff, 0xff907fff, 0xfff7beff, 0xffb685ff, 0xffe4b2fe, 0xfff492fe, 0xffd4a9ff, 0xfffe96f0, 0xffb29aff, 0xfffc9fca, 0xff9a91ff, 0xff8693fe, 0xfffba9ab, 0xfff9c6b1, 0xfff9c6b1, 0xfff8d8b5,
		0xff71afff, 0xfffedcf3, 0xff8693fe, 0xff7a7fff, 0xff907fff, 0xffffc6fc, 0xffb685ff, 0xffe4b2fe, 0xfff492fe, 0xffd4a9ff, 0xfffd99e3, 0xffb29aff, 0xfffc9fca, 0xff9a91ff, 0xfffba9ab, 0xfffab6ad, 0xfff9c6b1, 0xfff8d2b3, 0xfff8e4b9,
		0xff71afff, 0xff789bff, 0xfffedcf3, 0xffffd0f7, 0xffb685ff, 0xffffc6fc, 0xfff7beff, 0xfff7beff, 0xfff492fe, 0xffe4b2fe, 0xffd4a9ff, 0xfffc9fca, 0xfffca4bc, 0xffb29aff, 0xff9a91ff, 0xff9a91ff, 0xfff8d2b3, 0xfff8d8b5, 0xfff8e4b9,
		0xff789bff, 0xff8693fe, 0xff7a7fff, 0xff907fff, 0xffb685ff, 0xffb685ff, 0xffd98cff, 0xfff492fe, 0xfff492fe, 0xfffd99e3, 0xfffd9bda, 0xfffc9fca, 0xfffca4bc, 0xfffba9ab, 0xfffab6ad, 0xfffab6ad, 0xfff8d8b5, 0xfff8d8b5, 0xfff8e4b9,
		0xff789bff, 0xff7b8bff, 0xff907fff, 0xff907fff, 0xffb685ff, 0xffd98cff, 0xffd98cff, 0xfff492fe, 0xfffe96f0, 0xfffd99e3, 0xfffc9fca, 0xfffca4bc, 0xfffca4bc, 0xfffba9ab, 0xfff9c6b1, 0xfff9c6b1, 0xfff8d8b5, 0xfff8e4b9, 0xfff8e4b9,
		0xff7b8bff, 0xffffebf2, 0xff907fff, 0xffb685ff, 0xffffd0f7, 0xffd98cff, 0xfff492fe, 0xffffc6fc, 0xfffd99e3, 0xfffd9bda, 0xffe4b2fe, 0xfffca4bc, 0xfffba9ab, 0xfffba9ab, 0xffb29aff, 0xfff8d8b5, 0xff9a91ff, 0xff7b8bff, 0xff8693fe,
		0xff7b8bff, 0xffffebf2, 0xffffebf2, 0xffb685ff, 0xfffedcf3, 0xfff492fe, 0xffffd0f7, 0xfffe96f0, 0xffffc6fc, 0xfffc9fca, 0xffe4b2fe, 0xffe4b2fe, 0xfffba9ab, 0xffd4a9ff, 0xffb29aff, 0xfff8d8b5, 0xff9a91ff, 0xfff8e4b9, 0xfff8e4b9,
		0xff7a7fff, 0xffffebf2, 0xffb685ff, 0xfffedcf3, 0xfffedcf3, 0xfff492fe, 0xffffd0f7, 0xffffc6fc, 0xffffc6fc, 0xfffc9fca, 0xfff7beff, 0xfffba9ab, 0xffe4b2fe, 0xfff9c6b1, 0xffc398ff, 0xfff8e4b9, 0xffb29aff, 0xff9a91ff, 0xfff8e4b9,
		0xff7a7fff, 0xffffebf2, 0xffb685ff, 0xffd98cff, 0xffffebf2, 0xfff492fe, 0xfffedcf3, 0xfffd9bda, 0xffffc6fc, 0xfffca4bc, 0xfff7beff, 0xfffba9ab, 0xfffab6ad, 0xfff8d2b3, 0xffd4a9ff, 0xfff8e4b9, 0xffb29aff, 0xfff8e4b9, 0xfff8e4b9,
		0xff907fff, 0xffffebf2, 0xffb685ff, 0xffd98cff, 0xfffedcf3, 0xfff492fe, 0xfffedcf3, 0xfffd99e3, 0xffffd0f7, 0xfffca4bc, 0xfff7beff, 0xfffab6ad, 0xfff9c6b1, 0xfff8d2b3, 0xffd4a9ff, 0xfff8e4b9, 0xffb29aff, 0xffb29aff, 0xff9a91ff,
		0xffb685ff, 0xffb685ff, 0xffd98cff, 0xffd98cff, 0xfff492fe, 0xfffe96f0, 0xfffd99e3, 0xfffc9fca, 0xfffc9fca, 0xfffca4bc, 0xfffba9ab, 0xfffab6ad, 0xfff9c6b1, 0xfff8d2b3, 0xfff8e4b9, 0xfff8e4b9, 0xfff8e4b9, 0xfff8e4b9, 0xfff8e4b9,
		0xffb685ff, 0xffb685ff, 0xffd98cff, 0xfff492fe, 0xfffe96f0, 0xfffd99e3, 0xfffd9bda, 0xfffc9fca, 0xfffca4bc, 0xfffba9ab, 0xfffab6ad, 0xfff9c6b1, 0xfff8d2b3, 0xfff8e4b9, 0xfff8e4b9, 0xfff8e4b9, 0xfff8e4b9, 0xfff8e4b9, 0xfff8e4b9,
	})},

};

void printImageBytes(const video::IImage *img)
{
	const auto *data = (u8 *)img->getData();
	const auto w = img->getPitch();
	const auto h = img->getDimension().Height;
	for (int y = 0; y < h; y++) {
		for (int k = 0; k < w; k++) {
			std::printf("0x%02x, ", *data++);
		}
		std::printf("\n");
	}
}

int main(int argc, char *argv[])
try {
	if (argc != 3)
		throw std::runtime_error("Invalid arguments. Expected sample ID and image file name");

	const ImageDesc *sample = nullptr;
	for (auto &&image : test_images) {
		if (strcmp(argv[1], image.name) == 0)
			sample = &image;
	}
	if (!sample)
		throw std::runtime_error("Sample not found");

	SIrrlichtCreationParameters p;
	p.DriverType = video::EDT_NULL;
	p.WindowSize = core::dimension2du(640, 480);
	p.LoggingLevel = ELL_DEBUG;

	auto *device = createDeviceEx(p);
	if (!device)
		throw std::runtime_error("Failed to create device");

	auto *driver = device->getVideoDriver();

	auto *img = driver->createImageFromFile(argv[2]);
	if (!img)
		throw std::runtime_error("Failed to load image");

	if (img->getDimension() != core::dimension2du{19, 15})
		throw std::runtime_error("Wrong image dimensions");

	if (img->getColorFormat() != sample->format)
		throw std::runtime_error("Wrong image format");

	if (img->getImageDataSizeInBytes() != sample->data.size())
		throw std::logic_error("Image data size not equal to sample size");

	if (memcmp(img->getData(), sample->data.data(), sample->data.size()) != 0) {
		printImageBytes(img);
		throw std::runtime_error("Wrong image contents");
	}

	img->drop();
	device->drop();

	return 0;
} catch (const std::exception &e) {
	std::printf("Test failed: %s\n", e.what());
	return 1;
}
