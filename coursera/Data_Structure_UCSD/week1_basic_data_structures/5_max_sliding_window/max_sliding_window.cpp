#include <iostream>
#include <vector>
#include <deque>

using std::cin;
using std::cout;
using std::vector;
using std::max;



void max_sliding_window_naive(vector<int> const & A, int w) {

    std::deque <int> main_queue;
    std::deque <int> tracking_queue;
    
    for (int i = 0; i < w; i++){
        main_queue.push_back(A.at(i));

        if (i==0){
            tracking_queue.push_back(main_queue.back());
        }
        else{
        while(!tracking_queue.empty() && (tracking_queue.back() < main_queue.back())){
            tracking_queue.pop_back();
        }
        tracking_queue.push_back(A.at(i));
        }
    }
    
   
    std::cout << tracking_queue.front() << " ";
    
    for (int i = w; i < A.size(); i++){
        if (main_queue.front() == tracking_queue.front()){
            tracking_queue.pop_front();
        }
        main_queue.pop_front();
        main_queue.push_back(A.at(i));
        while(!tracking_queue.empty() && (tracking_queue.back() < main_queue.back())){
            tracking_queue.pop_back();
        }
        tracking_queue.push_back(A.at(i));
        cout << tracking_queue.front() << " ";
    }



    return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
