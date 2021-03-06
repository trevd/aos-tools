/*
 * Written by EiNSTeiN_
 * 		http://archos.g3nius.org/
 *
 * Released under the GNU General Public License v2
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
*/

#ifndef __LIBAOS_H
#define __LIBAOS_H

#include <stdint.h>

#include <openssl/rsa.h>
#include <openssl/aes.h>

/* Defines */

#define AOS_MAGIC				0x32534F41	// AOS2

// Signature blocks
#define AOS_TYPE_SIG0			0x30474953	// SIG0
#define AOS_TYPE_SIG1			0x31474953	// SIG1
#define AOS_TYPE_SIG2			0x32474953	// SIG2
#define AOS_TYPE_SIG3			0x33474953	// SIG3
#define AOS_TYPE_SIG4			0x34474953	// SIG4

// Header Blocks
#define AOS_TYPE_CIPHER		0x48504943	// CIPH
#define AOS_TYPE_UNIT			0x54494E55	// UNIT
#define AOS_TYPE_VERSION		0x53524556	// VERS
#define AOS_TYPE_DURATION		0x454d4954	// TIME

// Flash memory
#define AOS_TYPE_FLASH			0x48534c46	// FLSH
#define AOS_TYPE_MTD			0x4644544d	// MTDF

// File operations
#define AOS_TYPE_COPY			0x59504F43	// COPY
#define AOS_TYPE_DELETE		0x54454c44	// DLET
#define AOS_TYPE_MOVE			0x45564f4d	// MOVE
#define AOS_TYPE_SHELL			0x4c454853	// SHEL

// Boolean blocks
#define AOS_TYPE_BOOT			0x544f4f42	// BOOT
#define AOS_TYPE_ADEL			0x4c454441	// ADEL

// Unknown for now
#define AOS_TYPE_GULP			0x47554c50	// GULP
#define AOS_TYPE_FPAR			0x46504152	// FPAR
#define AOS_TYPE_PARM			0x5041524d	// PARM
#define AOS_TYPE_FRMT			0x46524d54	// FRMT
#define AOS_TYPE_PLUG			0x504c5547	// PLUG
#define AOS_TYPE_HDDL			0x4844444c	// HDDL
#define AOS_TYPE_MSGB			0x4d534742	// MSGB

#define AOS_SIGNATURE_LENGTH	128

// Block numbers for AOS2 mandatory blocks
#define AOS_SIGN_BLOCK_ID		0
#define AOS_CIPHER_BLOCK_ID	1
#define AOS_UNIT_BLOCK_ID		2
#define AOS_VERSION_BLOCK_ID	3
#define AOS_DURATION_BLOCK_ID	4

// Magic numbers for various AOS-related files
#define AOS_ZMfX_MAGIC		0x58664D5A // ZMfX
#define AOS_KERNEL_MAGIC		0xDAE589F0
#define AOS_CRAMFS_MAGIC		0xd3c284d5
#define AOS_CIPHER_MAGIC		0xBF959

#define AOS_GZIP_MAGIC			0x08088B1F
#define AOS_GZIP_NONAME_MAGIC	0x00088B1F
#define AOS_GZIP_NONAME_MASK	0x00ffffffff

/* Structures */

struct aos_block {
	uint32_t type;
	uint32_t length;
	uint8_t data[];
} __attribute__((packed));

struct aos_block_signature {
	uint8_t data[AOS_SIGNATURE_LENGTH];
} __attribute__((packed));

struct aos_block_cipher {
	uint32_t magic;
	uint8_t data[AES_BLOCK_SIZE];
} __attribute__((packed));

struct aos_block_unit {
	char product_name[16];
	char product_key[14];
} __attribute__((packed));

struct aos_block_version {
	uint32_t major;
	uint32_t minor;
	uint32_t build;
} __attribute__((packed));

struct aos_block_duration {
	uint32_t count;
	uint32_t time[100];
} __attribute__((packed));

struct aos_block_flash {
	uint32_t offset;
	uint32_t size;
	uint8_t data[];
} __attribute__((packed));

struct aos_block_mtd {
	uint8_t name[256];
	uint32_t offset;
	uint32_t size;
	uint8_t data[];
} __attribute__((packed));

struct aos_block_copy {
	uint32_t partition;
	uint8_t name[256];
	uint32_t size;
	uint8_t data[];
} __attribute__((packed));

#define AOS_PARTITION_SYSTEM	0
#define AOS_PARTITION_DATA		1
#define AOS_PARTITION_CRAMFS	2 // For .cramfs.secure files, on the A5IT only

struct aos_block_delete {
	uint32_t partition;
	uint8_t name[256];
} __attribute__((packed));

struct aos_block_boot {
	uint32_t value;
} __attribute__((packed));

struct aos_block_adel {
	uint32_t value;
} __attribute__((packed));

struct aos_block_shell {
	uint32_t length;
	uint8_t data[];
} __attribute__((packed));


