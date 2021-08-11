#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <unordered_map>

using namespace std;


struct Rules{
    vector <pair<string, string>> conclusionList;  //holds variable name of conclusions and conclusion value. Each position should have a matching rule
};

//struct designed to be held in a vector same size as amount of rules
struct Clauses{
    vector <pair<string, string>> clauses;  //holds a variable name and it's value (use clauses.pushback(make_pair(variablename, value)) when pushing onto vector)
};                                          


string Attacks_BW(Rules, vector<Clauses>, unordered_map <string, string>&);
void Prevention_FW(string, vector<Clauses>, Rules, unordered_map <string, string>&);
void getRules(Rules&, vector<Clauses>&);
void instaniate(unordered_map <string, string>&, string);

int main(){
    string attack; //the type of attack
    Rules rules; //
    vector <Clauses> clausesToRules;  //a vector to hold a clauses struct for each rule, should be same size and match up with rulesList
    clausesToRules.resize(30);
    getRules(rules, clausesToRules);
    unordered_map <string, string> variableMap; //holds variables to instantiate, varibale name is key
 
  
    attack = Attacks_BW(rules, clausesToRules,variableMap);
    Prevention_FW(attack,clausesToRules,rules,variableMap);

}

/*
    Attacks_BW: A backward chaining function to decide what typ of attack we are experiencing. 
    We know the conclusion is always the attack variable so the rules with the conclusion variable 'attack" are put on the stack 
    We instantiate variables until the correct answer is found starting with the type of problem (computer or network). 
    i.e. What are you having trouble with? (network or computer)
    The rules with the correct issue variable are put on the stack then starting form the first rule, we check and instantiate variables until proper attack type is found
*/
string Attacks_BW(Rules rules, vector <Clauses> clausesToRules, unordered_map <string, string> &variableMap){
    cout<<"Backwardchaining Start!\n";
    string conclusion = "attack";
    string attack = "";
    queue<int> conclusionStack; //holds position of rule in conclusion stack
    bool clausesTrue = true;

    //gets position of all rules containing proper conclusion and pushes onto stack
    
    cout<<"Finding rules with conclusion variable 'attack'...\n";
    for(int i = 0; i < rules.conclusionList.size(); i++){
        if(rules.conclusionList[i].first.compare(conclusion)==0){ 
            conclusionStack.push(i);
        }
    }
    
    //iterate through stack, finding variables, instantiating them to reach correct attack type. 
    //if a variable is instantiated and does not match the rule, that rule is taken off the stack and the next is compared until variables match
    while(!conclusionStack.empty()){
        clausesTrue = true;

        for(int i = 0; i < clausesToRules[conclusionStack.front()].clauses.size(); i++){  //loops trough variables of specific rule to instantiate and compare
            if(variableMap.count(clausesToRules[conclusionStack.front()].clauses[i].first) < 1){
                instaniate(variableMap, clausesToRules[conclusionStack.front()].clauses[i].first);
            }
            
            //checks if instantiaed variable value matches rule value, if not, it breaks for loop and pops stack
            cout << "Comparing intilized " << clausesToRules[conclusionStack.front()].clauses[i].first <<
                " variable with rule " << clausesToRules[conclusionStack.front()].clauses[i].first << " variable\n";
            if(variableMap[clausesToRules[conclusionStack.front()].clauses[i].first].compare(clausesToRules[conclusionStack.front()].clauses[i].second) != 0){
                clausesTrue = false;
                cout << "Comparison false\n";

                break;
            }
            cout << "Comparison true\n";
        }
        cout << "\n";
        if(clausesTrue){
            attack = rules.conclusionList[conclusionStack.front()].second;
            break;
        }else{
            cout << "Removing rule " << conclusionStack.front() << " from queue\n";
            conclusionStack.pop();
        }
        cout << "\n";
    }

    

    cout << "The attack you are experiencing is a(n) " << attack << " attack.\n\n";
    cout << "\n";
    return attack;
}
/*
    Prevention_FW(): a forward chaining function to decide best solution to problem. 
    Recieves first variable, which is the attack type from the backward chaining program.

*/
void Prevention_FW(string attack, vector <Clauses> clausesToRules,Rules rules, unordered_map <string, string> &variableMap) { //step 1
    cout<<"Forwardchaining Start!\n";
    string suggestion;
    queue<string> conclusionQueue;
    int rulePointer = 0;

    bool matchFound = true;
    bool trueClauses = true;
    
    //step 2: identified attack variable is pushed onto condition variable queue and value is marked on variable list
    cout << "Adding attack type " << attack << "to the queue\n\n";
    conclusionQueue.push(attack);
    variableMap.emplace("attack", attack);

    while (!conclusionQueue.empty()) {
        while (matchFound) {
            matchFound = false;
            trueClauses = true;
            //step 3: search clause variable list for matching variable name.
            for (int i = rulePointer; i < clausesToRules.size(); i++) {
                //if match is found, place rule number onto clause variable pointer
                if (clausesToRules[i].clauses[0].second.compare(attack) == 0) {
                    cout << "matching rule found\n";
                    rulePointer = i;
                    matchFound = true;
                    break;
                } 
            }
            cout << "\n";
            //step 4: instantiate all variables in the if clause of the rule that are not already instantiated
            for (int i = 1; i < clausesToRules[rulePointer].clauses.size(); i++) {

                if (variableMap.count(clausesToRules[rulePointer].clauses[i].first) < 1) {
                    instaniate(variableMap, clausesToRules[rulePointer].clauses[i].first);
                }
                cout << "Comparing initialized " << clausesToRules[rulePointer].clauses[i].first <<
                    " variable with rule " << clausesToRules[rulePointer].clauses[i].first << " variable\n";
                if (variableMap[clausesToRules[rulePointer].clauses[i].first].compare(clausesToRules[rulePointer].clauses[i].second) != 0) {
                    trueClauses = false;
                    cout << "Comparison false\n";
                    rulePointer++;
                }
                cout << "Comparison true\n";
            }
            cout << "\n";
            //step5: if all IF clauses are true, invoke then clause and push onto queue
            
            if (trueClauses) {
                cout << "invoking THEN clause: " << rules.conclusionList[rulePointer].first << "\n";
                conclusionQueue.pop();
                conclusionQueue.push(rules.conclusionList[rulePointer].second);
                break;
            }
            
        }
        cout << "\n";
        //step 6: when no more matching variables are found, pop that variable off the queue
        suggestion = conclusionQueue.front();
        cout << "Done with " << suggestion << "\n\n";
        conclusionQueue.pop();
    }
    //step 7: when queue is empty, end of process, print suggestion value.
    cout << "The recommended suggestion is: " << suggestion << "\n";
}

