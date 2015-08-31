#include <stdio.h>
#include <assert.h>
#include <cstdlib>

enum AType {
    QFINDWT_QUNION = 0,
    QUNION,
    WT_QUNION,
    AType_LEN
};
class UnionFind {
    private:
        int num_elements;
        int* elements;

    public:
        AType type;
        
        UnionFind (int num );
        ~UnionFind();
        void join (int x, int y);
        int is_connected (int x, int y);
        void print();
        void wt_join (int x, int y);
        int root (int x);
};