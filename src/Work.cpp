//
// Created by edward on 2021/6/10.
//

#include "Work.h"
#include "json.hpp"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;
using nlohmann::json;

Work::Work(const std::string &input)
    : buf(input) {}

string generate_data(int node_num, int edge_num) {
    srand(time(nullptr));
    json data = json::object();
    data["links"] = json::array();
    data["nodes"] = json::array();
    json &nodes = data["nodes"];
    json &links = data["links"];
    for (int i = 1; i <= node_num; ++i) {
        json node = json::object();
        node["id"] = i;
        nodes.push_back(node);
    }
    set<pair<int, int>> link_hash;
    int u, v;
    while (edge_num--) {
        u = rand() % node_num + 1;
        v = rand() % node_num + 1;
        if (u > v) swap(u, v);
        if (link_hash.count({u, v})) {
            ++edge_num;
            continue;
        }
        link_hash.insert({u, v});
        json link = json::object();
        link["source"] = u;
        link["target"] = v;
        links.push_back(link);
    }
    return data.dump(4);
}

std::string Work::operator()() {
    istringstream is(buf);
    int node_num, edge_num;
    is >> node_num >> edge_num;
    return generate_data(node_num, edge_num) + "\n";
}