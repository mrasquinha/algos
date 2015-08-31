#include <union.h>

UnionFind::UnionFind (int num)
{
    num_elements = num;
    assert(num_elements>0 && "0 size vector");
    elements = new int[num_elements];
    for (int i=0; i<num_elements; i++)
        elements[i] = i;

    //Dont need this for other algo's; but type is not known
    size = new int[num_elements];
    for (int i=; i<num_elements; i++)
        elements[i] = 1;

}

UnionFind::~UnionFind()
{
    delete elements;
}

void UnionFind::join ( int x, int y)
{
    if(is_connected(x,y)) return;
    if(type == QFIND) {
        int el_x = elements[x];
        int el_y = elements[y];
        for (int i=0; i<num_elements; i++)
        {
            if(elements[i] == el_x)
                elements[i] = el_y;
        }
    }
    else if(type == QUNION) {
        int i = root(x);
        int j = root(y);
        elements[i] = j;
    }
    else if(type == WT_QUNION) {
        int i = root(x);
        int j = root(y);
        if(size[i]<size[j]) {
            elements[i] = j; 
            size[j] += size[i]; 
        }
        else {
            elements[j] = i;
            size[i] += size[j];
        }
    }
    else {
        assert(0);
    }
}

int UnionFind::is_connected ( int x, int y)
{
    switch (type)
    {
        case QUNION:
        case WT_QUNION:
            return ((root(x) == root(y)) ? 1 : 0);
            break;
        case QFIND:
            return (elements[x] == elements[y]) ? 1 : 0;
            break;
        default:
            assert(0 && "Invalid type \n");
    }

}

void UnionFind::print()
{
    for (int i=0; i<num_elements; i++)
        printf("%d ",elements[i]);
    printf("\n");
}

/* Quick Union */
int UnionFind::root(int x) 
{
    return ((elements[x] == x) ? x : root(elements[x]));
}

int main (int argc, char** argv)
{
    if (argc <=1) { 
        printf("Usage: ./union <problem_number> \n");
        exit(1);
    }

    int problem_no = atoi(argv[1]);
    UnionFind* uf = new UnionFind (10);

    switch(problem_no) {
        case 0:
        case 1:
            uf->type = QFIND;
            printf("Problem number 1: ");
            /* Q1 union find */
            uf->join(1,4);
            uf->join(9,4);
            uf->join(6,8);
            uf->join(2,1);
            uf->join(0,4);
            uf->join(3,7);
            break;
        case 2:
            printf("Problem number 2: ");
            uf->type = WT_QUNION;
             /* Q2 Weighted quick union */
            uf->wt_join(7,9);
            uf->wt_join(9,4);
            uf->wt_join(7,0);
            uf->wt_join(8,1);
            uf->wt_join(3,7);
            uf->wt_join(5,6);
            uf->wt_join(5,1);
            uf->wt_join(3,8);
            uf->wt_join(2,6);
            break;
        default:
            assert(0 && "Invalid problem number");
            break;
    }

    uf->print();
    return 0;
}