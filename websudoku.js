let board = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
];

let form = document.forms.filein;
form.question.addEventListener('change', function(e){
    let result = e.target.files[0];
    let reader = new FileReader();
    reader.readAsText(result);
    reader.addEventListener('load', function(e){
        board = reader.result.split('\n').map(line => line.split(' ').map(Number));
    });
});

function isValid(row, col, num){
    for(let i = 0; i < 9; i++){
        if(board[row][i] === num || board[i][col] === num)
            return false;
    }

    for(let i = 0; i < 3; i++){
        for(let j = 0; j < 3; j++){
            if(board[row - row % 3 + i][col - col % 3 + j] === num)
                return false;
        }
    }

    return true;
}

function Solve(){
    for(let row = 0; row < 9; row++){
        for(let col = 0; col < 9; col++){
            if(board[row][col] === 0){
                for(let num = 1; num <= 9; num++){
                    if(isValid(row, col, num)){
                        board[row][col] = num;
                        if(Solve())
                            return true;
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

function main(){
    if(Solve())
        console.log("Success!");
    else
        console.log("Faile...");

    console.log(board.map(row => row.join(" ")).join("\n"));
}

let btn = document.getElementById("sub");
btn.addEventListener("click", function(e){
    main();
})