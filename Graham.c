#include  <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Point {
     int x;
     int y;
} point;

typedef struct Vector {
    point x;
    point y;
} vector;

vector makeVectorFromPoints(point A, point B){
 vector v;
 v.x = B.x-A.x;
 v.y = B.y=A.y;
 return vector;
}

//a function that calculates the angle between two line segments
    double angle(vector a, vector b){
        
        double aIntensity = sqrt(pow(a.x, 2) + pow(a.y, 2));
        double bIntensity = sqrt(pow(b.x, 2) + pow(b.y, 2));
        int dotProduct = (a.x * b.x) + (a.y * b.y);
        
        return acos(dotProduct/(aIntensity*bIntensity)); 
    }


//some examples
int main(int argc, char **argv){

    
    return 0;
}
