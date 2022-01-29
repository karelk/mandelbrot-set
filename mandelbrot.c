#include <stdio.h>
#include <complex.h>

#define ITERATIONS 1535		// DEFAULT 1535
//#define STEP  0.0000005		// DEFAULT  0.002
#define STEP  0.0000005		// DEFAULT  0.002
#define IMAX  0.1962000		// DEFAULT  1
#define IMIN  0.1912000		// DEFAULT -1
#define RMAX -1.1621500		// DEFAULT  1
#define RMIN -1.1656855		// DEFAULT -2


unsigned int iterate(complex k) {
 
  complex z=0;
  unsigned int j=0;

  while ((j++ < ITERATIONS) && (cabs(z) < 2))
    z=(z*z + k);
      
  return (cabs(z) > 2) ? j : 0;       
}


int main(int argc, char *argv[]) {

complex c;
unsigned char rgb[3] = {0,0,0};
unsigned int pixel,width=0,height=0;
unsigned long red=0, violet=0, yellow=0, white=0, blue=0, green=0;
FILE *fh=fopen("head.pnm","w");
FILE *fg=fopen("mandelbrotset.raw","w");


  for (c=(IMAX*I); cimag(c) > IMIN; c=(c-STEP*I)) {
     width=0;             

     for (c=(c+RMIN); creal(c) < RMAX; c=(c+STEP)) {
        width++;
        pixel=iterate(c); 

        if (pixel < 256) {  // 000000 - FF0000
           rgb[0] = pixel; rgb[1]=0; rgb[2]=0; red++;
        }else
           if (pixel < 512) { // FF0000 - FF00FF
              rgb[0]=255; rgb[1]=0; rgb[2]=(pixel-256); violet++;
           }else
              if (pixel < 768) { // FF00FF - FFFF00
                 rgb[0]=255; rgb[1]=pixel-512; rgb[2]=767-pixel; yellow++;
              }else
                 if (pixel < 1024) { //FFFF00 - FFFFFF
                    rgb[0]=255; rgb[1]=255; rgb[2]=pixel-768; white++;
                 }else  // FFFFFF - 0000FF
                    if (pixel < 1280) {
                       rgb[0]=1279-pixel; rgb[1]=1279-pixel; rgb[2]=255; blue++;
                    }else { // 0000FF - 00FFFF
                       rgb[0]=0; rgb[1]=pixel-1280; rgb[2]=255; green++;
                    } 
                                 
        fwrite(&rgb,3,1,fg);
        
     } // END "RE" FORCYCLE
     
     c=cimag(c)*I; // SET RE TO ZERO
     
     if (++height % 2)
        printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bgenerating Mandelbrot set: %.1f%%", (double) ((100*height*STEP) / (IMAX-IMIN)) );
   
  } // END "IM" FORCYCLE

  fprintf(fh, "P6\n%d %d\n255\n", width, height);
  
  fclose(fg);
  fclose(fh);

  printf("\n   red=%d\nviolet=%d\nyellow=%d\n white=%d\n  blue=%d\n green=%d\n", red, violet, yellow, white, blue, green);  

}