struct aos_signature {
	uint8_t data[AOS_SIGNATURE_LENGTH];
	RSA *rsa;
} __attribute__((packed));

struct aos_encryption {
	AES_KEY key;
	uint8_t iv[AES_BLOCK_SIZE];
} __attribute__((packed));

struct aos_file {
	uint8_t *data;
	unsigned int length; // file length
} __attribute__((packed));

struct flash_header {
	uint32_t magic;
	uint32_t bits;
	uint8_t signature[AOS_SIGNATURE_LENGTH];
	uint32_t unk_88; // data is signed from here to eof
	uint32_t filesize; // size of the file: always populated
	uint32_t entrypoint; // address of the file's entry point: in boot1 this
						// is typically 0x87e80100, in cramfs files this is 0x100,
						// in init/recovery kernel this is not populated
	uint32_t cpio; // offset to the .cpio.gz file: populated only in init/recovery kernel
	uint32_t cpio_size; // size of the .cpio.gz file
	uint32_t unk_9C[25];
	uint8_t data[];
} __attribute__((packed));

struct flash_file {
	struct flash_header *header;
	unsigned int length; // file length
} __attribute__((packed));

/* AOS generic functions */

// Create an aos_file structure
struct aos_file *aos_create(uint8_t *data, unsigned int length);
void aos_free(struct aos_file *file);

// Return 0 if the magic is not AOS2
int aos_verify_magic(struct aos_file *file);

// Return 1 if the signature on the file is valid.
int aos_verify_signature(struct aos_file *file, const uint8_t *mpk_key);

// Return 1 if the aos file is encrypted.
int aos_is_encrypted(struct aos_file *file);

// Decrypt an encrypted aos file.
int aos_decrypt_file(struct aos_file *file, const uint8_t *aes_key);

// Encrypt a plain aos file.
int aos_encrypt_file(struct aos_file *file, const uint8_t *aes_key);

// Detect the key used to sign the aos file and return its index in *device.
int aos_detect_key(struct aos_file *file, uint8_t **keys, unsigned int n, int *device);

// Return 0 if the signature data is all zeroes.
int aos_is_signed(struct aos_file *file);

// Clear the signature from an aos file SIGN block.
int flash_clear_signature(struct flash_file *file);

/* FLASH partitions generic functions */

// Create a flash_file structure
struct flash_file *flash_create(uint8_t *data, unsigned int length);
void flash_free(struct flash_file *file);

// Return 1 if the signature on the flash partition is valid.
int flash_verify_signature(struct flash_file *file, const uint8_t *mpk_key);

// Detect the key used to sign the flash file and return its index in *device.
int flash_detect_key(struct flash_file *file, uint8_t **keys, unsigned int n, int *device);

// Return 0 if the signature data is all zeroes.
int flash_is_signed(struct flash_file *file);

// Clear the signature from a flash segment header
int flash_clear_signature(struct flash_file *file);

 /* Block functions for AOS files */

// return the first block in the file
struct aos_block *block_first(struct aos_file *file);

// Move the block pointer to the next block
struct aos_block *block_next(struct aos_file *file, struct aos_block *block);

// Return 0 if the block's length is longer than the size of the file
int block_is_valid(struct aos_file *file, struct aos_block *block);

// Get a block by its number.
struct aos_block *block_get(struct aos_file *file, int num);

// Return the offset of the current block, counting from the start 
// of the data buffer passed to aos_create()
unsigned int block_offset(struct aos_file *file, struct aos_block *block);

// Append a new block to the aos file
struct aos_block *aos_append_block(struct aos_file *file, uint32_t type, unsigned int length);
struct aos_block *aos_append_block_nopadding(struct aos_file *file, uint32_t type, unsigned int length);

/* Crypto functions */

// Parse the signature block and extract data from it.
int aos_signature_set_data(struct aos_signature *sign, const uint8_t *sig_data);

// Set the decryption key data.
int aos_signature_set_decrypt_key(struct aos_signature *sign, const uint8_t *mpk_data);

// Set the encryption key data.
int aos_signature_set_encrypt_key(struct aos_signature *sign, const uint8_t *mpk_data);

// Verify the signature of the file. 
int aos_signature_check(struct aos_signature *sign, const uint8_t *data, unsigned int length);

// Parse the encryption block and extract the iv from it.
int aos_cipher_set_iv(struct aos_encryption *enc, const uint8_t *iv);

// Set the aes key data. Data must be AOS_BLOCK_SIZE, or 16 bytes long.
int aos_cipher_set_key(struct aos_encryption *enc, const uint8_t *aes_data);

// Return the decrypted data from *in
uint8_t *aos_cipher_decrypt(struct aos_encryption *enc, const uint8_t *in, unsigned int length);

// Return the encrypted data from *in
uint8_t *aos_cipher_encrypt(struct aos_encryption *enc, const uint8_t *in, unsigned int length);

#endif /* __LIBAOS_H */
