struct Edge {
    int target;
    double prob;
};

struct Node {
    int index;
    double prob;
    bool operator<(const Node& rhs) const {
        return prob < rhs.prob;
    }
};
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        // key - node
        // value - vector with edges and their weight
        unordered_map<int, vector<Edge>> graph;
        for(size_t i = 0; i < edges.size(); i++) {
            graph[edges[i][0]].push_back({ edges[i][1], succProb[i] });
            graph[edges[i][1]].push_back({ edges[i][0], succProb[i] });
        }
        
        vector<double> probs(n, 0);
        probs[start_node] = 1;
        priority_queue<Node> nextToProcess;
        nextToProcess.push({start_node, 1});
        
        while(!nextToProcess.empty()) {
            Node toProcess = nextToProcess.top();
            nextToProcess.pop();
            if(toProcess.prob > probs[toProcess.index]) continue;
            if(toProcess.index == end_node) {
                return probs[end_node];
            }

            for(auto& adj: graph[toProcess.index]) {
                double possibleProb = probs[toProcess.index] * adj.prob;
                if(probs[adj.target] < possibleProb) {
                    probs[adj.target] = possibleProb;
                    nextToProcess.push({ adj.target, possibleProb });
                }
            }
        }
        
        return probs[end_node];
    }
};
