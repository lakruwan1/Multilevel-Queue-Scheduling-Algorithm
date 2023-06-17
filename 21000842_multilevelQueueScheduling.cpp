#include<iostream>
#include <vector>
#include<algorithm>
#include<queue>
#include <vector>
#include <iomanip>
using namespace std;

#define qt_rr 4
 
typedef struct node{
    int p_id;
    int priority;
    int burst_time;
    int remaining_time;
    int turn_around_time;
    int waiting_time;

}process;

int total_time=0;
queue<process> q0, q1, q2, q3;
vector<process> completed0, completed1, completed2, completed3;

void RR(){
    int time_in_this_round=0;
    while(!q0.empty() && time_in_this_round<20){
        process process_in_this_round = q0.front();
        int rem_time_of_this_roundP = q0.front().remaining_time;
        int this_round_process_run_time, if_process_run_AfterTime;
        
        if(rem_time_of_this_roundP < qt_rr){
            this_round_process_run_time = rem_time_of_this_roundP;
        }else if(rem_time_of_this_roundP == qt_rr){
            this_round_process_run_time = qt_rr;
        }else if(rem_time_of_this_roundP > qt_rr && rem_time_of_this_roundP < 20){
            this_round_process_run_time = qt_rr;
        }else if(rem_time_of_this_roundP > qt_rr && rem_time_of_this_roundP > 20){
            this_round_process_run_time = 20;
        }

        if_process_run_AfterTime = time_in_this_round + this_round_process_run_time;
        if(if_process_run_AfterTime>20){
            this_round_process_run_time = 20 - time_in_this_round;
        }

        time_in_this_round = time_in_this_round + this_round_process_run_time;
        rem_time_of_this_roundP = rem_time_of_this_roundP - this_round_process_run_time;
        q0.front().remaining_time = rem_time_of_this_roundP;


        if(q0.front().remaining_time>0){
            process temp = q0.front();
            q0.push(temp);
            q0.pop();
        }else{
            q0.front().turn_around_time = total_time + time_in_this_round;
            q0.front().waiting_time = q0.front().turn_around_time - q0.front().burst_time;
            process temp = q0.front();
            completed0.push_back(temp);
            q0.pop();
        }

    }
    total_time = total_time + time_in_this_round;
}

bool my_cmp(process a1, process b1)
{
    return a1.burst_time < b1.burst_time;
}

queue<process> sortQ(queue<process> qu){
    vector<process> vec;
    queue<process> sorted;

    while(!qu.empty()){
        process temp = qu.front(); qu.pop();
        vec.push_back(temp);
        }

    sort(vec.begin(), vec.end(), my_cmp);
  
    for(int i=0; i<vec.size(); i++){
        process temp = vec.at(i);
        sorted.push(temp);
    }

    return sorted;
}

void SJF1(){
    queue<process> sortedQ = sortQ(q1);
    q1 = sortedQ;
    int time_in_this_round = 0;

    while(!q1.empty() && time_in_this_round < 20){
        process temp = q1.front();
        int if_process_run_After_time = time_in_this_round + temp.remaining_time;

        if(if_process_run_After_time <= 20){
            time_in_this_round = time_in_this_round + temp.remaining_time;
            temp.turn_around_time = total_time + time_in_this_round;
            temp.waiting_time = temp.turn_around_time - temp.burst_time;
            process temp1 = temp;
            completed1.push_back(temp1);
            q1.pop();
        }else{
            q1.front().remaining_time = q1.front().remaining_time - (20-time_in_this_round);
            time_in_this_round = 20;
            process temp1 = q1.front();
            q1.push(temp1);
            q1.pop();
        }
    }
    total_time = total_time + time_in_this_round; 
}

void SJF2(){
    queue<process> sortedQ = sortQ(q2);
    q2 = sortedQ;
    int time_in_this_round = 0;

    while(!q2.empty() && time_in_this_round < 20){
        process temp = q2.front();
        int if_process_run_After_time = time_in_this_round + temp.remaining_time;

        if(if_process_run_After_time <= 20){
            time_in_this_round = time_in_this_round + temp.remaining_time;
            temp.turn_around_time = total_time + time_in_this_round;
            temp.waiting_time = temp.turn_around_time - temp.burst_time;
            process temp1 = temp;
            completed2.push_back(temp1);
            q2.pop();
        }else{
            q2.front().remaining_time = q2.front().remaining_time - (20-time_in_this_round);
            time_in_this_round = 20;
            process temp1 = q2.front();
            q2.push(temp1);
            q2.pop();
        }
    }
    total_time = total_time + time_in_this_round; 
}

