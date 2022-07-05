#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct coord{
   long double x, y, z;
};

coord sum(coord a, coord b){
   coord ret;
   ret.x = a.x + b.x;
   ret.y = a.y + b.y;
   ret.z = a.z + b.z;
   return ret;
}

coord sum(coord a, long double b){
   coord ret;
   ret.x = a.x + b;
   ret.y = a.y + b;
   ret.z = a.z + b;
   return ret;
}

coord mul(coord a, coord b){
   coord ret;
   ret.x = a.x * b.x;
   ret.y = a.y * b.y;
   ret.z = a.z * b.z;
   return ret;
}

coord mul(coord a, long double b){
   coord ret;
   ret.x = a.x * b;
   ret.y = a.y * b;
   ret.z = a.z * b;
   return ret;
}

vector<coord> sum(vector<coord> a, vector<coord> b){
      vector<coord> ret(a.size());
      for(int i = 0; i < a.size(); i++)
         ret[i] = sum(a[i], b[i]);
      return ret;
}

vector<coord> sum(vector<coord> a, long double b){
      vector<coord> ret(a.size());
      for(int i = 0; i < a.size(); i++)
         ret[i] = sum(a[i], b);
      return ret;
}

vector<coord> mul(vector<coord> a, long double mult){
      vector<coord> ret(a.size());
      for(int i = 0; i < a.size(); i++)
         ret[i] = mul(a[i], mult);
      return ret;
}

vector<coord> zero(){
   vector<coord> ret(9, {0, 0, 0});
   return ret;
}

long double dotProduct(coord a){
   return a.x*a.x + a.y*a.y + a.z*a.z;
}