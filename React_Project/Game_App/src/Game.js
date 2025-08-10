import "./Game.css";
import { useState } from 'react';


function Square({ value, on_SquareClick }) {
    return (
        <button className="square" onClick={on_SquareClick}>
            {value}
        </button>
    );
}

function Board({ xIsNext, squares, onPlay }) {
    function handle_click(i) {
        if (calculate_winner(squares) || squares[i]) {
            return;
        }
        const nextSquares = squares.slice(); /** jsx中const关键字表示不能被重新赋值，但可以修改其内容 */
        if (xIsNext) {
            nextSquares[i] = "X";
        } else {
            nextSquares[i] = "O";
        }
        onPlay(nextSquares);
    }
    const winner = calculate_winner(squares);
    let status;
    if (winner) {
        status = "Winner is " + winner;
    } else {
        status = "Next player: " + (xIsNext ? "X" : "O");
    }
    return (
        <>
            <div className="status">
                {status}
            </div>
            <div className="board-row">
                <Square value={squares[0]} on_SquareClick={() => handle_click(0)} />
                <Square value={squares[1]} on_SquareClick={() => handle_click(1)} />
                <Square value={squares[2]} on_SquareClick={() => handle_click(2)} />
            </div>
            <div className="board-row">
                <Square value={squares[3]} on_SquareClick={() => handle_click(3)} />
                <Square value={squares[4]} on_SquareClick={() => handle_click(4)} />
                <Square value={squares[5]} on_SquareClick={() => handle_click(5)} />
            </div>
            <div className="board-row">
                <Square value={squares[6]} on_SquareClick={() => handle_click(6)} />
                <Square value={squares[7]} on_SquareClick={() => handle_click(7)} />
                <Square value={squares[8]} on_SquareClick={() => handle_click(8)} />
            </div>
        </>
    );
}

export default function Game() {
    const [history, setHistory] = useState([Array(9).fill(null)]);
    const [currentMove, setCurrentMove] = useState(0);
    const xIsNext = currentMove % 2 === 0;
    const currentSquares = history[currentMove];

    function handlePlay(nextSquares) {
        const nextHistory = [...history.slice(0, currentMove + 1), nextSquares];
        setHistory(nextHistory);
        setCurrentMove(nextHistory.length - 1);
    }

    function JumpTo(nextMove) {
        setCurrentMove(nextMove);
    }

    const moves = history.map((squares, move) => {
        let description;
        if (move > 0) {
            description = "Go to move #" + move;
        } else {
            description = "Go to game start";
        }

        return (
            <li key={move}>
                <button className="jump-button" onClick={() => JumpTo(move)}>
                    {description}
                </button>
            </li>
        );
    });
    return (
        <div className="game">
            <div className="game_board">
                <Board xIsNext={xIsNext} squares={currentSquares} onPlay={handlePlay} />
            </div>
            <div className="game-info">
                <ol>{moves}</ol>
            </div>
        </div>
    );
}

function calculate_winner(squares) {
    const lines = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],
        [0, 3, 6],
        [1, 4, 7],
        [2, 5, 8],
        [0, 4, 8],
        [2, 4, 6],
    ];
    for (let i = 0; i < lines.length; i++) {
        const [a, b, c] = lines[i];
        if (squares[a] && squares[a] === squares[b] && squares[a] === squares[c]) {
            return squares[a];
        }
    }
    return null;
}