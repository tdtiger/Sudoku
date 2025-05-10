let board = [
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0]
];

function UpdateTable(){
    let table = document.getElementById("sudoku_table");
    for(let row = 0; row < 9; row++){
        for(let col = 0; col < 9; col++){
            let cell = table.rows[row].cells[col];
            if(board[row][col] === 0)
                cell.textContent = " ";
            else
                cell.textContent = board[row][col];
        }
    }
}

let form = document.forms.filein;
form.question.addEventListener('change', function(e){
    let result = e.target.files[0];
    let reader = new FileReader();
    reader.readAsText(result);
    reader.addEventListener('load', function(e){
        board = reader.result.split('\n').map(line => line.split(' ').map(Number));
    });
    reader.addEventListener('loadend', function(e){
        UpdateTable();
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
    let start = performance.now();

    if(Solve())
        console.log("Success!");
    else
        console.log("Faile...");

    let end = performance.now();

    console.log(board.map(row => row.join(" ")).join("\n"));
    UpdateTable();
    document.getElementById("time").textContent = "Time: " + (end - start).toFixed(5) + "ms";
}

let btn = document.getElementById("sub");
btn.addEventListener("click", function(e){
    main();
})