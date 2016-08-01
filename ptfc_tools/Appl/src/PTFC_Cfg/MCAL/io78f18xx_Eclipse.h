/*
 * EclipsePatch.h
 *
 * Created on: 16/mag/2013
 * Author: Beppe
 */

#ifndef ECLIPSEPATCH_H_
#define ECLIPSEPATCH_H_

/****************************************/
/* PATCH FOR "io78f18xx_32.h"			*/
/****************************************/

typedef struct
{
	 unsigned char no0:1;
	 unsigned char no1:1;
	 unsigned char no2:1;
	 unsigned char no3:1;
	 unsigned char no4:1;
	 unsigned char no5:1;
	 unsigned char no6:1;
	 unsigned char no7:1;
} __BITS8;

extern unsigned char P0;
extern __BITS8 P0_bit;
extern unsigned char P1;
extern __BITS8 P1_bit;
extern unsigned char P3;
extern __BITS8 P3_bit;
extern unsigned char P4;
extern __BITS8 P4_bit;
extern unsigned char P5;
extern __BITS8 P5_bit;
extern unsigned char P6;
extern __BITS8 P6_bit;
extern unsigned char P7;
extern __BITS8 P7_bit;
extern unsigned char P8;
extern __BITS8 P8_bit;
extern unsigned char P9;
extern __BITS8 P9_bit;
extern unsigned char P10;
extern __BITS8 P10_bit;
extern unsigned char P12;
extern __BITS8 P12_bit;
extern unsigned char P13;
extern __BITS8 P13_bit;
extern unsigned char P14;
extern __BITS8 P14_bit;
extern unsigned char P15;
extern __BITS8 P15_bit;

extern unsigned short SDR00;
extern unsigned char SDR00L;

extern unsigned short SDR01;
extern unsigned char SDR01L;

extern unsigned short SDR10;
extern unsigned char SDR10L;

extern unsigned short SDR11;
extern unsigned char SDR11L;

extern unsigned short TDR00;
extern unsigned short TDR01;

extern unsigned short ADCR;
extern const unsigned char ADCRH;

extern unsigned char PM0;
extern  __BITS8 PM0_bit;
extern unsigned char PM1;
extern __BITS8 PM1_bit;
extern unsigned char PM3;
extern __BITS8 PM3_bit;
extern unsigned char PM4;
extern __BITS8 PM4_bit;
extern unsigned char PM5;
extern  __BITS8 PM5_bit;
extern unsigned char PM6;
extern __BITS8 PM6_bit;
extern unsigned char PM7;
extern __BITS8 PM7_bit;
extern unsigned char PM8;
extern __BITS8 PM8_bit;
extern unsigned char PM9;
extern __BITS8 PM9_bit;
extern unsigned char PM10;
extern __BITS8 PM10_bit;
extern unsigned char PM12;
extern __BITS8 PM12_bit;
extern unsigned char PM13;
extern __BITS8 PM13_bit;
extern unsigned char PM14;
extern __BITS8 PM14_bit;
extern unsigned char PM15;
extern __BITS8 PM15_bit;


