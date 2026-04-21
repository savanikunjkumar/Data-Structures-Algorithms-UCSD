/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 2
 * Assignment: Job Queue
 *
 * The Problem: Assign M jobs to N parallel worker threads. Threads pick jobs based 
 * on who is free first, breaking ties by thread ID.
 * * The Logic: The naive starter code uses a loop to find the next available worker, 
 * taking O(n * m) time which causes a Time Limit Exceeded (TLE) error. To fix this, 
 * we use a Min-Heap (Priority Queue) to keep track of workers. The heap is ordered 
 * primarily by `next_free_time` and secondarily by `worker_id`. For each job, we 
 * pop the top worker in O(log n) time, assign the job, update their free time, 
 * and push them back into the heap. Total time drops to a blazing fast O(m log n).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Worker {
    int id;
    long long next_free_time;

    // Custom comparator for the Min-Heap.
    // We want the smallest time at the top. If times are equal, smallest ID at the top.
    bool operator>(const Worker& other) const {
        if (next_free_time != other.next_free_time) {
            return next_free_time > other.next_free_time;
        }
        return id > other.id;
    }
};

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
        if (cin >> num_workers_ >> m) {
            jobs_.resize(m);
            for(int i = 0; i < m; ++i)
                cin >> jobs_[i];
        }
    }

    void AssignJobs() {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        
        // Priority Queue (Min-Heap) to track workers
        priority_queue<Worker, vector<Worker>, greater<Worker>> pq;

        // Initialize heap with all workers free at time 0
        for (int i = 0; i < num_workers_; ++i) {
            pq.push({i, 0});
        }

        for (int i = 0; i < jobs_.size(); ++i) {
            // Get the best available worker
            Worker best_worker = pq.top();
            pq.pop();

            // Assign job to this worker
            assigned_workers_[i] = best_worker.id;
            start_times_[i] = best_worker.next_free_time;

            // Update worker's free time and push back to heap
            best_worker.next_free_time += jobs_[i];
            pq.push(best_worker);
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
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    JobQueue job_queue;
    job_queue.Solve();
    
    return 0;
}
