#include <stdio.h>
#include <stdlib.h>
#include <math.h>



typedef struct Point {
     int x;
     int y;
} point;

typedef struct AnglePoint {
 point *p;   
 double angle;
} anglePoint;

point *points;


point* simplePolygon(point *points, int n);
point makeVectorFromPoints(point A, point B);
double angle(point a, point b);
point* simplePolygon(point *points, int n);
int comparator(const void *p, const void *q);
double distance(point *a, point *b);



point makeVectorFromPoints(point A, point B){
 point vector;
 vector.x = B.x-A.x;
 vector.y = B.y-A.y;
 return vector;
}

//a function that calculates the angle between two line segments
    double angle(point a, point b){
        
        double aIntensity = sqrt(pow(a.x, 2) + pow(a.y, 2));
        double bIntensity = sqrt(pow(b.x, 2) + pow(b.y, 2));
        int dotProduct = (a.x * b.x) + (a.y * b.y);
        
        return acos(dotProduct/(aIntensity*bIntensity)); 
    }

//returns an array of points which form a polygon when visited respectively
point* simplePolygon(point *points, int n){
    //p0 is a point with the lowest y coordinate (in case of many, choose one with the greatest x)
    int minIndex = 0, i;
    for(i=1; i<n;i++){
     if(points[i].y < points[minIndex].y)
            minIndex = i;
     else if(points[i].y == points[minIndex].y)
             minIndex = (points[i].x < points[minIndex].x) ? minIndex : i; 
    }
    //putting a point from minIndex position to a[0]
    point tmp = points[0];
    points[0] = points[minIndex];
    points[minIndex] = tmp;
    
    double *angles = malloc(sizeof(double)*n);
    if(angles == NULL){
     fprintf(stderr, "Unsuccessfull allocation, try again");   
     exit(1);
    }
    
    //x-axis vector
    point e1;
    e1.x = 1;
    e1.y = 0;
    //determining angles between lines p0 and pi and x-axis vector
    for(i=1; i<n;i++){
     angles[i-1] = angle(makeVectorFromPoints(points[0], points[i]), e1);   
    }
    
      qsort((void*)(points+1), n-1, sizeof(point), comparator); 
    
        return points;
    
}


int comparator(const void *p, const void *q) 
{ 
    // Get the values at given addresses 
    anglePoint* l = (anglePoint *)p; 
    anglePoint* r = (anglePoint *)q; 
    
    if((l->angle)>(r->angle))
        return 1;
    else if ((l->angle)<(r->angle))
        return -1;
        else
            if(distance(points,l->p)>distance(points,r->p))
                return 1;
            else
                return -1;
   
} 


double distance(point *a, point *b){
    
        return sqrt(pow(abs((a->x)-(b->x)),2)+pow(abs((a->x)-(b->y)),2));
}



//some examples
int main(int argc, char **argv){

    
    return 0;
}