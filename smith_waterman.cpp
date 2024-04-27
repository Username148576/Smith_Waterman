#include <bits/stdc++.h>

using namespace std;

struct point{
    int x,y;
};

string s1="HEAGAWGHEE", s2="PAWHEAE";

int score[20][20],high_score=0;

bool trace[20][20][3]={false}, visual[20][20]={false};

vector<point> seq_end;

vector<string> ansA,ansB;

//回朔取得最佳序列
void dfs(int x,int y,string ans1,string ans2){
    if(score[x][y]==0){
        reverse(ans1.begin(),ans1.end());
        reverse(ans2.begin(),ans2.end());
        ansA.push_back(ans1);
        ansB.push_back(ans2);
        return;
    }
    visual[x][y]=1;
    if(trace[x][y][0]==1)dfs(x-1,y-1,ans1+s1[x-1],ans2+s2[y-1]);
    if(trace[x][y][1]==1)dfs(x-1,y,ans1+s1[x-1],ans2+"_");
    if(trace[x][y][2]==1)dfs(x,y-1,ans1+"_",ans2+s2[y-1]);
}

int main()
{
    //Smith Waterman Algorithm
    for(int i=1;i<=s1.length();i++){
        for(int j=1;j<=s2.length();j++){
            if(s1[i-1]==s2[j-1]){
                if(score[i-1][j-1]+2>=score[i][j-1]-2 && score[i-1][j-1]+2>=score[i-1][j]-2){
                    score[i][j]=score[i-1][j-1]+2;
                    trace[i][j][0]=1;   //match
                    if(score[i][j-1]-2==score[i-1][j-1]+2)trace[i][j][2]=1; //gap
                    if(score[i-1][j]-2==score[i-1][j-1]+2)trace[i][j][1]=1; //gap
                }else if(score[i-1][j]>=score[i][j-1]){
                    score[i][j]=score[i-1][j]-2;
                    trace[i][j][1]=1;   //gap
                    if(score[i-1][j]==score[i][j-1])trace[i][j][2]=1;   //gap
                }else{
                    score[i][j]=score[i][j-1]-2;
                    trace[i][j][2]=1;   //gap
                }
            }
            else{
                if(score[i-1][j-1]-1>=score[i][j-1]-2 && score[i-1][j-1]-1>=score[i-1][j]-2 && score[i-1][j-1]-1>0){
                    score[i][j]=score[i-1][j-1]-1;
                    trace[i][j][0]=1;   //mismatch
                    if(score[i][j-1]-2==score[i-1][j-1]-1)trace[i][j][2]=1; //gap
                    if(score[i-1][j]-2==score[i-1][j-1]-1)trace[i][j][1]=1; //gap
                }else if(score[i-1][j]>=score[i][j-1] && score[i-1][j]-2>0){
                    score[i][j]=score[i-1][j]-2;
                    trace[i][j][1]=1;   //gap
                    if(score[i-1][j]==score[i][j-1])trace[i][j][2]=1;   //gap
                }else if(score[i][j-1]-2>0){
                    score[i][j]=score[i][j-1]-2;
                    trace[i][j][2]=1;   //gap
                }
            }
            //當前最佳序列的尾端index
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
    //顯示表格及回朔
    cout<<"         ";
    for(int i=0;i<s1.length();i++)cout<<s1[i]<<"   ";
    cout<<"\n\n";
    cout<<"    ";
    for(int i=0;i<=s1.length();i++)printf("%2d  ",score[i][0]);
    cout<<"\n";
    for(int i=1;i<=s2.length();i++){
        cout<<"      ";
        for(int j=1;j<=s1.length();j++){
            if(visual[j][i]==1){
                if(trace[j][i][0]==1)cout<<" ↖";
                else cout<<"  ";
                if(trace[j][i][2]==1)cout<<" ↑";
                else cout<<"  ";
            }else cout<<"    ";
        }
        cout<<'\n'<<s2[i-1]<<"   ";
        for(int j=0;j<=s1.length();j++){
            if(visual[j][i]==1 && trace[j][i][1])cout<<" ←";
            else if(j!=0) cout<<"  ";
            printf("%2d",score[j][i]);
        }
        cout<<"\n";
    }
    cout<<"\n\n";
    //輸出最佳序列
    for(int i=0;i<ansA.size();i++)
        cout<<i+1<<": "<<ansA[i]<<' '<<ansB[i]<<'\n';
    return 0;
}
