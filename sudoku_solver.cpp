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
        for(int j = 0;j < 9; j++){
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

// 実際に数字を置いていく関数
bool Solve(){
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            // まず，空のマスを探す
            if(board.at(row).at(col) == 0){
                for(int num = 1; num < 10; num++){
                    if(isValid(row, col, num)){
                        // 置ける数字を小さい順にとりあえず置く
                        board.at(row).at(col) = num;
                        if(Solve())
                            return true;
                        // ダメだったらやり直し
                        board.at(row).at(col) = 0;
                    }
                }
                // どの数字も置けなかったら解なし
                return false;
            }
        }
    }
    // 最後までやり切れたらそれが答え
    return true;
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