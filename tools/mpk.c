/*
 * Written by EiNSTeiN_
 * 		http://archos.g3nius.org/
 * Enhanced by scholbert
 * Released under the GNU General Public License v2
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
*/

#include <stdint.h>

#include "../libaos/libaos.h"
#include "keys.h"
#include "mpk.h"

unsigned char **mpk_possible_aos_keys(uint32_t sign_type)
{
	switch(sign_type) {
		case AOS_TYPE_SIG0:	return Rel_Keys;
		case AOS_TYPE_SIG1:	return Dev_Keys;
		case AOS_TYPE_SIG2:	return Plug_Keys;
		case AOS_TYPE_SIG3:	return HDD_Keys;
		case AOS_TYPE_SIG4:	return Games_Keys;
	}
	return NULL;
}

const char *mpk_signature_name(uint32_t sign_type)
{
	switch(sign_type) {
		case AOS_TYPE_SIG0:	return "Release";
		case AOS_TYPE_SIG1:	return "Development";
		case AOS_TYPE_SIG2:	return "Plugin";
		case AOS_TYPE_SIG3:	return "HDD";
		case AOS_TYPE_SIG4:	return "Games";
	}
	return "Unknown";
}

unsigned char **mpk_possible_bootloader_keys()
{
	return Bootloader_Keys;
}

unsigned char **mpk_possible_aes_keys()
{
	return AES_Keys;
}

const char *mpk_device_type(int device)
{
	switch(device) {
	case MPK_DEVICE_A5:	return "Archos 5";
	case MPK_DEVICE_A5IT:	return "Archos 5 Internet Tablet with Android";
	case MPK_DEVICE_A3GP:	return "Archos 3G+ from SFR";
	case MPK_DEVICE_G8A:	return "Archos Gen8";
	case MPK_DEVICE_G8AV2:	return "Archos Gen8 V2";
	case MPK_DEVICE_G9A:	return "Archos Gen9";
	case MPK_DEVICE_G10A:	return "Archos Gen10";
	}
	
	return "Unknown";
}