extern unsigned char ADM0;
extern __BITS8 ADM0_bit;
extern unsigned char ADS;
extern __BITS8 ADS_bit;
extern unsigned char ADSMP;
extern unsigned char IPSEL0;
extern __BITS8 IPSEL0_bit;
extern unsigned char KRM;
extern __BITS8 KRM_bit;
extern __BITS8 ADSMP_bit;
extern unsigned char EGP0;
extern __BITS8 EGP0_bit;
extern unsigned char EGN0;
extern __BITS8 EGN0_bit;
extern unsigned char EGP1;
extern __BITS8 EGP1_bit;
extern unsigned char EGN1;
extern __BITS8 EGN1_bit;
extern unsigned char STSEL;
extern __BITS8 STSEL_bit;
extern unsigned char TIS0;
extern __BITS8 TIS0_bit;
extern unsigned char TIS1;
extern __BITS8 TIS1_bit;
extern unsigned char ADM1;
extern __BITS8 ADM1_bit;
extern unsigned short SDR20;
extern unsigned char SDR20L;
extern unsigned short SDR21; 
extern unsigned char SDR21L;
extern unsigned short UF0TX;
extern unsigned char UF0TXB;
extern unsigned short UF0RX;
extern unsigned char UF0RXB;
extern unsigned short UF1TX;
extern unsigned char UF1TXB;
extern unsigned short UF1RX;
extern unsigned char UF1RXB;
extern unsigned char TOS0;
extern __BITS8 TOS0_bit;
extern unsigned char TOS1;
extern __BITS8 TOS1_bit;
extern unsigned short TDR02;
extern unsigned short TDR03;
extern unsigned short TDR04;
extern unsigned short TDR05;
extern unsigned short TDR06;
extern unsigned short TDR07;
extern unsigned short TDR10;
extern unsigned short TDR11;
extern unsigned short TDR12;
extern unsigned short TDR13;
extern unsigned short TDR14;
extern unsigned short TDR15;
extern unsigned short TDR16;
extern unsigned short TDR17;
extern unsigned short TDR20;
extern unsigned short TDR21;
extern unsigned short TDR22;
extern unsigned short TDR23;
extern unsigned char CMC;
extern unsigned char CSC;
extern __BITS8 CSC_bit;
extern unsigned char OSTC;
extern __BITS8 OSTC_bit;
extern unsigned char OSTS;
extern unsigned char CKC;
extern __BITS8 CKC_bit;
extern unsigned char CKS; 
extern __BITS8 CKS_bit;
extern const unsigned char RESF;
extern unsigned char LVIM;
extern __BITS8 LVIM_bit;
extern unsigned char LVIS;
extern __BITS8 LVIS_bit;
extern unsigned char WDTE;
extern unsigned char WUTMCTL;
extern __BITS8 WUTMCTL_bit;
extern unsigned short WUTMCMP;
extern unsigned char DSA0;
extern unsigned char DSA1;
extern unsigned short DRA0;
extern unsigned char DRA0L;
extern unsigned char DRA0H;
extern unsigned short DRA1;
extern unsigned char DRA1L;
extern unsigned char DRA1H;
extern unsigned short DBC0;
extern unsigned char DBC0L;
extern unsigned char DBC0H;
extern unsigned short DBC1;
extern unsigned char DBC1L;
extern unsigned char DBC1H;
extern unsigned char DMC0;
extern __BITS8 DMC0_bit;
extern unsigned char DMC1;
extern __BITS8 DMC1_bit;
extern unsigned char DRC0;
extern __BITS8 DRC0_bit;
extern unsigned char DRC1;
extern __BITS8 DRC1_bit;
extern unsigned char BECTL;
extern __BITS8 BECTL_bit;
extern unsigned short IF2;
extern unsigned char IF2L;
extern __BITS8 IF2L_bit;
extern unsigned char IF2H;
extern __BITS8 IF2H_bit;
extern unsigned short IF3;
extern unsigned char IF3L;
extern __BITS8 IF3L_bit;
extern unsigned char IF3H;
extern __BITS8 IF3H_bit;
extern unsigned short MK2;
extern unsigned char MK2L;
extern __BITS8 MK2L_bit;
extern unsigned char MK2H;
extern __BITS8 MK2H_bit;
extern unsigned short MK3;
extern unsigned char MK3L;
extern __BITS8 MK3L_bit;
extern unsigned char MK3H;
extern __BITS8 MK3H_bit;
extern unsigned short PR02;
extern unsigned char PR02L;
extern __BITS8 PR02L_bit;
extern unsigned char PR02H;
extern __BITS8 PR02H_bit;
extern unsigned short PR03;
extern unsigned char PR03L;
extern __BITS8 PR03L_bit;
extern unsigned char PR03H;
extern __BITS8 PR03H_bit;
extern unsigned short PR12;
extern unsigned char PR12L;
extern __BITS8 PR12L_bit;
extern unsigned char PR12H;
extern __BITS8 PR12H_bit;
extern unsigned short PR13;
extern unsigned char PR13L;
extern __BITS8 PR13L_bit;
extern unsigned char PR13H;
extern __BITS8 PR13H_bit;
extern unsigned short IF0;
extern unsigned char IF0L;
extern __BITS8 IF0L_bit;
extern unsigned char IF0H;
extern __BITS8 IF0H_bit;
extern unsigned short IF1;
extern unsigned char IF1L;
extern __BITS8 IF1L_bit;
extern unsigned char IF1H;
extern __BITS8 IF1H_bit;
extern unsigned short MK0;
extern unsigned char MK0L;
extern __BITS8 MK0L_bit;
extern unsigned char MK0H;
extern __BITS8 MK0H_bit;
extern unsigned short MK1;
extern unsigned char MK1L;
extern __BITS8 MK1L_bit;
extern unsigned char MK1H;
extern __BITS8 MK1H_bit;
extern unsigned short PR00;
extern unsigned char PR00L;
extern __BITS8 PR00L_bit;
extern unsigned char PR00H;
extern __BITS8 PR00H_bit;
extern unsigned short PR01;
extern unsigned char PR01L;
extern __BITS8 PR01L_bit;
extern unsigned char PR01H;
extern __BITS8 PR01H_bit;
extern unsigned short PR10;
extern unsigned char PR10L;
extern __BITS8 PR10L_bit;
extern unsigned char PR10H;
extern __BITS8 PR10H_bit;
extern unsigned short PR11;
extern unsigned char PR11L;
extern __BITS8 PR11L_bit;
extern unsigned char PR11H;
extern __BITS8 PR11H_bit;
extern unsigned short MDAL;
extern unsigned short MULA;
extern unsigned short MDAH;
extern unsigned short MULB;
extern unsigned short MDBH;
extern const unsigned short MULOH;
extern unsigned short MDBL;
extern const unsigned short MULOL;
extern unsigned char PMC;
extern __BITS8 PMC_bit;

