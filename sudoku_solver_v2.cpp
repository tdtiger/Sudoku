#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
using namespace std;
using namespace chrono;

void PrintBoard();

// 盤面を保存する変数
vector<vector<int>> board(9, vector<int>(9, 0));

// 盤面をキーボードから受け取る関数
void FromKeyboard(){
    cout << "Please input board (vecant is '0')" << endl;
    cout << "------------------" << endl << endl;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cin >> board.at(i).at(j);
        }
    }

    cout << endl << "------------------" << endl;
}

// 盤面をファイルから受け取る関数
void FromFile(){
    // 問題ファイルを開く準備
    ifstream question("data.txt");
    if(!question.is_open()){
        cout << "data isn't available." << endl;
        return;
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            question >> board.at(i).at(j);
            if(question.fail())
                cout << "error!" << endl;
        }
    }

    question.close();
}

// 盤面を表示する関数
void PrintBoard(){
    cout << endl;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cout << board.at(i).at(j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// row行col列にnumを置けるかを判定する関数
bool isValid(int row, int col, int num){
    // 行，列のチェック
    for(int i = 0; i < 9; i++){
        if(board.at(row).at(i) == num || board.at(i).at(col) == num)
            return false;
    }

    // ブロック内のチェック
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board.at(row - row % 3 + i).at(col - col % 3 + j) == num)
                return false;
        }
    }

    return true;
}

// あるマスに置ける数字の候補を求める関数
vector<int> GetCandidates(int row, int col){
    vector<int> cs;
    for(int num = 1; num <= 9; num++){
        if(isValid(row, col, num)){
            cs.push_back(num);
        }
    }

    return cs;
}

// 実際に数字を置いていく関数
bool Solve(){
    int targetRow = -1, targetCol = -1, MinCount = 10;
    vector<int> candidates;
    // まず，空のマスを探す
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            if(board.at(row).at(col) == 0){
                // そのマスに置ける数字の候補数を求める
                vector<int> c = GetCandidates(row, col);
                // 暫定最小のものより小さければ更新
                if(c.size() < MinCount){
                    MinCount = c.size();
                    targetRow = row;
                    targetCol = col;
                    candidates = c;
                }

                // 候補数1なら即採用
                if(MinCount == 1)
                    break;
                // 候補数0ならアウト
                else if(MinCount == 0)
                    return false;
            }
        }
    }
    // 最後までやり切れたらそれが答え
    if(targetRow == -1 && targetCol == -1)
        return true;

    for(int num : candidates){
        // 候補の数字を小さい順にとりあえず置く
        board.at(targetRow).at(targetCol) = num;
        if(Solve())
            return true;
        // ダメだったらやり直し
        board.at(targetRow).at(targetCol) = 0;
    }

    return false;
}

int main(){
    char c;
    cout << "Board from..." << endl;
    cout << "Keyboard : k   File : f" << endl;
    cout << "> ";
    cin >> c;

    // キーボード，あるいはcsvファイルから問題を読み込み
    if(c == 'k')
        FromKeyboard();
    else if(c == 'f')
        FromFile();

    PrintBoard();

    // 実行開始時間
    auto start = steady_clock::now();

    if(Solve())
        cout << "Success!" << endl;
    else
        cout << "Failed..." << endl;

    // 実行終了時間
    auto end = steady_clock::now();

    PrintBoard();

    auto time = duration_cast<milliseconds>(end - start).count();
    cout << "time:" << time << "ms" << endl;
}