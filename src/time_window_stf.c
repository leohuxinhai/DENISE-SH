/*------------------------------------------------------------------------
 *   Apply time damping (after Brossier (2009))                                 
 *   last update 31/08/11, D.Koehn
 *   modified    02/02/12, S.Heider
 *  ----------------------------------------------------------------------*/
#include "fd.h"

void time_window_stf(float **sectiondata, int iter, int ntr_glob, int ns, int ishot){

/* declaration of variables */
extern float DT;
extern int MYID;
extern int POS[3];
extern float GAMMA, TWLENGTH_PLUS, TWLENGTH_MINUS, DT;
extern char PICKS_FILE[STRING_SIZE];
int READ_PICKED_TIMES;
char pickfile_char[STRING_SIZE];
float time, dump, dump1, taper, taper1;
float *picked_times1;
int i, j, h;

FILE *fptime;

picked_times1 = vector(1,ntr_glob);

/* read picked first arrival times from external pick file */
/* ------------------------------------------------------- */

sprintf(pickfile_char,"%s%i.dat",PICKS_FILE,ishot);

fptime=fopen(pickfile_char,"r");
if (fptime == NULL) {
err(" picks_?.dat could not be opened !");
}

  for(i=1;i<=ntr_glob;i++){
    fscanf(fptime,"%f",&dump);
    picked_times1[i] = dump + TWLENGTH_PLUS;
  }

fclose(fptime);

/* calculate RMS */
for(i=1;i<=ntr_glob;i++){
      for(j=1;j<=ns;j++){
      
         time = (float)(j * DT);
         
         dump1  = time-picked_times1[i]; 
         taper1 = exp(-GAMMA*dump1*dump1);
	 
         if(time>=picked_times1[i]){
           sectiondata[i][j] = sectiondata[i][j] * taper1;
         }                                    
           
      }     
}

free_vector(picked_times1,1,ntr_glob);

} /* end of function time_window.c */