/*----------------------------------------------
 *       SFR bit declarations
 *--------------------------------------------*/

#define ADCE              ADM0_bit.no0
#define ADCS              ADM0_bit.no7

#define ADTMD             ADM1_bit.no7

#define HIOSTOP           CSC_bit.no0
#define XTSTOP            CSC_bit.no6
#define MSTOP             CSC_bit.no7

#define MCM0              CKC_bit.no4
#define MCS               CKC_bit.no5
#define CSS               CKC_bit.no6
#define CLS               CKC_bit.no7

#define PCLOE             CKS_bit.no7

#define LVIF              LVIM_bit.no0
#define LVIMD             LVIM_bit.no1
#define LVISEL            LVIM_bit.no2
#define LVION             LVIM_bit.no7

#define WUTMCE            WUTMCTL_bit.no7

#define DS0               DMC0_bit.no5
#define DRS0              DMC0_bit.no6
#define STG0              DMC0_bit.no7

#define DS1               DMC1_bit.no5
#define DRS1              DMC1_bit.no6
#define STG1              DMC1_bit.no7

#define DST0              DRC0_bit.no0
#define DEN0              DRC0_bit.no7

#define DST1              DRC1_bit.no0
#define DEN1              DRC1_bit.no7

#define FLMDPUP           BECTL_bit.no7

#define TMIF05            IF2L_bit.no0
#define TMIF06            IF2L_bit.no1
#define TMIF07            IF2L_bit.no2
#define KRIF              IF2L_bit.no3
#define PIF6              IF2L_bit.no3
#define PIF7              IF2L_bit.no4
#define C0ERRIF           IF2L_bit.no5
#define C0WUPIF           IF2L_bit.no6
#define C0RECIF           IF2L_bit.no7

#define C0TRXIF           IF2H_bit.no0
#define TMIF10            IF2H_bit.no1
#define TMIF11            IF2H_bit.no2
#define TMIF12            IF2H_bit.no3
#define TMIF13            IF2H_bit.no4
#define MDIF              IF2H_bit.no5
#define IICIF20           IF2H_bit.no6
#define STIF2             IF2H_bit.no6
#define SRIF2             IF2H_bit.no7

#define PIFR2             IF3L_bit.no0
#define TMIF14            IF3L_bit.no1
#define TMIF15            IF3L_bit.no2
#define TMIF16            IF3L_bit.no3
#define TMIF17            IF3L_bit.no4
#define TMIF20            IF3L_bit.no5
#define TMIF21            IF3L_bit.no6
#define TMIF22            IF3L_bit.no7

#define TMIF23            IF3H_bit.no0
#define DMAIF2            IF3H_bit.no3
#define DMAIF3            IF3H_bit.no4

#define TMMK05            MK2L_bit.no0
#define TMMK06            MK2L_bit.no1
#define TMMK07            MK2L_bit.no2
#define KRMK              MK2L_bit.no3
#define PMK6              MK2L_bit.no3
#define PMK7              MK2L_bit.no4
#define C0ERRMK           MK2L_bit.no5
#define C0WUPMK           MK2L_bit.no6
#define C0RECMK           MK2L_bit.no7

#define C0TRXMK           MK2H_bit.no0
#define TMMK10            MK2H_bit.no1
#define TMMK11            MK2H_bit.no2
#define TMMK12            MK2H_bit.no3
#define TMMK13            MK2H_bit.no4
#define MDMK              MK2H_bit.no5
#define IICMK20           MK2H_bit.no6
#define STMK2             MK2H_bit.no6
#define SRMK2             MK2H_bit.no7

