/*
 *************************************************************************
 *
 *                   "DHRYSTONE" Benchmark Program
 *                   -----------------------------
 *
 *  Version:    C, Version 2.1
 *
 *  File:       dhry_1.c (part 2 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Author:     Reinhold P. Weicker
 *
 *************************************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dhry.h"

/* Global Variables: */

Rec_Pointer     Ptr_Glob,
                Next_Ptr_Glob;
int             Int_Glob;
Boolean         Bool_Glob;
char            Ch_1_Glob,
                Ch_2_Glob;
int             Arr_1_Glob [50];
int             Arr_2_Glob [50] [50];

char Reg_Define[] = "Register option selected.";

/*extern char     *malloc ();*/
Enumeration     Func_1 ();
  /* forward declaration necessary since Enumeration may not simply be int */


#ifndef ROPT
#define REG
        /* REG becomes defined as empty */
        /* i.e. no register variables   */
#else
#define REG register
#endif

void Proc_1(REG Rec_Pointer);
void Proc_2 (One_Fifty *);
void Proc_3 (Rec_Pointer *);
void Proc_4 (void);
void Proc_5 (void);
#ifdef  NOSTRUCTASSIGN
 void memcpy (register char *, register char *, register int);
#endif

extern Boolean Func_2 (Str_30, Str_30);
extern void Proc_6 (Enumeration, Enumeration *);
extern void Proc_7 (One_Fifty, One_Fifty, One_Fifty *);
extern void Proc_8 (Arr_1_Dim, Arr_2_Dim, int, int);


/* variables for time measurement: */

#define Too_Small_Time 2
                /* Measurements should last at least 2 seconds */

double          Begin_Time,
                End_Time,
                User_Time;

double          Microseconds,
                Dhrystones_Per_Second,
                Vax_Mips;

/* end of variables for time measurement */


extern int
dhrymain (long nLoops, FILE *outbuf)
/*****/

  /* main program, corresponds to procedures        */
  /* Main and Proc_0 in the Ada version             */
{
  double   dtime();

        One_Fifty       Int_1_Loc = 0;
  REG   One_Fifty       Int_2_Loc = 0;
        One_Fifty       Int_3_Loc;
  REG   char            Ch_Index;
        Enumeration     Enum_Loc;
        Str_30          Str_1_Loc;
        Str_30          Str_2_Loc;
  REG   long            Run_Index;
  REG   long            Number_Of_Runs;

  /*      FILE            *Ap; */

  /* Initializations */
 /*#ifdef riscos
  if ((Ap = fopen("dhry/res","a+")) == NULL)
 #else
  if ((Ap = fopen("dhry.res","a+")) == NULL)
 #endif
    {
       printf("Can not open dhry.res\n\n");
       exit(1);
    }
	*/
  Next_Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type));
  Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type));

  Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
  Ptr_Glob->Discr                       = Ident_1;
  Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
  Ptr_Glob->variant.var_1.Int_Comp      = 40;
  strcpy (Ptr_Glob->variant.var_1.Str_Comp,
          "DHRYSTONE PROGRAM, SOME STRING");
  strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

  Arr_2_Glob [8][7] = 10;
        /* Was missing in published program. Without this statement,    */
        /* Arr_2_Glob [8][7] would have an undefined value.             */
        /* Warning: With 16-Bit processors and Number_Of_Runs > 32000,  */
        /* overflow may occur for this array element.                   */

  fprintf (outbuf,"\n");
  fprintf (outbuf,"Dhrystone Benchmark, Version 2.1 (Language: C)\n");
  fprintf (outbuf,"\n");
