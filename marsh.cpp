/* Dynamic Programming: Solution Mr K Marsh from Hacker Rank
 * see problem statment at https://www.hackerrank.com/challenges/mr-k-marsh
 * input: marsh format is on the problem statement page
 * output: number indicating the max perimeter of a valid fence
 *         "impossible" if fence cannot be built
 * Eg input:
 4 4
 ..x.
 x...
 .x..
 ....

 * */
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int findGreedyCol(int startRow, int endRow, int startCol, int endCol, 
    vector< vector<bool>>& land) {
  if(startRow==endRow) return 0;
  if(startCol==endCol) return 0;
  int perM = 0;
  int topCol = endCol-1;
  while(startRow>=0 && startCol>=0) {
    int topRow = endRow-1;
    for (; topRow>=startRow; topRow--) {
      if(!land[topRow][topCol]) break;
    }

    //make sure the top row is clean
    topRow++;
    bool topRowClean = true;
    for(int col=topCol; col<endCol; col++) {
      if(!land[topRow][col]) { 
        topRowClean = false;
        break;
      }
    }

    int len1 = endRow-topRow, len2=endCol-topCol; 
    if(len1>0 && len2>0 && topRowClean) {
      perM = max(perM, 2*(len1+len2));
    }
    topCol--;
    if(topCol<startCol) break;
  }
    
  return perM;
}

int findGreedyRow(int startRow, int endRow, int startCol, int endCol, 
    vector< vector<bool>>& land) {
  if(startRow==endRow) return 0;
  if(startCol==endCol) return 0;
  int perM = 0;
  int topRow = endRow-1;
  while(startRow>=0 && startCol>=0) {
    int topCol = endCol-1;
    for (; topCol>=startCol; topCol--) {
      if(!land[topRow][topCol]) break;
    }

    //make sure the top col is clean
    topCol++;
    bool topColClean = true;
    for(int row=topRow; row<endRow; row++) {
      if(!land[row][topCol]) { 
        topColClean = false;
        break;
      }
    }

    int len1 = endRow-topRow, len2=endCol-topCol; 
    if(len1>0 && len2>0 && topColClean) {
      perM = max(perM, 2*(len1+len2));
    }
    topRow--;
    if(topRow<startRow) break;
  }
    
  return perM;
}

int findPerimeter (vector<vector<bool> >& land, int m, int n) {
  int maxP = 0;
  
  // Calculate 2 2D matrices that can tell you if a valid marsh can
  // end at the corner of [i][j]; one for all rows top to botton(nrows)
  // second for all cols left to right(ncols)
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
 
  //first element [0][0]
  if(land[0][0]) { ncols[0][0] = 0; nrows[0][0] = 0; }

  //First row [0][i]
  for (int i=1; i<n; i++) {
    if(land[0][i]) { 
      ncols[0][i] = ncols[0][i-1]+1; 
      nrows[0][i] = 0;
    }
  }

  //First col [i][0]
  for (int i=1; i<m; i++) {
    if(land[i][0]) { 
      ncols[i][0] = 0; 
      nrows[i][0] = nrows[i-1][0]+1;
    }
  }
  
  // remaining matrix
  for (int i=1; i<m; i++) {
    for (int j=1; j<n; j++) {
      if(land[i][j]) {
        ncols[i][j] = ncols[i][j-1]+1;
        nrows[i][j] = nrows[i-1][j]+1;

        //search all valid sub squares
        int startRow = i-nrows[i][j];
        int startCol = j-ncols[i][j];
        int perM = findGreedyCol(startRow, i, startCol, j, land);
        maxP = max(perM, maxP);
        perM = findGreedyRow(startRow, i, startCol, j, land);
        maxP = max(perM, maxP);
      }
    }
  }
  return maxP;
}
    
int main() {
  int m, n;
  cin >> m >>n; cin.ignore();
  vector<vector<bool>> land (m);
  for (int i=0; i<m; i++) {
    vector<bool> l (n, false);
    land[i] = l;
  }
  
  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) { char x; cin >> x; land[i][j] = (bool)(x -'x'); }
  }
  
  int ans = findPerimeter(land, m, n);
  if(ans) cout << ans << endl;
  else cout << "impossible" << endl;
  
  return 0;
}