#define PMKR2             MK3L_bit.no0
#define TMMK14            MK3L_bit.no1
#define TMMK15            MK3L_bit.no2
#define TMMK16            MK3L_bit.no3
#define TMMK17            MK3L_bit.no4
#define TMMK20            MK3L_bit.no5
#define TMMK21            MK3L_bit.no6
#define TMMK22            MK3L_bit.no7

#define TMMK23            MK3H_bit.no0
#define DMAMK2            MK3H_bit.no3
#define DMAMK3            MK3H_bit.no4

#define TMPR005           PR02L_bit.no0
#define TMPR006           PR02L_bit.no1
#define TMPR007           PR02L_bit.no2
#define KRPR0             PR02L_bit.no3
#define PPR06             PR02L_bit.no3
#define PPR07             PR02L_bit.no4
#define C0ERRPR0          PR02L_bit.no5
#define C0WUPPR0          PR02L_bit.no6
#define C0RECPR0          PR02L_bit.no7

#define C0TRXPR0          PR02H_bit.no0
#define TMPR010           PR02H_bit.no1
#define TMPR011           PR02H_bit.no2
#define TMPR012           PR02H_bit.no3
#define TMPR013           PR02H_bit.no4
#define MDPR0             PR02H_bit.no5
#define IICPR020          PR02H_bit.no6
#define STPR02            PR02H_bit.no6
#define SRPR02            PR02H_bit.no7

#define PPR0R2            PR03L_bit.no0
#define TMPR014           PR03L_bit.no1
#define TMPR015           PR03L_bit.no2
#define TMPR016           PR03L_bit.no3
#define TMPR017           PR03L_bit.no4
#define TMPR020           PR03L_bit.no5
#define TMPR021           PR03L_bit.no6
#define TMPR022           PR03L_bit.no7

#define TMPR023           PR03H_bit.no0
#define DMAPR02           PR03H_bit.no3
#define DMAPR03           PR03H_bit.no4

#define TMPR105           PR12L_bit.no0
#define TMPR106           PR12L_bit.no1
#define TMPR107           PR12L_bit.no2
#define KRPR1             PR12L_bit.no3
#define PPR16             PR12L_bit.no3
#define PPR17             PR12L_bit.no4
#define C0ERRPR1          PR12L_bit.no5
#define C0WUPPR1          PR12L_bit.no6
#define C0RECPR1          PR12L_bit.no7

#define C0TRXPR1          PR12H_bit.no0
#define TMPR110           PR12H_bit.no1
#define TMPR111           PR12H_bit.no2
#define TMPR112           PR12H_bit.no3
#define TMPR113           PR12H_bit.no4
#define MDPR1             PR12H_bit.no5
#define IICPR120          PR12H_bit.no6
#define STPR12            PR12H_bit.no6
#define SRPR12            PR12H_bit.no7

#define PPR1R2            PR13L_bit.no0
#define TMPR114           PR13L_bit.no1
#define TMPR115           PR13L_bit.no2
#define TMPR116           PR13L_bit.no3
#define TMPR117           PR13L_bit.no4
#define TMPR120           PR13L_bit.no5
#define TMPR121           PR13L_bit.no6
#define TMPR122           PR13L_bit.no7

#define TMPR123           PR13H_bit.no0
#define DMAPR12           PR13H_bit.no3
#define DMAPR13           PR13H_bit.no4

#define WDTIIF            IF0L_bit.no0
#define LVIIF             IF0L_bit.no1
#define PIF0              IF0L_bit.no2
#define PIF1              IF0L_bit.no3
#define PIF2              IF0L_bit.no4
#define PIF3              IF0L_bit.no5
#define PIF4              IF0L_bit.no6
#define PIF5              IF0L_bit.no7

#define CLMIF             IF0H_bit.no0
#define CSIIF00           IF0H_bit.no1
#define CSIIF01           IF0H_bit.no2
#define DMAIF0            IF0H_bit.no3
#define DMAIF1            IF0H_bit.no4
#define WUTMIF            IF0H_bit.no5
#define FLIF              IF0H_bit.no6
#define LTIF0             IF0H_bit.no7

#define LRIF0             IF1L_bit.no0
#define LSIF0             IF1L_bit.no1
#define PIFLR0            IF1L_bit.no2
#define PIF8              IF1L_bit.no3
#define TMIF00            IF1L_bit.no4
#define TMIF01            IF1L_bit.no5
#define TMIF02            IF1L_bit.no6
#define TMIF03            IF1L_bit.no7

