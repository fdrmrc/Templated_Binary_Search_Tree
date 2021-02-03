#include "../include/bst.h"
#include <time.h>
#include <map>
#include <chrono>




std::pair<std::map<const int,int>, bst<const int,int>> tree_generator(const int nodes){
    
    bst<const int, int> rand_tree{};
    std::map<const int, int> rand_map{};
    srand (time(NULL)); //random seed
    int* rd_value = new int[nodes];
    for (auto i=0; i<=nodes; ++i) {
        rd_value[i]=std::rand() % 50000;
        auto it = rand_tree.insert(std::pair<const int,int>{rd_value[i],rd_value[i]});
        rand_map[i] = rd_value[i];
    }
    rand_tree.balance(); //balance the tree
    std::pair<std::map<const int,int>, bst<const int,int>>  ret = std::pair<std::map<const int, int>,bst<const int,int>> (rand_map, rand_tree);
    return ret;
}


int main(){

   
    
    std::vector<int> nodes_range{};
    for (auto i=1; i<=20000; i+=200) {
        nodes_range.push_back(i);
    }
    
    
    std::vector<bst<const int,int>> vec_trees{};
    std::vector<std::map<const int, int>> vec_maps{};
    for (auto& nodes: nodes_range) {
        //create trees with nodes in nodes_range
        vec_maps.push_back(tree_generator(nodes).first);
        vec_trees.push_back(tree_generator(nodes).second);
    }
    
    int lookups = 1000;
    double* times_tree{new double[vec_trees.size()-1]{}};
    double* times_map{new double[vec_maps.size()-1]{}};
    for (auto i=0; i<vec_trees.size(); ++i) {
        auto elapsed_time_tree = 0.0;
        auto elapsed_time_map = 0.0;
        for (auto j=1; j<lookups; ++j) {
            auto start_tree = std::chrono::system_clock::now();
            auto it = vec_trees[i].find(std::rand() % 5000);
            auto end_tree = std::chrono::system_clock::now();
            elapsed_time_tree+= std::chrono::duration_cast<std::chrono::nanoseconds>(end_tree - start_tree).count();
            
            auto start_map = std::chrono::system_clock::now();
            auto it_map = vec_maps[i].find(std::rand() % 5000);
            auto end_map = std::chrono::system_clock::now();
            elapsed_time_map+= std::chrono::duration_cast<std::chrono::nanoseconds>(end_map - start_map).count();

        }
        times_tree[i] = elapsed_time_tree/double(lookups);
        times_map[i] = elapsed_time_map/double(lookups);
    }
    
    for (auto i=0;i<vec_trees.size();++i) {
        std::cout << times_tree[i]   << "\t" << times_map[i]<<"\n";
    }

    
    return 0;
}


