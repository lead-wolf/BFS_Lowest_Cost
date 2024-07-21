#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <map>
#include <algorithm> // Thư viện cần thiết cho std::reverse
using namespace std;


// Định nghĩa một trạng thái
struct State {
    char id; // Sử dụng ký tự để biểu diễn tên node
    int cost;

    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

// Định nghĩa đồ thị
map<char, vector<pair<char, int>>> graph = {
    {'s', {{'d', 3}, {'p', 1}, {'e',9}}},
    {'a', {}},
    {'b', {{'a', 2}}},
    {'c', {{'a', 2}}},
    {'d', {{'b', 1}, {'c', 8}, {'e', 2}}},
    {'e', {{'h', 1}, {'r', 9}}},
    {'f', {{'c', 5}, {'g', 5}}},
    {'h', {{'q', 4}, {'p', 4}}},
    {'p', {{'q', 15}}},
    {'q', {{'r', 3}}},
    {'r', {{'f', 5}}}
};

// Hàm để tìm kiếm các trạng thái kế tiếp của một trạng thái
vector<State> successors(const State& s) {
    vector<State> result;
    for (const auto& neighbor : graph[s.id]) {
        result.push_back({neighbor.first, neighbor.second});
    }
    return result;
}

// Hàm tính chi phí giữa hai trạng thái
int cost(const State& s1, const State& s2) {
    for (const auto& neighbor : graph[s1.id]) {
        if (neighbor.first == s2.id) {
            return neighbor.second;
        }
    }
    return numeric_limits<int>::max(); // Trả về giá trị vô cùng nếu không có đường đi
}

// Hàm BFS với chi phí thấp nhất
vector<State> BFS_Lowest_Cost(const State& start, const State& goal) {
    unordered_map<char, State> previous;
    unordered_map<char, int> g;
    priority_queue<State, vector<State>, greater<State>> open_set;
    
    previous[start.id] = { '\0', 0 };
    g[start.id] = 0;
    open_set.push(start);
    
    while (!open_set.empty()) {
        State current = open_set.top();
        open_set.pop();
        
        if (current.id == goal.id) {
            vector<State> path;
            while (current.id != '\0') {
                path.push_back(current);
                current = previous[current.id];
            }
            reverse(path.begin(), path.end()); // Đảo ngược thứ tự các trạng thái trong đường đi
            return path;
        }
        
        for (const State& succ : successors(current)) {
            int tentative_g = g[current.id] + cost(current, succ);
            if (g.find(succ.id) == g.end() || tentative_g < g[succ.id]) {
                previous[succ.id] = current;
                g[succ.id] = tentative_g;
                State next_state = succ;
                next_state.cost = tentative_g;
                open_set.push(next_state);
            }
        }
    }
    
    return {}; // Trả về danh sách rỗng nếu không tìm thấy đường đi
}

int main() {
    State start = {'s', 0}; // Trạng thái bắt đầu
    State goal = {'g', 0};  // Trạng thái đích
    
    vector<State> path = BFS_Lowest_Cost(start, goal);
    
    if (!path.empty()) {
        cout << "Path found:" << endl;
        // for (const State& s : path) {
        //     cout << s.id << " -> " ;
        // }
        for (int i = 0; i < path.size(); i++)
        {
            if (!(i == (path.size()-1)))
            {
                cout << path[i].id << " -> " ;
            }else{
                cout << path[i].id << endl << "With cost: " << path[i].cost;
            }
        }
    } else {
        cout << "No path found." << endl;
    }
    
    return 0;
}
