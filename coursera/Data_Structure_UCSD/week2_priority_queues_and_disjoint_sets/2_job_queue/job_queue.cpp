#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  struct Job_queue
  {
    int worker;
    long long available_time;

    Job_queue(int worker, long long available_time)
      : worker(worker), available_time(available_time){

      } 
  };
  struct CompareJob{
    bool operator()(Job_queue const& p1, Job_queue const& p2){
      if (p1.available_time < p2.available_time){
        return false;
      }else if (p1.available_time == p2.available_time){
        return p1.worker > p2.worker;
      }else{
        return true;
      }
    }
  };
  


  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    // assigned_workers_.resize(jobs_.size());
    // start_times_.resize(jobs_.size());
    // vector<long long> next_free_time(num_workers_, 0);
    // for (int i = 0; i < jobs_.size(); ++i) {
    //   int duration = jobs_[i];
    //   int next_worker = 0;
    //   for (int j = 0; j < num_workers_; ++j) {
    //     if (next_free_time[j] < next_free_time[next_worker])
    //       next_worker = j;
    //   }
    //   assigned_workers_[i] = next_worker;
    //   start_times_[i] = next_free_time[next_worker];
    //   next_free_time[next_worker] += duration;
    // }
    std::priority_queue<Job_queue, vector<Job_queue>, CompareJob> q;
    for (int i = 0; i< num_workers_; i++){
      assigned_workers_.push_back(i);
      start_times_.push_back(0);
      q.push(Job_queue(i,jobs_[i]));
    }
    for (int i = num_workers_; i<jobs_.size(); i++){
      assigned_workers_.push_back(q.top().worker);
      start_times_.push_back(q.top().available_time);
      q.push(Job_queue(q.top().worker,q.top().available_time + jobs_[i]));
      q.pop();
    }

  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
