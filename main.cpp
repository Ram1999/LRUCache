#include "lru.h"
#include <string>

int main()
{
    int size = 3;
    int num = 16;
    vector<int> pages = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0};
    LRUCache<int,int> lru(size);
    for (int i=0; i<num; ++i) {
        lru.Get(pages[i]);
    }
    cout << lru.getCount << endl;
    return 0;
}
