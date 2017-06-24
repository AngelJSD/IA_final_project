#include <iostream>
#include <vector>
#include <random>
#include <time.h>

#define n 5

using namespace std;

vector <vector <float> > Q,R;

void qini(){

    Q.resize(n*n);

    for(int i=0; i<n*n; ++i){
        
        Q[i].resize(n*n);
        
        for(int j=0; j<n*n; ++j){
            
            Q[i][j]=0;
        }
    }

    R.resize(n*n);

    for(int i=0; i<n*n; ++i){
        
        R[i].resize(n*n);
        
        for(int j=0; j<n*n; ++j){
            
            if( (i%n!=0 && j==i-1) || ((i+1)%n!=0 && j==i+1) || (i-n>=0 && j==i-n) || (i+n<n*n && j==i+n) )
                R[i][j]=0;
            else
                R[i][j]=-1;
        }
    }
    cout<<"Iniciado"<<endl;
}

void setGoal(int x, int y){

    int goal=x*n+y;

    if(goal%n !=0) R[goal-1][goal]=100;
    if((goal+1)%n!=0) R[goal+1][goal]=100;
    if(goal-n>=0) R[goal-n][goal]=100;
    if(goal+n<n*n) R[goal+n][goal]=100;

    R[goal][goal]=100;

    cout<<"Goal seteado"<<endl;
}

float maxi(int state){

    float maxi=-1;
    vector<int> posibles;
    for(int i=0; i<n*n; ++i){
        if(R[state][i] !=-1)
            posibles.push_back(i);
    }

    for(int i=0; i<posibles.size(); ++i){

        if(Q[state][posibles[i]]>maxi)
            maxi = Q[state][posibles[i]];
    }

    return maxi;
}

void find_path(int xi, int yi, int xg, int yg){

    int state=xi*n+yi;
    int goal=xg*n+yg;
    int next_state = state;
    
    while(state!=goal){

        float maxi=-1;
        for(int i=0; i<Q[state].size(); ++i){
            if(Q[state][i]>maxi){
                maxi = Q[state][i];
                next_state = i;
            }
        }
        state=next_state;
        cout<<state<<",";
    }
}

void qlearning(int xi, int yi, int xg, int yg){

    int state=xi*n+yi;
    int goal=xg*n+yg;
    int next_state;
    float qant;

    while(state!=goal){

        vector<int> posibles;
        for(int i=0; i<n*n; ++i){
            if(R[state][i] !=-1)
                posibles.push_back(i);
        }

        bool rul[100];
        for(int i=0; i<2; ++i) rul[i]=1;
        for(int i=2; i<100; ++i) rul[i]=0;

        if(rul[rand()%100]){
            next_state = posibles[rand() % posibles.size()];
            cout<<"aleatorio";
        }
        else{
            
            float aux=maxi(state);
            vector<int> new_posibles;
            for(int i=0; i<posibles.size(); ++i){
                if(Q[state][posibles[i]]==aux) new_posibles.push_back(posibles[i]);
            }
            next_state = new_posibles[rand() % new_posibles.size()];
        }
        qant = Q[state][next_state];
        Q[state][next_state] = R[state][next_state] + 0.8*maxi(next_state);

        /*if(qant == Q[state][next_state] && Q[state][next_state] != 0) {find_path(state/n, state%n, 4, 4);
        cout<<endl;}*/

        state = next_state;

        //cout<<"estado: "<<state<<" actualizo: "<<Q[state][next_state]<<endl;
        cout<<state<<",";
        
    }
    cout<<endl<<endl;
}

int qlearning_step(int state, int ini, int goal){

    int next_state;
    if(state==goal) state=ini;

    vector<int> posibles;
    for(int i=0; i<n*n; ++i){
        if(R[state][i] !=-1)
            posibles.push_back(i);
    }

    /*bool rul[100];
    for(int i=0; i<2; ++i) rul[i]=1;
    for(int i=2; i<100; ++i) rul[i]=0;

    if(rul[rand()%100]){
        next_state = posibles[rand() % posibles.size()];
        cout<<"aleatorio";
    }
    else{*/
        
        float aux=maxi(state);
        vector<int> new_posibles;
        for(int i=0; i<posibles.size(); ++i){
            if(Q[state][posibles[i]]==aux) new_posibles.push_back(posibles[i]);
        }
        next_state = new_posibles[rand() % new_posibles.size()];
    //}
    Q[state][next_state] = R[state][next_state] + 0.8*maxi(next_state);

    return next_state;

    //cout<<"estado: "<<state<<" actualizo: "<<Q[state][next_state]<<endl;
    //cout<<state<<",";
}

/*
int main(){

    srand(time(NULL));
    ini();
    setGoal(4, 4);

    cout<<"Aprendiendo..."<<endl;

    for(int i=0; i<5; ++i){
        cout<<"vuelta: "<<i<<endl;
        qlearning(2, 1, 4, 4);
        
    }
    
    for(int i=0; i<n*n; ++i){
        
        for(int j=0; j<n*n; ++j){
            
            cout<<Q[i][j]<<",";
        }
        cout<<endl;
    }

    //find_path(2, 1, 4, 4);
    

    return 0;
}*/