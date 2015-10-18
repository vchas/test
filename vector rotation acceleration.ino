#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
float accel[3]={0.1,0,1.0};// data will come from the accelerometers
float gravity[3]={0,0,1.0};// always vertically downwards at g = 1.0
float rG[3],rA[3];
float mA[3];

// Angle of rotation will come from RTImuLib
float alpha= 0.1;// some aribitar values for testing
float beta=  0.2;// some aribitar values for testing
float theta = 0.3;// some aribitar values for testing

float R[3][3] =
{
 { cos(alpha)*cos(beta) , cos(alpha)*sin(beta)*sin(theta) - sin(alpha)*cos(theta) , cos(alpha)*sin(beta)*cos(theta) + sin(alpha)*sin(theta)},
 { sin(alpha)*cos(beta) , sin(alpha)*sin(beta)*sin(theta) + cos(alpha)*cos(theta) , sin(alpha)*sin(beta)*cos(theta) - cos(alpha)*sin(theta)},
 {     -1* sin(beta)    ,                  cos(beta) * sin(theta)                 ,               cos(beta) * cos(theta)                   }
};
float det =  R[0][0]*(R[1][1]*R[2][2]-R[1][2]*R[2][1])\
            -R[0][1]*(R[1][0]*R[2][2]-R[1][2]*R[2][0])\
            +R[0][2]*(R[1][0]*R[2][1]-R[1][1]*R[2][0]);

printf(" det= %f\r\n",det);  //for check, should be +1 exactly

rG[0]= gravity[0]*R[0][0] + gravity[1]*R[0][1] + gravity[2]*R[0][2] ;
rG[1]= gravity[0]*R[1][0] + gravity[1]*R[1][1] + gravity[2]*R[1][2] ;
rG[2]= gravity[0]*R[2][0] + gravity[1]*R[2][1] + gravity[2]*R[2][2] ;

rA[0]= accel[0]*R[0][0] + accel[1]*R[0][1] + accel[2]*R[0][2] ;
rA[1]= accel[0]*R[1][0] + accel[1]*R[1][1] + accel[2]*R[1][2] ;
rA[2]= accel[0]*R[2][0] + accel[1]*R[2][1] + accel[2]*R[2][2] ;

mA[0]=rA[0]-rG[0];
mA[1]=rA[1]-rG[1];
mA[2]=rA[2]-rG[2];

printf("A %8.5f %8.5f %8.5f\r\n",accel[0],accel[1],accel[2]);
printf("G %8.5f %8.5f %8.5f\r\n",gravity[0],gravity[1],gravity[2]);
printf("rA %8.5f %8.5f %8.5f\r\n",rA[0],rA[1],rA[2]);
printf("rG %8.5f %8.5f %8.5f\r\n",rG[0],rG[1],rG[2]);
printf("A-G %8.5f %8.5f %8.5f\r\n",mA[0],mA[1],mA[2]);

//rotate modified acceleration back into the Earth frame (use transpose of R)

rA[0]= mA[0]*R[0][0] + mA[1]*R[1][0] + mA[2]*R[2][0] ;
rA[1]= mA[0]*R[0][1] + mA[1]*R[1][1] + mA[2]*R[2][1] ;
rA[2]= mA[0]*R[0][2] + mA[1]*R[1][2] + mA[2]*R[2][2] ;

printf("A-G in Earth frame %8.5f %8.5f %8.5f\r\n",rA[0],rA[1],rA[2]);

   return 0;
}
