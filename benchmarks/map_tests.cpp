#include "../include/bst.h"
#include <time.h>
#include <map>
#include <chrono>
#include <fstream> //to write on a file



std::pair<std::map<const int,int>, bst<const int,int>> tree_generator(const int nodes){
    
    bst<const int, int> rand_tree{};
    std::map<const int, int> rand_map{};
    srand (time(NULL)); //random seed
    int* rd_value = new int[nodes];
    for (auto i=0; i<=nodes; ++i) {
        rd_value[i]=std::rand() % 100000;
        auto it = rand_tree.insert(std::pair<const int,int>{rd_value[i],rd_value[i]});
        rand_map[i] = rd_value[i];
    }
    rand_tree.balance(); //balance the tree
    std::pair<std::map<const int,int>, bst<const int,int>>  ret = std::pair<std::map<const int, int>,bst<const int,int>> (rand_map, rand_tree);
    delete[] rd_value;
    return ret;
}

bst<const int,int> unb_tree_generator(const int nodes){
    
    bst<const int, int> rand_tree{};
    srand (time(NULL)); //random seed
    int* rd_value = new int[nodes];
    for (auto i=0; i<=nodes; ++i) {
        rd_value[i]=std::rand() % 100000;
        auto it = rand_tree.insert(std::pair<const int,int>{rd_value[i],rd_value[i]});
    }
//    rand_tree.balance(); //balance the tree

    delete[] rd_value;
    return rand_tree;
}


int main(){

   

    std::vector<int> nodes_range{};
    for (auto i=1000; i<=150000; i+=1000) {
        nodes_range.push_back(i);
    }



    std::vector<bst<const int,int>> vec_trees;
    std::vector<std::map<const int, int>> vec_maps;
    std::vector<bst<const int,int>> vec_trees_unbalanced;

    for (auto& nodes: nodes_range) {
        //create trees with nodes in nodes_range
        vec_maps.push_back(tree_generator(nodes).first);
        vec_trees.push_back(tree_generator(nodes).second);
        vec_trees_unbalanced.push_back(unb_tree_generator(nodes));
    }

    int lookups = 1000;
    double* times_tree{new double[vec_trees.size()-1]{}};
    double* times_tree_unb{new double[vec_maps.size()-1]{}};
    double* times_map{new double[vec_maps.size()-1]{}};
    for (auto i=0; i<vec_trees.size(); ++i) {
        auto elapsed_time_tree = 0.0;
        auto elapsed_time_map = 0.0;
        auto elapsed_time_tree_unb = 0.0;
        for (auto j=1; j<lookups; ++j) {
            auto start_tree = std::chrono::system_clock::now();
            auto it_tree = vec_trees[i].find(std::rand() % 100000);
            auto end_tree = std::chrono::system_clock::now();
            elapsed_time_tree+= std::chrono::duration_cast<std::chrono::nanoseconds>(end_tree - start_tree).count();


            auto start_tree_unb = std::chrono::system_clock::now();
            auto it_tree_unb = vec_trees_unbalanced[i].find(std::rand() % 100000);
            auto end_tree_unb = std::chrono::system_clock::now();
            elapsed_time_tree_unb+= std::chrono::duration_cast<std::chrono::nanoseconds>(end_tree_unb - start_tree_unb).count();

            auto start_map = std::chrono::system_clock::now();
            auto it_map = vec_maps[i].find(std::rand() % 100000);
            auto end_map = std::chrono::system_clock::now();
            elapsed_time_map+= std::chrono::duration_cast<std::chrono::nanoseconds>(end_map - start_map).count();
        }
        times_tree[i] = elapsed_time_tree/double(lookups);
        times_tree_unb[i] = elapsed_time_tree_unb/double(lookups);
        times_map[i] = elapsed_time_map/double(lookups);
    }

    std::ofstream file_times_tree;
    file_times_tree.open("times_tree_balanced.txt");

    std::ofstream file_times_tree_unb;
    file_times_tree_unb.open("times_tree_unbalanced.txt");

    std::ofstream file_times_map;
    file_times_map.open("times_map.txt");

    for (auto i=0;i<vec_trees.size();++i) {
        file_times_tree << nodes_range[i] <<"\t" << times_tree[i] <<"\n";
        file_times_map<< nodes_range[i] <<"\t" << times_map[i] <<"\n";
        file_times_tree_unb << nodes_range[i] <<"\t" << times_tree_unb[i] <<"\n";
    }


    file_times_map.close();
    file_times_tree_unb.close();
    file_times_tree.close();

    delete[] times_tree;
    delete[] times_map;
    delete[] times_tree_unb;
    
    
    /*
     bst<const int,int> bigtest_unb{unb_tree_generator(6e6)}; //for unbalanced
    auto start_tree_unb = std::chrono::system_clock::now();
    auto it_tree_unb = bigtest_unb.find(std::rand() % 100000);
    auto end_tree_unb = std::chrono::system_clock::now();
    auto elapsed_time_tree_unb= std::chrono::duration_cast<std::chrono::nanoseconds>(end_tree_unb - start_tree_unb).count();
    
    bst<const int,int> bigtest_balanced{tree_generator(6e6).second}; //for balanced
    auto start_tree_b = std::chrono::system_clock::now();
    auto it_tree_b = bigtest_balanced.find(std::rand() % 100000);
    auto end_tree_b = std::chrono::system_clock::now();
    auto elapsed_time_tree_balanced= std::chrono::duration_cast<std::chrono::nanoseconds>(end_tree_b - start_tree_b).count();
    
    
    
    std::map<const int,int> bigmap{tree_generator(6e6).first};
    auto start_map = std::chrono::system_clock::now();
    auto it_map = bigmap.find(std::rand() % 100000);
    auto end_map = std::chrono::system_clock::now();
    auto elapsed_time_map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_map - start_map).count();
    
    std::cout <<"BST (balanced): "<< elapsed_time_tree_balanced<<"\t" << "std::map: " << elapsed_time_map<<"\t" <<"BST (unbalanced): " <<elapsed_time_tree_unb;
    
     */
    
    // BST (balanced): 3000    std::map: 5000    BST (unbalanced): 31000
    return 0;
}




