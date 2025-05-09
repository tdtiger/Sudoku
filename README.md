C++の練習もかねて数独を解くプログラムを作りました<br>

<h2>問題の入力方法</h2>
sudoku_solver.exeまたはsudoku_solver.cppをコンパイルして得られるファイルを実行すると，以下のような出力が行われます．

    Board from...
    Keyboard : k   File : f
    > 

<p>
キーボードから入力したい場合は，「k」と入力してください．
その後，各マス空白区切りで入力してください．
</p>
<p>
ファイルから入力したい場合は，"data.txt"というファイル名のtxtファイル(各マス空白区切り)を事前に用意しておき，「f」と入力してください．
もし，ファイルが存在しない場合は，すべてのマスが0で埋められた盤面として処理が進みます．
ファイル名については， `FromFile()` 関数内の以下の部分を書き換えることで変更できます．
</p>

    ifstream question("data.txt");

※デフォルトのdata.txtは約2400msで答えが見つかります．

<h2>デモ</h2>
<p>
GitHubPages上で動作する，JavaScriptで書き直したものを公開しました．
ただし，ファイルからの読み込みにしか対応しておらず，結果の出力はコンソールに行われます．
cssでの整形すらしてません．
</p>
リンク：https://tdtiger.github.io/Sudoku/index.html

<h2>実装のだいたいの手順</h2>

1. 盤面を表すデータ構造の決定
1. `PrintBoard()` 関数作成
1. `isValid()` 関数作成
1. `Solve()` 関数作成
1. `FromKeyboard()` 関数， `FromFile()` 関数作成

<h2>予定</h2>
数独の問題を生成する `sudoku_generate.cpp` も作りたい．<br>
↑一応仮完成