#define ADIF              IF1H_bit.no0
#define LTIF1             IF1H_bit.no1
#define LRIF1             IF1H_bit.no2
#define LSIF1             IF1H_bit.no3
#define PIFLR1            IF1H_bit.no4
#define CSIIF10           IF1H_bit.no5
#define IICIF11           IF1H_bit.no6
#define TMIF04            IF1H_bit.no7

#define WDTIMK            MK0L_bit.no0
#define LVIMK             MK0L_bit.no1
#define PMK0              MK0L_bit.no2
#define PMK1              MK0L_bit.no3
#define PMK2              MK0L_bit.no4
#define PMK3              MK0L_bit.no5
#define PMK4              MK0L_bit.no6
#define PMK5              MK0L_bit.no7

#define CLMMK             MK0H_bit.no0
#define CSIMK00           MK0H_bit.no1
#define CSIMK01           MK0H_bit.no2
#define DMAMK0            MK0H_bit.no3
#define DMAMK1            MK0H_bit.no4
#define WUTMMK            MK0H_bit.no5
#define FLMK              MK0H_bit.no6
#define LTMK0             MK0H_bit.no7

#define LRMK0             MK1L_bit.no0
#define LSMK0             MK1L_bit.no1
#define PMKLR0            MK1L_bit.no2
#define PMK8              MK1L_bit.no3
#define TMMK00            MK1L_bit.no4
#define TMMK01            MK1L_bit.no5
#define TMMK02            MK1L_bit.no6
#define TMMK03            MK1L_bit.no7

#define ADMK              MK1H_bit.no0
#define LTMK1             MK1H_bit.no1
#define LRMK1             MK1H_bit.no2
#define LSMK1             MK1H_bit.no3
#define PMKLR1            MK1H_bit.no4
#define CSIMK10           MK1H_bit.no5
#define IICMK11           MK1H_bit.no6
#define TMMK04            MK1H_bit.no7

#define WDTIPR0           PR00L_bit.no0
#define LVIPR0            PR00L_bit.no1
#define PPR00             PR00L_bit.no2
#define PPR01             PR00L_bit.no3
#define PPR02             PR00L_bit.no4
#define PPR03             PR00L_bit.no5
#define PPR04             PR00L_bit.no6
#define PPR05             PR00L_bit.no7

#define CLMPR0            PR00H_bit.no0
#define CSIPR000          PR00H_bit.no1
#define CSIPR001          PR00H_bit.no2
#define DMAPR00           PR00H_bit.no3
#define DMAPR01           PR00H_bit.no4
#define WUTMPR0           PR00H_bit.no5
#define FLPR0             PR00H_bit.no6
#define LTPR00            PR00H_bit.no7

#define LRPR00            PR01L_bit.no0
#define LSPR00            PR01L_bit.no1
#define PPR0LR0           PR01L_bit.no2
#define PPR08             PR01L_bit.no3
#define TMPR000           PR01L_bit.no4
#define TMPR001           PR01L_bit.no5
#define TMPR002           PR01L_bit.no6
#define TMPR003           PR01L_bit.no7

#define ADPR0             PR01H_bit.no0
#define LTPR01            PR01H_bit.no1
#define LRPR01            PR01H_bit.no2
#define LSPR01            PR01H_bit.no3
#define PPR0LR1           PR01H_bit.no4
#define CSIPR010          PR01H_bit.no5
#define IICPR011          PR01H_bit.no6
#define TMPR004           PR01H_bit.no7

#define WDTIPR1           PR10L_bit.no0
#define LVIPR1            PR10L_bit.no1
#define PPR10             PR10L_bit.no2
#define PPR11             PR10L_bit.no3
#define PPR12             PR10L_bit.no4
#define PPR13             PR10L_bit.no5
#define PPR14             PR10L_bit.no6
#define PPR15             PR10L_bit.no7

#define CLMPR1            PR10H_bit.no0
#define CSIPR100          PR10H_bit.no1
#define CSIPR101          PR10H_bit.no2
#define DMAPR10           PR10H_bit.no3
#define DMAPR11           PR10H_bit.no4
#define WUTMPR1           PR10H_bit.no5
#define FLPR1             PR10H_bit.no6
#define LTPR10            PR10H_bit.no7

#define LRPR10            PR11L_bit.no0
#define LSPR10            PR11L_bit.no1
#define PPR1LR0           PR11L_bit.no2
#define PPR18             PR11L_bit.no3
#define TMPR100           PR11L_bit.no4
#define TMPR101           PR11L_bit.no5
#define TMPR102           PR11L_bit.no6
#define TMPR103           PR11L_bit.no7