/*
  if (Reg)
  {
    printf ("Program compiled with 'register' attribute\n");
    printf ("\n");
  }
  else
  {
    printf ("Program compiled without 'register' attribute\n");
    printf ("\n");
  }
*/
  fprintf (outbuf,"Please give the number of runs through the benchmark: ");
  /*{
    long n;
    scanf ("%ld", &n);*/
    Number_Of_Runs = nLoops;
  /*}*/
  fprintf (outbuf,"\n");

  fprintf (outbuf,"Execution starts, %ld runs through Dhrystone\n",Number_Of_Runs);

  /***************/
  /* Start timer */
  /***************/

  Begin_Time = dtime();

  for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
  {

    Proc_5();
    Proc_4();
      /* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
    Int_1_Loc = 2;
    Int_2_Loc = 3;
    strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
    Enum_Loc = Ident_2;
    Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc);
      /* Bool_Glob == 1 */
    while (Int_1_Loc < Int_2_Loc)  /* loop body executed once */
    {
      Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
        /* Int_3_Loc == 7 */
      Proc_7 (Int_1_Loc, Int_2_Loc, &Int_3_Loc);
        /* Int_3_Loc == 7 */
      Int_1_Loc += 1;
    } /* while */
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Proc_8 (Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);
      /* Int_Glob == 5 */
    Proc_1 (Ptr_Glob);
    for (Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
                             /* loop body executed twice */
    {
      if (Enum_Loc == Func_1 (Ch_Index, 'C'))
          /* then, not executed */
        {
        Proc_6 (Ident_1, &Enum_Loc);
        strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
        Int_2_Loc = Run_Index;
        Int_Glob = Run_Index;
        }
    }
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Int_2_Loc = Int_2_Loc * Int_1_Loc;
    Int_1_Loc = Int_2_Loc / Int_3_Loc;
    Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
      /* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
    Proc_2 (&Int_1_Loc);
      /* Int_1_Loc == 5 */

  } /* loop "for Run_Index" */

  /**************/
  /* Stop timer */
  /**************/

  End_Time = dtime();

  fprintf(outbuf,"Execution ends\n");
  fprintf(outbuf,"\n");
  fprintf(outbuf,"Final values of the variables used in the benchmark:\n");
  fprintf(outbuf,"\n");
  fprintf(outbuf,"Int_Glob:            %d\n", Int_Glob);
  fprintf(outbuf,"        should be:   %d\n", 5);
  fprintf(outbuf,"Bool_Glob:           %d\n", Bool_Glob);
  fprintf(outbuf,"        should be:   %d\n", 1);
  fprintf(outbuf,"Ch_1_Glob:           %c\n", Ch_1_Glob);
  fprintf(outbuf,"        should be:   %c\n", 'A');
  fprintf(outbuf,"Ch_2_Glob:           %c\n", Ch_2_Glob);
  fprintf(outbuf,"        should be:   %c\n", 'B');
  fprintf(outbuf,"Arr_1_Glob[8]:       %d\n", Arr_1_Glob[8]);
  fprintf(outbuf,"        should be:   %d\n", 7);
  fprintf(outbuf,"Arr_2_Glob[8][7]:    %d\n", Arr_2_Glob[8][7]);
  fprintf(outbuf,"        should be:   Number_Of_Runs + 10\n");
  fprintf(outbuf,"Ptr_Glob->\n");
  fprintf(outbuf,"  Ptr_Comp:          %ld\n", (long) Ptr_Glob->Ptr_Comp);
  fprintf(outbuf,"        should be:   (implementation-dependent)\n");
  fprintf(outbuf,"  Discr:             %d\n", Ptr_Glob->Discr);
  fprintf(outbuf,"        should be:   %d\n", 0);
  fprintf(outbuf,"  Enum_Comp:         %d\n", Ptr_Glob->variant.var_1.Enum_Comp);
  fprintf(outbuf,"        should be:   %d\n", 2);
  fprintf(outbuf,"  Int_Comp:          %d\n", Ptr_Glob->variant.var_1.Int_Comp);
  fprintf(outbuf,"        should be:   %d\n", 17);
  fprintf(outbuf,"  Str_Comp:          %s\n", Ptr_Glob->variant.var_1.Str_Comp);
  fprintf(outbuf,"        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  fprintf(outbuf,"Next_Ptr_Glob->\n");
  fprintf(outbuf,"  Ptr_Comp:          %ld\n", (long) Next_Ptr_Glob->Ptr_Comp);
  fprintf(outbuf,"        should be:   (implementation-dependent), same as above\n");
  fprintf(outbuf,"  Discr:             %d\n", Next_Ptr_Glob->Discr);
  fprintf(outbuf,"        should be:   %d\n", 0);
  fprintf(outbuf,"  Enum_Comp:         %d\n", Next_Ptr_Glob->variant.var_1.Enum_Comp);
  fprintf(outbuf,"        should be:   %d\n", 1);
  fprintf(outbuf,"  Int_Comp:          %d\n", Next_Ptr_Glob->variant.var_1.Int_Comp);
  fprintf(outbuf,"        should be:   %d\n", 18);
  fprintf(outbuf,"  Str_Comp:          %s\n", Next_Ptr_Glob->variant.var_1.Str_Comp);
  fprintf(outbuf,"        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  fprintf(outbuf,"Int_1_Loc:           %d\n", Int_1_Loc);
  fprintf(outbuf,"        should be:   %d\n", 5);
  fprintf(outbuf,"Int_2_Loc:           %d\n", Int_2_Loc);
  fprintf(outbuf,"        should be:   %d\n", 13);
  fprintf(outbuf,"Int_3_Loc:           %d\n", Int_3_Loc);
  fprintf(outbuf,"        should be:   %d\n", 7);
  fprintf(outbuf,"Enum_Loc:            %d\n", Enum_Loc);
  fprintf(outbuf,"        should be:   %d\n", 1);
  fprintf(outbuf,"Str_1_Loc:           %s\n", Str_1_Loc);
  fprintf(outbuf,"        should be:   DHRYSTONE PROGRAM, 1'ST STRING\n");
  fprintf(outbuf,"Str_2_Loc:           %s\n", Str_2_Loc);
  fprintf(outbuf,"        should be:   DHRYSTONE PROGRAM, 2'ND STRING\n");
  fprintf(outbuf,"\n");

  User_Time = End_Time - Begin_Time;

  if (User_Time < Too_Small_Time)
  {
    fprintf(outbuf,"Measured time too small to obtain meaningful results:");
    fprintf(outbuf,"%10.1f\n",User_Time);
    fprintf(outbuf,"Please increase number of runs\n");
    fprintf(outbuf,"\n");
  }
  else
  {
    Microseconds = User_Time * Mic_secs_Per_Second
                        / (double) Number_Of_Runs;
    Dhrystones_Per_Second = (double) Number_Of_Runs / User_Time;
    Vax_Mips = Dhrystones_Per_Second / 1757.0;

#ifdef ROPT
    fprintf(outbuf,"Register option selected?  YES\n");
#else
    fprintf(outbuf,"Register option selected?  NO\n");
    strcpy(Reg_Define, "Register option not selected.");
#endif
    fprintf(outbuf,"Seconds for run through Dhrystone loops:    ");
    fprintf(outbuf,"%10.1f \n", User_Time);
    fprintf(outbuf,"Microseconds for one run through Dhrystone: ");
    fprintf(outbuf,"%7.1f \n", Microseconds);
    fprintf(outbuf,"Dhrystones per Second:                      ");
    fprintf(outbuf,"%10.1f \n", Dhrystones_Per_Second);
    fprintf(outbuf,"VAX MIPS rating = %10.3f \n",Vax_Mips);
    fprintf(outbuf,"\n");
    /*
  fprintf(Ap,"\n");
  fprintf(Ap,"Dhrystone Benchmark, Version 2.1 (Language: C)\n");
  fprintf(Ap,"%s\n",Reg_Define);
  fprintf(Ap,"Seconds for run through Dhrystone loops: ");
  fprintf(Ap,"%10.1f \n", User_Time);
  fprintf(Ap,"Microseconds for one loop: %7.1f\n",Microseconds);
  fprintf(Ap,"Dhrystones per second: %10.1f\n",Dhrystones_Per_Second);
  fprintf(Ap,"VAX MIPS rating: %10.3f\n",Vax_Mips);
  fclose(Ap);
*/
  }
	return 0;
}


void
Proc_1 (REG Rec_Pointer Ptr_Val_Par)
    /* executed once */
{
  REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;
                                        /* == Ptr_Glob_Next */
  /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
  /* corresponds to "rename" in Ada, "with" in Pascal           */

  structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob);
  Ptr_Val_Par->variant.var_1.Int_Comp = 5;
  Next_Record->variant.var_1.Int_Comp
        = Ptr_Val_Par->variant.var_1.Int_Comp;
  Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
  Proc_3 (&Next_Record->Ptr_Comp);
    /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp
                        == Ptr_Glob->Ptr_Comp */
  if (Next_Record->Discr == Ident_1)
    /* then, executed */
  {
    Next_Record->variant.var_1.Int_Comp = 6;
    Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp,
           &Next_Record->variant.var_1.Enum_Comp);
    Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
    Proc_7 (Next_Record->variant.var_1.Int_Comp, 10,
           &Next_Record->variant.var_1.Int_Comp);
  }
  else /* not executed */
    structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */


void
Proc_2 (One_Fifty *Int_Par_Ref)
/******************/
    /* executed once */
    /* *Int_Par_Ref == 1, becomes 4 */
{
  One_Fifty  Int_Loc;
  Enumeration   Enum_Loc = Ident_1;

  Int_Loc = *Int_Par_Ref + 10;
  do /* executed once */
    if (Ch_1_Glob == 'A')
      /* then, executed */
    {
      Int_Loc -= 1;
      *Int_Par_Ref = Int_Loc - Int_Glob;
      Enum_Loc = Ident_1;
    } /* if */
  while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */


void
Proc_3 (Rec_Pointer *Ptr_Ref_Par)
/******************/
    /* executed once */
    /* Ptr_Ref_Par becomes Ptr_Glob */
{
  if (Ptr_Glob != Null)
    /* then, executed */
    *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
  Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
} /* Proc_3 */


void
Proc_4 (void) /* without parameters */
/*******/
    /* executed once */
{
  Boolean Bool_Loc;

  Bool_Loc = Ch_1_Glob == 'A';
  Bool_Glob = Bool_Loc | Bool_Glob;
  Ch_2_Glob = 'B';
} /* Proc_4 */


void
Proc_5 (void) 	/* without parameters */
		/* executed once */
{
  Ch_1_Glob = 'A';
  Bool_Glob = false;
} /* Proc_5 */


        /* Procedure for the assignment of structures,          */
        /* if the C compiler doesn't support this feature       */
#ifdef  NOSTRUCTASSIGN
void
memcpy (register char *d, register char *s, register int l)
/* register char   *d; register char   *s; register int    l; */
{
        while (l--) *d++ = *s++;
}
#endif
