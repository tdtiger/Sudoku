#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<random>
#include<chrono>
using namespace std;
using namespace chrono;

void PrintBoard();

// 盤面を保存する変数
vector<vector<int>> board(9, vector<int>(9, 0));

// 盤面を引数で指定されたファイルにかき出す関数
void Export(string filename){
    // 拡張子を付加
    filename += ".txt";

    // ファイルを開く準備
    ofstream out(filename);
    if(!out.is_open()){
        cout << "file open error!" << endl;
        return;
    }

    // 盤面をファイルに書き出す
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            out << board.at(i).at(j) << " ";
        }
        out << endl;
    }
    out.close();
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
bool Generate(default_random_engine &engine){
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

            // numsをシャッフルする
            shuffle(nums.begin(), nums.end(), engine);

            // 空のマスに数字を入れていく
            if(board.at(row).at(col) == 0){
                // シャッフルされた数字を順に試す
                for(int i = 0; i < 9; i++){
                    if(isValid(row, col, nums.at(i))){
                        board.at(row).at(col) = nums.at(i);
                        if(Generate(engine))
                            return true;
                        // ダメだったらやり直し
                        board.at(row).at(col) = 0;
                    }
                }
                // どの数字も置けなかったらダメ
                return false;
            }
        }
    }
    // 最後までやり切れたらOK
    return true;
}

// 盤面の適当な位置を空白にする関数
void Dig(int n, default_random_engine &engine){
    // 空白の数を管理する変数
    int cnt = 0;

    // 盤面にn個空白を作る
    while(cnt <= n){
        int row = engine() % 9;
        int col = engine() % 9;
        if(board.at(row).at(col) != 0){
            board.at(row).at(col) = 0;
            cnt++;
        }
    }
}

int main(){
    int n;
    // 空白の数を受け取る
    cout << "Please input the number of blanks." << endl;
    cout << "> ";
    cin >> n;

    string filename;
    // 出力先の名前を受け取る
    cout << "Please input filiname." << endl << "!! The file extension(.txt) will be added automatically." << endl;
    cout << ">";
    cin >> filename;

    // 乱数生成器の準備
    random_device rd;
    default_random_engine engine(rd());

    // 実行開始時間
    auto start = steady_clock::now();

    Generate(engine);
    Dig(n, engine);

    // 実行終了時間
    auto end = steady_clock::now();

    PrintBoard();
    Export(filename);
    cout << "Exported to " << filename << ".txt" << endl;

    auto time = duration_cast<milliseconds>(end - start).count();
    cout << "time:" << time << "ms" << endl;
}