#define ADPR1             PR11H_bit.no0
#define LTPR11            PR11H_bit.no1
#define LRPR11            PR11H_bit.no2
#define LSPR11            PR11H_bit.no3
#define PPR1LR1           PR11H_bit.no4
#define CSIPR110          PR11H_bit.no5
#define IICPR111          PR11H_bit.no6
#define TMPR104           PR11H_bit.no7

#define MAA               PMC_bit.no0

/****************************************/
/* PATCH FOR "io78f18xx_32_ext.h"		*/
/****************************************/

extern unsigned char ADPC;
extern unsigned char PU1;
extern __BITS8 PU1_bit;
extern unsigned char PU3;
extern __BITS8 PU3_bit;
extern unsigned char PU4;
extern __BITS8 PU4_bit;
extern unsigned char PU5;
extern __BITS8 PU5_bit;
extern unsigned char PU6;
extern __BITS8 PU6_bit;
extern unsigned char PU12;
extern __BITS8 PU12_bit;
extern unsigned char PIM6;
extern __BITS8 PIM6_bit;
extern unsigned char NFEN0;
extern __BITS8 NFEN0_bit;
extern unsigned char NFEN1;
extern __BITS8 NFEN1_bit;
extern unsigned char NFEN2;
extern __BITS8 NFEN2_bit;
extern unsigned char PSRSEL;
extern __BITS8 PSRSEL_bit;
extern unsigned char GUARD;
extern __BITS8 GUARD_bit;
extern unsigned char WDTSELF;
extern unsigned char IAWCTL;
extern __BITS8 IAWCTL_bit;
extern unsigned char IAWRAM;
extern unsigned char IAWFLASH;
extern unsigned char DMCALL;
extern __BITS8 DMCALL_bit;
extern const unsigned short MDCL;
extern const unsigned short MDCH;
extern unsigned char MDUC;
extern __BITS8 MDUC_bit;;
extern unsigned char PER0;
extern __BITS8 PER0_bit;
extern unsigned char PER1;
extern __BITS8 PER1_bit;
extern unsigned char PCKSEL;
extern __BITS8 PCKSEL_bit;
extern unsigned char OSMC;
extern __BITS8 OSMC_bit;
extern const unsigned char PLLSTS;
extern __BITS8 PLLSTS_bit;
extern unsigned char PLLCTL;
extern __BITS8 PLLCTL_bit;
extern unsigned short HIOTRM;
extern unsigned char LIOTRM;
extern unsigned char POCRES;
extern __BITS8 POCRES_bit;
extern const unsigned char BCDADJ;
extern const unsigned short SSR00;
extern unsigned char SSR00L;;
extern unsigned short SIR00;
extern unsigned char SIR00L;;
extern unsigned short SMR00;
extern unsigned short SCR00;
extern const unsigned short SE0;
extern unsigned char SE0L;
extern __BITS8 SE0L_bit;
extern unsigned short SS0;
extern unsigned char SS0L;
extern __BITS8 SS0L_bit;
extern unsigned short ST0;
extern unsigned char ST0L;
extern __BITS8 ST0L_bit;
extern unsigned short SPS0;
extern unsigned char SPS0L;;
extern unsigned short SO0;
extern unsigned short SOE0;
extern unsigned char SOE0L;
extern __BITS8 SOE0L_bit;
extern unsigned short SOL0;
extern unsigned char SOL0L;
extern unsigned short SSE0;
extern unsigned char SSE0L;
extern __BITS8 SSE0L_bit;
extern const unsigned short SSR10;
extern unsigned char SSR10L;
extern const unsigned short SSR11;
extern unsigned char SSR11L;
extern unsigned short SIR10;
extern unsigned char SIR10L;
extern unsigned short SIR11;
extern unsigned char SIR11L;
extern unsigned short SMR10;
extern unsigned short SMR11;
extern unsigned short SCR10;
extern unsigned short SCR11;
extern const unsigned short SE1;
extern unsigned char SE1L;
extern __BITS8 SE1L_bit;
extern unsigned short SS1;
extern unsigned char SS1L;
extern __BITS8 SS1L_bit;
extern unsigned short ST1;
extern unsigned char ST1L;
extern __BITS8 ST1L_bit;
extern unsigned short SPS1;
extern unsigned char SPS1L;
extern unsigned short SO1;
extern unsigned short SOE1;
extern unsigned char SOE1L;
extern __BITS8 SOE1L_bit;
extern unsigned short SOL1;
extern unsigned char SOL1L;
extern const unsigned short TCR00;
extern const unsigned short TCR01;
extern const unsigned short TCR02;
extern const unsigned short TCR03;
extern const unsigned short TCR04;
extern const unsigned short TCR05;
extern const unsigned short TCR06;
extern const unsigned short TCR07;
extern unsigned short TMR00;
extern unsigned short TMR01;
extern unsigned short TMR02;
extern unsigned short TMR03;
extern unsigned short TMR04;
extern unsigned short TMR05;
extern unsigned short TMR06;
extern unsigned short TMR07;
extern const unsigned short TSR00;
extern const unsigned short TSR01;
extern const unsigned short TSR02;
extern const unsigned short TSR03;
extern const unsigned short TSR04;
extern const unsigned short TSR05;
extern const unsigned short TSR06;
extern const unsigned short TSR07;
extern unsigned char TSR00L;
extern unsigned char TSR01L;
extern unsigned char TSR02L;
extern unsigned char TSR03L;
extern unsigned char TSR04L;
extern unsigned char TSR05L;
extern unsigned char TSR06L;
extern unsigned char TSR07L;
extern const unsigned short TE0;
extern unsigned char TE0L;
extern __BITS8 TE0L_bit;
extern unsigned short TS0;
extern unsigned char TS0L;
extern __BITS8 TS0L_bit;
extern unsigned short TT0;
extern unsigned char TT0L;
extern __BITS8 TT0L_bit;
extern unsigned short TPS0;
extern unsigned short TO0;
extern unsigned char TO0L;
extern unsigned short TOE0;
extern unsigned char TOE0L;
extern __BITS8 TOE0L_bit;
extern unsigned short TOL0;
extern unsigned char TOL0L;
extern unsigned short TOM0;
extern unsigned char TOM0L;
extern const unsigned short TCR10;
extern const unsigned short TCR11;
extern const unsigned short TCR12;
extern const unsigned short TCR13;
extern const unsigned short TCR14;
extern const unsigned short TCR15;
extern const unsigned short TCR16;
extern const unsigned short TCR17;
extern unsigned short TMR10;
extern unsigned short TMR11;
extern unsigned short TMR12;
extern unsigned short TMR13;
extern unsigned short TMR14;
extern unsigned short TMR15;
extern unsigned short TMR16;
extern unsigned short TMR17;
extern const unsigned short TSR10;
extern const unsigned short TSR11;
extern const unsigned short TSR12;
extern const unsigned short TSR13;
extern const unsigned short TSR14;
extern const unsigned short TSR15;
extern const unsigned short TSR16;
extern const unsigned short TSR17;
extern unsigned char TSR10L;
extern unsigned char TSR11L;
extern unsigned char TSR12L;
extern unsigned char TSR13L;
extern unsigned char TSR14L;
extern unsigned char TSR15L;
extern unsigned char TSR16L;
extern unsigned char TSR17L;
extern const unsigned short TE1;
extern unsigned char TE1L;
extern __BITS8 TE1L_bit;
extern unsigned short TS1;
extern unsigned char TS1L;
extern __BITS8 TS1L_bit;;
extern unsigned short TT1;
extern unsigned char TT1L;
extern __BITS8 TT1L_bit;
extern unsigned short TPS1;
extern unsigned short TO1;
extern unsigned char TO1L;
extern unsigned short TOE1;
extern unsigned char TOE1L;
extern __BITS8 TOE1L_bit;
extern unsigned short TOL1;
extern unsigned char TOL1L;
extern unsigned short TOM1;
extern unsigned char TOM1L;
extern unsigned char UF0CTL0;
extern __BITS8 UF0CTL0_bit;
extern unsigned char UF0OPT0;
extern __BITS8 UF0OPT0_bit;
extern unsigned short UF0CTL1;
extern unsigned char UF0OPT1;
extern __BITS8 UF0OPT1_bit;
extern unsigned char UF0OPT2;
extern __BITS8 UF0OPT2_bit;;
extern const unsigned short UF0STR;
extern unsigned short UF0STC;
extern unsigned short UF0WTX;
extern unsigned char UF0WTXB;
extern unsigned char UF0ID;
extern unsigned char UF0BUF0;
extern unsigned char UF0BUF1;
extern unsigned char UF0BUF2;
extern unsigned char UF0BUF3;
extern unsigned char UF0BUF4;
extern unsigned char UF0BUF5;
extern unsigned char UF0BUF6;
extern unsigned char UF0BUF7;
extern unsigned char UF0BUF8;
extern unsigned short UF0BUCTL;
extern unsigned char UF1CTL0;
extern __BITS8 UF1CTL0_bit;
extern unsigned char UF1OPT0;
extern __BITS8 UF1OPT0_bit;
extern unsigned short UF1CTL1;
extern unsigned char UF1OPT1;
extern __BITS8 UF1OPT1_bit;
extern unsigned char UF1OPT2;
extern __BITS8 UF1OPT2_bit;
extern const unsigned short UF1STR;
extern unsigned short UF1STC;
extern unsigned short UF1WTX;  unsigned char UF1WTXB;
extern unsigned char UF1ID;
extern unsigned char UF1BUF0;
extern unsigned char UF1BUF1;
extern unsigned char UF1BUF2;
extern unsigned char UF1BUF3;
extern unsigned char UF1BUF4;
extern unsigned char UF1BUF5;
extern unsigned char UF1BUF6;
extern unsigned char UF1BUF7;
extern unsigned char UF1BUF8;
extern unsigned short UF1BUCTL;
extern const unsigned short ADCR0;
extern const unsigned short ADCR1;
extern const unsigned short ADCR2;
extern const unsigned short ADCR3;
extern const unsigned short ADCR4;
extern const unsigned short ADCR5;
extern const unsigned short ADCR6;
extern const unsigned short ADCR7;
extern const unsigned short ADCR8;
extern const unsigned short ADCR9;
extern const unsigned short ADCR10;
extern const unsigned short ADCR11;
extern const unsigned short ADCR12;
extern const unsigned short ADCR13;
extern const unsigned short ADCR14;
extern const unsigned short ADCR15;
extern const unsigned char ADCR0H;
extern const unsigned char ADCR1H;
extern const unsigned char ADCR2H;
extern const unsigned char ADCR3H;
extern const unsigned char ADCR4H;
extern const unsigned char ADCR5H;
extern const unsigned char ADCR6H;
extern const unsigned char ADCR7H;
extern const unsigned char ADCR8H;
extern const unsigned char ADCR9H;
extern const unsigned char ADCR10H;
extern const unsigned char ADCR11H;
extern const unsigned char ADCR12H;
extern const unsigned char ADCR13H;
extern const unsigned char ADCR14H;
extern const unsigned char ADCR15H;


