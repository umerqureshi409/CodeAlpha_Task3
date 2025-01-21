#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

class SudokuSolver {
private:
    static const int grid_size = 9;
    static const int subgrid_size = 3;
    vector<vector<int>> grid;

    struct Cell {
        int row, col;
        set<int> candidates;
    };

   
    bool isValid(int row, int col, int num) const {
       
        for (int x = 0; x < grid_size; x++) {
            if (grid[row][x] == num) return false;
        }
        
       
        for (int x = 0; x < grid_size; x++) {
            if (grid[x][col] == num) return false;
        }
        
        
        int startRow = row - row % subgrid_size;
        int startCol = col - col % subgrid_size;
        
        for (int i = 0; i < subgrid_size; i++) {
            for (int j = 0; j < subgrid_size; j++) {
                if (grid[i + startRow][j + startCol] == num) return false;
            }
        }
        
        return true;
    }

   
    Cell findBestCell() {
        Cell bestCell{-1, -1, set<int>()};
        int minCandidates = grid_size + 1;

        for (int row = 0; row < grid_size; row++) {
            for (int col = 0; col < grid_size; col++) {
                if (grid[row][col] == 0) {
                    set<int> candidates = findCandidates(row, col);
                    if (candidates.size() < minCandidates) {
                        minCandidates = candidates.size();
                        bestCell = {row, col, candidates};
                        
               
                        if (minCandidates == 1) return bestCell;
                    }
                }
            }
        }
        return bestCell;
    }

   
    set<int> findCandidates(int row, int col) const {
        set<int> candidates;
        if (grid[row][col] != 0) return candidates;

        for (int num = 1; num <= grid_size; num++) {
            if (isValid(row, col, num)) {
                candidates.insert(num);
            }
        }
        return candidates;
    }

   
    bool isFull() const {
        for (int row = 0; row < grid_size; row++) {
            for (int col = 0; col < grid_size; col++) {
                if (grid[row][col] == 0) return false;
            }
        }
        return true;
    }

public:
    SudokuSolver() : grid(grid_size, vector<int>(grid_size, 0)) {}

    
    void loadPuzzle(const vector<vector<int>>& puzzle) {
        grid = puzzle;
    }

  
    const vector<vector<int>>& getGrid() const {
        return grid;
    }

    
    bool solve() {
        if (isFull()) return true;

        
        Cell bestCell = findBestCell();
        if (bestCell.row == -1) return false;

      
        for (int num : bestCell.candidates) {
            grid[bestCell.row][bestCell.col] = num;
            
            if (solve()) return true;
            
            
            grid[bestCell.row][bestCell.col] = 0;
        }

        return false;
    }

 
    void print() const {
        for (int row = 0; row < grid_size; row++) {
            if (row % subgrid_size == 0 && row != 0) {
                cout << string(25, '-') << '\n';
            }
            
            for (int col = 0; col < grid_size; col++) {
                if (col % subgrid_size == 0 && col != 0) {
                    cout << "| ";
                }
                
                if (grid[row][col] == 0) {
                    cout << ". ";
                } else {
                    cout << grid[row][col] << " ";
                }
            }
            cout << '\n';
        }
    }

    bool isValid() const {
    
        for (int row = 0; row < grid_size; row++) {
            vector<bool> seen(grid_size + 1, false);
            for (int col = 0; col < grid_size; col++) {
                int current = grid[row][col];
                if (current != 0) {
                    if (seen[current]) return false;
                    seen[current] = true;
                }
            }
        }

        for (int col = 0; col < grid_size; col++) {
            vector<bool> seen(grid_size + 1, false);
            for (int row = 0; row < grid_size; row++) {
                int current = grid[row][col];
                if (current != 0) {
                    if (seen[current]) return false;
                    seen[current] = true;
                }
            }
        }

        
        for (int box = 0; box < grid_size; box++) {
            vector<bool> seen(grid_size + 1, false);
            int rowStart = (box / subgrid_size) * subgrid_size;
            int colStart = (box % subgrid_size) * subgrid_size;
            
            for (int i = 0; i < subgrid_size; i++) {
                for (int j = 0; j < subgrid_size; j++) {
                    int current = grid[rowStart + i][colStart + j];
                    if (current != 0) {
                        if (seen[current]) return false;
                        seen[current] = true;
                    }
                }
            }
        }

        return true;
    }
};
int main() {
    SudokuSolver solver;
    string choice;
    
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"+             SUDOKU PUZZLE SOLVER             +"<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<endl;
    cout<<"Do you want to give puzzle at your own : ('yes' or 'no')"<<endl;
    cin>>choice;
    if(choice == "yes" || choice == "Yes"){
    cout << "Enter your Sudoku puzzle row by row (9 rows, use 0 for empty cells):\n";
    vector<vector<int>> puzzle(9, vector<int>(9));

    for (int i = 0; i < 9; i++) {
        cout << "Row " << i + 1 << ": ";
        string rowInput;
        cin >> rowInput;

        if (rowInput.length() != 9 || !all_of(rowInput.begin(), rowInput.end(), ::isdigit)) {
            cout << "Invalid input. Each row must contain exactly 9 digits (0-9).\n";
            return 1; 
        }

        for (int j = 0; j < 9; j++) {
            puzzle[i][j] = rowInput[j] - '0'; 
        }
    }
    
    solver.loadPuzzle(puzzle);
}
else if (choice == "no" || choice == "No"){
       vector<vector<int>> puzzle = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };
    solver.loadPuzzle(puzzle);

}


    cout << "\nOriginal puzzle:\n";
    solver.print();

    if (solver.solve()) {
        cout << "\nSolved puzzle:\n";
        solver.print();

        if (solver.isValid()) {
            cout << "\nSolution is valid!\n";
        } else {
            cout << "\nWARNING: Solution is invalid!\n";
        }
    } else {
        cout << "\nNo solution exists!\n";
    }

    return 0;
}

