#include <stdio.h>

typedef unsigned char uChar;
#define SFP_VENDOR_NAME_OFFSET        20   
#define SFP_VENDOR_NAME_WIDTH         16 
#define SFP_VENDOR_OUI_OFFSET         37 
#define SFP_VENDOR_OUI_WIDTH          3
#define SFP_VENDOR_PART_NUM_OFFSET    40 
#define SFP_VENDOR_PART_NUM_WIDTH     16   
#define SFP_VENDOR_REVISION_OFFSET    56   
#define SFP_VENDOR_REVISION_WIDTH     4    
#define SFP_EXT_FIELDS_OPTIONS_WIDTH  2    
#define SFP_VENDOR_SERIAL_NUM_WIDTH   16   
#define SFP_DATE_CODE_WIDTH            8   
#define SFP_SPECIFIC_DATA_WIDTH       32   
#define SFP_BASE_SIZE                  64  
#define SFP_EXTENDED_ADDR              64  
#define SFP_EXTENDED_CHECKSUM_ADDR     95 

#define PACKED __attribute__ ((__packed__))

typedef struct _SFP_SPROM_DATA_ {
  uChar Identifier                         ; // @0
  uChar Ext_Identifier                     ;
  uChar Connector                          ;
  uChar Infiniband_Compl_Code              ;
  uChar Sonet_Compl_Code[2]                ;
  uChar Gigabit_Ethernet_Compl_Code        ; // @6
  uChar Fibre_Chan_Link_Length         : 4 ; // @7
  uChar Fibre_Chan_Trans_Tech_7_4      : 4 ;
  uChar Fibre_Chan_Trans_Tech_3_0      : 4 ; // @8
  uChar Fibre_Chan_Trans_Tech_Reserved : 4 ;
  uChar Fibre_Chan_Trans_Media             ; // @9
  uChar Fibre_Chan_Speed                   ; // @10
  uChar Encoding                           ;
  uChar BR_Nominal                         ;
  uChar Reserved1                          ;
  uChar Length_9u_1                        ;
  uChar Length_9u_2                        ;
  uChar Length_50u                         ;
  uChar Length_60u                         ;
  uChar Length_Copper                      ;
  uChar Reserved2                          ; // @19
        
  uChar Vendor_Name[SFP_VENDOR_NAME_WIDTH] ; // @20-35
  uChar Reserved3                          ;
  uChar Vendor_OUI[SFP_VENDOR_OUI_WIDTH]   ;
  uChar Vendor_Part_No[SFP_VENDOR_PART_NUM_WIDTH]  ;
  uChar Vendor_Revision[SFP_VENDOR_REVISION_WIDTH] ;
  uChar Reserved4[3]                       ;
  uChar Check_Code_ID                      ;                                                                                                             
  uChar Options[SFP_EXT_FIELDS_OPTIONS_WIDTH]      ;
  uChar BR_Max                             ;                                                                                                             
  uChar BR_Min                             ;                                                                                                             
  uChar Vendor_Serial_No[SFP_VENDOR_SERIAL_NUM_WIDTH] ;
  uChar Date_Code[SFP_DATE_CODE_WIDTH]     ;
  uChar Diag_Monitoring                    ;
  uChar Reserved5[2]                       ;
  uChar Check_Code_EXT                     ; // @95
  uChar Vendor_Specific_ID[SFP_SPECIFIC_DATA_WIDTH]   ;
  uChar Reserved6[128]                                ;
} PACKED SFP_SPROM_DATA;

#define offsetof(st, m) ((size_t) ( (char*)&((st *)(0))->m - (char*) 0))

int main(void)
{
    int offset = offsetof(SFP_SPROM_DATA, Vendor_Specific_ID);
    printf("Vendor_Specific_ID offset %d, 0x%x\n", offset, offset);
    offset = offsetof(SFP_SPROM_DATA, Identifier);
    printf("Identifier offset %d, 0x%x\n", offset, offset);
    offset = offsetof(SFP_SPROM_DATA, Vendor_Part_No);
    printf("Vendor_Part_No offset %d, 0x%x\n", offset, offset);

    return 0;
}
