#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <thread>

void C(std::vector<std::vector<int>>& res, const std::vector<int>& sorted_array, const int k, const int last,
       const int it = -1, const int cnt = 1, std::vector<int> to_add = std::vector<int>()){
    to_add.push_back(-1);
    for(int i = it + 1; i < sorted_array.size(); ++i){
        if(i == last) break;
        if(i == it || sorted_array[i] != sorted_array[i - 1]) {
            if (cnt == k) {
                to_add[cnt - 1] = sorted_array[i];
                res.push_back(to_add);
            } else {
                to_add[cnt - 1] = sorted_array[i];
                C(res, sorted_array, k, -2, i, cnt + 1, to_add);
            }
        }
    }
}

void A(std::vector<std::vector<int>>& res, const std::vector<int>& sorted_array, const int k, const int last,
       const int it = -1, const int cnt = 1, std::vector<int> to_add = std::vector<int>()){
    to_add.push_back(-1);
    for(int i = it + 1; i < sorted_array.size(); ++i){
        if(i == last) break;
        if(i == it || sorted_array[i] != sorted_array[i - 1]) {
            if (cnt == k) {
                to_add[cnt - 1] = sorted_array[i];
                do {
                    res.push_back(to_add);
                } while(std::next_permutation(to_add.begin(), to_add.end()));
            } else {
                to_add[cnt - 1] = sorted_array[i];
                A(res, sorted_array, k, -2, i, cnt + 1, to_add);
            }
        }
    }
}

std::vector<std::vector<int>> C_With_Multithreading(const std::vector<int>& array, const int k_size_of_selection = 1,
                            const int amount_of_threads = 1){
    std::vector<std::vector<int>> res;
    auto sorted_array = array;
    std::sort(sorted_array.begin(), sorted_array.end());
    std::thread* Threads = new std::thread[amount_of_threads];
    auto* res_personal = new std::vector<std::vector<int>>[amount_of_threads];
    for(int i = 0; i < amount_of_threads; ++i){
        int start = sorted_array.size() * i / amount_of_threads;
        int finish = sorted_array.size() * (i + 1) / amount_of_threads;
        Threads[i] = std::thread(C, std::ref(res_personal[i]), std::ref(sorted_array), k_size_of_selection,
                                 finish, start - 1, 1, std::vector<int>());
    }
    for(int i = 0; i < amount_of_threads; ++i){
        Threads[i].join();
        for(auto& v : res_personal[i]){
            res.push_back(v);
        }
    }
    return res;
}

std::vector<std::vector<int>> A_With_Multithreading(const std::vector<int>& array, const int k_size_of_selection = 1,
                           const int amount_of_threads = 1){
    std::vector<std::vector<int>> res;
    auto sorted_array = array;
    std::sort(sorted_array.begin(), sorted_array.end());
    std::thread* Threads = new std::thread[amount_of_threads];
    auto* res_personal = new std::vector<std::vector<int>>[amount_of_threads];
    for(int i = 0; i < amount_of_threads; ++i){
        int start = sorted_array.size() * i / amount_of_threads;
        int finish = sorted_array.size() * (i + 1) / amount_of_threads;
        Threads[i] = std::thread(A, std::ref(res_personal[i]), std::ref(sorted_array), k_size_of_selection,
                                 finish, start - 1, 1, std::vector<int>());
    }
    for(int i = 0; i < amount_of_threads; ++i){
        Threads[i].join();
        for(auto& v : res_personal[i]){
            res.push_back(v);
        }
    }
    return res;
}