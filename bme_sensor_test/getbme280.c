/*
Modified by Mehul Patel  

Author : Frank M.
reference : https://github.com/fm4dd/pi-bme280
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include "getbme280.h"

int verbose = 0;
int outflag = 0;
int argflag = 0; // 1=dump, 2=info, 3=reset, 4=data, 5=continuous
char osrs_mode[7] = {0};  // oversampling mode
char pwr_mode[7]  = {0};  // power mode
char iir_mode[4]  = {0};  // IIR filter mode
char stby_time[5] = {0};  // standby time
char senaddr[256] = BME280_ADDR;
char i2c_bus[256] = I2CBUS;
char htmfile[256] = {0};



int main() 
{    
   /* ----------------------------------------------------------- *
    * get current time (now), write program start if verbose      *
    * ----------------------------------------------------------- */
   //time_t tsnow = time(NULL);
   //if(verbose == 1) printf("Debug: ts=[%lld] date=%s", (long long) tsnow, ctime(&tsnow));

   /* ----------------------------------------------------------- *
    * "-a" open the I2C bus and connect to the sensor i2c address *
    * ----------------------------------------------------------- */
   get_i2cbus(i2c_bus, senaddr);
  
  // argflag = 6;
    

   /* ----------------------------------------------------------- *
    *  "-c" continuously read and output compensated sensor data  *
    * 1584280335 Temp=22.76*C Humidity=22.30% Pressure=1002.56hPa *
    * ----------------------------------------------------------- */
   //if(argflag == 5) 
   {
      struct bmecal bmec;
      struct bmedata bmed;
      get_calib(&bmec);

      /* -------------------------------------------------------- *
       * If power mode != NORMAL, set NORMAL for continuous reads *
       * -------------------------------------------------------- */
      if(get_power() != 0x3) 
      {
         set_power(normal);
      }
         time_t tsnow = time(NULL);
         get_data(&bmec, &bmed);
   
         /* ----------------------------------------------------------- *
          * print the formatted output string to stdout (Example below) *
          * ----------------------------------------------------------- */
         printf("%lld Temp=%3.2f*C Humidity=%3.2f%% Pressure=%3.2fhPa\n", 
                (long long) tsnow, bmed.temp_c, bmed.humi_p, bmed.pres_p/100);
   
         if(outflag == 1) {
            /* -------------------------------------------------------- *
             *  Open the html file for writing accelerometer data       *
             * -------------------------------------------------------- */
            FILE *html;
            if(! (html=fopen(htmfile, "w"))) {
               printf("Error open %s for writing.\n", htmfile);
               exit(-1);
            }
            fprintf(html, "<table><tr>\n");
            fprintf(html, "<td class=\"sensordata\">Temperature:<span class=\"sensorvalue\">%3.2f</span></td>\n", bmed.temp_c);
            fprintf(html, "<td class=\"sensorspace\"></td>\n");
            fprintf(html, "<td class=\"sensordata\">Humidity:<span class=\"sensorvalue\">%3.2f</span></td>\n", bmed.humi_p);
            fprintf(html, "<td class=\"sensorspace\"></td>\n");
            fprintf(html, "<td class=\"sensordata\">Pressure:<span class=\"sensorvalue\">%3.2f</span></td>\n", bmed.pres_p);
            fprintf(html, "</tr></table>\n");
            fclose(html);
         }
   } /* End reading continuous data */
}