void FCFS(){
        int time_in_this_round = 0;
        while(!q3.empty() && time_in_this_round < 20){
        process temp = q3.front();
        int if_process_run_After_time = time_in_this_round + temp.remaining_time;

        if(if_process_run_After_time <= 20){
            time_in_this_round = time_in_this_round + temp.remaining_time;
            temp.turn_around_time = total_time + time_in_this_round;
            temp.waiting_time = temp.turn_around_time - temp.burst_time;
            process temp1 = temp;
            completed3.push_back(temp1);
            q3.pop();
        }else{
            q3.front().remaining_time = q3.front().remaining_time - (20-time_in_this_round);
            time_in_this_round = 20;
            process temp1 = q3.front();
            q3.push(temp1);
            q3.pop();
        }
    }
    total_time = total_time + time_in_this_round; 
}

int main(){

    int no_of_process;
    process p;

    cout << "Enter the number of processes: ";
    cin >> no_of_process;
    cout << endl;

    for(int i=0; i<no_of_process; i++){
        cout << "Process " << i << "|\n";
        cout << "  Priority(0-3): ";
        cin >> p.priority;
        cout << "  Burst time(s): ";
        cin >> p.burst_time;
        p.remaining_time=p.burst_time;
        p.p_id=i;
        
        switch(p.priority){
            case 0:
                q0.push(p);
                break;
            case 1:
                q1.push(p);
                break;
            case 2:
                q2.push(p);
                break;
            case 3:
                q3.push(p);
                break;
        }
    }

    while(!q0.empty() || !q1.empty() || !q2.empty() || !q3.empty()){
        RR();
        SJF1();
        SJF2();
        FCFS();
    }
    cout << endl << endl;
    cout << "Processes of Q0 (Round robin)\n";
    cout << " process_ID | " << "Priority(Q_number) | " << "Burst_time | " << "Turn_around_time | " << "Waiting_time | " << endl;
    cout << "            | " << "                   | " << "           | " << "                 | " << "             | " << endl;

    for(int i=0; i<completed0.size(); i++){
        cout << "    "<< setw(3) << setfill('0') <<completed0.at(i).p_id <<"     |";
        cout << "         "<< setw(3) << setfill('0') <<completed0.at(i).priority <<"        |";
        cout << "     "<< setw(3) << setfill('0') <<completed0.at(i).burst_time <<"    |";
        cout << "        "<< setw(3) << setfill('0') <<completed0.at(i).turn_around_time <<"       |";
        cout << "      "<< setw(3) << setfill('0') <<completed0.at(i).waiting_time <<"     |"<< endl;
    }
    cout << endl << endl;
    cout << "Processes of Q1 (Shortest Job first01)\n";
    cout << " process_ID | " << "Priority(Q_number) | " << "Burst_time | " << "Turn_around_time | " << "Waiting_time | " << endl;
    cout << "            | " << "                   | " << "           | " << "                 | " << "             | " << endl;
        for(int i=0; i<completed1.size(); i++){
        cout << "    "<< setw(3) << setfill('0') <<completed1.at(i).p_id <<"     |";
        cout << "         "<< setw(3) << setfill('0') <<completed1.at(i).priority <<"        |";
        cout << "     "<< setw(3) << setfill('0') <<completed1.at(i).burst_time <<"    |";
        cout << "        "<< setw(3) << setfill('0') <<completed1.at(i).turn_around_time <<"       |";
        cout << "      "<< setw(3) << setfill('0') <<completed1.at(i).waiting_time <<"     |"<< endl;
    }

    cout << endl << endl;
    cout << "Processes of Q2 (Shortest Job first02)\n";
    cout << " process_ID | " << "Priority(Q_number) | " << "Burst_time | " << "Turn_around_time | " << "Waiting_time | " << endl;
    cout << "            | " << "                   | " << "           | " << "                 | " << "             | " << endl;
        for(int i=0; i<completed2.size(); i++){
        cout << "    "<< setw(3) << setfill('0') <<completed2.at(i).p_id <<"     |";
        cout << "         "<< setw(3) << setfill('0') <<completed2.at(i).priority <<"        |";
        cout << "     "<< setw(3) << setfill('0') <<completed2.at(i).burst_time <<"    |";
        cout << "        "<< setw(3) << setfill('0') <<completed2.at(i).turn_around_time <<"       |";
        cout << "      "<< setw(3) << setfill('0') <<completed2.at(i).waiting_time <<"     |"<< endl;
    }
    cout << endl << endl;
    cout << "Processes of Q3 (First Come first Serve)\n";
    cout << " process_ID | " << "Priority(Q_number) | " << "Burst_time | " << "Turn_around_time | " << "Waiting_time | " << endl;
    cout << "            | " << "                   | " << "           | " << "                 | " << "             | " << endl;
        for(int i=0; i<completed3.size(); i++){
        cout << "    "<< setw(3) << setfill('0') <<completed3.at(i).p_id <<"     |";
        cout << "         "<< setw(3) << setfill('0') <<completed3.at(i).priority <<"        |";
        cout << "     "<< setw(3) << setfill('0') <<completed3.at(i).burst_time <<"    |";
        cout << "        "<< setw(3) << setfill('0') <<completed3.at(i).turn_around_time <<"       |";
        cout << "      "<< setw(3) << setfill('0') <<completed3.at(i).waiting_time <<"     |"<< endl;
    }

    return 0;
}