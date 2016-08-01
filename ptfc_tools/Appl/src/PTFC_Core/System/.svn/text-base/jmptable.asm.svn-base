;/* ============================================================================ **
;**                           B I T R O N    S p A                               **
;** ============================================================================ **
;**                      +++++++++++++++++++++++++++++                           **
;**           Modulo:    +    JmpTable.asm           +                           **
;**                      +++++++++++++++++++++++++++++                           **
;**                                                                              **
;**   Progetto :          TESLA MSM                                              **
;**                                                                              **
;**                                                                              **
;**   Descrizione :                                                              **
;**     Jump Table per gestione Interrupt                                        **
;**                                                                              **
;**                                                                              **
;**   Procedure Globali :                                                        **
;**                                                                              **
;**                                                                              **
;** ============================================================================ **
;**         modifica                                    data       autore        **
;**  Prima stesura                                  05/ 5/2005  M. Bellucca      **
;**  Adattamento al progetto Tesla                  09/11/2011  E. Yáñez         **
;**  Adattamento alla piattaforma                   20/01/2015  Carmine Celozzi  **
;** ============================================================================ */

    NAME  JMPTABLE
    RSEG  JMPSEG(1)

    PUBLIC  JmpTable

    EXTERN  __program_start
    
    RSEG  JMPSEG

;/* ============================================================================ */
;/*              FUNZIONE :  Interrupt Jump Table()                              */
;/*     .                                                                        */
;/*     .                                                                        */
;/* ============================================================================ */

JmpTable:
RstEntry       BR  __program_start
    
    END
