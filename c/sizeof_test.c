#include <stdio.h>
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;
#define EMC_IMAGE_SIG_SIZE              256
#define EMC_IMAGE_KEY_SIZE              256
/// Image header field sizes
#define IMG_HEADER_SP_NAME_SIZE          32
#define IMG_HEADER_IMAGE_NAME_SIZE       16
#define IMG_HEADER_REV_STRING_SIZE       12
#define IMG_HEADER_DATE_TIME_STAMP_SIZE  24
#define IMG_HEADER_SPARE_SIZE            8
#define IMG_HEADER_RELOCATE_RECORD_SIZE  108
#define IMG_HEADER_RELOCATE_RECORD_MAX_ENTRY 9

#define IMG_HEADER_RELOCATE_RECORD_END_ADDRESS  0xFFFFFFF0
#define IMG_HEADER_SECURE_HDR_SIZE      (4096+256+256)
struct
reloc_record_t
{
       uint32_t address;               // RAM or ROM address
       uint32_t size;                  // in bytes
       uint32_t binary_file_offset;    // Offset within the binary file to pull the information
   } __attribute__((__packed__));
 // Certificate Header
 struct secure_header_t
 {
     uint8_t capsule_efi_guid[16];
     uint32_t header_size;
     uint32_t flags;
     uint32_t capsule_size;
     uint16_t rom_image_offset;
     uint16_t rom_layout_offset;
     struct
     {
         uint32_t win_length;
         uint16_t win_revision;
         uint16_t win_type;
         uint8_t win_efi_guid[16];
         uint8_t efi_guid[16];
         uint8_t public_key[EMC_IMAGE_KEY_SIZE];
         uint8_t signature[EMC_IMAGE_SIG_SIZE];
     } cert;
     struct
     {
         uint8_t efi_guid[16];
         uint8_t public_key[EMC_IMAGE_KEY_SIZE];
         uint8_t signature[EMC_IMAGE_SIG_SIZE];
     } root_cert;
 }__attribute__((__packed__));

struct img_header_t
{
     uint32_t        checksum;                                           // 4 bytes
     uint8_t         sp_name[IMG_HEADER_SP_NAME_SIZE];                   // 32 bytes
     uint8_t         image_name[IMG_HEADER_IMAGE_NAME_SIZE];             // 16 bytes
     uint8_t         rev_string[IMG_HEADER_REV_STRING_SIZE];             // 12 bytes
     uint8_t         date_time_stamp[IMG_HEADER_DATE_TIME_STAMP_SIZE];   // 24 bytes
     uint16_t        image_id;                                           // 2 byte
     uint8_t         major_rev;                                          // 1 byte
     uint8_t         minor_rev;                                          // 1 byte
     uint32_t        image_size;                                         // 4 bytes
     uint32_t        spare[IMG_HEADER_SPARE_SIZE];                       // spares for the future, 32 bytes
     uint32_t        header_size;                                        // 4 bytes 
     struct reloc_record_t  records[IMG_HEADER_RELOCATE_RECORD_MAX_ENTRY];      // 108 bytes, RELOCATE_RECORD
     uint16_t        feature_flag;                                       // 2 bytes
     uint16_t        reserved;                                           // 2 bytes
     uint32_t        reserved1;                                          // 4 bytes
     uint64_t        long_rev;                                           // 8 bytes
 } __attribute__((__packed__));                                          // 256 bytes total

struct probe
{
	int a;
	int b;
	char c[4];
};
struct node
{
	int a;
	char b;
};
struct netlink_event
{
	int type;
	int index;

	union
	{
		struct probe bs_probe;
		struct node bs_node;
	} data;
};

struct test
{
	unsigned short a;
	int b;
	unsigned short c;
	unsigned char d;
	unsigned char e; 
	unsigned char f;
};

int main(int argc, char* argv[])
{
	typedef struct qca
	{
		char a;
		int b;
	} qc;
	
	qc qc1;
	qc* qc2;
	qc qc3[2];
	int len1 = sizeof qc1;
	int len2 = sizeof *qc2;
	int len3 = sizeof(qc);
	int len4 = sizeof(qc3);
	int len5 = sizeof(qc3[0]);
	printf("sizeof qc1 %d, sizeof qc2 %d,sizeof(qc) %d\n", len1, len2, len3); 
	printf("sizeof qc3 %d, qc3[0] %d\n", len4, len5);
	printf("sizeof netlink_event %d\n", sizeof(struct netlink_event));
	struct test ts;
	printf("sizefo ts %d\n", sizeof(ts));

	printf("sizeof secure_header_t is 0x%x\n", sizeof(struct secure_header_t)); 
	printf("sizeof img_header_t is 0x%x\n", sizeof(struct img_header_t)); 

	int i = 0;
	int j = sizeof(i++);
	printf("%d %d\n", i, j);
	return 0;
}