extern const unsigned char DFLST;
extern __BITS8 DFLST_bit;



/*----------------------------------------------
 * Extended SFR bit declarations
 *--------------------------------------------*/

#define GDCSC  GUARD_bit.no0
#define GDPLL  GUARD_bit.no1
#define GDLTRM  GUARD_bit.no2
#define GDLVI  GUARD_bit.no5
#define GDIAW  GUARD_bit.no6
#define GDWDT  GUARD_bit.no7

#define IAWEN  IAWCTL_bit.no7

#define DWAITALL  DMCALL_bit.no0
#define DPRMOD  DMCALL_bit.no7

#define DIVST  MDUC_bit.no0
#define DIVMODE  MDUC_bit.no7

#define TAU0EN  PER0_bit.no0
#define TAU1EN  PER0_bit.no1
#define SAU0EN  PER0_bit.no3
#define SAU1EN  PER0_bit.no4
#define LIN0EN  PER0_bit.no5
#define LIN1EN  PER0_bit.no6
#define ADCEN   PER0_bit.no7

#define DFLEN  PER1_bit.no0
#define WUTEN  PER1_bit.no1

#define WUTMCKE  PCKSEL_bit.no2

#define SELPLLS  PLLSTS_bit.no3
#define LOCK  PLLSTS_bit.no7

#define PLLON  PLLCTL_bit.no0
#define SELPLL  PLLCTL_bit.no2

#define UF0RXE  UF0CTL0_bit.no5
#define UF0TXE  UF0CTL0_bit.no6

#define UF0BTT  UF0OPT0_bit.no5
#define UF0BRT  UF0OPT0_bit.no6
#define UF0BRF  UF0OPT0_bit.no7

#define UF0EBC  UF0OPT1_bit.no5

#define UF0ITS  UF0OPT2_bit.no0

#define UF1RXE  UF1CTL0_bit.no5
#define UF1TXE  UF1CTL0_bit.no6

#define UF1BTT  UF1OPT0_bit.no5
#define UF1BRT  UF1OPT0_bit.no6
#define UF1BRF  UF1OPT0_bit.no7

#define UF1EBC  UF1OPT1_bit.no5

#define UF1ITS  UF1OPT2_bit.no0

#define DFRDY   DFLST_bit.no0

#define __saddr
#define __no_init
#define __interrupt
#define __far
#define __callt
#define __root

#endif /* ECLIPSEPATCH_H_ */
