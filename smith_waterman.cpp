#include <bits/stdc++.h>

using namespace std;

struct point{
    int x,y;
};

string s1="AGTCTTGACCTCAGGAGAT", s2="CTTGACCTCAGGAGATGG";

int score[20][20],high_score=0;

vector<point> trace[20][20],seq_end;

vector<string> ansA,ansB;

void dfs(int x,int y,string ans1,string ans2){
    if(score[x][y]==0){
        reverse(ans1.begin(),ans1.end());
        reverse(ans2.begin(),ans2.end());
        ansA.push_back(ans1);
        ansB.push_back(ans2);
        return;
    }
    for(int i=0;i<trace[x][y].size();i++){
        if(trace[x][y][i].x==x)ans1+="_";
        else if(trace[x][y][i].x==x-1)ans1+=s1[x-1];
        if(trace[x][y][i].y==y)ans2+="_";
        else if(trace[x][y][i].y==y-1)ans2+=s2[y-1];
        dfs(trace[x][y][i].x,trace[x][y][i].y,ans1,ans2);
    }
}

int main()
{
    for(int i=1;i<=s1.length();i++){
        for(int j=1;j<=s2.length();j++){
            if(s1[i-1]==s2[j-1]){
                if(score[i-1][j-1]+2>=score[i][j-1]-2 && score[i-1][j-1]+2>=score[i-1][j]-2){
                    score[i][j]=score[i-1][j-1]+2;
                    trace[i][j].push_back({i-1,j-1});
                    if(score[i][j-1]-2==score[i-1][j-1]+2)trace[i][j].push_back({i,j-1});
                    if(score[i-1][j]-2==score[i-1][j-1]+2)trace[i][j].push_back({i-1,j});
                }else if(score[i-1][j]>=score[i][j-1]){
                    score[i][j]=score[i-1][j]-2;
                    trace[i][j].push_back({i-1,j});
                    if(score[i-1][j]==score[i][j-1])trace[i][j].push_back({i,j-1});
                }else{
                    score[i][j]=score[i][j-1]-2;
                    trace[i][j].push_back({i,j-1});
                }
            }
            else{
                if(score[i-1][j-1]-1>=score[i][j-1]-2 && score[i-1][j-1]-1>=score[i-1][j]-2 && score[i-1][j-1]-1>0){
                    score[i][j]=score[i-1][j-1]-1;
                    trace[i][j].push_back({i-1,j-1});
                    if(score[i][j-1]-2==score[i-1][j-1]-1)trace[i][j].push_back({i,j-1});
                    if(score[i-1][j]-2==score[i-1][j-1]-1)trace[i][j].push_back({i-1,j});
                }else if(score[i-1][j]>=score[i][j-1] && score[i-1][j]-2>0){
                    score[i][j]=score[i-1][j]-2;
                    trace[i][j].push_back({i-1,j});
                    if(score[i-1][j]==score[i][j-1])trace[i][j].push_back({i,j-1});
                }else if(score[i][j-1]-2>0){
                    score[i][j]=score[i][j-1]-2;
                    trace[i][j].push_back({i,j-1});
                }
            }
            if(score[i][j]>high_score){
                high_score=score[i][j];
                seq_end.clear();
                seq_end.push_back({i,j});
            }else if(score[i][j]==high_score)seq_end.push_back({i,j});
        }
    }
    for(int i=0;i<seq_end.size();i++){
        int x=seq_end[i].x,y=seq_end[i].y;
        dfs(x,y,"","");
    }
    for(int i=0;i<ansA.size();i++)
        cout<<i+1<<": "<<ansA[i]<<' '<<ansB[i]<<'\n';
    return 0;
}