/*
    Instantiate(): instantiates a variable
    will have prompts to user based off of variable name recieved to fill variable
*/
void instaniate(unordered_map <string, string>& variableMap, string variable){
    string answer;
    if(variable.compare("issue") == 0){
        cout << "What are you having problems with? Enter computer or network: ";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else if(variable.compare("visible") == 0){
        cout << "Can you see anything on your screen? (yes/no): ";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else if(variable.compare("actions")==0){
        cout << "Is your computer doing stuff on its own? (yes/no): ";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else if(variable.compare("openprograms") == 0){
        cout << "Can you open programs? (yes/no): ";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else if(variable.compare("networktype") == 0){
        cout << "what kind of network do you have? (work/personal)";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else if(variable.compare("changedfiles") == 0){
        cout << "did your files change without your doing? (yes/no)";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else if(variable.compare("commonpass") == 0){
        cout << "do you share passwords? (yes/no)";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else if(variable.compare("people") == 0){
        cout << "do you share this device/network with other people? (yes/no)";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else if(variable.compare("listshow") == 0){
        cout << "does your network show on the list of networks? (yes/no)";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else if(variable.compare("serviceload") == 0){
        cout << "do the internet service act as if they are going to loadup? (yes/no)";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else if(variable.compare("showbefore") == 0){
        cout << "did you have a connection before the issue started? (yes/no)";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }else{
        cout << "Is the problem " << variable << ": (yes/no)";
        cin >> answer;
        variableMap.emplace(variable, answer);
    }

}
/*
    getRules: Rules are saved in a text file and need loaded in and applied to knowledge base, clauses should be loaded into vector in order
    So every clauses and value between if and then should be loaded into the clausausesOfRules as a seperatere variable value pair
    every conclusion should be loaded into the conclusionList vector with a value matching the number of mariables in it's rule
    every possible variable name is loaded into the variableNames vector
    Each rule should be loaded into the ruleList for easy printing
    all input must be converted to lower case
*/
void getRules(Rules& rules, vector<Clauses>& clausesToRules){
    cout<<"Loading in conclusions\n";
    fstream fin;
    fin.open("conclusions.txt");
    string word1;
    string word2;
    while(fin >> word1){
        fin>>word2;
        rules.conclusionList.push_back(make_pair(word1,word2));
    }
    fin.close();
    cout<<"Loading in clauses\n";
    fin.open("clauses.txt");
    int counter = 0;
    while(fin >> word1){
        if(word1 != "1"){
            fin>>word2;
            
            clausesToRules[counter].clauses.push_back(make_pair(word1,word2));
        }
        if(word1 == "1"){
            counter++;
        }
    }
    fin.close();
    
}