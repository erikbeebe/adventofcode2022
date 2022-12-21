#include <bits/stdc++.h>
#include <sstream>

using namespace std;

const bool debug = false;
enum OPERATION_TYPES { ADD, MULTIPLY };
typedef OPERATION_TYPES OPERATION_TYPES;
struct Monkey {
    vector<uint64_t> items;
    //char operation_type;
    OPERATION_TYPES operation_type;
    int multiplier;
    int test; // divisible by
    int true_target;
    int false_target;
};
map<int, Monkey> monkey_map;

class Monkeys {
    unordered_map<int, uint64_t> monkey_inspections;
    int rounds = 0;
    map<int, Monkey> monkey_mapper;
    
    public:
        Monkeys(int rounds) {
            this->rounds = rounds;
            monkey_mapper.insert(monkey_map.begin(), monkey_map.end());
        }

        uint64_t run_monkeys(bool enable_division) {
            uint64_t worry_level;

            // compute product of divisor tests for p2
            int monkey_product = monkey_mapper[0].test;
            for (int i=1; i<monkey_mapper.size(); ++i) {
               monkey_product *= monkey_mapper[i].test;
            }

            for (int round=0; round < this->rounds; round++) {
                for (const auto &[key, value] : monkey_mapper) {
                    Monkey cur = monkey_mapper[key];
                    vector<uint64_t> local_items;
                    local_items = cur.items;

                    for (auto &item : local_items) {
                        incr_monkey_inspections(key);

                        worry_level = item;
                        uint64_t multiplier;

                        multiplier = (monkey_mapper[key].multiplier == 0) ? item : get_multiplier(key);

                        if (monkey_mapper[key].operation_type == MULTIPLY) {
                            // multiply
                            worry_level *= multiplier;
                        } else if (monkey_mapper[key].operation_type == ADD) {
                            worry_level += multiplier;
                        }

                        // Part 1 == divide by 3, Part 2 == monkey divisor product
                        if (enable_division) {
                            worry_level /= 3;
                        } else {
                            worry_level = worry_level % monkey_product;
                        }

                        if (worry_level % monkey_mapper[key].test == 0) {
                            move_item(key, monkey_mapper[key].true_target, item, worry_level);
                        } else {
                            move_item(key, monkey_mapper[key].false_target, item, worry_level);
                        }
                    }
                }

                //cout << "ROUND " << round << endl;
                if (debug) {
                    for (const auto &[key, value] : monkey_mapper) {
                        for (auto &item : value.items) {
                            cout << item << " ";
                        }
                        cout << endl;
                    }

                    for (auto &m : monkey_inspections) {
                        cout << "Monkey: " << m.first << " " << m.second << endl;
                    }
                }
            }
            return top_two_monkeys();
        }

        uint64_t get_multiplier(int monkey) {
            return monkey_mapper[monkey].multiplier;
        }

        void move_item(int source_monkey, int target_monkey, uint64_t source_item, uint64_t target_item) {
            if (debug) cout << "Removing item " << source_item << " from monkey " << source_monkey << ", placing target_item " << target_item << " to target monkey " << target_monkey << endl;
            monkey_mapper[target_monkey].items.emplace_back(target_item);
            monkey_mapper[source_monkey].items.erase(
                remove(
                    monkey_mapper[source_monkey].items.begin(),
                    monkey_mapper[source_monkey].items.end(), source_item
                ),
                 monkey_mapper[source_monkey].items.end());
        }

        void incr_monkey_inspections(int monkey_id) {
            if (monkey_inspections.find(monkey_id) == monkey_inspections.end()) {
                monkey_inspections.insert({monkey_id, 1});
            } else {
                monkey_inspections[monkey_id]++;
            }
        }

        uint64_t top_two_monkeys() {
            vector<uint64_t> top_monkeys;
            for (auto &m : monkey_inspections) {
                top_monkeys.push_back(m.second);
            }
            sort(top_monkeys.begin(), top_monkeys.end(), greater<int>());
            return top_monkeys[0] * top_monkeys[1];
        }
};

void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](unsigned char ch) { return !std::isspace(ch); }));
}
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

void make_monkey(ifstream &infile, int monkey_id) {
    Monkey m;
    string line;
    string tmp;

    while (getline(infile, line)) {
        if (line.empty()) {
            monkey_map.insert({monkey_id, m});
            return;
        }

        ltrim(line);
        
        if (line.rfind("Starting") == 0) {
            line.erase(remove(line.begin(), line.end(), ','), line.end());
            istringstream ss(line.substr(16));

            while (ss >> tmp) {
                m.items.push_back(stoi(tmp));
            }
        } else if (line.rfind("Operation") == 0) {
            // Operation: new = old + 8
            istringstream ss(line.substr(21));
            //ss >> m.operation_type;
            ss >> tmp;
            m.operation_type = (tmp[0] == '+') ? ADD : MULTIPLY;

            ss >> tmp;
            m.multiplier = isdigit(tmp[0]) ? stoi(tmp) : 0;
        } else if (line.rfind("Test") == 0) {
            istringstream ss(line.substr(19));
            ss >> tmp;

            m.test = stoi(tmp);
        } else if (line.rfind("If true") == 0) {
            istringstream ss(line.substr(25));
            ss >> tmp;
            m.true_target = stoi(tmp);
        } else if (line.rfind("If false") == 0) {
            istringstream ss(line.substr(26));
            ss >> tmp;
            m.false_target = stoi(tmp);
        }
    }
}

int main() {
    string filename = "input.txt";
    ifstream infile (filename);
    string monkey;


    while (getline(infile, monkey)) { 
        int monkey_id = stoi(monkey.substr(7));
        make_monkey(infile, monkey_id);
    }

    Monkeys m(20);
    cout << "Part 1: " << m.run_monkeys(true) << endl;

    Monkeys m2(10000);
    cout << "Part 2: " << m2.run_monkeys(false) << endl;
};