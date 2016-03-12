// Solution to the Hacker Rank Mr K marsh problem
// https://www.hackerrank.com/challenges/mr-k-marsh
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int findPerimeter (vector<vector<bool> >& land, int m, int n) {
  int maxP = 0;
  
  vector<vector<int> > ncols (m);
  for (int i=0; i<m; i++) {
    vector<int> l (n, -1);
    ncols[i] = l;
  }
  
  vector<vector<int> > nrows (m);
  for (int i=0; i<m; i++) {
    vector<int> l (n, -1);
    nrows[i] = l;
  }
 

  //first row
  if(land[0][0]) { ncols[0][0] = 0; nrows[0][0] = 0; }
  //First row [0][i]
  for (int i=1; i<n; i++) {
    if(land[0][i]) { 
      ncols[0][i] = ncols[0][i-1]+1; nrows[0][i] = nrows[0][i]=0;
    }
  }
  //First col [i][0]
  for (int i=1; i<m; i++) {
    if(land[i][0]) { 
      ncols[i][0] = 0; 
      nrows[i][0] = nrows[i-1][0]+1;
    }
  }
  
  for (int i=1; i<m; i++) {
    for (int j=1; j<n; j++) {
      int perM = 0;
      if(land[i][j]) { 
        ncols[i][j] = ncols[i][j-1]+1;
        nrows[i][j] = nrows[i-1][j]+1;

        int nr = nrows[i][j], nc=ncols[i][j];
        int stR=i-nr, stC=j-nc;
        while(stR<i && stC<j && nc!=0 && nr!=0) {
          bool rMine=false, cMine=false;
          for (int k=stR; k<i; k++) 
            if(nrows[k][stC]==-1) {stC++; nc--; rMine=true; break;}
          for (int k=stC; nc && k<j; k++) 
            if(ncols[stR][k]==-1) {stR++; nr--; cMine=true; break;}

          if(!rMine && !cMine) {
            printf("Found %d square top=%d %d bottom=%d %d\n", 
                2*(nr+nc), nr,nc, i, j);
            break; // found the top ends
          }
        }
        printf("\n");
        if(nc!=0 && nr!=0) {
          //printf("Update i=%d j=%d nc=%d nr=%d", i, j, nc, nr);
          perM = 2*(nc+nr);
        }
      }
      maxP = max(maxP, perM);
    }
  }
  
  
  cout << "nrow is" << endl;
  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++)
      printf("%02d,",nrows[i][j]);
    cout << endl;
  }
  cout << "ncol is" << endl;
  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++)
      printf("%02d,",ncols[i][j]);
    cout << endl;
  }
     
  return maxP;
}
    
void printMarsh(vector<vector<bool> > land, int m, int n) {
  for(int i=0; i<m; i++) {
    for(int j=0; j<n; j++) {
      printf("%d,", (int)land[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int m, n;
  cin >> m >>n; cin.ignore();
  vector<vector<bool> > land (m);
  for (int i=0; i<m; i++) {
    vector<bool> l (n, false);
    land[i] = l;
  }
  
  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) { char x; cin >> x; land[i][j] = (bool)(x -'x'); }
  }
  
  printMarsh(land, m, n);
  int ans = findPerimeter(land, m, n);
  if(ans) cout << ans << endl;
  else cout << "impossible" << endl;
  
  return 0;
}

