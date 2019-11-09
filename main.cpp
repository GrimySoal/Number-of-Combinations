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

void C_With_Multithreading(std::vector<std::vector<int>>& res, const std::vector<int>& sorted_array, const int k,
                            const int amount_of_threads = 1){
    std::thread* Threads = new std::thread[amount_of_threads];
    auto* res_personal = new std::vector<std::vector<int>>[amount_of_threads];
    for(int i = 0; i < amount_of_threads; ++i){
        int start = sorted_array.size() * i / amount_of_threads;
        int finish = sorted_array.size() * (i + 1) / amount_of_threads;
        Threads[i] = std::thread(C, std::ref(res_personal[i]), std::ref(sorted_array), k, finish, start - 1, 1,
                                 std::vector<int>());
    }
    for(int i = 0; i < amount_of_threads; ++i){
        Threads[i].join();
        for(auto& v : res_personal[i]){
            res.push_back(v);
        }
    }
}

int main() {
    srand(time(nullptr));
    int n, k, amount_of_threads;
    std::cin >> n >> k >> amount_of_threads;
    std::vector<int> array(n);
    std::cout << "Array: ";
    for(int i = 0; i < n; ++i){
        array[i] = rand() % 77;
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::vector<std::vector<int>> res;
    std::sort(array.begin(), array.end());
    C_With_Multithreading(res, array, k);
    std::cout << "Combinations: " << std::endl;
    for(auto& u : res){
        for(int el : u){
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}