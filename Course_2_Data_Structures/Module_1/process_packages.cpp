/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 1
 * Assignment: Network simulation
 *
 * The Problem: Simulate a network router's buffer. Packets arrive at specific times 
 * and take time to process. If the fixed-size buffer is full, drop the incoming packet.
 * * The Logic: We maintain a queue of 'finish times' representing packets currently 
 * in the system. When a new packet arrives, we first pop all packets from the queue 
 * that finished before or exactly at the new arrival time. If the queue size hits the 
 * max buffer size, the packet is dropped. Otherwise, the packet starts either immediately 
 * (if queue is empty) or right after the last packet finishes. We calculate its finish 
 * time, push it to the queue, and return its start time. O(N) total time.
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) {
        // Remove packets that have already finished processing by the time the new one arrives
        while (!finish_time_.empty() && finish_time_.front() <= request.arrival_time) {
            finish_time_.pop();
        }

        // If the buffer is full, drop the packet
        if (finish_time_.size() == size_) {
            return Response(true, -1);
        }

        // Determine the start time for the new packet
        int start_time;
        if (finish_time_.empty()) {
            start_time = request.arrival_time;
        } else {
            // It starts exactly when the last packet in the queue finishes
            start_time = finish_time_.back();
        }

        // Calculate and record its finish time
        int finish_time = start_time + request.process_time;
        finish_time_.push(finish_time);

        return Response(false, start_time);
    }

private:
    int size_;
    queue<int> finish_time_;
};

vector<Request> ReadRequests() {
    vector<Request> requests;
    int count;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

vector<Response> ProcessRequests(const vector<Request> &requests, Buffer *buffer) {
    vector<Response> responses;
    for (int i = 0; i < requests.size(); ++i) {
        responses.push_back(buffer->Process(requests[i]));
    }
    return responses;
}

void PrintResponses(const vector<Response> &responses) {
    for (int i = 0; i < responses.size(); ++i) {
        cout << (responses[i].dropped ? -1 : responses[i].start_time) << "\n";
    }
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int size;
    if (cin >> size) {
        vector<Request> requests = ReadRequests();
        Buffer buffer(size);
        vector<Response> responses = ProcessRequests(requests, &buffer);
        PrintResponses(responses);
    }
    
    return 0;
}
