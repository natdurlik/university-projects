#include <iostream>
#include <vector>
using namespace std;
typedef  vector<vector<vector<int>>> vec3int;

vec3int next_partition(vec3int partitions, int x) {
    int n=partitions.size();
    vec3int new_partitions(partitions);
    vector<int> v{x};
    for(int i=0;i<n;i++) {
        new_partitions[i].push_back(v);
        for(int j=0;j<partitions[i].size();j++) {
            partitions[i][j].push_back(x);
            new_partitions.push_back(partitions[i]);
            partitions[i][j].pop_back();
        }
    }
    return new_partitions;
}

void print_parts(vec3int partitions) {
    for(int i=0;i<partitions.size();i++) {
        for(int j=0;j<partitions[i].size();j++) {
            cout<<"{";
            for(int z=0;z<partitions[i][j].size();z++) {
                cout<<partitions[i][j][z];
            }
            cout<<"} ";
        }
        cout<<endl;
    }
    cout<<"bell number="<<partitions.size()<<endl;
    cout<<endl;
}

int main()
{
    int n=7;
    vec3int partitions{{{1}}};
  //  print_parts(partitions);
   /* for(int i=2;i<=n;i++) {
        partitions=next_partition(partitions,i);
        print_parts(partitions);
    }*/
    for(int i=2;i<=n;i++) {
        partitions=next_partition(partitions,i);
    }
    print_parts(partitions);
    return 0;
}
