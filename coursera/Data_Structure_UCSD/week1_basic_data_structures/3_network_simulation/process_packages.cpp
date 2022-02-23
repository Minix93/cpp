#include <iostream>
#include <queue>
#include <vector>

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
        // write your code here
        //pop from front all the packets which are already processed by the time new packet arrives
        while (!finish_time_.empty() &&  finish_time_.front() <= request.arrival_time) {
            finish_time_.pop();
        }
        //check if buffer is full, if yes, just drop the request
        Response temp_response(false, 0);
        
        if (finish_time_.size() == size_){
            temp_response.dropped = true;
            temp_response.start_time = -1;
        }
        else{
        // check if current queue is empty, time start to process is the arrival time,
        if (finish_time_.empty()){
            temp_response.start_time = request.arrival_time;
        }
        else{
            temp_response.start_time = finish_time_.back();
        }
        finish_time_.push(temp_response.start_time + request.process_time);
        }
        return temp_response;
    }
private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
