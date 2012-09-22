/*
 * Written by EiNSTeiN_
 * 		http://archos.g3nius.org/
 *
 * Released under the GNU General Public License v2
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
*/

#ifndef __MPK_H
#define __MPK_H

#include <stdint.h>

#include "keys.h"

#define MPK_DEVICE_A5			0
#define MPK_DEVICE_A5IT		1
#define MPK_DEVICE_A3GP		2
#define MPK_DEVICE_G9A			3
#define MPK_KNOWN_DEVICES		4 // number of keys in each array

static unsigned char *AES_Keys[] = {
	A5_AES,
	A5IT_AES,
	A3GP_AES,
	G9A_AES
};

static unsigned char *Bootloader_Keys[] = {
	A5_BOOTLOADER,
	A5IT_BOOTLOADER,
	A3GP_BOOTLOADER,
	G9A_BOOTLOADER
};

static unsigned char *Rel_Keys[] = {
	A5_RELMPK,
	A5IT_RELMPK,
	A3GP_RELMPK,
	G9A_RELMPK
};

static unsigned char *Dev_Keys[] = {
	A5_DEVMPK,
	A5IT_DEVMPK,
	A3GP_DEVMPK,
	G9A_DEVMPK
};

static unsigned char *Plug_Keys[] = {
	A5_PLUGMPK,
	A5IT_PLUGMPK,
	A3GP_PLUGMPK,
	G9A_PLUGMPK
};

static unsigned char *HDD_Keys[] = {
	A5_HDDMPK,
	A5IT_HDDMPK,
	A3GP_HDDMPK,
	G9A_HDDMPK
};

static unsigned char *Games_Keys[] = {
	A5_GAMESMPK,
	A5IT_GAMESMPK,
	A3GP_GAMESMPK,
};

unsigned char **mpk_possible_aos_keys(uint32_t sign_type);
unsigned char **mpk_possible_bootloader_keys();
unsigned char **mpk_possible_aes_keys();

const char *mpk_device_type(int device);
const char *mpk_signature_name(uint32_t sign_type);

#endif /* __MPK_H */
