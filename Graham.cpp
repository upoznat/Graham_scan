#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

//gcc -o Graham Graham_scan.c -L/path/to/libs -lm


typedef struct Point {

    double x;
    double y;

} point;

typedef struct AnglePoint {

    point *p;
    double angle;

} anglePoint;



point *points;
anglePoint *angles;


point makeVectorFromPoints(point a, point b);
double angle(point a, point b);
void simplePolygon(point *points, int n);
int comparator(const void *p, const void *q);
double distance(point *a, point *b);
int dot(point a, point b);
int perpdot(point a, point b);



//makes vector ab
point makeVectorFromPoints(point a, point b){
 point vector;
 vector.x = b.x-a.x;
 vector.y = b.y-a.y;
 return vector;
}

//a function that calculates a relative(signed) angle between two line segments
    double angle(point a, point b){

        return atan2(perpdot(a,b), dot(a,b));

    }

//reorders an array of points so that they form a polygon when visited respectively
void simplePolygon(point *points, int n){
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

    angles = new anglePoint[n];


    //x-axis vector
    point e1;
    e1.x = 1;
    e1.y = 0;
    //determining angles between lines p0 and pi and x-axis vector
    for(i=1; i<n;i++){
      anglePoint ap;
      ap.p = points+i;
      
      ap.angle = angle(e1,makeVectorFromPoints(points[0], points[i]));
      
     // if(abs(ap.angle-3.14)<0.01)
     // 	ap.angle = 0.0;
      
	  angles[i-1] = ap;
    }

		 for(i=0;i<n;i++)
      	cout<<points[i].x<<" "<<points[i].y<<" "<<endl;
      	
      	for(i=0;i<n-1;i++)
      	cout<<angles[i].angle<<endl;

      qsort((void*)(angles), n-1, sizeof(anglePoint), comparator);
      
      cout<<"posle sorta"<<endl;
      for(i=0;i<n-1;i++)
      	cout<<angles[i].p->x<<" "<<angles[i].p->y<<endl;
      	

}

//comparator function for qsort
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
            if(distance(points,l->p)<distance(points,r->p))
                return 1;
            else
                return -1;

}


double distance(point *a, point *b){

        return sqrt(pow(abs((a->x)-(b->x)),2)+pow(abs((a->x)-(b->y)),2));

}


//dot product of two vectors
int dot(point a, point b){
    return a.x*b.x + a.y*b.y;
}


int perpdot(point a, point b){
    return a.x*b.y-a.y*b.x;
}


//returns a convex hull for points given as input
vector<point> Graham_scan(point *points, int n){
    vector <point> convexHull;
    int i, m;


    convexHull.push_back( points[0] );
    convexHull.push_back(*(angles[0].p));
    convexHull.push_back( *(angles[1].p));
    m=2;
    
     cout<<"KONV OMOTAC:";
			for(vector<point>::iterator it = convexHull.begin(); it<convexHull.end(); ++it) 
  				cout<<it->x<<" "<<it->y<<endl;

	

    for(i=2;i<n-1;i++){
    	
    		cout<<"for:    "<<angle(makeVectorFromPoints(convexHull[m-1], convexHull[m]),
                      makeVectorFromPoints(convexHull[m] ,*(angles[i].p)))<<endl;

          while(angle(makeVectorFromPoints(convexHull[m-1], convexHull[m]),
                      makeVectorFromPoints(convexHull[m] ,*(angles[i].p)))<=0){
                      	
                      

            m--;
            convexHull.pop_back();
          }

            m++;
            convexHull.push_back(*(angles[i].p));
        }
            
            cout<<"KONV OMOTAC:";
			for(vector<point>::iterator it = convexHull.begin(); it<convexHull.end(); ++it) 
  				cout<<it->x<<" "<<it->y<<endl;
   

    return convexHull;

}



//some examples
int main(int argc, char **argv){

//point a,b,c;
//
//a.x = 0, a.y = 0;
//b.x = 1, b.y = 0;
//c.x = 5, c.y = 10;
//
//cout<<  angle(makeVectorFromPoints(b, a),
//              makeVectorFromPoints(a , c));
//
//




  fstream file;
  string filename = "data.txt";
  file.open(filename.c_str());
  int i = 0, n;





  file >> n;
  points = new point[n];

  while(!file.eof()){
      file>>points[i].x;
      file>>points[i].y;
      i++;
  }
  
  simplePolygon(points,n);

vector<point> convexHull = Graham_scan(points, n);


i=1;
cout<<"convexHull";
for(vector<point>::iterator it = convexHull.begin(); it<convexHull.end(); ++it) {
  cout<<//"q"<<i++<<": "<<
   it->x<<" "<<it->y<<endl;
}

    return 0;
}
